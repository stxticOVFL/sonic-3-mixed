using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using SonicRetro.SonLVL.API;

namespace RSDKv5 {
    public class Scene {
        public class IObjectEntry : ObjectEntry {
            public bool LoadAnyY = false;
            public new UInt16 ID = 0;

            public override void FromBytes(byte[] bytes) {
                throw new NotImplementedException();
            }

            public override byte[] GetBytes() {
                throw new NotImplementedException();
            }
        }
        public class IRingEntry : RingEntry {
            public override void FromBytes(byte[] bytes) {
                throw new NotImplementedException();
            }

            public override byte[] GetBytes() {
                throw new NotImplementedException();
            }

            public override void UpdateSprite() {
                throw new NotImplementedException();
            }
        }

        public class SceneMetadata {
            public string LevelTitle = "";
            public byte ZoneID = 1;
            public byte Act = 1;
            public bool VisibleHUD = true;
            public string SongFile = "";
            public uint LoopPoint = 0;
            public Color BackgroundColor;

            public SceneMetadata() {
                BackgroundColor = Color.EMPTY;
            }

            internal SceneMetadata(Reader reader) {
                LevelTitle = reader.ReadRSDKString();
                ZoneID = reader.ReadByte();
                Act = reader.ReadByte();
                VisibleHUD = reader.ReadBoolean();
                SongFile = reader.ReadRSDKString();
                LoopPoint = reader.ReadUInt32();
                BackgroundColor = new Color(reader);
            }

            internal void Write(Writer writer) {
                writer.WriteRSDKString(LevelTitle);
                writer.Write(ZoneID);
                writer.Write(Act);
                writer.Write(VisibleHUD);
                writer.WriteRSDKString(SongFile);
                writer.Write(LoopPoint);
                BackgroundColor.Write(writer);
            }
        }

        public bool ImpostorScene = false;
        public bool ImpostorScene2 = false;
        public byte[] MAGIC = new byte[] { (byte)'S', (byte)'C', (byte)'N', (byte)'\0' };
        public byte[] MAGIC_UCD = new byte[] { (byte)'S', (byte)'C', (byte)'N', (byte)'\0' };
        public byte[] MAGIC_ISCN = new byte[] { (byte)'I', (byte)'S', (byte)'C', (byte)'N' };

        public int SonStartPosX = 0;
        public int SonStartPosY = 0;
        public int KnuStartPosX = 0;
        public int KnuStartPosY = 0;

        public SceneEditorMetadata EditorMetadata = null;
        public SceneMetadata Metadata = null;

        public List<SceneLayer> Layers = new List<SceneLayer>();
        public List<SceneObject> Objects = new List<SceneObject>();

        public List<IObjectEntry> ObjectEntries = new List<IObjectEntry>();
        public List<IRingEntry> RingEntries = new List<IRingEntry>();

        public List<ISCN_ObjectDefinition> ObjectDefinitions = new List<ISCN_ObjectDefinition>();

        public class ISCN_Object {
            public short X;
            public short Y;
            public byte FlipX;
            public byte FlipY;
            public byte Priority;
            public byte Unused;
            public List<int> Attributes = new List<int>();

            public ISCN_ObjectDefinition Definition = null;

            public ISCN_Object() { }
            public ISCN_Object(int acg, ISCN_ObjectDefinition Def, Stream stream) : this(acg, Def, new Reader(stream)) { }
            public ISCN_Object(ISCN_ObjectDefinition Def, Stream stream) : this(Def.AttributeCount, Def, new Reader(stream)) { }


            public ISCN_Object Copy() {
                ISCN_Object copy = new ISCN_Object();
                copy.X = X;
                copy.Y = Y;
                copy.FlipX = FlipX;
                copy.FlipY = FlipY;
                copy.Priority = Priority;
                copy.Unused = Unused;
                for (int i = 0; i < Attributes.Count; ++i)
                    copy.Attributes.Add(Attributes[i]);

                copy.Definition = Definition;
                return copy;
            }

            internal ISCN_Object(int AttributeCount, ISCN_ObjectDefinition Def, Reader reader) {
                X = reader.ReadInt16();
                Y = reader.ReadInt16();
                FlipX = reader.ReadByte();
                FlipY = reader.ReadByte();
                Priority = reader.ReadByte();
                Unused = reader.ReadByte();
                for (int i = 0; i < AttributeCount; ++i)
                    Attributes.Add(reader.ReadInt32());

                Definition = Def;
            }

            internal void Write(Writer writer) {
                writer.Write(X);
                writer.Write(Y);
                writer.Write(FlipX);
                writer.Write(FlipY);
                writer.Write(Priority);
                writer.Write(Unused);
                for (int i = 0; i < Attributes.Count; ++i)
                    writer.Write(Attributes[i]);
            }
        }
        public class ISCN_ObjectDefinition {
            public UInt32                           ObjectHash;
            public string                           ObjectName;
            public byte                             AttributeCount;
            public List<byte>                       AttributeTypes = new List<byte>();
            public List<ISCN_Object>                ObjectList = new List<ISCN_Object>();

