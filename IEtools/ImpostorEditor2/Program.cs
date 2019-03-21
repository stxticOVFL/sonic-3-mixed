using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImpostorEditor2
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            using (var stream = Assembly.GetExecutingAssembly().GetManifestResourceStream("ImpostorEditor2.Resources.objects_attributes"))
            {
                //RSDKv5.Objects.InitObjects(stream);
            }
            new Editor().Run();
            //Application.Run(new GUI.MapEditor());
        }
    }
}
