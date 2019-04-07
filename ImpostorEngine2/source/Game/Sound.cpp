#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IAudio.h>
#include <Engine/ISound.h>

class Sound {
public:
	enum {
		SFX_RING = 0x33,
		SFX_34 = 0x34,
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

		SFX_40 = 0x40,
		SFX_SHIELD_ELECTRIC = 0x41,
		SFX_INSTASHIELD = 0x42,
		SFX_SHIELD_FIRE_DASH = 0x43,
		SFX_SHIELD_BUBBLE_BOUNCE = 0x44,
		SFX_SHIELD_ELECTRIC_JUMP = 0x45,
		SFX_46 = 0x46,
		SFX_47 = 0x47,
		SFX_48 = 0x48,
		SFX_49 = 0x49,
		SFX_GRAB = 0x4A,
		SFX_BIG_SPLASH = 0x4B,
		SFX_4C = 0x4C,
		SFX_SHOT = 0x4D,
		SFX_BOMB_EXPLOSION = 0x4E,
		SFX_4F = 0x4F,

		SFX_50 = 0x50,
		SFX_DROP = 0x51,
		SFX_52 = 0x52,
		SFX_53 = 0x53,
		SFX_54 = 0x54,
		SFX_55 = 0x55,
		SFX_56 = 0x56,
		SFX_57 = 0x57,
		SFX_58 = 0x58,
		SFX_COLLAPSE = 0x59,
		SFX_5A = 0x5A,
		SFX_SCORE_ADD = 0x5B,
		SFX_IMPACT1 = 0x5C,
		SFX_IMPACT2 = 0x5D,
		SFX_IMPACT3 = 0x5E,
		SFX_IMPACT4 = 0x5F,

		SFX_IMPACT5 = 0x60,
		SFX_IMPACT6 = 0x61,
		SFX_JUMP = 0x62,
		SFX_STARPOST = 0x63,
		SFX_64 = 0x64,
		SFX_BLUEBALL = 0x65,
		SFX_SPECIALSTAGE_FLYAWAY = 0x66,
		SFX_67 = 0x67,
		SFX_68 = 0x68,
		SFX_PUSHING = 0x69,
		SFX_SPECIALSTAGE_EXIT = 0x6A,
		SFX_6B = 0x6B,
		SFX_6C = 0x6C,
		SFX_6D = 0x6D,
		SFX_BOSSHIT = 0x6E,
		SFX_RUMBLE = 0x6F,

		SFX_70 = 0x70,
		SFX_71 = 0x71,
		SFX_CARNIVAL_FAN = 0x72,
		SFX_73 = 0x73,
		SFX_VACUUM_TUBE = 0x74,
		SFX_75 = 0x75,
		SFX_76 = 0x76,
		SFX_BALLOON_POP = 0x77,
		SFX_78 = 0x78,
		SFX_79 = 0x79,
		SFX_7A = 0x7A,
		SFX_PAD_BOUNCE = 0x7B,
		SFX_7C = 0x7C,
		SFX_7D = 0x7D,
		SFX_7E = 0x7E,
		SFX_7F = 0x7F,

		SFX_80 = 0x80,
		SFX_81 = 0x81,
		SFX_82 = 0x82,
		SFX_83 = 0x83,
		SFX_84 = 0x84,
		SFX_85 = 0x85,
		SFX_86 = 0x86,
		SFX_87 = 0x87,
		SFX_88 = 0x88,
		SFX_89 = 0x89,
		SFX_8A = 0x8A,
		SFX_8B = 0x8B,
		SFX_8C = 0x8C,
		SFX_8D = 0x8D,
		SFX_8E = 0x8E,
		SFX_8F = 0x8F,

		SFX_90 = 0x90,
		SFX_91 = 0x91,
		SFX_92 = 0x92,
		SFX_93 = 0x93,
		SFX_94 = 0x94,
		SFX_95 = 0x95,
		SFX_96 = 0x96,
		SFX_97 = 0x97,
		SFX_98 = 0x98,
		SFX_99 = 0x99,
		SFX_9A = 0x9A,
		SFX_9B = 0x9B,
		SFX_9C = 0x9C,
		SFX_9D = 0x9D,
		SFX_9E = 0x9E,
		SFX_TRANSFORM = 0x9F,

		SFX_UNDERWATER_BEEP = 0xA9,
		SFX_BUMPER = 0xAA,
		SFX_SPINDASHREV = 0xAB,
		SFX_SS_WARP = 0xAF,

		SFX_SCORE_TOTAL = 0xB0,
		SFX_SPRING = 0xB1,
		SFX_ENTER_SS_RING = 0xB3,
		SFX_BOSSEXPLOSION = 0xB4,
		SFX_SPINDASH = 0xB6,
		SFX_RINGLOSS = 0xB9,
		SFX_TAILS_FLY = 0xBA,
		SFX_TAILS_TIRED = 0xBB,
		SFX_SLIDE = 0xBC,
		SFX_AIRSHIP = 0xBD,

		SFX_FAN_BIG = 0xC0,
		SFX_FAN_SMALL = 0xC1,

		SFX_WATERRUN = 0xDB,

		SFX_EMERALD = 0xE1,

		SFX_MIGHTY_DRILL = 0xC2,
		SFX_MIGHTY_LAND = 0xC3,
		SFX_MIGHTY_DEFLECT = 0xC4,
		SFX_MIGHTY_UNSPIN = 0xC5,

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

