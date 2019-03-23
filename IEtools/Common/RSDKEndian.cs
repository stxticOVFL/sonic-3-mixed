namespace SonicRetro.KensSharp {
    using System.IO;
    using System.Text;

    public static class RSDKEndian {
        public static string Read(Stream stream) {
            string str = "";
            int length = stream.ReadByte();
            if (length == -1) {
                throw new EndOfStreamException();
            }
            for (int i = 0; i < length; i++) {
                char it = (char)stream.ReadByte();
                if (it > 0)
                    str += it;
            }
            return str;
        }

        public static void Write(Stream stream, string str) {
            stream.WriteByte((byte)(str.Length + 1));
            stream.Write(Encoding.Default.GetBytes(str), 0, str.Length);
            stream.WriteByte(0);
        }
    }
}
