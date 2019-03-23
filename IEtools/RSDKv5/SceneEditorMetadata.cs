using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RSDKv5
{
    public class SceneEditorMetadata
    {
        byte ZoneID; // 2/3/4
        public Color BackgroundColor1;
        public Color BackgroundColor2;
        byte[] UnknownBytes; // Const: 01010400010400
        public string LevelName;
        byte UnknownByte2;

        public SceneEditorMetadata()
        {
            ZoneID = 3;
            BackgroundColor1 = Color.EMPTY;
            BackgroundColor2 = Color.EMPTY;
            UnknownBytes = new byte[] { 0x1, 0x1, 0x4, 0x0, 0x1, 0x4, 0x0 };
        }

        internal SceneEditorMetadata(Reader reader)
        {
            ZoneID = reader.ReadByte();
            BackgroundColor1 = new Color(reader);
            BackgroundColor2 = new Color(reader);
            UnknownBytes = reader.ReadBytes(7);
            LevelName = reader.ReadRSDKString();
            UnknownByte2 = reader.ReadByte();
        }

        internal void Write(Writer writer)
        {
            writer.Write(ZoneID);
            BackgroundColor1.Write(writer);
            BackgroundColor2.Write(writer);
            writer.Write(UnknownBytes);
            writer.WriteRSDKString(LevelName);
            writer.Write(UnknownByte2);
        }
    }
}
