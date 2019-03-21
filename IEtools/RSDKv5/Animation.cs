using SonicRetro.KensSharp;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RSDKv5 {
    // Thanks to Xeeynamo for the Animation information
    [Serializable]
    public class Animation {

        public const uint Sig = 0x00525053;
        public int FrameCount = 0;
        public List<string> SpriteSheets = new List<string>();
        public List<string> CollisionBoxes = new List<string>();
        public List<AnimationEntry> Animations = new List<AnimationEntry>();


        public void Load(BinaryReader reader) {
            if (reader.ReadUInt32() != Sig)
                throw new Exception("Invalid Signature!");
            FrameCount = reader.ReadInt32();
            int spriteSheetCount = reader.ReadByte();
            for (int i = 0; i < spriteSheetCount; ++i)
                SpriteSheets.Add(RSDKEndian.Read(reader.BaseStream));

            int collisionBoxCount = reader.ReadByte();
            for (int i = 0; i < collisionBoxCount; ++i)
                CollisionBoxes.Add(RSDKEndian.Read(reader.BaseStream));

            var animationCount = reader.ReadInt16();
            for (int i = 0; i < animationCount; ++i)
                Animations.Add(new AnimationEntry(reader, this));
        }

        public void Save(Stream writer) {
            LittleEndian.Write4(writer, Sig);

            LittleEndian.Write4(writer, FrameCount);
            NeutralEndian.Write1(writer, (byte)SpriteSheets.Count);
            for (int i = 0; i < SpriteSheets.Count; ++i)
                RSDKEndian.Write(writer, SpriteSheets[i]);

            NeutralEndian.Write1(writer, (byte)CollisionBoxes.Count);
            for (int i = 0; i < CollisionBoxes.Count; ++i)
                RSDKEndian.Write(writer, CollisionBoxes[i]);

            LittleEndian.Write2(writer, (ushort)Animations.Count);
            for (int i = 0; i < Animations.Count; ++i)
                Animations[i].Write(writer, this);
        }

        public class AnimationEntry {
            public string AnimName;
            public List<Frame> Frames = new List<Frame>();
            public int FrameLoop;
            public int FrameSpeed;
            public byte Unknown;

            public AnimationEntry(string animName) {
                AnimName = animName;
                FrameLoop = 0;
                FrameSpeed = 0;
            }

            public AnimationEntry(BinaryReader reader, Animation anim) {
                Read(reader, anim);
            }

            public AnimationEntry Read(BinaryReader reader, Animation anim) {
                AnimName = RSDKEndian.Read(reader.BaseStream);
                short frameCount = reader.ReadInt16();
                FrameSpeed = reader.ReadInt16();
                FrameLoop = reader.ReadByte();
                Unknown = reader.ReadByte();
                for (int i = 0; i < frameCount; ++i) {
                    Frames.Add(Frame.ReadFrame(reader, anim));
                }
                return this;
            }

            public AnimationEntry Write(Stream writer, Animation anim) {
                RSDKEndian.Write(writer, AnimName);
                LittleEndian.Write2(writer, (ushort)Frames.Count);
                LittleEndian.Write2(writer, (ushort)FrameSpeed);
                NeutralEndian.Write1(writer, (byte)FrameLoop);
                NeutralEndian.Write1(writer, (byte)Unknown);
                for (int i = 0; i < Frames.Count; ++i) {
                    Frame.WriteFrame(writer, anim, this, i);
                }
                return this;
            }
        }

        public class Frame {
            public List<HitBox> HitBoxes = new List<HitBox>();
            public int SpriteSheet = 0;
            public int CollisionBox = 0;
            public int Duration = 0;
            public int ID = 0;
            public int X = 0;
            public int Y = 0;
            public int Width = 0;
            public int Height = 0;
            public int CenterX = 0;
            public int CenterY = 0;

            public static Frame ReadFrame(BinaryReader reader, Animation anim) {
                var frame = new Frame();
                frame.SpriteSheet = reader.ReadByte();
                frame.CollisionBox = 0;
                frame.Duration = reader.ReadInt16();
                frame.ID = reader.ReadInt16();
                frame.X = reader.ReadInt16();
                frame.Y = reader.ReadInt16();
                frame.Width = reader.ReadInt16();
                frame.Height = reader.ReadInt16();
                frame.CenterX = reader.ReadInt16();
                frame.CenterY = reader.ReadInt16();

                for (int i = 0; i < anim.CollisionBoxes.Count; ++i) {
                    var hitBox = new HitBox();
                    hitBox.Left = reader.ReadInt16();
                    hitBox.Top = reader.ReadInt16();
                    hitBox.Right = reader.ReadInt16();
                    hitBox.Bottom = reader.ReadInt16();
                    frame.HitBoxes.Add(hitBox);
                }
                return frame;
            }

            public static Frame WriteFrame(Stream writer, Animation anim, AnimationEntry anime, int index) {
                var frame = anime.Frames[index];
                writer.WriteByte((byte)frame.SpriteSheet);
                // frame.CollisionBox = 0;
                LittleEndian.Write2(writer, (ushort)frame.Duration);
                LittleEndian.Write2(writer, (ushort)frame.ID);
                LittleEndian.Write2(writer, (ushort)frame.X);
                LittleEndian.Write2(writer, (ushort)frame.Y);
                LittleEndian.Write2(writer, (ushort)frame.Width);
                LittleEndian.Write2(writer, (ushort)frame.Height);
                LittleEndian.Write2(writer, (ushort)frame.CenterX);
                LittleEndian.Write2(writer, (ushort)frame.CenterY);

                for (int i = 0; i < frame.HitBoxes.Count; ++i) {
                    var hitBox = frame.HitBoxes[i];
                    LittleEndian.Write2(writer, (ushort)hitBox.Left);
                    LittleEndian.Write2(writer, (ushort)hitBox.Top);
                    LittleEndian.Write2(writer, (ushort)hitBox.Right);
                    LittleEndian.Write2(writer, (ushort)hitBox.Bottom);
                }
                return frame;
            }

            public Frame Clone() {
                Frame frame = new Frame();
                frame.SpriteSheet = SpriteSheet;
                frame.CollisionBox = CollisionBox;
                frame.Duration = Duration;
                frame.ID = ID;
                frame.X = X;
                frame.Y = Y;
                frame.Width = Width;
                frame.Height = Height;
                frame.CenterX = CenterX;
                frame.CenterY = CenterY;

                for (int i = 0; i < frame.HitBoxes.Count; ++i) {
                    var hitBox = new HitBox();
                    hitBox.Left = frame.HitBoxes[i].Left;
                    hitBox.Top = frame.HitBoxes[i].Top;
                    hitBox.Right = frame.HitBoxes[i].Right;
                    hitBox.Bottom = frame.HitBoxes[i].Bottom;
                    frame.HitBoxes.Add(hitBox);
                }
                return frame;
            }

            public class HitBox {
                public int Left, Right, Top, Bottom;
            }

            /// <summary>
            /// Retrieves the PivotX value for the frame relative to its horrizontal flipping.
            /// </summary>
            /// <param name="fliph">Horizontal flip</param>
            public int RelCenterX(bool fliph) {
                return (fliph ? -(Width + CenterX) : CenterX);
            }

            /// <summary>
            /// Retrieves the PivotY value for the frame relative to its vertical flipping.
            /// </summary>
            /// <param name="flipv">Vertical flip</param>
            public int RelCenterY(bool flipv) {
                return (flipv ? -(Height + CenterY) : CenterY);
            }
        }
    }
}