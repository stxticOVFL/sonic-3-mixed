namespace SonicRetro.KensSharp {
    using System.IO;

    public static class LittleEndian {
        public static ushort Read2(Stream stream) {
            byte[] bytes = new byte[2];
            if (stream.Read(bytes, 0, 2) != 2) {
                throw new EndOfStreamException();
            }
            return (ushort)((bytes[1] << 8) | bytes[0]);
        }

        public static ushort ReadUInt16(Stream stream) {
            return Read2(stream);
        }
        public static short ReadInt16(Stream stream) {
            return (short)Read2(stream);
        }
        public static uint ReadUInt32(Stream stream) {
            byte[] bytes = new byte[4];
            if (stream.Read(bytes, 0, 4) != 4) {
                throw new EndOfStreamException();
            }
            return (uint)((bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0]);
        }
        public static int ReadInt32(Stream stream) {
            return (int)ReadUInt32(stream);
        }

        public static void Write2(Stream stream, ushort value) {
            byte[] bytes = new byte[] { (byte)(value & 0xFF), (byte)(value >> 8) };
            stream.Write(bytes, 0, 2);
        }

        public static void Write4(Stream stream, uint value) {
            byte[] bytes = new byte[] { (byte)(value & 0xFF), (byte)(value >> 8), (byte)(value >> 16), (byte)(value >> 24) };
            stream.Write(bytes, 0, 4);
        }
        public static void Write4(Stream stream, int value) {
            byte[] bytes = new byte[] { (byte)(value & 0xFF), (byte)(value >> 8), (byte)(value >> 16), (byte)(value >> 24) };
            stream.Write(bytes, 0, 4);
        }
    }
}
