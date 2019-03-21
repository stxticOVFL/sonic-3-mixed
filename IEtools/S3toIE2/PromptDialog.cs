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
    public partial class PromptDialog : Form {
        public PromptDialog() {
            InitializeComponent();
        }

        public PromptDialog(string caption, string text) {
            InitializeComponent();

            TextLabel.Text = caption;
            TextEntry.Text = text;
            TextEntry.SelectAll();
        }

        private void buttonOK_Click(object sender, EventArgs e) {
            DialogResult = DialogResult.OK;
        }
    }
}
