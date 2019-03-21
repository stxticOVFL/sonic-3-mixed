using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using ImpostorEditor2.Actions;
using System.Collections;
using System.Net;
using SharpDX.Direct3D9;
using RSDKv5;
using System.IO;
using Color = System.Drawing.Color;
using MyTabControl;
using System.Runtime.InteropServices;

namespace ImpostorEditor2 {
    public partial class Editor : Form, IDrawArea {
        bool dragged;
        bool startDragged;
        int lastX, lastY, draggedX, draggedY;
        int ShiftX = 0, ShiftY = 0, ScreenWidth, ScreenHeight;

        int ClickedX = -1, ClickedY = -1;

        public Stack<IAction> undo = new Stack<IAction>();
        public Stack<IAction> redo = new Stack<IAction>();

        bool draggingSelection;
        int selectingX, selectingY;
        bool zooming;
        double Zoom = 1;
        int ZoomLevel = 0;

        string DataDirectory;

        GameConfig GameConfig;

        string SelectedZone;
        string SelectedScene;

        internal StageTiles StageTiles;
        internal Scene Scene;

        string SceneFilename = null;

        internal EditorLayer FGHigh;
        internal EditorLayer FGLow;

        internal EditorBackground Background;

        internal EditorLayer EditLayer;

        internal List<EditorLayer> EditorLayers;

        internal TilesToolbar TilesToolbar = null;
        private EntitiesToolbar entitiesToolbar = null;

        internal Dictionary<Point, ushort> TilesClipboard;
        private List<EditorEntity> entitiesClipboard;

        internal int SceneWidth;
        internal int SceneHeight;

        bool scrolling = false;
        bool scrollingDragged = false, wheelClicked = false;
        Point scrollPosition;

        EditorEntities entities;

        public static Editor Instance;

        PropertyGrid propertyGridLayer;

        class MySR : ToolStripSystemRenderer {
            public MySR() { }

            protected override void OnRenderToolStripBorder(ToolStripRenderEventArgs e) {
                //base.OnRenderToolStripBorder(e);
            }
        }

        public Editor() {
            Instance = this;
            InitializeComponent();

            this.splitContainer1.Panel2MinSize = 254;

            GraphicPanel.GotFocus += new EventHandler(OnGotFocus);
            GraphicPanel.LostFocus += new EventHandler(OnLostFocus);

            GraphicPanel.Width = SystemInformation.PrimaryMonitorSize.Width;
            GraphicPanel.Height = SystemInformation.PrimaryMonitorSize.Height;

            SetViewSize();

            toolStrip1.Renderer = new MySR();
            toolStripLayers.Renderer = new MySR();
            statusStrip1.Renderer = new MySR();
            statusStrip1.ForeColor = SystemColors.Control;

            UpdateControls();
        }

        private bool IsEditing() {
            return IsTilesEdit() || IsEntitiesEdit();
        }

        private bool IsTilesEdit() {
            return EditLayer != null;
        }

        private bool IsEntitiesEdit() {
            return EditEntities.Checked;
        }


        private bool IsSelected() {
            if (IsTilesEdit()) {
                return EditLayer.SelectedTiles.Count > 0 || EditLayer.TempSelectionTiles.Count > 0;
            }
            else if (IsEntitiesEdit()) {
                return entities.IsSelected();
            }
            return false;
        }

        private void SetSceneOnlyButtonsState(bool enabled) {
            saveToolStripMenuItem.Enabled = enabled;
            saveAsToolStripMenuItem.Enabled = enabled;
            saveAspngToolStripMenuItem.Enabled = enabled;

            Save.Enabled = enabled;

            zoomInButton.Enabled = enabled && ZoomLevel < 5;
            zoomOutButton.Enabled = enabled && ZoomLevel > -5;

            SetEditButtonsState(enabled);
        }

        private void SetSelectOnlyButtonsState(bool enabled = true) {
            enabled &= IsSelected();
            deleteToolStripMenuItem.Enabled = enabled;
            copyToolStripMenuItem.Enabled = enabled;
            cutToolStripMenuItem.Enabled = enabled;
            duplicateToolStripMenuItem.Enabled = enabled;

            flipHorizontalToolStripMenuItem.Enabled = enabled && IsTilesEdit();
            flipVerticalToolStripMenuItem.Enabled = enabled && IsTilesEdit();

            if (IsEntitiesEdit()) {
                entitiesToolbar.SelectedEntities = entities.SelectedEntities.Select(x => x.Entity).ToList();
            }
        }

        // SetEditButtonsState
        private void SetEditButtonsState(bool enabled) {
            //EditFGLow.Enabled = enabled;
            //EditFGHigh.Enabled = enabled && FGHigh != null;
            EditEntities.Enabled = enabled;

            //EditLayer = null;

            undoToolStripMenuItem.Enabled = enabled && undo.Count > 0;
            redoToolStripMenuItem.Enabled = enabled && redo.Count > 0;

            undoButton.Enabled = enabled && undo.Count > 0;
            redoButton.Enabled = enabled && redo.Count > 0;

            pointerButton.Enabled = enabled && IsTilesEdit();
            selectTool.Enabled = enabled && IsTilesEdit();
            placeTilesButton.Enabled = enabled && IsTilesEdit();

            if (enabled && IsTilesEdit() && TilesClipboard != null)
                pasteToolStripMenuItem.Enabled = true;
            else
                pasteToolStripMenuItem.Enabled = false;

            if (IsTilesEdit()) {
                if (TilesToolbar == null) {
                    TilesToolbar = new TilesToolbar(StageTiles);
                    TilesToolbar.TileDoubleClick = new Action<int>(x => {
                        EditorPlaceTile(new Point((int)(ShiftX / Zoom) + EditorLayer.TILE_SIZE - 1, (int)(ShiftY / Zoom) + EditorLayer.TILE_SIZE - 1), x);
                    });
                    TilesToolbar.TileOptionChanged = new Action<int, bool>((option, state) => {
                        EditLayer.SetPropertySelected(option + 12, state);
                    });

                    TilesToolbar.Dock = DockStyle.Fill;

                    UpdateTilesOptions();

                    splitContainer1.Panel2Collapsed = false;
                    splitContainer1.SplitterDistance = 1900;

                    if (!tabControlSidebar.HasTab(tabLayerTiles))
                        tabControlSidebar.AddTab("Tiles", tabLayerTiles);

                    tabLayerTiles.Controls.Add(TilesToolbar);
                }
                
                TilesToolbar.ShowShortcuts = placeTilesButton.Checked;
            }
            else {
                tabControlSidebar.RemoveTab(tabLayerTiles);

                TilesToolbar?.Dispose();
                TilesToolbar = null;
            }
            if (IsEntitiesEdit()) {
                if (entitiesToolbar == null) {
                    entitiesToolbar = new EntitiesToolbar();
                    entitiesToolbar.SelectedEntity = new Action<int>(x => {
                        entities.SelectSlot(x);
                        SetSelectOnlyButtonsState();
                    });
                    entitiesToolbar.AddAction = new Action<IAction>(x => {
                        undo.Push(x);
                        redo.Clear();
                        UpdateControls();
                    });
                    //splitContainer1.Panel2.Controls.Clear();
                    //splitContainer1.Panel2.Controls.Add(entitiesToolbar);
                    //splitContainer1.Panel2Collapsed = false;
                    //entitiesToolbar.Width = splitContainer1.Panel2.Width - 2;
                    //entitiesToolbar.Height = splitContainer1.Panel2.Height - 2;

                    splitContainer1.Panel2Collapsed = false;
                    splitContainer1.SplitterDistance = 1900;

                    if (!tabControlSidebar.HasTab(tabEntities))
                        tabControlSidebar.AddTab("Entity Properties", tabEntities);

                    tabEntities.Controls.Add(entitiesToolbar);

                    Form1_Resize(null, null);
                }
                UpdateEntitiesToolbarList();
                //entitiesToolbar.SelectedEntities = entities.SelectedEntities.Select(x => x.Entity).ToList();
            }
            else {
                tabControlSidebar.RemoveTab(tabEntities);

                entitiesToolbar?.Dispose();
                entitiesToolbar = null;
            }
            if (TilesToolbar == null && entitiesToolbar == null) {
                //splitContainer1.Panel2Collapsed = true;
                Form1_Resize(null, null);
            }

            SetSelectOnlyButtonsState(enabled);
        }

        private void UpdateEntitiesToolbarList() {
            entitiesToolbar.Entities = entities.Entities.Select(x => x.Entity).ToList();
        }

        private void UpdateTilesOptions() {
            if (IsTilesEdit()) {
                List<ushort> values = EditLayer.GetSelectedValues();
                if (values.Count > 0) {
                    for (int i = 0; i < 4; ++i) {
                        bool set = ((values[0] & (1 << (i + 12))) != 0);
                        bool unk = false;
                        foreach (ushort value in values) {
                            if (set != ((value & (1 << (i + 12))) != 0)) {
                                unk = true;
                                break;
                            }
                        }
                        TilesToolbar.SetTileOptionState(i, unk ? TilesToolbar.TileOptionState.Indeterminate : set ? TilesToolbar.TileOptionState.Checked : TilesToolbar.TileOptionState.Unchcked);
                    }
                }
                else {
                    for (int i = 0; i < 4; ++i)
                        TilesToolbar.SetTileOptionState(i, TilesToolbar.TileOptionState.Disabled);
                }
            }
        }

