#if INTERFACE

#include <Utils/Standard.h>
#include <Engine/IStreamer.h>

class GIF {
public:
    Uint32* Colors = NULL;
    Uint8*  Data = NULL;
    Uint32  Width = 0;
    Uint32  Height = 0;
    Uint32  TransparentColorIndex = 0;
	bool indexed = true;
};
#endif

#include <Engine/IApp.h>
#include <Engine/IResources.h>

#include <Engine/ImageFormats/GIF.h>
#include <Engine/Diagnostics/Memory.h>

struct Entry {
    uint8_t  Used;
    uint16_t Length;
	uint16_t Prefix;
	uint8_t  Suffix;
};
PUBLIC STATIC Uint32 GIF::ReadCode(IStreamer* stream, int codeSize, int* blockLength, int* bitCache, int* bitCacheLength) {
    if (*blockLength == 0)
        *blockLength = stream->ReadByte();

    while (*bitCacheLength <= codeSize && *blockLength > 0) {
        Uint32 byte = stream->ReadByte();
        (*blockLength)--;
        *bitCache |= byte << *bitCacheLength;
        *bitCacheLength += 8;

        if (*blockLength == 0) {
            *blockLength = stream->ReadByte();
        }
    }
    Uint32 result = *bitCache & ((1 << codeSize) - 1);
    *bitCache >>= codeSize;
    *bitCacheLength -= codeSize;

    return result;
}

