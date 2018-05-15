using System;
using System.Text;

namespace xroad
{
    namespace car
    {
        internal class Converter
        {
            public static int to_bytes(int val, ref byte[] bytes, int offset)
            {
                bytes[0 + offset] = (byte) val;
                bytes[1 + offset] = (byte) (val >> 8);
                bytes[2 + offset] = (byte) (val >> 16);
                bytes[3 + offset] = (byte) (val >> 24);
                return 4;
            }
            public static int to_bytes(uint val, ref byte[] bytes, int offset)
            {
                bytes[0 + offset] = (byte) val;
                bytes[1 + offset] = (byte) (val >> 8);
                bytes[2 + offset] = (byte) (val >> 16);
                bytes[3 + offset] = (byte) (val >> 24);
                return 4;
            }
            public static int to_bytes(long val, ref byte[] bytes, int offset)
            {
                bytes[0 + offset] = (byte) val;
                bytes[1 + offset] = (byte) (val >> 8);
                bytes[2 + offset] = (byte) (val >> 16);
                bytes[3 + offset] = (byte) (val >> 24);
                bytes[4 + offset] = (byte) (val >> 32);
                bytes[5 + offset] = (byte) (val >> 40);
                bytes[6 + offset] = (byte) (val >> 48);
                bytes[7 + offset] = (byte) (val >> 56);
                return 8;
            }
            public static int to_bytes(ulong val, ref byte[] bytes, int offset)
            {
                bytes[0 + offset] = (byte) val;
                bytes[1 + offset] = (byte) (val >> 8);
                bytes[2 + offset] = (byte) (val >> 16);
                bytes[3 + offset] = (byte) (val >> 24);
                bytes[4 + offset] = (byte) (val >> 32);
                bytes[5 + offset] = (byte) (val >> 40);
                bytes[6 + offset] = (byte) (val >> 48);
                bytes[7 + offset] = (byte) (val >> 56);
                return 8;
            }
            public static int to_bytes(short val, ref byte[] bytes, int offset)
            {
                bytes[0 + offset] = (byte) val;
                bytes[1 + offset] = (byte) (val >> 8);
                return 8;
            }
            public static int to_bytes(ushort val, ref byte[] bytes, int offset)
            {
                bytes[0 + offset] = (byte) val;
                bytes[1 + offset] = (byte) (val >> 8);
                return 8;
            }
            public static int to_bytes(byte val, ref byte[] bytes, int offset)
            {
                bytes[0 + offset] = val;
                return 8;
            }
            public static int to_bytes(sbyte val, ref byte[] bytes, int offset)
            {
                bytes[0 + offset] = (byte) val;
                return 8;
            }
            public static int to_bytes(float val, ref byte[] bytes, int offset)
            {
                var arr = BitConverter.GetBytes(val);
                bytes[0 + offset] = arr[0];
                bytes[1 + offset] = arr[1];
                bytes[2 + offset] = arr[2];
                bytes[3 + offset] = arr[3];
                return 4;
            }
            public static int to_bytes(double val, ref byte[] bytes, int offset)
            {
                var arr = BitConverter.GetBytes(val);
                bytes[0 + offset] = arr[0];
                bytes[1 + offset] = arr[1];
                bytes[2 + offset] = arr[2];
                bytes[3 + offset] = arr[3];
                bytes[4 + offset] = arr[4];
                bytes[5 + offset] = arr[5];
                bytes[6 + offset] = arr[6];
                bytes[7 + offset] = arr[7];
                return 8;
            }
            public static int to_bytes(string val, ref byte[] bytes, int size, int offset)
            {
                var arr = Encoding.ASCII.GetBytes(val);
                var sz = Math.Min(val.Length, size);
                for(var i = 0; i < sz; ++i) bytes[i + offset] = arr[i];
                return sz;
            }
        }

        internal enum Templates : short
        {
            car = 1

        }

        /// Message Header Encoder
        internal class MessageHeaderTypeEncoder
        {
            private int size_ = 8;
            private byte[] data_;
            private readonly int offset_;

            public MessageHeaderTypeEncoder(ref byte[] data, int offset)
            {
                data_ = data;
                offset_ = offset;
            }
            public int size
            {
                get { return size_; }
            }
            public short blockLength
            {
                set { Converter.to_bytes(value, ref data_, offset_ + 0); }
            }
            public Templates templateId
            {
                set { Converter.to_bytes((short) value, ref data_, offset_ + 2); }
            }
            public short schemaId
            {
                set { Converter.to_bytes(value, ref data_, offset_ + 4); }
            }
            public short version
            {
                set { Converter.to_bytes(value, ref data_, offset_ + 6); }
            }
        }

        /// Message Header Decoder
        internal class MessageHeaderTypeDecoder
        {
            public int size_ = 8;
            private byte[] data_;

            public MessageHeaderTypeDecoder(ref byte[] data)
            {
                data_ = data;
            }
            public int size
            {
                get { return size_; }
            }
            public short blockLength
            {
                get { return BitConverter.ToInt16(data_, 0); }
            }
            public Templates templateId
            {
                get { return (Templates) BitConverter.ToInt16(data_, 2); }
            }
            public short schemaId
            {
                get { return BitConverter.ToInt16(data_, 4); }
            }
            public short version
            {
                get { return BitConverter.ToInt16(data_, 6); }
            }
        }

