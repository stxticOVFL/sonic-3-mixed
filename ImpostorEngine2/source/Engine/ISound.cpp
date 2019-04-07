#if INTERFACE
#include <Utils/Standard.h>
#include <Utils/StandardSDL2.h>
#include <Engine/IApp.h>
#include <Engine/IResources.h>

class ISound {
public:
    SDL_AudioSpec     Format;

    uint32_t          Length = 0;
    uint8_t*          Buffer = NULL;
    uint32_t          Remaining = 0;

    char*             Name = NULL;

    bool              LoadFailed = false;

    bool              StreamFromFile = false;
    SDL_AudioStream*  Stream = NULL;
    IResource*        Resource = NULL;
    uint8_t*          ExtraBuffer = NULL;

    struct Vorbis {
        OggVorbis_File vf;
        vorbis_info* info = NULL;
        Uint32 audio_len;
    };

    Vorbis* vorbis_file = NULL;
};
#endif

#include <Engine/ISound.h>

struct  WAV_HEADER {	
    /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4];        // RIFF Header Magic header
    uint32_t        ChunkSize;      // RIFF Chunk Size
    uint8_t         WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4];         // FMT header
    uint32_t        Subchunk1Size;  // Size of the fmt chunk
    uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t        bytesPerSec;    // bytes per second
    uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4]; // "data"  string
    uint32_t        Subchunk2Size;  // Sampled data length
    uint8_t         padding[8]; // "data"  string
};

PRIVATE STATIC size_t ISound::StaticRead(void* ptr, size_t size, size_t nmemb, void *datasource) {
    return ((IResource*)datasource)->Read(ptr, size * nmemb); // SDL_RWread((*)datasource, ptr, size, nmemb);
}
PRIVATE STATIC int ISound::StaticSeek(void* datasource, ogg_int64_t offset, int whence) {
    // return SDL_RWseek((SDL_RWops*)datasource, (int)offset, whence);
    return ((IResource*)datasource)->Seek(offset, whence);
}
PRIVATE STATIC int ISound::StaticCloseFree(void* datasource) {
    return 0; // SDL_RWclose((SDL_RWops*)datasource);
}
PRIVATE STATIC int ISound::StaticCloseNoFree(void* datasource) {
    return 0; // SDL_RWseek((SDL_RWops*)datasource, 0, RW_SEEK_SET);
}
PRIVATE STATIC long ISound::StaticTell(void* datasource) {
    // return SDL_RWtell((SDL_RWops*)datasource);
    return ((IResource*)datasource)->Position();
}
PUBLIC bool ISound::LoadOGG_RW(IResource* src, int freesrc, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len) {
    OggVorbis_File vf;
    ov_callbacks callbacks = OV_CALLBACKS_NOCLOSE;
    vorbis_info *info;
    Uint8 *buf;
    int bitstream = -1;
    long samplesize;
    long samples;
    int read, to_read;
    int must_close = 1;
    int was_error = 1;

    callbacks.read_func = StaticRead;
    callbacks.seek_func = StaticSeek;
    callbacks.tell_func = StaticTell;
    callbacks.close_func = freesrc ? StaticCloseFree : StaticCloseNoFree;

    if (ov_open_callbacks(src, &vf, NULL, 0, callbacks) != 0) {
        SDL_SetError("OGG bitstream is not valid Vorbis stream!");
        goto done;
    }

    must_close = 0;

    info = ov_info(&vf, -1);

    *audio_buf = NULL;
    *audio_len = 0;
    memset(spec, 0, sizeof(SDL_AudioSpec));

    spec->format = AUDIO_S16;
    spec->channels = info->channels;
    spec->freq = info->rate;
    spec->samples = 4096; /* buffer size */

    samples = (long)ov_pcm_total(&vf, -1);

    *audio_len = spec->size = samples * spec->channels * 2;
    *audio_buf = (uint8_t*)malloc(*audio_len);
	if (*audio_buf == NULL) {
		IApp::Print(2, "Could not make memory for Vorbis stream.");
		goto done;
	}

    buf = *audio_buf;
    to_read = *audio_len;
    for (read = ov_read(&vf, (char*)buf, to_read, 0/*LE*/, 2/*16bit*/, 1/*signed*/, &bitstream);
         read > 0;
         read = ov_read(&vf, (char*)buf, to_read, 0, 2, 1, &bitstream))
    {
        if (read == OV_HOLE || read == OV_EBADLINK)
            break; /* error */

        to_read -= read;
        buf += read;
    }

    ov_clear(&vf);
    was_error = 0;

    /* Don't return a buffer that isn't a multiple of samplesize */
    samplesize = ((spec->format & 0xFF) / 8) * spec->channels;
    *audio_len &= ~(samplesize - 1);

    done:
    if (src && must_close) {
        // if (freesrc)
        //     SDL_RWclose(src);
        // else
            src->Seek(0, RW_SEEK_SET); //SDL_RWseek(src, 0, RW_SEEK_SET);
    }

    if (was_error)
        spec = NULL;

    return spec;
}

