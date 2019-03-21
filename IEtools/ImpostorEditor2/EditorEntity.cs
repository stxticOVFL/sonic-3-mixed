using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ImpostorEditor2
{
    class EditorEntity : IDrawable
    {
        const int NAME_BOX_WIDTH = 20;
        const int NAME_BOX_HEIGHT = 20;

        public bool Selected;

        private RSDKv5.Scene.ISCN_Object entity;

        public RSDKv5.Scene.ISCN_Object Entity { get { return entity; } }

        public EditorEntity(RSDKv5.Scene.ISCN_Object entity)
        {
            this.entity = entity;
        }
 
        public void Draw(Graphics g)
        {
        }

        public bool ContainsPoint(Point point)
        {
            return GetDimensions().Contains(point);
        }

        public bool IsInArea(Rectangle area)
        {
            return GetDimensions().IntersectsWith(area);
        }

        public void Move(Point diff)
        {
            entity.X += (short)diff.X;
            entity.Y += (short)diff.Y;
        }

        public Rectangle GetDimensions()
        {
            return new Rectangle(entity.X, entity.Y, NAME_BOX_WIDTH, NAME_BOX_HEIGHT);
        }

        public void Draw(DevicePanel d)
        {
            if (!d.IsObjectOnScreen(entity.X, entity.Y, NAME_BOX_WIDTH, NAME_BOX_HEIGHT)) return;
            Color color = Selected ? Color.MediumPurple : Color.MediumTurquoise;
            Color color2 = Color.DarkBlue;
            int Transparency = (Editor.Instance.EditLayer == null) ? 0xff : 0x32;

            int x = entity.X;
            int y = entity.Y;

            d.DrawRectangle(x, y, x + NAME_BOX_WIDTH, y + NAME_BOX_HEIGHT, Color.FromArgb(Transparency, color));
            d.DrawLine(x, y, x + NAME_BOX_WIDTH, y, Color.FromArgb(Transparency, color2));
            d.DrawLine(x, y, x, y + NAME_BOX_HEIGHT, Color.FromArgb(Transparency, color2));
            d.DrawLine(x, y + NAME_BOX_HEIGHT, x + NAME_BOX_WIDTH, y + NAME_BOX_HEIGHT, Color.FromArgb(Transparency, color2));
            d.DrawLine(x + NAME_BOX_WIDTH, y, x + NAME_BOX_WIDTH, y + NAME_BOX_HEIGHT, Color.FromArgb(Transparency, color2));

            if (Editor.Instance.GetZoom() >= 1)
                d.DrawTextSmall(String.Format("{0} (ID: {1})", entity.Definition?.ObjectName, 0), x + 2, y + 2, NAME_BOX_WIDTH - 4, Color.FromArgb(Transparency, Color.Black), true);
        }
    }
}
