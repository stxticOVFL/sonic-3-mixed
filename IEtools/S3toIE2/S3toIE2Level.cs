using SonicRetro.KensSharp;
using SonicRetro.SonLVL.API;
using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.Globalization;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;
using zlib;
using IniDictionary = System.Collections.Generic.Dictionary<string, System.Collections.Generic.Dictionary<string, string>>;
using IniGroup = System.Collections.Generic.Dictionary<string, string>;
using IniNameGroup = System.Collections.Generic.KeyValuePair<string, System.Collections.Generic.Dictionary<string, string>>;
using IniNameValue = System.Collections.Generic.KeyValuePair<string, string>;

namespace S3toIE2 {
    public class S3toIE2Level {

        //Aurum = 0
        //Frizz = 1
        //Ducky = 2
        static int User = 2;

        public static int ParseInt(string str) {
            // if (str == "") return 0;

            int t;
            int num = 1;
            if (str[0] == '-') {
                num = -1;
                str = str.Substring(1);
            }
            
            if (str.StartsWith("0x"))
                num *= int.Parse(str.Substring(2), NumberStyles.HexNumber);
            else if (int.TryParse(str, out t))
                num *= int.Parse(str, NumberStyles.Integer, NumberFormatInfo.InvariantInfo);
            return num;
        }

        public class FileInfo {
            public string Filename;
            public int Offset;

            public FileInfo(string data) {
                string[] split = data.Split(':');
                Filename = split[0];

                Filename = Filename.Substring(3).Replace("/", @"\");

                Offset = -1;
                if (split.Length > 1) {
                    string offstr = split[1];
                    if (offstr.StartsWith("0x"))
                        Offset = int.Parse(offstr.Substring(2), NumberStyles.HexNumber);
                    else if (int.TryParse(offstr, out Offset))
                        Offset = int.Parse(offstr, NumberStyles.Integer, NumberFormatInfo.InvariantInfo);
                }
            }

            public static FileInfo[] Load(string all) {
                string[] fileStrings = all.Split('|');
                FileInfo[] files = new FileInfo[fileStrings.Length];

                int i = 0;
                foreach (string file in fileStrings) {
                    files[i] = new FileInfo(file);
                    i++;
                }

                return files;
            }
        }
        public class AnimatedTiles {
            public int ID = 0;
            public int Count = 0;
            public int AnimTileID = 0;
            public int Frames = 0;
            public int FrameLength = 0;
            public bool OnlyVisual = false;

            public AnimatedTiles(int id, int count, int animTileID, int frames, bool onlyVisual) {
                ID = id;
                Count = count;
                AnimTileID = animTileID;
                Frames = frames;
                FrameLength = 0;
                OnlyVisual = onlyVisual;
            }
        }
        
        public class AniPLC {
            public int GlobalDuration;
            public int SourceAddr;
            public int ID;
            public int FrameCount;
            public int FrameTileCount;
            public List<AniPLCFrame> Frames = new List<AniPLCFrame>();

            public class AniPLCFrame {
                public int Offset;
                public int Duration;
            }
        }

        public static int GetInt(string offstr) {
            int fj;
            if (offstr.StartsWith("0x"))
                fj = int.Parse(offstr.Substring(2), NumberStyles.HexNumber);
            else
                fj = int.Parse(offstr, NumberStyles.Integer, NumberFormatInfo.InvariantInfo);
            return fj;
        }

        public static Bitmap help = null;

        public static bool DOTILEDCONVERT = false;

        static string[] lvlIDs = new string[] {
            "AIZ",
            "HCZ",
            "MGZ",
            "CNZ",
            "ICZ",
            "LBZ",

            "MHZ",
            "FBZ",
            "SOZ",
            "LRZ",
            "HPZ",
            "SSZ",
            "DEZ",
            "DDZ",
        };
        static string[] lvlNames = new string[] {
            "Angel Island",
            "Hydrocity",
            "Marble Garden",
            "Carnival Night",
            "Icecap",
            "Launch Base",

            "Mushroom Hill",
            "Flying Battery",
            "Sandopolis",
            "Lava Reef",
            "Hidden Palace",
            "Sky Sanctuary",
            "Death Egg",
            "The Doomsday",
        };

        public static Dictionary<string, ObjectData> INIObjDefs;

        public static List<string> S3Objects = new List<string>();
        public static List<string> SKObjects = new List<string>();

        public static void Init() {
            if (File.Exists(Path.Combine("Object List", "List.txt"))) {
                int id = 0;
                string[] lines = File.ReadAllLines(Path.Combine("Object List", "List.txt"));
                foreach (string line in lines) {
                    string name = line.Split(',')[1];
                    if (id < 0x100)
                        S3Objects.Add(name);
                    else
                        SKObjects.Add(name);
                    id++;
                }
            }
        }

        public static void ConvertTiledToIE2(string tmxFilename) {
            /*XmlDocument doc = new XmlDocument();
            doc.Load(tmxFilename);

            string filePath = Path.Combine(Path.GetDirectoryName(tmxFilename), "IE2 Conversion");
            if (!Directory.Exists(filePath))
                Directory.CreateDirectory(filePath);

            filePath = Path.Combine(filePath, "SceneNEW.bin");
            
            using (FileStream fileStream = new FileStream(filePath, FileMode.OpenOrCreate)) {
                RSDKv5.Scene scene = new RSDKv5.Scene();
                scene.ImpostorScene2 = true;
                scene.MAGIC = new byte[] { (byte)'I', (byte)'S', (byte)'C', (byte)'N' };
                if (doc.DocumentElement.ChildNodes[0].Name != "properties")
                    throw new Exception("First node in .tmx file must be a <properties>!");

                Console.WriteLine("Converting metadata...");
                // Metadata
                foreach (XmlNode node in doc.DocumentElement.ChildNodes[0].ChildNodes) {
                    if (node.Name != "property")
                        throw new Exception("Invalid property <" + node.Name + "> in .tmx file!");

                    string text = node.Attributes["name"]?.InnerText;
                    string value = node.Attributes["value"]?.InnerText;
                    switch (text) {
                        case "Level Title":
                            scene.Metadata.LevelTitle = value;
                            break;
                        case "Zone ID":
                            scene.Metadata.ZoneID = (byte)Convert.ToInt32(value);
                            break;
                        case "Act":
                            scene.Metadata.Act = (byte)Convert.ToInt32(value);
                            break;
                        case "Visible HUD":
                            scene.Metadata.VisibleHUD = Convert.ToBoolean(value);
                            break;
                        case "Song File":
                            scene.Metadata.SongFile = value;
                            break;
                        case "Song Loop Point (Samples)":
                            scene.Metadata.LoopPoint = Convert.ToUInt32(value);
                            break;
                    }
                }

                Console.WriteLine("Converting layers...");
                // Layers and their ScrollingInfo
                int index = -1;
                foreach (XmlNode node in doc.DocumentElement.ChildNodes) {
                    ++index;
                    //if (node.Name != "layer")
                    //continue;
                    if (node.Name != "objectgroup")
                        continue;
                    if (node.Attributes["name"]?.InnerText == "Scrolling Info Layer")
                        continue;
                    if (node.Attributes["name"]?.InnerText == "Objects")
                        continue;

                    int width = 0; // Convert.ToInt32(node.Attributes["width"]?.InnerText);
                    int height = 0; //Convert.ToInt32(node.Attributes["height"]?.InnerText);
                    string name = node.Attributes["name"]?.InnerText;
                    
                    int relativeY = 0;
                    int constantY = 0;
                    int flags = 0;
                    bool infiniteVScoll = false;
                    foreach (XmlNode nodeProp in node.ChildNodes[0].ChildNodes) {
                        if (nodeProp.Name != "property")
                            throw new Exception("Invalid property <" + nodeProp.Name + "> in .tmx file!");

                        string text = nodeProp.Attributes["name"]?.InnerText;
                        string value = nodeProp.Attributes["value"]?.InnerText;
                        switch (text) {
                            case "Relative Y":
                                relativeY = Convert.ToInt32(value);
                                break;
                            case "Constant Y":
                                constantY = Convert.ToInt32(value);
                                break;
                            case "Flags":
                                flags = Convert.ToInt32(value);
                                break;
                            case "Infinitely Vertical":
                                infiniteVScoll = Convert.ToBoolean(value);
                                break;
                            case "Width":
                                width = Convert.ToInt32(value);
                                break;
                            case "Height":
                                height = Convert.ToInt32(value);
                                break;
                        }
                    }

                    RSDKv5.SceneLayer layer = new RSDKv5.SceneLayer(name, (ushort)width, (ushort)height);
                    layer.Behaviour = (byte)(infiniteVScoll ? 1 : 0);
                    layer.RelativeY = (ushort)relativeY;
                    layer.ConstantY = (ushort)constantY;
                    layer.DrawingOrder = (byte)flags;

                    // Tiles (In Chunks)
                    /*
                    foreach (XmlNode nodeChunk in node.ChildNodes[1].ChildNodes) {
                        if (nodeChunk.Name != "chunk")
                            throw new Exception("Invalid chunk <" + nodeChunk.Name + "> in .tmx file!");

                        int x = Convert.ToInt32(nodeChunk.Attributes["x"].InnerText);
                        int y = Convert.ToInt32(nodeChunk.Attributes["y"].InnerText);
                        int w = Convert.ToInt32(nodeChunk.Attributes["width"].InnerText);
                        int h = Convert.ToInt32(nodeChunk.Attributes["height"].InnerText);

                        string base64data = nodeChunk.InnerText;
                        byte[] chunkData = Convert.FromBase64String(base64data);
                        
                        for (int rx = 0; rx < w && x + rx < width; rx++) {
                            for (int ry = 0; ry < h && y + ry < height; ry++) {
                                uint tile = BitConverter.ToUInt32(chunkData, (rx + ry * w) * 4);

                                uint word = (tile & 0x3FF) - 1;
                                if ((tile & 0x80000000U) != 0)
                                    word |= 1 << 10;
                                if ((tile & 0x40000000U) != 0)
                                    word |= 1 << 11;
                                word |= 0x2 << 14; // Set Top-only solidity since we can't edit this in Tiled yet
                                word |= 0x2 << 12;
                                layer.Tiles[y + ry][x + rx] = (ushort)word;
                            }
                        }
                    }
                    //
            // Tiles (As Objects)
            foreach (XmlNode nodeTile in node.ChildNodes) {
                        if (node.Name != "object")
                            continue;
                        
                        int x = Convert.ToInt32(nodeTile.Attributes["x"]?.InnerText) >> 4;
                        int y = Convert.ToInt32(nodeTile.Attributes["y"]?.InnerText) >> 4;
                        y -= 1;
                        uint tileID = Convert.ToUInt32(nodeTile.Attributes["gid"]?.InnerText) & 0x3FF;
                        bool flipX = (Convert.ToUInt32(nodeTile.Attributes["gid"]?.InnerText) & 0x80000000) != 0;
                        bool flipY = (Convert.ToUInt32(nodeTile.Attributes["gid"]?.InnerText) & 0x40000000) != 0;
                        int solidityA = 0;
                        int solidityB = 0;

                        if (nodeTile.FirstChild?.Name == "properties" && nodeTile.FirstChild?.HasChildNodes == true) {
                            foreach (XmlNode nodeProp in nodeTile.FirstChild.ChildNodes) {
                                switch (nodeProp.Attributes["name"]?.InnerText) {
                                    case "Solidity A":
                                        solidityA = Convert.ToInt32(nodeProp.Attributes["value"]?.InnerText);
                                        break;
                                    case "Solidity B":
                                        solidityB = Convert.ToInt32(nodeProp.Attributes["value"]?.InnerText);
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                        
                        uint word = (tileID & 0x3FF) - 1;
                        if (flipX)
                            word |= 1 << 10;
                        if (flipY)
                            word |= 1 << 11;
                        word |= (uint)(solidityA & 3) << 14;
                        word |= (uint)(solidityB & 3) << 12;
                        layer.Tiles[y][x] = (ushort)word;
                    }

                    layer.ResetParallax();
                    // Parallaxes
                    if (doc.DocumentElement.ChildNodes[index + 1] != null) {
                        foreach (XmlNode nodeParallaxObj in doc.DocumentElement.ChildNodes[index + 1].ChildNodes) {
                            int prelatx = 0x100;
                            int pconstx = 0;
                            int pflag = 0;
                            bool deform = false;
                            //int y = Convert.ToInt32(nodeParallaxObj.Attributes["y"]?.InnerText);
                            int h = Convert.ToInt32(nodeParallaxObj.Attributes["height"]?.InnerText);
                            // these need to be added to a list and sorted by Y instead of this
                            foreach (XmlNode nodeProp in nodeParallaxObj.FirstChild.ChildNodes) {
                                if (nodeProp.Name != "property")
                                    throw new Exception("Invalid property <" + nodeProp.Name + "> in .tmx file!");

                                string text = nodeProp.Attributes["name"]?.InnerText;
                                string value = nodeProp.Attributes["value"]?.InnerText;
                                switch (text) {
                                    case "Relative X":
                                        prelatx = Convert.ToInt32(value);
                                        break;
                                    case "Constant X":
                                        pconstx = Convert.ToInt32(value);
                                        break;
                                    case "Flags":
                                        pflag = Convert.ToInt32(value);
                                        break;
                                    case "Deform":
                                        deform = Convert.ToBoolean(value);
                                        break;
                                }
                            }
                            layer.AddParallax(h, prelatx, pconstx, pflag, deform);
                        }
                    }

                    scene.Layers.Add(layer);
                }

                Console.WriteLine("Converting objects...");
                // Object Definitions
                Dictionary<string, int> ObjectNameToDefIndex = new Dictionary<string, int>();
                foreach (XmlNode node in doc.DocumentElement.ChildNodes) {
                    if (node.Name != "tileset")
                        continue;
                    if (node.Attributes["source"]?.InnerText == "Tileset.tsx")
                        continue;

                    string objectName = node.Attributes["source"]?.InnerText;
                    objectName = objectName.Substring(0, objectName.IndexOf('.'));

                    ObjectNameToDefIndex[objectName] = scene.ObjectDefinitions.Count;

                    RSDKv5.Scene.ISCN_ObjectDefinition objDef = new RSDKv5.Scene.ISCN_ObjectDefinition();
                    objDef.ObjectName = objectName;
                    objDef.ObjectHash = Globals.Crc32(objectName);
                    objDef.AttributeCount = 0;
                    scene.ObjectDefinitions.Add(objDef);
                    // Console.WriteLine(objDef.ObjectName + ": 0x" + objDef.ObjectHash.ToString("X"));
                }
                // Individual Object Definitions
                foreach (XmlNode node in doc.DocumentElement.ChildNodes) {
                    if (node.Name != "objectgroup")
                        continue;
                    if (node.Attributes["name"]?.InnerText != "Objects")
                        continue;

                    foreach (XmlNode nodeObj in node.ChildNodes) {
                        string objectName = nodeObj.Attributes["template"]?.InnerText;
                        if (objectName == null) continue;
                        objectName = objectName.Substring(0, objectName.IndexOf('.'));

                        RSDKv5.Scene.ISCN_ObjectDefinition objDef = scene.ObjectDefinitions[ObjectNameToDefIndex[objectName]];
                        RSDKv5.Scene.ISCN_Object obj = new RSDKv5.Scene.ISCN_Object();

                        int x = Convert.ToInt32(nodeObj.Attributes["x"]?.InnerText);
                        int y = Convert.ToInt32(nodeObj.Attributes["y"]?.InnerText);
                        bool flipX = (Convert.ToUInt32(nodeObj.Attributes["gid"]?.InnerText) & 0x80000000) != 0;
                        bool flipY = (Convert.ToUInt32(nodeObj.Attributes["gid"]?.InnerText) & 0x40000000) != 0;
                        bool priority = false;
                        byte unused = 0;

                        if (nodeObj.FirstChild?.Name == "properties" && nodeObj.FirstChild?.HasChildNodes == true) {
                            if (objDef.AttributeCount == 0) {
                                objDef.AttributeCount = (byte)nodeObj.FirstChild.ChildNodes.Count;
                                foreach (XmlNode nodeProp in nodeObj.FirstChild.ChildNodes) {
                                    switch (nodeProp.Attributes["type"]?.InnerText) {
                                        case "int":
                                            objDef.AttributeTypes.Add(2);
                                            break;
                                        case "bool":
                                            objDef.AttributeTypes.Add(7);
                                            break;
                                        default:
                                            objDef.AttributeTypes.Add(2);
                                            break;
                                    }
                                }
                            }

                            foreach (XmlNode nodeProp in nodeObj.FirstChild.ChildNodes) {
                                switch (nodeProp.Attributes["type"]?.InnerText) {
                                    case "int":
                                        obj.Attributes.Add(Convert.ToInt32(nodeProp.Attributes["value"]?.InnerText));
                                        break;
                                    case "bool":
                                        obj.Attributes.Add(nodeProp.Attributes["value"]?.InnerText == "true" ? 1 : 0);
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }

                        obj.X = (short)x;
                        obj.Y = (short)y;
                        obj.FlipX = (byte)(flipX ? 1 : 0);
                        obj.FlipY = (byte)(flipY ? 1 : 0);
                        obj.Priority = (byte)(priority ? 1 : 0);
                        obj.Unused = unused;
                        objDef.ObjectList.Add(obj);
                    }
                    break;
                }

                scene.Write(fileStream);
            }
            Console.WriteLine("Successfully converted for ImpostorEngine2!");*/
        }