        private void UpdateControls() {
            SetSceneOnlyButtonsState(Scene != null);
        }

        public void OnGotFocus(object sender, EventArgs e) {
        }
        public void OnLostFocus(object sender, EventArgs e) {
        }

        public void EditorPlaceTile(Point position, int tile) {
            Dictionary<Point, ushort> tiles = new Dictionary<Point, ushort>();
            tiles[new Point(0, 0)] = (ushort)tile;
            EditLayer?.PasteFromClipboard(position, tiles);
            UpdateEditLayerActions();
        }

        public void MagnetDisable() {
        }

        private void UpdateEditLayerActions() {
            if (EditLayer != null) {
                List<IAction> actions = EditLayer.Actions;
                if (actions.Count > 0) redo.Clear();
                while (actions.Count > 0) {
                    bool create_new = false;
                    if (undo.Count == 0 || !(undo.Peek() is ActionsGroup)) {
                        create_new = true;
                    }
                    else {
                        create_new = (undo.Peek() as ActionsGroup).IsClosed;
                    }
                    if (create_new) {
                        undo.Push(new ActionsGroup());
                    }
                    (undo.Peek() as ActionsGroup).AddAction(actions[0]);
                    actions.RemoveAt(0);
                }
                UpdateControls();
            }
        }

        public void DeleteSelected() {
            EditLayer?.DeleteSelected();
            UpdateEditLayerActions();

            if (IsEntitiesEdit()) {
                entities.DeleteSelected();
                UpdateLastEntityAction();
            }
        }

        public void UpdateLastEntityAction() {
            if (entities.LastAction != null) {
                redo.Clear();
                undo.Push(entities.LastAction);
                entities.LastAction = null;
                UpdateControls();
            }

        }

        public void GraphicPanel_OnKeyDown(object sender, KeyEventArgs e) {
            if (e.KeyCode == Keys.ControlKey) {
                if (IsTilesEdit() && placeTilesButton.Checked)
                    TilesToolbar.SetSelectTileOption(0, true);
            }
            else if (e.KeyCode == Keys.ShiftKey) {
                if (IsTilesEdit() && placeTilesButton.Checked)
                    TilesToolbar.SetSelectTileOption(1, true);
            }
            else if (e.Control && e.KeyCode == Keys.O) {
                Open_Click(null, null);
            }
            else if (e.Control && e.KeyCode == Keys.N) {
                New_Click(null, null);
            }
            else if (e.Control && e.KeyCode == Keys.S) {
                Save_Click(null, null);
            }
            else if (e.Control && (e.KeyCode == Keys.D0 || e.KeyCode == Keys.NumPad0)) {
                SetZoomLevel(0, new Point(0, 0));
            }
            else if (e.KeyCode == Keys.Z) {
                EditorUndo();
            }
            else if (e.KeyCode == Keys.Y) {
                EditorRedo();
            }
            if (IsEditing()) {
                if (e.Control) {
                    if (e.KeyCode == Keys.V) {
                        pasteToolStripMenuItem_Click(sender, e);
                    }
                }
                if (IsSelected()) {
                    if (e.KeyData == Keys.Delete) {
                        DeleteSelected();
                    }
                    else if (e.KeyData == Keys.Up || e.KeyData == Keys.Down || e.KeyData == Keys.Left || e.KeyData == Keys.Right) {
                        int x = 0, y = 0;
                        switch (e.KeyData) {
                            case Keys.Up: y = -1; break;
                            case Keys.Down: y = 1; break;
                            case Keys.Left: x = -1; break;
                            case Keys.Right: x = 1; break;
                        }
                        EditLayer?.MoveSelectedQuonta(new Point(x, y));
                        UpdateEditLayerActions();

                        if (IsEntitiesEdit()) {
                            entities.MoveSelected(new Point(0, 0), new Point(x, y), false);
                            entitiesToolbar.UpdateCurrentEntityProperites();

                            // Try to merge with last move
                            if (undo.Count > 0 && undo.Peek() is ActionMoveEntities && (undo.Peek() as ActionMoveEntities).UpdateFromKey(entities.SelectedEntities, new Point(x, y))) { }
                            else {
                                undo.Push(new ActionMoveEntities(entities.SelectedEntities.ToList(), new Point(x, y), true));
                                redo.Clear();
                                UpdateControls();
                            }
                        }
                    }
                    else if (e.KeyData == Keys.F) {
                        if (IsTilesEdit())
                            flipVerticalToolStripMenuItem_Click(sender, e);
                    }
                    else if (e.KeyData == Keys.M) {
                        if (IsTilesEdit())
                            flipHorizontalToolStripMenuItem_Click(sender, e);
                    }
                    if (e.Control) {
                        if (e.KeyCode == Keys.X) {
                            cutToolStripMenuItem_Click(sender, e);
                        }
                        else if (e.KeyCode == Keys.C) {
                            copyToolStripMenuItem_Click(sender, e);
                        }
                        else if (e.KeyCode == Keys.D) {
                            duplicateToolStripMenuItem_Click(sender, e);
                        }
                    }
                }
            }
        }

        public void GraphicPanel_OnKeyUp(object sender, KeyEventArgs e) {
            if (e.KeyCode == Keys.ControlKey) {
                if (IsTilesEdit() && placeTilesButton.Checked)
                    TilesToolbar.SetSelectTileOption(0, false);
            }
            else if (e.KeyCode == Keys.ShiftKey) {
                if (IsTilesEdit() && placeTilesButton.Checked)
                    TilesToolbar.SetSelectTileOption(1, false);
            }
        }

        private bool CtrlPressed() {
            return ModifierKeys.HasFlag(Keys.Control);
        }

        private bool ShiftPressed() {
            return ModifierKeys.HasFlag(Keys.Shift);
        }

        private void GraphicPanel_OnMouseDoubleClick(object sender, MouseEventArgs e) {
        }