/*
PUBLIC Vorbis* ISound::LoadVorbis(IResource* src, SDL_AudioSpec *spec) {
}
*/

ISound::Vorbis* ISound::LoadVorbis(IResource* src, SDL_AudioSpec *spec) {
    Vorbis* vorb = new Vorbis();
    ov_callbacks callbacks;
    long samples;
	callbacks = OV_CALLBACKS_STREAMONLY;
	callbacks = OV_CALLBACKS_STREAMONLY_NOCLOSE;
	callbacks = OV_CALLBACKS_NOCLOSE;
	callbacks = OV_CALLBACKS_DEFAULT;

    callbacks.read_func = StaticRead;
    callbacks.seek_func = StaticSeek;
    callbacks.tell_func = StaticTell;
    // callbacks.close_func = freesrc ? StaticCloseFree : StaticCloseNoFree;

    if (ov_open_callbacks(src, &vorb->vf, NULL, 0, callbacks) != 0) {
        IApp::Print(2, "Resource is not valid Vorbis stream!");
        return NULL;
    }

    vorb->info = ov_info(&vorb->vf, -1);

    memset(spec, 0, sizeof(SDL_AudioSpec));

    spec->format = AUDIO_S16;
    spec->channels = vorb->info->channels;
    spec->freq = vorb->info->rate;
    spec->samples = 4096;

    samples = (long)ov_pcm_total(&vorb->vf, -1);

    vorb->audio_len = spec->size = samples * spec->channels * 2;
    return vorb;
}

PUBLIC int ISound::ReadVorbis(Vorbis* vorb, void* dst, int size) {
    int bitstream = -1;

    int tot = 0;
    int read;
    int to_read = size;
    char* buf = (char*)dst;
    uint32_t left = vorb->audio_len;
    for (read = ov_read(&vorb->vf, (char*)buf, to_read, 0/*LE*/, 2/*16bit*/, 1/*signed*/, &bitstream); read > 0; read = ov_read(&vorb->vf, (char*)buf, to_read, 0, 2, 1, &bitstream)) {
        if (read == OV_HOLE || read == OV_EBADLINK)
            break; /* error */

        to_read -= read;
        buf += read;
        tot += read;
        left -= read;
        if (left <= 0)
            break;
    }
    return tot;
}
PUBLIC int ISound::SeekVorbis(Vorbis* vorb, int64_t pos) {
    return ov_pcm_seek(&vorb->vf, (ogg_int64_t)pos);
}

PUBLIC long long ISound::TellVorbis(Vorbis* vorb) {
	return ov_pcm_tell(&vorb->vf);
}

PUBLIC ISound::ISound(const char* filename) {
    ISound::Load(filename, false);
}
PUBLIC ISound::ISound(const char* filename, bool streamFromFile) {
    ISound::Load(filename, streamFromFile);
}

