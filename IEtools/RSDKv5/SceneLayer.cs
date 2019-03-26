using System;
using System.Collections.Generic;
using System.IO;

namespace RSDKv5
{
    [Serializable]
    public class SceneLayer
    {
        /// <summary>
        /// ok taxman retar
        /// </summary>
        byte IgnoredByte;
        private string _name;

        /// <summary>
        /// a special byte that tells the game if this layer has any special properties
        /// </summary>
        public byte Behaviour;
        /// <summary>
        /// what drawlayer this layer is on
        /// </summary>
        public byte DrawingOrder;

        private ushort _width;
        private ushort _height;

        /// <summary>
        /// the Speed of the layer when the player is moving
        /// </summary>
        public short RelativeSpeed;
        /// <summary>
        /// the Speed of the layer when the player isn't moving
        /// </summary>
        public short ConstantSpeed;

        public int ParallaxY = 0;

        /// <summary>
        /// the line scroll data
        /// </summary>
        public List<ScrollInfo> ScrollingInfo = new List<ScrollInfo>();

        /// <summary>
        /// the line scroll indexes
        /// </summary>
        public byte[] ScrollIndexes;

        /// <summary>
        /// the tile array for the map
        /// </summary>
        public ushort[][] Tiles;

        /// <summary>
        /// the layer's name
        /// </summary>
        public string Name { get => _name; set => _name = value; }
        /// <summary>
        /// the layer's width (in tiles)
        /// </summary>
        public ushort Width { get => _width; private set => _width = value; }
        /// <summary>
        /// the layer's height (in tiles)
        /// </summary>
        public ushort Height { get => _height; private set => _height = value; }

        public SceneLayer(string name, ushort width, ushort height)
        {
            Name = name;
            Width = width;
            Height = height;

            ScrollingInfo.Add(new ScrollInfo());
            // Per pixel (of height or of width, depends if it scrolls horizontal or veritcal)
            ScrollIndexes = new byte[Height * 16];
            Tiles = new ushort[Height][];
            for (int i = 0; i < Height; ++i)
            {
                Tiles[i] = new ushort[Width];
                for (int j = 0; j < Width; ++j)
                    Tiles[i][j] = 0xffff;
            }
        }

        internal SceneLayer(Reader reader)
        {
            IgnoredByte = reader.ReadByte();

            Name = reader.ReadRSDKString();

            Behaviour = reader.ReadByte();
            DrawingOrder = reader.ReadByte();

            Width = reader.ReadUInt16();
            Height = reader.ReadUInt16();

            RelativeSpeed = reader.ReadInt16();
            ConstantSpeed = reader.ReadInt16();

            ushort scrolling_info_count = reader.ReadUInt16();
            for (int i = 0; i < scrolling_info_count; ++i)
                ScrollingInfo.Add(new ScrollInfo(reader));

            ScrollIndexes = reader.ReadCompressed();

            Tiles = new ushort[Height][];
            using (Reader creader = reader.GetCompressedStream())
            {
                for (int i = 0; i < Height; ++i)
                {
                    Tiles[i] = new ushort[Width];
                    for (int j = 0; j < Width; ++j)
                        Tiles[i][j] = creader.ReadUInt16();
                }
            }
        }

        internal void Write(Writer writer)
        {
            writer.Write(IgnoredByte);

            writer.WriteRSDKString(Name);

            writer.Write(Behaviour);
            writer.Write(DrawingOrder);

            writer.Write(Width);
            writer.Write(Height);

            writer.Write(RelativeSpeed);
            writer.Write(ConstantSpeed);

            writer.Write((ushort)ScrollingInfo.Count);
            foreach (ScrollInfo info in ScrollingInfo)
                info.Write(writer);

            writer.WriteCompressed(ScrollIndexes);

            using (MemoryStream cmem = new MemoryStream())
            using (Writer cwriter = new Writer(cmem))
            {
                for (int i = 0; i < Height; ++i)
                    for (int j = 0; j < Width; ++j)
                        cwriter.Write(Tiles[i][j]);
                cwriter.Close();
                writer.WriteCompressed(cmem.ToArray());
            }
        }