        private void GraphicPanel_OnMouseMove(object sender, MouseEventArgs e) {
            if (ClickedX != -1) {
                Point clicked_point = new Point((int)(ClickedX / Zoom), (int)(ClickedY / Zoom));
                // There was just a click now we can determine that this click is dragging
                if (IsTilesEdit()) {
                    if (EditLayer.IsPointSelected(clicked_point)) {
                        // Start dragging the tiles
                        dragged = true;
                        startDragged = true;
                        EditLayer.StartDrag();
                    }
                    else if (!selectTool.Checked && !ShiftPressed() && !CtrlPressed() && EditLayer.HasTileAt(clicked_point)) {
                        // Start dragging the single selected tile
                        EditLayer.Select(clicked_point);
                        dragged = true;
                        startDragged = true;
                        EditLayer.StartDrag();
                    }
                    else {
                        // Start drag selection
                        //EditLayer.Select(clicked_point, ShiftPressed || CtrlPressed, CtrlPressed);
                        if (!ShiftPressed() && !CtrlPressed())
                            Deselect();
                        UpdateControls();
                        UpdateEditLayerActions();
                        draggingSelection = true;
                        selectingX = ClickedX;
                        selectingY = ClickedY;
                    }
                }
                else if (IsEntitiesEdit()) {
                    if (entities.GetEntityAt(clicked_point)?.Selected ?? false) {
                        ClickedX = e.X;
                        ClickedY = e.Y;
                        // Start dragging the entity
                        dragged = true;
                        draggedX = 0;
                        draggedY = 0;
                        startDragged = true;
                    }
                    else {
                        // Start drag selection
                        if (!ShiftPressed() && !CtrlPressed())
                            Deselect();
                        UpdateControls();
                        draggingSelection = true;
                        selectingX = ClickedX;
                        selectingY = ClickedY;
                    }
                }
                ClickedX = -1;
                ClickedY = -1;
            }
            if (scrolling) {
                if (wheelClicked) {
                    scrollingDragged = true;
                }

                int xMove = (hScrollBar1.Visible) ? e.X - ShiftX - scrollPosition.X : 0;
                int yMove = (vScrollBar1.Visible) ? e.Y - ShiftY - scrollPosition.Y : 0;

                if (Math.Abs(xMove) < 15) xMove = 0;
                if (Math.Abs(yMove) < 15) yMove = 0;

                if (xMove > 0) {
                    if (yMove > 0) Cursor = Cursors.PanSE;
                    else if (yMove < 0) Cursor = Cursors.PanNE;
                    else Cursor = Cursors.PanEast;
                }
                else if (xMove < 0) {
                    if (yMove > 0) Cursor = Cursors.PanSW;
                    else if (yMove < 0) Cursor = Cursors.PanNW;
                    else Cursor = Cursors.PanWest;
                }
                else {
                    if (yMove > 0) Cursor = Cursors.PanSouth;
                    else if (yMove < 0) Cursor = Cursors.PanNorth;
                    else {
                        if (vScrollBar1.Visible && hScrollBar1.Visible) Cursor = Cursors.NoMove2D;
                        else if (vScrollBar1.Visible) Cursor = Cursors.NoMoveVert;
                        else if (hScrollBar1.Visible) Cursor = Cursors.NoMoveHoriz;
                    }
                }

                Point position = new Point(ShiftX, ShiftY); ;
                int x = xMove / 10 + position.X;
                int y = yMove / 10 + position.Y;

                if (x < 0) x = 0;
                if (y < 0) y = 0;
                if (x > hScrollBar1.Maximum - hScrollBar1.LargeChange) x = hScrollBar1.Maximum - hScrollBar1.LargeChange;
                if (y > vScrollBar1.Maximum - vScrollBar1.LargeChange) y = vScrollBar1.Maximum - vScrollBar1.LargeChange;

                if (x != position.X || y != position.Y) {
                    if (vScrollBar1.Visible) {
                        vScrollBar1.Value = y;
                    }
                    if (hScrollBar1.Visible) {
                        hScrollBar1.Value = x;
                    }
                    GraphicPanel.Render();
                    GraphicPanel.OnMouseMoveEventCreate();
                }
            }

            toolStripStatusLabel1.Text = 
                "X: " + (int)(e.X / Zoom) + " (0x" + ((int)(e.X / Zoom)).ToString("X") + ") " + 
                "Y: " + (int)(e.Y / Zoom) + " (0x" + ((int)(e.Y / Zoom)).ToString("X") + ") ";

            if (EditLayer != null)
                toolStripStatusLabel1.Text += "Tile ID: " + (EditLayer.GetTileAt(new Point((int)(e.X / Zoom), (int)(e.Y / Zoom))) & 0x3FF).ToString("X");

            if (IsEditing()) {
                if (IsTilesEdit() && placeTilesButton.Checked) {
                    Point p = new Point((int)(e.X / Zoom), (int)(e.Y / Zoom));
                    if (e.Button == MouseButtons.Left) {
                        // Place tile
                        if (TilesToolbar.SelectedTile != -1) {
                            if (EditLayer.GetTileAt(p) != TilesToolbar.SelectedTile) {
                                EditorPlaceTile(p, TilesToolbar.SelectedTile);
                            }
                            else if (!EditLayer.IsPointSelected(p)) {
                                EditLayer.Select(p);
                            }
                        }
                    }
                    else if (e.Button == MouseButtons.Right) {
                        // Remove tile
                        if (!EditLayer.IsPointSelected(p)) {
                            EditLayer.Select(p);
                        }
                        DeleteSelected();
                    }
                }
                if (draggingSelection || dragged) {
                    Point position = new Point(ShiftX, ShiftY); ;
                    int ScreenMaxX = position.X + splitContainer1.Panel1.Width - System.Windows.Forms.SystemInformation.VerticalScrollBarWidth;
                    int ScreenMaxY = position.Y + splitContainer1.Panel1.Height - System.Windows.Forms.SystemInformation.HorizontalScrollBarHeight;
                    int ScreenMinX = position.X;
                    int ScreenMinY = position.Y;

                    int x = position.X;
                    int y = position.Y;

                    if (e.X > ScreenMaxX) {
                        x += (e.X - ScreenMaxX) / 10;
                    }
                    else if (e.X < ScreenMinX) {
                        x += (e.X - ScreenMinX) / 10;
                    }
                    if (e.Y > ScreenMaxY) {
                        y += (e.Y - ScreenMaxY) / 10;
                    }
                    else if (e.Y < ScreenMinY) {
                        y += (e.Y - ScreenMinY) / 10;
                    }

                    if (x < 0) x = 0;
                    if (y < 0) y = 0;
                    if (x > hScrollBar1.Maximum - hScrollBar1.LargeChange) x = hScrollBar1.Maximum - hScrollBar1.LargeChange;
                    if (y > vScrollBar1.Maximum - vScrollBar1.LargeChange) y = vScrollBar1.Maximum - vScrollBar1.LargeChange;

                    if (x != position.X || y != position.Y) {
                        if (vScrollBar1.Visible) {
                            vScrollBar1.Value = y;
                        }
                        if (hScrollBar1.Visible) {
                            hScrollBar1.Value = x;
                        }
                        GraphicPanel.Render();
                        GraphicPanel.OnMouseMoveEventCreate();
                    }

                }

                if (draggingSelection) {
                    if (selectingX != e.X && selectingY != e.Y) {
                        int x1 = (int)(selectingX / Zoom), x2 = (int)(e.X / Zoom);
                        int y1 = (int)(selectingY / Zoom), y2 = (int)(e.Y / Zoom);
                        if (x1 > x2) {
                            x1 = (int)(e.X / Zoom);
                            x2 = (int)(selectingX / Zoom);
                        }
                        if (y1 > y2) {
                            y1 = (int)(e.Y / Zoom);
                            y2 = (int)(selectingY / Zoom);
                        }
                        EditLayer?.TempSelection(new Rectangle(x1, y1, x2 - x1, y2 - y1), CtrlPressed());
                        UpdateTilesOptions();

                        if (IsEntitiesEdit()) entities.TempSelection(new Rectangle(x1, y1, x2 - x1, y2 - y1), CtrlPressed());
                    }
                }
                else if (dragged) {
                    Point oldPoint = new Point((int)(lastX / Zoom), (int)(lastY / Zoom));
                    Point newPoint = new Point((int)(e.X / Zoom), (int)(e.Y / Zoom));

                    EditLayer?.MoveSelected(oldPoint, newPoint, CtrlPressed());
                    UpdateEditLayerActions();
                    if (IsEntitiesEdit()) {
                        try {
                            entities.MoveSelected(oldPoint, newPoint, CtrlPressed() && startDragged);
                        }
                        catch (EditorEntities.TooManyEntitiesException) {
                            MessageBox.Show("Too many entities! (limit: 2048)");
                            dragged = false;
                            return;
                        }
                        draggedX += newPoint.X - oldPoint.X;
                        draggedY += newPoint.Y - oldPoint.Y;
                        if (CtrlPressed() && startDragged) {
                            UpdateEntitiesToolbarList();
                            SetSelectOnlyButtonsState();
                        }
                        entitiesToolbar.UpdateCurrentEntityProperites();
                    }
                    startDragged = false;
                }
            }
            lastX = e.X;
            lastY = e.Y;
        }
        private void GraphicPanel_OnMouseDown(object sender, MouseEventArgs e) {
            //GraphicPanel.Focus();
            if (e.Button == MouseButtons.Left) {
                if (IsEditing() && !dragged) {
                    if (IsTilesEdit()) {
                        if (placeTilesButton.Checked) {
                            // Place tile
                            if (TilesToolbar.SelectedTile != -1) {
                                EditorPlaceTile(new Point((int)(e.X / Zoom), (int)(e.Y / Zoom)), TilesToolbar.SelectedTile);
                            }
                        }
                        else {
                            ClickedX = e.X;
                            ClickedY = e.Y;
                        }
                    }
                    else if (IsEntitiesEdit()) {
                        Point clicked_point = new Point((int)(e.X / Zoom), (int)(e.Y / Zoom));
                        if (entities.GetEntityAt(clicked_point)?.Selected ?? false) {
                            // We will have to check if this dragging or clicking
                            ClickedX = e.X;
                            ClickedY = e.Y;
                        }
                        else if (!ShiftPressed() && !CtrlPressed() && entities.GetEntityAt(clicked_point) != null) {
                            entities.Select(clicked_point);
                            SetSelectOnlyButtonsState();
                            // Start dragging the single selected entity
                            dragged = true;
                            draggedX = 0;
                            draggedY = 0;
                            startDragged = true;
                        }
                        else {
                            ClickedX = e.X;
                            ClickedY = e.Y;
                        }
                    }
                }

                if (scrolling) {
                    scrolling = false;
                    Cursor = Cursors.Default;
                }
            }
            else if (e.Button == MouseButtons.Right) {
                if (IsTilesEdit() && placeTilesButton.Checked) {
                    // Remove tile
                    Point p = new Point((int)(e.X / Zoom), (int)(e.Y / Zoom));
                    if (!EditLayer.IsPointSelected(p)) {
                        EditLayer.Select(p);
                    }
                    DeleteSelected();
                }
            }
            else if (e.Button == MouseButtons.Middle) {
                wheelClicked = true;
                scrolling = true;
                scrollingDragged = false;
                scrollPosition = new Point(e.X - ShiftX, e.Y - ShiftY);
                if (vScrollBar1.Visible && hScrollBar1.Visible) {
                    Cursor = Cursors.NoMove2D;
                }
                else if (vScrollBar1.Visible) {
                    Cursor = Cursors.NoMoveVert;
                }
                else if (hScrollBar1.Visible) {
                    Cursor = Cursors.NoMoveHoriz;
                }
                else {
                    scrolling = false;
                }
            }
        }
        private void GraphicPanel_OnMouseUp(object sender, MouseEventArgs e) {
            if (e.Button == MouseButtons.Left) {
                if (IsEditing()) {
                    MagnetDisable();
                    if (draggingSelection) {
                        if (selectingX != e.X && selectingY != e.Y) {

                            int x1 = (int)(selectingX / Zoom), x2 = (int)(e.X / Zoom);
                            int y1 = (int)(selectingY / Zoom), y2 = (int)(e.Y / Zoom);
                            if (x1 > x2) {
                                x1 = (int)(e.X / Zoom);
                                x2 = (int)(selectingX / Zoom);
                            }
                            if (y1 > y2) {
                                y1 = (int)(e.Y / Zoom);
                                y2 = (int)(selectingY / Zoom);
                            }

                            EditLayer?.Select(new Rectangle(x1, y1, x2 - x1, y2 - y1), ShiftPressed() || CtrlPressed(), CtrlPressed());
                            if (IsEntitiesEdit()) entities.Select(new Rectangle(x1, y1, x2 - x1, y2 - y1), ShiftPressed() || CtrlPressed(), CtrlPressed());
                            SetSelectOnlyButtonsState();
                            UpdateEditLayerActions();
                        }
                        draggingSelection = false;
                        EditLayer?.EndTempSelection();
                        if (IsEntitiesEdit()) entities.EndTempSelection();
                    }
                    else {
                        if (ClickedX != -1) {
                            // So it was just click
                            Point clicked_point = new Point((int)(ClickedX / Zoom), (int)(ClickedY / Zoom));
                            if (IsTilesEdit()) {
                                EditLayer.Select(clicked_point, ShiftPressed() || CtrlPressed(), CtrlPressed());
                                UpdateEditLayerActions();
                            }
                            else if (IsEntitiesEdit()) {
                                entities.Select(clicked_point, ShiftPressed() || CtrlPressed(), CtrlPressed());
                            }
                            SetSelectOnlyButtonsState();
                            ClickedX = -1;
                            ClickedY = -1;
                        }
                        if (dragged && (draggedX != 0 || draggedY != 0)) {
                            if (IsEntitiesEdit()) {
                                IAction action = new ActionMoveEntities(entities.SelectedEntities.ToList(), new Point(draggedX, draggedY));
                                if (entities.LastAction != null) {
                                    // If it is move & duplicate, merge them together
                                    var taction = new ActionsGroup();
                                    taction.AddAction(entities.LastAction);
                                    entities.LastAction = null;
                                    taction.AddAction(action);
                                    taction.Close();
                                    action = taction;
                                }
                                undo.Push(action);
                                redo.Clear();
                                UpdateControls();
                            }
                        }
                        dragged = false;
                    }
                }
            }
            else if (e.Button == MouseButtons.Middle) {
                wheelClicked = false;
                if (scrollingDragged) {
                    scrolling = false;
                    Cursor = Cursors.Default;
                }
            }
        }

