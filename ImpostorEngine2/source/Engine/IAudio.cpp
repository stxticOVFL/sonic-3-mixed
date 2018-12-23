#if INTERFACE
#include <Utils/Standard.h>
#include <Utils/StandardSDL2.h>
#include <Engine/IApp.h>

class IAudio {
public:
    struct StackNode {
        ISound*    Audio = NULL;
        uint8_t*   Buffer = NULL;
        uint32_t   Length = 0;
        uint8_t*   BufferStart = NULL;
        uint32_t   LengthStart = 0;
        bool       Loop = false;
        uint32_t   LoopPoint = 0;
        bool       FadeOut = false;
    };

    IApp* App = NULL;

    SDL_AudioDeviceID    Device;
    SDL_AudioSpec        Want;
    SDL_AudioSpec        DeviceFmt;
    static SDL_AudioSpec DeviceFormat;
    SDL_AudioSpec        AudioFormat;
    bool                 AudioEnabled = false;


    // Bytes = Sample Rate * Seconds * 4
    // LoopPointInBytes = LoopPoint(Samples) * 4
    // LoopPointInSeconds = LoopPoint(Samples) / Sample Rate
    uint32_t*            LoopPoint;
    bool*                Loop;

    bool*                Paused;
    uint32_t*            Length;
    uint8_t**            Buffer;
    uint32_t*            LengthStart;
    uint8_t**            BufferStart;

    deque<StackNode*>    MusicStack;

    double               FadeOutTimer = 1.0;
    double               FadeOutTimerMax = 1.0;
};
#endif

#include <Engine/IAudio.h>
#include <Engine/ISound.h>

#define AUDIO_FORMAT AUDIO_S16

#define AUDIO_FREQUENCY 22050
// #define AUDIO_FREQUENCY 44100
#define AUDIO_CHANNELS 2
#define AUDIO_SAMPLES 0x100
#define AUDIO_MAX_SOUNDS 4
#define SDL_AUDIO_ALLOW_CHANGES SDL_AUDIO_ALLOW_ANY_CHANGE

SDL_AudioSpec IAudio::DeviceFormat;

