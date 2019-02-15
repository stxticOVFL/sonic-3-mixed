#if INTERFACE
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

		SFX_BUMPER = 0xAA,

        SFX_TAILS_FLY = 0xBA,
        SFX_TAILS_TIRED = 0xBB,
        SFX_SLIDE = 0xBC,
        SFX_AIRSHIP = 0xBD,


        SFX_SS_WARP = 0xAF,
        SFX_ENTER_SS_RING = 0xB3,
        SFX_BOSSEXPLOSION = 0xB4,

        SFX_FAN_BIG = 0xC0,
        SFX_FAN_SMALL = 0xC1,

		SFX_BLUEBALL = 0x65,
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
};

#endif

#include <Game/Sound.h>

IAudio* Sound::Audio = NULL;
bool    Sound::AudioLoaded = false;
ISound* Sound::SoundBank[256];

PUBLIC Sound::Sound() {

}

PUBLIC STATIC void Sound::Init() {
    if (Sound::AudioLoaded) return;

    // Audio Channel 0 is for music

#define LOADSOUND(id, str) Sound::SoundBank[id] = new ISound(str)

	LOADSOUND(SFX_SPINDASHREV, "Sounds/Charge.wav");
	LOADSOUND(SFX_SPINDASH, "Sounds/Release.wav");
	LOADSOUND(SFX_SPLASH, "Sounds/Splash.wav");
	LOADSOUND(SFX_ROLL, "Sounds/Roll.wav");
	LOADSOUND(SFX_DROPDASHREADY, "Sounds/DropDash.wav");
	LOADSOUND(SFX_DROPDASH, "Sounds/Release.wav");
	LOADSOUND(SFX_JUMP, "Sounds/Jump.wav");
	LOADSOUND(SFX_SHIELD_FIRE, "Sounds/FireShield.wav");
	LOADSOUND(SFX_SHIELD_BUBBLE, "Sounds/BubbleShield.wav");
	LOADSOUND(SFX_SHIELD_ELECTRIC, "Sounds/LightningShield.wav");
	LOADSOUND(SFX_SHIELD_FIRE_DASH, "Sounds/FireDash.wav");
	LOADSOUND(SFX_SHIELD_BUBBLE_BOUNCE, "Sounds/BubbleBounce.wav");
	LOADSOUND(SFX_SHIELD_ELECTRIC_JUMP, "Sounds/LightningJump.wav");
	LOADSOUND(SFX_RING, "Sounds/Ring.wav");
	LOADSOUND(SFX_UNDERWATER_BEEP, "Sounds/Warning.wav");
	LOADSOUND(SFX_INSTASHIELD, "Sounds/InstaShield.wav");
	LOADSOUND(SFX_RINGLOSS, "Sounds/LoseRings.wav");
	LOADSOUND(SFX_DESTROY, "Sounds/Destroy.wav");
	LOADSOUND(SFX_TRANSFORM, "Sounds/Transform2.wav");
	LOADSOUND(SFX_DEATH, "Sounds/Hurt.wav");
	LOADSOUND(SFX_SKID, "Sounds/Skidding.wav");
	LOADSOUND(SFX_AIR_BUBBLE, "Sounds/Breathe.wav");
	LOADSOUND(SFX_DROWN, "Sounds/Drown.wav");
	LOADSOUND(SFX_SPRING, "Sounds/Spring.wav");
	LOADSOUND(SFX_STARPOST, "Sounds/StarPost.wav");
	LOADSOUND(SFX_COLLAPSE, "Sounds/LedgeBreak3.wav");
	LOADSOUND(SFX_PUSHING, "Sounds/Push.wav");
	LOADSOUND(SFX_WATERRUN, "Sounds/WaterRun.wav");

	LOADSOUND(SFX_DROP, "Sounds/Drop.wav");
	LOADSOUND(SFX_SHOT, "Sounds/Shot.wav");
	LOADSOUND(SFX_BOMB_EXPLOSION, "Sounds/Explosion3.wav");

	LOADSOUND(SFX_GRAB, "Sounds/Grab.wav");
	LOADSOUND(SFX_TAILS_FLY, "Sounds/Flying.wav");
	LOADSOUND(SFX_TAILS_TIRED, "Sounds/Tired.wav");

	LOADSOUND(SFX_BOSSHIT, "Sounds/BossHit.wav");
	LOADSOUND(SFX_BOSSEXPLOSION, "Sounds/Explosion2.wav");

	LOADSOUND(SFX_73, "Sounds/S3K_73.wav");
	LOADSOUND(SFX_VACUUM_TUBE, "Sounds/S3K_74.wav");
	LOADSOUND(SFX_BALLOON_POP, "Sounds/S3K_77.wav");
	LOADSOUND(SFX_PAD_BOUNCE, "Sounds/S3K_7B.wav");


	LOADSOUND(SFX_FAN_BIG, "Sounds/BigFan.wav");
	LOADSOUND(SFX_FAN_SMALL, "Sounds/SmallFan.wav");
	LOADSOUND(SFX_SLIDE, "Sounds/Waterfall.wav");

	LOADSOUND(SFX_IMPACT4, "Sounds/Impact4.wav");
	LOADSOUND(SFX_RUMBLE, "Sounds/Rumble.wav");

	LOADSOUND(SFX_ENTER_SS_RING, "Sounds/SpecialRing.wav");
	LOADSOUND(SFX_SS_WARP, "Sounds/SpecialWarp.wav");

	LOADSOUND(SFX_SPIKE_DEATH, "Sounds/Hurt.wav");

	LOADSOUND(SFX_SCORE_ADD, "Sounds/ScoreAdd.wav");
	LOADSOUND(SFX_SCORE_TOTAL, "Sounds/ScoreTotal.wav");

	LOADSOUND(SFX_BUMPER, "Sounds/Bumper.wav");

	LOADSOUND(SFX_MENUACCEPT, "Sounds/MenuAccept.wav");
	LOADSOUND(SFX_MENUBLEEP, "Sounds/MenuBleep.wav");
	LOADSOUND(SFX_MENUWOOSH, "Sounds/MenuWoosh.wav");
	LOADSOUND(SFX_MENUFAIL, "Sounds/Fail.wav");

	LOADSOUND(SFX_AIRSHIP, "Sounds/S3K_BD.wav");
	LOADSOUND(SFX_AIRSHIP2, "Sounds/S3K_BD.wav");

	LOADSOUND(SFX_RAY_DIVE, "Sounds/RayDive.wav");
	LOADSOUND(SFX_RAY_SWOOP, "Sounds/RaySwoop.wav");

	LOADSOUND(SFX_BLUEBALL, "Sounds/BlueSphere.wav");

    Sound::SoundBank[0xFF] = new ISound("Music/S3 Invincibility.ogg", true);
    Sound::SoundBank[0xFE] = new ISound("Music/Mixed/Sneakers.ogg", true);
    Sound::SoundBank[0xFD] = new ISound("Music/Drowning.ogg", true);
    Sound::SoundBank[0xFC] = new ISound("Music/ActComplete.ogg", true);
    Sound::SoundBank[0xFB] = new ISound("Music/S3 1up.ogg", false);

    Sound::SoundBank[0xF2] = new ISound("Music/S3 Knux Theme.ogg", true);
    Sound::SoundBank[0xF1] = new ISound("Music/S3 Miniboss.ogg", true);
    Sound::SoundBank[0xF0] = new ISound("Music/Boss.ogg", true);

    Sound::AudioLoaded = true;
}

PUBLIC STATIC void Sound::Play(int sound) {
    if (Sound::SoundBank[sound]->LoadFailed) return;

    Sound::Audio->SetSound(sound, Sound::SoundBank[sound]->Buffer, Sound::SoundBank[sound]->Length);
}
PUBLIC STATIC void Sound::Loop(int sound, int looppoint) {
    if (Sound::SoundBank[sound]->LoadFailed) return;

    Sound::Audio->SetSound(sound, Sound::SoundBank[sound]->Buffer, Sound::SoundBank[sound]->Length);
    Sound::Audio->Loop[sound] = true;
    Sound::Audio->LoopPoint[sound] = looppoint;
}
PUBLIC STATIC void Sound::Stop(int sound) {
    if (Sound::SoundBank[sound]->LoadFailed) return;

    Sound::Audio->SetSound(sound, NULL, Sound::SoundBank[sound]->Length);
}