        private void GraphicPanel_MouseWheel(object sender, MouseEventArgs e) {
            //GraphicPanel.Focus();
            if (CtrlPressed()) {
                int change = e.Delta / 120;
                ZoomLevel += change;
                if (ZoomLevel > 5) ZoomLevel = 5;
                if (ZoomLevel < -5) ZoomLevel = -5;

                SetZoomLevel(ZoomLevel, new Point(e.X - ShiftX, e.Y - ShiftY));
            }
            else {
                if (vScrollBar1.Visible) {
                    int y = vScrollBar1.Value - e.Delta;
                    if (y < 0) y = 0;
                    if (y > vScrollBar1.Maximum - vScrollBar1.LargeChange) y = vScrollBar1.Maximum - vScrollBar1.LargeChange;
                    vScrollBar1.Value = y;
                }

            }
        }

        public void SetZoomLevel(int zoom_level, Point zoom_point) {
            double old_zoom = Zoom;

            ZoomLevel = zoom_level;

            switch (ZoomLevel) {
                case 5: Zoom = 4; break;
                case 4: Zoom = 3; break;
                case 3: Zoom = 2; break;
                case 2: Zoom = 3 / 2.0; break;
                case 1: Zoom = 5 / 4.0; break;
                case 0: Zoom = 1; break;
                case -1: Zoom = 2 / 3.0; break;
                case -2: Zoom = 1 / 2.0; break;
                case -3: Zoom = 1 / 3.0; break;
                case -4: Zoom = 1 / 4.0; break;
                case -5: Zoom = 1 / 8.0; break;
            }

            zooming = true;

            int oldShiftX = ShiftX;
            int oldShiftY = ShiftY;

            if (Scene != null)
                SetViewSize((int)(SceneWidth * Zoom), (int)(SceneHeight * Zoom));

            if (hScrollBar1.Visible) {
                ShiftX = (int)((zoom_point.X + oldShiftX) / old_zoom * Zoom - zoom_point.X);
                ShiftX = Math.Min(hScrollBar1.Maximum - hScrollBar1.LargeChange, Math.Max(0, ShiftX));
                hScrollBar1.Value = ShiftX;
            }
            if (vScrollBar1.Visible) {
                ShiftY = (int)((zoom_point.Y + oldShiftY) / old_zoom * Zoom - zoom_point.Y);
                ShiftY = Math.Min(vScrollBar1.Maximum - vScrollBar1.LargeChange, Math.Max(0, ShiftY));
                vScrollBar1.Value = ShiftY;
            }

            zooming = false;

            UpdateControls();
        }

        private bool load() {
            /*
            if (DataDirectory == null) {
                do {
                    MessageBox.Show("Please select the \"Data\" folder", "Message");

                    FolderSelectDialog folderBrowserDialog = new FolderSelectDialog();
                    folderBrowserDialog.Title = "Select Data Folder";

                    if (!folderBrowserDialog.ShowDialog())
                        return false;

                    DataDirectory = folderBrowserDialog.FileName;
                }
                while (!File.Exists(Path.Combine(DataDirectory, "Game", "GameConfig.bin")));

                GameConfig = new GameConfig(Path.Combine(DataDirectory, "Game", "GameConfig.bin"));
            }
            //*/
            return true;
        }

        void UnloadScene() {
            Scene = null;
            SceneFilename = null;

            SelectedScene = null;
            SelectedZone = null;

            if (StageTiles != null) StageTiles.Dispose();
            StageTiles = null;

            if (FGHigh != null) FGHigh.Dispose();
            FGHigh = null;
            if (FGLow != null) FGLow.Dispose();
            FGLow = null;

            Background = null;

            TilesClipboard = null;
            entitiesClipboard = null;

            entities = null;

            Zoom = 1;
            ZoomLevel = 0;

            undo.Clear();
            redo.Clear();
            
            EditEntities.Checked = false;

            SetViewSize();

            UpdateControls();
        }

