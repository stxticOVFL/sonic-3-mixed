using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Drawing;
using System.Drawing.Design;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Windows.Forms.Design;

namespace ImpostorEditor2 {
    public class ScrollInfoTypeEditor : UITypeEditor {
        public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context) {
            if (context == null || context.Instance == null)
                return base.GetEditStyle(context);
            return UITypeEditorEditStyle.Modal;
        }

        public override object EditValue(ITypeDescriptorContext context, IServiceProvider provider, object value) {
            IWindowsFormsEditorService editorService;

            if (context == null || context.Instance == null || provider == null)
                return value;

            try {
                // get the editor service, just like in windows forms
                editorService = (IWindowsFormsEditorService)
                   provider.GetService(typeof(IWindowsFormsEditorService));

                OpenFileDialog dlg = new OpenFileDialog();
                dlg.Filter = "All Files (*.*)|*.*";
                dlg.CheckFileExists = true;

                string filename = (string)value;
                if (!File.Exists(filename))
                    filename = null;
                dlg.FileName = filename;

                using (dlg) {
                    DialogResult res = dlg.ShowDialog();
                    if (res == DialogResult.OK) {
                        filename = dlg.FileName;
                    }
                }
                return filename;

            }
            finally {
                editorService = null;
            }
        }
    } // class FileSelectorTypeEditor
}