        /// Repeating group dimensions
        internal class GroupSizeEncodingTypeEncoder
        {
            public int size_ = 4;
            private byte[] data_;
            private readonly int offset_;
            private int var_offset_;

            public GroupSizeEncodingTypeEncoder(ref byte[] data, ref int var_offset, int offset)
            {
                data_ = data;
                offset_ = offset;
                var_offset_ = var_offset;
            }
            public int size
            {
                get { return size_; }
            }
            public short blockLength
            {
                set { Converter.to_bytes(value, ref data_, var_offset_ + offset_ + 0); }
            }
            public short numInGroup
            {
                set { Converter.to_bytes(value, ref data_, var_offset_ + offset_ + 2); }
            }
        }

        /// Repeating group dimensions
        internal class GroupSizeEncodingTypeDecoder
        {

            public int size_ = 4;
            private byte[] data_;
            private readonly int offset_;
            private int var_offset_;

            public GroupSizeEncodingTypeDecoder(ref byte[] data, ref int var_offset, int offset)
            {
                data_ = data;
                offset_ = offset;
                var_offset_ = var_offset;
            }
            public int size
            {
                get { return size_; }
            }
            public short blockLength
            {
                get { return BitConverter.ToInt16(data_, var_offset_ + offset_ + 0); }
            }
            public short numInGroup
            {
                get { return BitConverter.ToInt16(data_, var_offset_ + offset_ + 2); }
            }
        }

        /// Variable-length string encoder
        internal class VarStringTypeEncoder
        {
            public int size_ = 2;
            private byte[] data_;
            private readonly int offset_;
            private int var_offset_;

            public VarStringTypeEncoder(ref byte[] data, ref int var_offset, int offset)
            {
                data_ = data;
                offset_ = offset;
                var_offset_ = var_offset;
            }
            public int size
            {
                get { return size_; }
            }
            public string val
            {
                set
                {
                    Converter.to_bytes((ushort)value.Length, ref data_, var_offset_ + offset_ + 0);
                    Converter.to_bytes(value, ref data_, value.Length, var_offset_ + offset_ + 2);
                    size_ += value.Length;
                    var_offset_ += value.Length;
                }
            }
        }

        /// Variable-length string decoder
        internal class VarStringTypeDecoder
        {
            public int size_ = 2;
            private byte[] data_;
            private readonly int offset_;
            private int var_offset_;

            public VarStringTypeDecoder(ref byte[] data, ref int var_offset, int offset)
            {
                data_ = data;
                offset_ = offset;
                var_offset_ = var_offset;
            }
            public int size
            {
                get { return size_; }
            }
            public string val
            {
                get
                {
                    int length = BitConverter.ToUInt16(data_, var_offset_ + offset_ + 0);
                    var arr = new byte[length];
                    Array.Copy(data_, var_offset_ + offset_ + 2, arr, 0, arr.Length);
                    size_ += length;
                    var_offset_ += length;
                    return System.Text.Encoding.Default.GetString(arr);
                }
            }
        }

        internal partial class carEncoder
        {
            private byte[] data_;
            private int size_;
            private readonly int offset_;
            private int var_offset_ = 0;

            public carEncoder(ref byte[] data, int size, int offset)
            {
                data_ = data;
                size_ = size;
                offset_ = offset;
            }
            public int size
            {
                get { return size_ + 24 + var_offset_; }
            }
            // car id
            public Int32 id
            {
                set
                {
                    Converter.to_bytes(value, ref data_, var_offset_ + offset_ + 0);
                }
            }
            // car name
            public string name
            {
                set
                {
                    Converter.to_bytes(value, ref data_, 20, var_offset_ + offset_ + 4);
                }
            }
        }

        internal partial class carDecoder
        {
            private byte[] data_;
            private readonly int offset_;
            private int var_offset_ = 0;

            public carDecoder(ref byte[] data, int offset)
            {
                data_ = data;
                offset_ = offset;
            }
            // car id
            public Int32 id
            {
                get
                {
                    return BitConverter.ToInt32(data_, offset_ + 0);
                }
            }
            // car name
            public string name
            {
                get
                {
                    return Encoding.ASCII.GetString(data_, offset_ + 4, 20).TrimEnd((char)0);
                }
            }
        }

        internal class ObjectFactory
        {
            public static object createEncoder<T>(ref byte[] data, ref int size)
            {
                if(typeof(T) == typeof(carEncoder))
                {
                    MessageHeaderTypeEncoder hdr = new MessageHeaderTypeEncoder(ref data, 0);
                    hdr.blockLength = 24;
                    hdr.templateId = Templates.car;
                    hdr.schemaId = 1;
                    hdr.version = 1;
                    carEncoder obj = new carEncoder(ref data, hdr.size, hdr.size);
                    return obj;
                }
                throw new ArgumentException("unknown object type");
            }
        }
    }
} // namespace xroad