PUBLIC void ISound::Load(const char* filename, bool streamFromFile) {
    LoadFailed = true;

    StreamFromFile = streamFromFile;

    Name = (char*)filename;

    if (StreamFromFile) {
        IResource* res = IResources::Load(filename);
    	if (!res) {
    		IApp::Print(2, "Couldn't open file '%s'!", filename);
    		fflush(stdin);
    		return;
    	}

        if (strstr(filename, ".ogg")) {
            vorbis_file = LoadVorbis(res, &Format);
        }
        else {
            WAV_HEADER wvhrd;
            res->Read(&wvhrd, 0x2E);

            Format.freq = wvhrd.SamplesPerSec;
            Format.format = 0x8100 | (wvhrd.bitsPerSample & 0xFF);
            Format.channels = wvhrd.NumOfChan;
        }

        Stream = SDL_NewAudioStream(Format.format, Format.channels, Format.freq, IAudio::DeviceFormat.format, IAudio::DeviceFormat.channels, IAudio::DeviceFormat.freq);
        if (Stream == NULL) {
            IApp::Print(2, "Stream failed to create: %s", SDL_GetError());
    		return;
        }

        Buffer = (uint8_t*)malloc(0x1000);
        ExtraBuffer = (uint8_t*)malloc(0x1000);
        Resource = res;
        LoadFailed = false;
    }
    else {
        IResource* res = IResources::Load(filename, true);
    	if (!res) {
    		IApp::Print(2, "Couldn't open file '%s'!", filename);
    		fflush(stdin);
    		return;
    	}

        uint32_t length = 0;
        uint8_t* buffer = NULL;

        Resource = res;

        if (strstr(filename, ".wav")) {
            if (!SDL_LoadWAV_RW(Resource->RW, 0, &Format, &buffer, &length)) {
                IApp::Print(2, "Could not load Sound! (%s)", SDL_GetError());
                return;
            }
        }
        else {
            if (!LoadOGG_RW(Resource, false, &Format, &buffer, &length)) {
                IApp::Print(2, "Could not load OGG Sound! (%s)", filename);
                return;
            }
        }

        if (!buffer) {
            IApp::Print(2, "Could not load Sound buffer!");
            return;
        }

        SDL_AudioCVT convert;
        if (SDL_BuildAudioCVT(&convert, Format.format, Format.channels, Format.freq, IAudio::DeviceFormat.format, IAudio::DeviceFormat.channels, IAudio::DeviceFormat.freq) > 0) {
            convert.buf = (uint8_t*)malloc(length * convert.len_mult);
            convert.len = length;
            memcpy(convert.buf, buffer, length);
			SDL_FreeWAV(buffer);
            SDL_ConvertAudio(&convert);

            Buffer = convert.buf;
            Length = convert.len_cvt;
            Remaining = convert.len_cvt;
        }
        else {
            Buffer = buffer;
            Length = length;
            Remaining = length;
        }

        IResources::Close(res);
        LoadFailed = false;
    }
}

PUBLIC int  ISound::RequestMoreData(int samples, int amount) {
	int out = (IAudio::DeviceFormat.format & 0xFF) / 8 * samples * IAudio::DeviceFormat.channels;
	int avail = SDL_AudioStreamAvailable(Stream);
	if (avail < out * 2) {
		int num_samples = 0;
		if (vorbis_file)
			num_samples = ReadVorbis(vorbis_file, ExtraBuffer, (Format.format & 0xFF) / 8 * samples * Format.channels);
		else
			num_samples = Resource->Read(ExtraBuffer, (Format.format & 0xFF) / 8 * samples * Format.channels * 2);
		if (num_samples == 0) {
			return 0;
		}

		int rc = SDL_AudioStreamPut(Stream, ExtraBuffer, num_samples);
		if (rc == -1) {
			IApp::Print(2, "Uhoh, failed to put samples in stream: %s", SDL_GetError());
			return -1;
		}
	}

    int gotten = SDL_AudioStreamGet(Stream, Buffer, out);
    if (gotten == -1) {
        IApp::Print(2, "Uhoh, failed to get converted data: %s", SDL_GetError());
        return -1;
    }
    if (gotten == 0)
        gotten = -2;

    return gotten;
}
PUBLIC void ISound::Seek(int amount) {
    if (StreamFromFile) {
        if (vorbis_file)
            SeekVorbis(vorbis_file, amount);
        else
            Resource->Seek((Format.format & 0xFF) / 8 * amount * Format.channels + 0x2E, RW_SEEK_SET);
    }
}

PUBLIC long long ISound::GetPosition() {
	if (StreamFromFile) {
		if (vorbis_file)
			return TellVorbis(vorbis_file);
		else
			return Resource->Position();
	}
}

PUBLIC void ISound::Cleanup() {
	if (Buffer) {
		SDL_FreeWAV(Buffer);
	}

    if (Stream) {
		SDL_FreeWAV(ExtraBuffer);
        SDL_FreeAudioStream(Stream);
        IResources::Close(Resource);
    }
}