        public void PopulateLayerToolstrip() {
            System.Drawing.Font font = new System.Drawing.Font("Segoe UI", 9, FontStyle.Regular, GraphicsUnit.Point);
            System.Drawing.Font fontBold = new System.Drawing.Font("Segoe UI", 9, FontStyle.Bold, GraphicsUnit.Point);

            toolStripLayers.Items.Clear();

            ToolStripLabel layersLabel = new ToolStripLabel("Layers");
            layersLabel.ForeColor = Color.FromArgb(0, 127, 255);
            layersLabel.Font = font;
            toolStripLayers.Items.Add(layersLabel);

            int i = 1;
            foreach (SceneLayer layer in Scene.Layers) {
                EditorLayer editorLayer = EditorLayers[i - 1];

                ToolStripDropDownButton layerLabel = new ToolStripDropDownButton(i.ToString());
                layerLabel.ShowDropDownArrow = false;
                layerLabel.ForeColor = SystemColors.Control;
                layerLabel.Font = font;
                layerLabel.ToolTipText = layer.Name;
                toolStripLayers.Items.Add(layerLabel);
                editorLayer.ToolStripButton = layerLabel;

                ToolStripMenuItem menuItemName = new ToolStripMenuItem("Layer: " + layer.Name);
                menuItemName.Enabled = false;
                menuItemName.Font = font;
                layerLabel.DropDownItems.Add(menuItemName);

                layerLabel.DropDownItems.Add(new ToolStripSeparator());

                ToolStripMenuItem menuItemVisible = new ToolStripMenuItem("Visible");
                menuItemVisible.CheckOnClick = true;
                menuItemVisible.Font = font;
                menuItemVisible.Checked = editorLayer.Visible;
                menuItemVisible.CheckedChanged += new EventHandler(delegate (Object o, EventArgs a) {
                    editorLayer.Visible = menuItemVisible.Checked;
                });

                layerLabel.DropDownItems.Add(menuItemVisible);

                ToolStripMenuItem menuItemSort = new ToolStripMenuItem("Order");
                menuItemSort.Font = font;
                layerLabel.DropDownItems.Add(menuItemSort);

                {
                    ToolStripMenuItem menuItemSendToBack = new ToolStripMenuItem("Send To Back");
                    menuItemSendToBack.Font = font;
                    menuItemSendToBack.Click += new EventHandler(delegate (Object o, EventArgs a) {
                        int new_index = 0;

                        Scene.Layers.Remove(editorLayer.Layer);
                        EditorLayers.Remove(editorLayer);

                        Scene.Layers.Insert(new_index, editorLayer.Layer);
                        EditorLayers.Insert(new_index, editorLayer);

                        PopulateLayerToolstrip();
                    });
                    menuItemSort.DropDownItems.Add(menuItemSendToBack);

                    menuItemSort.DropDownItems.Add(new ToolStripSeparator());

                    ToolStripMenuItem menuItemSendBackward = new ToolStripMenuItem("Send Backward");
                    menuItemSendBackward.Font = font;
                    menuItemSendBackward.Click += new EventHandler(delegate (Object o, EventArgs a) {
                        int new_index = EditorLayers.IndexOf(editorLayer) - 1;
                        if (new_index < 0)
                            return;

                        Scene.Layers.Remove(editorLayer.Layer);
                        EditorLayers.Remove(editorLayer);

                        Scene.Layers.Insert(new_index, editorLayer.Layer);
                        EditorLayers.Insert(new_index, editorLayer);

                        PopulateLayerToolstrip();
                    });
                    menuItemSort.DropDownItems.Add(menuItemSendBackward);

                    ToolStripMenuItem menuItemBringForward = new ToolStripMenuItem("Bring Forward");
                    menuItemBringForward.Font = font;
                    menuItemBringForward.Click += new EventHandler(delegate (Object o, EventArgs a) {
                        int new_index = EditorLayers.IndexOf(editorLayer) + 1;
                        if (new_index >= EditorLayers.Count)
                            return;

                        Scene.Layers.Remove(editorLayer.Layer);
                        EditorLayers.Remove(editorLayer);

                        Scene.Layers.Insert(new_index, editorLayer.Layer);
                        EditorLayers.Insert(new_index, editorLayer);

                        PopulateLayerToolstrip();
                    });
                    menuItemSort.DropDownItems.Add(menuItemBringForward);

                    menuItemSort.DropDownItems.Add(new ToolStripSeparator());

                    ToolStripMenuItem menuItemBringToFront = new ToolStripMenuItem("Bring To Front");
                    menuItemBringToFront.Font = font;
                    menuItemBringToFront.Click += new EventHandler(delegate (Object o, EventArgs a) {
                        Scene.Layers.Remove(editorLayer.Layer);
                        EditorLayers.Remove(editorLayer);

                        Scene.Layers.Add(editorLayer.Layer);
                        EditorLayers.Add(editorLayer);

                        PopulateLayerToolstrip();
                    });
                    menuItemSort.DropDownItems.Add(menuItemBringToFront);
                }

                layerLabel.DropDownItems.Add(new ToolStripSeparator());

                ToolStripMenuItem menuItemProperties = new ToolStripMenuItem("Properties");
                menuItemProperties.Font = font;
                menuItemProperties.Click += new EventHandler(delegate (Object o, EventArgs a) {
                    if (!tabControlSidebar.HasTab(tabLayerProperties))
                        tabControlSidebar.AddTab("Layer Properties", tabLayerProperties);
                    splitContainer1.Panel2Collapsed = false;
                    splitContainer1.SplitterDistance = 1900;
                    propertyGridLayer.SelectedObject = editorLayer;
                });
                layerLabel.DropDownItems.Add(menuItemProperties);

                ToolStripMenuItem menuItemEdit = new ToolStripMenuItem("Edit");
                menuItemEdit.Font = font;
                menuItemEdit.Click += new EventHandler(delegate (Object o, EventArgs a) {
                    if (EditLayer == editorLayer)
                        EditLayer = null;
                    else
                        EditLayer = editorLayer;
                });
                layerLabel.DropDownItems.Add(menuItemEdit);

                ToolStripMenuItem menuItemScrollingInfo = new ToolStripMenuItem("Scrolling Info");
                menuItemScrollingInfo.Font = font;
                menuItemScrollingInfo.Click += new EventHandler(delegate (Object o, EventArgs a) {
                    string[] str_rels = TilesList.Prompt.ShowDialog("comma separated", "ScrollInfo Relative Xs").Split(',');
                    if (str_rels.Length == 0)
                        return;

                    int[] rels = new int[str_rels.Length];

                    if (str_rels[0] == "-1") {
                        editorLayer.Layer.ScrollingInfo.Clear();
                        
                        for (int p = 0; p < editorLayer.Layer.Height * 16; p++) {
                            editorLayer.Layer.ScrollIndexes[p] = 0;
                        }
                        return;
                    }

                    // 0.250f, 0.21875f,  0.1875f, 0.15625f,   0.125f, 0.09375f,  0.0625f, 0.09375f,   0.125f, 0.15625f,  0.1875f, 0.21875f,   0.250f,   0.250f,   0.125f
                    for (int ib = 0; ib < rels.Length; ib++) {
                        str_rels[ib] = str_rels[ib].Trim().Replace("f", "");
                        rels[ib] = (int)(Convert.ToSingle(str_rels[ib]) * 256);
                        Console.WriteLine("rels[ib]: " + rels[ib].ToString("X"));
                    }

                    string[] str_sizes = TilesList.Prompt.ShowDialog("comma separated", "ScrollInfo Sizes").Split(',');
                    int[] sizes = new int[str_sizes.Length];

                    // 0x0040,   0x0008,   0x0008,   0x0005,   0x0005,   0x0006,   0x00F0,   0x0006,   0x0005,   0x0005,   0x0008,   0x0008,   0x0030,   0x80C0,   0x7FFF
                    for (int ib = 0; ib < sizes.Length; ib++) {
                        str_sizes[ib] = str_sizes[ib].Trim();
                        sizes[ib] = Convert.ToInt32(str_sizes[ib], 16);
                    }

                    editorLayer.Layer.ScrollingInfo.Clear();
                    for (int ib = 0; ib < rels.Length; ib++) {
                        editorLayer.Layer.ScrollingInfo.Add(new SceneLayer.ScrollInfo((ushort)rels[ib]));
                    }

                    int py = 0;
                    for (int ib = 0; ib < sizes.Length; ib++) {
                        for (int p = py; p < py + sizes[ib] && p < editorLayer.Layer.Height * 16; p++) {
                            editorLayer.Layer.ScrollIndexes[p] = (byte)ib;
                            //Console.WriteLine("editorLayer.Layer.ScrollIndexes[" + p + "]: " + editorLayer.Layer.ScrollIndexes[p]);
                        }
                        py += sizes[ib];
                    }
                });
                layerLabel.DropDownItems.Add(menuItemScrollingInfo);

                layerLabel.DropDownItems.Add(new ToolStripSeparator());

                ToolStripMenuItem menuItemDelete = new ToolStripMenuItem("Delete");
                menuItemDelete.Font = font;
                menuItemDelete.Click += new EventHandler(delegate (Object o, EventArgs a) {
                    if (EditLayer == editorLayer)
                        EditLayer = null;

                    Scene.Layers.Remove(editorLayer.Layer);
                    EditorLayers.Remove(editorLayer);

                    PopulateLayerToolstrip();
                });
                layerLabel.DropDownItems.Add(menuItemDelete);

                layerLabel.MouseDown += new MouseEventHandler(delegate (object o, MouseEventArgs e) {
                    if (e.Button == MouseButtons.Right) {
                        if (EditLayer == editorLayer)
                            EditLayer = null;
                        else
                            EditLayer = editorLayer;
                    }
                });

                i++;
            }



            ToolStripButton layersAdd = new ToolStripButton("Add");
            layersAdd.ForeColor = SystemColors.Control;
            layersAdd.Font = font;
            toolStripLayers.Items.Add(layersAdd);
            layersAdd.Click += new EventHandler(delegate (Object o, EventArgs a) {
                SceneLayer la = new SceneLayer("Layer " + (Scene.Layers.Count + 1), Scene.Layers.Last().Width, Scene.Layers.Last().Height);

                Scene.Layers.Add(la);
                EditorLayers.Add(new EditorLayer(la));

                PopulateLayerToolstrip();
            });
        }

