#if INTERFACE

#include <Utils/Standard.h>
#include <Engine/IStreamer.h>

class BMP {
public:
	Uint32* Colors = NULL;
	Uint32* Data = NULL;
	Uint32  Width = 0;
	Uint32  Height = 0;
	Uint32  TransparentColorIndex = 0;
	bool  indexed = true;
};
#endif

#include <Engine/IApp.h>
#include <Engine/IResources.h>

#include <Engine/ImageFormats/BMP.h>
#include <Engine/Diagnostics/Memory.h>

PUBLIC STATIC BMP* BMP::Load(const char* filename) {

	BMP* bmp = new BMP;
	IStreamer* stream = NULL;

	IResource* R = IResources::Load(filename);
	if (!R) {
		IApp::Print(2, "Could not open file '%s'!", filename);
		goto BMP_Load_FAIL;
	}

	stream = new IStreamer(R);
	if (!stream)
		goto BMP_Load_FAIL;

	stream->ReadByte(); //B(it)
	stream->ReadByte(); //M(ap)

	int BMPSIZE = stream->ReadInt32();

	int unused1 = stream->ReadInt32();

	int ImgDataOffset = stream->ReadInt32();

	int BMPHeaderSize = stream->ReadInt32();//Header size

	bmp->Width = stream->ReadInt32();
	bmp->Height = stream->ReadInt32();
	int ColourPlaneCount = stream->ReadUInt16(); //Colour Planes count (it's always 1 lmao)
	int bpp = stream->ReadUInt16();

	int CompressionType = stream->ReadInt32(); //is it compressed?
	int CompressedImageSize = stream->ReadInt32(); //if so what is the size (else 0)
	int XpixelsPerM = stream->ReadInt32(); //horizontal resolution: Pixels/meter
	int YpixelsPerM = stream->ReadInt32(); //vertical resolution: Pixels/meter
	int palCnt = stream->ReadInt32();// how many colours used
	int ImportantColours = stream->ReadInt32();

	bmp->indexed = bpp <= 8;

	int RowSize = bmp->Width;
	RowSize += RowSize % 4;

	int ArraySize = RowSize * bmp->Height;

	//Make it a UINT32 so we can store palette indexes or full colours
	bmp->Data = (Uint32*)Memory::TrackedCalloc("BMP::Data", bmp->Width * bmp->Height, sizeof(Uint32));
	Uint32* buffer = (Uint32*)Memory::TrackedCalloc("BMP::Data", bmp->Width * bmp->Height, sizeof(Uint32));

	if (bmp->indexed)
	{

		for (int p = 0; p < palCnt; p++) {
			bmp->Colors[p] = 0;
			// Load 'blue'
			bmp->Colors[p] |= stream->ReadByte();
			// Load 'green'
			bmp->Colors[p] |= stream->ReadByte() << 8;
			// Load 'red'
			bmp->Colors[p] |= stream->ReadByte() << 16;
		}

		//stream->Position = ImgDataOffset;

		for (int i = 0; i < ArraySize; i++)
		{
			buffer[i] = stream->ReadByte();
		}
	}
	else
	{
		
		switch (bpp)
		{
		case 32:
			

			for (int p = 0; p < ArraySize; p++)
			{
				buffer[p] = 0;
				// Load 'blue'
				buffer[p] |= stream->ReadByte();
				// Load 'green'
				buffer[p] |= stream->ReadByte() << 8;
				// Load 'red'
				buffer[p] |= stream->ReadByte() << 16;
				// Load 'alpha'
				buffer[p] |= stream->ReadByte() << 24;
			}

			break;
		case 24:

			for (int p = 0; p < ArraySize; p++)
			{
				buffer[p] = 0;
				// Load 'blue'
				buffer[p] |= stream->ReadByte();
				// Load 'green'
				buffer[p] |= stream->ReadByte() << 8;
				// Load 'red'
				buffer[p] |= stream->ReadByte() << 16;
				stream->ReadByte();//Unused
			}

			break;
		}
	}

	int cnt = 0;

	//Bitmaps are stored from the bottom left so this basically flips the image iirc
	for (int y = bmp->Height - 1; y > 0; y--)
	{
		for (int x = 0; x < bmp->Width; x++)
		{
			bmp->Data[(y * bmp->Width) + x] = buffer[cnt];
			cnt++;
		}
	}

	goto BMP_Load_Success;

BMP_Load_FAIL:
	delete bmp;
	bmp = NULL;

BMP_Load_Success:
	IResources::Close(R);
	Memory::Free(buffer);
	if (stream) delete stream;
	return bmp;
}

PUBLIC BMP::~BMP() {
	if (Data != NULL)
		Memory::Free(Data);
}