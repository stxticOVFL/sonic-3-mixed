using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace ImpostorEditor2
{
    interface IDrawable
    {
        void Draw(Graphics g);

        void Draw(DevicePanel d);

        //void DrawAnimation(DevicePanel d);
    }
}