        public SceneLayer Clone()
        {
            SceneLayer sceneLayer = new SceneLayer(Name, Width, Height);

            sceneLayer.Behaviour = Behaviour;
            sceneLayer.DrawingOrder = DrawingOrder;

            sceneLayer.RelativeSpeed = RelativeSpeed;
            sceneLayer.ConstantSpeed = ConstantSpeed;

            sceneLayer.ScrollingInfo.Clear();
            foreach (ScrollInfo si in ScrollingInfo)
            {
                sceneLayer.ScrollingInfo.Add(new ScrollInfo(si.RelativeSpeed, si.ConstantSpeed, si.Behaviour, si.DrawOrder));
            }
            for (int i = 0; i < Height * 16; ++i)
            {
                sceneLayer.ScrollIndexes[i] = ScrollIndexes[i];
            }

            for (int i = 0; i < Height; ++i)
            {
                for (int j = 0; j < Width; ++j)
                    sceneLayer.Tiles[i][j] = Tiles[i][j];
            }
            return sceneLayer;
        }


        public void ResetParallax()
        {
            ParallaxY = 0;
            ScrollingInfo.Clear();
        }
        public void AddParallax(int size, int relativeX, int constantX, int ignoredByte, bool mirageFuzziness)
        {
            ScrollingInfo.Add(new ScrollInfo((short)relativeX, (short)constantX, (byte)(mirageFuzziness ? 1 : 0), (byte)ignoredByte));
            for (int i = ParallaxY; i < ParallaxY + size && i < Height * 16; i++)
                ScrollIndexes[i] = (byte)(ScrollingInfo.Count - 1);
            ParallaxY += size;
        }

        public void CropTo(int x, int y, int w, int h)
        {
            ushort[][] tiles = new ushort[h][];
            for (int i = 0; i < h; ++i)
            {
                tiles[i] = new ushort[w];
                for (int j = 0; j < w; ++j)
                    tiles[i][j] = Tiles[i + y][j + x];
            }
            Tiles = tiles;
            Width = (ushort)w;
            Height = (ushort)h;
        }
        public void Remove(int x, int y, int w, int h)
        {
            for (int i = y; i < y + h; ++i)
            {
                for (int j = x; j < x + w; ++j)
                    Tiles[i][j] = 0;
            }
        }
        public void Move(int x, int y)
        {
            ushort[][] tiles = new ushort[Height][];
            for (int i = 0; i < Height; ++i)
            {
                tiles[i] = new ushort[Width];
                for (int j = 0; j < Width; ++j)
                {
                    if (j + x < 0) continue;
                    if (i + y < 0) continue;
                    if (j + x >= Width) continue;
                    if (i + y >= Height) continue;
                    tiles[i + y][j + x] = Tiles[i][j];
                }
            }
            Tiles = tiles;
        }


        /// <summary>
        /// Resizes a layer.
        /// </summary>
        /// <param name="width">The new Width</param>
        /// <param name="height">The new Height</param>
        public void Resize(ushort width, ushort height)
        {
            // first take a backup of the current dimensions
            // then update the internal dimensions
            ushort oldWidth = Width;
            ushort oldHeight = Height;
            Width = width;
            Height = height;

            // resize the various scrolling and tile arrays
            Array.Resize(ref ScrollIndexes, Height * 16);
            Array.Resize(ref Tiles, Height);

            // fill the extended tile arrays with "empty" values

            // if we're actaully getting shorter, do nothing!
            for (ushort i = oldHeight; i < Height; i++)
            {
                // first create arrays child arrays to the old width
                // a little inefficient, but at least they'll all be equal sized
                Tiles[i] = new ushort[oldWidth];
                for (int j = 0; j < oldWidth; ++j)
                    Tiles[i][j] = 0xffff; // fill the new ones with blanks
            }

            for (ushort i = 0; i < Height; i++)
            {
                // now resize all child arrays to the new width
                Array.Resize(ref Tiles[i], Width);
                for (ushort j = oldWidth; j < Width; j++)
                    Tiles[i][j] = 0xffff; // and fill with blanks if wider
            }
        }
    }
}
