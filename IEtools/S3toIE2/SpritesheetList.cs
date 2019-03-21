using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace S3toIE2 {
    public partial class SpritesheetList : Form {
        public SpritesheetList() {
            InitializeComponent();
        }

        public string currentFilename = "";

        private void listBoxHitboxes_DrawItem(object sender, DrawItemEventArgs e) {
            bool isSelected = ((e.State & DrawItemState.Selected) == DrawItemState.Selected);

            if (e.Index > -1) {
                Color color = isSelected ? SystemColors.Highlight : listBoxSpritesheetFilenames.BackColor;

                // Background item brush
                SolidBrush backgroundBrush = new SolidBrush(color);
                SolidBrush textBrush = new SolidBrush(e.ForeColor);

                RectangleF rectF = new RectangleF(e.Bounds.X + 2, e.Bounds.Y + 2, e.Bounds.Width, e.Bounds.Height);

                // Draw the background
                e.Graphics.FillRectangle(backgroundBrush, e.Bounds);
                e.Graphics.DrawString(listBoxSpritesheetFilenames.GetItemText(listBoxSpritesheetFilenames.Items[e.Index]), e.Font, textBrush, rectF, StringFormat.GenericDefault);

                // Clean up
                backgroundBrush.Dispose();
                textBrush.Dispose();
            }
            e.DrawFocusRectangle();
        }

        private void buttonOK_Click(object sender, EventArgs e) {
            this.DialogResult = DialogResult.OK;
        }

        private void listBoxHitboxes_DoubleClick(object sender, EventArgs e) {
            if (listBoxSpritesheetFilenames.Items.Count > 0) {
                if (listBoxSpritesheetFilenames.SelectedIndex >= 0) {
                    OpenFileDialog ofd = new OpenFileDialog();
                    if (currentFilename == "")
                        ofd.InitialDirectory = @"C:\Users\Justin\Dropbox\ImpostorEngine2\source\Resources\Sprites\";
                    else
                        ofd.InitialDirectory = Directory.GetParent(Path.GetDirectoryName(currentFilename)).FullName;
                    ofd.AddExtension = true;
                    ofd.Filter = "GIF Files (*.gif)|*.gif";

                    if (ofd.ShowDialog() == DialogResult.OK) {
                        listBoxSpritesheetFilenames.Items[listBoxSpritesheetFilenames.SelectedIndex] = ofd.FileName;
                        currentFilename = ofd.FileName;
                    }
                }
            }
        }

        private void toolStripButtonAdd_Click(object sender, EventArgs e) {
            OpenFileDialog ofd = new OpenFileDialog();
            if (currentFilename == "")
                ofd.InitialDirectory = @"C:\Users\Justin\Dropbox\ImpostorEngine2\source\Resources\Sprites\";
            else
                ofd.InitialDirectory = Directory.GetParent(Path.GetDirectoryName(currentFilename)).FullName;
            ofd.AddExtension = true;
            ofd.Filter = "GIF Files (*.gif)|*.gif";

            if (ofd.ShowDialog() == DialogResult.OK) {
                listBoxSpritesheetFilenames.Items.Add(ofd.FileName);
                currentFilename = ofd.FileName;
            }
        }

        private void toolStripButtonDelete_Click(object sender, EventArgs e) {
            listBoxSpritesheetFilenames.Items.RemoveAt(listBoxSpritesheetFilenames.SelectedIndex);
        }
    }
}
