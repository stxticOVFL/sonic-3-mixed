using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace S3toIE2 {
    public partial class HitboxEditor : Form {
        public HitboxEditor() {
            InitializeComponent();
        }
        
        private void listBoxHitboxes_DrawItem(object sender, DrawItemEventArgs e) {
            bool isSelected = ((e.State & DrawItemState.Selected) == DrawItemState.Selected);

            if (e.Index > -1) {
                Color color = isSelected ? SystemColors.Highlight : listBoxHitboxes.BackColor;

                // Background item brush
                SolidBrush backgroundBrush = new SolidBrush(color);
                SolidBrush textBrush = new SolidBrush(e.ForeColor);

                RectangleF rectF = new RectangleF(e.Bounds.X + 2, e.Bounds.Y + 2, e.Bounds.Width, e.Bounds.Height);

                // Draw the background
                e.Graphics.FillRectangle(backgroundBrush, e.Bounds);
                e.Graphics.DrawString(listBoxHitboxes.GetItemText(listBoxHitboxes.Items[e.Index]), e.Font, textBrush, rectF, StringFormat.GenericDefault);

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
            if (listBoxHitboxes.Items.Count > 0) {
                if (listBoxHitboxes.SelectedIndex >= 0) {
                    PromptDialog prompt = new PromptDialog("New name for \"" + listBoxHitboxes.SelectedItem + "\"?", listBoxHitboxes.SelectedItem.ToString());
                    if (prompt.ShowDialog() == DialogResult.OK) {
                        listBoxHitboxes.Items[listBoxHitboxes.SelectedIndex] = prompt.TextEntry.Text;
                    }
                }
            }
        }

        private void toolStripButtonAdd_Click(object sender, EventArgs e) {
            listBoxHitboxes.Items.Add("New Hitbox");
        }

        private void toolStripButtonDelete_Click(object sender, EventArgs e) {
            listBoxHitboxes.Items.RemoveAt(listBoxHitboxes.SelectedIndex);
        }
    }
}