PUBLIC STATIC GIF* GIF::Load(const char* filename) {
    Uint8* px;
    Entry* codeTable = (Entry*)Memory::Calloc(0x1000, sizeof(Entry));

    GIF* gif = new GIF;
    IStreamer* stream = NULL;

    IResource* R = IResources::Load(filename);
    if (!R) {
        IApp::Print(2, "Could not open file '%s'!", filename);
        goto GIF_Load_FAIL;
    }

    stream = new IStreamer(R);
    if (!stream)
        goto GIF_Load_FAIL;

    Uint8 magicGIF[3];
    stream->ReadBytesTo(magicGIF, 3);
    if (memcmp(magicGIF, "GIF", 3) != 0) {
        IApp::Print(2, "Invalid GIF file! Found \"%*.s\", expected \"GIF\"!", 3, magicGIF);
        goto GIF_Load_FAIL;
    }

    Uint8 magic89a[4];
    stream->ReadBytesTo(magic89a, 3);
    if (memcmp(magic89a, "89a", 3) != 0) {
		magic89a[3] = 0;
        // IApp::Print(2, "Invalid GIF version! Found \"%s\", expected \"89a\"! %s", magic89a, filename);
        // goto GIF_Load_FAIL;
    }

    Uint16 width, height, paletteTableSize;
    int bitsWidth, eighthHeight, quarterHeight, halfHeight;
    Uint8 logicalScreenDesc, colorBitDepth, transparentColorIndex, pixelAspectRatio;

    width = stream->ReadUInt16();
    height = stream->ReadUInt16();

    logicalScreenDesc = stream->ReadByte();

    transparentColorIndex = stream->ReadByte();
    pixelAspectRatio = stream->ReadByte();

    if ((logicalScreenDesc & 0x80) == 0) {
        IApp::Print(2, "GIF missing palette table!");
        goto GIF_Load_FAIL;
    }

    gif->Width = width;
    gif->Height = height;

    if ((width & (width - 1)) != 0) {
        IApp::Print(2, "GIF width must be power of two!");
        //goto GIF_Load_FAIL;
    }
    if ((height & (height - 1)) != 0) {
        IApp::Print(2, "GIF height must be power of two!");
        //goto GIF_Load_FAIL;
    }

    colorBitDepth = ((logicalScreenDesc & 0x70) >> 4) + 1; // normally 7, sometimes it is 4 (wrong)
    //sortFlag = (logicalScreenDesc & 0x8) != 0; // This is unneeded.
    paletteTableSize = 2 << (logicalScreenDesc & 0x7);

    gif->TransparentColorIndex = transparentColorIndex;

    // Load Palette Table
    gif->Colors = (Uint32*)Memory::TrackedCalloc("GIF::Colors", 0x100, sizeof(Uint32));
    for (int p = 0; p < paletteTableSize; p++) {
        gif->Colors[p] = 0;
        // Load 'red'
        gif->Colors[p] |= stream->ReadByte() << 16;
        // Load 'green'
        gif->Colors[p] |= stream->ReadByte() << 8;
        // Load 'blue'
        gif->Colors[p] |= stream->ReadByte();
    }

    // Prepare image data
    gif->Data = (Uint8*)Memory::TrackedCalloc("GIF::Data", width * height, sizeof(Uint8));
    px = gif->Data;

    width--;
    height--;

    eighthHeight = gif->Height >> 3;
    quarterHeight = gif->Height >> 2;
    halfHeight = gif->Height >> 1;

    // Get frame
    Uint8 type, subtype, temp;
    type = stream->ReadByte();
    while (type) {
        bool tableFull, interlaced;
        int codeSize, initCodeSize;
        int clearCode, eoiCode, emptyCode;
        int blockLength, bitCache, bitCacheLength;
        int codeToAddFrom, mark, str_len = 0, frm_off = 0;
        Uint32 currentCode;

        switch (type) {
            // Extension
            case 0x21:
                subtype = stream->ReadByte();
                switch (subtype) {
                    // Graphics Control Extension
                    case 0xF9:
                        stream->Skip(0x06);
                        // temp = stream->ReadByte();  // Block Size [byte] (always 0x04)
                        // temp = stream->ReadByte();  // Packed Field [byte] //
                        // temp16 = stream->ReadUInt16(); // Delay Time [short] //
                        // temp = stream->ReadByte();  // Transparent Color Index? [byte] //
                        // temp = stream->ReadByte();  // Block Terminator [byte] //
                        break;
                    // Plain Text Extension
                    case 0x01:
                    // Comment Extension
                    case 0xFE:
                    // Application Extension
                    case 0xFF:
                        temp = stream->ReadByte(); // Block Size
                        // Continue until we run out of blocks
                        while (temp) {
                            // Read block
                            stream->Skip(temp); // stream->ReadBytesTo(buffer, temp);
                            temp = stream->ReadByte(); // next block Size
                        }
                        break;
                    default:
                        IApp::Print(2, "Unsupported GIF control extension '%02X'!", subtype);
                        goto GIF_Load_FAIL;
                }
                break;
            // Image descriptor
            case 0x2C:
                // temp16 = stream->ReadUInt16(); // Destination X
                // temp16 = stream->ReadUInt16(); // Destination Y
                // temp16 = stream->ReadUInt16(); // Destination Width
                // temp16 = stream->ReadUInt16(); // Destination Height
                stream->Skip(8);
                temp = stream->ReadByte();    // Packed Field [byte]

                // If a local color table exists,
                if (temp & 0x80) {
                    int size = 2 << (temp & 0x07);
                    // Load all colors
                    stream->Skip(3 * size); // stream->ReadBytesTo(buffer, 3 * size);
                }

                interlaced = (temp & 0x40) == 0x40;
                if (interlaced) {
                    bitsWidth = 0;
                    while (width) {
                        width >>= 1;
                        bitsWidth++;
                    }
                    width = gif->Width - 1;
                }

                codeSize = stream->ReadByte();

                clearCode = 1 << codeSize;
                eoiCode = clearCode + 1;
                emptyCode = eoiCode + 1;

                codeSize++;
                initCodeSize = codeSize;

                // Init table
                for (int i = 0; i <= eoiCode; i++) {
                    codeTable[i].Length = 1;
                    codeTable[i].Prefix = 0xFFF;
                    codeTable[i].Suffix = (Uint8)i;
                }

                blockLength = 0;
                bitCache = 0b00000000;
                bitCacheLength = 0;
                tableFull = false;

                currentCode = ReadCode(stream, codeSize, &blockLength, &bitCache, &bitCacheLength);

                codeSize = initCodeSize;
                emptyCode = eoiCode + 1;
                tableFull = false;

                Entry entry;
                entry.Suffix = 0;

                while (blockLength) {
                    codeToAddFrom = -1;
                    mark = 0;

                    if (currentCode == clearCode) {
                        codeSize = initCodeSize;
                        emptyCode = eoiCode + 1;
                        tableFull = false;
                    }
                    else if (!tableFull) {
                        codeTable[emptyCode].Length = str_len + 1;
                        codeTable[emptyCode].Prefix = currentCode;
                        codeTable[emptyCode].Suffix = entry.Suffix;
                        emptyCode++;

                        // Once we reach highest code, increase code size
                        if ((emptyCode & (emptyCode - 1)) == 0)
                            mark = 1;
                        else
                            mark = 0;

                        if (emptyCode >= 0x1000) {
                            mark = 0;
                            tableFull = true;
                        }
                    }

                    currentCode = ReadCode(stream, codeSize, &blockLength, &bitCache, &bitCacheLength);

                    if (currentCode == clearCode) continue;
                    if (currentCode == eoiCode) goto GIF_Load_Success;
                    if (mark == 1) codeSize++;

                    entry = codeTable[currentCode];
                    str_len = entry.Length;

                    while (true) {
            			int p = frm_off + entry.Length - 1;
                        if (interlaced) {
                            int row = p >> bitsWidth;
                            if (row < eighthHeight)
                                p = (p & width) + ((((row) << 3) + 0) << bitsWidth);
                            else if (row < quarterHeight)
                                p = (p & width) + ((((row - eighthHeight) << 3) + 4) << bitsWidth);
                            else if (row < halfHeight)
                                p = (p & width) + ((((row - quarterHeight) << 2) + 2) << bitsWidth);
                            else
                                p = (p & width) + ((((row - halfHeight) << 1) + 1) << bitsWidth);
                        }

            			gif->Data[p] = entry.Suffix;
            			if (entry.Prefix != 0xFFF)
            				entry = codeTable[entry.Prefix];
            			else
            				break;
            		}
            		frm_off += str_len;
            		if (currentCode < emptyCode - 1 && !tableFull)
            			codeTable[emptyCode - 1].Suffix = entry.Suffix;
                }
                break;
        }

        type = stream->ReadByte();

        if (type == 0x3B) break;
    }

    goto GIF_Load_Success;

    GIF_Load_FAIL:
        delete gif;
        gif = NULL;

    GIF_Load_Success:
        IResources::Close(R);
        Memory::Free(codeTable);
        if (stream) delete stream;
        return gif;
}

PUBLIC GIF::~GIF() {
    if (Data != NULL)
        Memory::Free(Data);
}