        // Open
        private void Open_Click(object sender, EventArgs e) {
            if (load()) {
                UnloadScene();

                int ACT = 1;

                string stageResult = @"C:\Users\Justin\Dropbox\ImpostorEngine2\source\Resources\Stages\MGZ\Scene" + ACT + ".bin";

                using (OpenFileDialog openFileDialog = new OpenFileDialog()) {
                    openFileDialog.InitialDirectory = @"C: \Users\Justin\Dropbox\ImpostorEngine2\source\Resources\Stages\";
                    openFileDialog.Filter = "Scene BIN files (*.bin)|*.bin|All files (*.*)|*.*";
                    openFileDialog.FilterIndex = 0;
                    openFileDialog.RestoreDirectory = true;

                    if (openFileDialog.ShowDialog() == DialogResult.OK) {
                        stageResult = openFileDialog.FileName;
                        ACT = -1;
                    }
                }

                if (File.Exists(stageResult)) {
                    // Selected file

                    string[] splitted = stageResult.Split('\\');

                    if (File.Exists(Path.Combine(Path.GetDirectoryName(stageResult), "16x16Tiles.gif"))) {
                        if (ACT > 0)
                            StageTiles = new StageTiles(Path.GetDirectoryName(stageResult), ACT);
                        else
                            StageTiles = new StageTiles(Path.GetDirectoryName(stageResult));
                    }
                    else if (stageResult.Contains("Scene1.bin")) {
                        StageTiles = new StageTiles(Path.GetDirectoryName(stageResult), 1);
                    }
                    else if (stageResult.Contains("Scene2.bin")) {
                        StageTiles = new StageTiles(Path.GetDirectoryName(stageResult), 2);
                        Console.WriteLine("stageResult: " + stageResult);
                    }

                    Console.WriteLine("ath.GetDirectoryName(stageResult): " + Path.GetDirectoryName(stageResult));


                    SceneFilename = stageResult;
                }
                else {
                    string[] splitted = stageResult.Split('/');

                    SelectedZone = splitted[0];
                    SelectedScene = splitted[1];


                    if (ACT > 0)
                        StageTiles = new StageTiles(Path.Combine(DataDirectory, "Stages", SelectedZone), ACT);
                    else
                        StageTiles = new StageTiles(Path.Combine(DataDirectory, "Stages", SelectedZone), 1);
                    SceneFilename = Path.Combine(DataDirectory, "Stages", SelectedZone, SelectedScene);
                }
                Scene = new Scene(SceneFilename);
                
                EditorLayers = new List<EditorLayer>();
                foreach (SceneLayer layer in Scene.Layers) {
                    EditorLayers.Add(new EditorLayer(layer));

                    if (layer.Name == "FG Low" || layer.Name == "Playfield")
                        FGLow = EditorLayers[EditorLayers.Count - 1];
                    else if (layer.Name == "FG High" || layer.Name == "Ring Count")
                        FGHigh = EditorLayers[EditorLayers.Count - 1];


                }

                PopulateLayerToolstrip();

                Background = new EditorBackground();

                entities = new EditorEntities(Scene);

                SceneWidth = FGLow.Layer.Width * 16;
                SceneHeight = FGLow.Layer.Height * 16;

                SetViewSize(SceneWidth, SceneHeight);

                UpdateControls();
            }
        }

        private void Form1_Resize(object sender, EventArgs e) {
            if (splitContainer1.Panel2.Controls.Count == 1) {
                splitContainer1.Panel2.Controls[0].Height = splitContainer1.Panel2.Height - 2;
                splitContainer1.Panel2.Controls[0].Width = splitContainer1.Panel2.Width - 2;
            }

            // TODO: It hides right now few pixels at the edge

            bool nvscrollbar = false;
            bool nhscrollbar = false;

            if (hScrollBar1.Maximum > viewPanel.Width - 2) nhscrollbar = true;
            if (vScrollBar1.Maximum > viewPanel.Height - 2) nvscrollbar = true;
            if (hScrollBar1.Maximum > viewPanel.Width - (nvscrollbar ? vScrollBar1.Width : 0)) hScrollBar1.Visible = true;
            if (vScrollBar1.Maximum > viewPanel.Height - (nhscrollbar ? hScrollBar1.Height : 0)) vScrollBar1.Visible = true;

            vScrollBar1.Visible = nvscrollbar;
            hScrollBar1.Visible = nhscrollbar;

            if (vScrollBar1.Visible) {
                // Docking isn't enough because we want that it will be high/wider when only one of the scroll bars is visible
                //vScrollBar1.Location = new Point(splitContainer1.SplitterDistance - 19, 0);
                vScrollBar1.Height = viewPanel.Height - (hScrollBar1.Visible ? hScrollBar1.Height : 0);
                vScrollBar1.LargeChange = vScrollBar1.Height;
                ScreenHeight = vScrollBar1.Height;
                hScrollBar1.Value = Math.Max(0, Math.Min(hScrollBar1.Value, hScrollBar1.Maximum - hScrollBar1.LargeChange));
            }
            else {
                ScreenHeight = GraphicPanel.Height;
                ShiftY = 0;
                vScrollBar1.Value = 0;
            }
            if (hScrollBar1.Visible) {
                //hScrollBar1.Location = new Point(0, splitContainer1.Height - 18);
                hScrollBar1.Width = viewPanel.Width - (vScrollBar1.Visible ? vScrollBar1.Width : 0);
                hScrollBar1.LargeChange = hScrollBar1.Width;
                ScreenWidth = hScrollBar1.Width;
                vScrollBar1.Value = Math.Max(0, Math.Min(vScrollBar1.Value, vScrollBar1.Maximum - vScrollBar1.LargeChange));
            }
            else {
                ScreenWidth = GraphicPanel.Width;
                ShiftX = 0;
                hScrollBar1.Value = 0;
            }

            if (hScrollBar1.Visible && vScrollBar1.Visible) {
                panel3.Visible = true;
                //panel3.Location = new Point(hScrollBar1.Width, vScrollBar1.Height);
            }
            else panel3.Visible = false;

            while (ScreenWidth > GraphicPanel.Width)
                ResizeGraphicPanel(GraphicPanel.Width * 2, GraphicPanel.Height);
            while (ScreenHeight > GraphicPanel.Height)
                ResizeGraphicPanel(GraphicPanel.Width, GraphicPanel.Height * 2);
        }


        private void SetViewSize(int width = 0, int height = 0) {
            vScrollBar1.Maximum = height;
            hScrollBar1.Maximum = width;

            GraphicPanel.DrawWidth = Math.Min(width, GraphicPanel.Width);
            GraphicPanel.DrawHeight = Math.Min(height, GraphicPanel.Height);

            Form1_Resize(null, null);

            hScrollBar1.Value = Math.Max(0, Math.Min(hScrollBar1.Value, hScrollBar1.Maximum - hScrollBar1.LargeChange));
            vScrollBar1.Value = Math.Max(0, Math.Min(vScrollBar1.Value, vScrollBar1.Maximum - vScrollBar1.LargeChange));
        }

        private void ResizeGraphicPanel(int width = 0, int height = 0) {
            GraphicPanel.Width = width;
            GraphicPanel.Height = height;

            GraphicPanel.ResetDevice();

            GraphicPanel.DrawWidth = Math.Min(hScrollBar1.Maximum, GraphicPanel.Width);
            GraphicPanel.DrawHeight = Math.Min(vScrollBar1.Maximum, GraphicPanel.Height);
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e) {
            Open_Click(sender, e);
        }

        public void OnResetDevice(object sender, DeviceEventArgs e) {
            Device device = e.Device;
        }

        private void GraphicPanel_OnRender(object sender, DeviceEventArgs e) {
            // hmm, if I call refresh when I update the values, for some reason it will stop to render until I stop calling refrsh
            // So I will refresh it here
            if (entitiesToolbar?.NeedRefresh ?? false) entitiesToolbar.PropertiesRefresh();
            if (Scene != null) {
                if (!IsTilesEdit())
                    Background.Draw(GraphicPanel);

                foreach (EditorLayer elayer in EditorLayers)
                    elayer.Draw(GraphicPanel);

                if (EditEntities.Checked)
                    entities.Draw(GraphicPanel);
            }
            if (draggingSelection) {
                int x1 = (int)(selectingX / Zoom), x2 = (int)(lastX / Zoom);
                int y1 = (int)(selectingY / Zoom), y2 = (int)(lastY / Zoom);
                if (x1 != x2 && y1 != y2) {
                    if (x1 > x2) {
                        x1 = (int)(lastX / Zoom);
                        x2 = (int)(selectingX / Zoom);
                    }
                    if (y1 > y2) {
                        y1 = (int)(lastY / Zoom);
                        y2 = (int)(selectingY / Zoom);
                    }

                    GraphicPanel.DrawRectangle(x1, y1, x2, y2, Color.FromArgb(50, Color.Purple));

                    GraphicPanel.DrawLine(x1, y1, x2, y1, Color.Purple);
                    GraphicPanel.DrawLine(x1, y1, x1, y2, Color.Purple);
                    GraphicPanel.DrawLine(x2, y2, x2, y1, Color.Purple);
                    GraphicPanel.DrawLine(x2, y2, x1, y2, Color.Purple);
                }
            }
            if (scrolling) {
                if (vScrollBar1.Visible && hScrollBar1.Visible) GraphicPanel.Draw2DCursor(scrollPosition.X, scrollPosition.Y);
                else if (vScrollBar1.Visible) GraphicPanel.DrawVertCursor(scrollPosition.X, scrollPosition.Y);
                else if (hScrollBar1.Visible) GraphicPanel.DrawHorizCursor(scrollPosition.X, scrollPosition.Y);
            }
        }

        public TabPanelControl tabLayerProperties;
        public TabPanelControl tabLayerTiles;
        public TabPanelControl tabEntities;

