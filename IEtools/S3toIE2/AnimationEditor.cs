using SonicRetro.KensSharp;
using SonicRetro.SonLVL.API;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace S3toIE2 {
    public partial class AnimationEditor : Form {

        public class SprFrm {
            public int    Index = 0;
            public Sprite Spr = null;
            public SprFrm(int i, Sprite s) {
                Index = i;
                Spr = s;
            }
        }

        public class SprAnim {
            public string Name = "Anim";
            public int FrameLoop = 0;
            public int FrameSpeed = 1;
            public int FrameDuration = 1;
            public List<SprFrm> Frames = new List<SprFrm>();
            public List<FrameAlt> FrameAlterations = new List<FrameAlt>();

            public static SprAnim GetSpan(Sprite spr, string name, int frameDur, int from, int to, int fl) {
                SprAnim sprAnim = new SprAnim();
                sprAnim.Name = name;
                sprAnim.FrameDuration = frameDur;
                sprAnim.FrameLoop = fl;
                sprAnim.FrameSpeed = 1;
                for (int i = from; i <= to; i++) {
                    sprAnim.Frames.Add(new SprFrm(i, spr));
                }
                return sprAnim;
            }

            public static SprAnim WrapSprAnim(string name, int frameDur, SprAnim o) {
                SprAnim sprAnim = new SprAnim();
                sprAnim.Name = name;
                sprAnim.FrameDuration = frameDur;
                sprAnim.FrameLoop = o.FrameLoop;
                sprAnim.FrameSpeed = 1;
                sprAnim.Frames = new List<SprFrm>(o.Frames);
                return sprAnim;
            }
            public static SprAnim WrapSprAnim(string name, SprAnim o) {
                SprAnim sprAnim = new SprAnim();
                sprAnim.Name = name;
                sprAnim.FrameDuration = o.FrameDuration;
                sprAnim.FrameLoop = o.FrameLoop;
                sprAnim.FrameSpeed = 1;
                sprAnim.Frames = new List<SprFrm>(o.Frames);
                return sprAnim;
            }
        }

        public class SpriteFrameTile {
            public int X;
            public int Y;
            public bool FlipX;
            public bool FlipY;
            public int Tile;
            public int W;
            public int H;
            public int Pal;
        }

        public class SpriteFrame {
            public short X = -100;
            public short Y = -100;
            public ushort W = 0;
            public ushort H = 0;
            public short BoxX = -100;
            public short BoxY = -100;
            public int Index = -1;
            public int PalOff = 0;
            public Sprite Parent = null;
            public List<SpriteFrameTile> Tiles = new List<SpriteFrameTile>();
        }

        public class Sprite {
            public string Name = "";
            public int StartingArtTile = 0;
            public int PalStart = 0;
            public List<SpriteFrame> Frames = new List<SpriteFrame>();
            public List<SprAnim> Anim = new List<SprAnim>();
        }

        public class PLCRequest {
            public string filename = "";
            public int offset = -1;

            public CompressionType compression = CompressionType.Nemesis;

            public PLCRequest(string f, int o) {
                filename = f;
                offset = o;
                compression = CompressionType.Nemesis;
            }
            public PLCRequest(string f, int o, CompressionType c) {
                filename = f;
                offset = o;
                compression = c;
            }
        }

        Sprite sprite = null;

        enum UseType {
            AnimationEditor,
            LevelExporting,
            SpriteExporting,
        }

        public AnimationEditor() {
            // OpenFolder("");
            //goto DOPRGM;
            //goto DOEXIT;

            bool exitAfter = false;
            UseType useType = UseType.SpriteExporting;

            if (useType == UseType.LevelExporting) {
                
                goto DOEXIT;
            }
            else if (useType == UseType.SpriteExporting) {
                Globals.OUT = @"C:\Users\Justin\sonic-3-mixed\ImpostorEngine2\source\Resources\Sprites\";

                Dictionary<uint, uint> checksums = new Dictionary<uint, uint>();

                // OpenFolder("Player"); return;

                // Load from file
                if (File.Exists("PatchSpriteChecksums.bin")) {
                    byte[] vs = File.ReadAllBytes("PatchSpriteChecksums.bin");
                    for (int i = 0; i < vs.Length; i += 8) {
                        uint key = BitConverter.ToUInt32(vs, i);
                        uint val = BitConverter.ToUInt32(vs, i + 4);
                        checksums.Add(key, val);
                    }
                }

                DirectoryInfo d = new DirectoryInfo(@".");
                System.IO.FileInfo[] Files = d.GetFiles("Patches/PatchSprite_*.txt");
                foreach (System.IO.FileInfo file in Files) {
                    var bytes = Encoding.ASCII.GetBytes(file.Name);
                    var key = Crc32Algorithm.Compute(bytes);
                    var chk = Crc32Algorithm.Compute(File.ReadAllBytes("Patches/" + file.Name));
                    if (checksums.ContainsKey(key)) {
                        if (checksums[key] == chk)
                            continue;
                    }

                    Console.WriteLine("Opening '" + file.Name + "'...");
                    OpenFolder("Patches/" + file.Name);

                    if (checksums.ContainsKey(key))
                        checksums[key] = chk;
                    else
                        checksums.Add(key, chk);
                }

                using (FileStream fs = new FileStream("PatchSpriteChecksums.bin", FileMode.OpenOrCreate)) {
                    foreach (KeyValuePair<uint, uint> key in checksums) {
                        fs.Write(BitConverter.GetBytes(key.Key), 0, 4);
                        fs.Write(BitConverter.GetBytes(key.Value), 0, 4);
                    }
                }

                if (exitAfter)
                    goto DOEXIT;
            }

            DOPRGM:
            InitializeComponent();

            splitContainer2.SplitterWidth = 1;
            splitContainerMain.SplitterWidth = 1;

            New();

            return;

            DOEXIT:
            Environment.Exit(0);
        }

        public Bitmap Image = null;
        public Bitmap Image2 = null;
        public List<Bitmap> spriteSheets = new List<Bitmap>();

        byte[] ArtToBitmap(string palFilename, List<PLCRequest> requests) {
            int totalTiles = 0;
            Bitmap tileImage = null;
            byte[] tileData = new byte[0];
            
            // Load Palette
            int[] palette;
            ushort[] palEnc;
            int paletteLines = 0;
            using (MemoryStream output = new MemoryStream()) {
                using (FileStream input = File.OpenRead(@"C:\Users\Justin\skdisasm-master\General\Sprites\Sonic\Palettes\SonicAndTails.bin")) {
                    for (int i = 0; i < 16; i++) {
                        LittleEndian.Write2(output, BigEndian.Read2(input));
                    }
                    if (palFilename == null) {
                        for (int i = 0; i < 16; i++) {
                            LittleEndian.Write2(output, BigEndian.Read2(input));
                        }
                    }
                }

                if (palFilename != null) {
                    using (FileStream input = File.OpenRead(palFilename)) {
                        for (int i = 0; i < input.Length / 2; i++) {
                            LittleEndian.Write2(output, BigEndian.Read2(input));
                        }
                    }
                }

                byte[] d = output.ToArray();
                palEnc = new ushort[d.Length / 2];
                Buffer.BlockCopy(d, 0, palEnc, 0, d.Length);
            }
            palette = new int[palEnc.Length];
            for (int i = 0; i < palEnc.Length; i++) {
                byte r = (byte)(palEnc[i] & 0xF);
                byte g = (byte)(palEnc[i] >> 4 & 0xF);
                byte b = (byte)(palEnc[i] >> 8 & 0xF);
                
                palette[i] = Globals.GetGenesisColors(ref r, ref g, ref b);
            }
            paletteLines = palette.Length / 16;

            // Load tiles
            for (int d = 0; d < requests.Count; d++) {
                string file = requests[d].filename;

                if (totalTiles < requests[d].offset) {
                    byte[] nbs = new byte[(requests[d].offset - totalTiles) * 0x20];
                    tileData = tileData.Concat(nbs).ToArray();
                    totalTiles += nbs.Length / 0x20;
                }

                byte[] dec = null;
                if (file.Contains("Tiles\\"))
                    dec = ModuledKosinski.Decompress(file, Endianness.BigEndian);
                else {
                    switch (requests[d].compression) {
                        case CompressionType.Uncompressed:
                            dec = File.ReadAllBytes(file);
                            break;

                        case CompressionType.Kosinski:
                            dec = Kosinski.Decompress(file);
                            break;

                        case CompressionType.KosinskiM:
                            dec = ModuledKosinski.Decompress(file, Endianness.BigEndian);
                            break;

                        case CompressionType.Nemesis:
                            dec = Nemesis.Decompress(file);
                            break;

                        default:
                            dec = Nemesis.Decompress(file);
                            break;
                    }
                    
                }
                tileData = tileData.Concat(dec).ToArray();

                Console.WriteLine("\"" + file + "\": 0x" + totalTiles.ToString("X"));
                totalTiles += dec.Length / 0x20;
            }

            tileImage = new Bitmap(8 * paletteLines, totalTiles * 8, PixelFormat.Format8bppIndexed);
            // Set palette
            ColorPalette cpal = tileImage.Palette;
            for (int i = 0; i < palette.Length; i++) {
                cpal.Entries[i] = Color.FromArgb(palette[i] >> 16 & 0xFF, palette[i] >> 8 & 0xFF, palette[i] & 0xFF);
                // Set Transparent Color
                cpal.Entries[i & 0xF0] = Color.FromArgb(0, 0xFF, 0x00, 0xFF);
            }
            tileImage.Palette = cpal;
            
            // Set pixels
            Rectangle rect = new Rectangle(0, 0, tileImage.Width, tileImage.Height);
            System.Drawing.Imaging.BitmapData bmpData = tileImage.LockBits(rect, ImageLockMode.WriteOnly, tileImage.PixelFormat);

            IntPtr ptr = bmpData.Scan0;

            byte[] px = new byte[tileData.Length * 2 * paletteLines];
            for (int i = 0; i < tileData.Length / 0x20; i++) {
                int tilStart = i * 0x20;
                for (int x = 0; x < 4; x++) {
                    for (int y = 0; y < 8; y++) {
                        int basee = tileData[tilStart + x + y * 4];
                        for (int p = 0; p < paletteLines * 8; p += 8) {
                            px[(i * 8 + y) * bmpData.Stride + x * 2 + p] = (byte)((basee >> 4) + p * 2);
                            px[(i * 8 + y) * bmpData.Stride + x * 2 + p + 1] = (byte)((basee & 0xF) + p * 2);
                        }
                    }
                }
            }
            Marshal.Copy(px, 0, ptr, px.Length);
            tileImage.UnlockBits(bmpData);
            
            Image = tileImage;

            return tileData;
        }

        Sprite LoadSprite(string obj, int startingArtTile, int palStart) {
            return LoadSprite(obj, startingArtTile, palStart, "", false);
        }
        Sprite LoadSprite(string obj, int startingArtTile, int palStart, string dplcpath, bool isPlayerDPLC) {
            return LoadSprite(obj, startingArtTile, palStart, dplcpath, isPlayerDPLC, 0, 9999999, startingArtTile);
        }
        Sprite LoadSprite(string obj, int startingArtTile, int palStart, string dplcpath, bool isPlayerDPLC, int minframe, int maxframe) {
            return LoadSprite(obj, startingArtTile, palStart, dplcpath, isPlayerDPLC, minframe, maxframe, startingArtTile);
        }
        Sprite LoadSprite(string obj, int startingArtTile, int palStart, string dplcpath, bool isPlayerDPLC, int minframe, int maxframe, int dplcStartingArtTile) {
            Sprite sprite = new Sprite();
            string[] spp = obj.Split('\\');
            sprite.Name = spp[spp.Length - 1].Replace("Map - ", "").Replace(".asm", "");

            EngineVersion engineVersionPLC = EngineVersion.S2;
            if (!isPlayerDPLC)
                engineVersionPLC = EngineVersion.S3K;

            byte[] bin_dplc = null;
            List<int> frames_dplc = new List<int>();
            if (dplcpath != "") {
                if (!File.Exists(dplcpath)) {
                    throw new Exception("Could not find file: '" + dplcpath + "'");
                }
                Dictionary<string, int> labelzzzz;
                bin_dplc = LevelData.ASMToBin(dplcpath, engineVersionPLC, out labelzzzz);

                short endlist = short.MaxValue;
                for (int i = 0; i < endlist; i += 2) {
                    short val = SonicRetro.SonLVL.API.ByteConverter.ToInt16(bin_dplc, i);
                    if (val > -1) {
                        frames_dplc.Add(val);
                        if (val > 0)
                            endlist = Math.Min(endlist, val);
                    }
                }
            }

            Dictionary<string, int> labels = new Dictionary<string, int>();
            byte[] bin = LevelData.ASMToBin(obj, EngineVersion.S3K, out labels);
            List<int> frames = new List<int>();

            int[] addresses = LevelData.GetOffsetList(bin);
            foreach (int item in addresses) {
                if (true) {
                    frames.Add(item);
                }
                else {
                    if (labels != null && labels.ContainsValue(item))
                        foreach (KeyValuePair<string, int> label in labels)
                            if (label.Value == item)
                                frames.Add(item);
                }
            }

            // using (MemoryStream input = new MemoryStream(bin)) {
            Console.WriteLine(obj + ": ");

            for (int f = minframe; f < frames.Count && f <= maxframe; f++) {
                int frameByteOffset = frames[f];

                // Read frame
                int pieces = SonicRetro.SonLVL.API.ByteConverter.ToUInt16(bin, frameByteOffset);
                SpriteFrame frame = new SpriteFrame();
                //for (int i = pieces - 1; i >= 0; i--) {

                int tilIn = 0;
                for (int i = 0; i < pieces; i++) {
                    int yup = i * MappingsTile.Size(EngineVersion.S3K) + frameByteOffset + 2;

                    SpriteFrameTile ti = new SpriteFrameTile();
                    ti.Y = (char)bin[yup];
                    int size = bin[yup + 1];
                    ti.W = (size >> 2 & 0x3) + 1;
                    ti.H = (size & 0x3) + 1;
                    ti.Tile = SonicRetro.SonLVL.API.ByteConverter.ToUInt16(bin, yup + 2);
                    ti.Pal = ti.Tile >> 13 & 3;

                    ti.X = SonicRetro.SonLVL.API.ByteConverter.ToInt16(bin, yup + 4);

                    //*
                    if (ti.Y >= 0x80)
                        ti.Y = ti.Y - 0x100;
                    if (ti.X >= 0x8000)
                        ti.X = ti.X - 0x10000;
                    //*/

                    ti.FlipY = (ti.Tile >> 12 & 1) == 1;
                    ti.FlipX = (ti.Tile >> 11 & 1) == 1;
                    ti.Tile &= 0x7FF;
                    if (bin_dplc != null && f < frames_dplc.Count) {
                        // Console.WriteLine("f: " + f + "      frames_dplc.Count: " + frames_dplc.Count);
                        using (MemoryStream dinput = new MemoryStream(bin_dplc)) {
                            dinput.Seek(frames_dplc[f], SeekOrigin.Begin);
                            
                            int max = BigEndian.Read2(dinput);
                            List<int> frrrrs = new List<int>();

                            if (!isPlayerDPLC) {
                                max++;
                            }

                            int loc = 0, tilecount = 0;
                            for (int d = 0; d < max; d++) {
                                dinput.Seek(d * 2 + frames_dplc[f] + (engineVersionPLC == EngineVersion.S1 ? 1 : 2), SeekOrigin.Begin);
                                ushort read = BigEndian.Read2(dinput);
                                if (isPlayerDPLC) {
                                    tilecount = (read >> 12) + 1;
                                    loc = read & 0xFFF;
                                }
                                else {
                                    tilecount = (read & 0xF) + 1;
                                    loc = read >> 4;
                                }
                                for (int c = 0; c < tilecount; c++) {
                                    frrrrs.Add(loc + c);
                                }
                            }

                            if (isPlayerDPLC) {
                                bool shieldDPLC = false;
                                if (shieldDPLC)
                                    tilIn = ti.Tile;
                                if (tilIn < frrrrs.Count) {
                                    ti.Tile = dplcStartingArtTile + frrrrs[tilIn] - startingArtTile;
                                    // Console.WriteLine("frrrrs[tilIn]: " + ti.Tile.ToString("X"));
                                }
                            }
                            else {
                                if (ti.Tile < frrrrs.Count) {
                                    ti.Tile = frrrrs[ti.Tile];
                                    // Console.WriteLine("frrrrs[ti.Tile]: " + ti.Tile.ToString("X"));
                                }
                            }
                            /*
                            if (isPlayerDPLC && i >= max) {
                                // letsgo = false;
                                truei -= max;
                            }
                            else if (!isPlayerDPLC && i >= max + 1) {
                                letsgo = false;
                            }
                            if (letsgo) {
                                long where = truei * 2 + frames_dplc[f] + (engineVersionPLC == EngineVersion.S1 ? 1 : 2);

                                dinput.Seek(where, SeekOrigin.Begin);

                                // DPLCFrame 
                                // ProcessDPLC

                                int loc;
                                ushort read = BigEndian.Read2(dinput);
                                if (isPlayerDPLC) {
                                    //int tilecount = (read >> 12) + 1;
                                    loc = read & 0xFFF;
                                }
                                else {
                                    //int tilecount = (read & 0xF) + 1;
                                    loc = read >> 4;
                                }
                                ti.Tile = loc;
                            }*/
                        }
                    }

                    tilIn += ti.W * ti.H;

                    frame.Tiles.Add(ti);
                }

                if (pieces == 0) {
                    frame.X = 0;
                    frame.Y = 0;
                    frame.W = 0;
                    frame.H = 0;
                    frame.BoxX = 0;
                    frame.BoxY = 0;
                    sprite.Frames.Add(frame);
                }
                else {
                    sprite.Frames.Add(frame);
                }
            }
            sprite.StartingArtTile = startingArtTile;
            sprite.PalStart = palStart;
            // }
            foreach (SpriteFrame spriteFrame in sprite.Frames) {
                spriteFrame.Parent = sprite;
                if (spriteFrame.BoxX == 0) continue;

                int minX = 9999999;
                int maxX = 0;
                int minY = 9999999;
                int maxY = 0;
                for (int sft = spriteFrame.Tiles.Count - 1; sft >= 0; sft--) {
                    SpriteFrameTile spriteFrameTile = spriteFrame.Tiles[sft];
                    for (int x = 0; x < spriteFrameTile.W; x++) {
                        for (int y = 0; y < spriteFrameTile.H; y++) {
                            int jx = spriteFrameTile.X + x * 8 + 4;
                            int jy = spriteFrameTile.Y + y * 8 + 4;

                            int tx = x;
                            int ty = y;
                            if (spriteFrameTile.FlipX)
                                tx = spriteFrameTile.W - 1 - x;
                            if (spriteFrameTile.FlipY)
                                ty = spriteFrameTile.H - 1 - y;

                            if (minX > jx - 4)
                                minX = jx - 4;
                            if (maxX < jx + 4)
                                maxX = jx + 4;
                            if (minY > jy - 4)
                                minY = jy - 4;
                            if (maxY < jy + 4)
                                maxY = jy + 4;
                        }
                    }
                }
                spriteFrame.X = (short)minX;
                spriteFrame.Y = (short)minY;
                spriteFrame.W = (ushort)(maxX - minX);
                spriteFrame.H = (ushort)(maxY - minY);
            }
            return sprite;
        }

        public int MaxX = 0;
        public int MaxY = 0;
        public short NextX = 0;
        public short NextY = 0;
        public short PackingSpace = 1;

        bool BoxCollide(List<SpriteFrame> spriteFrames, SpriteFrame spriteFrame, int x, int y) {
            for (var i = 0; i < spriteFrames.Count; i++) {
                var s2 = spriteFrames[i];
                if (s2 == spriteFrame)
                    continue;

                if (s2.BoxX < 0)
                    continue;

                if (x < s2.BoxX + s2.W + PackingSpace &&
                    x + spriteFrame.W + PackingSpace >= s2.BoxX &&
                    y < s2.BoxY + s2.H + PackingSpace &&
                    y + spriteFrame.H + PackingSpace >= s2.BoxY)
                    return true;
            }

            return false;
        }
        bool PlaceBox(List<SpriteFrame> spriteFrames, SpriteFrame box, int maxX, int maxy) {
            for (int y = PackingSpace; y < maxy; y += 1) {
                for (int x = PackingSpace; x < maxX - box.W - PackingSpace; x += 1) {
                    if (!BoxCollide(spriteFrames, box, x, y)) {
                        box.BoxX = (short)x;
                        box.BoxY = (short)y;
                        return true;
                    }
                }
            }
            return false;
        }
        bool PackBoxes(List<SpriteFrame> spriteFrames, SpriteFrame box) {
            if (MaxX == 0) {
                box.BoxX = NextX;
                box.BoxY = NextY;
                NextX += (short)(box.W + PackingSpace);
            }
            else {
                // if we can place the item, we move to the next row
                if (!PlaceBox(spriteFrames, box, MaxX, MaxY)) {
                    // Can't fit on the current row, let's move to the next
                    if (NextX + box.W > MaxX) {
                        NextY = (short)MaxY;
                        NextX = PackingSpace;
                    }
                    box.BoxX = NextX;
                    box.BoxY = NextY;
                    NextY += (short)(box.H + PackingSpace);
                }
            }

            /*
            if ((MaxX < box.BoxX + box.W + PackingSpace) || (MaxY < box.BoxY + box.H + PackingSpace)) {
                MaxX *= 2;
                MaxY *= 2;
                if (MaxX == 0) {
                    MaxX = 256;
                    MaxY = 256;
                }
            }
            //*/

            MaxX = Math.Max(MaxX, box.BoxX + box.W + PackingSpace);
            MaxY = Math.Max(MaxY, box.BoxY + box.H + PackingSpace);

            return true;
        }


        int PackAllBoxes(List<SpriteFrame> spriteFrames, int intialH) {
            var area = 0;
            var maxW = 0;
            var maxH = 0;
            for (var i = 0; i < spriteFrames.Count; i++) {
                area += spriteFrames[i].W * spriteFrames[i].H;
                maxW = Math.Max(maxW, spriteFrames[i].W);
                maxH = Math.Max(maxH, spriteFrames[i].H);
                spriteFrames[i].Index = i;
            }
            var size = Math.Max(maxW, maxH);
            
            int FinalWidth = 512;
            int FinalHeight = intialH;

            // spriteFrames.Sort((x, y) => (y.W * y.H) - (x.W * x.H));
            spriteFrames.Sort((x, y) => y.H - x.H);

            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine("New iteration! Size: " + FinalHeight);

            bool Reset = false;
            bool Valid = false;
            do {
                int MaxX = 0;
                int MaxY = 0;
                Valid = true;
                Reset = false;

                NextX = PackingSpace;
                NextY = PackingSpace;
                for (var i = 0; i < spriteFrames.Count; i++) {
                    SpriteFrame box = spriteFrames[i];
                    if (box.W == 0) {
                        box.BoxX = 0;
                        box.BoxY = 0;
                        continue;
                    }

                    if (MaxX == 0) {
                        box.BoxX = NextX;
                        box.BoxY = NextY;
                        NextX += (short)(box.W + PackingSpace);
                    }
                    else {
                        // if we can place the item, we move to the next row
                        if (!PlaceBox(spriteFrames, box, FinalWidth, MaxY)) {
                            // Can't fit on the current row, let's move to the next
                            if (NextX + box.W > FinalWidth) {
                                NextY = (short)MaxY;
                                NextX = PackingSpace;
                            }
                            box.BoxX = NextX;
                            box.BoxY = NextY;
                        }
                        NextX += (short)(box.W + PackingSpace);
                    }
                    MaxX = Math.Max(MaxX, box.BoxX + box.W + PackingSpace);
                    MaxY = Math.Max(MaxY, box.BoxY + box.H + PackingSpace);

                    if (box.BoxY + box.H + PackingSpace >= FinalHeight) {
                        Valid = false;
                        Console.WriteLine("Invalid Y: " + box.BoxY + " (Height: " + box.H + ", Size: " + FinalHeight + ")");
                        break;
                    }
                }
                if (!Valid) {
                    if (FinalWidth < 512)
                        FinalHeight = FinalWidth += FinalWidth;
                    else
                        FinalHeight += FinalHeight;

                    Console.WriteLine("New iteration! Size: " + FinalHeight);

                    Reset = true;
                    foreach (SpriteFrame spriteFrame in spriteFrames) {
                        spriteFrame.BoxX = -100;
                        spriteFrame.BoxY = -100;
                    }
                }
            }
            while (Reset);

            spriteFrames.Sort((x, y) => x.Index - y.Index);
            for (var i = 0; i < spriteFrames.Count; i++) {
                SpriteFrame box = spriteFrames[i];
                // Console.WriteLine("Placed box[" + (box.Index + 1).ToString("X") + "] at " + box.BoxX + ", " + box.BoxY + "");
            }

            return FinalWidth | FinalHeight << 16;
        }

        List<SprAnim> GetAnimsFromFile(Sprite spr, string filename, int frameoff) {
            List<SprAnim> list = new List<SprAnim>();

            byte[] bin = null;
            List<int> frames = new List<int>();
            bin = LevelData.ASMToBin(filename, EngineVersion.S2);

            short endlist = short.MaxValue;
            for (int i = 0; i < endlist; i += 2) {
                short val = SonicRetro.SonLVL.API.ByteConverter.ToInt16(bin, i);
                if (val > -1) {
                    frames.Add(val);
                    if (val > 0)
                        endlist = Math.Min(endlist, val);
                }
            }

            for (int i = 0; i < frames.Count; i++) {
                SprAnim sprAnim = new SprAnim();
                sprAnim.Name = "Animation " + (i + 1);
                sprAnim.FrameDuration = bin[frames[i]];
                if ((sprAnim.FrameDuration & 0x80) == 0x80)
                    sprAnim.FrameDuration = 0;
                sprAnim.FrameDuration++;

                int tape = frames[i];
                while (bin[++tape] < 0xF0) {
                    sprAnim.Frames.Add(new SprFrm(bin[tape] + frameoff, spr));
                }

                switch (bin[tape]) {
                    case 0xFF:
                        sprAnim.FrameLoop = 0;
                        break;
                    case 0xFE:
                        sprAnim.FrameLoop = sprAnim.Frames.Count - bin[tape + 1];
                        break;
                    default:
                        sprAnim.FrameLoop = 0;
                        break;
                }


                for (int d = 0; d < sprAnim.Frames.Count; d++) {
                    // Console.Write(sprAnim.Frames[d].ToString("X") + " ");
                }
                // Console.WriteLine();

                list.Add(sprAnim);
            }

            return list;
        }

        enum SpriteToExport {
            Sonic,
            AIZ1,
        }

        public class FrameAlt {
            public List<int> Frames = new List<int>();
            public string Property;
            public string Value;
            public FrameAlt(List<int> frames, string property, string value) {
                Frames = frames;
                Property = property;
                Value = value;
            }
        }

        void OpenFolder(string wh) {
            string root;
            string where;
            string paleetteLeeel = null;
            string outZoneID = "Generic";
            string fileName = "Objects";
            byte[] artTiles = null;
            List<Sprite> sprites = new List<Sprite>();
            List<PLCRequest> requests = new List<PLCRequest>();

            List<FrameAlt> frameAlterations = new List<FrameAlt>();

            root = @"C:\Users\Justin\skdisasm-master\";


            /*
            requests.Add(new PLCRequest(root + @"General\Sprites\xxxxxxxxx\xxxxxxxxx.bin", -1, CompressionType.KosinskiM));
            //*/

            {
                /*
                Spring Twirl
                48 - 59
                Spring CS
                48 - 59
                Stand CS
                60 - 70

                Running Down Thing
                72 - 83

                Turntable/Twister
                84 - 90
                Pole Swing H/Shaft Swing
                91 - 96
                Pole Swing V
                98 - 103

                Running Up Cylinder/Tree
                104 - 118

                Hang Idle
                143 - 146
                Hang Move
                127 - 132

                Shimmy Idle/Move
                147 - 148
                */
            }

            bool customSpriteDirective = false;
            List<Sprite> customSprites = new List<Sprite>();

            int intialH = 512;
            int frmoff = 0;

            if (File.Exists(wh) && wh != "Player") {
                Match args;
                string pattern;
                string[] fileLines = File.ReadAllLines(wh);
                foreach (string line in fileLines) {
                    if (line == "") continue;
                    if (line[0] == '#') continue;

                    if (line.StartsWith("OUTFOLDER")) {
                        pattern = @"OUTFOLDER (.+)$";
                        args = Regex.Match(line, pattern);

                        outZoneID = args.Groups[1].Value;

                    }
                    else if (line.StartsWith("INITIALH")) {
                        string[] argsStr = line.Substring("INITIALH ".Length).Split(',');
                        intialH = S3toIE2Level.ParseInt(argsStr[0].Trim());
                    }
                    else if (line.StartsWith("FRAMEOFF")) {
                        string[] argsStr = line.Substring("FRAMEOFF ".Length).Split(',');
                        frmoff = S3toIE2Level.ParseInt(argsStr[0].Trim());
                    }
                    else if (line.StartsWith("FILENAME")) {
                        pattern = @"FILENAME (.+)$";
                        args = Regex.Match(line, pattern);

                        fileName = args.Groups[1].Value;
                    }
                    else if (line.StartsWith("PALETTE")) {
                        pattern = @"PALETTE (.+)$";
                        args = Regex.Match(line, pattern);

                        paleetteLeeel = Globals.ROOT + args.Groups[1].Value;
                    }
                    else if (line.StartsWith("REQUEST")) {
                        pattern = @"REQUEST (.+),([A-Fa-f0-9]*)(?:,?(.*))$";
                        string[] argsStr = line.Substring("REQUEST ".Length).Split(',');

                        string reqfile = Globals.ROOT + argsStr[0].Trim();
                        int offset = -1;
                        if (argsStr.Length >= 2 && argsStr[1].Trim() != "")
                            offset = S3toIE2Level.ParseInt(argsStr[1].Trim());
                        string comptype = "";
                        if (argsStr.Length >= 3 && argsStr[2].Trim() != "")
                            comptype = argsStr[2].Trim();
                        requests.Add(new PLCRequest(reqfile, offset, comptype == "NEM" ? CompressionType.Nemesis : comptype == "ENI" ? CompressionType.Enigma : comptype == "KOS" ? CompressionType.Kosinski : comptype == "KOSM" ? CompressionType.KosinskiM : CompressionType.Uncompressed));
                    }
                    else if (line.StartsWith("SPRITE")) {
                        pattern = @"SPRITE (.+),(.*),([A-Fa-f0-9]+),([A-Fa-f0-9]+),?([A-Fa-f0-9]*),?([A-Fa-f0-9]*),?(.*),?(.*)$";
                        string[] argsStr = line.Substring("SPRITE ".Length).Split(',');

                        string mapfile = Globals.ROOT + argsStr[0].Trim();
                        string rename = argsStr[1].Trim();
                        int startingArtTile = S3toIE2Level.ParseInt(argsStr[2].Trim());
                        int pal = S3toIE2Level.ParseInt(argsStr[3].Trim());
                        int minframe = 0;
                        int maxframe = 99999999;
                        string dplcfile = "";
                        bool isPlayer = false;
                        int dplcArtTile = startingArtTile;
                        if (argsStr.Length >= 5) minframe = S3toIE2Level.ParseInt(argsStr[4].Trim());
                        if (argsStr.Length >= 6) maxframe = S3toIE2Level.ParseInt(argsStr[5].Trim());
                        if (argsStr.Length >= 7 && argsStr[6].Trim() != "") dplcfile = Globals.ROOT + argsStr[6].Trim();
                        if (argsStr.Length >= 8) isPlayer = argsStr[7].Trim().ToUpper() == "TRUE";
                        if (argsStr.Length >= 9) dplcArtTile = S3toIE2Level.ParseInt(argsStr[8].Trim());

                        sprites.Add(LoadSprite(mapfile, startingArtTile, pal, dplcfile, isPlayer, minframe, maxframe, dplcArtTile));
                        if (rename != "")
                            sprites.Last().Name = rename;
                    }
                    else if (line.StartsWith("CUSTOMSPRITETOGGLE")) {
                        string[] argsStr = line.Substring("CUSTOMSPRITETOGGLE ".Length).Split(',');
                        customSpriteDirective = argsStr[0].Trim().ToUpper() == "TRUE";
                    }
                    else if (line.StartsWith("NEWSPRITE")) {
                        string[] argsStr = line.Substring("NEWSPRITE ".Length).Split(',');
                        customSprites.Add(new Sprite());
                        customSprites.Last().Name = argsStr[0].Trim();
                    }
                    else if (line.StartsWith("ANIMATION")) {
                        string[] argsStr = line.Substring("ANIMATION ".Length).Split(',');
                        customSprites.Last().Anim.Add(new SprAnim());
                        customSprites.Last().Anim.Last().Name = argsStr[0].Trim();

                        string framesWhereStr = argsStr[1].Trim();
                        string[] framesWhere = framesWhereStr.Split('|');
                        foreach (string whe in framesWhere) {
                            string[] ar = whe.Split('[');
                            if (ar.Length == 1)
                                ar = whe.Split('{');
                            if (ar.Length == 1)
                                ar = whe.Split(';');

                            Sprite spr = null;
                            foreach (Sprite s in sprites) {
                                if (s.Name == ar[0]) {
                                    spr = s;
                                    break;
                                }
                            }

                            if (spr == null) {
                                throw new Exception("Could not find Sprite of name '" + ar[0] + "'!");
                            }

                            SprAnim sprAnim = customSprites.Last().Anim.Last();
                            sprAnim.FrameSpeed = 1;
                            sprAnim.FrameLoop = 0;
                            sprAnim.FrameDuration = 1;
                            ar[1] = ar[1].Replace("]", "").Replace("}", "");
                            string[] arrrgs = ar[1].Split(';');
                            
                            // if this is a [From;To]
                            if (whe.Contains('[')) {
                                for (int i = S3toIE2Level.ParseInt(arrrgs[0]); i <= S3toIE2Level.ParseInt(arrrgs[1]); i++) {
                                    sprAnim.Frames.Add(new SprFrm(i, spr));
                                }
                            }
                            // if this is a list of frames 0;1;2;3;4
                            else if (whe.Contains('{')) {
                                foreach (string ind in arrrgs) {
                                    sprAnim.Frames.Add(new SprFrm(S3toIE2Level.ParseInt(ind), spr));
                                }
                            }
                            // if this is ALL
                            else if (ar[1] == "ALL") {
                                for (int i = 0; i < spr.Frames.Count; i++) {
                                    sprAnim.Frames.Add(new SprFrm(i, spr));
                                }
                            }
                            // just a frame number
                            else {
                                sprAnim.Frames.Add(new SprFrm(S3toIE2Level.ParseInt(ar[1]), spr));
                            }
                        }
                    }
                    else if (line.StartsWith("SPEED")) {
                        string[] argsStr = line.Substring("SPEED ".Length).Split(',');
                        customSprites.Last().Anim.Last().FrameSpeed = S3toIE2Level.ParseInt(argsStr[0].Trim());
                    }
                    else if (line.StartsWith("LOOPINDEX")) {
                        string[] argsStr = line.Substring("LOOPINDEX ".Length).Split(',');
                        customSprites.Last().Anim.Last().FrameLoop = S3toIE2Level.ParseInt(argsStr[0].Trim());
                    }
                    else if (line.StartsWith("FRAME")) {
                        string[] argsStr = line.Substring("FRAME ".Length).Split(',');

                        List<int> indexes = new List<int>();
                        string selector = argsStr[0].Trim().Replace("]", "").Replace("}", "");
                        string[] arrrgs = selector.Substring(1).Split(';');

                        // if this is a [From;To]
                        if (selector[0] == '[') {
                            for (int i = S3toIE2Level.ParseInt(arrrgs[0]); i <= S3toIE2Level.ParseInt(arrrgs[1]); i++) {
                                indexes.Add(i);
                            }
                        }
                        // if this is a list of frames 0;1;2;3;4
                        else if (selector[0] == '{') {
                            int b = 0;
                            foreach (string ind in arrrgs) {
                                indexes.Add(b);
                                b++;
                            }
                        }
                        // if this is ALL
                        else if (selector == "ALL") {
                            SprAnim sprAnim = customSprites.Last().Anim.Last();
                            for (int i = 0; i < sprAnim.Frames.Count; i++) {
                                indexes.Add(i);
                            }
                        }
                        // just a frame number
                        else {
                            indexes.Add(S3toIE2Level.ParseInt(selector));
                        }

                        customSprites.Last().Anim.Last().FrameAlterations.Add(new FrameAlt(indexes, argsStr[1].Trim(), argsStr[2].Trim()));
                    }
                    else if (line.StartsWith("PALSHIFT")) {
                        string[] argsStr = line.Substring("PALSHIFT ".Length).Split(',');

                        List<int> indexes = new List<int>();
                        string selector = argsStr[0].Trim().Replace("]", "").Replace("}", "");
                        string[] arrrgs = selector.Substring(1).Split(';');

                        // if this is a [From;To]
                        if (selector[0] == '[') {
                            for (int i = S3toIE2Level.ParseInt(arrrgs[0]); i <= S3toIE2Level.ParseInt(arrrgs[1]); i++) {
                                indexes.Add(i);
                            }
                        }
                        // if this is a list of frames 0;1;2;3;4
                        else if (selector[0] == '{') {
                            int b = 0;
                            foreach (string ind in arrrgs) {
                                indexes.Add(b);
                                b++;
                            }
                        }
                        // if this is ALL
                        else if (selector == "ALL") {
                            SprAnim sprAnim = customSprites.Last().Anim.Last();
                            for (int i = 0; i < sprAnim.Frames.Count; i++) {
                                indexes.Add(i);
                            }
                        }
                        // just a frame number
                        else {
                            indexes.Add(S3toIE2Level.ParseInt(selector));
                        }

                        Sprite sss = sprites.Last();
                        foreach (int d in indexes) {
                            sss.Frames[d].PalOff = S3toIE2Level.ParseInt(argsStr[1]);
                        }
                    }
                }
                
                artTiles = ArtToBitmap(paleetteLeeel, requests);
            }

            if (customSpriteDirective) {
                foreach (Sprite sprite in customSprites) {
                    List<SpriteFrame> mySpriteFrames = new List<SpriteFrame>();
                    for (int a = 0; a < sprite.Anim.Count; a++) {
                        // Console.WriteLine("For anim '" + sprite.Anim[a].Name + "':");
                        for (int f = 0; f < sprite.Anim[a].Frames.Count; f++) {
                            Sprite wherespr = sprite.Anim[a].Frames[f].Spr;
                            int wherenst = sprite.Anim[a].Frames[f].Index;
                            if (wherenst < 0)
                                wherenst = 0;

                            // Console.WriteLine("   added frame using mapping frame " + wherenst + " of sprite '" + wherespr.Name + "' to index " + mySpriteFrames.Count + ".");
                            mySpriteFrames.Add(wherespr.Frames[wherenst]);

                            sprite.Anim[a].Frames[f].Spr = sprite;
                            sprite.Anim[a].Frames[f].Index = mySpriteFrames.Count - 1;
                        }
                    }
                    sprite.Frames = mySpriteFrames;
                }
                sprites = customSprites;
            }

            int spriteToExport = -1;
            // Player
            if (spriteToExport == 0 || wh == "Player") {
                outZoneID = "S3";
                fileName = "Sonic";
                where = root + @"General\Sprites\Sonic\";
                requests.Add(new PLCRequest(where + @"Art\Sonic.bin", 0, CompressionType.Uncompressed));
                requests.Add(new PLCRequest(where + @"Art\Sonic Extra.bin", -1, CompressionType.Uncompressed));
                artTiles = S3toIE2Level.LoadTiles(requests);

                sprites.Add(LoadSprite(where + @"Map - Sonic.asm", 0x0, 0, where + @"DPLC - Sonic.asm", true, 0, 0xD9));

                Sprite sonic = sprites.Last();
                //*
                List<SprAnim> animList = GetAnimsFromFile(sonic, where + @"Anim - Sonic.asm", -1);
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Idle", 1, 0xB9, 0xB9, 0));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Bored 1", animList[6 - 1]));
                sonic.Anim.Last().Frames.RemoveRange(0, 30); // Remove 3 seconds.
                sonic.Anim.Add(SprAnim.WrapSprAnim("Bored 2", animList[6 - 1]));
                sonic.Anim.Last().Frames.RemoveRange(0, 30); // Remove 3 seconds.
                sonic.Anim.Add(SprAnim.WrapSprAnim("Look Up", animList[8 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Crouch", animList[9 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Walk", 256, animList[1 - 1]));
                sonic.Anim.Last().FrameSpeed = 256;
                sonic.Anim.Add(SprAnim.WrapSprAnim("Air Walk", 256, animList[1 - 1]));
                sonic.Anim.Last().FrameSpeed = 256;
                sonic.Anim.Add(SprAnim.WrapSprAnim("Jog", 256, animList[1 - 1]));
                sonic.Anim.Last().FrameSpeed = 256;
                sonic.Anim.Add(SprAnim.WrapSprAnim("Run", 256, animList[2 - 1]));
                sonic.Anim.Last().FrameSpeed = 256;
                sonic.Anim.Add(SprAnim.WrapSprAnim("Dash", 256, animList[2 - 1]));
                sonic.Anim.Last().FrameSpeed = 256;
                sonic.Anim.Add(SprAnim.WrapSprAnim("Jump", 256, animList[3 - 1]));
                sonic.Anim.Last().FrameSpeed = 256;
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Spring Twirl", 5, 48, 59, 0));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Spring Diagonal", animList[17 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Skid", animList[14 - 1]));
                sonic.Anim.Last().Frames.Remove(sonic.Anim.Last().Frames.Last());
                sonic.Anim.Add(SprAnim.WrapSprAnim("Skid Turn", animList[14 - 1]));
                sonic.Anim.Last().Frames.RemoveRange(0, sonic.Anim.Last().Frames.Count - 1);
                sonic.Anim.Add(SprAnim.WrapSprAnim("Spindash", animList[10 - 1]));
                sonic.Anim.Last().FrameSpeed = 1;
                sonic.Anim.Add(SprAnim.WrapSprAnim("Dropdash", animList[3 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Push", 32, animList[5 - 1]));
                sonic.Anim.Last().FrameSpeed = 1;
                sonic.Anim.Add(SprAnim.WrapSprAnim("Hurt", animList[27 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Die", animList[25 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Drown", animList[24 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Balance 1", animList[7 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Balance 2", animList[13 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Spring CS", animList[17 - 1]));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Stand CS", 4, 60, 70, 0));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Fan", animList[16 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Victory", animList[20 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Outta Here", animList[3 - 1]));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Hang", 9, 143, 146, 0));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Hang Move", 4, 127, 132, 0));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Pole Swing V", 9, 98, 103, 0));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Pole Swing H", 9, 91, 96, 0));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Shaft Swing", 9, 91, 96, 0));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Turntable", 9, 84, 90, 0));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Twister", 9, 84, 90, 0));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Spiral Run", 9, 104, 118, 0));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Stick", animList[3 - 1])); // #
                sonic.Anim.Add(SprAnim.WrapSprAnim("Pulley Hold", animList[12 - 1]));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Shimmy Idle", 9, 147, 148, 0));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Shimmy Move", 0, 148, 148, 0));
                sonic.Anim.Add(SprAnim.GetSpan(sonic, "Bubble", 1, 0x69, 0x76, 0));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Breathe", animList[22 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Ride", animList[3 - 1])); // #
                sonic.Anim.Add(SprAnim.WrapSprAnim("Cling", animList[18 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Bungee", animList[3 - 1])); // #
                sonic.Anim.Add(SprAnim.WrapSprAnim("TwistRun", animList[3 - 1])); // #
                sonic.Anim.Add(SprAnim.WrapSprAnim("Flume", animList[26 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Transform", animList[32 - 1]));
                sonic.Anim.Add(SprAnim.WrapSprAnim("Fly", animList[3 - 1])); // #
                sonic.Anim.Add(SprAnim.WrapSprAnim("Fly Tired", animList[3 - 1])); // #
                sonic.Anim.Add(SprAnim.WrapSprAnim("Fly Lift", animList[3 - 1])); // #
                sonic.Anim.Add(SprAnim.WrapSprAnim("Fly Lift Tired", animList[3 - 1])); // #
                sonic.Anim.Add(SprAnim.WrapSprAnim("Swim", animList[3 - 1])); // #
                sonic.Anim.Add(SprAnim.WrapSprAnim("Swim Tired", animList[3 - 1])); // #

                // sonic.Anim.Add(SprAnim.WrapSprAnim("Cylinder Run", animList[3 - 1])); // #
            }
            // AIZ
            else if (spriteToExport == 1) {
                outZoneID = "AIZ";
                where = root + @"Levels\AIZ\";
                requests.Add(new PLCRequest(where + @"Tiles\Act 1 Primary.bin", 0));
                //requests.Add(new PLCRequest(where + @"Tiles\Act 1 Main Level.bin", -1));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Zip Vine.bin", 0x324, CompressionType.Nemesis));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Misc Art 1.bin", 0x333, CompressionType.Nemesis));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Falling Log.bin", 0x3CF, CompressionType.Nemesis));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Cork Floor 1.bin", 0x3F7, CompressionType.Nemesis));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Swing Vine.bin", 0x41B, CompressionType.Nemesis));
                requests.Add(new PLCRequest(root + @"General\Sprites\Bubbles\Bubbles.bin", 0x45C));
                requests.Add(new PLCRequest(root + @"General\Sprites\Rhino\Rhino.bin", 0x800, CompressionType.Uncompressed));
                requests.Add(new PLCRequest(root + @"General\Sprites\Monkey Dude\Monkey Dude.bin", -1, CompressionType.KosinskiM));
                requests.Add(new PLCRequest(root + @"General\Sprites\Tulipon\Tulipon.bin", -1, CompressionType.KosinskiM));
                requests.Add(new PLCRequest(root + @"General\Sprites\Caterkiller Jr\Caterkiller Jr.bin", -1, CompressionType.KosinskiM));

                requests.Add(new PLCRequest(where + @"Tiles\Act 2 Primary.bin", 0x2000));
                requests.Add(new PLCRequest(where + @"Tiles\Act 2 Secondary.bin", -1));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Misc Art 2.bin", 0x22E9));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Swing Vine.bin", 0x241B));
                // requests.Add(new PLCRequest(where + @"Nemesis Art\BG Tree.bin", 0x2438));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Cork Floor 2.bin", 0x2440));
                requests.Add(new PLCRequest(@"C:\Users\Justin\skdisasm-master\General\Sprites\Buttons\Gray Button.bin", 0x2456));
                requests.Add(new PLCRequest(@"C:\Users\Justin\skdisasm-master\General\Sprites\Bubbles\Bubbles.bin", 0x245C));

                // requests.Add(new PLCRequest(where + @"Nemesis Art\Miniboss.bin", 0x3000));
                // requests.Add(new PLCRequest(where + @"Nemesis Art\Miniboss Fire.bin", -1));
                // requests.Add(new PLCRequest(where + @"Nemesis Art\Miniboss Small.bin", -1));
                // requests.Add(new PLCRequest(where + @"Nemesis Art\End Boss.bin", 0x3800, CompressionType.KosinskiM));

                artTiles = ArtToBitmap(where + @"Palettes\Main.bin", requests);
                paleetteLeeel = where + @"Palettes\Main.bin";

                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - (&MHZ) Ride Vine.asm", 0x41B, 0));
                sprites.Last().Name = "Ride Vine";
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Act 1 Tree.asm", 1, 2));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Act 1 Zipline Peg.asm", 0x324, 2));
                // sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Act 2 Background Tree.asm", 0x2438, 2));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Collapsing Platform.asm", 1, 2, "", false, 0, 0));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Collapsing Platform 2.asm", 0x2001, 2, "", false, 0, 0));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Cork Floor.asm", 1, 2, "", false, 0, 0));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Cork Floor 2.asm", 0x2001, 2, "", false, 0, 0));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Falling Log.asm", 0x3CF, 2));
                sprites.Last().Name = "Falling Log (Act 1)";
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Falling Log Splash.asm", 0x3CF, 2));
                sprites.Last().Name = "Falling Log Splash (Act 1)";
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Falling Log 2.asm", 0x22E9, 2));
                sprites.Last().Name = "Falling Log (Act 2)";
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Falling Log Splash 2.asm", 0x22E9, 3));
                sprites.Last().Name = "Falling Log Splash (Act 2)";
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Floating Platform.asm", 0x3F7, 2));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Floating Platform.asm", 0x2440, 2));
                sprites.Last().Name = "Floating Platform 2";
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Foreground Plant.asm", 0x333, 2));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Rock.asm", 0x333, 1));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Rock 2.asm", 0x22E9, 2));

                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Breakable Wall.asm", 0x2001, 2));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Disappearing Floor.asm", 0x2001, 2));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Disappearing Floor Water.asm", 0x22E9, 3));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Draw Bridge Fire.asm", 0x22E9, 2));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Collapsing Log Bridge.asm", 0x22E9, 2));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Drawbridge.asm", 0x22E9, 2));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Flipping Bridge.asm", 0x22E9, 2));
                sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Spiked Log.asm", 0x22E9, 2));

                sprites.Add(LoadSprite(root + @"Levels\Misc\Map - Still Sprites.asm", 0x22E9, 2, "", false, 0, 4));
                sprites.Last().Name = "Non Animated Sprites";

                sprites.Add(LoadSprite(root + @"Levels\Misc\Map - Animated Still Sprites.asm", 0x22E9, 2, "", false, 0, 8));
                sprites.Last().Name = "Animated Sprites";

                sprites.Add(LoadSprite(root + @"General\Sprites\Rhino\Map - RhinoBot.asm", 0x800, 1, root + @"General\Sprites\Rhino\DPLC - RhinoBot.asm", false, 0, 3));
                sprites.Add(LoadSprite(root + @"General\Sprites\Rhino\Map - RhinoBot.asm", 0x800, 0, root + @"General\Sprites\Rhino\DPLC - RhinoBot.asm", false, 4, 7));
                sprites.Last().Name = "RhinoBot Dust";
                sprites.Add(LoadSprite(root + @"General\Sprites\Tulipon\Map - Tulipon.asm", 0x86C, 1));
                sprites.Add(LoadSprite(root + @"General\Sprites\Monkey Dude\Map - Monkey Dude.asm", 0x855, 1));
                sprites.Add(LoadSprite(root + @"General\Sprites\Caterkiller Jr\Map - Caterkiller Jr.asm", 0x88A, 1));

                // sprites.Add(LoadSprite(root + @"General\Sprites\xxxxxx\xxxxxxx.asm", 0x800, 1));
            }
            // CNZ
            else if (spriteToExport == 4) {
                outZoneID = "CNZ";
                where = root + @"Levels\CNZ\";
                requests.Add(new PLCRequest(where + @"Tiles\Act 1 Primary.bin", 0));
                //requests.Add(new PLCRequest(where + @"Tiles\Act 1 Main Level.bin", -1));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Zip Vine.bin", 0x324, CompressionType.Nemesis));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Misc Art 1.bin", 0x333, CompressionType.Nemesis));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Falling Log.bin", 0x3CF, CompressionType.Nemesis));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Cork Floor 1.bin", 0x3F7, CompressionType.Nemesis));
                requests.Add(new PLCRequest(where + @"Nemesis Art\Swing Vine.bin", 0x41B, CompressionType.Nemesis));
                requests.Add(new PLCRequest(root + @"General\Sprites\Bubbles\Bubbles.bin", 0x45C));
                requests.Add(new PLCRequest(root + @"General\Sprites\Rhino\Rhino.bin", 0x800, CompressionType.Uncompressed));
                requests.Add(new PLCRequest(root + @"General\Sprites\Monkey Dude\Monkey Dude.bin", -1, CompressionType.KosinskiM));
                requests.Add(new PLCRequest(root + @"General\Sprites\Tulipon\Tulipon.bin", -1, CompressionType.KosinskiM));
                requests.Add(new PLCRequest(root + @"General\Sprites\Caterkiller Jr\Caterkiller Jr.bin", -1, CompressionType.KosinskiM));
            }

            /*
            where = @"C:\Users\Justin\skdisasm-master\Levels\MGZ\";
            requests.Add(new PLCRequest(where + @"Tiles\Primary.bin", 0));
            requests.Add(new PLCRequest(where + @"Tiles\Act 1 Secondary.bin", -1));
            requests.Add(new PLCRequest(where + @"Nemesis Art\Misc Art 1.bin", 0x35F));
            requests.Add(new PLCRequest(where + @"Nemesis Art\Misc Art 2.bin", 0x3FF));
            ArtToBitmap(where + @"Palettes\Main.bin", requests);

            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Dash Trigger.asm", 0x35F, 1));
            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Head Trigger.asm", 0x3FF, 1));
            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Pulley.asm", 0x35F, 1));
            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Floating Platform.asm", 1, 2));
            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Collapsing Bridge.asm", 1, 2));
            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Breakable Wall.asm", 1, 2));
            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Moving Spike Platform.asm", 1, 2));
            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Smashing Pillar.asm", 1, 2));
            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Swinging Platform.asm", 0x35F, 2));
            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Swinging Spike Ball.asm", 0x35F, 1));
            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Top Platform.asm", 0x35F, 1));
            sprites.Add(LoadSprite(where + @"Misc Object Data\Map - Trigger Platform.asm", 1, 2));
            //*/

            if (sprites.Count == 0) return;

            List<SpriteFrame> spriteFrames = new List<SpriteFrame>();
            foreach (Sprite sprite in sprites) {
                foreach (SpriteFrame spriteFrame in sprite.Frames) {
                    spriteFrame.BoxX = -100;
                    spriteFrame.BoxY = -100;
                    spriteFrames.Add(spriteFrame);
                }
            }

            MaxX = 0;
            MaxY = 0;
            NextX = PackingSpace;
            NextY = PackingSpace;

            MaxX = MaxY = PackAllBoxes(spriteFrames, intialH);
            MaxX &= 0xFFFF;
            MaxY >>= 16;

            foreach (SpriteFrame spriteFrame in spriteFrames) {
                if (spriteFrame.BoxX < 0) {
                    spriteFrame.BoxX = 0;
                    spriteFrame.BoxY = 0;
                }
            }

            if (!Directory.Exists(Globals.OUT + outZoneID + "\\"))
                Directory.CreateDirectory(Globals.OUT + outZoneID + "\\");
            
            // Export RSDK Animation file
            foreach (Sprite sprite in sprites) {
                using (FileStream output = File.Create(Globals.OUT + outZoneID + "/" + sprite.Name + ".bin")) {
                    Console.WriteLine("" + outZoneID + fileName + "Sprite->LoadAnimation(\"Sprites/" + outZoneID + "/" + sprite.Name + ".bin\");");

                    // Magic
                    output.WriteByte((byte)'S');
                    output.WriteByte((byte)'P');
                    output.WriteByte((byte)'R');
                    output.WriteByte(0);

                    // Total Frame Count
                    LittleEndian.Write4(output, (uint)sprite.Frames.Count);

                    // spriteSheetCount
                    byte spriteSheetCount = 1;
                    NeutralEndian.Write1(output, spriteSheetCount);
                    for (int i = 0; i < spriteSheetCount; i++) {
                        RSDKEndian.Write(output, outZoneID + "/" + fileName + ".gif");
                    }
                    /// for loop RSDK strings

                    // collisionBoxCount
                    NeutralEndian.Write1(output, 0);
                    /// for loop RSDK strings

                    if (sprite.Anim.Count == 0) {
                        // animationCount
                        LittleEndian.Write2(output, 1);
                        for (int a = 0; a < 1; a++) {
                            // Name
                            RSDKEndian.Write(output, sprite.Name);
                            //NeutralEndian.Write1(output, (byte)(sprite.Name.Length + 1));
                            //output.Write(Encoding.Default.GetBytes(sprite.Name), 0, sprite.Name.Length);
                            //NeutralEndian.Write1(output, 0); // zero terminate
                            // Frame Count
                            LittleEndian.Write2(output, (ushort)sprite.Frames.Count);
                            // Frame Speed
                            LittleEndian.Write2(output, 1);
                            // Frame Loop
                            NeutralEndian.Write1(output, 0);
                            // Flags
                            NeutralEndian.Write1(output, 0);

                            for (int f = 0; f < sprite.Frames.Count; f++) {
                                NeutralEndian.Write1(output, 0); // spriteSheet
                                LittleEndian.Write2(output, 4); // duration
                                LittleEndian.Write2(output, (ushort)f); // ID
                                LittleEndian.Write2(output, (ushort)sprite.Frames[f].BoxX); // X
                                LittleEndian.Write2(output, (ushort)sprite.Frames[f].BoxY); // Y
                                LittleEndian.Write2(output, sprite.Frames[f].W); // W
                                LittleEndian.Write2(output, sprite.Frames[f].H); // H
                                LittleEndian.Write2(output, (ushort)sprite.Frames[f].X); // Centering X
                                LittleEndian.Write2(output, (ushort)sprite.Frames[f].Y); // Centering Y
                            }
                        }
                    }
                    else {
                        // animationCount
                        LittleEndian.Write2(output, (ushort)sprite.Anim.Count);
                        for (int a = 0; a < sprite.Anim.Count; a++) {
                            // Name
                            RSDKEndian.Write(output, sprite.Anim[a].Name);
                            // Frame Count
                            LittleEndian.Write2(output, (ushort)sprite.Anim[a].Frames.Count);
                            // Frame Speed
                            LittleEndian.Write2(output, (ushort)sprite.Anim[a].FrameSpeed);
                            // Frame Loop
                            NeutralEndian.Write1(output, (byte)sprite.Anim[a].FrameLoop);
                            // Flags
                            NeutralEndian.Write1(output, 0);

                            Dictionary<int, int> frameLeftOffsets = new Dictionary<int, int>();
                            Dictionary<int, int> frameTopOffsets = new Dictionary<int, int>();
                            Dictionary<int, int> frameWidthOffsets = new Dictionary<int, int>();
                            Dictionary<int, int> frameHeightOffsets = new Dictionary<int, int>();
                            Dictionary<int, int> frameCenterXOffsets = new Dictionary<int, int>();
                            Dictionary<int, int> frameCenterYOffsets = new Dictionary<int, int>();
                            Dictionary<int, int> frameDurationOffsets = new Dictionary<int, int>();

                            Dictionary<string, Dictionary<int, int>> frameOffsets = new Dictionary<string, Dictionary<int, int>>();
                            frameOffsets.Add("Top", frameTopOffsets);
                            frameOffsets.Add("Left", frameLeftOffsets);
                            frameOffsets.Add("Width", frameWidthOffsets);
                            frameOffsets.Add("Height", frameHeightOffsets);
                            frameOffsets.Add("CenterX", frameCenterXOffsets);
                            frameOffsets.Add("CenterY", frameCenterYOffsets);
                            frameOffsets.Add("Duration", frameDurationOffsets);


                            foreach (FrameAlt fa in sprite.Anim[a].FrameAlterations) {
                                string prop = fa.Property;
                                string valu = fa.Value;
                                int numval = 0;
                                numval = S3toIE2Level.GetInt(valu);
                                if (frameOffsets.ContainsKey(prop))
                                    foreach (int f in fa.Frames)
                                        frameOffsets[prop][f] = numval;
                            }

                            for (int f = 0; f < sprite.Anim[a].Frames.Count; f++) {
                                Sprite wherespr = sprite;//.Anim[a].Frames[f].Spr;
                                int wherenst = sprite.Anim[a].Frames[f].Index;
                                if (wherenst < 0)
                                    wherenst = 0;

                                int left = wherespr.Frames[wherenst].BoxX;
                                int top = wherespr.Frames[wherenst].BoxY;
                                int w = wherespr.Frames[wherenst].W;
                                int h = wherespr.Frames[wherenst].H;
                                int cx = wherespr.Frames[wherenst].X;
                                int cy = wherespr.Frames[wherenst].Y;
                                int dur = sprite.Anim[a].FrameDuration;

                                if (frameLeftOffsets.ContainsKey(f))
                                    left += frameLeftOffsets[f];
                                if (frameTopOffsets.ContainsKey(f))
                                    top += frameTopOffsets[f];

                                if (frameWidthOffsets.ContainsKey(f))
                                    w = frameWidthOffsets[f];
                                if (frameHeightOffsets.ContainsKey(f))
                                    h = frameHeightOffsets[f];

                                if (frameCenterXOffsets.ContainsKey(f))
                                    cx = frameCenterXOffsets[f];
                                if (frameCenterYOffsets.ContainsKey(f))
                                    cy = frameCenterYOffsets[f];

                                if (frameDurationOffsets.ContainsKey(f))
                                    dur = frameDurationOffsets[f];

                                NeutralEndian.Write1(output, 0); // spriteSheet
                                LittleEndian.Write2(output, (ushort)dur); // duration
                                LittleEndian.Write2(output, (ushort)f); // ID
                                LittleEndian.Write2(output, (ushort)left); // X
                                LittleEndian.Write2(output, (ushort)top); // Y
                                LittleEndian.Write2(output, (ushort)w); // W
                                LittleEndian.Write2(output, (ushort)h); // H
                                LittleEndian.Write2(output, (ushort)cx); // Centering X
                                LittleEndian.Write2(output, (ushort)cy); // Centering Y
                            }
                        }
                    }
                }
            }
            
            Bitmap bitmap = new Bitmap(MaxX, MaxY, PixelFormat.Format8bppIndexed);
            // Set Palette
            int lasti = 0;
            ColorPalette cpal = bitmap.Palette;
            int[] palette = S3toIE2Level.LoadPalette(Globals.ROOT + @"General\Sprites\Sonic\Palettes\SonicAndTails.bin", paleetteLeeel);
            for (int i = 0; i < palette.Length; i++) {
                cpal.Entries[i] = Color.FromArgb(palette[i] >> 16 & 0xFF, palette[i] >> 8 & 0xFF, palette[i] & 0xFF);
                cpal.Entries[i & 0xF0] = Color.FromArgb(0, 0xFF, 0x00, 0xFF);
                lasti = i;
            }
            for (int i = lasti + 1; i < 256; i++)
                cpal.Entries[i] = Color.FromArgb(0, 0, 0, 0);
            bitmap.Palette = cpal;

            BitmapData bmpData = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height), ImageLockMode.WriteOnly, bitmap.PixelFormat);
            IntPtr bitmapPtr = bmpData.Scan0;
            byte[] px = new byte[bmpData.Stride * bitmap.Height];

            foreach (SpriteFrame spriteFrame in spriteFrames) {
                for (int sft = spriteFrame.Tiles.Count - 1; sft >= 0; sft--) {
                    SpriteFrameTile spriteFrameTile = spriteFrame.Tiles[sft];
                    for (int x = 0; x < spriteFrameTile.W; x++) {
                        for (int y = 0; y < spriteFrameTile.H; y++) {
                            int jx = spriteFrameTile.X + x * 8 - spriteFrame.X;
                            int jy = spriteFrameTile.Y + y * 8 - spriteFrame.Y;

                            int tx = x;
                            int ty = y;
                            if (spriteFrameTile.FlipX)
                                tx = spriteFrameTile.W - 1 - x;
                            if (spriteFrameTile.FlipY)
                                ty = spriteFrameTile.H - 1 - y;

                            S3toIE2Level.DrawTile(bmpData, ref px, artTiles, 
                                spriteFrame.Parent.StartingArtTile + spriteFrameTile.Tile + ty + tx * spriteFrameTile.H, 
                                jx + spriteFrame.BoxX, 
                                jy + spriteFrame.BoxY, 
                                spriteFrameTile.FlipX, spriteFrameTile.FlipY, 
                                spriteFrameTile.Pal + spriteFrame.Parent.PalStart + spriteFrame.PalOff);
                        }
                    }
                }
            }
            Marshal.Copy(px, 0, bitmapPtr, px.Length);
            bitmap.UnlockBits(bmpData);
            bitmap.Save(Globals.OUT + outZoneID + "\\" + fileName + ".gif", ImageFormat.Gif);
            bitmap.Dispose();
            Process.Start("file://" + Path.GetFullPath(Globals.OUT + outZoneID));
        }

        RSDKv5.Animation currentAnimation = null;
        int currentAnimationIndex = -1;
        int currentFrame = 0;
        string currentFilename = "";

        void New() {
            currentAnimation = new RSDKv5.Animation();

            this.Text = "Animation Editor - " + "New Animation" + ".bin";
            this.currentFilename = "";
            ClearUI();
        }

        void Open(string filename) {
            using (FileStream input = File.OpenRead(filename)) {
                using (BinaryReader reader = new BinaryReader(input)) {
                    string[] spp = filename.Split('\\');
                    currentAnimation = new RSDKv5.Animation();
                    currentAnimation.Load(reader);

                    this.Text = "Animation Editor - " + spp[spp.Length - 1];
                    this.currentFilename = filename;
                    ClearUI();
                }
            }
        }

        void SaveAs(string filename) {
            using (FileStream output = File.OpenWrite(filename)) {
                currentAnimation.Save(output);
                currentFilename = filename;

                string[] spp = filename.Split('\\');
                this.Text = "Animation Editor - " + spp[spp.Length - 1];
                this.currentFilename = filename;
            }
        }

        void Save(bool showDialog) {
            string fn = this.currentFilename;
            if (fn == "" || showDialog) {
                SaveFileDialog svd = new SaveFileDialog();
                svd.InitialDirectory = this.currentFilename;
                if (currentFilename == "")
                    svd.InitialDirectory = @"C:\Users\Justin\Dropbox\ImpostorEngine2\source\Resources\Sprites\";
                else
                    svd.InitialDirectory = Directory.GetParent(Path.GetDirectoryName(currentFilename)).FullName;
                svd.AddExtension = true;
                svd.Filter = "BIN Files (*.bin)|*.bin";
                if (svd.ShowDialog() == DialogResult.OK) {
                    fn = svd.FileName;
                }
            }
            if (fn != "") {
                SaveAs(fn);
            }
        }

        void ClearUI() {
            currentAnimationIndex = -1;

            listBoxAnimations.Items.Clear();
            for (int i = 0; i < currentAnimation.Animations.Count; i++) {
                Console.WriteLine(currentAnimation.Animations[i].AnimName.Replace(" ", "") + ",");
                listBoxAnimations.Items.Add(currentAnimation.Animations[i].AnimName);
                currentAnimationIndex = 0;
            }
            listBoxAnimations.ClearSelected();

            spriteSheets.Clear();

            if (currentFilename != "")
                Console.WriteLine(Directory.GetParent(Path.GetDirectoryName(currentFilename)).FullName);

            comboBoxTexture.Items.Clear();
            for (int i = 0; i < currentAnimation.SpriteSheets.Count; i++) {
                string yum = Directory.GetParent(Path.GetDirectoryName(currentFilename)).FullName;
                if (File.Exists(yum + "\\" + currentAnimation.SpriteSheets[i].Replace("\\", "/")))
                    spriteSheets.Add(new Bitmap(yum + "\\" + currentAnimation.SpriteSheets[i].Replace("\\", "/")));
                else if (File.Exists(currentAnimation.SpriteSheets[i].Replace("\\", "/")))
                    spriteSheets.Add(new Bitmap(currentAnimation.SpriteSheets[i].Replace("\\", "/")));
                else
                    spriteSheets.Add(new Bitmap(512, 512));

                comboBoxTexture.Items.Add(currentAnimation.SpriteSheets[i]);
                comboBoxTexture.SelectedIndex = 0;
            }

            comboBoxHitbox.Items.Clear();
            for (int i = 0; i < currentAnimation.CollisionBoxes.Count; i++) {
                comboBoxHitbox.Items.Add(currentAnimation.CollisionBoxes[i]);
                comboBoxHitbox.SelectedIndex = 0;
            }

            listViewFrames.Items.Clear();

            currentFrame = 0;

            splitContainerFrame.Enabled = false;

            panelPreview.Refresh();
        }
        void UpdateAnimationUI() {
            if (currentAnimationIndex < 0) return;

            splitContainerFrame.Enabled = true;

            RSDKv5.Animation.AnimationEntry animationEntry = currentAnimation.Animations[currentAnimationIndex];
            numericUpDownSpeed.Value = animationEntry.FrameSpeed;
            numericUpDownLoopIndex.Value = animationEntry.FrameLoop;
            comboBoxFlags.SelectedIndex = animationEntry.Unknown;
            groupBoxFrame.Text = "Current Frame: " + currentFrame + " - Total: " + animationEntry.Frames.Count;

            listViewFrames.Items.Clear();
            for (int i = 0; i < animationEntry.Frames.Count; i++) {
                listViewFrames.Items.Add(i.ToString());
            }

            for (int i = 0; i < currentAnimation.CollisionBoxes.Count; i++) {
                comboBoxHitbox.SelectedIndex = 0;
            }

            UpdateFrameUI();

            panelPreview.Refresh();
        }
        void UpdateFrameUI() {
            if (currentAnimationIndex >= 0 && currentFrame >= 0 && currentFrame < currentAnimation.Animations[currentAnimationIndex].Frames.Count) {
                RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
                numericUpDownCenterX.Value = frame.CenterX;
                numericUpDownCenterY.Value = frame.CenterY;
                numericUpDownLeft.Value = frame.X;
                numericUpDownTop.Value = frame.Y;
                numericUpDownWidth.Value = frame.Width;
                numericUpDownHeight.Value = frame.Height;
                numericUpDownID.Value = frame.ID;
                numericUpDownDuration.Value = frame.Duration;
                groupBoxFrame.Text = "Current Frame: " + currentFrame + " - Total: " + currentAnimation.Animations[currentAnimationIndex].Frames.Count;

                comboBoxHitbox_SelectedIndexChanged(null, null);

                panelPreview.Refresh();
            }
        }

        void   PutOnClipboard(Byte[] byteArr) {
            DataObject data = new DataObject();
            using (MemoryStream memStream = new MemoryStream()) {
                memStream.Write(byteArr, 0, byteArr.Length);
                data.SetData("rawbinary", false, memStream);
                Clipboard.SetDataObject(data, true);
            }
        }
        byte[] GetFromClipboard() {
            DataObject retrievedData = Clipboard.GetDataObject() as DataObject;
            if (retrievedData == null || !retrievedData.GetDataPresent("rawbinary"))
                return null;
            MemoryStream byteStream = retrievedData.GetData("rawbinary") as MemoryStream;
            if (byteStream == null)
                return null;
            return byteStream.ToArray();
        }

        private void panelPreview_Paint(object sender, PaintEventArgs e) {
            Graphics g = e.Graphics;

            if (currentAnimation.Animations.Count > 0) {
                if (spriteSheets.Count > 0) {
                    if (currentAnimationIndex >= 0) {
                        if (currentAnimation.Animations[currentAnimationIndex].Frames.Count > 0) {
                            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];

                            int w = frame.Width;
                            int h = frame.Height;
                            int x = (panelPreview.Width) / 2;
                            int y = (panelPreview.Height) / 2;

                            g.DrawLine(Pens.Black, x, y - h, x, y + h);
                            g.DrawLine(Pens.Black, x - w, y, x + w, y);

                            //g.FillRectangle(new SolidBrush(Color.FromArgb(0xFF, 0x00, 0xFF)), x, y, w, h);
                            g.DrawImage(spriteSheets[frame.SpriteSheet], x + frame.CenterX, y + frame.CenterY, new Rectangle(frame.X, frame.Y, w, h), GraphicsUnit.Pixel);
                        }
                    }
                }
            }

            listViewFrames.Refresh();

            return;
            if (Image != null && sprite != null) {
                int xxx = 0;
                int yyy = 0;
                int f = 0;
                foreach (SpriteFrame spriteFrame in sprite.Frames) {
                    g.FillRectangle(new SolidBrush(Color.FromArgb(0xFF, 0x00, 0xFF)), xxx + 2, yyy + 2, spriteFrame.W, spriteFrame.H);

                    for (int sft = spriteFrame.Tiles.Count - 1; sft >= 0; sft--) {
                        SpriteFrameTile spriteFrameTile = spriteFrame.Tiles[sft];
                        for (int x = 0; x < spriteFrameTile.W; x++) {
                            for (int y = 0; y < spriteFrameTile.H; y++) {
                                int jx = spriteFrameTile.X + x * 8 + 4 - spriteFrame.X;
                                int jy = spriteFrameTile.Y + y * 8 + 4 - spriteFrame.Y;

                                int tx = x;
                                int ty = y;
                                if (spriteFrameTile.FlipX)
                                    tx = spriteFrameTile.W - 1 - x;
                                if (spriteFrameTile.FlipY)
                                    ty = spriteFrameTile.H - 1 - y;

                                g.TranslateTransform(jx + xxx + 2, jy + yyy + 2);
                                g.ScaleTransform(spriteFrameTile.FlipX ? -1 : 1, spriteFrameTile.FlipY ? -1 : 1);
                                g.DrawImage(Image, -4, -4, new Rectangle(((spriteFrameTile.Pal + 2) & 3) * 8, (sprite.StartingArtTile + spriteFrameTile.Tile + ty + tx * spriteFrameTile.H) << 3, 8, 8), GraphicsUnit.Pixel);
                                g.ResetTransform();
                                
                            }
                        }
                    }
                    xxx += spriteFrame.W + 1;
                    f++;
                }
            }
        }

        private void listBoxAnimations_DrawItem(object sender, DrawItemEventArgs e) {
            bool isSelected = ((e.State & DrawItemState.Selected) == DrawItemState.Selected);

            if (e.Index > -1) {
                Color color = isSelected ? SystemColors.Highlight : listBoxAnimations.BackColor;

                // Background item brush
                SolidBrush backgroundBrush = new SolidBrush(color);
                SolidBrush textBrush = new SolidBrush(e.ForeColor);

                RectangleF rectF = new RectangleF(e.Bounds.X + 2, e.Bounds.Y + 2, e.Bounds.Width, e.Bounds.Height);

                // Draw the background
                e.Graphics.FillRectangle(backgroundBrush, e.Bounds);
                e.Graphics.DrawString(listBoxAnimations.GetItemText(listBoxAnimations.Items[e.Index]), e.Font, textBrush, rectF, StringFormat.GenericDefault);

                // Clean up
                backgroundBrush.Dispose();
                textBrush.Dispose();
            }
            e.DrawFocusRectangle();
        }

        private void listBoxAnimations_SelectedIndexChanged(object sender, EventArgs e) {
            listViewFrames.SelectedIndices.Clear();

            currentFrame = 0;
            currentAnimationIndex = listBoxAnimations.SelectedIndex;
            Console.WriteLine("Current Animation Index: " + currentAnimationIndex);

            UpdateAnimationUI();

            panelPreview.Refresh();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e) {
            New();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e) {
            OpenFileDialog svd = new OpenFileDialog();
            if (currentFilename == "")
                svd.InitialDirectory = @"C:\Users\Justin\Dropbox\ImpostorEngine2\source\Resources\Sprites\";
            else
                svd.InitialDirectory = Directory.GetParent(Path.GetDirectoryName(currentFilename)).FullName;
            svd.AddExtension = true;
            svd.Filter = "BIN Files (*.bin)|*.bin";
            if (svd.ShowDialog() == DialogResult.OK) {
                Open(svd.FileName);
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e) {
            Save(false);
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e) {
            Save(true);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e) {
            Application.Exit();
        }

        private void Form1_ResizeEnd(object sender, EventArgs e) {
            panelPreview.Refresh();
        }

        private void Form1_Resize(object sender, EventArgs e) {
            panelPreview.Refresh();
        }

        private void numericUpDownSpeed_ValueChanged(object sender, EventArgs e) {
            RSDKv5.Animation.AnimationEntry animationEntry = currentAnimation.Animations[currentAnimationIndex];
            animationEntry.FrameSpeed = (int)numericUpDownSpeed.Value;
        }

        private void numericUpDownLoopIndex_ValueChanged(object sender, EventArgs e) {
            RSDKv5.Animation.AnimationEntry animationEntry = currentAnimation.Animations[currentAnimationIndex];
            animationEntry.FrameLoop = (int)numericUpDownLoopIndex.Value;
        }

        private void comboBoxFlags_SelectedIndexChanged(object sender, EventArgs e) {
            RSDKv5.Animation.AnimationEntry animationEntry = currentAnimation.Animations[currentAnimationIndex];
            animationEntry.Unknown = (byte)comboBoxFlags.SelectedIndex;
        }

        private void numericUpDownLeft_ValueChanged(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.X = (int)numericUpDownLeft.Value;
            panelPreview.Refresh();
        }

        private void numericUpDownTop_ValueChanged(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.Y = (int)numericUpDownTop.Value;
            panelPreview.Refresh();
        }

        private void numericUpDownWidth_ValueChanged(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.Width = (int)numericUpDownWidth.Value;
            panelPreview.Refresh();
        }

        private void numericUpDownHeight_ValueChanged(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.Height = (int)numericUpDownHeight.Value;
            panelPreview.Refresh();
        }

        private void numericUpDownCenterX_ValueChanged(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.CenterX = (int)numericUpDownCenterX.Value;
            panelPreview.Refresh();
        }

        private void numericUpDownCenterY_ValueChanged(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.CenterY = (int)numericUpDownCenterY.Value;
            panelPreview.Refresh();
        }

        private void numericUpDownID_ValueChanged(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.ID = (int)numericUpDownID.Value;
            panelPreview.Refresh();
        }

        private void numericUpDownDuration_ValueChanged(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.Duration = (int)numericUpDownDuration.Value;
            panelPreview.Refresh();
        }

        private void listView1_DrawItem(object sender, DrawListViewItemEventArgs e) {
            Graphics g = e.Graphics;

            g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.None;
            g.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.Half;


            if (currentAnimation.Animations.Count > 0) {
                if (spriteSheets.Count > 0) {
                    if (currentAnimationIndex >= 0) {
                        if (currentAnimation.Animations[currentAnimationIndex].Frames.Count > 0) {
                            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[e.ItemIndex];

                            g.FillRectangle(new SolidBrush(Color.FromArgb(0xFF, 0x00, 0xFF)), e.Bounds);

                            int w = frame.Width;
                            int h = frame.Height;

                            if (w > 0 && h > 0) {
                                int x = e.Bounds.X;
                                int y = e.Bounds.Y;
                                int sw = w;
                                int sh = h;

                                if (w > h) {
                                    sw = e.Bounds.Width;
                                    sh = h * e.Bounds.Width / w;
                                }
                                else {
                                    sw = w * e.Bounds.Height / h;
                                    sh = e.Bounds.Height;
                                }

                                x += (e.Bounds.Width - sw) / 2;
                                y += (e.Bounds.Height - sh) / 2;

                                g.DrawImage(spriteSheets[frame.SpriteSheet], new Rectangle(x, y, sw, sh), frame.X, frame.Y, w, h, GraphicsUnit.Pixel);
                            }
                        }
                    }
                }
            }

            Color c = Color.FromArgb(0x80, new Pen(SystemBrushes.Highlight).Color);
            if ((e.State & ListViewItemStates.Selected) != 0)
                g.FillRectangle(new SolidBrush(c), e.Bounds);
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e) {
            if (listViewFrames.SelectedIndices.Count == 0) return;
            if (listViewFrames.SelectedIndices[0] < 0) return;

            currentFrame = listViewFrames.SelectedIndices[0];

            UpdateFrameUI();
        }

        private void toolStripButtonAnimationAdd_Click(object sender, EventArgs e) {
            RSDKv5.Animation.AnimationEntry animation = new RSDKv5.Animation.AnimationEntry("New Animation");
            currentAnimation.Animations.Add(animation);

            currentAnimationIndex = currentAnimation.Animations.Count - 1;
            ClearUI();
        }

        private void toolStripButtonAnimationDelete_Click(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count > 0) {
                if (spriteSheets.Count > 0) {
                    if (currentAnimationIndex >= 0) {
                        currentAnimation.Animations.RemoveAt(currentAnimationIndex);
                        listBoxAnimations.Items.RemoveAt(currentAnimationIndex);
                        currentAnimationIndex = -1;
                        listBoxAnimations.ClearSelected();
                        UpdateAnimationUI();
                    }
                }
            }
        }

        private void toolStripButtonAnimationDuplicate_Click(object sender, EventArgs e) {

        }

        private void toolStripButtonAnimationCopy_Click(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count > 0) {
                if (spriteSheets.Count > 0) {
                    if (currentAnimationIndex >= 0) {
                        RSDKv5.Animation.AnimationEntry anim = currentAnimation.Animations[currentAnimationIndex];
                        using (MemoryStream output = new MemoryStream()) {
                            output.Write(BitConverter.GetBytes(0x494E41), 0, 4);
                            anim.Write(output, currentAnimation);
                            PutOnClipboard(output.ToArray());
                        }
                    }
                }
            }
        }

        private void toolStripButtonAnimationPaste_Click(object sender, EventArgs e) {
            using (MemoryStream input = new MemoryStream(GetFromClipboard())) {
                if (LittleEndian.ReadUInt32(input) == 0x494E41) {
                    RSDKv5.Animation.AnimationEntry anim = new RSDKv5.Animation.AnimationEntry(new BinaryReader(input), currentAnimation);
                    int count = 1;
                    foreach (RSDKv5.Animation.AnimationEntry an in currentAnimation.Animations) {
                        if (an.AnimName.Substring(0, anim.AnimName.Length < an.AnimName.Length ? anim.AnimName.Length : an.AnimName.Length) == anim.AnimName)
                            count++;
                    }
                    if (count > 1)
                        anim.AnimName += " (" + count + ")";
                    currentAnimation.Animations.Add(anim);
                    listBoxAnimations.Items.Add(anim.AnimName);
                }
            }
            
            UpdateAnimationUI();
        }

        private void hitboxEditorToolStripMenuItem_Click(object sender, EventArgs e) {
            HitboxEditor hitboxEditor = new HitboxEditor();

            for (int i = 0; i < currentAnimation.CollisionBoxes.Count; i++) {
                hitboxEditor.listBoxHitboxes.Items.Add(currentAnimation.CollisionBoxes[i]);
            }

            if (hitboxEditor.ShowDialog() == DialogResult.OK) {
                if (comboBoxHitbox.Items.Count > 0)
                    comboBoxHitbox.SelectedIndex = 0;

                comboBoxHitbox.Items.Clear();
                currentAnimation.CollisionBoxes.Clear();
                for (int i = 0; i < hitboxEditor.listBoxHitboxes.Items.Count; i++) {
                    currentAnimation.CollisionBoxes.Add((string)hitboxEditor.listBoxHitboxes.Items[i]);
                    comboBoxHitbox.Items.Add(currentAnimation.CollisionBoxes[i]);
                    comboBoxHitbox.SelectedIndex = 0;
                }
            }
        }

        private void numericUpDownHitboxLeft_ValueChanged(object sender, EventArgs e) {
            if (comboBoxHitbox.SelectedText == "") return;
            if (comboBoxHitbox.SelectedIndex < 0) return;
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.HitBoxes[comboBoxHitbox.SelectedIndex].Left = (int)numericUpDownHitboxLeft.Value;
            panelPreview.Refresh();
        }

        private void numericUpDownHitboxTop_ValueChanged(object sender, EventArgs e) {
            if (comboBoxHitbox.SelectedText == "") return;
            if (comboBoxHitbox.SelectedIndex < 0) return;
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.HitBoxes[comboBoxHitbox.SelectedIndex].Top = (int)numericUpDownHitboxTop.Value;
            panelPreview.Refresh();
        }

        private void numericUpDownHitboxRight_ValueChanged(object sender, EventArgs e) {
            if (comboBoxHitbox.SelectedText == "") return;
            if (comboBoxHitbox.SelectedIndex < 0) return;
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.HitBoxes[comboBoxHitbox.SelectedIndex].Right = (int)numericUpDownHitboxRight.Value;
            panelPreview.Refresh();
        }

        private void numericUpDownHitboxBottom_ValueChanged(object sender, EventArgs e) {
            if (comboBoxHitbox.SelectedText == "") return;
            if (comboBoxHitbox.SelectedIndex < 0) return;
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];
            frame.HitBoxes[comboBoxHitbox.SelectedIndex].Bottom = (int)numericUpDownHitboxBottom.Value;
            panelPreview.Refresh();
        }

        private void comboBoxHitbox_SelectedIndexChanged(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count == 0) return;
            if (currentAnimation.Animations[currentAnimationIndex].Frames.Count == 0) return;
            RSDKv5.Animation.Frame frame = currentAnimation.Animations[currentAnimationIndex].Frames[currentFrame];

            if (frame.HitBoxes.Count == 0) {
                numericUpDownHitboxLeft.Enabled = numericUpDownHitboxRight.Enabled = numericUpDownHitboxTop.Enabled = numericUpDownHitboxBottom.Enabled = false;
                numericUpDownHitboxLeft.Value = numericUpDownHitboxRight.Value = numericUpDownHitboxTop.Value = numericUpDownHitboxBottom.Value = 0;
            }
            else {
                numericUpDownHitboxLeft.Enabled = numericUpDownHitboxRight.Enabled = numericUpDownHitboxTop.Enabled = numericUpDownHitboxBottom.Enabled = true;

                numericUpDownHitboxTop.Value = frame.HitBoxes[comboBoxHitbox.SelectedIndex].Top;
                numericUpDownHitboxLeft.Value = frame.HitBoxes[comboBoxHitbox.SelectedIndex].Left;
                numericUpDownHitboxRight.Value = frame.HitBoxes[comboBoxHitbox.SelectedIndex].Right;
                numericUpDownHitboxBottom.Value = frame.HitBoxes[comboBoxHitbox.SelectedIndex].Bottom;
            }
        }

        private void listBoxAnimations_DoubleClick(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count > 0) {
                if (spriteSheets.Count > 0) {
                    if (currentAnimationIndex >= 0) {
                        RSDKv5.Animation.AnimationEntry anim = currentAnimation.Animations[currentAnimationIndex];
                        PromptDialog prompt = new PromptDialog("New name for \"" + anim.AnimName + "\"?", anim.AnimName);
                        if (prompt.ShowDialog() == DialogResult.OK) {
                            anim.AnimName = prompt.TextEntry.Text;
                            listBoxAnimations.Items[currentAnimationIndex] = anim.AnimName;
                        }
                    }
                }
            }
        }

        private void toolStripButtonFrameAdd_Click(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count > 0) {
                if (spriteSheets.Count > 0) {
                    if (currentAnimationIndex >= 0) {
                        RSDKv5.Animation.AnimationEntry anim = currentAnimation.Animations[currentAnimationIndex];
                        RSDKv5.Animation.Frame f = new RSDKv5.Animation.Frame();
                        f.Width = 32;
                        f.Height = 32;
                        for (int i = 0; i < currentAnimation.CollisionBoxes.Count; ++i) {
                            var hitBox = new RSDKv5.Animation.Frame.HitBox();
                            hitBox.Left = 0;
                            hitBox.Top = 0;
                            hitBox.Right = 0;
                            hitBox.Bottom = 0;
                            f.HitBoxes.Add(hitBox);
                        }
                        anim.Frames.Add(f);
                        listViewFrames.Items.Add("");
                    }
                }
            }
        }

        private void toolStripButtonFrameDelete_Click(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count > 0) {
                if (spriteSheets.Count > 0) {
                    if (currentAnimationIndex >= 0) {
                        if (listViewFrames.SelectedIndices.Count >= 0) {
                            RSDKv5.Animation.AnimationEntry anim = currentAnimation.Animations[currentAnimationIndex];
                            
                            for (int i = anim.Frames.Count - 1; i >= 0; i--) {
                                if (listViewFrames.SelectedIndices.Contains(i)) {
                                    anim.Frames.RemoveAt(i);
                                    listViewFrames.Items.RemoveAt(i);
                                }
                            }
                        }
                    }
                }
            }
        }

        private void toolStripButtonFrameDuplicate_Click(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count > 0) {
                if (spriteSheets.Count > 0) {
                    if (currentAnimationIndex >= 0) {
                        if (listViewFrames.SelectedIndices.Count >= 0) {
                            RSDKv5.Animation.AnimationEntry anim = currentAnimation.Animations[currentAnimationIndex];
                            using (MemoryStream output = new MemoryStream()) {
                                int whereEnd = anim.Frames.Count;
                                for (int i = 0; i < anim.Frames.Count; i++) {
                                    if (listViewFrames.SelectedIndices.Contains(i)) {
                                        anim.Frames.Insert(i + 1, anim.Frames[i].Clone());
                                        listViewFrames.Items.Add("");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void toolStripButtonFrameLeft_Click(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count <= 0) return;
            if (spriteSheets.Count <= 0) return;
            if (currentAnimationIndex < 0) return;

            if (listViewFrames.SelectedIndices.Count >= 0) {
                if (listViewFrames.SelectedIndices.Contains(0)) return;

                RSDKv5.Animation.AnimationEntry anim = currentAnimation.Animations[currentAnimationIndex];

                List<int> guys = new List<int>();
                for (int i = 0; i < anim.Frames.Count; i++) {
                    if (listViewFrames.SelectedIndices.Contains(i)) {
                        RSDKv5.Animation.Frame f = anim.Frames[i];
                        anim.Frames.RemoveAt(i);
                        anim.Frames.Insert(i - 1, f);
                        guys.Add(i - 1);
                    }
                }
                
                listViewFrames.SelectedItems.Clear();
                listViewFrames.SelectedIndices.Clear();
                foreach (int g in guys) {
                    listViewFrames.SelectedIndices.Add(g);
                }

                currentFrame--;
                if (currentFrame < 0)
                    currentFrame = 0;

                listViewFrames.Refresh();
            }
        }

        private void toolStripButtonFrameRight_Click(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count <= 0) return;
            if (spriteSheets.Count <= 0) return;
            if (currentAnimationIndex < 0) return;

            RSDKv5.Animation.AnimationEntry anim = currentAnimation.Animations[currentAnimationIndex];

            if (listViewFrames.SelectedIndices.Count >= 0) {
                if (listViewFrames.SelectedIndices.Contains(anim.Frames.Count - 1)) return;

                List<int> guys = new List<int>();
                for (int i = anim.Frames.Count - 1; i >= 0; i--) {
                    if (listViewFrames.SelectedIndices.Contains(i)) {
                        RSDKv5.Animation.Frame f = anim.Frames[i];
                        anim.Frames.RemoveAt(i);
                        anim.Frames.Insert(i + 1, f);
                        guys.Add(i + 1);
                    }
                }

                listViewFrames.SelectedItems.Clear();
                listViewFrames.SelectedIndices.Clear();
                foreach (int g in guys) {
                    listViewFrames.SelectedIndices.Add(g);
                }

                currentFrame++;
                if (currentFrame > anim.Frames.Count - 1)
                    currentFrame = anim.Frames.Count - 1;

                listViewFrames.Refresh();
            }
        }

        private void toolStripButtonFrameCopy_Click(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count > 0) {
                if (spriteSheets.Count > 0) {
                    if (currentAnimationIndex >= 0) {
                        if (listViewFrames.SelectedIndices.Count >= 0) {
                            RSDKv5.Animation.AnimationEntry anim = currentAnimation.Animations[currentAnimationIndex];
                            using (MemoryStream output = new MemoryStream()) {
                                for (int i = 0; i < anim.Frames.Count; i++) {
                                    if (listViewFrames.SelectedIndices.Contains(i)) {
                                        output.Write(BitConverter.GetBytes(0x69696969), 0, 4);
                                        RSDKv5.Animation.Frame.WriteFrame(output, currentAnimation, anim, i);
                                    }
                                }
                                output.Write(BitConverter.GetBytes(0xFFFFFFFF), 0, 4);
                                PutOnClipboard(output.ToArray());
                            }
                        }
                    }
                }
            }
        }

        private void toolStripButtonFramePaste_Click(object sender, EventArgs e) {
            if (currentAnimation.Animations.Count > 0) {
                if (spriteSheets.Count > 0) {
                    if (currentAnimationIndex >= 0) {
                        using (MemoryStream input = new MemoryStream(GetFromClipboard())) {
                            while (LittleEndian.ReadUInt32(input) == 0x69696969) {
                                RSDKv5.Animation.AnimationEntry anim = currentAnimation.Animations[currentAnimationIndex];
                                anim.Frames.Add(RSDKv5.Animation.Frame.ReadFrame(new BinaryReader(input), currentAnimation));
                                listViewFrames.Items.Add("");
                            }
                        }
                    }
                }
            }
        }

        private void spritesheetListEditorToolStripMenuItem_Click(object sender, EventArgs e) {
            SpritesheetList hitboxEditor = new SpritesheetList();

            for (int i = 0; i < currentAnimation.SpriteSheets.Count; i++) {
                hitboxEditor.listBoxSpritesheetFilenames.Items.Add(currentAnimation.SpriteSheets[i]);
            }

            if (hitboxEditor.ShowDialog() == DialogResult.OK) {
                if (comboBoxTexture.Items.Count > 0)
                    comboBoxTexture.SelectedIndex = 0;

                for (int i = 0; i < spriteSheets.Count; i++) {
                    spriteSheets[i].Dispose();
                }
                spriteSheets.Clear();


                comboBoxTexture.Items.Clear();
                currentAnimation.SpriteSheets.Clear();
                for (int i = 0; i < hitboxEditor.listBoxSpritesheetFilenames.Items.Count; i++) {
                    currentAnimation.SpriteSheets.Add((string)hitboxEditor.listBoxSpritesheetFilenames.Items[i]);
                    comboBoxTexture.Items.Add(currentAnimation.SpriteSheets[i]);
                    comboBoxTexture.SelectedIndex = 0;

                    spriteSheets.Add(new Bitmap(currentAnimation.SpriteSheets[i]));
                }
            }
        }
        
        private void listViewFrames_KeyDown(object sender, KeyEventArgs e) {
            if (e.KeyCode == Keys.Left) {
                toolStripButtonFrameLeft_Click(null, null);
            }
            else if (e.KeyCode == Keys.Right) {
                toolStripButtonFrameRight_Click(null, null);
            }
        }
    }
}