	LOADSOUND(SFX_CARNIVAL_FAN, "Sounds/CarnivalFan.wav");
	LOADSOUND(SFX_73, "Sounds/S3K_73.wav");
	LOADSOUND(SFX_VACUUM_TUBE, "Sounds/S3K_74.wav");
	LOADSOUND(SFX_BALLOON_POP, "Sounds/S3K_77.wav");
	LOADSOUND(SFX_PAD_BOUNCE, "Sounds/S3K_7B.wav");

	LOADSOUND(SFX_FAN_BIG, "Sounds/BigFan.wav");
	LOADSOUND(SFX_FAN_SMALL, "Sounds/SmallFan.wav");
	LOADSOUND(SFX_SLIDE, "Sounds/Waterfall.wav");

	LOADSOUND(SFX_IMPACT1, "Sounds/Impact1.wav");
	LOADSOUND(SFX_IMPACT2, "Sounds/Impact2.wav");
	LOADSOUND(SFX_IMPACT3, "Sounds/Impact3.wav");
	LOADSOUND(SFX_IMPACT4, "Sounds/Impact4.wav");	
	LOADSOUND(SFX_IMPACT5, "Sounds/Impact5.wav");
	LOADSOUND(SFX_IMPACT6, "Sounds/Impact6.wav");
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

	LOADSOUND(SFX_MIGHTY_DRILL, "Sounds/MightyDrill.wav");
	LOADSOUND(SFX_MIGHTY_LAND, "Sounds/MightyLand.wav");
	LOADSOUND(SFX_MIGHTY_DEFLECT, "Sounds/MightyDeflect.wav");
	LOADSOUND(SFX_MIGHTY_UNSPIN, "Sounds/MightyUnspin.wav");

	LOADSOUND(SFX_BLUEBALL, "Sounds/BlueSphere.wav");
	LOADSOUND(SFX_SPECIALSTAGE_EXIT, "Sounds/SSExit.wav");
	LOADSOUND(SFX_SPECIALSTAGE_FLYAWAY, "Sounds/SSJettison.wav");

	LOADSOUND(SFX_EMERALD, "Sounds/Emerald.wav");

	//Load Mixed mode SFX for safety
	if (!Sound::SoundBank[0xFF] || strcmp(Sound::SoundBank[0xFF]->Name, "Mixed/Music/Invincible.ogg")) Sound::SoundBank[0xFF] = new ISound("Mixed/Music/Invincible.ogg", true);
	if (!Sound::SoundBank[0xFE] || strcmp(Sound::SoundBank[0xFE]->Name, "Mixed/Music/Sneakers.ogg")) Sound::SoundBank[0xFE] = new ISound("Mixed/Music/Sneakers.ogg", true);
	if (!Sound::SoundBank[0xFD] || strcmp(Sound::SoundBank[0xFD]->Name, "Mixed/Music/Drowning.ogg")) Sound::SoundBank[0xFD] = new ISound("Mixed/Music/Drowning.ogg", true);
	if (!Sound::SoundBank[0xFC] || strcmp(Sound::SoundBank[0xFC]->Name, "Mixed/Music/ActComplete.ogg")) Sound::SoundBank[0xFC] = new ISound("Mixed/Music/ActComplete.ogg", true);
	if (!Sound::SoundBank[0xFB] || strcmp(Sound::SoundBank[0xFB]->Name, "Mixed/Music/1up.ogg")) Sound::SoundBank[0xFB] = new ISound("Mixed/Music/1up.ogg", false);

	if (!Sound::SoundBank[0xF2] || strcmp(Sound::SoundBank[0xF2]->Name, "Mixed/Music/Knuckles.ogg")) Sound::SoundBank[0xF2] = new ISound("Mixed/Music/Knuckles.ogg", true);
	if (!Sound::SoundBank[0xF1] || strcmp(Sound::SoundBank[0xF1]->Name, "Mixed/Music/Miniboss.ogg")) Sound::SoundBank[0xF1] = new ISound("Mixed/Music/Miniboss.ogg", true);
	if (!Sound::SoundBank[0xF0] || strcmp(Sound::SoundBank[0xF0]->Name, "Mixed/Music/Boss.ogg")) Sound::SoundBank[0xF0] = new ISound("Mixed/Music/Boss.ogg", true);

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

PUBLIC STATIC void Sound::LoadStream(int sound, const char* file, bool loop, int lp, bool override) {
	if (!Sound::SoundBank[sound] || strcmp(Sound::SoundBank[sound]->Name, file) != 0 || override) {
		Sound::SoundBank[sound] = new ISound(file, true);

		Sound::Audio->LoopPoint[sound] = lp;
		Sound::Audio->Loop[sound] = loop;
	}
}

PUBLIC STATIC void Sound::PlayStream(int sound, const char* file, bool loop, int lp, int at, bool override) {
	if (!Sound::SoundBank[sound] || !Audio->IsPlayingMusic(Sound::SoundBank[sound]) || strcmp(Sound::SoundBank[sound]->Name, file) != 0 || override) {
		Sound::LoadStream(sound, file, loop, lp, true);
		Sound::Audio->PushMusicAt(Sound::SoundBank[sound], at, loop, lp);
	}
}