        // Load
        private void Form1_Load(object sender, EventArgs e) {
            GraphicPanel.Init(this);

            propertyGridLayer = new PropertyGrid();
            propertyGridLayer.Dock = DockStyle.Fill;
            propertyGridLayer.ToolbarVisible = false;

            propertyGridLayer.ViewBorderColor = Color.Transparent;
            propertyGridLayer.ViewForeColor = SystemColors.Control;
            propertyGridLayer.ViewBackColor = Color.FromArgb(37, 37, 38);

            propertyGridLayer.HelpBorderColor = Color.Transparent;
            propertyGridLayer.HelpForeColor = SystemColors.Control;
            propertyGridLayer.HelpBackColor = Color.FromArgb(37, 37, 38);
            
            propertyGridLayer.LineColor = Color.FromArgb(45, 45, 48);
            propertyGridLayer.CategorySplitterColor = Color.FromArgb(45, 45, 48);
            propertyGridLayer.CategoryForeColor = SystemColors.Control;
            propertyGridLayer.PropertySort = PropertySort.Categorized;

            propertyGridLayer.CanShowVisualStyleGlyphs = false;

            propertyGridLayer.BackColor = Color.FromArgb(45, 45, 48);

            tabLayerProperties = new TabPanelControl();
            tabLayerProperties.Dock = DockStyle.Fill;
            tabLayerProperties.Controls.Add(propertyGridLayer);

            tabLayerTiles = new TabPanelControl();
            tabLayerTiles.Dock = DockStyle.Fill;

            tabEntities = new TabPanelControl();
            tabEntities.Dock = DockStyle.Fill;
        }

        public void Run() {
            /*
            Bitmap bmp = new Bitmap(@"C:\Users\Justin\Dropbox\ImpostorEngine2\source\Resources\Stages\MGZ\" + "MarbleGardenMania.png");
            Bitmap outBmp = new Bitmap(16, 0x4000, System.Drawing.Imaging.PixelFormat.Format24bppRgb);

            using (Graphics graphics = Graphics.FromImage(outBmp)) {
                for (int i = 0; i < 0x400; i++)
                    graphics.DrawImage(bmp, new Rectangle(0, i << 4, 16, 16), (i & 0x1F) << 4, (i >> 5) << 4, 16, 16, GraphicsUnit.Pixel);
            }

            outBmp.Save(@"C:\Users\Justin\Dropbox\ImpostorEngine2\source\Resources\Stages\MGZ\16x16TilesM.png");

            outBmp.Dispose();
            bmp.Dispose();

            return;
            */

            Show();
            Focus();
            GraphicPanel.Run();
        }

        private void LayerShowButton_Click(ToolStripButton button, string desc) {
            if (button.Checked) {
                button.Checked = false;
                button.ToolTipText = "Show " + desc;
            }
            else {
                button.Checked = true;
                button.ToolTipText = "Hide " + desc;
            }
        }

        public void Deselect(bool updateControls = true) {
            if (IsEditing()) {
                EditLayer?.Deselect();
                if (IsEntitiesEdit()) entities.Deselect();
                SetSelectOnlyButtonsState(false);
                if (updateControls)
                    UpdateEditLayerActions();
            }
            //MagnetDisable();
        }

        private void LayerEditButton_Click(ToolStripButton button) {
            Deselect(false);
            if (button.Checked) {
                button.Checked = false;
            }
            else {
                EditEntities.Checked = false;
                button.Checked = true;
            }
            UpdateControls();
        }

        private void EditFGLow_Click(object sender, EventArgs e) {
            //LayerEditButton_Click(EditFGLow);
        }

        private void EditFGHigh_Click(object sender, EventArgs e) {
            //LayerEditButton_Click(EditFGHigh);
        }

        private void EditEntities_Click(object sender, EventArgs e) {
            LayerEditButton_Click(EditEntities);
        }

        // Save
        private void Save_Click(object sender, EventArgs e) {
            if (Scene == null) return;

            if (IsTilesEdit()) {
                // Apply changes
                Deselect();
            }

            if (File.Exists(SceneFilename)) {
                string newfilename = SceneFilename.Replace(".bin", ".bak.bin");
                if (!File.Exists(newfilename)) {
                    File.Copy(SceneFilename, newfilename);
                }
            }

            Scene.Write(SceneFilename);
        }

        private void MagnetMode_Click(object sender, EventArgs e) {
        }


        private void New_Click(object sender, EventArgs e) {
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e) {
            New_Click(sender, e);
        }

        private void sToolStripMenuItem_Click(object sender, EventArgs e) {
            Save_Click(sender, e);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e) {
            Close();
        }
        private void saveAspngToolStripMenuItem_Click(object sender, EventArgs e) {
            if (Scene != null) {
                SaveFileDialog save = new SaveFileDialog();
                save.Filter = ".png File|*.png";
                save.DefaultExt = "png";
                if (save.ShowDialog() != DialogResult.Cancel) {
                    using (Bitmap bitmap = new Bitmap(SceneWidth, SceneHeight)) {
                        using (Graphics g = Graphics.FromImage(bitmap)) {
                            FGLow.Draw(g);
                            FGHigh.Draw(g);
                        }
                        bitmap.Save(save.FileName);
                    }
                }
            }
        }

        private void splitContainer1_SplitterMoved(object sender, SplitterEventArgs e) {
            Form1_Resize(null, null);
        }

        private void deleteToolStripMenuItem_Click(object sender, EventArgs e) {
            DeleteSelected();
        }

        private void flipHorizontalToolStripMenuItem_Click(object sender, EventArgs e) {
            EditLayer?.FlipPropertySelected(1 << 10);
            UpdateEditLayerActions();
        }


        private void copyToolStripMenuItem_Click(object sender, EventArgs e) {
            if (IsTilesEdit()) {
                TilesClipboard = EditLayer.CopyToClipboard();
            }
            else if (IsEntitiesEdit()) {
                entitiesClipboard = entities.CopyToClipboard();
            }
            UpdateControls();
        }

        private void duplicateToolStripMenuItem_Click(object sender, EventArgs e) {
            if (IsTilesEdit()) {
                EditLayer.PasteFromClipboard(new Point(16, 16), EditLayer.CopyToClipboard(true));
                UpdateEditLayerActions();
            }
            else if (IsEntitiesEdit()) {
                try {
                    entities.PasteFromClipboard(new Point(16, 16), entities.CopyToClipboard(true));
                    UpdateLastEntityAction();
                }
                catch (EditorEntities.TooManyEntitiesException) {
                    MessageBox.Show("Too many entities! (limit: 2048)");
                    return;
                }
                UpdateEntitiesToolbarList();
                SetSelectOnlyButtonsState();
            }
        }

        private void undoToolStripMenuItem_Click(object sender, EventArgs e) {
            EditorUndo();
        }

        private void redoToolStripMenuItem_Click(object sender, EventArgs e) {
            EditorRedo();
        }

        private void undoButton_Click(object sender, EventArgs e) {
            EditorUndo();
        }

        private void redoButton_Click(object sender, EventArgs e) {
            EditorRedo();
        }

        public void EditorUndo() {
            if (undo.Count > 0) {
                if (IsTilesEdit()) {
                    // Deselect to apply the changes
                    Deselect();
                }
                else if (IsEntitiesEdit()) {
                    if (undo.Peek() is ActionAddDeleteEntities) {
                        // deselect only if delete/create
                        Deselect();
                    }
                }
                IAction act = undo.Pop();
                act.Undo();
                redo.Push(act.Redo());
                if (IsEntitiesEdit() && IsSelected()) {
                    // We need to update the properties of the selected entity
                    entitiesToolbar.UpdateCurrentEntityProperites();
                }
            }
            UpdateControls();
        }

        public void EditorRedo() {
            if (redo.Count > 0) {
                IAction act = redo.Pop();
                act.Undo();
                undo.Push(act.Redo());
                if (IsEntitiesEdit() && IsSelected()) {
                    // We need to update the properties of the selected entity
                    entitiesToolbar.UpdateCurrentEntityProperites();
                }
            }
            UpdateControls();
        }

        private void cutToolStripMenuItem_Click(object sender, EventArgs e) {
            if (IsTilesEdit()) {
                TilesClipboard = EditLayer.CopyToClipboard();
                DeleteSelected();
                UpdateControls();
                UpdateEditLayerActions();
            }
            else if (IsEntitiesEdit()) {
                entitiesClipboard = entities.CopyToClipboard();
                DeleteSelected();
                UpdateControls();
            }
        }

        private void pasteToolStripMenuItem_Click(object sender, EventArgs e) {
            if (IsTilesEdit() && TilesClipboard != null) {
                EditLayer.PasteFromClipboard(new Point((int)(ShiftX / Zoom) + EditorLayer.TILE_SIZE - 1, (int)(ShiftY / Zoom) + EditorLayer.TILE_SIZE - 1), TilesClipboard);
                UpdateEditLayerActions();
            }
            else if (IsEntitiesEdit()) {
                try {
                    entities.PasteFromClipboard(new Point((int)(ShiftX / Zoom), (int)(ShiftY / Zoom)), entitiesClipboard);
                    UpdateLastEntityAction();
                }
                catch (EditorEntities.TooManyEntitiesException) {
                    MessageBox.Show("Too many entities! (limit: 2048)");
                    return;
                }
                UpdateEntitiesToolbarList();
                SetSelectOnlyButtonsState();
            }
        }

        private void GraphicPanel_MouseEnter(object sender, EventArgs e) {
            //GraphicPanel.Focus();
        }