PUBLIC IAudio::IAudio(IApp* app) {
    App = app;

	Loop = (bool*)calloc(1, 256 * sizeof(bool));
	Paused = (bool*)calloc(1, 256 * sizeof(bool));
	Buffer = (uint8_t**)calloc(1, 256 * sizeof(uint8_t*));
	Length = (uint32_t*)calloc(1, 256 * sizeof(uint32_t));
	BufferStart = (uint8_t**)calloc(1, 256 * sizeof(uint8_t*));
	LengthStart = (uint32_t*)calloc(1, 256 * sizeof(uint32_t));
	LoopPoint = (uint32_t*)calloc(1, 256 * sizeof(uint32_t));

	memset(Loop, 0, 256 * sizeof(bool));
	memset(Paused, 0, 256 * sizeof(bool));
	memset(Buffer, 0, 256 * sizeof(uint8_t*));
	memset(Length, 0, 256 * sizeof(uint32_t));
	memset(BufferStart, 0, 256 * sizeof(uint8_t*));
	memset(LengthStart, 0, 256 * sizeof(uint32_t));
	memset(LoopPoint, 0, 256 * sizeof(uint32_t));

    Want.freq = AUDIO_FREQUENCY;
    Want.format = AUDIO_FORMAT;
    Want.samples = AUDIO_SAMPLES;
    Want.channels = AUDIO_CHANNELS;
    Want.callback = IAudio::AudioCallback;
    Want.userdata = this;

    Device = SDL_OpenAudioDevice(NULL, 0, &Want, &DeviceFmt, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (Device) {
        AudioEnabled = true;
        SDL_PauseAudioDevice(Device, 0);
    }
    else {
        App->Print(2, "Could not open audio device!");
    }

    IApp::Print(0, "%s = %d", "freq", DeviceFmt.freq);
    IApp::Print(0, "%s = %X", "format", DeviceFmt.format);
    IApp::Print(0, "%s = %X", "samples", DeviceFmt.samples);
    IApp::Print(0, "%s = %X", "channels", DeviceFmt.channels);
    IApp::Print(0, "%s = %X", "callback", DeviceFmt.callback);
    IApp::Print(0, "%s = %X", "userdata", DeviceFmt.userdata);

    IAudio::DeviceFormat = DeviceFmt;
}

PUBLIC void IAudio::SetSound(int channel, uint8_t* buffer, int length) {
    SetSoundAt(channel, buffer, length, buffer, length);
}
PUBLIC void IAudio::SetSoundAt(int channel, uint8_t* bufferAt, int lengthAt, uint8_t* buffer, int length) {
    SDL_LockAudioDevice(Device);

    if (channel != 0) {
        Paused[channel] = bufferAt == NULL;

        Buffer[channel] = bufferAt;
        Length[channel] = lengthAt;

        BufferStart[channel] = buffer;
        LengthStart[channel] = length;
    }

    SDL_UnlockAudioDevice(Device);
}

PUBLIC void IAudio::PushMusic(ISound* music, bool loop, uint32_t lp) {
    PushMusicAt(music, 0.0, loop, lp);
}
PUBLIC void IAudio::PushMusicAt(ISound* music, double at, bool loop, uint32_t lp) {
    if (music->LoadFailed) return;

    SDL_LockAudioDevice(Device);

    StackNode* newms = new StackNode();
    newms->Audio = music;
    // music->Seek(int(ceil(at * AUDIO_FREQUENCY)));
    newms->Buffer = music->Buffer + int(ceil(at * AUDIO_FREQUENCY)) * 4;
    newms->Length = music->Length - int(ceil(at * AUDIO_FREQUENCY)) * 4;
    newms->BufferStart = music->Buffer;
    newms->LengthStart = music->Length;
    music->Seek(0);
    music->Seek(0);
    newms->Loop = loop;
    newms->LoopPoint = lp;
    newms->FadeOut = false;
    MusicStack.push_front(newms);

    for (int i = 1; i < MusicStack.size(); i++) {
        MusicStack[i]->FadeOut = false;
    }

    FadeOutTimer = 1.0;
    FadeOutTimerMax = 1.0;

    Paused[0] = false;

    SDL_UnlockAudioDevice(Device);
}
PUBLIC void IAudio::RemoveMusic(ISound* music) {
    SDL_LockAudioDevice(Device);
    for (int i = 0; i < MusicStack.size(); i++) {
        if (MusicStack[i]->Audio == music) {
            delete MusicStack[i];
            MusicStack.erase(MusicStack.begin() + i);
        }
    }
    SDL_UnlockAudioDevice(Device);
}
PUBLIC bool IAudio::IsPlayingMusic() {
    return MusicStack.size() > 0;
}
PUBLIC bool IAudio::IsPlayingMusic(ISound* music) {
    for (int i = 0; i < MusicStack.size(); i++) {
        if (MusicStack[i]->Audio == music) {
            return true;
        }
    }
    return false;
}
PUBLIC void IAudio::ClearMusic() {
    SDL_LockAudioDevice(Device);
    for (int i = 0; i < MusicStack.size(); i++) {
        delete MusicStack[i];
    }
    MusicStack.clear();
    SDL_UnlockAudioDevice(Device);
}
PUBLIC void IAudio::FadeMusic(double seconds) {
    SDL_LockAudioDevice(Device);
    if (MusicStack.size() > 0) {
        MusicStack[0]->FadeOut = true;
        FadeOutTimer = seconds;
        FadeOutTimerMax = seconds;
    }
    SDL_UnlockAudioDevice(Device);
}

PUBLIC void IAudio::AudioUnpause(int channel) {
    SDL_LockAudioDevice(Device);
    Paused[channel] = false;
    SDL_UnlockAudioDevice(Device);
}
PUBLIC void IAudio::AudioPause(int channel) {
    SDL_LockAudioDevice(Device);
    Paused[channel] = true;
    SDL_UnlockAudioDevice(Device);
}
PUBLIC void IAudio::AudioUnpauseAll() {
    SDL_LockAudioDevice(Device);
    for (int i = 0; i < 256; i++)
        Paused[i] = false;
    SDL_UnlockAudioDevice(Device);
}
PUBLIC void IAudio::AudioPauseAll() {
    SDL_LockAudioDevice(Device);
    for (int i = 0; i < 256; i++)
        Paused[i] = true;
    SDL_UnlockAudioDevice(Device);
}

PUBLIC STATIC void IAudio::AudioCallback(void* data, uint8_t* stream, int len) {
    IAudio* audio = (IAudio*)data;
    if (audio != NULL) {
        SDL_memset(stream, 0, len);

        do {
            if (audio->Paused[0])
                break;

            if (audio->MusicStack.size() == 0)
                break;

            if (audio->MusicStack[0]->Audio->StreamFromFile) {
                if (audio->MusicStack[0]->FadeOut) {
                    audio->FadeOutTimer -= (double)AUDIO_SAMPLES / AUDIO_FREQUENCY;
                    if (audio->FadeOutTimer < 0.0)
                        audio->FadeOutTimer = 0.0;
                }

                bool deleted = false;
                int bytes = audio->MusicStack[0]->Audio->RequestMoreData(AUDIO_SAMPLES, len);
                if (bytes > 0) {
                    SDL_MixAudioFormat(stream, audio->MusicStack[0]->Audio->Buffer, audio->DeviceFmt.format, (uint32_t)bytes, ((int)(0xFF * (audio->FadeOutTimer / audio->FadeOutTimerMax)) >> 3) + 1);
                }
                else if (bytes == -1) {
                    // error
                }
                else if (bytes == 0) {
                    // end of file
                    if (audio->MusicStack[0]->Loop) {
                        audio->MusicStack[0]->Audio->Seek(audio->MusicStack[0]->LoopPoint);
                    }
                    else {
                        delete audio->MusicStack[0];
                        audio->MusicStack.pop_front();
                        deleted = true;
                    }
                }

                if (audio->FadeOutTimer == 0.0 && !deleted) {
                    audio->FadeOutTimer = 1.0;
                    audio->FadeOutTimerMax = 1.0;

                    delete audio->MusicStack[0];
                    audio->MusicStack.pop_front();
                }
            }
            else {
                if (audio->MusicStack[0]->Buffer) {
                    if (audio->MusicStack[0]->FadeOut) {
                        audio->FadeOutTimer -= (double)AUDIO_SAMPLES / AUDIO_FREQUENCY;
                        if (audio->FadeOutTimer < 0.0)
                            audio->FadeOutTimer = 0.0;
                    }
                    if (audio->MusicStack[0]->Length > 0) {
                        int possibleSampleLength = ((uint32_t)len > audio->MusicStack[0]->Length) ? audio->MusicStack[0]->Length : (uint32_t)len;

                        SDL_MixAudioFormat(stream, audio->MusicStack[0]->Buffer, audio->DeviceFmt.format, possibleSampleLength, ((int)(0x60 * (audio->FadeOutTimer / audio->FadeOutTimerMax)) >> 3) + 1);

                        audio->MusicStack[0]->Buffer += possibleSampleLength;
                        audio->MusicStack[0]->Length -= possibleSampleLength;
                    }
                    if (audio->MusicStack[0]->Length == 0) {
                        audio->MusicStack[0]->Buffer = NULL;
                        if (audio->MusicStack[0]->Loop) {
                            audio->MusicStack[0]->Buffer = audio->MusicStack[0]->BufferStart + audio->MusicStack[0]->LoopPoint * (len / AUDIO_SAMPLES);
                            audio->MusicStack[0]->Length = audio->MusicStack[0]->LengthStart - audio->MusicStack[0]->LoopPoint * (len / AUDIO_SAMPLES);
                        }
                        else {
                            delete audio->MusicStack[0];
                            audio->MusicStack.pop_front();
                        }
                    }

                    if (audio->FadeOutTimer == 0.0) {
                        audio->FadeOutTimer = 1.0;
                        audio->FadeOutTimerMax = 1.0;

                        delete audio->MusicStack[0];
                        audio->MusicStack.pop_front();
                        if (audio->MusicStack.size() > 0) {
                            audio->MusicStack[0]->Buffer = audio->MusicStack[0]->BufferStart;
                            audio->MusicStack[0]->Length = audio->MusicStack[0]->LengthStart;
                        }
                    }
                }
            }
        }
        while (false);

        for (int i = 1; i < 256; i++) {
            if (audio->Paused[i])
                continue;

            if (audio->Buffer[i]) {
                if (audio->Length[i] > 0) {
                    int possibleSampleLength = ((uint32_t)len > audio->Length[i]) ? audio->Length[i] : (uint32_t)len;

                    SDL_MixAudioFormat(stream, audio->Buffer[i], audio->DeviceFmt.format, possibleSampleLength, (0x80) >> 3);

                    audio->Buffer[i] += possibleSampleLength;
                    audio->Length[i] -= possibleSampleLength;
                }
                if (audio->Length[i] == 0) {
                    audio->Buffer[i] = NULL;
                    if (audio->Loop[i]) {
                        audio->Buffer[i] = audio->BufferStart[i] + audio->LoopPoint[i] * (len / AUDIO_SAMPLES);
                        audio->Length[i] = audio->LengthStart[i] - audio->LoopPoint[i] * (len / AUDIO_SAMPLES);
                    }
                }
            }
        }
    }
}

PUBLIC void IAudio::Cleanup() {
    SDL_PauseAudioDevice(Device, 1);
    SDL_CloseAudioDevice(Device);
}
