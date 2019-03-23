using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace RSDKv5 {
    public class SceneLayer {
        byte IgnoredByte;
        public string Name;

        public byte IsScrollingVertical;
        public byte UnknownByte2;

        public ushort Width;
        public ushort Height;

        public ushort RelativeY;
        public ushort ConstantY;

        public class ScrollInfo {
            public ushort RelativeX;
            public ushort ConstantX;
            public byte HeatWaveEnabled;
            public byte UnknownByte2;

            public ScrollInfo(ushort relX = 0x100, ushort constX = 0, byte heatWaveEnabled = 0, byte byte2 = 0) {
                this.RelativeX = relX;
                this.ConstantX = constX;

                this.HeatWaveEnabled = heatWaveEnabled;
                this.UnknownByte2 = byte2;
            }

            internal ScrollInfo(Reader reader) {
                RelativeX = reader.ReadUInt16();
                ConstantX = reader.ReadUInt16();

                HeatWaveEnabled = reader.ReadByte();
                UnknownByte2 = reader.ReadByte();
            }

            internal void Write(Writer writer) {
                writer.Write(RelativeX);
                writer.Write(ConstantX);

                writer.Write(HeatWaveEnabled);
                writer.Write(UnknownByte2);
            }
        }

        int ParallaxY = 0;
        public List<ScrollInfo> ScrollingInfo = new List<ScrollInfo>();

        public byte[] ScrollIndexes;

        public ushort[][] Tiles;

        public void ResetParallax() {
            ParallaxY = 0;
            ScrollingInfo.Clear();
        }
        public void AddParallax(int size, int relativeX, int constantX, int ignoredByte, bool mirageFuzziness) {
            ScrollingInfo.Add(new ScrollInfo((ushort)relativeX, (ushort)constantX, (byte)(mirageFuzziness ? 1 : 0), (byte)ignoredByte));
            for (int i = ParallaxY; i < ParallaxY + size && i < Height * 16; i++)
                ScrollIndexes[i] = (byte)(ScrollingInfo.Count - 1);
            ParallaxY += size;
        }


        public SceneLayer(string name, ushort Width, ushort Height) {
            this.Name = name;
            this.Width = Width;
            this.Height = Height;

            this.RelativeY = 0x100;

            ScrollingInfo.Add(new ScrollInfo());
            // Per pixel (of height or of width, depends if it scrolls horizontal or veritcal)
            ScrollIndexes = new byte[Height * 16];
            Tiles = new ushort[Height][];
            for (int i = 0; i < Height; ++i) {
                Tiles[i] = new ushort[Width];
                for (int j = 0; j < Width; ++j)
                    //Tiles[i][j] = 0xffff;
                    Tiles[i][j] = 0x0000;
            }
        }

        public SceneLayer Clone() {
            SceneLayer sceneLayer = new SceneLayer(Name, Width, Height);
            
            sceneLayer.IsScrollingVertical = IsScrollingVertical;
            sceneLayer.UnknownByte2 = UnknownByte2;

            sceneLayer.RelativeY = RelativeY;
            sceneLayer.ConstantY = ConstantY;

            sceneLayer.ScrollingInfo.Clear();
            foreach (ScrollInfo si in ScrollingInfo) {
                sceneLayer.ScrollingInfo.Add(new ScrollInfo(si.RelativeX, si.ConstantX, si.HeatWaveEnabled, si.UnknownByte2));
            }
            for (int i = 0; i < Height * 16; ++i) {
                sceneLayer.ScrollIndexes[i] = ScrollIndexes[i];
            }

            for (int i = 0; i < Height; ++i) {
                for (int j = 0; j < Width; ++j)
                    sceneLayer.Tiles[i][j] = Tiles[i][j];
            }
            return sceneLayer;
        }

        public void CropTo(int x, int y, int w, int h) {
            ushort[][] tiles = new ushort[h][];
            for (int i = 0; i < h; ++i) {
                tiles[i] = new ushort[w];
                for (int j = 0; j < w; ++j)
                    tiles[i][j] = Tiles[i + y][j + x];
            }
            Tiles = tiles;
            Width = (ushort)w;
            Height = (ushort)h;
        }
        public void Remove(int x, int y, int w, int h) {
            for (int i = y; i < y + h; ++i) {
                for (int j = x; j < x + w; ++j)
                    Tiles[i][j] = 0;
            }
        }
        public void Move(int x, int y) {
            ushort[][] tiles = new ushort[Height][];
            for (int i = 0; i < Height; ++i) {
                tiles[i] = new ushort[Width];
                for (int j = 0; j < Width; ++j) {
                    if (j + x < 0) continue;
                    if (i + y < 0) continue;
                    if (j + x >= Width) continue;
                    if (i + y >= Height) continue;
                    tiles[i + y][j + x] = Tiles[i][j];
                }
            }
            Tiles = tiles;
        }


        internal SceneLayer(Reader reader) {
            IgnoredByte = reader.ReadByte();

            Name = reader.ReadRSDKString();

            IsScrollingVertical = reader.ReadByte();
            UnknownByte2 = reader.ReadByte();

            Width = reader.ReadUInt16();
            Height = reader.ReadUInt16();

            RelativeY = reader.ReadUInt16();
            ConstantY = reader.ReadUInt16();

            ushort scrolling_info_count = reader.ReadUInt16();
            for (int i = 0; i < scrolling_info_count; ++i)
                ScrollingInfo.Add(new ScrollInfo(reader));

            ScrollIndexes = reader.ReadCompressed();

            Tiles = new ushort[Height][];
            using (Reader creader = reader.GetCompressedStream()) {
                for (int i = 0; i < Height; ++i) {
                    Tiles[i] = new ushort[Width];
                    for (int j = 0; j < Width; ++j)
                        Tiles[i][j] = creader.ReadUInt16();
                }
            }
        }

        internal void Write(Writer writer) {
            writer.Write(IgnoredByte);

            writer.WriteRSDKString(Name);

            writer.Write(IsScrollingVertical);
            writer.Write(UnknownByte2);

            writer.Write(Width);
            writer.Write(Height);

            writer.Write(RelativeY);
            writer.Write(ConstantY);

            writer.Write((ushort)ScrollingInfo.Count);
            foreach (ScrollInfo info in ScrollingInfo)
                info.Write(writer);

            writer.WriteCompressed(ScrollIndexes);

            using (MemoryStream cmem = new MemoryStream())
            using (Writer cwriter = new Writer(cmem)) {
                for (int i = 0; i < Height; ++i)
                    for (int j = 0; j < Width; ++j)
                        cwriter.Write(Tiles[i][j]);
                cwriter.Close();
                writer.WriteCompressed(cmem.ToArray());
            }
        }
    }
}