        public static void ConvertSonLVLObjDefToTiled(string zone, int act, string outFolderName, string iniName, bool andknux, int zoneID) {
            // string filepath, string filename, string RSDKfolderID

            string filepath = "";

            switch(User)
            {
                case 0:
                    filepath = @"C:\Users\Justin\skdisasm-master\SonLVL INI Files\";//, @"AIZ\1.ini"//, "AIZ1";
                    break;
                case 1:
                    filepath = @"C:\Users\theclashingfritz\Documents\skdisasm\SonLVL INI Files\";
                    break;
                case 2:
                    filepath = @"C:\Users\owner\Documents\Fan Games\3mZones\Sonic 3\SonLVL INI Files";
                    break;
                default:

                    break;
            }
            string filename = zone + "\\" + act + ".ini";
            string RSDKfolderID = outFolderName;

            if (!File.Exists(Path.Combine(filepath, filename)))
                filename = zone + "\\Main.ini";

            string ogDirectory = Environment.CurrentDirectory;

            Environment.CurrentDirectory = filepath;
            LevelData.UnknownSprite = new Sprite(new BitmapBits(new Bitmap(32, 32, PixelFormat.Format8bppIndexed)));
            LevelData.Game = GameInfo.Load(Path.Combine(filepath, "SonLVL.ini"));
            LevelData.LoadLevel((andknux ? @"Sonic & Knuckles\" : @"Sonic 3\") + iniName, true);

            INIObjDefs = new Dictionary<string, ObjectData>();
            Dictionary<string, ObjectData> obj;

            if (File.Exists(Path.Combine(filepath, filename))) {
                obj = IniSerializer.Deserialize<Dictionary<string, ObjectData>>(Path.Combine(filepath, filename));
                foreach (KeyValuePair<string, ObjectData> group in obj) {
                    group.Value.Init();
                    INIObjDefs[group.Key] = group.Value;
                }
            }

            obj = IniSerializer.Deserialize<Dictionary<string, ObjectData>>(Path.Combine(filepath, "Common/Main.ini")); // Global.ini
            foreach (KeyValuePair<string, ObjectData> group in obj) {
                group.Value.Init();
                INIObjDefs[group.Key] = group.Value;
            }

            obj = IniSerializer.Deserialize<Dictionary<string, ObjectData>>(Path.Combine(filepath, "Common/Global.ini")); // Global.ini
            foreach (KeyValuePair<string, ObjectData> group in obj) {
                group.Value.Init();
                INIObjDefs[group.Key] = group.Value;
            }

            if (File.Exists(Path.Combine(filepath, zone + "\\Main.ini"))) {
                obj = IniSerializer.Deserialize<Dictionary<string, ObjectData>>(Path.Combine(filepath, zone + "\\Main.ini")); // Global.ini
                foreach (KeyValuePair<string, ObjectData> group in obj) {
                    group.Value.Init();
                    INIObjDefs[group.Key] = group.Value;
                }
            }

            if (File.Exists(Path.Combine(filepath, zone + "\\S3.ini"))) {
                obj = IniSerializer.Deserialize<Dictionary<string, ObjectData>>(Path.Combine(filepath, zone + "\\S3.ini")); // S3.ini
                foreach (KeyValuePair<string, ObjectData> group in obj) {
                    group.Value.Init();
                    INIObjDefs[group.Key] = group.Value;
                }
            }

            List<KeyValuePair<byte, ObjectDefinition>> objdefs = new List<KeyValuePair<byte, ObjectDefinition>>();
            foreach (KeyValuePair<string, ObjectData> group in INIObjDefs) {
                if (group.Value.ArtCompression == CompressionType.Invalid)
                    group.Value.ArtCompression = CompressionType.Nemesis;
                if (byte.TryParse(group.Key, System.Globalization.NumberStyles.HexNumber, System.Globalization.NumberFormatInfo.InvariantInfo, out byte ID)) {
                    ObjectDefinition def = null;
                    if (group.Value.CodeFile != null) {
                        string fulltypename = group.Value.CodeType;
                        string dllfile = Path.Combine("dllcache", fulltypename + ".dll");
                        DateTime modDate = DateTime.MinValue;
                        if (File.Exists(dllfile))
                            modDate = File.GetLastWriteTime(dllfile);
                        string fp = Path.Combine(filepath, group.Value.CodeFile.Replace('/', Path.DirectorySeparatorChar));
                        // Console.WriteLine("Loading ObjectDefinition type " + fulltypename + " from \"" + fp + "\"...");

                        if (modDate >= File.GetLastWriteTime(fp) & modDate > File.GetLastWriteTime(Application.ExecutablePath)) {
                            // Console.WriteLine("Loading type from cached assembly \"" + dllfile + "\"...");
                            def = (ObjectDefinition)Activator.CreateInstance(System.Reflection.Assembly.LoadFile(Path.Combine(filepath, dllfile)).GetType(fulltypename));
                        }
                        else {
                            Console.WriteLine("Compiling code file...");
                            string ext = Path.GetExtension(fp);
                            CodeDomProvider pr = null;
                            switch (ext.ToLowerInvariant()) {
                                case ".cs":
                                    pr = new Microsoft.CSharp.CSharpCodeProvider();
                                    break;
                                case ".vb":
                                    pr = new Microsoft.VisualBasic.VBCodeProvider();
                                    break;
                            }

                            if (pr != null) {
                                CompilerParameters para = new CompilerParameters(new string[] {
                                    "System.dll",
                                    "System.Core.dll",
                                    "System.Drawing.dll",
                                    System.Reflection.Assembly.GetAssembly(typeof(Block)).Location,
                                    System.Reflection.Assembly.GetExecutingAssembly().Location,
                                }) {
                                    GenerateExecutable = false,
                                    GenerateInMemory = false,
                                    IncludeDebugInformation = true,
                                    OutputAssembly = Path.Combine(Environment.CurrentDirectory, dllfile),
                                };
                                CompilerResults res = pr.CompileAssemblyFromFile(para, fp);
                                if (res.Errors.HasErrors) {
                                    Console.WriteLine("Compile failed.", "Errors:");
                                    foreach (CompilerError item in res.Errors)
                                        Console.WriteLine(item.ToString());
                                    Console.WriteLine(string.Empty);
                                    def = new DefaultObjectDefinition();
                                }
                                else {
                                    Console.WriteLine("Compile succeeded.");
                                    def = (ObjectDefinition)Activator.CreateInstance(res.CompiledAssembly.GetType(fulltypename));
                                }
                            }
                            else
                                def = new DefaultObjectDefinition();
                        }
                    }
                    else if (group.Value.XMLFile != null)
                        def = new XMLObjectDefinition();
                    else
                        def = new DefaultObjectDefinition();

                    objdefs.Add(new KeyValuePair<byte, ObjectDefinition>(ID, def));
                    def.Init(group.Value);
                }
            }

            Environment.CurrentDirectory = ogDirectory;

            if (!Directory.Exists("Out (Tiled)"))
                Directory.CreateDirectory("Out (Tiled)");

            if (!Directory.Exists("Out (Tiled)/" + RSDKfolderID))
                Directory.CreateDirectory("Out (Tiled)/" + RSDKfolderID);

            List<KeyValuePair<int, string>> Objects = new List<KeyValuePair<int, string>>();
            List<int> IDs = new List<int>();

            var settings = new XmlWriterSettings() {
                Indent = true,
                IndentChars = "  "
            };
            foreach (KeyValuePair<byte, ObjectDefinition> def in objdefs) {
                Console.WriteLine(def.Value.Name + " (" + def.Key.ToHex68k() + ")");
                /*
                Console.WriteLine("Named Subtypes:");
                foreach (byte n in def.Value.Subtypes) {
                    Console.WriteLine(def.Value.SubtypeName(n) + ": " + n.ToHex68k());
                }
                //*/

                Console.WriteLine("Custom Properties:");
                foreach (PropertySpec n in def.Value.CustomProperties) {
                    Console.WriteLine(n.Name + " (" + n.Type + "): " + n.Category);
                }

                Sprite mainSprite = def.Value.Image;

                if (true) {
                    //mainSprite = def.Value.SubtypeImage(def.Value.Subtypes[0]);
                }

                string objectName = andknux && zone != "FBZ" ? SKObjects[def.Key] : S3Objects[def.Key];

                Bitmap bitmap = mainSprite.GetBitmap().ToBitmap();
                ColorPalette colorPalette = bitmap.Palette;
                for (int i = 0; i < 64; i++) {
                    colorPalette.Entries[i] = LevelData.PaletteToColor(i >> 4, i & 0xF, true);
                }
                bitmap.Palette = colorPalette;
                bitmap.Save("Out (Tiled)/" + RSDKfolderID + "/" + objectName + ".png");

                Console.WriteLine("def.Value.Pos: " + mainSprite.X + ", " + mainSprite.Y);

                Objects.Add(new KeyValuePair<int, string>(def.Key, objectName));
                IDs.Add(def.Key);

                // Object Tile
                using (XmlWriter writer = XmlWriter.Create("Out (Tiled)/" + RSDKfolderID + "/" + objectName + ".tsx", settings)) {
                    writer.WriteStartDocument();
                    writer.WriteStartElement("tileset");
                    writer.WriteAttributeString("version", "1.2");
                    writer.WriteAttributeString("tiledversion", "1.2.2");
                    writer.WriteAttributeString("name", objectName);
                    writer.WriteAttributeString("tilewidth", bitmap.Width.ToString());
                    writer.WriteAttributeString("tileheight", bitmap.Height.ToString());
                    writer.WriteAttributeString("tilecount", (1).ToString());
                    writer.WriteAttributeString("columns", (1).ToString());
                    
                    writer.WriteStartElement("tileoffset");
                    writer.WriteAttributeString("x", mainSprite.X.ToString());
                    writer.WriteAttributeString("y", (bitmap.Height + mainSprite.Y).ToString());
                    writer.WriteEndElement();

                    writer.WriteStartElement("image");
                    writer.WriteAttributeString("source", objectName + ".png");
                    writer.WriteAttributeString("width", bitmap.Width.ToString());
                    writer.WriteAttributeString("height", bitmap.Height.ToString());
                    writer.WriteEndElement();

                    writer.WriteEndElement();
                    writer.WriteEndDocument();
                    writer.Flush();
                }
                // Object Template
                using (XmlWriter writer = XmlWriter.Create("Out (Tiled)/" + RSDKfolderID + "/" + objectName + ".tx", settings)) {
                    writer.WriteStartDocument();
                    writer.WriteStartElement("template");

                    writer.WriteStartElement("tileset");
                    writer.WriteAttributeString("firstgid", "1");
                    writer.WriteAttributeString("source", objectName + ".tsx");
                    writer.WriteEndElement();

                    writer.WriteStartElement("object");
                    writer.WriteAttributeString("name", objectName);
                    writer.WriteAttributeString("gid", "1");
                    writer.WriteAttributeString("width", bitmap.Width.ToString());
                    writer.WriteAttributeString("height", bitmap.Height.ToString());

                    writer.WriteStartElement("properties");
                    foreach (PropertySpec n in def.Value.CustomProperties) {
                        writer.WriteStartElement("property");
                        writer.WriteAttributeString("name", n.Name);
                        writer.WriteAttributeString("type", n.Type == typeof(bool) ? "bool" : "int");
                        if (n.DefaultValue != null)
                            writer.WriteAttributeString("value", n.DefaultValue.ToString());
                        writer.WriteEndElement();
                    }
                    writer.WriteEndElement(); // properties

                    writer.WriteEndElement(); // object


                    writer.WriteEndElement(); // template
                    writer.WriteEndDocument();
                    writer.Flush();
                }

                Console.WriteLine();
            }

            switch (User)
            {
                case 0:
                    Globals.OUT = @"C:\Users\Justin\sonic-3-mixed\ImpostorEngine2\source\Resources\Stages\";
                    break;
                case 1:

                    break;
                case 2:
                    Globals.OUT = @"C:\Users\owner\Documents\Fan Games\sonic-3-mixed\ImpostorEngine2\source\Resources\Stages\MStages";
                    break;
            }
            

            using (XmlWriter writer = XmlWriter.Create("Out (Tiled)/" + RSDKfolderID + "/Tileset.tsx", settings)) {
                writer.WriteStartDocument();
                writer.WriteStartElement("tileset");
                writer.WriteAttributeString("version", "1.2");
                writer.WriteAttributeString("tiledversion", "1.2.2");
                writer.WriteAttributeString("name", RSDKfolderID);
                writer.WriteAttributeString("tilewidth", (16).ToString());
                writer.WriteAttributeString("tileheight", (16).ToString());
                writer.WriteAttributeString("tilecount", (1024).ToString());
                writer.WriteAttributeString("columns", (32).ToString());

                writer.WriteStartElement("image");
                writer.WriteAttributeString("source", "16x16Tiles.gif");
                writer.WriteAttributeString("width", (512).ToString());
                writer.WriteAttributeString("height", (512).ToString());
                writer.WriteEndElement();

                writer.WriteEndElement();
                writer.WriteEndDocument();
                writer.Flush();
            }

            File.Copy(Globals.OUT + RSDKfolderID + "\\16x16Tiles.gif", "Out (Tiled)/" + RSDKfolderID + "\\16x16Tiles.gif", true);

                RSDKv5.Scene scene = new RSDKv5.Scene(Globals.OUT + RSDKfolderID + "\\Scene.bin");

                int maxW = 0;
                int maxH = 0;

                foreach (RSDKv5.SceneLayer layer in scene.Layers) {
                    maxW = Math.Max(layer.Width, maxW);
                    maxH = Math.Max(layer.Height, maxH);
                }

                using (XmlWriter writer = XmlWriter.Create("Out (Tiled)/" + RSDKfolderID + "/Scene.tmx", settings)) {
                    writer.WriteStartDocument();
                    writer.WriteStartElement("map");
                    writer.WriteAttributeString("version", "1.2");
                    writer.WriteAttributeString("tiledversion", "1.2.2");
                    writer.WriteAttributeString("name", RSDKfolderID);
                    writer.WriteAttributeString("orientation", "orthogonal");
                    writer.WriteAttributeString("renderorder", "right-down");
                    writer.WriteAttributeString("infinite", "1");
                    writer.WriteAttributeString("tilewidth", (16).ToString());
                    writer.WriteAttributeString("tileheight", (16).ToString());
                    writer.WriteAttributeString("width", maxW.ToString());
                    writer.WriteAttributeString("height", maxH.ToString());

                    writer.WriteStartElement("properties");

                    writer.WriteStartElement("property");
                    writer.WriteAttributeString("name", "Act");
                    writer.WriteAttributeString("type", "int");
                    writer.WriteAttributeString("value", act.ToString());
                    writer.WriteEndElement();
                    writer.WriteStartElement("property");
                    writer.WriteAttributeString("name", "Song File");
                    writer.WriteAttributeString("value", "Music/" + outFolderName + ".ogg");
                    writer.WriteEndElement();
                    writer.WriteStartElement("property");
                    writer.WriteAttributeString("name", "Song Loop Point (Samples)");
                    writer.WriteAttributeString("type", "int");
                    writer.WriteAttributeString("value", (0).ToString());
                    writer.WriteEndElement();
                    writer.WriteStartElement("property");
                    writer.WriteAttributeString("name", "Level Title");
                    writer.WriteAttributeString("value", lvlNames[zoneID]);
                    writer.WriteEndElement();
                    writer.WriteStartElement("property");
                    writer.WriteAttributeString("name", "Zone ID");
                    writer.WriteAttributeString("type", "int");
                    writer.WriteAttributeString("value", (zoneID + 1).ToString());
                    writer.WriteEndElement();
                    writer.WriteStartElement("property");
                    writer.WriteAttributeString("name", "Visible HUD");
                    writer.WriteAttributeString("type", "bool");
                    writer.WriteAttributeString("value", "true");
                    writer.WriteEndElement();

                    writer.WriteEndElement(); // properties
                    
                    int gid = 1;
                    writer.WriteStartElement("tileset");
                    writer.WriteAttributeString("firstgid", gid.ToString());
                    writer.WriteAttributeString("source", "Tileset.tsx");
                    writer.WriteEndElement();
                    gid += 1024;
                    foreach (KeyValuePair<int, string> str in Objects) {
                        writer.WriteStartElement("tileset");
                        writer.WriteAttributeString("firstgid", (gid + str.Key).ToString());
                        writer.WriteAttributeString("source", str.Value + ".tsx");
                        writer.WriteEndElement();
                    }

                    int id = 1;
                    foreach (RSDKv5.SceneLayer layer in scene.Layers) {
                        // writer.WriteStartElement("objectgroup");
                        writer.WriteStartElement("layer");
                        writer.WriteAttributeString("id", (id).ToString());
                        writer.WriteAttributeString("name", layer.Name);
                        writer.WriteAttributeString("width", layer.Width.ToString());
                        writer.WriteAttributeString("height", layer.Height.ToString());
                        
                        writer.WriteStartElement("properties");
                        {
                            writer.WriteStartElement("property");
                            writer.WriteAttributeString("name", "Infinitely Vertical");
                            writer.WriteAttributeString("type", "bool");
                            writer.WriteAttributeString("value", layer.Behaviour.ToString());
                            writer.WriteEndElement();
                            writer.WriteStartElement("property");
                            writer.WriteAttributeString("name", "Flags");
                            writer.WriteAttributeString("type", "int");
                            writer.WriteAttributeString("value", layer.DrawingOrder.ToString());
                            writer.WriteEndElement();
                            writer.WriteStartElement("property");
                            writer.WriteAttributeString("name", "Relative Y");
                            writer.WriteAttributeString("type", "int");
                            writer.WriteAttributeString("value", layer.RelativeSpeed.ToString());
                            writer.WriteEndElement();
                            writer.WriteStartElement("property");
                            writer.WriteAttributeString("name", "Constant Y");
                            writer.WriteAttributeString("type", "int");
                            writer.WriteAttributeString("value", layer.ConstantSpeed.ToString());
                            writer.WriteEndElement();

                            writer.WriteStartElement("property");
                            writer.WriteAttributeString("name", "Width");
                            writer.WriteAttributeString("type", "int");
                            writer.WriteAttributeString("value", layer.Width.ToString());
                            writer.WriteEndElement();
                            writer.WriteStartElement("property");
                            writer.WriteAttributeString("name", "Height");
                            writer.WriteAttributeString("type", "int");
                            writer.WriteAttributeString("value", layer.Height.ToString());
                            writer.WriteEndElement();
                        }
                        writer.WriteEndElement();
                        
                        /*
                        for (int y = 0; y < layer.Height; y++) {
                            for (int x = 0; x < layer.Width; x++) {
                                bool flipX = (layer.Tiles[y][x] >> 10 & 1) == 1;
                                bool flipY = (layer.Tiles[y][x] >> 11 & 1) == 1;

                                int solidityA = (layer.Tiles[y][x] >> 12 & 3);
                                int solidityB = (layer.Tiles[y][x] >> 14 & 3);

                                uint til = (uint)(layer.Tiles[y][x] & 0x3FF);
                                if (til > 0) {
                                    if (flipX) til |= 0x80000000;
                                    if (flipY) til |= 0x40000000;

                                    til++;

                                    writer.WriteStartElement("object");
                                    writer.WriteAttributeString("gid", til.ToString());
                                    writer.WriteAttributeString("x", (x << 4).ToString());
                                    writer.WriteAttributeString("y", ((y << 4) + 16).ToString());
                                    writer.WriteAttributeString("width", "16");
                                    writer.WriteAttributeString("height", "16");

                                    writer.WriteStartElement("properties");
                                    {
                                        writer.WriteStartElement("property");
                                        writer.WriteAttributeString("name", "Solidity A");
                                        writer.WriteAttributeString("type", "int");
                                        writer.WriteAttributeString("value", solidityA.ToString());
                                        writer.WriteEndElement();
                                        writer.WriteStartElement("property");
                                        writer.WriteAttributeString("name", "Solidity B");
                                        writer.WriteAttributeString("type", "int");
                                        writer.WriteAttributeString("value", solidityB.ToString());
                                        writer.WriteEndElement();
                                    }
                                    writer.WriteEndElement();

                                    writer.WriteEndElement();
                                }
                            }
                        }
                        //*/

                        //*
                        writer.WriteStartElement("data");
                        writer.WriteAttributeString("encoding", "base64");
                        int tid = 0;
                        byte[] bytearr = new byte[layer.Height * layer.Width * 4];
                        for (int y = 0; y < layer.Height; y++) {
                            for (int x = 0; x < layer.Width; x++) {
                                bool flipX = (layer.Tiles[y][x] >> 10 & 1) == 1;
                                bool flipY = (layer.Tiles[y][x] >> 11 & 1) == 1;

                                uint til = (uint)(layer.Tiles[y][x] & 0x3FF);
                                if (til > 0) {
                                    if (flipX) til |= 0x80000000;
                                    if (flipY) til |= 0x40000000;

                                    til++;
                                }

                                til |= 0x3C000000;

                                bytearr[(tid << 2) + 0] = (byte)(til >> 00 & 0xFF);
                                bytearr[(tid << 2) + 1] = (byte)(til >> 08 & 0xFF);
                                bytearr[(tid << 2) + 2] = (byte)(til >> 16 & 0xFF);
                                bytearr[(tid << 2) + 3] = (byte)(til >> 24 & 0xFF);
                                tid++;
                            }
                        }
                        writer.WriteString(Convert.ToBase64String(bytearr));
                        writer.WriteEndElement();
                        //*/


                        writer.WriteEndElement();


                        writer.WriteStartElement("objectgroup");
                        {
                            writer.WriteAttributeString("id", (id).ToString());
                            writer.WriteAttributeString("name", "Scrolling Info Layer");
                            writer.WriteAttributeString("visible", "0");

                            int y = 0;
                            int h = 0;
                            int skefbid = 1;
                            byte lastval = layer.ScrollIndexes[0];
                            for (int ty = 0; ty < layer.Height * 16; ty++) {
                                if (lastval != layer.ScrollIndexes[ty] || ty == layer.Height * 16 - 1) {
                                    if (ty == layer.Height * 16 - 1)
                                        h++;

                                    writer.WriteStartElement("object");
                                    {
                                        writer.WriteAttributeString("id", skefbid.ToString());
                                        writer.WriteAttributeString("x", (0).ToString());
                                        writer.WriteAttributeString("y", y.ToString());
                                        writer.WriteAttributeString("width", (layer.Width * 16).ToString());
                                        writer.WriteAttributeString("height", h.ToString());
                                        writer.WriteStartElement("properties");
                                        {
                                            writer.WriteStartElement("property");
                                            writer.WriteAttributeString("name", "Deform");
                                            writer.WriteAttributeString("type", "bool");
                                            writer.WriteAttributeString("value", layer.ScrollingInfo[lastval].Behaviour.ToString());
                                            writer.WriteEndElement();
                                            writer.WriteStartElement("property");
                                            writer.WriteAttributeString("name", "Flags");
                                            writer.WriteAttributeString("type", "int");
                                            writer.WriteAttributeString("value", layer.ScrollingInfo[lastval].DrawOrder.ToString());
                                            writer.WriteEndElement();
                                            writer.WriteStartElement("property");
                                            writer.WriteAttributeString("name", "Relative X");
                                            writer.WriteAttributeString("type", "int");
                                            writer.WriteAttributeString("value", layer.ScrollingInfo[lastval].RelativeSpeed.ToString());
                                            writer.WriteEndElement();
                                            writer.WriteStartElement("property");
                                            writer.WriteAttributeString("name", "Constant X");
                                            writer.WriteAttributeString("type", "int");
                                            writer.WriteAttributeString("value", layer.ScrollingInfo[lastval].ConstantSpeed.ToString());
                                            writer.WriteEndElement();
                                        }
                                        writer.WriteEndElement();
                                    }
                                    writer.WriteEndElement();

                                    skefbid++;
                                    lastval = layer.ScrollIndexes[ty];
                                    y += h;
                                    h = 0;
                                }
                                h++;
                            }
                            id++;
                        }
                        writer.WriteEndElement();

                        id++;
                    }

                    writer.WriteStartElement("objectgroup");
                    writer.WriteAttributeString("id", (id).ToString());
                    writer.WriteAttributeString("name", "Objects");
                    /*for (int o = 0; o < scene.Objects.Count; o++) {
                        int ID = scene.Objects[o].ID;
                        uint GID = (uint)ID + 1024 + 1;

                        if (scene.ObjectEntries[o].XFlip) GID |= 0x80000000;
                        if (scene.ObjectEntries[o].YFlip) GID |= 0x40000000;

                        writer.WriteStartElement("object");
                        writer.WriteAttributeString("id", (id++).ToString());
                        writer.WriteAttributeString("gid", GID.ToString());
                        writer.WriteAttributeString("x", scene.ObjectEntries[o].X.ToString());
                        writer.WriteAttributeString("y", scene.ObjectEntries[o].Y.ToString());

                        if (IDs.Contains(ID)) {
                            int idid = IDs.IndexOf(ID);
                            string objectName = andknux && zone != "FBZ" ? SKObjects[ID] : S3Objects[ID];
                            writer.WriteAttributeString("template", objectName + ".tx");
                            writer.WriteStartElement("properties");
                            bool none = true;
                            foreach (PropertySpec n in objdefs[idid].Value.CustomProperties) {
                                writer.WriteStartElement("property");
                                writer.WriteAttributeString("name", n.Name);
                                writer.WriteAttributeString("type", n.Type == typeof(bool) ? "bool" : "int");
                                writer.WriteAttributeString("value", n.GetValue(scene.ObjectEntries[o]).ToString());
                                writer.WriteEndElement();
                                none = false;
                            }
                            if (none) {
                                writer.WriteStartElement("property");
                                writer.WriteAttributeString("name", "Type");
                                writer.WriteAttributeString("type", "int");
                                writer.WriteAttributeString("value", scene.ObjectEntries[o].SubType.ToString());
                                writer.WriteEndElement();
                            }
                            writer.WriteEndElement(); // properties
                        }

                        writer.WriteEndElement();
                    }*/
                    writer.WriteEndElement();
                    id++;

                    writer.WriteEndElement();
                    writer.WriteEndDocument();
                    writer.Flush();
                }
            
        }

        public static void ConvertLevel(string zone, int act, string outFolderName, string iniName, bool andknux) {
            int zoneID = 0;
            for (; zoneID < 15; zoneID++) {
                if (zone == lvlIDs[zoneID])
                    break;
            }

            if (DOTILEDCONVERT) {
                ConvertSonLVLObjDefToTiled(zone, act, outFolderName, iniName, andknux, zoneID);
                return;
            }

            string LEVELROOT = Globals.ROOT + @"Levels\" + zone + "\\";

            switch (User)
            {
                case 0:

                    break;
                case 1:
                    Globals.OUT = @"C:\Users\theclashingfritz\Documents\Sonic-3-Mixed\ImpostorEngine2\source\Resources\MStages\";
                    Globals.ROOT = @"C:\Users\theclashingfritz\Documents\skdisasm\";
                    break;
                case 2:
                    Globals.OUT = @"C:\Users\owner\Documents\Fan Games\sonic-3-mixed\ImpostorEngine2\source\Resources\Stages\MStages\";
                    Globals.ROOT = @"C:\Users\owner\Documents\Fan Games\3mZones\Sonic 3\";
                    break;
            }
            

            IniDictionary iniDictionary = IniFile.Load(Globals.ROOT + @"SonLVL INI Files\SonLVL.ini");
            IniGroup iniLevel = iniDictionary[(andknux ? @"Sonic & Knuckles\" : @"Sonic 3\") + iniName];

            /*
             * Timeline:
             * 1. 16x16 Tiles needs to be generated, and if it contains animated tiles note that
             * 2. Construct animated tile spritesheet
             * 3. Generate TileConfig
             * 4. Generate Scene Data
             */

            ///
            /// Step 1.
            ///

            byte[] tileData;
            byte[] animTileData;
            byte[] blocksData;

            int[] TilePriorityConfig = new int[0x400];
            List<int> SplitLayerTilesList = new List<int>();
            Dictionary<int, int> SplitLayerTiles = new Dictionary<int, int>();
            Dictionary<int, int> TilesAnimedList = new Dictionary<int, int>();
            List<AnimatedTiles> AnimTiles = new List<AnimatedTiles>();

            GenerateTiles(iniLevel, outFolderName, ref TilePriorityConfig, ref SplitLayerTilesList, ref SplitLayerTiles, ref TilesAnimedList, ref AnimTiles, out tileData, out animTileData, out blocksData);

            ///
            /// Step 3.
            ///

            byte[] collisionHeightsData = File.ReadAllBytes(Globals.ROOT + FileInfo.Load(iniDictionary[""]["colarr1"])[0].Filename);
            byte[] collisionAnglesData = File.ReadAllBytes(Globals.ROOT + FileInfo.Load(iniDictionary[""]["angles"])[0].Filename);

            GenerateTileConfig(iniLevel, outFolderName, SplitLayerTilesList, collisionHeightsData, collisionAnglesData, blocksData);

            ///
            /// Step 4.
            ///

            GenerateSceneBinRSDK(iniLevel, outFolderName, TilePriorityConfig, SplitLayerTiles, TilesAnimedList, AnimTiles, zoneID, act, tileData, animTileData, blocksData, iniName);
        }

        public static void GenerateTiles(
            IniGroup iniLevel, 
            string outFolderName, 
            ref int[] TilePriorityConfig,
            ref List<int> SplitLayerTilesList,
            ref Dictionary<int, int> SplitLayerTiles,
            ref Dictionary<int, int> tilesAnimedList,
            ref List<AnimatedTiles> animTiles,
            out byte[] tileData,
            out byte[] animTileData,
            out byte[] blocksData) {

            int SplitLayerTilesCount = 0;
            TilePriorityConfig = new int[0x400];

            FileInfo[] fileInfos;
            List<AnimationEditor.PLCRequest> requests;
            Bitmap tileImage = new Bitmap(32 * 0x10, 32 * 0x10, PixelFormat.Format8bppIndexed);

            // Set Palette
            int lasti = 0;
            ColorPalette cpal = tileImage.Palette;
            int[] palette = LoadPalette(Globals.ROOT + @"General\Sprites\Sonic\Palettes\SonicAndTails.bin", Globals.ROOT + FileInfo.Load(iniLevel["palette"])[1].Filename);
            for (int i = 0; i < palette.Length; i++) {
                cpal.Entries[i] = Color.FromArgb(palette[i] >> 16 & 0xFF, palette[i] >> 8 & 0xFF, palette[i] & 0xFF);
                cpal.Entries[i & 0xF0] = Color.FromArgb(0, 0xFF, 0x00, 0xFF);
                lasti = i;
            }
            if (iniLevel.ContainsKey("palette2")) {
                palette = LoadPalette(null, Globals.ROOT + FileInfo.Load(iniLevel["palette2"])[1].Filename);
                for (int i = 0; i < palette.Length; i++) {
                    cpal.Entries[i + 0x40] = Color.FromArgb(palette[i] >> 16 & 0xFF, palette[i] >> 8 & 0xFF, palette[i] & 0xFF);
                    cpal.Entries[(i + 0x40) & 0xF0] = Color.FromArgb(0, 0xFF, 0x00, 0xFF);
                    lasti = i + 0x40;
                }
            }

            for (int i = lasti + 1; i < 256; i++)
                cpal.Entries[i] = Color.FromArgb(0, 0, 0, 0);

            tileImage.Palette = cpal;

            // Get Tiles
            fileInfos = FileInfo.Load(iniLevel["tiles"]);
            requests = new List<AnimationEditor.PLCRequest>();
            for (int i = 0; i < fileInfos.Length; i++)
                requests.Add(new AnimationEditor.PLCRequest(Globals.ROOT + fileInfos[i].Filename, fileInfos[i].Offset / 0x20));
            tileData = LoadTiles(requests);

            Console.WriteLine(outFolderName);

            // Get Animated Tiles
            byte[] dec;
            animTileData = new byte[0];
            for (int j = 1; j <= 8; j++) {
                if (!iniLevel.ContainsKey("animtiles" + j)) continue;

                string[] info = iniLevel["animtiles" + j].Split(':');

                dec = File.ReadAllBytes(Globals.ROOT + info[0].Substring(3).Replace("/", "\\"));

                animTiles.Add(new AnimatedTiles(GetInt(info[2]), GetInt(info[3]), animTileData.Length / 0x20, (dec.Length / 0x20) / GetInt(info[3]), info.Length >= 5));
                // Console.WriteLine("animtiles" + j + ": " + (info.Length >= 5));

                animTileData = animTileData.Concat(dec).ToArray();
                Console.WriteLine("animtiles" + ": " + (animTileData.Length / 0x20) + " (" + dec.Length / 0x20 + ")");
            }

            // Get Blocks
            fileInfos = FileInfo.Load(iniLevel["blocks"]);
            requests = new List<AnimationEditor.PLCRequest>();
            for (int i = 0; i < fileInfos.Length; i++)
                requests.Add(new AnimationEditor.PLCRequest(Globals.ROOT + fileInfos[i].Filename, fileInfos[i].Offset / 8));
            blocksData = LoadBlocks(requests);

            // Set pixels
            BitmapData bmpData = tileImage.LockBits(new Rectangle(0, 0, tileImage.Width, tileImage.Height), ImageLockMode.WriteOnly, tileImage.PixelFormat);
            IntPtr tileImagePtr = bmpData.Scan0;
            byte[] px = new byte[bmpData.Stride * tileImage.Height];

            for (int til = 0; til < blocksData.Length / 8; til++) {
                TilePriorityConfig[til] = 0x0;
                for (int j = 0; j < 4; j++) {
                    int word = (blocksData[til * 8 + j * 2] & 0xFF) * 0x100 + (blocksData[til * 8 + j * 2 + 1] & 0xFF);
                    int priorit = (word & 0x8000) >> 15;
                    int pal = (word & 0x6000) >> 13;
                    int flipY = (word & 0x1000) >> 12;
                    int flipX = (word & 0x800) >> 11;
                    int ind = word & 0x7FF;

                    int x = ((j &  1) << 3) + ((til & 0x1F) << 4);
                    int y = ((j >> 1) << 3) + ((til >> 0x5) << 4);

                    if (ind >= tileData.Length / 0x20)
                        continue;

                    bool Anim = false;
                    int i = 0;
                    int of = 0;
                    foreach (AnimatedTiles a in animTiles) {
                        if (!a.OnlyVisual) { of++; }

                        if (ind >= a.ID && ind < a.ID + a.Count) {
                            ind = a.AnimTileID + (ind - a.ID);
                            Anim = true;

                            TilePriorityConfig[til] = priorit * 0xF;

                            if (!a.OnlyVisual)
                                tilesAnimedList[til] = of - 1;
                            break;
                        }
                        i++;
                    }

                    if (ind == 0) {
                        for (int ghgh = j + 1; ghgh < j + 3; ghgh++) {
                            int gh = ghgh & 3;
                            int word2 = (blocksData[til * 8 + gh * 2] & 0xFF) * 0x100 + (blocksData[til * 8 + gh * 2 + 1] & 0xFF);
                            int priorit2 = (word2 & 0x8000) >> 15;
                            int ind2 = word2 & 0x7FF;
                            if (ind2 != 0) {
                                priorit = priorit2;
                                break;
                            }
                        }
                    }

                    if (Anim)
                        DrawTile(bmpData, ref px, animTileData, ind, x, y, flipX == 1, flipY == 1, pal);
                    else
                        DrawTile(bmpData, ref px, tileData, ind, x, y, flipX == 1, flipY == 1, pal);

                    if (!Anim)
                        TilePriorityConfig[til] |= (priorit << j);
                }

                if (TilePriorityConfig[til] != 0 && TilePriorityConfig[til] != 0xF) {
                    SplitLayerTilesList.Add(til);
                    SplitLayerTiles[til | 0x0000] = SplitLayerTilesCount + blocksData.Length / 8;
                    SplitLayerTiles[til | 0xF000] = SplitLayerTilesCount + blocksData.Length / 8 + 1;

                    for (int j = 0; j < 4; j++) {
                        if (til * 8 + j * 2 >= blocksData.Length) continue;

                        int word = (blocksData[til * 8 + j * 2] & 0xFF) * 0x100 + (blocksData[til * 8 + j * 2 + 1] & 0xFF);
                        int priorit = (word & 0x8000) >> 15;
                        int pal = (word & 0x6000) >> 13;
                        int flipY = (word & 0x1000) >> 12;
                        int flipX = (word & 0x800) >> 11;
                        int ind = word & 0x7FF;

                        int til2 = (blocksData.Length / 8 + SplitLayerTilesCount);

                        if (priorit == 1) {
                            til2++;
                        }
                        int x = ((j & 1) << 3) + ((til2 & 0x1F) << 4);
                        int y = ((j >> 1) << 3) + ((til2 >> 0x5) << 4);

                        // if (Anim)
                        //     DrawTile(bmpData, ref px, animTileData, ind, x, y, flipX == 1, flipY == 1, pal);
                        // else
                        DrawTile(bmpData, ref px, tileData, ind, x, y, flipX == 1, flipY == 1, pal);

                        TilePriorityConfig[til] |= (priorit << j);
                    }

                    SplitLayerTilesCount += 2;
                }
            }

            Directory.CreateDirectory(Path.GetFullPath(@"Out (Level)\" + outFolderName));

            Marshal.Copy(px, 0, tileImagePtr, px.Length);
            tileImage.UnlockBits(bmpData);

            Directory.CreateDirectory(Globals.OUT + outFolderName);
            tileImage.Save(Globals.OUT + outFolderName + "\\16x16Tiles.gif", ImageFormat.Gif);
            tileImage.Dispose();
        }

        public static void GenerateTileConfig(
            IniGroup iniLevel,
            string outFolderName,
            List<int> SplitLayerTilesList,
            byte[] collisionHeightsData,
            byte[] collisionAnglesData,
            byte[] blocksData) {
            List<byte> tileset1 = new List<byte>(); // 0x400 * 0x26 // make sure to padd out
            List<byte> tileset2 = new List<byte>();

            byte[] collisionIndexData = File.ReadAllBytes(Globals.ROOT + FileInfo.Load(iniLevel["colind"])[0].Filename);

            int collisionDataSize = 1;
            if (iniLevel.ContainsKey("colindsz"))
                collisionDataSize = ParseInt(iniLevel["colindsz"]);
            
            int DecompressedSize;
            int CompressedSize;

            using (FileStream fileStream = new FileStream(Globals.OUT + outFolderName + "\\TileConfig.bin", FileMode.OpenOrCreate)) {
                // Magic (TIL0)
                fileStream.WriteByte(0x54);
                fileStream.WriteByte(0x49);
                fileStream.WriteByte(0x4C);
                fileStream.WriteByte(0x00);

                using (MemoryStream memoryStream = new MemoryStream()) {
                    int tcount = 0;
                    for (int i = 0; i < blocksData.Length / 8; i++) {
                        int overX = (i % 32) * 16;
                        int overY = (i / 32) * 16;

                        int til = i;
                        // int flipTX = 0;
                        // int flipTY = 0;

                        byte[] Collision;
                        byte[] HasCollision;
                        byte[] Config;
                        byte IsCeiling;
                        int pl1, pl2;
                        byte ang;
                        int heightsIndex;

                        // int heightToObserve = 0xC2;

                        Collision = new byte[16];
                        HasCollision = new byte[16];
                        Config = new byte[5];
                        IsCeiling = 0;
                        heightsIndex = collisionIndexData[(collisionDataSize == 2 ? til * 2 + 1 + 0x000 : til * 2)] & 0xFF;
                        for (int ii = 0; ii < 16; ii++) {
                            byte h = collisionHeightsData[heightsIndex * 0x10 + ii];
                            if ((h >> 7) == 0) {
                                Collision[ii] = (byte)(0x10 - h);
                            }
                            else {
                                h = (byte)(h - 0xF0);
                                Collision[ii] = h;
                                IsCeiling = 1;
                            }
                            HasCollision[ii] = (byte)(h > 0 ? 1 : 0);
                        }

                        Config[0] = 0x00;
                        Config[1] = 0xC0;
                        Config[2] = 0x40;
                        Config[3] = 0x80;
                        Config[4] = 0x69;
                        ang = collisionAnglesData[heightsIndex];
                        if (ang >= 0xC0) { pl1 = 0; pl2 = 1; }
                        else if (ang < 0xC0 && ang >= 0x80) { pl1 = 1; pl2 = 3; }
                        else if (ang < 0x80 && ang >= 0x40) { pl1 = 2; pl2 = 3; }
                        else { pl1 = 0; pl2 = 2; }
                        if (ang != 0xFF) {
                            Config[pl1] = ang;
                            Config[pl2] = ang;
                        }

                        for (int ii = 0; ii < 0x10; ii++)
                            tileset1.Add(Collision[ii]);
                        for (int ii = 0; ii < 0x10; ii++)
                            tileset1.Add(HasCollision[ii]);

                        tileset1.Add(IsCeiling);

                        for (int ii = 0; ii < 5; ii++)
                            tileset1.Add(Config[ii]);

                        Collision = new byte[16];
                        HasCollision = new byte[16];
                        Config = new byte[5];
                        IsCeiling = 0;
                        heightsIndex = collisionIndexData[(collisionDataSize == 2 ? til * 2 + 1 + 0x600 : til * 2 + 1)] & 0xFF;
                        for (int ii = 0; ii < 16; ii++) {
                            byte h = collisionHeightsData[heightsIndex * 0x10 + ii];
                            if ((h >> 7) == 0) {
                                Collision[ii] = (byte)(0x10 - h);
                            }
                            else {
                                h = (byte)(h - 0xF0);
                                Collision[ii] = h;
                                IsCeiling = 1;
                            }
                            HasCollision[ii] = (byte)(h > 0 ? 1 : 0);
                        }
                        Config[0] = 0x00;
                        Config[1] = 0xC0;
                        Config[2] = 0x40;
                        Config[3] = 0x80;
                        Config[4] = 0x69;
                        ang = collisionAnglesData[heightsIndex];
                        if (ang >= 0xC0) { pl1 = 0; pl2 = 1; }
                        else if (ang < 0xC0 && ang >= 0x80) { pl1 = 1; pl2 = 3; }
                        else if (ang < 0x80 && ang >= 0x40) { pl1 = 2; pl2 = 3; }
                        else { pl1 = 0; pl2 = 2; }
                        if (ang != 0xFF) {
                            Config[pl1] = ang;
                            Config[pl2] = ang;
                        }

                        for (int ii = 0; ii < 0x10; ii++)
                            tileset2.Add(Collision[ii]);
                        for (int ii = 0; ii < 0x10; ii++)
                            tileset2.Add(HasCollision[ii]);
                        tileset2.Add(IsCeiling);
                        for (int ii = 0; ii < 5; ii++)
                            tileset2.Add(Config[ii]);

                        tcount++;
                    }
                    for (int i = 0; i < SplitLayerTilesList.Count; i++) {
                        for (int ii = 0; ii < 0x26; ii++) {
                            tileset1.Add(tileset1[SplitLayerTilesList[i] * 0x26 + ii]);
                            tileset2.Add(tileset2[SplitLayerTilesList[i] * 0x26 + ii]);
                        }
                        for (int ii = 0; ii < 0x26; ii++) {
                            tileset1.Add(tileset1[SplitLayerTilesList[i] * 0x26 + ii]);
                            tileset2.Add(tileset2[SplitLayerTilesList[i] * 0x26 + ii]);
                        }
                        tcount++;
                        tcount++;
                    }

                    for (int i = 0; i < 0x400 - tcount; i++) {
                        for (int ii = 0; ii < 0x26; ii++) {
                            tileset1.Add(0x00);
                            tileset2.Add(0x00);
                        }
                    }

                    memoryStream.Write(tileset1.ToArray(), 0, tileset1.Count);
                    memoryStream.Write(tileset2.ToArray(), 0, tileset2.Count);

                    using (RSDKv5.Writer writer = new RSDKv5.Writer(fileStream)) {
                        writer.WriteCompressed(memoryStream.ToArray());
                    }
                }
            }
        }

        public static void GenerateSceneBinRSDK(
    IniGroup iniLevel,
    string outFolderName,
    int[] TilePriorityConfig,
    Dictionary<int, int> SplitLayerTiles,
    Dictionary<int, int> TilesAnimedList,
    List<AnimatedTiles> AnimTiles,
    int ZoneID,
    int Act,
    byte[] tileData,
    byte[] animTileData,
    byte[] blocksData, string iniName)
        {

            List<int> rem = new List<int>();
            foreach (AnimatedTiles a in AnimTiles)
            {
                if (a.OnlyVisual) rem.Add(AnimTiles.IndexOf(a));
            }
            rem.Reverse();
            foreach (int a in rem)
            {
                AnimTiles.RemoveAt(a);
            }

            byte[] layoutData = File.ReadAllBytes(Globals.ROOT + FileInfo.Load(iniLevel["layout"])[0].Filename);
            byte[] chunkData = new byte[0];

            FileInfo[] fileInfos = FileInfo.Load(iniLevel["chunks"]);
            for (int i = 0; i < fileInfos.Length; i++)
                chunkData = chunkData.Concat(Kosinski.Decompress(Globals.ROOT + fileInfos[i].Filename)).ToArray();

            byte[] fillerChunkData = new byte[0x100 * 128 - chunkData.Length];
            chunkData = chunkData.Concat(fillerChunkData).ToArray();

            int foregroundWidth = (layoutData[0] << 8) + layoutData[1];
            int backgroundWidth = (layoutData[2] << 8) + layoutData[3];
            int foregroundHeight = (layoutData[4] << 8) + layoutData[5];
            int backgroundHeight = (layoutData[6] << 8) + layoutData[7];

            bool patchChunks = true;
            if (patchChunks)
            {
                if (ZoneID == 0 && Act == 1)
                {
                    int us = 0x2A;
                    us = us * 128;
                    for (int i = us; i < us + 128; i += 2)
                    {
                        int word = (chunkData[i] << 8) + chunkData[i + 1];
                        if ((word >> 14 & 0x3) == 1)
                            word |= 3 << 14;
                        if ((word >> 12 & 0x3) == 1)
                            word |= 3 << 12;
                        chunkData[i] = (byte)(word >> 8);
                        chunkData[i + 1] = (byte)(word & 0xFF);
                    }
                    us = 0x2B;
                    us = us * 128;
                    for (int i = us; i < us + 128; i += 2)
                    {
                        int word = (chunkData[i] << 8) + chunkData[i + 1];
                        if ((word >> 14 & 0x3) == 1)
                            word |= 3 << 14;
                        if ((word >> 12 & 0x3) == 1)
                            word |= 3 << 12;
                        chunkData[i] = (byte)(word >> 8);
                        chunkData[i + 1] = (byte)(word & 0xFF);
                    }
                }
            }

            using (FileStream fileStream = new FileStream(Globals.OUT + outFolderName + "\\SceneRS.bin", FileMode.OpenOrCreate))
            {
                RSDKv5.Scene scene = new RSDKv5.Scene();
                // scene.MAGIC = new byte[] { (byte)'U', (byte)'C', (byte)'D', (byte)'\0' };
                scene.EditorMetadata.BinName = outFolderName;

                RSDKv5.SceneLayer background = new RSDKv5.SceneLayer("Background", (ushort)(backgroundWidth * 8), (ushort)(backgroundHeight * 8));
                background.Behaviour = 0;
                background.RelativeSpeed = 0x0100;
                background.ConstantSpeed = 0x0000;
                background.ResetParallax();
                background.AddParallax(0x7FFF, 0x20, 0x00, 0x69, false);
                for (int x = 0; x < backgroundWidth; x++)
                {
                    for (int y = 0; y < backgroundHeight; y++)
                    {
                        int us = layoutData[(layoutData[10 + y * 4] << 8) + layoutData[11 + y * 4] - 0x8000 + x];
                        int sx = x * 8;
                        int sy = y * 8;
                        us = us * 128;
                        for (int i = us; i < us + 128; i += 2)
                        {
                            int word = (chunkData[i] << 8) + chunkData[i + 1];
                            int rel = i - us;
                            int nx = sx + (rel / 2) % 8;
                            int ny = sy + (rel / 2) / 8;
                            background.Tiles[ny][nx] = (ushort)word;
                        }
                    }
                }
                scene.Layers.Add(background);

                RSDKv5.SceneLayer foreground1 = new RSDKv5.SceneLayer("FG Low", (ushort)(foregroundWidth * 8), (ushort)(foregroundHeight * 8));
                foreground1.DrawingOrder = 0x01;
                foreground1.Behaviour = 0;
                foreground1.RelativeSpeed = 0x0100;
                foreground1.ConstantSpeed = 0x0000;
                foreground1.ResetParallax();
                foreground1.AddParallax(0x7FFF, 0x100, 0x00, 0x69, false);
                for (int x = 0; x < foregroundWidth; x++)
                {
                    for (int y = 0; y < foregroundHeight; y++)
                    {
                        int us = layoutData[(layoutData[8 + y * 4] << 8) + layoutData[9 + y * 4] - 0x8000 + x];
                        int sx = x * 8;
                        int sy = y * 8;
                        us = us * 128;
                        for (int i = us; i < us + 128; i += 2)
                        {
                            int word = (chunkData[i] << 8) + chunkData[i + 1];
                            int rel = i - us;
                            int nx = sx + (rel / 2) % 8;
                            int ny = sy + (rel / 2) / 8;
                            if (TilePriorityConfig[word & 0x3FF] == 0x0)
                            {
                                foreground1.Tiles[ny][nx] = (ushort)word;
                            }
                            else if (SplitLayerTiles.ContainsKey((word & 0x3FF) | 0x0000))
                            {
                                foreground1.Tiles[ny][nx] = (ushort)((word & 0xFC00) | SplitLayerTiles[(word & 0x3FF) | 0x0000]);
                            }
                            else
                            {
                                foreground1.Tiles[ny][nx] = 0x0000;
                            }
                        }
                    }
                }
                scene.Layers.Add(foreground1);

                RSDKv5.SceneLayer foreground2 = new RSDKv5.SceneLayer("FG High", (ushort)(foregroundWidth * 8), (ushort)(foregroundHeight * 8));
                foreground2.DrawingOrder = 0x01;
                foreground2.Behaviour = 0;
                foreground2.RelativeSpeed = 0x0100;
                foreground2.ConstantSpeed = 0x0000;
                foreground2.ResetParallax();
                foreground2.AddParallax(0x7FFF, 0x100, 0x00, 0x69, false);
                for (int x = 0; x < foregroundWidth; x++)
                {
                    for (int y = 0; y < foregroundHeight; y++)
                    {
                        int us = layoutData[(layoutData[8 + y * 4] << 8) + layoutData[9 + y * 4] - 0x8000 + x];
                        int sx = x * 8;
                        int sy = y * 8;
                        us = us * 128;
                        for (int i = us; i < us + 128; i += 2)
                        {
                            int word = (chunkData[i] << 8) + chunkData[i + 1];
                            int rel = i - us;
                            int nx = sx + (rel / 2) % 8;
                            int ny = sy + (rel / 2) / 8;
                            if (TilePriorityConfig[word & 0x3FF] == 0xF)
                            {
                                foreground2.Tiles[ny][nx] = (ushort)word;
                            }
                            else if (SplitLayerTiles.ContainsKey((word & 0x3FF) | 0xF000))
                            {
                                foreground2.Tiles[ny][nx] = (ushort)((word & 0xFC00) | SplitLayerTiles[(word & 0x3FF) | 0xF000]);
                            }
                            else
                            {
                                foreground2.Tiles[ny][nx] = 0x0000;
                            }
                        }
                    }
                }
                scene.Layers.Add(foreground2);

                if (File.Exists("Patches/PatchBGParallax_" + outFolderName + ".txt"))
                {
                    Dictionary<string, int> labels = new Dictionary<string, int>();
                    for (int i = 0; i < scene.Layers.Count; i++)
                    {
                        labels[scene.Layers[i].Name] = i;
                    }

                    string pattern;
                    Match args;

                    Console.WriteLine("'PatchBGParallax_" + outFolderName + ".txt' found!");
                    string[] fileLines = File.ReadAllLines("Patches/PatchBGParallax_" + outFolderName + ".txt");

                    foreach (string line in fileLines)
                    {
                        if (line == "") continue;
                        if (line[0] == '#') continue;

                        if (line.StartsWith("RELATY"))
                        {
                            pattern = @"RELATY (.+),([A-Fa-f0-9]+)$";
                            args = Regex.Match(line, pattern);

                            scene.Layers[labels[args.Groups[1].Value]].RelativeSpeed = Convert.ToInt16(args.Groups[2].Value, 16);
                        }
                        else if (line.StartsWith("CONSTY"))
                        {
                            pattern = @"CONSTY (.+),([A-Fa-f0-9]+)";
                            args = Regex.Match(line, pattern);

                            scene.Layers[labels[args.Groups[1].Value]].ConstantSpeed = Convert.ToInt16(args.Groups[2].Value, 16);
                        }
                        else if (line.StartsWith("COPY"))
                        {
                            pattern = @"COPY (.+),(.+)";
                            args = Regex.Match(line, pattern);

                            RSDKv5.SceneLayer copy = scene.Layers[labels[args.Groups[1].Value]].Clone();
                            copy.Name = args.Groups[2].Value;

                            int src = labels[args.Groups[1].Value];

                            for (int i = src + 1; i < scene.Layers.Count; i++)
                            {
                                labels[scene.Layers[i].Name]++;
                            }

                            scene.Layers.Insert(src + 1, copy);
                            labels[args.Groups[2].Value] = src + 1;
                        }
                        else if (line.StartsWith("RENAME"))
                        {
                            pattern = @"RENAME (.+),(.+)";
                            args = Regex.Match(line, pattern);

                            labels[args.Groups[2].Value] = labels[args.Groups[1].Value];

                            scene.Layers[labels[args.Groups[1].Value]].Name = args.Groups[2].Value;
                        }
                        else if (line.StartsWith("VISIBLE"))
                        {
                            pattern = @"VISIBLE (.+),([A-Fa-f0-9]+)";
                            args = Regex.Match(line, pattern);

                            // scene.Layers[labels[args.Groups[1].Value]].Name = args.Groups[2].Value;
                        }
                        else if (line.StartsWith("PARARESET"))
                        {
                            pattern = @"PARARESET (.+)";
                            args = Regex.Match(line, pattern);

                            scene.Layers[labels[args.Groups[1].Value]].ResetParallax();
                        }
                        else if (line.StartsWith("PARA"))
                        {
                            pattern = @"PARA (.+),([A-Fa-f0-9]+),([A-Fa-f0-9]+),([A-Fa-f0-9]+),([A-Fa-f0-9]+),([A-Fa-f0-9]+)";
                            args = Regex.Match(line, pattern);

                            scene.Layers[labels[args.Groups[1].Value]].AddParallax(
                                Convert.ToUInt16(args.Groups[2].Value, 16),
                                Convert.ToUInt16(args.Groups[3].Value, 16),
                                Convert.ToUInt16(args.Groups[4].Value, 16),
                                Convert.ToUInt16(args.Groups[5].Value, 16),
                                Convert.ToUInt16(args.Groups[6].Value, 16) == 1);
                        }
                        else if (line.StartsWith("CROP"))
                        {
                            pattern = @"CROP (.+),([A-Fa-fx0-9]+),([A-Fa-fx0-9]+),([A-Fa-fx0-9]+),([A-Fa-fx0-9]+)";
                            args = Regex.Match(line, pattern);

                            scene.Layers[labels[args.Groups[1].Value]].CropTo(
                                ParseInt(args.Groups[2].Value),
                                ParseInt(args.Groups[3].Value),
                                ParseInt(args.Groups[4].Value),
                                ParseInt(args.Groups[5].Value));
                        }
                        else if (line.StartsWith("DELTILES"))
                        {
                            pattern = @"DELTILES (.+),([A-Fa-fx0-9]+),([A-Fa-fx0-9]+),([A-Fa-fx0-9]+),([A-Fa-fx0-9]+)";
                            args = Regex.Match(line, pattern);

                            scene.Layers[labels[args.Groups[1].Value]].Remove(
                                ParseInt(args.Groups[2].Value),
                                ParseInt(args.Groups[3].Value),
                                ParseInt(args.Groups[4].Value),
                                ParseInt(args.Groups[5].Value));
                        }
                        else if (line.StartsWith("MOVE "))
                        {
                            pattern = @"MOVE (.+),([A-Fa-fx0-9]+),([A-Fa-fx0-9]+)";
                            args = Regex.Match(line, pattern);

                            scene.Layers[labels[args.Groups[1].Value]].Move(
                                ParseInt(args.Groups[2].Value),
                                ParseInt(args.Groups[3].Value));
                        }
                        else if (line.StartsWith("MOVETOFRONT "))
                        {
                            pattern = @"MOVETOFRONT (.+)";
                            args = Regex.Match(line, pattern);

                            RSDKv5.SceneLayer layer = scene.Layers[labels[args.Groups[1].Value]];
                            scene.Layers.RemoveAt(labels[args.Groups[1].Value]);
                            scene.Layers.Add(layer);

                            for (int i = 0; i < scene.Layers.Count; i++)
                            {
                                labels[scene.Layers[i].Name] = i;
                            }
                        }
                    }
                }

                ushort SlotID = 0;

                RSDKv5.SceneObject playerObjects = new RSDKv5.SceneObject(new RSDKv5.NameIdentifier("PlayerSpawn"), new List<RSDKv5.AttributeInfo>());
                playerObjects.Attributes.Add(new RSDKv5.AttributeInfo("Filter", RSDKv5.AttributeTypes.UINT8));
                playerObjects.Attributes.Add(new RSDKv5.AttributeInfo("Subtype", RSDKv5.AttributeTypes.UINT8));
                playerObjects.Attributes.Add(new RSDKv5.AttributeInfo("FlipX", RSDKv5.AttributeTypes.BOOL));
                playerObjects.Attributes.Add(new RSDKv5.AttributeInfo("FlipY", RSDKv5.AttributeTypes.BOOL));
                playerObjects.Attributes.Add(new RSDKv5.AttributeInfo("CharacterID", RSDKv5.AttributeTypes.VAR));

                // Write Start Positions
                byte[] startPosDataSonic = File.ReadAllBytes(Globals.ROOT + FileInfo.Load(iniLevel["startpos"])[0].Filename);
                Array.Reverse(startPosDataSonic);
                byte[] startPosDataKnux = File.ReadAllBytes(Globals.ROOT + FileInfo.Load(iniLevel["startpos"])[1].Filename);
                Array.Reverse(startPosDataKnux);

                RSDKv5.SceneEntity startPosSonicTails = new RSDKv5.SceneEntity(playerObjects, SlotID++);
                startPosSonicTails.Position.X.High = (short)BitConverter.ToUInt16(startPosDataSonic, 2);
                startPosSonicTails.Position.Y.High = (short)BitConverter.ToUInt16(startPosDataSonic, 0);
                startPosSonicTails.Attributes[0].ValueUInt8 = 0xFF;
                startPosSonicTails.Attributes[4] = new RSDKv5.AttributeValue(RSDKv5.AttributeTypes.VAR);
                startPosSonicTails.Attributes[4].ValueVar = 0b00011011;
                playerObjects.Entities.Add(startPosSonicTails);

                RSDKv5.SceneEntity startPosSonicKnux = new RSDKv5.SceneEntity(playerObjects, SlotID++);
                startPosSonicKnux.Position.X.High = (short)BitConverter.ToUInt16(startPosDataKnux, 2);
                startPosSonicKnux.Position.Y.High = (short)BitConverter.ToUInt16(startPosDataKnux, 0);
                startPosSonicKnux.Attributes[0].ValueUInt8 = 0xFF;
                startPosSonicKnux.Attributes[4] = new RSDKv5.AttributeValue(RSDKv5.AttributeTypes.VAR);
                startPosSonicKnux.Attributes[4].ValueVar = 0b00000100;
                playerObjects.Entities.Add(startPosSonicKnux);

                scene.Objects.Add(playerObjects);


                // Write Ring Data
                byte[] ringData = File.ReadAllBytes(Globals.ROOT + FileInfo.Load(iniLevel["rings"])[0].Filename);
                int ringDataCount = ringData.Length / 4 - 1;

                RSDKv5.SceneObject ringObjects = new RSDKv5.SceneObject(new RSDKv5.NameIdentifier("Ring"), new List<RSDKv5.AttributeInfo>());
                ringObjects.Attributes.Add(new RSDKv5.AttributeInfo(new RSDKv5.NameIdentifier("Filter"), RSDKv5.AttributeTypes.UINT8));
                ringObjects.Attributes.Add(new RSDKv5.AttributeInfo(new RSDKv5.NameIdentifier("Type"), RSDKv5.AttributeTypes.VAR));
                ringObjects.Attributes.Add(new RSDKv5.AttributeInfo(new RSDKv5.NameIdentifier("PlaneFilter"), RSDKv5.AttributeTypes.VAR));
                ringObjects.Attributes.Add(new RSDKv5.AttributeInfo(new RSDKv5.NameIdentifier("MoveType"), RSDKv5.AttributeTypes.VAR));
                ringObjects.Attributes.Add(new RSDKv5.AttributeInfo(new RSDKv5.NameIdentifier("Amplitude"), RSDKv5.AttributeTypes.POSITION));
                ringObjects.Attributes.Add(new RSDKv5.AttributeInfo(new RSDKv5.NameIdentifier("Speed"), RSDKv5.AttributeTypes.VAR));
                ringObjects.Attributes.Add(new RSDKv5.AttributeInfo(new RSDKv5.NameIdentifier("Angle"), RSDKv5.AttributeTypes.INT32));

                using (MemoryStream ringStream = new MemoryStream(ringData))
                {
                    for (int i = 0; i < ringDataCount; i++)
                    {
                        short x = (short)BigEndian.Read2(ringStream);
                        short y = (short)BigEndian.Read2(ringStream);

                        if (i == 0) continue; // remove TOp Left ring

                        RSDKv5.SceneEntity ringEntity = new RSDKv5.SceneEntity(ringObjects, SlotID++);
                        ringEntity.Position.X.High = x;
                        ringEntity.Position.Y.High = y;
                        ringEntity.Attributes[0].ValueUInt8 = 0xFF;
                        ringObjects.Entities.Add(ringEntity);
                    }
                }

                scene.Objects.Add(ringObjects);


                // Write Object Data
                /*
                byte[] objectData = File.ReadAllBytes(Globals.ROOT + FileInfo.Load(iniLevel["objects"])[0].Filename);
                int objectDataCount = objectData.Length / 6 - 1;

                LittleEndian.Write2(fileStream, (ushort)objectDataCount);
                fileStream.Write(objectData, 0, objectDataCount * 6);
                //*/

                string filepath = "";

                switch (User)
                {
                    case 0:
                        filepath =  @"C:\Users\Justin\skdisasm-master\SonLVL INI Files\";
                        break;
                    case 1:

                        break;
                    case 2:
                        filepath = @"C:\Users\owner\Documents\Fan Games\3mZones\Sonic 3\SonLVL INI Files";
                        break;
                }
                string filename = lvlIDs[ZoneID] + "\\" + Act + ".ini";
                string RSDKfolderID = outFolderName;

                if (!File.Exists(Path.Combine(filepath, filename)))
                    filename = lvlIDs[ZoneID] + "\\Main.ini";

                bool andknux = ZoneID >= 6;
                bool andknuxobjects = andknux;
                if (lvlIDs[ZoneID] == "FBZ")
                    andknuxobjects = false;

                string ogDirectory = Environment.CurrentDirectory;

                Environment.CurrentDirectory = filepath;
                LevelData.UnknownSprite = new Sprite(new BitmapBits(new Bitmap(32, 32, PixelFormat.Format8bppIndexed)));
                LevelData.Game = GameInfo.Load(Path.Combine(filepath, "SonLVL.ini"));
                LevelData.LoadLevel((andknux ? @"Sonic & Knuckles\" : @"Sonic 3\") + iniName, true);

                INIObjDefs = new Dictionary<string, ObjectData>();
                Dictionary<string, ObjectData> obj;

                if (File.Exists(Path.Combine(filepath, filename)))
                {
                    obj = IniSerializer.Deserialize<Dictionary<string, ObjectData>>(Path.Combine(filepath, filename));
                    foreach (KeyValuePair<string, ObjectData> group in obj)
                    {
                        group.Value.Init();
                        INIObjDefs[group.Key] = group.Value;
                    }
                }

                obj = IniSerializer.Deserialize<Dictionary<string, ObjectData>>(Path.Combine(filepath, "Common/Main.ini")); // Global.ini
                foreach (KeyValuePair<string, ObjectData> group in obj)
                {
                    group.Value.Init();
                    INIObjDefs[group.Key] = group.Value;
                }

                obj = IniSerializer.Deserialize<Dictionary<string, ObjectData>>(Path.Combine(filepath, "Common/Global.ini")); // Global.ini
                foreach (KeyValuePair<string, ObjectData> group in obj)
                {
                    group.Value.Init();
                    INIObjDefs[group.Key] = group.Value;
                }

                if (File.Exists(Path.Combine(filepath, lvlIDs[ZoneID] + "\\Main.ini")))
                {
                    obj = IniSerializer.Deserialize<Dictionary<string, ObjectData>>(Path.Combine(filepath, lvlIDs[ZoneID] + "\\Main.ini")); // ZONE/Main.ini
                    foreach (KeyValuePair<string, ObjectData> group in obj)
                    {
                        group.Value.Init();
                        INIObjDefs[group.Key] = group.Value;
                    }
                }

                if (File.Exists(Path.Combine(filepath, lvlIDs[ZoneID] + "\\S3.ini")))
                {
                    obj = IniSerializer.Deserialize<Dictionary<string, ObjectData>>(Path.Combine(filepath, lvlIDs[ZoneID] + "\\S3.ini")); // ZONE/S3.ini
                    foreach (KeyValuePair<string, ObjectData> group in obj)
                    {
                        group.Value.Init();
                        INIObjDefs[group.Key] = group.Value;
                    }
                }

                List<KeyValuePair<byte, ObjectDefinition>> objdefs = new List<KeyValuePair<byte, ObjectDefinition>>();
                foreach (KeyValuePair<string, ObjectData> group in INIObjDefs)
                {
                    if (group.Value.ArtCompression == CompressionType.Invalid)
                        group.Value.ArtCompression = CompressionType.Nemesis;
                    if (byte.TryParse(group.Key, System.Globalization.NumberStyles.HexNumber, System.Globalization.NumberFormatInfo.InvariantInfo, out byte ID))
                    {
                        ObjectDefinition def = null;
                        if (group.Value.CodeFile != null)
                        {
                            string fulltypename = group.Value.CodeType;
                            string dllfile = Path.Combine("dllcache", fulltypename + ".dll");
                            DateTime modDate = DateTime.MinValue;
                            if (File.Exists(dllfile))
                                modDate = File.GetLastWriteTime(dllfile);
                            string fp = Path.Combine(filepath, group.Value.CodeFile.Replace('/', Path.DirectorySeparatorChar));
                            // Console.WriteLine("Loading ObjectDefinition type " + fulltypename + " from \"" + fp + "\"...");

                            if (modDate >= File.GetLastWriteTime(fp) & modDate > File.GetLastWriteTime(Application.ExecutablePath))
                            {
                                // Console.WriteLine("Loading type from cached assembly \"" + dllfile + "\"...");
                                def = (ObjectDefinition)Activator.CreateInstance(System.Reflection.Assembly.LoadFile(Path.Combine(filepath, dllfile)).GetType(fulltypename));
                            }
                            else
                            {
                                Console.WriteLine("Compiling code file...");
                                string ext = Path.GetExtension(fp);
                                CodeDomProvider pr = null;
                                switch (ext.ToLowerInvariant())
                                {
                                    case ".cs":
                                        pr = new Microsoft.CSharp.CSharpCodeProvider();
                                        break;
                                    case ".vb":
                                        pr = new Microsoft.VisualBasic.VBCodeProvider();
                                        break;
                                }

                                if (pr != null)
                                {
                                    CompilerParameters para = new CompilerParameters(new string[] {
                                    "System.dll",
                                    "System.Core.dll",
                                    "System.Drawing.dll",
                                    System.Reflection.Assembly.GetAssembly(typeof(Block)).Location,
                                    System.Reflection.Assembly.GetExecutingAssembly().Location,
                                })
                                    {
                                        GenerateExecutable = false,
                                        GenerateInMemory = false,
                                        IncludeDebugInformation = true,
                                        OutputAssembly = Path.Combine(Environment.CurrentDirectory, dllfile),
                                    };
                                    CompilerResults res = pr.CompileAssemblyFromFile(para, fp);
                                    if (res.Errors.HasErrors)
                                    {
                                        Console.WriteLine("Compile failed.", "Errors:");
                                        foreach (CompilerError item in res.Errors)
                                            Console.WriteLine(item.ToString());
                                        Console.WriteLine(string.Empty);
                                        def = new DefaultObjectDefinition();
                                    }
                                    else
                                    {
                                        Console.WriteLine("Compile succeeded.");
                                        def = (ObjectDefinition)Activator.CreateInstance(res.CompiledAssembly.GetType(fulltypename));
                                    }
                                }
                                else
                                    def = new DefaultObjectDefinition();
                            }
                        }
                        else if (group.Value.XMLFile != null)
                            def = new XMLObjectDefinition();
                        else
                            def = new DefaultObjectDefinition();

                        objdefs.Add(new KeyValuePair<byte, ObjectDefinition>(ID, def));
                        def.Init(group.Value);
                    }
                }

                Environment.CurrentDirectory = ogDirectory;

                List<KeyValuePair<int, string>> Objects = new List<KeyValuePair<int, string>>();
                List<int> IDs = new List<int>();

                var settings = new XmlWriterSettings()
                {
                    Indent = true,
                    IndentChars = "  "
                };

                int[] ObjectIDtoObjectDefinitionIndexMap = new int[256];

                foreach (KeyValuePair<byte, ObjectDefinition> def in objdefs)
                {
                    string ObjectName = S3Objects[def.Key];
                    if (andknuxobjects)
                        ObjectName = SKObjects[def.Key];

                    Console.WriteLine(ObjectName + " (" + def.Key.ToHex68k() + ")");

                    ObjectIDtoObjectDefinitionIndexMap[def.Key] = scene.Objects.Count;

                    IDs.Add(def.Key);

                    RSDKv5.SceneObject objDefinition = new RSDKv5.SceneObject(new RSDKv5.NameIdentifier(ObjectName), new List<RSDKv5.AttributeInfo>());
                    objDefinition.Attributes.Add(new RSDKv5.AttributeInfo("Filter", RSDKv5.AttributeTypes.UINT8));
                    objDefinition.Attributes.Add(new RSDKv5.AttributeInfo("Subtype", RSDKv5.AttributeTypes.UINT8));
                    objDefinition.Attributes.Add(new RSDKv5.AttributeInfo("FlipX", RSDKv5.AttributeTypes.BOOL));
                    objDefinition.Attributes.Add(new RSDKv5.AttributeInfo("FlipY", RSDKv5.AttributeTypes.BOOL));
                    foreach (PropertySpec n in def.Value.CustomProperties)
                    {
                        if (n.Type == typeof(bool))
                            objDefinition.Attributes.Add(new RSDKv5.AttributeInfo(n.Name.ToLower().Replace(" ", ""), RSDKv5.AttributeTypes.BOOL));
                        else
                            objDefinition.Attributes.Add(new RSDKv5.AttributeInfo(n.Name.ToLower().Replace(" ",""), RSDKv5.AttributeTypes.INT32));
                    }

                    scene.Objects.Add(objDefinition);
                }

                byte[] objectData = File.ReadAllBytes(Globals.ROOT + FileInfo.Load(iniLevel["objects"])[0].Filename);
                int objectDataCount = objectData.Length / 6 - 1;

                for (int o = 0; o < objectDataCount; o++)
                {
                    int x = objectData[o * 6 + 0] << 8 | objectData[o * 6 + 1];
                    int y = objectData[o * 6 + 2] << 8 | objectData[o * 6 + 3];
                    int ID = objectData[o * 6 + 4];
                    int SubType = objectData[o * 6 + 5];

                    bool FlipX = (y & 0x2000) != 0;
                    bool FlipY = (y & 0x4000) != 0;

                    y &= 0x1FFF;

                    byte[] objectDataData = new byte[6];
                    Array.Copy(objectData, o * 6, objectDataData, 0, 6);

                    if (IDs.Contains(ID))
                    {
                        //int idid = IDs.IndexOf(ID);

                        RSDKv5.SceneObject def = scene.Objects[ObjectIDtoObjectDefinitionIndexMap[ID]];

                        RSDKv5.SceneEntity objEntity = new RSDKv5.SceneEntity(def, SlotID++);
                        objEntity.Position.X.High = (short)x;
                        objEntity.Position.Y.High = (short)y;
                        objEntity.Attributes[0].ValueUInt8 = 0xFF;
                        objEntity.Attributes[1].ValueUInt8 = (byte)SubType;
                        objEntity.Attributes[2].ValueBool = FlipX;
                        objEntity.Attributes[3].ValueBool = FlipY;
                        def.Entities.Add(objEntity);
                    }

                }

                StreamWriter NamesWriter = new StreamWriter(File.OpenWrite(Globals.OUT + outFolderName + "\\ObjectNames.txt"));
                for (int i = 0; i < scene.Objects.Count; i++)
                {
                    NamesWriter.WriteLine(scene.Objects[i].Name.Name);
                }
                NamesWriter.Close();

                List<string> AttribNames = new List<string>();

                for (int i = 0; i < scene.Objects.Count; i++)
                {
                    for (int ii = 0; ii < scene.Objects[i].Attributes.Count; ii++)
                    {
                        if (!AttribNames.Contains(scene.Objects[i].Attributes[ii].Name.Name))
                        {
                            AttribNames.Add(scene.Objects[i].Attributes[ii].Name.Name);
                        }
                    }
                }

                NamesWriter = new StreamWriter(File.OpenWrite(Globals.OUT + outFolderName + "\\AttributeNames.txt"));
                for (int i = 0; i < AttribNames.Count; i++)
                {
                    NamesWriter.WriteLine(AttribNames[i]);
                }
                NamesWriter.Close();

                scene.Write(fileStream);

                using (FileStream fileStreamStageConfig = new FileStream(Globals.OUT + outFolderName + "\\StageConfig.bin", FileMode.OpenOrCreate))
                {
                    using (RSDKv5.Writer writer = new RSDKv5.Writer(fileStreamStageConfig))
                    {
                        fileStreamStageConfig.WriteByte((byte)'C');
                        fileStreamStageConfig.WriteByte((byte)'F');
                        fileStreamStageConfig.WriteByte((byte)'G');
                        fileStreamStageConfig.WriteByte(0);

                        fileStreamStageConfig.WriteByte(1); // UseGameObjects

                        fileStreamStageConfig.WriteByte((byte)scene.Objects.Count);
                        for (int i = 0; i < scene.Objects.Count; i++)
                        {
                            writer.WriteRSDKString(scene.Objects[i].Name.Name);
                        }

                        // Palette Tables
                        for (int i = 0; i < 8; i++)
                        {
                            // Palette Positions
                            ushort Positions = 0b0000000000000000;
                            writer.Write(Positions);
                            for (int col = 0; col < 16; col++)
                            {
                                if ((Positions & (1 << col)) != 0)
                                {
                                    for (int d = 0; d < 16; d++)
                                    {
                                        int R = 0;
                                        int G = 0;
                                        int B = 0;
                                        fileStreamStageConfig.WriteByte((byte)R);
                                        fileStreamStageConfig.WriteByte((byte)G);
                                        fileStreamStageConfig.WriteByte((byte)B);
                                    }
                                }
                            }
                        }

                        int WAVCount = 0;
                        fileStreamStageConfig.WriteByte((byte)WAVCount);
                        for (int i = 0; i < WAVCount; i++)
                        {
                            writer.WriteRSDKString("SoundEffectName.wav");
                            fileStreamStageConfig.WriteByte((byte)0); // MaxConcurrentPlay
                        }
                    }
                }



                /*

                // Write Animated Tile IsAnims
                LittleEndian.Write2(fileStream, (ushort)TilesAnimedList.Count);
                // Console.WriteLine("TilesAnimedList.Count " + TilesAnimedList.Count.ToString("X"));
                int tilerow = 0;
                for (int h = 0; h < 0x400; h++) {
                    if (TilesAnimedList.ContainsKey(h)) {
                        LittleEndian.Write2(fileStream, (ushort)h); // ID of 16x16 RSDK tile
                        // NeutralEndian.Write1(fileStream, (byte)tilerow); // row of tile on image 
                        BigEndian.Write2(fileStream, (ushort)(tilerow << 8 | TilesAnimedList[h])); // ID of anim tile in AnimTiles
                        tilerow++;
                    }
                }

                // Write Animated Tile Data
                List<int> aniPLCOffsets = new List<int>();
                Dictionary<int, AniPLC> aniTileMap = new Dictionary<int, AniPLC>();
                byte[] aniPLCdata = LevelData.ASMToBin("AniPLCs.txt", EngineVersion.S3K);
                using (MemoryStream input = new MemoryStream(aniPLCdata)) {
                    int start = 0xFFFFFFF;
                    while (input.Position != start) {
                        int frOffset = BigEndian.Read2(input);
                        aniPLCOffsets.Add(frOffset);

                        if (start > frOffset)
                            start = frOffset;
                    }
                    aniPLCOffsets.Add((int)input.Length);
                    
                    input.Seek(aniPLCOffsets[ZoneID * 2 + Act - 1], SeekOrigin.Begin);
                    int startc = aniPLCOffsets[ZoneID * 2 + Act - 1];
                    int comp = aniPLCOffsets[ZoneID * 2 + Act - 1 + 1];
                    int of = 0;
                    while (comp == input.Position)
                        comp = aniPLCOffsets[ZoneID * 2 + Act - 1 + 1 + (++of)];
                    while (input.Position != comp) {
                        AniPLC aniPLC = new AniPLC();

                        aniPLC.GlobalDuration = (short)BigEndian.Read2(input);
                        aniPLC.SourceAddr = BigEndian.Read2(input);
                        aniPLC.ID = BigEndian.Read2(input);
                        aniPLC.FrameCount = BigEndian.Read2(input);
                        aniPLC.FrameTileCount = BigEndian.Read2(input);

                        // Console.WriteLine("dc.w " + aniPLC.GlobalDuration + ",  " + aniPLC.SourceAddr.ToString("X") + ",  " + aniPLC.ID.ToString("X") + ",  " + aniPLC.FrameCount.ToString("X") + ",  " + aniPLC.FrameTileCount.ToString("X") + " ");

                        int ff = 0;
                        if (ZoneID > 9)
                            ff = (aniPLC.FrameCount & 1);

                        if (aniPLC.GlobalDuration != -1) {
                            for (int i = 0; i < aniPLC.FrameCount + ff; i++) {
                                aniPLC.Frames.Add(new AniPLC.AniPLCFrame());
                                aniPLC.Frames.Last().Offset = NeutralEndian.Read1(input);
                                aniPLC.Frames.Last().Duration = aniPLC.GlobalDuration;
                            }
                        }
                        else {
                            for (int i = 0; i < aniPLC.FrameCount + ff; i++) {
                                aniPLC.Frames.Add(new AniPLC.AniPLCFrame());
                                aniPLC.Frames.Last().Offset = NeutralEndian.Read1(input);
                                aniPLC.Frames.Last().Duration = NeutralEndian.Read1(input) + 1;
                            }
                        }

                        // AnimatedTiles a = new AnimatedTiles(aniPLC.ID, aniPLC.FrameTileCount, 0, aniPLC.FrameCount);
                        // Console.WriteLine("new AnimatedTiles(" + a.ID.ToString("X") + ", " + a.Count + ", " + a.AnimTileID + ", " + a.Frames + ");");

                        aniTileMap[aniPLC.ID] = aniPLC;
                    }

                    int animTilesCount = 0;
                    foreach (AnimatedTiles a in AnimTiles) {
                        if (a.OnlyVisual) continue;
                        animTilesCount++;
                    }

                    LittleEndian.Write2(fileStream, (ushort)animTilesCount);
                    foreach (AnimatedTiles a in AnimTiles) {
                        if (a.OnlyVisual) continue;

                        a.Frames = aniTileMap[a.ID].FrameCount;
                        LittleEndian.Write2(fileStream, (ushort)aniTileMap[a.ID].FrameCount);
                        for (int u = 0; u < aniTileMap[a.ID].FrameCount; u++) {
                            NeutralEndian.Write1(fileStream, (byte)aniTileMap[a.ID].Frames[u].Duration);
                        }
                    }

                    // Tiles are drawn;
                    // if the IsAnims[TileID] isn't 0xFFFF, TileSprite is now Anim
                    // To get Sprite UVs, IsAnims[TileID] >> 8 for the row index
                    // Frame = Data->animatedTileFrame[IsAnims[TileID] & 0xFF]
                }


                int g = 0;
                for (int h = 0; h < 0x400; h++) {
                    if (TilesAnimedList.ContainsKey(h)) {
                        AnimatedTiles a = AnimTiles[TilesAnimedList[h]];
                        if (g < aniTileMap[a.ID].FrameCount)
                            g = aniTileMap[a.ID].FrameCount;
                    }
                }

                if (TilesAnimedList.Count > 0) {
                    int roundedW = 16;
                    while (roundedW < g * 0x10)
                        roundedW *= 2;
                    int roundedH = 16;
                    while (roundedH < TilesAnimedList.Count * 0x10)
                        roundedH *= 2;
                    // Make Image
                    Bitmap aniTileImage = new Bitmap(roundedW, roundedH, PixelFormat.Format8bppIndexed);
                    int lasti = 0;
                    ColorPalette cpal = aniTileImage.Palette;
                    int[] palette = LoadPalette(Globals.ROOT + @"General\Sprites\Sonic\Palettes\SonicAndTails.bin", Globals.ROOT + FileInfo.Load(iniLevel["palette"])[1].Filename);
                    for (int i = 0; i < palette.Length; i++) {
                        cpal.Entries[i] = Color.FromArgb(palette[i] >> 16 & 0xFF, palette[i] >> 8 & 0xFF, palette[i] & 0xFF);
                        cpal.Entries[i & 0xF0] = Color.FromArgb(0, 0xFF, 0x00, 0xFF);
                        lasti = i;
                    }
                    if (iniLevel.ContainsKey("palette2")) {
                        palette = LoadPalette(null, Globals.ROOT + FileInfo.Load(iniLevel["palette2"])[1].Filename);
                        for (int i = 0; i < palette.Length; i++) {
                            cpal.Entries[i + 0x40] = Color.FromArgb(palette[i] >> 16 & 0xFF, palette[i] >> 8 & 0xFF, palette[i] & 0xFF);
                            cpal.Entries[(i + 0x40) & 0xF0] = Color.FromArgb(0, 0xFF, 0x00, 0xFF);
                            lasti = i + 0x40;
                        }
                    }
                    for (int i = lasti + 1; i < 256; i++)
                        cpal.Entries[i] = Color.FromArgb(0, 0, 0, 0);

                    aniTileImage.Palette = cpal;

                    BitmapData bmpData = aniTileImage.LockBits(new Rectangle(0, 0, aniTileImage.Width, aniTileImage.Height), ImageLockMode.WriteOnly, aniTileImage.PixelFormat);
                    IntPtr tileImagePtr = bmpData.Scan0;
                    byte[] px = new byte[bmpData.Stride * bmpData.Height];

                    tilerow = 0;
                    for (int h = 0; h < 0x400; h++) {
                        if (TilesAnimedList.ContainsKey(h)) {
                            // g.DrawImage(help, 0, tilerow * 0x10, new Rectangle(0, h << 4, 16, 16), GraphicsUnit.Pixel);
                            AnimatedTiles a = AnimTiles[TilesAnimedList[h]];
                            for (int f = 0; f < aniTileMap[a.ID].FrameCount; f++)
                                DrawBlock(h, aniTileMap[a.ID].Frames[f].Offset / aniTileMap[a.ID].FrameTileCount, f * 0x10, tilerow * 0x10, bmpData, ref px, AnimTiles, tileData, animTileData, blocksData);
                            tilerow++;
                        }
                    }
                    Marshal.Copy(px, 0, tileImagePtr, px.Length);
                    aniTileImage.UnlockBits(bmpData);

                    aniTileImage.Save(Globals.OUT + outFolderName + "\\Animated Tiles.gif", ImageFormat.Gif);
                    aniTileImage.Dispose();
                }

                //*/
            }
        }

        public static void DrawBlock(int til, int frame, int cx, int cy, BitmapData bmpData, ref byte[] px, List<AnimatedTiles> animTiles, byte[] tileData, byte[] animTileData, byte[] blocksData) {
            for (int j = 0; j < 4; j++) {
                int word = (blocksData[til * 8 + j * 2] & 0xFF) * 0x100 + (blocksData[til * 8 + j * 2 + 1] & 0xFF);
                int priorit = (word & 0x8000) >> 15;
                int pal = (word & 0x6000) >> 13;
                int flipY = (word & 0x1000) >> 12;
                int flipX = (word & 0x800) >> 11;
                int ind = word & 0x7FF;

                int x = (j % 2) * 8 + cx;
                int y = (j / 2) * 8 + cy;

                if (ind >= tileData.Length / 0x20)
                    continue;

                bool Anim = false;
                foreach (AnimatedTiles a in animTiles) {
                    if (ind >= a.ID && ind < a.ID + a.Count) {
                        ind = a.AnimTileID + (ind - a.ID) + a.Count * frame;
                        Anim = true;
                        break;
                    }
                }
                
                if (Anim)
                    DrawTile(bmpData, ref px, animTileData, ind, x, y, flipX == 1, flipY == 1, pal);
                else
                    DrawTile(bmpData, ref px, tileData, ind, x, y, flipX == 1, flipY == 1, pal);
            }
        }

        public static int[] LoadPalette(string sonicAndTailsPal, string levelPal) {
            int[] palette;
            ushort[] palEnc;
            using (MemoryStream output = new MemoryStream()) {
                if (sonicAndTailsPal != null) {
                    using (FileStream input = File.OpenRead(sonicAndTailsPal)) {
                        for (int i = 0; i < 16; i++) {
                            LittleEndian.Write2(output, BigEndian.Read2(input));
                        }
                        for (int i = 0; i < 16 && levelPal == null; i++) {
                            LittleEndian.Write2(output, BigEndian.Read2(input));
                        }
                    }
                }

                if (levelPal != null) {
                    using (FileStream input = File.OpenRead(levelPal)) {
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

            return palette;
        }
        public static byte[] LoadTiles(List<AnimationEditor.PLCRequest> requests) {
            int totalTiles  = 0;
            byte[] tileData = new byte[0];

            for (int d = 0; d < requests.Count; d++) {
                string file = requests[d].filename;

                if (totalTiles < requests[d].offset) {
                    byte[] nbs = new byte[(requests[d].offset - totalTiles) * 0x20];
                    tileData = tileData.Concat(nbs).ToArray();
                    totalTiles += nbs.Length / 0x20;
                }

                byte[] dec = null;
                if (file.Contains("\\Tiles\\"))
                    dec = ModuledKosinski.Decompress(file, Endianness.BigEndian);
                else if (file.Contains("Blocks\\"))
                    dec = Kosinski.Decompress(file);
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
                
                totalTiles += dec.Length / 0x20;
            }

            return tileData;
        }
        public static byte[] LoadBlocks(List<AnimationEditor.PLCRequest> requests) {
            int totalTiles = 0;
            byte[] tileData = new byte[0];

            for (int d = 0; d < requests.Count; d++) {
                string file = requests[d].filename;

                if (totalTiles < requests[d].offset) {
                    byte[] nbs = new byte[(requests[d].offset - totalTiles) * 8];
                    tileData = tileData.Concat(nbs).ToArray();
                    totalTiles += nbs.Length / 8;
                }

                byte[] dec = null;
                if (file.Contains("Tiles\\"))
                    dec = ModuledKosinski.Decompress(file, Endianness.BigEndian);
                else if (file.Contains("Blocks\\"))
                    dec = Kosinski.Decompress(file);
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

                totalTiles += dec.Length / 8;
            }

            return tileData;
        }

        public static void DrawTile(BitmapData bmpData, ref byte[] pixels, byte[] tileData, int id, int xpos, int ypos, bool flipX, bool flipY, int pal) {
            int tilStart = id * 0x20;
            int tilStride = 4;
            int fX = flipX ? 1 : 0;
            for (int x = 0; x < tilStride; x++) {
                for (int y = 0; y < 8; y++) {
                    try
                    {
                        int basee = tileData[tilStart + x + y * tilStride];
                        int baseY = (ypos + y) * bmpData.Stride;
                        if (flipY)
                            baseY = (ypos + 7 - y) * bmpData.Stride;
                        int bX = x;
                        if (flipX)
                            bX = (tilStride - 1 - x);

                        pal &= 3;

                        if ((((basee >> 4) + pal * 0x10) & 0xF) != 0)
                            pixels[baseY + xpos + bX * 2 + fX] = (byte)((basee >> 4) + pal * 0x10);
                        if ((((basee & 0xF) + pal * 0x10) & 0xF) != 0)
                            pixels[baseY + xpos + bX * 2 + 1 - fX] = (byte)((basee & 0xF) + pal * 0x10);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("ERROR: " + ex.Message);
                    }
                }
            }
        }
    }
}
