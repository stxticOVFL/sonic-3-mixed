#if INTERFACE

#include <Utils/Standard.h>
#include <Engine/IStreamer.h>
#include <Engine/ImageFormats/GIF.h>

class PNG {
public:
	Uint32* Colors = NULL;
	Uint32* Data = NULL;
	Uint32  Width = 0;
	Uint32  Height = 0;
	Uint32  TransparentColorIndex = 0;
	bool  indexed = false;
};
#endif

#include <Engine/IApp.h>
#include <Engine/IResources.h>

#include <Engine/ImageFormats/PNG.h>
#include <Engine/Diagnostics/Memory.h>

PUBLIC STATIC PNG* PNG::Load(const char* filename) {

	PNG* png = new PNG;
	IStreamer* stream = NULL;

	IResource* R = IResources::Load(filename);
	if (!R) {
		IApp::Print(2, "Could not open file '%s'!", filename);
		goto PNG_Load_FAIL;
	}

	stream = new IStreamer(R);
	if (!stream)
		goto PNG_Load_FAIL;

	int PNGCheck = stream->ReadByte();
	if (memcmp(stream->ReadBytes(3), "PNG", 3) != 0) {
		//NOT 'PNG', ABORT!
		IApp::Print(2, "File was not a PNG image!");
		goto PNG_Load_FAIL;
	}

	int headerChunkSize = stream->ReadInt32();
	stream->ReadBytes(4); //IHDR

	//HEADER
	Uint8* buf;
	buf = (Uint8*)stream->ReadBytes(4);
	png->Width = (buf[3] | ((int)buf[2] << 8) | ((int)buf[1] << 16) | ((int)buf[0] << 24));
	buf = (Uint8*)stream->ReadBytes(4);
	png->Height = (buf[3] | ((int)buf[2] << 8) | ((int)buf[1] << 16) | ((int)buf[0] << 24));
	Uint8 bitDepth = stream->ReadByte();
	Uint8 colourType = stream->ReadByte();
	Uint8 compressionMethod = stream->ReadByte();
	Uint8 filterMethod = stream->ReadByte();
	Uint8 interlaceMethod = stream->ReadByte();

	bool indexed = false;

	png->Data = (Uint32*)Memory::TrackedCalloc("PNG::Data", png->Width * png->Height, sizeof(Uint32));

	while (true)
	{
		stream->ReadInt32();//idk but i hate it
		buf = (Uint8*)stream->ReadBytes(4);
		int ChunkSize = (buf[3] | ((int)buf[2] << 8) | ((int)buf[1] << 16) | ((int)buf[0] << 24));
		Uint8 ChunkName[4];
		for (int i = 0; i < 4; i++)
		{
			ChunkName[i] = (char)stream->ReadByte();
		}

		if (memcmp(ChunkName, "PLTE", 4) != 0) {
			indexed = true;
			for (int p = 0; p < ChunkSize / 3; p++)
			{
				png->Colors[p] = 0;
				// Load 'red'
				png->Colors[p] |= stream->ReadByte() << 16;
				// Load 'green'
				png->Colors[p] |= stream->ReadByte() << 8;
				// Load 'blue'
				png->Colors[p] |= stream->ReadByte();
			}
		}
		else if (memcmp(ChunkName, "IDAT", 4) != 0) {
			//TO-DO: Load image data
			if (indexed)
			{

			}
			else
			{

			}

			//TEMP
			stream->ReadBytes(ChunkSize);
		}
		else if (memcmp(ChunkName, "IEND", 4) != 0) {
			//that's all folks!
			goto PNG_Load_Success;
		}
		else
		{
			//Who cares about this chunk
			stream->ReadBytes(ChunkSize);
		}

	}

	goto PNG_Load_Success;

PNG_Load_Success:
	IResources::Close(R);
	Memory::Free(buf);
	if (stream) delete stream;
	return png;

PNG_Load_FAIL:
	delete png;
	png = NULL;

	IResources::Close(R);
	if (stream) delete stream;
	return NULL;
}

PUBLIC STATIC GIF* PNG::ToGif(PNG* png) {
	if (png) {
		if (!png->indexed) {
			IApp::Print(2, "BMP Wasn't indexed! GIF can only be indexed!");
			return NULL;
		}
		GIF* gif = new GIF;
		gif->Colors = png->Colors;
		gif->Width = png->Width;
		gif->Height = png->Height;
		gif->TransparentColorIndex = png->TransparentColorIndex;
		gif->Data = (Uint8*)Memory::TrackedCalloc("PNG::Data->GIF::Data", png->Width * png->Height, sizeof(Uint8));
		for (int i = 0; i < png->Width * png->Height; i++) {
			gif->Data[i] = (Uint8)png->Data[i];
		}
		return gif;
	}
	return NULL;
}

PUBLIC PNG::~PNG() {
	if (Data != NULL)
		Memory::Free(Data);
}