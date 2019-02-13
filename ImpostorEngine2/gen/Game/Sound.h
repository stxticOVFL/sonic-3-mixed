#ifndef SOUND_H
#define SOUND_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL


#include <Utils/Standard.h>
#include <Engine/IAudio.h>
#include <Engine/ISound.h>

class Sound {
public:
    enum {
    SFX_RING = 0x33,
    SFX_DEATH = 0x35,
    SFX_SKID = 0x36,
    SFX_SPIKE_DEATH = 0x37,
    SFX_AIR_BUBBLE = 0x38,
    SFX_SPLASH = 0x39,
    SFX_SHIELD = 0x3A,
    SFX_DROWN = 0x3B,
    SFX_ROLL = 0x3C,
    SFX_DESTROY = 0x3D,
    SFX_SHIELD_FIRE = 0x3E,
    SFX_SHIELD_BUBBLE = 0x3F,
    SFX_SHIELD_ELECTRIC = 0x41,
    SFX_SPINDASHREV = 0xAB,
    SFX_SPINDASH = 0xB6,
    SFX_BIG_SPLASH = 0x4B,
    SFX_JUMP = 0x62,
    SFX_SHIELD_FIRE_DASH = 0x43,
    SFX_SHIELD_BUBBLE_BOUNCE = 0x44,
    SFX_SHIELD_ELECTRIC_JUMP = 0x45,
    SFX_UNDERWATER_BEEP = 0xA9,
    SFX_INSTASHIELD = 0x42,
    SFX_RINGLOSS = 0xB9,
    SFX_TRANSFORM = 0x9F,
    SFX_SPRING = 0xB1,
    SFX_STARPOST = 0x63,
    SFX_COLLAPSE = 0x59,
    SFX_PUSHING = 0x69,
    SFX_WATERRUN = 0xDB,
    SFX_BOSSHIT = 0x6E,
    SFX_73 = 0x73,
    SFX_VACUUM_TUBE = 0x74,
    SFX_BALLOON_POP = 0x77,
    SFX_PAD_BOUNCE = 0x7B,
    SFX_GRAB = 0x4A,
    SFX_SHOT = 0x4D,
    SFX_BOMB_EXPLOSION = 0x4E,
    SFX_DROP = 0x51,
    SFX_TAILS_FLY = 0xBA,
    SFX_TAILS_TIRED = 0xBB,
    SFX_SLIDE = 0xBC,
    SFX_AIRSHIP = 0xBD,
    SFX_SS_WARP = 0xAF,
    SFX_ENTER_SS_RING = 0xB3,
    SFX_BOSSEXPLOSION = 0xB4,
    SFX_FAN_BIG = 0xC0,
    SFX_FAN_SMALL = 0xC1,
    SFX_SPECIALSTAGEFLYAWAY = 0x66,
    SFX_SCORE_ADD = 0x5B,
    SFX_RUMBLE = 0x6F,
    SFX_IMPACT4 = 0x5F,
    SFX_SCORE_TOTAL = 0xB0,
    SFX_DROPDASHREADY = 0x01,
    SFX_DROPDASH = 0x02,
    SFX_MENUACCEPT = 0x03,
    SFX_MENUBLEEP = 0x04,
    SFX_MENUWOOSH = 0x05,
    SFX_MENUFAIL = 0x06,
    SFX_AIRSHIP2 = 0x07,
    SFX_RAY_DIVE = 0x08,
    SFX_RAY_SWOOP = 0x09,
    }; 
    static IAudio* Audio;
    static bool    AudioLoaded;
    static ISound* SoundBank[256];

    Sound();
    static void Init();
    static void Play(int sound);
    static void Loop(int sound, int looppoint);
    static void Stop(int sound);
};

#endif /* SOUND_H */