        private void GraphicPanel_DragEnter(object sender, DragEventArgs e) {
            if (e.Data.GetDataPresent(typeof(Int32)) && IsTilesEdit()) {
                Point rel = GraphicPanel.PointToScreen(Point.Empty);
                e.Effect = DragDropEffects.Move;
                // (ushort)((Int32)e.Data.GetData(e.Data.GetFormats()[0])
                EditLayer.StartDragOver(new Point((int)(((e.X - rel.X) + ShiftX) / Zoom), (int)(((e.Y - rel.Y) + ShiftY) / Zoom)), (ushort)TilesToolbar.SelectedTile);
                UpdateEditLayerActions();
            }
            else {
                e.Effect = DragDropEffects.None;
            }
        }

        private void GraphicPanel_DragOver(object sender, DragEventArgs e) {
            if (e.Data.GetDataPresent(typeof(Int32)) && IsTilesEdit()) {
                Point rel = GraphicPanel.PointToScreen(Point.Empty);
                EditLayer.DragOver(new Point((int)(((e.X - rel.X) + ShiftX) / Zoom), (int)(((e.Y - rel.Y) + ShiftY) / Zoom)), (ushort)TilesToolbar.SelectedTile);
                GraphicPanel.Render();
            }
        }

        private void GraphicPanel_DragLeave(object sender, EventArgs e) {
            EditLayer?.EndDragOver(true);
            GraphicPanel.Render();
        }

        private void GraphicPanel_DragDrop(object sender, DragEventArgs e) {
            EditLayer?.EndDragOver(false);
        }

        private void zoomInButton_Click(object sender, EventArgs e) {
            ZoomLevel += 1;
            if (ZoomLevel > 5) ZoomLevel = 5;
            if (ZoomLevel < -5) ZoomLevel = -5;

            SetZoomLevel(ZoomLevel, new Point(0, 0));
        }

        private void zoomOutButton_Click(object sender, EventArgs e) {
            ZoomLevel -= 1;
            if (ZoomLevel > 5) ZoomLevel = 5;
            if (ZoomLevel < -5) ZoomLevel = -5;

            SetZoomLevel(ZoomLevel, new Point(0, 0));
        }

        private void selectTool_Click(object sender, EventArgs e) {
            selectTool.Checked = !selectTool.Checked;
            pointerButton.Checked = false;
            placeTilesButton.Checked = false;
            UpdateControls();
        }

        private void pointerButton_Click(object sender, EventArgs e) {
            pointerButton.Checked = !pointerButton.Checked;
            selectTool.Checked = false;
            placeTilesButton.Checked = false;
            UpdateControls();
        }

        private void placeTilesButton_Click(object sender, EventArgs e) {
            placeTilesButton.Checked = !placeTilesButton.Checked;
            selectTool.Checked = false;
            pointerButton.Checked = false;
            UpdateControls();
        }

        private void MapEditor_Activated(object sender, EventArgs e) {
            GraphicPanel.Focus();
        }

        private void MapEditor_KeyDown(object sender, KeyEventArgs e) {
            if (!GraphicPanel.Focused && e.Control) {
                GraphicPanel_OnKeyDown(sender, e);
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e) {
            if (Scene == null) return;

            if (IsTilesEdit()) {
                // Apply changes
                Deselect();
            }

            SaveFileDialog save = new SaveFileDialog();
            save.Filter = "Scene File|*.bin";
            save.DefaultExt = "bin";
            save.InitialDirectory = Path.GetDirectoryName(SceneFilename);
            save.RestoreDirectory = false;
            save.FileName = Path.GetFileName(SceneFilename);
            if (save.ShowDialog() != DialogResult.Cancel) {
                Scene.Write(save.FileName);
            }
        }

        private void tabControlSidebar_DrawItem(object sender, DrawItemEventArgs e) {
            
        }

        private void tileSwapToolStripMenuItem_Click(object sender, EventArgs e) {
            TileSwapper swapper = new TileSwapper();
            swapper.tilesList1.TilesImage = StageTiles.Image.Clone();
            swapper.tilesList1.TileScale = 2;

            string sauce = @"C:\Users\Justin\Dropbox\ImpostorEngine2\source\Resources\Stages\MGZ\16x16TilesM";

            swapper.tilesList2.TilesImage = new GIF(sauce + ".gif");
            swapper.tilesList2.TileScale = 2;
            swapper.tilesList2.Switchable = true;

            swapper.tilesList2.Load("MGZ1swap.bin");

            swapper.FormClosing += new FormClosingEventHandler(delegate (Object o, FormClosingEventArgs a) {
                Bitmap bmp = new Bitmap(sauce + ".gif");
                Bitmap outBmp = (Bitmap)bmp.Clone();

                Console.WriteLine("Console.WriteLine: " + bmp.PixelFormat);

                Rectangle rect = new Rectangle(0, 0, bmp.Width, bmp.Height);
                System.Drawing.Imaging.BitmapData bmpData = bmp.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadWrite, bmp.PixelFormat);
                System.Drawing.Imaging.BitmapData newBmpData = outBmp.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadWrite, outBmp.PixelFormat);

                IntPtr ptr = bmpData.Scan0;
                int bytes = Math.Abs(bmpData.Stride) * bmp.Height;
                byte[] idxValues = new byte[bytes];
                System.Runtime.InteropServices.Marshal.Copy(ptr, idxValues, 0, bytes);

                IntPtr outPtr = newBmpData.Scan0;

                for (int i = 0; i < 0x400; i++) {
                    int bytesppix = Math.Abs(bmpData.Stride) / bmpData.Width;
                    int oldPos = (i << 4) * bmpData.Stride;
                    int newPos = (swapper.tilesList2.Remapping[i] << 4) * bmpData.Stride;

                    if (swapper.tilesList2.Flips[i] == 0) {
                        Marshal.Copy(idxValues, newPos, outPtr + oldPos, 16 * bmpData.Stride);
                    }
                    else { 
                        if (swapper.tilesList2.Flips[i] == 1) { // horizontal
                            for (int line = 0; line < 16; line++) {
                                byte[] flipped = new byte[bmpData.Stride];
                                Marshal.Copy(ptr + newPos + line * bmpData.Stride, flipped, 0, bmpData.Stride);
                                Array.Reverse(flipped);

                                Marshal.Copy(flipped, 0, outPtr + oldPos + line * bmpData.Stride, bmpData.Stride);
                            }
                        }
                        else if (swapper.tilesList2.Flips[i] == 2) { // vertical
                            for (int line = 0; line < 16; line++) {
                                byte[] flipped = new byte[bmpData.Stride];
                                Marshal.Copy(ptr + newPos + (15 - line) * bmpData.Stride, flipped, 0, bmpData.Stride);

                                Marshal.Copy(flipped, 0, outPtr + oldPos + line * bmpData.Stride, bmpData.Stride);
                            }
                        }
                        else if (swapper.tilesList2.Flips[i] == 3) { // horizontal | vertical
                            for (int line = 0; line < 16; line++) {
                                byte[] flipped = new byte[bmpData.Stride];
                                Marshal.Copy(ptr + newPos + (15 - line) * bmpData.Stride, flipped, 0, bmpData.Stride);
                                Array.Reverse(flipped);

                                Marshal.Copy(flipped, 0, outPtr + oldPos + line * bmpData.Stride, bmpData.Stride);
                            }
                        }
                    }
                }

                bmp.UnlockBits(bmpData);
                outBmp.UnlockBits(newBmpData);

                outBmp.Save(sauce + "_Remapped.gif");

                bmp.Dispose();
                outBmp.Dispose();
                
                swapper.tilesList1.Dispose();
                swapper.tilesList2.Dispose();
                swapper.tilesList1.TilesImage.Dispose();
                swapper.tilesList2.TilesImage.Dispose();
            });

            swapper.ShowDialog();
        }

        private void MapEditor_KeyUp(object sender, KeyEventArgs e) {
            if (!GraphicPanel.Focused && e.Control) {
                GraphicPanel_OnKeyUp(sender, e);
            }
        }

        private void flipVerticalToolStripMenuItem_Click(object sender, EventArgs e) {
            EditLayer?.FlipPropertySelected(1 << 11);
            UpdateEditLayerActions();
        }

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e) {
            ShiftY = e.NewValue;
            GraphicPanel.Render();
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e) {
            ShiftX = e.NewValue;
            GraphicPanel.Render();
        }

        private void vScrollBar1_ValueChanged(object sender, EventArgs e) {
            ShiftY = (sender as VScrollBar).Value;
            if (!(zooming || draggingSelection || dragged || scrolling)) GraphicPanel.Render();

            if (draggingSelection) {
                GraphicPanel.OnMouseMoveEventCreate();
            }
        }

        private void hScrollBar1_ValueChanged(object sender, EventArgs e) {
            ShiftX = hScrollBar1.Value;
            if (!(zooming || draggingSelection || dragged || scrolling)) GraphicPanel.Render();
        }

        public void DisposeTextures() {
            if (StageTiles != null) StageTiles.DisposeTextures();
            if (FGHigh != null) FGHigh.DisposeTextures();
            if (FGLow != null) FGLow.DisposeTextures();
        }

        public Rectangle GetScreen() {
            return new Rectangle(ShiftX, ShiftY, viewPanel.Width, viewPanel.Height);
        }

        public double GetZoom() {
            return Zoom;
        }
    }
}