            public ISCN_ObjectDefinition() { }
            public ISCN_ObjectDefinition(Stream stream) : this(new Reader(stream)) { }
            internal ISCN_ObjectDefinition(Reader reader) {
                ObjectHash = reader.ReadUInt32(); // Read Object Hash
                ObjectName = reader.ReadRSDKString();

                AttributeCount = reader.ReadByte();
                for (int i = 0; i < AttributeCount; ++i)
                    AttributeTypes.Add(reader.ReadByte());

                ushort ObjectCount = reader.ReadUInt16();
                for (int i = 0; i < ObjectCount; ++i)
                    ObjectList.Add(new ISCN_Object(AttributeCount, this, reader));
            }

            internal void Write(Writer writer) {
                writer.Write(ObjectHash);
                writer.Write(ObjectName);

                writer.Write(AttributeCount);
                for (int i = 0; i < AttributeCount; ++i)
                    writer.Write(AttributeTypes[i]);

                writer.Write((ushort)ObjectList.Count);
                for (int i = 0; i < ObjectList.Count; ++i)
                    ObjectList[i].Write(writer);
            }
        }

        public Scene() {
            EditorMetadata = new SceneEditorMetadata();
            Metadata = new SceneMetadata();
        }

        public Scene(string filename) : this(new Reader(filename)) {

        }

        public Scene(Stream stream) : this(new Reader(stream)) {

        }

        private Scene(Reader reader) {
            // Load scene
            byte[] magic = reader.ReadBytes(4);
            if (magic.SequenceEqual(MAGIC_UCD))
                ImpostorScene = true;
            else if (magic.SequenceEqual(MAGIC_ISCN))
                ImpostorScene2 = true;
            //throw new Exception("Invalid scene file header magic");

            if (ImpostorScene2)
                Metadata = new SceneMetadata(reader);
            else
                EditorMetadata = new SceneEditorMetadata(reader);

            byte layers_count = reader.ReadByte();
            for (int i = 0; i < layers_count; ++i)
                Layers.Add(new SceneLayer(reader));

            if (ImpostorScene2) {
                int ObjectDefinitionCount = reader.ReadUInt16();
                for (int i = 0; i < ObjectDefinitionCount; ++i)
                    ObjectDefinitions.Add(new ISCN_ObjectDefinition(reader));
            }
            else {
                byte objects_count = reader.ReadByte();
                for (int i = 0; i < objects_count; ++i)
                    Objects.Add(new SceneObject(reader));
            }

            if (ImpostorScene) {
                SonStartPosX = reader.ReadUInt16();
                SonStartPosY = reader.ReadUInt16();
                KnuStartPosX = reader.ReadUInt16();
                KnuStartPosY = reader.ReadUInt16();
                int ObjectCount = reader.ReadUInt16();
                for (int i = 0; i < ObjectCount; ++i) {
                    IObjectEntry entry = new IObjectEntry();
                    entry.X = (ushort)(reader.ReadByte() << 8 | reader.ReadByte()); // reader.ReadUInt16();
                    entry.Y = (ushort)(reader.ReadByte() << 8 | reader.ReadByte()); // reader.ReadUInt16();

                    entry.XFlip = (entry.Y >> 13 & 1) == 1;
                    entry.YFlip = (entry.Y >> 14 & 1) == 1;
                    entry.LoadAnyY = (entry.Y >> 15 & 1) == 1;
                    entry.Y &= 0xFFF;

                    entry.ID = reader.ReadByte(); // reader.ReadUInt16();
                    entry.SubType = reader.ReadByte();

                    ObjectEntries.Add(entry);
                }

                int RingCount = reader.ReadUInt16();
                for (int i = 0; i < RingCount; ++i) {
                    IRingEntry entry = new IRingEntry();
                    entry.X = reader.ReadUInt16();
                    entry.Y = reader.ReadUInt16();
                    RingEntries.Add(entry);
                }
            }
        }

        public void Write(string filename) {
            using (Writer writer = new Writer(filename))
                this.Write(writer);
        }

        public void Write(Stream stream) {
            Writer writer = new Writer(stream);
            this.Write(writer);
        }

        internal void Write(Writer writer) {
            writer.Write(MAGIC);

            if (ImpostorScene2)
                Metadata.Write(writer);
            else
                EditorMetadata.Write(writer);

            writer.Write((byte)Layers.Count);
            foreach (SceneLayer layer in Layers)
                layer.Write(writer);

            if (ImpostorScene2) {
                writer.Write((ushort)ObjectDefinitions.Count);
                foreach (ISCN_ObjectDefinition obj in ObjectDefinitions)
                    obj.Write(writer);
            }
            else {
                Console.WriteLine("Objects.Count: " + Objects.Count);
                writer.Write((byte)Objects.Count);
                foreach (SceneObject obj in Objects)
                    obj.Write(writer);
            }

            if (ImpostorScene) {
                writer.Write((ushort)SonStartPosX);
                writer.Write((ushort)SonStartPosY);
                writer.Write((ushort)KnuStartPosX);
                writer.Write((ushort)KnuStartPosY);

                writer.Write((ushort)ObjectEntries.Count);
                for (int i = 0; i < ObjectEntries.Count; ++i) {
                }
                writer.Write((ushort)RingEntries.Count); // Ring Count
                // write rings
            }
        }
    }
}
