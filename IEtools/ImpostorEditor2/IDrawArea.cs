using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ImpostorEditor2
{
    public interface IDrawArea
    {
        void DisposeTextures();

        Rectangle GetScreen();
        double GetZoom();
    }
}
