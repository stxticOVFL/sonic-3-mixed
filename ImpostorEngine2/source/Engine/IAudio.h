#ifndef IAUDIO_H
#define IAUDIO_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISound;
class IApp;

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
    int 	   Volume = 0xFF;
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
    float 			GlobalVolume = 1.0f;
    float 			MusicVolume = 1.0f;
    float 			SoundFXVolume = 1.0f;
    void* operator new(size_t const size) noexcept;
    void* operator new(size_t const size, std::nothrow_t const&) noexcept;
    void operator delete(void* const block) noexcept;

    IAudio(IApp* app);
    void SetSound(int channel, uint8_t* buffer, int length);
    void SetSoundAt(int channel, uint8_t* bufferAt, int lengthAt, uint8_t* buffer, int length);
    void PushMusic(ISound* music, bool loop, uint32_t lp);
    void PushMusicAt(ISound* music, double at, bool loop, uint32_t lp);
    void RemoveMusic(ISound* music);
    bool IsPlayingMusic();
    bool IsPlayingMusic(ISound* music);
    void ClearMusic();
    void FadeMusic(double seconds);
    void AudioUnpause(int channel);
    void AudioPause(int channel);
    void AudioUnpauseAll();
    void AudioPauseAll();
    static void AudioCallback(void* data, uint8_t* stream, int len);
    void Cleanup();
};

#endif /* IAUDIO_H */
