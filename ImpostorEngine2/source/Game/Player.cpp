#include <Game/Player.h>
#include <Engine/IResources.h>
#include <Engine/IGraphics.h>

#include <Game/Explosion.h>
#include <Game/BubbleCountdown.h>

// Find:    #([A-f0-9]+) ([A-f0-9]+) ([A-f0-9]+) ([A-f0-9]+)
// Replace: 0x$3$2$1,

Uint32 SonicPaletteNormal[6] = {
	// Just blue
	0x00000080,
	0x000038C0,
	0x000068F0,
	0x001888F0,
	0x0030A0F0,
	0x0068D0F0,
};
Uint32 SonicPaletteSuper[6] = {
	// Just gold
	0x00F0C000,
	0x00F0D028,
	0x00F0E040,
	0x00F0E860,
	0x00F0E898,
	0x00F0E8D0,
};

Uint32 SonicPaletteSuperPulse[6] = {
	0x00F0D898,
	0x00F0E0B0,
	0x00F0E8C0,
	0x00F0F0D8,
	0x00F0F0F0,
	0x00F0F0F8,
};

Uint32 TailsPaletteNormal[6] = {
	0x800801,
	0xB01801,
	0xD05001,
	0xE07808,
	0xE89008,
	0xF0A801,
};
Uint32 TailsPaletteSuper[6] = {
	0xF03830,
	0xF06848,
	0xF09860,
	0xF0B868,
	0xF0C870,
	0xF0D870,
};
Uint32 TailsPaletteSuperPulse[6] = {
	0x800801,
	0xB01801,
	0xD05001,
	0xE07808,
	0xE89008,
	0xF0A801,
};

Uint32 KnuxPaletteNormal[6] = {
	0x580818,
	0x980130,
	0xD00840,
	0xE82858,
	0xF06080,
	0xF08088,
};
Uint32 KnuxPaletteSuper[6] = {
	0xF05878,
	0xF06090,
	0xF080A0,
	0xF098B0,
	0xF0B0C8,
	0xF0C0C8,
};
Uint32 KnuxPaletteSuperPulse[6] = {
	0x580818,
	0x980130,
	0xD00840,
	0xE82858,
	0xF06080,
	0xF08088,
};

Uint32 SonicPaletteNormalHCZ[6] = {
	0x200888,
	0x3020C8,
	0x3840F0,
	0x4070F0,
	0x4098F0,
	0x40C0F0,
};
Uint32 SonicPaletteSuperHCZ[6] = {
	0x88C880,
	0x68E090,
	0x50F098,
	0x68F0C0,
	0x78F0C8,
	0xA0F0D8,
};
Uint32 SonicPaletteSuperPulseHCZ[6] = {
	0x60E898,
	0x48F0A0,
	0x58F0B0,
	0x68F0C0,
	0x90F0D0,
	0xA0F0D8,
};

Uint32 TailsPaletteNormalHCZ[6] = {
	0x880808,
	0xA03810,
	0xA05848,
	0xB07058,
	0xC08068,
	0xC89078,
};
Uint32 TailsPaletteSuperHCZ[6] = {
	0xCC6161,
	0xDC8462,
	0xD5978A,
	0xDEA893,
	0xE6B09D,
	0xEABAA7,
};
Uint32 TailsPaletteSuperPulseHCZ[6] = {
	0x880808,
	0xA03810,
	0xA05848,
	0xB07058,
	0xC08068,
	0xC89078,
};

Uint32 KnuxPaletteNormalHCZ[6] = {
	0x181050,
	0x301090,
	0x5018A8,
	0x8828C0,
	0xA048C0,
	0xB868C8,
};
Uint32 KnuxPaletteSuperHCZ[6] = {
	0x746DA3,
	0x7F65D0,
	0x9768E0,
	0xC070EF,
	0xD086EB,
	0xDE9CED,
};
Uint32 KnuxPaletteSuperPulseHCZ[6] = {
	0x181050,
	0x301090,
	0x5018A8,
	0x8828C0,
	0xA048C0,
	0xB868C8,
};

Uint32 SonicPaletteS3Normal[3] = {
	0x6666EE,
	0x2244CC,
	0x222288,
};
Uint32 SonicPaletteS3Super[3] = {
	0xEEEE88,
	0xEEEE00,
	0xAAAA00,
};
Uint32 SonicPaletteS3SuperPulse[3] = {
	0xEEEECC,
	0xEEEECC,
	0xEEEEAA,
};

Uint32 SonicPaletteS3Hyper[17] = {
	0x00ACCEFF,
	0x0090ACFF,
	0x00CEFFCE,
	0x00ACFFAC,
	0x0000FF34,
	0x00CEFFAC,
	0x00CEFF57,
	0x00CECE00,
	0x00FFFFCE,
	0x00FFFF90,
	0x00FFCE57,
	0x00FFCECE,
	0x00FFACAC,
	0x00FFCEFF,
	0x00CEACCE,
};

Uint32 SonicPaletteS3HyperBlend[16] = {
	0x00F693F2,
	0x00F4FFF4,
	0x0030FF14,
	0x00FFFFCC,
	0x00CEFF8B,
	0x00DFF3FC,
	0x00FFFB56,
	0x00FFFFC8,
	0x00FFF69B,
	0x00FFDE52,
	0x00FFFDF4,
	0x00FFE693,
	0x00FFF7F2,
	0x00FFDFCB,
	0x007B7078, // This one is iffy. But is a Gray Color. Also was blended with 0, 0, 0 in RGB for some odd reason.
	0x008DF4FF,
};

Uint32 SonicPaletteS3HyperExtended[31] = {
	0x00ACCEFF,
	0x00F693F2,
	0x0090ACFF,
	0x00F4FFF4,
	0x00CEFFCE,
	0x0030FF14,
	0x00ACFFAC,
	0x00FFFFCC,
	0x0000FF34,
	0x00CEFF8B,
	0x00CEFFAC,
	0x00DFF3FC,
	0x00CEFF57,
	0x00FFFB56,
	0x00CECE00,
	0x00FFFFC8,
	0x00FFFFCE,
	0x00FFF69B,
	0x00FFFF90,
	0x00FFDE52,
	0x00FFCE57,
	0x00FFFDF4,
	0x00FFCECE,
	0x00FFE693,
	0x00FFACAC,
	0x00FFF7F2,
	0x00FFCEFF,
	0x00FFDFCB,
	0x00CEACCE,
	0x007B7078,    // This one is iffy. But is a Gray Color. Also was blended with 0, 0, 0 in RGB for some odd reason.
	0x008DF4FF,
};

Uint32 SonicPaletteS3HyperPulse[3] = {
	0xEEEECC,
	0xEEEECC,
	0xEEEEAA,
};

Uint32 SonicPaletteS3NormalHCZ[3] = {
	0x2288AA,
	0x006688,
	0x004466,
};
Uint32 SonicPaletteS3SuperHCZ[3] = {
	0xCCEE88,
	0xAAEE44,
	0x88AA44,
};
Uint32 SonicPaletteS3SuperPulseHCZ[3] = {
	0xEEEECC,
	0xCCEECC,
	0xCCEEAA,
};

enum class AnimationEnum {
	Idle = 0,
	Bored1,
	Bored2,
	LookUp,
	Crouch,
	Walk,
	AirWalk,
	Jog,
	Run,
	Dash,
	Jump,
	SpringTwirl,
	SpringDiagonal,
	Skid,
	SkidTurn,
	Spindash,
	Dropdash,
	Push,
	Hurt,
	Die,
	Drown,
	Balance1,
	Balance2,
	SpringCS,
	StandCS,
	Fan,
	Victory,
	OuttaHere,
	Hang,
	HangMove,
	PoleSwingV,
	PoleSwingH,
	ShaftSwing,
	Turntable,
	Twister,
	SpiralRun,
	Stick,
	PulleyHold,
	ShimmyIdle,
	ShimmyMove,
	Bubble,
	Breathe,
	Ride,
	Cling,
	Bungee,
	TwistRun,
	Flume,
	Transform,
	Fly,
	FlyTired,
	FlyLift,
	FlyLiftTired,
	Swim,
	SwimTired,
	SwimLift,

	LedgePullup = 16,
	Glide = 48,
	GlideDrop,
	GlideLand,
	GlideSlide,
	ClimbIdle,
	ClimbUp,
	ClimbDown,

	Hang2 = 16,
	RayFlyUp = 48,
	RayFlyDown,

	MightyDrillDrive = 16
};

IPlayer::IPlayer() {
	EZX = 512;
	EZY = 64;
	W = 22;
	H = 40;
	OrigH = H;
	DropDashEnabled = false;

	ModeSin[0] = 0;
	ModeSin[1] = 1;
	ModeSin[2] = 0;
	ModeSin[3] = -1;

	ModeCos[0] = 1;
	ModeCos[1] = 0;
	ModeCos[2] = -1;
	ModeCos[3] = 0;

	memset(Sprites, 0, sizeof(Sprites));
}

void IPlayer::Create() {
	InputLockLeftRight = false;
	Ground = false;
	WaitTimer = -1;
	Action = ActionType::Normal;
	InputUp = false;
	InputDown = false;
	InputLeft = false;
	InputRight = false;
	InputJump = false;
	InputJumpHold = false;
	InputLeftPress = false;
	InputRightPress = false;

	Hidden = false;

	if (ReloadPlayer) {
		ShieldAnimation = 0;
		ShieldUsable = true;
		ShieldAction = false;
		//Shield = ShieldType::None;

		FlyFlag = 0;
		FlyTimer = 480;
		FlyTimerMax = 480;

		SuperForm = false;
		HyperForm = false;
		SuperFormAnim = SuperFormAnimType::None;
		Layer = 0;
		VisualLayer = 0;
		Angle = 0;
		AngleMode = 0;
		DisplayAngle = 0;
		Cutscene = false;
		RingLifeValue = 100;
		HyperRings = false;
		GroundSpeed = 0;
		XSpeed = 0;
		YSpeed = 0;
		Flip = 1;
		DisplayFlip = 1;
		CameraX = 0;
		CameraY = 0;
		InputAlarm = 0;
		Layer = 0;
		VisualLayer = 0;
		EnemyCombo = 0;

		HoldingPlayer = NULL;

		ForceRoll = false;
		CameraLookTimer = 0;
		CameraLockTimer = 0;
		GenericTimer = -1;
		ObjectControlled = 0;
		RingAlarm = 0;

		Underwater = false;
		UnderwaterTimer = 1800;

		InvincibilityTimer = 0;
		Invincibility = InvincibilityType::None;

		SpeedSneakersTimer = 0;
		SpeedSneakersActive = false;
	};

	if (Sprites[0]) { // prevent re-loading sprites on restart
		goto PlayerSetPalettes;
	}

	//Character = CharacterType::Knuckles;

	for (int a = 0; a < 256; a++) {
		this->Sin[a] = -(float)std::sin(a * M_PI / 128);
		this->Cos[a] = (float)std::cos(a * M_PI / 128);
	}

	// Flags:
	// 0x00 - None (Animation Controlled By Code)
	// 0x01 - Animation Loops
	// 0x04 - Animation Stops

	if (Character == CharacterType::Sonic) {
		H = 40;
		OrigH = H;
		DropDashEnabled = true; // Default to true for now.
		if (!Thremixed) {
			int i = 0;
			Sprites[0] = new ISprite("Sprites/Players/S3/Sonic.gif", App);

			Sprites[0]->LoadAnimation("Sprites/Players/S3/Sonic.bin");
			for (; i < Sprites[0]->AnimCount; i++) {
				AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
			}

			Sprites[0]->LoadAnimation("Sprites/Players/S3/Super Sonic.bin");
			for (; i < Sprites[0]->AnimCount; i++) {
				AnimationMap.emplace("S_" + string(Sprites[0]->Animations[i].Name), i);
			}
		}
		else {
			bool Tria = true;
			if (Tria) {
				Sprites[0] = new ISprite("Sprites/Players/Sonic1.gif", App);
				Sprites[1] = new ISprite("Sprites/Players/Sonic2.gif", App);
				Sprites[2] = new ISprite("Sprites/Players/Sonic3.gif", App);
				Sprites[3] = new ISprite("Sprites/Players/Sonic4.gif", App);
				Sprites[4] = new ISprite("Sprites/Players/SonicCutsceneCPZ.gif", App);

				Sprites[0]->LoadAnimation("Sprites/Players/Sonicold.bin");

				int i = 0;
				for (; i < Sprites[0]->AnimCount; i++) {
					AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
				}

				Sprites[0]->LoadAnimation("Sprites/Players/SuperSonic.bin");
				for (; i < Sprites[0]->AnimCount; i++) {
					AnimationMap.emplace("S_" + string(Sprites[0]->Animations[i].Name), i);
				}

				Sprites[1]->LinkAnimation(Sprites[0]->Animations);
				Sprites[2]->LinkAnimation(Sprites[0]->Animations);
				Sprites[3]->LinkAnimation(Sprites[0]->Animations);
				Sprites[4]->LinkAnimation(Sprites[0]->Animations);

				Sprites[0]->Animations[54 + (int)AnimationEnum::Walk].AnimationSpeed = 0x100;
				Sprites[0]->Animations[54 + (int)AnimationEnum::AirWalk].AnimationSpeed = 0x100;
				Sprites[0]->Animations[54 + (int)AnimationEnum::Jog].AnimationSpeed = 0x100;
				Sprites[0]->Animations[54 + (int)AnimationEnum::Run].AnimationSpeed = 0x100;
				Sprites[0]->Animations[54 + (int)AnimationEnum::Dash].AnimationSpeed = 0x100;
				Sprites[0]->Animations[54 + (int)AnimationEnum::Jump].AnimationSpeed = 0x100;
			}
			else {
				int i = 0;
				Sprites[0] = new ISprite("Sprites/Players/S3/Sonic3MClassic.gif", App); Sprites[0]->SetTransparentColorIndex(1);
				Sprites[1] = new ISprite("Sprites/Players/S3/Sonic.gif", App);

				Sprites[0]->LoadAnimation("Sprites/Players/S3/Sonic3MClassic.bin");
				for (; i < Sprites[0]->AnimCount; i++) {
					AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
				}

				Sprites[0]->LoadAnimation("Sprites/Players/S3/Super Sonic.bin");
				for (; i < Sprites[0]->AnimCount; i++) {
					AnimationMap.emplace("S_" + string(Sprites[0]->Animations[i].Name), i);
				}

				Sprites[1]->LinkAnimation(Sprites[0]->Animations);
			}
		}
	}
	else if (Character == CharacterType::Tails) {
		H = 32;
		OrigH = H;
		if (!Thremixed) {
			int i = 0;
			Sprites[0] = new ISprite("Sprites/Players/S3/Tails.gif", App);

			Sprites[0]->LoadAnimation("Sprites/Players/S3/Tails.bin");
			Sprites[0]->LoadAnimation("Sprites/Players/S3/TailSprite.bin");
			for (; i < Sprites[0]->AnimCount; i++) {
				AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
			}
		}
		else {
			Sprites[0] = new ISprite("Sprites/Players/Tails1.gif", App);
			Sprites[1] = new ISprite("Sprites/Players/Tails2.gif", App);
			Sprites[2] = new ISprite("Sprites/Players/Tails3.gif", App);
			Sprites[3] = new ISprite("Sprites/Players/TailsCutsceneCPZ.gif", App);

			Sprites[0]->LoadAnimation("Sprites/Players/Tails.bin");
			Sprites[0]->LoadAnimation("Sprites/Players/TailSprite.bin");
			Sprites[1]->LinkAnimation(Sprites[0]->Animations);
			Sprites[2]->LinkAnimation(Sprites[0]->Animations);
			Sprites[3]->LinkAnimation(Sprites[0]->Animations);

			for (int i = 0; i < Sprites[0]->AnimCount; i++) {
				AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
			}
		}
	}
	else if (Character == CharacterType::Knuckles) {
		H = 40;
		OrigH = H;
		Thremixed = true;
		if (Scene->KnuxSprite[0]) {
			for (int i = 0; i < 5; i++) {
				Sprites[i] = Scene->KnuxSprite[i];
			}
		}
		else {
			Sprites[0] = new ISprite("Sprites/Players/Knux1.gif", App);
			Sprites[1] = new ISprite("Sprites/Players/Knux2.gif", App);
			Sprites[2] = new ISprite("Sprites/Players/Knux3.gif", App);
			Sprites[3] = new ISprite("Sprites/Players/KnuxCutsceneAIZ.gif", App);
			Sprites[4] = new ISprite("Sprites/Players/KnuxCutsceneHPZ.gif", App);

			Sprites[0]->LoadAnimation("Sprites/Players/Knux.bin");
			Sprites[1]->LinkAnimation(Sprites[0]->Animations);
			Sprites[2]->LinkAnimation(Sprites[0]->Animations);
			Sprites[3]->LinkAnimation(Sprites[0]->Animations);
			Sprites[4]->LinkAnimation(Sprites[0]->Animations);
		}

		for (int i = 0; i < Sprites[0]->AnimCount; i++) {
			AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
		}
	}
	else if (Character == CharacterType::Mighty) {
		Thremixed = true;
		Sprites[0] = new ISprite("Sprites/Players/Mighty1.gif", App);
		Sprites[1] = new ISprite("Sprites/Players/Mighty2.gif", App);
		Sprites[2] = new ISprite("Sprites/Players/Mighty2.gif", App);
		Sprites[3] = new ISprite("Sprites/Players/MightyCutsceneCPZ.gif", App);

		Sprites[0]->LoadAnimation("Sprites/Players/Mighty.bin");
		Sprites[1]->LinkAnimation(Sprites[0]->Animations);
		Sprites[2]->LinkAnimation(Sprites[0]->Animations);
		Sprites[3]->LinkAnimation(Sprites[0]->Animations);

		for (int i = 0; i < Sprites[0]->AnimCount; i++) {
			AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
		}
	}
	else if (Character == CharacterType::Ray) {
		Thremixed = true;
		Sprites[0] = new ISprite("Sprites/Players/Ray1.gif", App);
		Sprites[1] = new ISprite("Sprites/Players/Ray2.gif", App);
		Sprites[2] = new ISprite("Sprites/Players/Ray3.gif", App);
		Sprites[3] = new ISprite("Sprites/Players/RayCutsceneCPZ.gif", App);

		Sprites[0]->LoadAnimation("Sprites/Players/Ray.bin");
		Sprites[1]->LinkAnimation(Sprites[0]->Animations);
		Sprites[2]->LinkAnimation(Sprites[0]->Animations);
		Sprites[3]->LinkAnimation(Sprites[0]->Animations);

		for (int i = 0; i < Sprites[0]->AnimCount; i++) {
			AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
		}
	}

	Sprites[0]->Animations[(int)AnimationEnum::Walk].AnimationSpeed = 0x100;
	Sprites[0]->Animations[(int)AnimationEnum::AirWalk].AnimationSpeed = 0x100;
	Sprites[0]->Animations[(int)AnimationEnum::Jog].AnimationSpeed = 0x100;
	Sprites[0]->Animations[(int)AnimationEnum::Run].AnimationSpeed = 0x100;
	Sprites[0]->Animations[(int)AnimationEnum::Dash].AnimationSpeed = 0x100;
	Sprites[0]->Animations[(int)AnimationEnum::Jump].AnimationSpeed = 0x100;

	SpriteDashDust = Scene->ExplosionSprite;

	if (Thremixed) {
		SpriteShields = new ISprite("Sprites/Global/ShieldsOld.gif", App);
		SpriteShields->LoadAnimation("Sprites/Global/ShieldsOld.bin");
	}
	else {
		SpriteShields = new ISprite("Sprites/GlobalS3K/ShieldsOld.gif", App);
		SpriteShields->LoadAnimation("Sprites/GlobalS3K/ShieldsOld.bin");
	}

	SpriteShields2 = new ISprite("Sprites/Global/Shields.gif", App);
	SpriteShields2->LoadAnimation("Sprites/Global/Invincible.bin");
	SpriteShields2->LoadAnimation("Sprites/Global/Shields.bin");

	for (int i = 0; i < 8; i++) {
		if (!Sprites[i]) break;

		memcpy(Sprites[i]->PaletteAlt, Sprites[i]->Palette, 256 * 4);
		Sprites[i]->UpdatePalette();
	}

	// Set Palettes
PlayerSetPalettes:
	int palWhere;
	Uint32 *palNormal, *palNormalHCZ;

	if (!Thremixed) {
		if (Scene->TileSprite) {
			if (Scene->TileSprite->PaletteAlt) {
				memcpy(Sprites[0]->PaletteAlt, Scene->TileSprite->PaletteAlt, 16 * 4);
				Sprites[0]->Paletted = 2;
				Sprites[0]->UpdatePalette();
			}
		}
		return;
	}

	if (Character == CharacterType::Sonic) {
		palWhere = 0x40;
		palNormal = SonicPaletteNormal;
		palNormalHCZ = SonicPaletteNormalHCZ;
	}
	else if (Character == CharacterType::Tails) {
		palWhere = 0x46;
		palNormal = TailsPaletteNormal;
		palNormalHCZ = TailsPaletteNormalHCZ;
	}
	else if (Character == CharacterType::Knuckles) {
		palWhere = 0x50;
		palNormal = KnuxPaletteNormal;
		palNormalHCZ = KnuxPaletteNormalHCZ;
	}
	else {
		// Default to Sonic
		palWhere = 0x40;
		palNormal = SonicPaletteNormal;
		palNormalHCZ = SonicPaletteNormalHCZ;
	}

	for (int i = 0; i < 8; i++) {
		if (!Sprites[i]) break;

		memcpy(Sprites[i]->Palette + palWhere, palNormal, 6 * 4);
		memcpy(Sprites[i]->PaletteAlt + palWhere, palNormalHCZ, 6 * 4);
		Sprites[i]->Paletted = 2;
		Sprites[i]->UpdatePalette();
	}

}

void IPlayer::ChangeAnimation(int animationID) {
	ChangeAnimation(animationID, 0);
}

void IPlayer::ChangeAnimation(int animationID, int startFrame) {
	if (CurrentAnimation != animationID)
		CurrentFrame = startFrame * 0x100;
	CurrentAnimation = animationID;
	AnimationDone = 0;
}

void IPlayer::ChangeAnimation2(int animationID) {
	ChangeAnimation2(animationID, 0);
}

void IPlayer::ChangeAnimation2(int animationID, int startFrame) {
	CurrentFrame = startFrame << 8;
	CurrentAnimation = animationID;
	AnimationDone = 0;
}

/*

The Doomsday (original):
Super Sonic has no acceleration, when UDLR is pressed, (middle step)
Sonic's speed is set to 0x300

When jump is pressed, speed is set to 0x900 (end step)

Speed decrements by 0x40 per begin step

when hit by asteroid, speed goes to -0xC0, then
after a frame, -0x80

*/

void IPlayer::Update() {
	if (Action == ActionType::Transform)
		return;

	int16_t acc = 0xC;
	int16_t dec = 0x80;
	int16_t frc = 0xC;
	int16_t top = 0x600;
	int16_t slp = 0x20;
	int16_t slprollup = 0x14;
	int16_t slprolldown = 0x50;
	int16_t fall = 0x280;
	int16_t grv = 0x38;
	int16_t air = 0x18;
	int16_t rel = -0x400;

	HyperEnabled = SaveGame::CurrentEmeralds == 0xFFFF;

	if (Sidekick) {
		IPlayer* player = Scene->Player;
		PlayerStatus status = player->PlayerStatusTable[(player->PlayerStatusTableIndex + 0x20 - 0x10) & 0x1F];

		if (!PanicSpindashing) {
			InputUp = status.InputUp;
			InputDown = status.InputDown;
			InputLeft = status.InputLeft;
			InputRight = status.InputRight;
			InputJump = false;
			InputJumpHold = status.InputJumpHold;

			if (Ground || Action == ActionType::Fly || (InputUp && Character == CharacterType::Tails && player->Action != ActionType::Transform)) {
				InputJump = status.InputJump;
			}

			if (!InputJump) {
				if (player->Ground && player->EZY < EZY - 0x10 && player->YSpeed >= 0x0) {
					if ((IMath::abs(GroundSpeed) <= 0x100 || Angle == 0) && InputAlarm > 0) {
						InputDown = true;
						PanicSpindashing = true;
						GroundSpeed = 0;
					}
					else if (InputAlarm == 0) {
						if (Ground && !(Scene->Frame & 0x1F))
							InputJump = true;
						InputJumpHold = true;
					}
				}
			}

			if (X + W / 2 >= player->X - W / 2 &&
				Y + H / 2 >= player->Y - H / 2 &&
				X - W / 2 < player->X + W / 2 &&
				Y - H / 2 < player->Y &&
				Action == ActionType::Fly && !HoldingPlayer && player->GrabTimer == 0) {
				HoldingPlayer = player;
				HoldingPlayer->ObjectControlled = 0x80;
				HoldingPlayer->Action = ActionType::GrabFall;
			}

			if (HoldingPlayer) {
				InputUp = HoldingPlayer->InputUp;
				InputDown = HoldingPlayer->InputDown;
				InputLeft = HoldingPlayer->InputLeft;
				InputRight = HoldingPlayer->InputRight;
				InputJump = HoldingPlayer->InputJump;
				InputJumpHold = HoldingPlayer->InputJumpHold;

				if (HoldingPlayer->Ground) {
					HoldingPlayer->ObjectControlled = 0x00;
					HoldingPlayer->Action = ActionType::Normal;
					HoldingPlayer->GroundSpeed = XSpeed;
					HoldingPlayer->GrabTimer = 60;
					HoldingPlayer = NULL;
				}
				else if (InputDown && InputJump) {
					HoldingPlayer->ObjectControlled = 0x00;
					HoldingPlayer->Jump();
					HoldingPlayer->GrabTimer = 60;
					HoldingPlayer = NULL;
				}
				else if (HoldingPlayer->Action != ActionType::GrabFall) {
					HoldingPlayer->ObjectControlled = 0x00;
					HoldingPlayer->GrabTimer = 60;
					HoldingPlayer = NULL;
				}
				else {
					HoldingPlayer->Action = ActionType::GrabFall;
				}
			}

			if (Action == ActionType::Respawn) {
				VisualLayer = 1;

				if (player->EZX < EZX - 0x10)
					EZX -= 2;
				if (player->EZX > EZX + 0x10)
					EZX += 2;

				if (EZY < player->EZY)
					EZY += 1;
				else
					Action = ActionType::Normal;
				YSpeed = 0x100;
				DoCollision = true;
				ObjectControlled = 0x00;
				return;
			}
			else if (!HoldingPlayer) {
				VisualLayer = player->VisualLayer;

				if (Action != ActionType::Fly) {
					if (player->EZX < EZX - 0x10) {
						InputRight = false;
						InputLeft = true;
					}
					if (player->EZX > EZX + 0x10) {
						InputLeft = false;
						InputRight = true;
					}
				}
				else {
					if (player->EZX < EZX - 0x2) {
						InputRight = false;
						InputLeft = true;
					}
					if (player->EZX > EZX + 0x2) {
						InputLeft = false;
						InputRight = true;
					}
				}
			}
		}
		else {
			InputDown = true;
			InputJump = false;
			if (((Scene->Frame >> 3) & 1) && Action == ActionType::CrouchDown)
				InputJump = true;

			if (!(Scene->Frame & 0x3F)) {
				InputJump = false;
				InputDown = false;
				PanicSpindashing = false;
			}
		}
	}

	OnScreen = false;
	if (EZX + W / 2 >= Scene->CameraX &&
		EZY + H / 2 >= Scene->CameraY &&
		EZX - W / 2 < Scene->CameraX + App->WIDTH &&
		EZY - H / 2 < Scene->CameraY + App->HEIGHT) {
		OnScreen = true;
	}

	CheckDespawn();

	if (Action == ActionType::Dead) {
		YSpeed += grv;
		SubY += YSpeed << 8;
		return;
	}

	bool isHurt = Action == ActionType::Hurt;
	if (isHurt) {
		grv = 0x30;
		if (Underwater)
			grv /= 2;
	}

	if (Angle < 0)
		Angle += 0x100;
	Angle &= 0xFF;

	// Underwater checker
	if (Action != ActionType::Respawn) {
		if (!Underwater && EZY >= Scene->WaterLevel) {
			Underwater = true;

			XSpeed >>= 1;
			if (Action != ActionType::Spring)
				YSpeed >>= 2;

			switch (Shield) {
			case ShieldType::Fire:
			case ShieldType::Electric:
				Shield = ShieldType::None;
				break;
			default:
				break;
			}

			if (YSpeed != 0 && Action != ActionType::InStream && Action != ActionType::InStreamGrab) {
				Explosion* watersplash = new Explosion();
				watersplash->G = G;
				watersplash->App = App;
				watersplash->CurrentAnimation = 1;
				watersplash->FlipX = false;
				watersplash->Active = true;
				watersplash->Sprite = Scene->WaterSprite;
				watersplash->X = EZX;
				watersplash->Y = Scene->WaterLevel;
				Scene->Explosions.push_back(watersplash);
				Sound::Play(Sound::SFX_SPLASH);

				Scene->WaterEnteredCounter++;
			}
		}
		else if (Underwater && EZY < Scene->WaterLevel) {
			if (YSpeed >= -0x400 && ObjectControlled == 0 && Action != ActionType::Hurt)
				YSpeed <<= 1;

			if (YSpeed < -0x1000)
				YSpeed = -0x1000;

			App->Audio->RemoveMusic(Sound::SoundBank[0xFD]);

			if (YSpeed != 0) {
				Explosion* watersplash = new Explosion();
				watersplash->G = G;
				watersplash->App = App;
				watersplash->CurrentAnimation = 1;
				watersplash->FlipX = false;
				watersplash->Active = true;
				watersplash->Sprite = Scene->WaterSprite;
				watersplash->X = EZX;
				watersplash->Y = Scene->WaterLevel;
				Scene->Explosions.push_back(watersplash);
				Sound::Play(Sound::SFX_SPLASH);

				Scene->WaterEnteredCounter++;
			}
			Underwater = false;
		}
	}

	int superflag = 0;
	if ((SuperForm || HyperForm) && Character == CharacterType::Sonic)
		superflag = 54;

	if (Underwater) {
		acc = 0x6;
		dec = 0x40;
		frc = 0x6;
		top = 0x300;
		slp = 0x20;
		slprollup = 0x14;
		slprolldown = 0x50;
		fall = 0x280;
		grv = 0x10;
		air = 0xC;
		rel = -0x200;

		SpeedSneakersActive = false;
	}
	if (SpeedSneakersActive) {
		acc *= 2;
		top *= 2;
		air *= 2;
		frc *= 2;
	}
	if (SuperForm || HyperForm) {
		acc = 0x30;
		dec = 0x100;
		frc = 0xC;
		top = 0xA00 + (SpeedSneakersActive << 9);
		air = 0x60;

		if (Character != CharacterType::Sonic) {
			top -= 0x200;
			air /= 2;
		}

		if (Underwater) {
			top /= 2;
			acc /= 2;
			air /= 2;
		}
	}

	switch (Character) {
		case CharacterType::Knuckles:
		case CharacterType::Mighty:
			PushSpeed = 0x4000;
			break;
		case CharacterType::Sonic:
		case CharacterType::Tails:
		case CharacterType::Ray:
		default:
			PushSpeed = 0x1000;
			break;
	}

	H = OrigH;

	switch (Action) {
	case ActionType::Fan:
		Ground = false;
		grv = 0;
		JumpVariable = 1;
		break;
	case ActionType::Glide:
	{
		int Flip = IMath::sign(DisplayFlip);
		grv = 0x0;
		H = 32;

		if (YSpeed < 0x80) YSpeed += 0x20;
		if (YSpeed > 0x80) YSpeed -= 0x20;

		if (SuperForm || HyperForm) {
			if (XSpeed < 0)
				XSpeed -= 0xC;
			else
				XSpeed += 0xC;
		}
		else {
			if (XSpeed < 0)
				XSpeed -= 0x4;
			else
				XSpeed += 0x4;
		}

		if (Flip > 0) {
			if (XSpeed < 0)
				XSpeed = 0;
		}
		else {
			if (XSpeed > 0)
				XSpeed = 0;
		}

		if (Scene->CollisionAtClimbable(EZX + 12 * Flip, EZY - 10, NULL, XSpeed < 0 ? 3 : 1, this)) {
			if (SuperForm && IMath::abs(XSpeed) >= 0x480) {
				// Sound::Play(0x49);
				// Scene->ShakeTimer = 14;
			}
			else {
				Sound::Play(Sound::SFX_GRAB);
			}

			DisplayFlip = Flip;
			XSpeed = 0;
			Action = ActionType::Climb;

			// To make sure Knuckles is properly on the wall
			while (Scene->CollisionAtClimbable(EZX + 10 * DisplayFlip, EZY - 10, NULL, DisplayFlip < 0 ? 3 : 1, this))
				EZX -= DisplayFlip;
			while (!Scene->CollisionAtClimbable(EZX + 10 * DisplayFlip, EZY - 10, NULL, DisplayFlip < 0 ? 3 : 1, this))
				EZX += DisplayFlip;
		}

		if (!InputJumpHold) {
			Action = ActionType::GlideFall;
			XSpeed /= 4;
			grv = 0x38;
		}
		break;
	}
	case ActionType::GlideSlide:
	{
		frc = 0x20;
		H = 32;

		InputAlarm = 3;

		if (!InputJumpHold) {
			GroundSpeed = 0;
		}
		if (GroundSpeed == 0) {
			H = OrigH;

			while (Scene->CollisionAt(EZX, EZY + H / 2 - 1, NULL, 0, this))
				EZY--;
		}

		if (!Ground) {
			Action = ActionType::GlideFall;
			grv = 0x38;
		}
		break;
	}
	case ActionType::Climb:
	{
		int Flip = IMath::sign(DisplayFlip);
		grv = 0;
		air = 0;
		YSpeed = 0;
		XSpeed = 0;
		if (!SuperForm && !HyperForm) {
			if (InputUp) {
				YSpeed = -0x100;
			}
			else if (InputDown) {
				YSpeed = 0x100;
			}
		}
		else {
			if (InputUp) {
				YSpeed = -0x200;
			}
			else if (InputDown) {
				YSpeed = 0x200;
			}
		}

		if (!Scene->CollisionAtClimbable(EZX + 12 * Flip, EZY - 10, NULL, Flip < 0 ? 3 : 1, this)) {
			if (YSpeed >= 0) {
				Action = ActionType::GlideFall;
				ChangeAnimation((int)AnimationEnum::GlideDrop, 2);
			}
			else {
				Action = ActionType::ClimbRise;
				StoredX = EZX;
				StoredY = EZY;
			}
		}

		if (InputJump) {
			Jump();
			XSpeed = Flip * -0x400;
			YSpeed = -0x400;
			InputJump = false;
		}
		break;
	}
	case ActionType::ClimbRise:
		grv = 0;
		air = 0;
		XSpeed = 0;
		YSpeed = 0;
		break;
	case ActionType::RayGlide:
	{
		// sub_4CD660
		if (Angle == 1) { // Is Facing Up
			if (GlideTurnCos < 0x70)
				GlideTurnCos += 8;
		}
		else {
			if (GlideTurnCos > 0x10)
				GlideTurnCos -= 8;
		}

		if (GlideSpeedStore != 0) {
			YSpeed += GlideSpeedStore >> (2 - Underwater);
			if (YSpeed < GlideSpeedStore) {
				YSpeed = GlideSpeedStore;
				GlideSpeedStore = 0;
			}
		}
		else {
			YSpeed += 0x38 * GlideTurnCos >> 9;
		}

		if (YSpeed < -0x600)
			YSpeed = -0x600;

		if (Angle == 1) {
			grv = 0;
			air = 0;
			int tempYSpeed = YSpeed;
			if (tempYSpeed > 0x100)
				YSpeed = tempYSpeed - (tempYSpeed >> 2);
		}

		int storedYSpeed = YSpeed;
		if (storedYSpeed <= 0) {
			MaxGlideSpeed -= (22 * (0x50 - GlideTurnCos)) >> 6;
			if (MaxGlideSpeed < 0x400)
				MaxGlideSpeed = 0x400;
		}
		else if (storedYSpeed > MaxGlideSpeed) {
			MaxGlideSpeed = storedYSpeed - (storedYSpeed >> 6);
		}

		if (XSpeed) {
			int v23 = 0x50 - GlideTurnCos;
			if (DisplayFlip < 0) {
				XSpeed -= (0x16 * v23 >> (int)Underwater) >> 6;
				if (XSpeed > -0x100)
					XSpeed = -0x100;

				int signedMaxGlideSpeed = -MaxGlideSpeed;
				if (XSpeed < signedMaxGlideSpeed)
					XSpeed = signedMaxGlideSpeed;
			}
			else {
				XSpeed += (0x16 * v23 >> (int)Underwater) >> 6;
				if (XSpeed < 0x100)
					XSpeed = 0x100;

				int signedMaxGlideSpeed = MaxGlideSpeed;
				if (XSpeed > signedMaxGlideSpeed)
					XSpeed = signedMaxGlideSpeed;
			}
		}

		int v7 = 0; // 1A8
		if (v7) {
			// 1A8
		}
		else {
			bool did = true;
			if (DisplayFlip < 0) {
				if (!InputRight || GlideTurnCos != 0x10) {
					if (InputLeft && GlideTurnCos == 0x70 && Angle == 1) {
						GlideSpeedStore = 0;
						Angle = 0;
						ChangeAnimation((int)AnimationEnum::RayFlyDown, 0);
						Sound::Play(Sound::SFX_RAY_DIVE);
					}
					did = false;
				}
			}
			else if (!InputLeft || GlideTurnCos != 0x10) {
				if (InputRight && GlideTurnCos == 0x70 && Angle == 1) {
					GlideSpeedStore = 0;
					Angle = 0;
					ChangeAnimation((int)AnimationEnum::RayFlyDown, 0);
					Sound::Play(Sound::SFX_RAY_DIVE);
				}
				did = false;
			}

			if (did && !Angle) {
				bool ySpeedGreaterThan = YSpeed > 0x280 && false;
				bool ySpeedEquals = YSpeed == 0x280;
				bool ySpeedLessThan = YSpeed < 0x280;

				Angle = 1;

				if (!((ySpeedLessThan != ySpeedGreaterThan) || ySpeedEquals)
					|| RayBoostCount == 0x100
					|| (Underwater && YSpeed > 0x180)) {
					int YCalcSpeed = YSpeed;
					if (YCalcSpeed < 0) {
						YCalcSpeed = -YCalcSpeed;
					}

					/*
					int XCalcSpeed = XSpeed;
					if (XCalcSpeed < 0) {
						XCalcSpeed = -XSpeed;
					}

					int speedStore = -(RayBoostCount * ((YCalcSpeed >> 1) + (XCalcSpeed >> 2) + (YCalcSpeed >> 4)) >> 8);
					*/

					int speedStore = -(RayBoostCount * ((YCalcSpeed >> 1) + (YCalcSpeed >> 2) + (YCalcSpeed >> 4)) >> 8);
					GlideSpeedStore = speedStore;
					if (Underwater)
						GlideSpeedStore = (speedStore >> 1) + (speedStore >> 3);
					if (RayBoostCount > 0x10)
						RayBoostCount = RayBoostCount - 0x20;
					if (GlideSpeedStore < -0x600)
						GlideSpeedStore = -0x600;
				}
				ChangeAnimation((int)AnimationEnum::RayFlyUp, 0);
				Sound::Play(Sound::SFX_RAY_SWOOP);
			}
		}

		if (!InputJumpHold || XSpeed == 0 || EZY < Scene->CameraY) {
			Action = ActionType::Jumping;
			JumpVariable = 0;
			Sound::Stop(Sound::SFX_RAY_DIVE);
			Sound::Stop(Sound::SFX_RAY_SWOOP);
		}
		break;
	}
	case ActionType::Fly:
	{
		if (Underwater && HoldingPlayer) {
			FlyFlag = 0;
		}
		else {
			if (YSpeed < -0x100)
				FlyFlag = 0x8;

			if (InputJump && FlyTimer > 0) {
				FlyFlag = -0x20;
			}
		}

		if (InputJump && InputDown) {
			FlyTimer = 0;
			Action = ActionType::Jumping;
			JumpVariable = 0;
		}

		if (!Underwater && !(Scene->Frame & 0xF)) {
			if (FlyTimer > 0)
				Sound::Play(Sound::SFX_TAILS_FLY);
			else
				Sound::Play(Sound::SFX_TAILS_TIRED);
		}

		grv = FlyFlag;

		if (FlyTimer > 0)
			FlyTimer--;
		break;
	}
	case ActionType::Spring:
	case ActionType::Jumping:
		H = 32;
		break;
	case ActionType::Slide:
		if (!(Scene->Frame & 0x1F))
			Sound::Play(Sound::SFX_SLIDE);
		break;
	default:
		break;
	}

	bool IUp = InputUp;
	bool IDown = InputDown;
	bool IJump = InputJump;
	bool ILeft = InputLeft;
	bool IRight = InputRight;
	bool IJumpHold = InputJumpHold;

	if (ObjectControlled != 0 || ForceRoll || isHurt || ControlLocked) {
		InputUp = false;
		InputDown = false;
		InputLeft = false;
		InputRight = false;

		if ((ObjectControlled >> 7 & 1) == 1) {
			InputJump = false;
			InputJumpHold = false;
		}
	}

	if (InputLockLeftRight) {
		InputUp = false;
		InputDown = false;
		InputJump = false;
		InputJumpHold = false;
	}

	if (ObjectControlled == 0) {
		DoCollision = true;
	}

	if (Action == ActionType::Grab) {
		DoCollision = false;
	}

	if (Action == ActionType::InStream) {
		if (InputUp)
			YSpeed = -0x120;
		if (InputDown)
			YSpeed = 0xC0;
	}
	if (Action == ActionType::InStreamGrab) {
		grv = 0;
		YSpeed = 0;
		XSpeed = 0;
		if (InputUp)
			YSpeed = -0x100;
		if (InputDown)
			YSpeed = 0x100;
	}

	if (ForceRoll) {
		Action = ActionType::Rolling;
		if (IMath::abs(GroundSpeed) < 0x100) {
			GroundSpeed = 0x580;
		}
	}

	if (InputUp || InputDown || InputLeft || InputRight || InputJump) {
		if (Action == ActionType::CancelableAnim)
			Action = ActionType::Normal;
	}

	if (InputUp || InputDown || InputLeft || InputRight || InputJump || InputJumpHold || !Ground || XSpeed != 0) {
		WaitTimer = 180;

		//if (Ground) {
		if (Action == ActionType::Bored1)
			Action = ActionType::Normal;
		//}
	}

	bool doRollFriction =
		Action == ActionType::Rolling ||
		Action == ActionType::Slide;

	if (!doRollFriction) {
		GroundSpeed -= (slp * IMath::sinHex(Angle)) >> 16;
	}
	else {
		if (IMath::sign(GroundSpeed) == IMath::sign(IMath::sinHex(Angle)))
			GroundSpeed -= (slprollup * IMath::sinHex(Angle)) >> 16;
		else
			GroundSpeed -= (slprolldown * IMath::sinHex(Angle)) >> 16;
	}

	bool doLeftRight =
		Action != ActionType::InStreamGrab &&
		Action != ActionType::CrouchDown &&
		Action != ActionType::Spindash &&
		Action != ActionType::LookUp &&
		Action != ActionType::RayGlide &&
		Action != ActionType::Glide &&
		Action != ActionType::GlideFallLand &&
		Action != ActionType::Climb &&
		Action != ActionType::ClimbRise &&
		Action != ActionType::Slide;

	if (Action == ActionType::Corkscrew)
		frc = 0x6;

	if (Action == ActionType::Skid) {
		if (DisplayFlip > 0) {
			if (GroundSpeed <= 0) {
				Action = ActionType::CancelableAnim;
				ChangeAnimation((int)AnimationEnum::SkidTurn + superflag);
			}
		}
		else {
			if (GroundSpeed >= 0) {
				Action = ActionType::CancelableAnim;
				ChangeAnimation((int)AnimationEnum::SkidTurn + superflag);
			}
		}
		if ((!InputLeft && GroundSpeed > 0) || (!InputRight && GroundSpeed < 0)) {
			Action = ActionType::Normal;
			ChangeAnimation((int)AnimationEnum::Walk + superflag);
		}
	}

	if (doLeftRight && InputLeft && InputAlarm == 0) {
		if (Action == ActionType::Rolling) {
			if (GroundSpeed > 0) {
				GroundSpeed -= 0x20;
			}
		}
		else {
			if (GroundSpeed >= 0x480 && Action != ActionType::Skid && Ground) {
				Action = ActionType::Skid;
				DisplayFlip = 1;
				Sound::Play(Sound::SFX_SKID);
			}
			else if (Action != ActionType::Skid)
				DisplayFlip = -1;

			if (Ground) {
				if (GroundSpeed > 0) {
					GroundSpeed -= dec;
				}
				else if (GroundSpeed > -top) {
					GroundSpeed -= acc;
				}
			}
			else {
				if (XSpeed > -top)
					XSpeed -= air;
			}
		}
	}
	else if (doLeftRight && InputRight && InputAlarm == 0) {
		if (Action == ActionType::Rolling) {
			if (GroundSpeed < 0) {
				GroundSpeed += 0x20;
			}
		}
		else {
			if (GroundSpeed <= -0x480 && Action != ActionType::Skid && Ground) {
				Action = ActionType::Skid;
				DisplayFlip = -1;
				Sound::Play(Sound::SFX_SKID);
			}
			else if (Action != ActionType::Skid)
				DisplayFlip = 1;

			if (Ground) {
				if (GroundSpeed < 0) {
					GroundSpeed += dec;
				}
				else if (GroundSpeed < top) {
					GroundSpeed += acc;
				}
			}
			else {
				if (XSpeed < top)
					XSpeed += air;
			}
		}
	}
	else {
		if (!doRollFriction)
			GroundSpeed -= IMath::min(IMath::abs(GroundSpeed), frc) * IMath::sign(GroundSpeed);
	}
	if (doRollFriction)
		GroundSpeed -= IMath::min(IMath::abs(GroundSpeed), frc / 2) * IMath::sign(GroundSpeed);

	// Flip player when hitting left/right
	if (doLeftRight && InputAlarm == 0) {
		if (InputLeft) {
			if (Action != ActionType::Skid && Action != ActionType::Rolling)
				DisplayFlip = -1;
		}
		else if (InputRight) {
			if (Action != ActionType::Skid && Action != ActionType::Rolling)
				DisplayFlip = 1;
		}
	}

	switch (Action) {
	case ActionType::Normal:
	{
		if (GroundSpeed == 0 && InputUp && Ground) {
			CameraLookTimer = 0;
			Action = ActionType::LookUp;
		}
		break;
	}
	case ActionType::CrouchDown:
		if (!InputDown) {
			Action = ActionType::CancelableAnim;
		}
		break;
	case ActionType::LookUp:
		if (!InputUp)
			Action = ActionType::CancelableAnim;
		break;
	case ActionType::Rolling:
		if (!ManiaPhysics && IMath::abs(GroundSpeed) < 0x80)
			Action = ActionType::Normal;
		else if (ManiaPhysics && GroundSpeed == 0x00)
			Action = ActionType::Normal;
		break;
	default:
		break;
	}

	if (InputAlarm > 0)
		InputAlarm--;

	WallLeft = false;
	WallRight = false;
	LastObject = NULL;

	HandleMonitors(); // handle breakable objects before collision, so that solids dont override breakability

	/// BEGIN COLLISION
	int angleOut;
	int SensorEFWidth = 10;
	// AIZ1 Loop Hack
	bool AngelIslandTriLoopFlag = false;
	if (Scene->ZoneID == 1 && Scene->Act == 1 && AngleMode == 1 &&
		EZX > 0x2B40 && EZX < 0x2B54 &&
		EZY > 0x388 && EZY < 0x3F0) {
		AngelIslandTriLoopFlag = true;
		AngleIslandFlag = true;
		EZX = 0x2B60 - H / 2;
	}
	if (AngleIslandFlag && (EZY < 0x35B || GroundSpeed < 0 || YSpeed > 0 || !Ground)) {
		AngleIslandFlag = false;
		AngelIslandTriLoopFlag = false;
	}
	if (AngelIslandTriLoopFlag)
		SensorEFWidth = -1;

	// Handle ABCD Sensors (Floor and ceiling collisions)
	int CheckStepsMax = 4;
	int CheckSteps = CheckStepsMax;
	bool CanModeChange = true;

	if (Ground) {
		XSpeed = (GroundSpeed * IMath::cosHex(Angle)) >> 16;
		YSpeed = (GroundSpeed * -IMath::sinHex(Angle)) >> 16;
	}
	else {
		if (Action != ActionType::InStream) {
			YSpeed += grv;
			if (YSpeed > 0x1000) YSpeed = 0x1000;

			if (YSpeed < 0x0 && YSpeed > -0x400) {
				XSpeed -= XSpeed / 0x20;
			}
		}
	}

	while (CheckSteps--) {
		// Handle EF sensors (Wall collisions)
		if (Ground) {
			int angleOut;
			int SensorEFPos = EZY;
			if (Angle == 0)
				SensorEFPos = EZY + 8;
			if (DisplayAngle == 0 && AngleMode == 0)
				SensorEFPos = EZY + 8;

			if (AngleMode != 0 && AngleMode != 2) {
				//SensorEFPos -= EZY - EZX;
			}

			// Check Sensor E
			SensorE = -1;
			for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
				if (Scene->CollisionAt(EZX - (1 + x), SensorEFPos, &angleOut, (AngleMode + 3) & 3, this)) {
					if (angleOut == 0)
						angleOut = AngleMode * 0x40;
					SensorE = x;
					break;
				}
			}
			if (SensorE <= SensorEFWidth && SensorE >= 0 && GroundSpeed * ModeCos[AngleMode] < 0 && (AngleMode == 0 || AngleMode == 2)) {
				EZX = (EZX - 1 + (SensorEFWidth + 1 - SensorE));
				WallLeft = true;
				GroundSpeed = 0;
				XSpeed = 0;
			}

			// Check Sensor F
			SensorF = -1;
			for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
				if (Scene->CollisionAt(EZX + (1 + x), SensorEFPos, &angleOut, (AngleMode + 1) & 3, this)) {
					if (angleOut == 0)
						angleOut = AngleMode * 0x40;
					SensorF = x;
					break;
				}
			}
			if (SensorF <= SensorEFWidth && SensorF >= 0 && GroundSpeed * ModeCos[AngleMode] > 0 && (AngleMode == 0 || AngleMode == 2)) {
				EZX = (EZX + 1 - (SensorEFWidth + 1 - SensorF));
				WallRight = true;
				GroundSpeed = 0;
				XSpeed = 0;
			}
			//*/

			if (IMath::abs(GroundSpeed) < 0x280 && AngleMode != 0 && !ForceRoll) {
				if (Action == ActionType::Rolling) {
					SubX += (IMath::sinHex(Angle) * (H / 2 - 16));
					SubY += (IMath::cosHex(Angle) * (H / 2 - 16));
				}

				if (Angle <= 0xC0 && Angle >= 0x40) {
					if (Action == ActionType::Rolling)
						Action = ActionType::Jumping;
					Ground = false;
					GroundSpeed = 0;
					Angle = 0;
					AngleMode = 0;
					// printf("%s\n", "fell off");
				}
				InputAlarm = 30;
			}
		}
		else {
			int angleOut;
			int SensorEFPos = EZY;

			// Check Sensor E
			SensorE = -1;
			for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
				if (Scene->CollisionAt(EZX - 1 - x, SensorEFPos, &angleOut, (AngleMode + 3) & 3, this)) {
					if (angleOut == 0)
						angleOut = AngleMode * 0x40;
					SensorE = x;
					break;
				}
			}
			if (SensorE <= SensorEFWidth && SensorE >= 0 && XSpeed <= 0) {
				EZX = (EZX - 1 + (SensorEFWidth + 1 - SensorE));
				XSpeed = 0;
			}
			// Check Sensor F
			SensorF = -1;
			for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
				if (Scene->CollisionAt(EZX + 1 + x, SensorEFPos, &angleOut, (AngleMode + 3) & 3, this)) {
					if (angleOut == 0)
						angleOut = AngleMode * 0x40;
					SensorF = x;
					break;
				}
			}
			if (SensorF <= SensorEFWidth && SensorF >= 0 && XSpeed > 0) {
				EZX = (EZX + 1 - (SensorEFWidth + 1 - SensorF));
				XSpeed = 0;
			}
		}

		int SensorEFPos = EZY;
		if (Angle == 0)
			SensorEFPos = EZY + 8;
		if (DisplayAngle == 0 && AngleMode == 0)
			SensorEFPos = EZY + 8;
		if (!Ground)
			SensorEFPos = EZY;
		if (AngleMode != 0 && AngleMode != 2) {
			SensorEFPos -= EZY - EZX;
		}

		bool extraCheck = false;

		// Check Sensor E
	CheckSensorE:
		SensorE = -1;
		if (AngleMode == 0 || AngleMode == 2) {
			for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
				if (Scene->CollisionAt(EZX - x, SensorEFPos, &angleOut, (AngleMode + 3) & 3, this)) {
					if (angleOut == 0)
						angleOut = AngleMode * 0x40;
					SensorE = x;
					break;
				}
			}
			if (SensorE < 11 && SensorE >= 0 && XSpeed < 0 && ((DisplayAngle == 0 && AngleMode == 0) || Action == ActionType::InStream || !Ground || (Angle == 0) || (AngleMode == 2))) {
				EZX = EZX + (11 - SensorE);
				if (Action == ActionType::InStream)
					SubX -= (XSpeed << 9);

				if (SensorE == 0)
					goto CheckSensorE;
			}
		}
		else {
			for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
				if (Scene->CollisionAt(SensorEFPos, EZY - x, &angleOut, (AngleMode + 3) & 3, this)) {
					if (angleOut == 0)
						angleOut = AngleMode * 0x40;
					SensorE = x;
					break;
				}
			}
			if (SensorE < 11 && SensorE >= 0 && YSpeed < 0) {
				EZY = EZY + (11 - SensorE);
				if (AngleMode == 1)
					GroundSpeed = 0;
				if (SensorE == 0)
					goto CheckSensorE;
			}
		}

		// Check Sensor F
	CheckSensorF:
		SensorF = -1;
		if (AngleMode == 0 || AngleMode == 2) {
			for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
				if (Scene->CollisionAt(EZX + x, SensorEFPos, &angleOut, (AngleMode + 1) & 3, this)) {
					if (angleOut == 0)
						angleOut = AngleMode * 0x40;
					SensorF = x;
					break;
				}
			}
			if (SensorF < 11 && SensorF >= 0 && XSpeed > 0 && ((DisplayAngle == 0 && AngleMode == 0) || Action == ActionType::InStream || !Ground || (Angle == 0) || (AngleMode == 2))) {
				EZX = EZX - (11 - SensorF);
				if (Action == ActionType::InStream)
					SubX -= (XSpeed << 9);

				if (SensorF == 0)
					goto CheckSensorF;
			}
		}
		else {
			for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
				if (Scene->CollisionAt(SensorEFPos, EZY + x, &angleOut, (AngleMode + 1) & 3, this)) {
					if (angleOut == 0)
						angleOut = AngleMode * 0x40;
					SensorF = x;
					break;
				}
			}
			if (SensorF < 11 && SensorF >= 0 && YSpeed > 0) {
				EZY = EZY - (11 - SensorF);
				if (AngleMode == 3)
					GroundSpeed = 0;
				if (SensorF == 0)
					goto CheckSensorF;
			}
		}

		if ((Action != ActionType::Jumping || YSpeed < 0) && ShieldAction) {
			ShieldAction = false;
		}

		int SensorLength = H / 2;
		if (Ground || ForceRoll) {
			SensorLength += 16;
		}

		int SensorABCDWidth = 9;
		if (Action == ActionType::Jumping ||
			Action == ActionType::Rolling ||
			Action == ActionType::Spring)
			SensorABCDWidth = 7;

		// CheckSensorsAB:
		int d0 = (Angle + 0x20) & 0xFF;
		if (CanModeChange) {
			if (d0 >= 0x80) { d0 = Angle; if (d0 >= 0x80) d0--; d0 += 0x20; }
			else { d0 = Angle; if (d0 >= 0x80) d0++; d0 += 0x1F; }
			if (ForceRoll) d0++;
			switch (d0 & 0xC0) {
			case 0x00: AngleMode = 0; break;
			case 0x40: AngleMode = 3; break;
			case 0x80: AngleMode = 2; break;
			case 0xC0: AngleMode = 1; break;
			}
		}
		// Check Sensor A
		SensorA = -1;
		int SensorA_Angle = -1;
		Object* lastObj = NULL;
		for (int y = 0; y <= SensorLength && DoCollision; y++) {
			if (Scene->CollisionAt(
				EZX - SensorABCDWidth * ModeCos[AngleMode] + y * ModeSin[AngleMode],
				EZY + SensorABCDWidth * ModeSin[AngleMode] + y * ModeCos[AngleMode], &SensorA_Angle, AngleMode, this)) {
				if (!SensorA_Angle)
					SensorA_Angle = ((4 - AngleMode) & 0x3) * 0x40;
				SensorA = y;
				break;
			}
		}
		if (SensorA == 0) SensorA = -1;

		if (LastObject)
			lastObj = LastObject;

		// Check Sensor B
		SensorB = -1;
		int SensorB_Angle = -1;
		for (int y = 0; y <= SensorLength && DoCollision; y++) {
			if (Scene->CollisionAt(
				EZX + SensorABCDWidth * ModeCos[AngleMode] + y * ModeSin[AngleMode],
				EZY - SensorABCDWidth * ModeSin[AngleMode] + y * ModeCos[AngleMode], &SensorB_Angle, AngleMode, this)) {
				if (!SensorB_Angle)
					SensorB_Angle = ((4 - AngleMode) & 0x3) * 0x40;
				SensorB = y;
				break;
			}
		}
		if (SensorB == 0) SensorB = -1;

		if (!LastObject)
			LastObject = lastObj;

		// Handle falling and ground reacquisition
		if (Ground) {
			if (AngleIslandFlag && SensorEFWidth == -1 && AngelIslandTriLoopFlag) {
				Angle = 0xC0;
				AngleMode = 1;
				Ground = true;
				EZX = 0x2B60 - H / 2;
			}
			else {
				if (SensorA == -1 && SensorB == -1 && !ForceRoll) {
					XSpeed = (GroundSpeed * IMath::cosHex(Angle)) >> 16;
					YSpeed = (GroundSpeed * -IMath::sinHex(Angle)) >> 16;

					Ground = false;
					if (Action == ActionType::Rolling && !ForceRoll) {
						JumpVariable = 2;
						Action = ActionType::Jumping;
						SubX += IMath::sinHex(Angle) * (H / 2 - 16);
						SubY += IMath::cosHex(Angle) * (H / 2 - 16);
					}
					Angle = 0;
					AngleMode = 0;
					ShieldUsable = false;

					if (Action == ActionType::Skid) {
						Action = ActionType::Normal;
						ChangeAnimation((int)AnimationEnum::AirWalk + superflag);
					}
				}

				int ang = 0;
				int value = 0xFF;
				if (SensorA == -1 && SensorB != -1) {
					value = SensorB;
					ang = SensorB_Angle;
				}
				else if (SensorA != -1 && SensorB == -1) {
					value = SensorA;
					ang = SensorA_Angle;
				}
				else if (SensorA != -1 && SensorB != -1) {
					if (SensorA < SensorB) {
						value = SensorA;
						ang = SensorA_Angle;
					}
					else {
						value = SensorB;
						ang = SensorB_Angle;
					}
				}

				if (value != 0xFF) {
					if (LastObject && !extraCheck) {
						SubX += ((LastObject->XSpeed) << 8) / CheckStepsMax;
						if (LastObject->XSpeed != 0) {
							if (XSpeed == 0) {
								//*
								if (LastObject->XSpeed < 0)
									XSpeed = -1;
								else
									XSpeed = 1;
								//*/
							}
							extraCheck = true;
							// goto CheckSensorE;
						}
					}

					bool DoStick = Angle == ang;

					// Spindash from 0xCFF, lowest spin rev possible, if Y ever gets to 0xCD1, it will bug

					if (GroundSpeed != 0) {
						// smallest angle difference
						int diff = IMath::abs(((ang - Angle + 0x80) & 0xFF) - 0x80);
						if (diff < 0x28 || ForceRoll) {
							Angle = ang;
							DoStick = true;
						}
					}
					if (DoStick && CanModeChange) {
						d0 = (Angle + 0x20) & 0xFF;
						if (d0 >= 0x80) { d0 = Angle; if (d0 >= 0x80) d0--; d0 += 0x20; }
						else { d0 = Angle; if (d0 >= 0x80) d0++; d0 += 0x1F; }
						if (ForceRoll) d0++;
						switch (d0 & 0xC0) {
						case 0x00: AngleMode = 0; break;
						case 0x40: AngleMode = 3; break;
						case 0x80: AngleMode = 2; break;
						case 0xC0: AngleMode = 1; break;
						}
						if (AngleMode != 0 && !ForceRoll)
							CanModeChange = false;
					}

					if ((Angle & 0x3F) == 0 && value > H / 2 && AngleMode != 0 && !ForceRoll) DoStick = false;

					if (DoStick) {
						if (AngleMode == 0)
							SubY = (EZY + value - H / 2) << 16;
						else if (AngleMode == 1)
							SubX = (EZX + value - H / 2) << 16;
						else if (AngleMode == 2)
							SubY = (EZY - value + H / 2) << 16;
						else if (AngleMode == 3)
							SubX = (EZX - value + H / 2) << 16;
					}
				}
			}
		}
		else {
			bool Landed = false;

			int ang = 40;
			int value = 0xFF;
			if (SensorA == -1 && SensorB != -1) {
				value = SensorB - SensorLength;
				ang = SensorB_Angle;
			}
			else if (SensorA != -1 && SensorB == -1) {
				value = SensorA - SensorLength;
				ang = SensorA_Angle;
			}
			else if (SensorA != -1 && SensorB != -1) {
				if (SensorA < SensorB) {
					value = SensorA - SensorLength;
					ang = SensorA_Angle;
				}
				else {
					value = SensorB - SensorLength;
					ang = SensorB_Angle;
				}
			}

			if (value != 0xFF) {
				if (value <= 0 && YSpeed >= 0) {
					EZY += value;
					Angle = ang;
					Landed = true;
				}
			}

			if (Landed) {
				JumpVariable = 0;
			}

			// if ((SensorA == 0 || SensorB == 0) && Landed) {
			//     goto CheckSensorsAB;
			// }

			if (DropDashRev > 0 && InputJumpHold) {
				DropDashRev++;
			}
			if (DropDashRev > 0 && !InputJumpHold) {
				DropDashRev = 0;
			}
			if (DropDashRev == 71) {
				Sound::Play(Sound::SFX_DROPDASHREADY);
			}

			if (Landed) {
				if (Shield == ShieldType::Bubble && ShieldAction) {
					Ground = false;
					ShieldUsable = true;
					ShieldAction = false;
					if (Underwater)
						YSpeed = -0x400;
					else
						YSpeed = -0x780;
					XSpeed = 0;
					if (Angle > 0)
					{
						XSpeed = Angle;
						if (XSpeed < 180) { XSpeed += 180;  XSpeed = -XSpeed; }
						XSpeed = -XSpeed;
						XSpeed *= 10;
					}
					JumpVariable = 1;
				}
				else if (Action == ActionType::GlideFall) {
					XSpeed = 0;
					GroundSpeed = 0;
					if (InputDown) {
						Action = ActionType::CrouchDown;
					}
					else {
						Action = ActionType::GlideFallLand;
					}
					Ground = true;
				}
				else if (Action == ActionType::Victory) {
					XSpeed = 0;
					GroundSpeed = 0;
					Ground = true;
				}
				else if (Action == ActionType::InStream || Action == ActionType::InStreamGrab) {
				}
				else if (Action == ActionType::MightyStomp) {
					Action = ActionType::Jumping;
					//GroundSpeed = 0;
					//XSpeed = 0;
					Sound::Play(Sound::SFX_MIGHTY_LAND);
					Ground = false;

					int value = 0x100;
					if (!Underwater)
						value = 0x200;

					XSpeed = (-(value + 0x38) * IMath::sinHex(ang)) >> 16;
					YSpeed = (-(value + 0x38) * IMath::cosHex(ang)) >> 16;
					JumpVariable = 0;
					Scene->ShakeTimer = 14;

					Explosion* landdust = Scene->AddExplosion(Scene->ExplosionSprite, 0, false, X, Y + H / 2 - 4, VisualLayer);
					landdust->XSpeed = 0x100;
					landdust = Scene->AddExplosion(Scene->ExplosionSprite, 0, false, X, Y + H / 2 - 4, VisualLayer);
					landdust->XSpeed = -0x100;

					landdust = Scene->AddExplosion(Scene->ExplosionSprite, 0, false, X, Y + H / 2 - 4, VisualLayer);
					landdust->XSpeed = 0x180;
					landdust = Scene->AddExplosion(Scene->ExplosionSprite, 0, false, X, Y + H / 2 - 4, VisualLayer);
					landdust->XSpeed = -0x180;

					landdust = Scene->AddExplosion(Scene->ExplosionSprite, 0, false, X, Y + H / 2 - 4, VisualLayer);
					landdust->XSpeed = 0x200;
					landdust = Scene->AddExplosion(Scene->ExplosionSprite, 0, false, X, Y + H / 2 - 4, VisualLayer);
					landdust->XSpeed = -0x200;
				}
				else {
					if (Angle >= 0xF0 && Angle <= 0xFF)
						GroundSpeed = XSpeed;
					else if (Angle >= 0x00 && Angle <= 0x0F)
						GroundSpeed = XSpeed;
					else if (IMath::abs(XSpeed) > YSpeed) {
						GroundSpeed = XSpeed;
					}
					else {
						if (Angle >= 0xE0 && Angle <= 0xEF)
							GroundSpeed = YSpeed / 2 * -IMath::sign(IMath::sinHex(Angle));
						else if (Angle >= 0x10 && Angle <= 0x1F)
							GroundSpeed = YSpeed / 2 * -IMath::sign(IMath::sinHex(Angle));

						else if (Angle >= 0xC0 && Angle <= 0xDF)
							GroundSpeed = YSpeed * -IMath::sign(IMath::sinHex(Angle));
						else if (Angle >= 0x20 && Angle <= 0x3F)
							GroundSpeed = YSpeed * -IMath::sign(IMath::sinHex(Angle));
					}

					Ground = true;
					ShieldUsable = true;
					YSpeed = 0;
					EZY -= (OrigH - H) / 2; H = OrigH;

					if (Action == ActionType::Peril) {
						Action = ActionType::Normal;
					}
					else if (Action == ActionType::Slide) {
						Action = ActionType::Normal;
					}
					else if (Action == ActionType::Glide) {
						Action = ActionType::GlideSlide;
					}
					else if (Action == ActionType::Hurt) {
						Invincibility = InvincibilityType::Temporary;
						InvincibilityTimer = 120;
						Action = ActionType::Normal;
						GroundSpeed = 0;
						XSpeed = 0;
						isHurt = false;
					}
					else if (Action == ActionType::Spindash) {
					}
					else {
						if (DropDashRev >= 71 && Action == ActionType::Jumping) {
							Sound::Play(Sound::SFX_DROPDASH);

							Explosion* dropdashdust;
							dropdashdust = new Explosion();
							dropdashdust->G = G;
							dropdashdust->App = App;
							dropdashdust->CurrentAnimation = 2;
							dropdashdust->FlipX = DisplayFlip < 0;
							dropdashdust->Active = true;
							dropdashdust->Sprite = Scene->ExplosionSprite;
							dropdashdust->X = EZX;
							dropdashdust->Y = EZY + H / 2;
							Scene->Explosions.push_back(dropdashdust);

							CameraLockTimer = 8;

							Action = ActionType::Rolling;

							int dashspeed = 0x800;
							int maxspeed = 0xC00;

							if (InputRight)
								DisplayFlip = 1;
							if (InputLeft)
								DisplayFlip = -1;

							if (SuperForm || HyperForm) {
								dashspeed = 0xC00;
								maxspeed = 0xD00;

								Scene->ShakeTimer = 20;
							}
							else {
								dashspeed = 0x800;
								maxspeed = 0xC00;
							}

							if (DisplayFlip < 0) {
								if (XSpeed <= 0) {
									GroundSpeed = IMath::max(-maxspeed, (GroundSpeed >> 2) - dashspeed);
									goto LABEL_25;
								}
								if (Angle != 0) {
									GroundSpeed = (GroundSpeed >> 1) - dashspeed;
									goto LABEL_25;
								}
								dashspeed = -dashspeed;
							}
							else {
								if (XSpeed >= 0) {
									GroundSpeed = IMath::min(maxspeed, dashspeed + (GroundSpeed >> 2));
									goto LABEL_25;
								}
								if (Angle != 0) {
									GroundSpeed = dashspeed + (GroundSpeed >> 1);
									goto LABEL_25;
								}
							}
							GroundSpeed = dashspeed;
						LABEL_25:
							DropDashRev = 0;
						}
						else if ((ObjectControlled & 1) == 0) {
							Action = ActionType::Normal;
							// EZY -= (OrigH - H) / 2; H = OrigH;
						}
					}

					DropDashRev = 0;
				}
			}

			// Check Sensor C
			SensorC = -1;
			int SensorC_Angle;
			for (int y = 0; y <= SensorLength && DoCollision; y++) {
				if (Scene->CollisionAt(
					EZX - SensorABCDWidth * ModeCos[AngleMode] - y * ModeSin[AngleMode],
					EZY - SensorABCDWidth * ModeSin[AngleMode] - y * ModeCos[AngleMode], &SensorC_Angle, (AngleMode + 2) & 0x3, this)) {
					SensorC = y;
					break;
				}
			}

			// Check Sensor D
			SensorD = -1;
			int SensorD_Angle;
			for (int y = 0; y <= SensorLength && DoCollision; y++) {
				if (Scene->CollisionAt(
					EZX + SensorABCDWidth * ModeCos[AngleMode] - y * ModeSin[AngleMode],
					EZY + SensorABCDWidth * ModeSin[AngleMode] - y * ModeCos[AngleMode], &SensorD_Angle, (AngleMode + 2) & 0x3, this)) {
					SensorD = y;
					break;
				}
			}

			ang = 40;
			value = 0xFF;
			if (SensorC == -1 && SensorD != -1) {
				value = SensorD;
				ang = SensorD_Angle;
			}
			else if (SensorC != -1 && SensorD == -1) {
				value = SensorC;
				ang = SensorC_Angle;
			}
			else if (SensorC != -1 && SensorD != -1) {
				if (SensorC < SensorD) {
					value = SensorC;
					ang = SensorC_Angle;
				}
				else {
					value = SensorD;
					ang = SensorD_Angle;
				}
			}

			if (value != 0xFF) {
				if (YSpeed < 0) {
					if (Action != ActionType::InStream && Action != ActionType::InStreamGrab) {
						if (ang >= 0xA0 && ang <= 0xBF) {
							Angle = ang;
							AngleMode = 1;
							GroundSpeed = YSpeed * -IMath::sign(IMath::sinHex(Angle));
							Ground = true;
							ShieldUsable = true;
							Action = ActionType::Normal;
							EZY += (OrigH - H) / 2; H = OrigH;
							DisplayAngle = Angle << 8;
						}
						else if (ang >= 0x40 && ang <= 0x5F) {
							Angle = ang;
							AngleMode = 3;
							GroundSpeed = YSpeed * -IMath::sign(IMath::sinHex(Angle));
							Ground = true;
							ShieldUsable = true;
							Action = ActionType::Normal;
							EZY += (OrigH - H) / 2; H = OrigH;
							DisplayAngle = Angle << 8;
						}
						else {
							YSpeed = 0;
						}

						FlyFlag = 0x8;
						SubY = (EZY - value + H / 2) << 16;
					}
					else {
						if (ang >= 0xA0 && ang <= 0xBF) {
							SubX -= 2 << 16;
						}
						else if (ang >= 0x40 && ang <= 0x5F) {
							SubX += 2 << 16;
						}
						else {
							SubY = (EZY - value + H / 2) << 16;
							YSpeed = 0;
						}
					}
				}
			}

			// if (Action == ActionType::InStream || Action == ActionType::InStreamGrab) {
			//     Angle = 0;
			// 	Ground = false;
			// }
		}

		SubX += (XSpeed << 8) / CheckStepsMax;
		SubY += (YSpeed << 8) / CheckStepsMax;

		HandlePathSwitchers();
		HandleSprings();
	}

	if (Action == ActionType::Victory) {
		Angle = 0;
		AngleMode = 0;
	}

	if (InputDown && Ground && Action != ActionType::Slide) {
		if (ManiaPhysics) {
			if (Action == ActionType::Normal) {
				if (GroundSpeed == 0 && IMath::abs((int8_t)Angle) < 0x10) {
					Action = ActionType::CrouchDown;
				}
				else if (IMath::abs(GroundSpeed) >= 0x90) {
					Action = ActionType::Rolling;
					Sound::Play(Sound::SFX_ROLL);
				}
			}
		}
		else {
			if (Action == ActionType::Normal) {
				if (IMath::abs(GroundSpeed) > 0x108) {
					Action = ActionType::Rolling;
					Sound::Play(Sound::SFX_ROLL);
				}
				else {
					Action = ActionType::CrouchDown;
				}
			}
			else {
				if (IMath::abs(GroundSpeed) > 0x88) {
					if (Action != ActionType::Rolling)
						Sound::Play(Sound::SFX_ROLL);
					Action = ActionType::Rolling;
				}
			}
		}
	}

	if (Ground) {
		JumpVariable = 0;
		EnemyCombo = 0;
	}

	if (HoldingPlayer) {
		HoldingPlayer->X = X;
		HoldingPlayer->Y = Y + 0x20;
		HoldingPlayer->YSpeed = 0;
		HoldingPlayer->DisplayFlip = DisplayFlip;
		HoldingPlayer->Action = ActionType::GrabFall;
		if (HoldingPlayer->Ground) {
			HoldingPlayer->ObjectControlled = 0x00;
			HoldingPlayer->Action = ActionType::Normal;
			HoldingPlayer->GroundSpeed = XSpeed;
			HoldingPlayer->GrabTimer = 60;
			HoldingPlayer = NULL;
		}
		else if (!HoldingPlayer->ObjectControlled) {
			HoldingPlayer->GrabTimer = 60;
			HoldingPlayer = NULL;
		}
		else if (Action != ActionType::Fly) {
			HoldingPlayer->ObjectControlled = 0x00;
			HoldingPlayer->Action = ActionType::Normal;
			HoldingPlayer->GroundSpeed = XSpeed;
			HoldingPlayer->GrabTimer = 60;
			HoldingPlayer = NULL;
		}
		else {
			HoldingPlayer->ChangeAnimation2((int)AnimationEnum::Hang, 0);
		}
		//HoldingPlayer->AnimationSpeedMult = 0;
	}

	if (Action == ActionType::Jumping && JumpVariable == 1 && App->Input->GetControllerInput(InputController, IInput::I_EXTRA2_PRESSED)) {
		if (!SuperForm && !HyperForm) {
			if (Rings >= 50 && !Scene->StopTimer) {
				if (SaveGame::GetEmeralds() == 0x3FFF) {
					DoSuperTransform();
				}
				else if ((SaveGame::GetEmeralds() & 0x7F) == 0x7F) { // AND if super emerald room hasnt been activated
					DoSuperTransform();
				}
			}
		}
	}

	// Mid-air actions, etc...
	if (InputJump) {
		if (Action == ActionType::Normal ||
			Action == ActionType::Rolling ||
			Action == ActionType::LookUp ||
			Action == ActionType::Skid ||
			Action == ActionType::Spinning ||
			Action == ActionType::Slide) {
			if (Ground || (ObjectControlled <= 0x7F && ObjectControlled > 0x00)) {
				if (ObjectControlled <= 0x7F && ObjectControlled > 0x00) {
					ObjectControlled = 0;
					GroundSpeed >>= 1;
					EZY -= 4;
				}

				Jump();
			}
		}
		else if (Action == ActionType::CrouchDown) {
			Action = ActionType::Spindash;
			SpindashRev = 0x200;
			Vibrate(VibrationType::SpindashRev);
			Sound::Play(Sound::SFX_SPINDASHREV);
		}
		else if (Action == ActionType::Spindash) {
			Vibrate(VibrationType::SpindashRev);
			SpindashRev += 0x200;
			if (SpindashRev > 0x800)
				SpindashRev = 0x800;
			ChangeAnimation2((int)AnimationEnum::Spindash + superflag);
			Sound::Play(Sound::SFX_SPINDASHREV);
		}
		else if (Action == ActionType::Jumping && JumpVariable == 1) {
			if (HyperForm) {
				if (ShieldUsable && Character == CharacterType::Sonic) {
					if (InputUp) {
						YSpeed = -0x800;
					}
					if (InputJumpHold && DropDashEnabled) {
						if (DropDashRev == 0) {
							DropDashRev = 1;
						}
					}
					else {
						XSpeed = 0x800 * DisplayFlip;
						YSpeed = 0;
						CameraLockTimer = 16;
					}
					ShieldUsable = false;
				}
			}
			else if (Character == CharacterType::Sonic) {
				if (ShieldUsable) {
					if ((SuperForm || HyperForm || Shield == ShieldType::None)) {
						if (DropDashEnabled && !InputUp) {
							if (DropDashRev == 0) {
								DropDashRev = 1;
							}
						}
						else if (!InputUp) {
							ShieldAnimation = 8;
							Shield = ShieldType::Instashield;
							Sound::Play(Sound::SFX_INSTASHIELD);
						}
						ShieldUsable = false;
					}
					else if (Shield == ShieldType::Fire) {
						XSpeed = 0x800 * DisplayFlip;
						YSpeed = 0;
						CameraLockTimer = 16;
						ShieldAnimation = 12;
						Sound::Play(Sound::SFX_SHIELD_FIRE_DASH);
						if (InputJumpHold && DropDashEnabled) {
							if (DropDashRev == 0) {
								DropDashRev = 1;
							}
						}
					}
					else if (Shield == ShieldType::Bubble) {
						XSpeed = 0;
						YSpeed = 0x800;
						ShieldAction = true;
						Sound::Play(Sound::SFX_SHIELD_BUBBLE_BOUNCE);
					}
					else if (Shield == ShieldType::Electric) {
						YSpeed = -0x580;
						Sound::Play(Sound::SFX_SHIELD_ELECTRIC_JUMP);
						Scene->AddMovingSprite(SpriteShields, EZX, EZY, 7, 0, false, false, -0x200, -0x200, 0x18, 22, 0);
						Scene->AddMovingSprite(SpriteShields, EZX, EZY, 7, 0, false, false, 0x200, -0x200, 0x18, 22, 0);
						Scene->AddMovingSprite(SpriteShields, EZX, EZY, 7, 0, false, false, -0x200, 0x200, 0x18, 22, 0);
						Scene->AddMovingSprite(SpriteShields, EZX, EZY, 7, 0, false, false, 0x200, 0x200, 0x18, 22, 0);
						if (InputJumpHold && DropDashEnabled) {
							if (DropDashRev == 0) {
								DropDashRev = 1;
							}
						}
					}
					else if (Shield == ShieldType::Basic) {
						// Do nothing special.
						if (DropDashEnabled) {
							if (DropDashRev == 0) {
								DropDashRev = 1;
							}
						}
					}

					ShieldUsable = false;
				}
			}
			else if (Character == CharacterType::Tails) {
				if (!InputDown) {
					Action = ActionType::Fly;
					FlyFlag = 0x8;
					FlyTimer = FlyTimerMax;
				}
			}
			else if (Character == CharacterType::Knuckles) {
				Action = ActionType::Glide;
				XSpeed = DisplayFlip * 0x400;
				if (YSpeed < 0)
					YSpeed = 0;
			}
			else if (Character == CharacterType::Mighty && JumpVariable == 1) {
				ChangeAnimation((int)AnimationEnum::MightyDrillDrive);
				XSpeed >>= 1;
				YSpeed = 0xC00;
				if (Underwater)
					YSpeed = 0x800;
				Action = ActionType::MightyStomp;
				Sound::Play(Sound::SFX_MIGHTY_DRILL);
			}
			else if (Character == CharacterType::Ray) {
				// sub_4C8DF0
				if (JumpVariable == 1) {
					Action = ActionType::RayGlide;

					int adjustedXSpeed = XSpeed - (XSpeed / 8);
					XSpeed = adjustedXSpeed;

					int maxx = 0x300;
					if (Underwater)
						maxx = 0x180;

					if (DisplayFlip < 0) {
						if (XSpeed > -maxx)
							XSpeed = -maxx;
					}
					else if (XSpeed < maxx) {
						XSpeed = maxx;
					}

					if ((DisplayFlip < 0 || !InputRight) && (DisplayFlip > 0 || !InputLeft)) {
						ChangeAnimation((int)AnimationEnum::RayFlyUp, 3);
						Sound::Play(Sound::SFX_RAY_SWOOP);

						Angle = 1; // Facing Up

						bool goingLeft = (XSpeed >> 1) < 0;
						XSpeed >>= 1;

						int leftSpeed = XSpeed;
						if (goingLeft)
							leftSpeed = -leftSpeed;

						if (XSpeed < 0) {
							XSpeed = -XSpeed;
						}
						int speedStore = -((leftSpeed >> 1) + (XSpeed >> 2) + (XSpeed >> 4)) >> (int)Underwater;
						if (speedStore > 0x400)
							speedStore = 0x400;

						GlideSpeedStore = speedStore;
					}
					else {
						ChangeAnimation((int)AnimationEnum::RayFlyDown, 3);
						Sound::Play(Sound::SFX_RAY_DIVE);
						Angle = 0; // Facing Down
						GlideSpeedStore = 0;
					}

					YSpeed >>= 1;
					GlideTurnCos = 0x40;
					MaxGlideSpeed = IMath::abs(XSpeed);
					RayBoostCount = 0x100;
				}
			}
		}
	}
	// Handle Spindash
	if (Action == ActionType::Spindash) {
		GroundSpeed = 0;
		if (!InputDown) {
			Action = ActionType::Rolling;
			GroundSpeed = DisplayFlip * (SpindashRev / 2 + 0x800);
			CameraLockTimer = 16;

			Sound::Play(Sound::SFX_SPINDASH);
		}
		SpindashRev -= SpindashRev / 0x20;
	}
	// Handle Air Drag
	if (Action == ActionType::Jumping && !InputJumpHold && YSpeed < rel && JumpVariable == 1)
		YSpeed = rel;
	if (Action == ActionType::Spring && YSpeed < 0) {
		if (InputJump) {
			Action = ActionType::Jumping;
		}
	}
	// Change Animation to Air Walk after springed
	if (Action == ActionType::Spring && YSpeed >= 0) {
		if (SpringFlip <= 1) {
			Action = ActionType::Normal;
			ChangeAnimation((int)AnimationEnum::AirWalk + superflag);
		}
	}
	// Produce Dust particles when necessary
	if (Action == ActionType::Skid || Action == ActionType::GlideSlide) {
		if (!Ground && Action == ActionType::Skid) {
			Action = ActionType::Normal;
		}
		else if (Scene->Frame % 5 == 0 && GroundSpeed != 0 && Ground) {
			Scene->AddExplosion(Scene->ExplosionSprite, 0, false, X, Y + H / 2 - 4, VisualLayer);
		}
	}
	// Handle Fan action
	if (Action == ActionType::Fan)
		Action = ActionType::Normal;
	// Handle Temporary invulnerablity
	if (isHurt) {
		if (Action != ActionType::Hurt) {
			Invincibility = InvincibilityType::Temporary;
			InvincibilityTimer = 120;
			if (Ground)
				GroundSpeed = 0;
		}
	}
	// Handle various timers
	if (CameraLockTimer > 0)
		CameraLockTimer--;

	if (InvincibilityTimer > 0) {
		InvincibilityTimer--;
		if (InvincibilityTimer == 0) {
			if (Invincibility == InvincibilityType::Full)
				App->Audio->RemoveMusic(Sound::SoundBank[0xFF]);
			Invincibility = InvincibilityType::None;
		}
	}

	if (SpeedSneakersTimer > 0) {
		SpeedSneakersTimer--;
		if (SpeedSneakersTimer == 0) {
			SpeedSneakersActive = false;
			App->Audio->RemoveMusic(Sound::SoundBank[0xFE]);
		}
	}

	if (WaitTimer > 0) {
		WaitTimer--;
		if (WaitTimer == 0) {
			WaitTimer = -1;
			if (Action == ActionType::Normal) {
				Action = ActionType::Bored1;
			}
		}
	}

	if (RingAlarm > 0)
		RingAlarm--;

	if ((SuperForm || HyperForm) && Rings > 0) {
		if (Scene->Frame % 60 == 0)
			Rings--;

		if (Rings == 0)
			Deform();
	}

	// Handle a few action sounds
	if ((WallLeft && InputLeft) || (WallRight && InputRight)) {
		//if ((Scene->Frame & 0xF) == 0)
		//Sound::Play(Sound::SFX_PUSHING);
	}
	if (WaterRunning && (Scene->Frame & 0xF) == 0) {
		Sound::Play(Sound::SFX_WATERRUN);
	}

	// Beeps
	if (Underwater && Shield != ShieldType::Bubble) {
		if (UnderwaterTimer > 0)
			UnderwaterTimer--;
		else
			Die(true);

		if (UnderwaterTimer == 1440 ||
			UnderwaterTimer == 1140 ||
			UnderwaterTimer == 840) {
			Sound::Play(Sound::SFX_UNDERWATER_BEEP);
		}
		if (UnderwaterTimer == 750 && !Sidekick) {
			App->Audio->PushMusic(Sound::SoundBank[0xFD], false, 0);
		}
		if (UnderwaterTimer == 720 ||
			UnderwaterTimer == 600 ||
			UnderwaterTimer == 480 ||
			UnderwaterTimer == 360 ||
			UnderwaterTimer == 240 ||
			UnderwaterTimer == 120) {
			int number = (UnderwaterTimer / 120) - 1;
			BubbleCountdown* countdown = new BubbleCountdown();
			countdown->G = G;
			countdown->App = App;
			countdown->Scene = Scene;
			countdown->Number = number;
			countdown->FlipX = false;
			countdown->FlipY = false;
			countdown->Active = true;
			countdown->VisualLayer = 1;
			countdown->Sprite = Scene->WaterSprite;
			countdown->X = EZX - Scene->CameraX + 20;
			countdown->Y = EZY - Scene->CameraY - 20;
			Scene->Explosions.push_back(countdown);
		}
	}
	else {
		UnderwaterTimer = 1800;
	}

	if (ShieldAnimation > 0) {
		ShieldAnimation--;
		if (Shield == ShieldType::Instashield) {
			if (ShieldAnimation == 0)
				Shield = ShieldType::None;
		}
	}

	if (GrabTimer > 0)
		GrabTimer--;

	InputUp = IUp;
	InputDown = IDown;
	InputJump = IJump;
	InputLeft = ILeft;
	InputRight = IRight;
	InputJumpHold = IJumpHold;

	if (Scene->StopTimer && (SuperForm || HyperForm)) {
		Deform();
	}
	if (AngleIslandFlag) {
		EZX = 0x2B60 - H / 2;
		AngleMode = 1;
		Angle = 0xC0;
	}
}

void IPlayer::LateUpdate() {
	AnimationSpeedMult = 0x100;

	// Apply animations based on Action states
	if (!Cutscene) {
		int superflag = 0;
		if ((SuperForm || HyperForm) && Character == CharacterType::Sonic)
			superflag = 54;

		if (Ground) {
			if (Action == ActionType::Rolling) {
				if (IMath::abs(GroundSpeed) < 0x500)
					AnimationSpeedMult = 0x100 / (5 - (IMath::abs(GroundSpeed) >> 8));

				ChangeAnimation((int)AnimationEnum::Jump + superflag);
			}
			else if (Action == ActionType::Victory) {
				ChangeAnimation((int)AnimationEnum::Victory + superflag);
			}
			else if (Action == ActionType::GlideSlide) {
				ChangeAnimation((int)AnimationEnum::GlideSlide, 0);
			}
			else if (Action == ActionType::GlideFallLand) {
				ChangeAnimation((int)AnimationEnum::GlideLand);
			}
			else if (Action == ActionType::CrouchDown) {
				ChangeAnimation((int)AnimationEnum::Crouch + superflag);
				if (CurrentFrame >= 0x400)
					CurrentFrame = 0x400;
			}
			else if (Action == ActionType::Spindash) {
				AnimationSpeedMult = 0x100;

				ChangeAnimation((int)AnimationEnum::Spindash + superflag);
			}
			else if (Action == ActionType::Skid) {
				ChangeAnimation((int)AnimationEnum::Skid + superflag);
			}
			else if (Action == ActionType::Bored1) {
				ChangeAnimation((int)AnimationEnum::Bored1 + superflag);
			}
			else if (Action == ActionType::LookUp) {
				ChangeAnimation((int)AnimationEnum::LookUp + superflag);
				if (CurrentFrame >= 0x400 && Character == CharacterType::Sonic)
					CurrentFrame = 0x400;
				else if (CurrentFrame >= 0x500)
					CurrentFrame = 0x500;
			}
			else if ((WallLeft && InputLeft) || (WallRight && InputRight)) {
				ChangeAnimation((int)AnimationEnum::Push + superflag);
			}
			else if (Action != ActionType::CancelableAnim) {
				if (!Thremixed) {
					if (IMath::abs(GroundSpeed) == 0x0 && (Angle <= 0x10 || Angle >= 0xF0)) {
						bool below = !Scene->CollisionAt(EZX, EZY + H / 2 + 2, NULL, 0, this);
						bool yikes = !Scene->CollisionAt(EZX - DisplayFlip * 4, EZY + H / 2 + 2, NULL, 0, this);

						below &= Angle == 0;
						yikes &= Angle == 0;

						AnimationSpeedMult = 0x100;
						if (below && !yikes) {
							ChangeAnimation((int)AnimationEnum::Balance1 + superflag);
							WaitTimer = 180;
						}
						else if (below) {
							ChangeAnimation((int)AnimationEnum::Balance2 + superflag);
							WaitTimer = 180;
						}
						else
							ChangeAnimation((int)AnimationEnum::Idle + superflag);
					}
					else if (IMath::abs(GroundSpeed) < 0x600) {
						AnimationSpeedMult = 0x100 / (8 - (IMath::abs(GroundSpeed) >> 8));

						ChangeAnimation((int)AnimationEnum::Walk + superflag);
					}
					else {
						if (IMath::abs(GroundSpeed) < 0x800)
							AnimationSpeedMult = 0x100 / (8 - (IMath::abs(GroundSpeed) >> 8));
						else
							AnimationSpeedMult = 0x100;

						ChangeAnimation((int)AnimationEnum::Run + superflag, 0x100);
					}
				}
				else {
					if (IMath::abs(GroundSpeed) == 0x0 && (Angle <= 0x10 || Angle >= 0xF0)) {
						bool below = !Scene->CollisionAt(EZX, EZY + H / 2 + 2, NULL, 0, this);
						bool yikes = !Scene->CollisionAt(EZX - DisplayFlip * 4, EZY + H / 2 + 2, NULL, 0, this);

						below &= Angle == 0;
						yikes &= Angle == 0;

						AnimationSpeedMult = 0x100;
						if (below && !yikes) {
							ChangeAnimation((int)AnimationEnum::Balance1 + superflag);
							WaitTimer = 180;
						}
						else if (below) {
							ChangeAnimation((int)AnimationEnum::Balance2 + superflag);
							WaitTimer = 180;
						}
						else {
							ChangeAnimation((int)AnimationEnum::Idle + superflag);
						}
					}
					else if (IMath::abs(GroundSpeed) < 0x400) {
						AnimationSpeedMult = 0x100 / (8 - (IMath::abs(GroundSpeed) >> 8));

						// AnimationSpeedMult = 0x200 * IMath::abs(GroundSpeed) / 0x400;
						// if (AnimationSpeedMult < 0x100)
						// AnimationSpeedMult = 0x100;

						ChangeAnimation((int)AnimationEnum::Walk + superflag);
					}
					else if (IMath::abs(GroundSpeed) < 0x600) {
						// AnimationSpeedMult = 0x200 * IMath::abs(GroundSpeed) / 0x600;

						AnimationSpeedMult = 0x100 / (8 - (IMath::abs(GroundSpeed) >> 8));

						ChangeAnimation((int)AnimationEnum::Jog + superflag);
					}
					else if (IMath::abs(GroundSpeed) < 0xC00) {
						// AnimationSpeedMult = 0x200 * IMath::abs(GroundSpeed) / 0xC00;

						if (IMath::abs(GroundSpeed) < 0x800)
							AnimationSpeedMult = 0x100 / (8 - (IMath::abs(GroundSpeed) >> 8));
						else
							AnimationSpeedMult = 0x100;

						ChangeAnimation((int)AnimationEnum::Run + superflag, 0x100);
					}
					else {
						AnimationSpeedMult = 0x100;

						ChangeAnimation((int)AnimationEnum::Dash + superflag);
					}
				}
			}
		}
		else {
			if (Action == ActionType::Fan) {
				AnimationSpeedMult = 0x200;
				ChangeAnimation((int)AnimationEnum::SpringCS + superflag);
			}
			else if (Action == ActionType::Jumping && DropDashRev > 70)
				ChangeAnimation((int)AnimationEnum::Dropdash + superflag);
			else if (Action == ActionType::Jumping) {
				if (IMath::abs(GroundSpeed) < 0x500)
					AnimationSpeedMult = 0x100 / (5 - (IMath::abs(GroundSpeed) >> 8));

				ChangeAnimation((int)AnimationEnum::Jump + superflag);
			}
			else if (Action == ActionType::Spring) {
				if (SpringFlip)
					ChangeAnimation((int)AnimationEnum::SpringCS + superflag);
				else
					ChangeAnimation((int)AnimationEnum::SpringDiagonal + superflag);
			}
			else if (Action == ActionType::Transform) {
				ChangeAnimation((int)AnimationEnum::Transform);
			}
			//ChangeAnimation((int)AnimationEnum::AirWalk + superflag);
		}

		// Overriding animations
		if (Action == ActionType::Peril) {
			if ((int)AnimationEnum::Flume) {
				ChangeAnimation((int)AnimationEnum::Flume + superflag);
			}
			else {
				ChangeAnimation((int)AnimationEnum::Hurt + superflag, 0x300);
			}
		}
		else if (Action == ActionType::Slide) {
			if ((int)AnimationEnum::Flume) {
				ChangeAnimation((int)AnimationEnum::Flume + superflag);
			}
			else {
				ChangeAnimation((int)AnimationEnum::Hurt + superflag, 0x300);
			}
		}
		else if (Action == ActionType::Hurt) {
			ChangeAnimation((int)AnimationEnum::Hurt + superflag);
		}
		else if (Action == ActionType::InStream) {
			ChangeAnimation((int)AnimationEnum::Fan + superflag);
			DisplayFlip = 1;
		}
		else if (Action == ActionType::InStreamGrab) {
			ChangeAnimation((int)AnimationEnum::Cling + superflag);
			DisplayFlip = 1;
		}
		else if (Action == ActionType::Glide) {
			ChangeAnimation((int)AnimationEnum::Glide, 0x500);
			//if (CurrentFrame >= 0x400)
			//CurrentFrame = 0x400;
		}
		else if (Action == ActionType::GlideFall) {
			ChangeAnimation((int)AnimationEnum::GlideDrop);
		}
		else if (Action == ActionType::Climb) {
			if (YSpeed == 0) {
				ChangeAnimation((int)AnimationEnum::ClimbIdle);
			}
			else if (YSpeed < 0) {
				ChangeAnimation((int)AnimationEnum::ClimbUp);
			}
			else {
				ChangeAnimation((int)AnimationEnum::ClimbDown);
			}
		}
		else if (Action == ActionType::ClimbRise) {
			ChangeAnimation((int)AnimationEnum::LedgePullup);
		}
		else if (Action == ActionType::Dead) {
			if (Underwater) {
				ChangeAnimation((int)AnimationEnum::Drown + superflag);
			}
			else {
				ChangeAnimation((int)AnimationEnum::Die + superflag);
			}
		}
		else if (Action == ActionType::Grab) {
			ChangeAnimation((int)AnimationEnum::Hang + superflag);
			if (GrabSwingValue != -1) {
				CurrentFrame = (Sprites[0]->Animations[CurrentAnimation].FrameCount - 1 - 1) * GrabSwingValue;
			}
		}
		else if (Action == ActionType::GrabFall) {
			ChangeAnimation((int)AnimationEnum::Hang + superflag);
			CurrentFrame = 0;
		}
		else if (Action == ActionType::Corkscrew) {
			ChangeAnimation((int)AnimationEnum::Bubble + superflag);
			if (GrabSwingValue != -1) {
				CurrentFrame = (Sprites[0]->Animations[CurrentAnimation].FrameCount - 1 - 1) * GrabSwingValue;
			}
		}
		else if (Action == ActionType::Conveyor) {
			if (IMath::abs(XSpeed) == 0x200) {
				ChangeAnimation((int)AnimationEnum::ShimmyIdle + superflag);
			}
			else if (IMath::abs(XSpeed) > 0x200) {
				ChangeAnimation((int)AnimationEnum::ShimmyMove + superflag);
				DisplayFlip = 1 * IMath::sign(XSpeed);
			}
			else {
				ChangeAnimation((int)AnimationEnum::ShimmyMove + superflag);
				DisplayFlip = -1 * IMath::sign(XSpeed);
			}
		}
		else if (Action == ActionType::Spinning) {
			ChangeAnimation2((int)AnimationEnum::Twister + superflag, (Scene->Frame >> 2) % 24);
		}
		else if (Action == ActionType::Fly) {
			if (Underwater) {
				if (HoldingPlayer) {
					ChangeAnimation((int)AnimationEnum::SwimLift);
				}
				else {
					if (FlyTimer > 0) {
						ChangeAnimation((int)AnimationEnum::Swim);
					}
					else {
						ChangeAnimation((int)AnimationEnum::SwimTired);
					}
				}
			}
			else {
				if (HoldingPlayer) {
					if (FlyTimer > 0 && YSpeed > 0) {
						ChangeAnimation((int)AnimationEnum::Fly);
					}
					else if (FlyTimer > 0) {
						ChangeAnimation((int)AnimationEnum::FlyLift);
					}
					else {
						ChangeAnimation((int)AnimationEnum::FlyLiftTired);
					}
				}
				else {
					if (FlyTimer > 0) {
						ChangeAnimation((int)AnimationEnum::Fly);
					}
					else {
						ChangeAnimation((int)AnimationEnum::FlyTired);
					}
				}
			}
		}
		else if (Action == ActionType::Respawn) {
			if (Character == CharacterType::Tails) {
				ChangeAnimation((int)AnimationEnum::Fly);
			}
			else if (Character == CharacterType::Knuckles) {
				ChangeAnimation((int)AnimationEnum::Fly);
			}
			else if (Character == CharacterType::Ray) {
				ChangeAnimation((int)AnimationEnum::RayFlyUp);
			}
			else {
				ChangeAnimation((int)AnimationEnum::Fly);
			}
		}
		else if (Action == ActionType::MightyStomp) {
			ChangeAnimation((int)AnimationEnum::MightyDrillDrive);
		}
		else if (Action == ActionType::MightyUncurl) {
			ChangeAnimation(48); //(int)AnimationEnum::Mighty);
		}

		if (!Ground && (CurrentAnimation == 5 + superflag || CurrentAnimation == 6 + superflag || CurrentAnimation == 7 + superflag)) {
			AnimationSpeedMult = 0x10000 / (0x800 - IMath::min(0x400, IMath::abs(GroundSpeed)));
		}
	}

	ISprite::Animation animation = Sprites[0]->Animations[CurrentAnimation];

	/*
	if (animation.AnimationSpeed > 2)
	CurrentFrame += (animation.AnimationSpeed * AnimationSpeedMult) >> 8;
	else if (animation.Frames[CurrentFrame / 0x100].Duration != 0)
	CurrentFrame += ((0x100 * animation.AnimationSpeed * AnimationSpeedMult) >> 8) / animation.Frames[CurrentFrame / 0x100].Duration;
	else if (Action == ActionType::Transform)
	CurrentFrame += 0x100;
	*/

	int yiss = CurrentFrame / 0x100;
	if (yiss < 0)
		yiss = 0;
	if (yiss > animation.FrameCount - 1)
		yiss = animation.FrameCount - 1;
	if (animation.AnimationSpeed > 0 && animation.Frames[yiss].Duration != 0) {
		CurrentFrame += ((0x100 * animation.AnimationSpeed * AnimationSpeedMult) >> 8) / animation.Frames[yiss].Duration;
	}
	else if (Action == ActionType::Transform) {
		CurrentFrame += 0x100;
	}

	if (Action == ActionType::ClimbRise) {
		int offsetsX[7] = { 0x00, 0x00,  0x05,  0x0A,  0x0F,  0x14,  0x14 };
		int offsetsY[7] = { 0x01, 0x01, -0x07, -0x0F, -0x11, -0x1F, -0x1D };

		int reindex = (CurrentFrame) >> 8;
		if (reindex < 7) {
			X = 0;
			Y = 0;
			EZX = StoredX + offsetsX[reindex] * DisplayFlip;
			EZY = StoredY + offsetsY[reindex];
		}
		if (reindex == 8)
			Action = ActionType::Normal;
	}
	else if (Action == ActionType::GlideSlide) {
		if (GroundSpeed != 0) {
			if ((CurrentFrame >> 8) >= 3)
				CurrentFrame = 0x200;
		}
		else {
			if ((CurrentFrame >> 8) >= animation.FrameCount - 1) {
				CurrentFrame = (animation.FrameCount - 1) << 8;
				Action = ActionType::Normal;
			}
		}
	}

	if (CurrentFrame >= animation.FrameCount * 0x100) {
		// Actions that cancel after animation is finished

		AnimationDone = 1;

		bool loop = true;

		if (Action == ActionType::CancelableAnim)
			Action = ActionType::Normal;
		else if (Action == ActionType::Bored1) {
			Action = ActionType::Normal;

			WaitTimer = 180;
		}
		else if (Action == ActionType::GlideFallLand) {
			loop = false;
			Action = ActionType::Normal;
			ChangeAnimation((int)AnimationEnum::Idle);
		}
		else if (Action == ActionType::ClimbRise) {
			loop = false;
			Action = ActionType::Normal;
			CurrentFrame = animation.FrameCount * 0x100 - 0x100;
		}

		if (Action == ActionType::Transform) {
			if (HyperEnabled) {
				HyperForm = true;
			}
			else {
				SuperForm = true;
			}
			Action = ActionType::Normal;
			SuperFormAnim = SuperFormAnimType::Super;
			XSpeed = 0;
			YSpeed = 0;
			ChangeAnimation((int)AnimationEnum::Jump);

			loop = false;
			CurrentFrame = 0;
		}

		if (loop) {
			if (false)
				CurrentFrame = animation.FrameCount * 0x100 - 0x100;
			else
				CurrentFrame = animation.FrameToLoop * 0x100;
		}
	}

	if (CurrentFrame < 0)
		CurrentFrame = 0;

	if (Shield != ShieldType::None) {
		ISprite::Animation ani = SpriteShields2->Animations[0];

		if (Shield == ShieldType::Fire)
			ani = SpriteShields->Animations[2];
		else if (Shield == ShieldType::Electric)
			ani = SpriteShields->Animations[3];
		else if (Shield == ShieldType::Bubble)
			ani = SpriteShields->Animations[1];
		else if (Shield == ShieldType::Basic)
			ani = SpriteShields->Animations[0];

		if (ShieldFrame / 0x100 >= ani.FrameCount - 1) {
			ShieldFrame = ani.FrameToLoop * 0x100;
		}

		if (ani.AnimationSpeed > 2)
			ShieldFrame += ani.AnimationSpeed;
		else if (ani.Frames[ShieldFrame / 0x100].Duration != 0)
			ShieldFrame += 0x100 / ani.Frames[ShieldFrame / 0x100].Duration;
	}

	if (Action == ActionType::Spindash) {
		ISprite::Animation ani = SpriteDashDust->Animations[1];

		if (DashFrame / 0x100 >= ani.FrameCount - 1) {
			DashFrame = ani.FrameToLoop * 0x100;
		}

		if (ani.AnimationSpeed > 2)
			DashFrame += ani.AnimationSpeed;
		else if (ani.Frames[DashFrame / 0x100].Duration != 0)
			DashFrame += 0x100 / ani.Frames[DashFrame / 0x100].Duration;
	}

	DisplayX = EZX;
	DisplayY = EZY;

	int palWhere, palCount = 6;
	Uint32 *palSuper, *palHyper = NULL, *palNormal, *palSuperHCZ, *palHyperHCZ = NULL, *palNormalHCZ, *palSuperPulse, *palSuperPulseHCZ, *palHyperPulse = NULL, *palHyperPulseHCZ = NULL;

	if (Character == CharacterType::Sonic) {
		palWhere = 0x40;
		palSuper = SonicPaletteSuper;
		palNormal = SonicPaletteNormal;
		palSuperHCZ = SonicPaletteSuperHCZ;
		if (ExtendedHyperPallete) {
			palHyper = SonicPaletteS3HyperExtended;
		}
		else {
			palHyper = SonicPaletteS3Hyper;
		}
		palNormalHCZ = SonicPaletteNormalHCZ;
		palSuperPulse = SonicPaletteSuperPulse;
		palSuperPulseHCZ = SonicPaletteSuperPulseHCZ;
		palHyperPulse = SonicPaletteS3HyperPulse;
		palHyperPulseHCZ = SonicPaletteS3HyperPulse;
		if (!Thremixed) {
			palWhere = 0x2;
			palCount = 3;
			palSuper = SonicPaletteS3Super;
			if (ExtendedHyperPallete) {
				palHyper = SonicPaletteS3HyperExtended;
			}
			else {
				palHyper = SonicPaletteS3Hyper;
			}
			palNormal = SonicPaletteS3Normal;
			palSuperHCZ = SonicPaletteS3SuperHCZ;
			palNormalHCZ = SonicPaletteS3NormalHCZ;
			palSuperPulse = SonicPaletteS3SuperPulse;
			palSuperPulseHCZ = SonicPaletteS3SuperPulseHCZ;
			palHyperPulse = SonicPaletteS3HyperPulse;
			palHyperPulseHCZ = SonicPaletteS3HyperPulse;
		}
	}
	else if (Character == CharacterType::Tails) {
		palWhere = 0x46;
		palSuper = TailsPaletteSuper;
		palNormal = TailsPaletteNormal;
		palSuperHCZ = TailsPaletteSuperHCZ;
		palNormalHCZ = TailsPaletteNormalHCZ;
		palSuperPulse = TailsPaletteSuperPulse;
		palSuperPulseHCZ = TailsPaletteSuperPulseHCZ;
	}
	else if (Character == CharacterType::Knuckles) {
		palWhere = 0x50;
		palSuper = KnuxPaletteSuper;
		palNormal = KnuxPaletteNormal;
		palSuperHCZ = KnuxPaletteSuperHCZ;
		palNormalHCZ = KnuxPaletteNormalHCZ;
		palSuperPulse = KnuxPaletteSuperPulse;
		palSuperPulseHCZ = KnuxPaletteSuperPulseHCZ;
	}
	/*else if (Character == CharacterType::Mighty) {
		palWhere = 0x60;
		palSuper = SonicPaletteSuper;
		palNormal = SonicPaletteNormal;
		palNormalHCZ = SonicPaletteNormalHCZ;
	}
	else if (Character == CharacterType::Ray) {
		palWhere = 0x70;
		palSuper = SonicPaletteSuper;
		palNormal = SonicPaletteNormal;
		palNormalHCZ = SonicPaletteNormalHCZ;
	}*/
	else {
		// Default to Sonic
		palWhere = 0x40;
		palSuper = SonicPaletteSuper;
		palNormal = SonicPaletteNormal;
		palSuperHCZ = SonicPaletteSuperHCZ;
		if (ExtendedHyperPallete) {
			palHyper = SonicPaletteS3HyperExtended;
		}
		else {
			palHyper = SonicPaletteS3Hyper;
		}
		palNormalHCZ = SonicPaletteNormalHCZ;
		palSuperPulse = SonicPaletteSuperPulse;
		palSuperPulseHCZ = SonicPaletteSuperPulseHCZ;
		palHyperPulse = SonicPaletteS3HyperPulse;
		palHyperPulseHCZ = SonicPaletteS3HyperPulse;
		if (!Thremixed) {
			palWhere = 0x2;
			palCount = 3;
			palSuper = SonicPaletteS3Super;
			if (ExtendedHyperPallete) {
				palHyper = SonicPaletteS3HyperExtended;
			}
			else {
				palHyper = SonicPaletteS3Hyper;
			}
			palNormal = SonicPaletteS3Normal;
			palSuperHCZ = SonicPaletteS3SuperHCZ;
			palNormalHCZ = SonicPaletteS3NormalHCZ;
			palSuperPulse = SonicPaletteS3SuperPulse;
			palSuperPulseHCZ = SonicPaletteS3SuperPulseHCZ;
			palHyperPulse = SonicPaletteS3HyperPulse;
			palHyperPulseHCZ = SonicPaletteS3HyperPulse;
		}
	}

	/*static bool looped = false;

	if (!looped) {
		uint16_t EncodedColors[] = { 0xEEC, 0xECA, 0xEA8, 0xCEC, 0xAEA, 0x2E0,
									 0xAEC, 0x4EC, 0x0CC, 0xCEE, 0x8EE, 0x4CE, 0xCCE,
									 0xAAE, 0xECE, 0xCAC, 0xEEE };

		for (int p = 0; p < 17; p++) {
			uint16_t color = G->GetRetroColor(EncodedColors[p]);
		}
	}
	looped = true;*/
	int hyperFullPalCount;
	if (ExtendedHyperPallete) {
		hyperFullPalCount = 31;
	}
	else {
		hyperFullPalCount = 17;
	}
	const unsigned int HyperLoopMaxIndex = 320;

	if (SuperFormAnim == SuperFormAnimType::Super) {
		double superblend = Cos[(Scene->Frame << 1) & 0xFF] / 2.0 + 0.5;
		if (HyperEnabled && OCMode && palHyper != NULL) {
			palCount = 17;
		}
		for (int i = 0; i < 4; i++) {
			if (!Sprites[i]) continue;

			for (int p = 0; p < palCount; p++) {
				if (HyperEnabled && palHyper != NULL) {
					if (!palHyperPulse || !palHyperPulseHCZ) {
						palHyperPulse = palSuperPulse;
						palHyperPulseHCZ = palSuperPulseHCZ;
					}
					if (OCMode) {
						Sprites[i]->SetPalette(palWhere + p, G->ColorBlend(palHyper[LastHyperIndex], palSuperPulse[p], superblend));
						Sprites[i]->SetPaletteAlt(palWhere + p, G->ColorBlend(palHyper[LastHyperIndex], palSuperPulseHCZ[p], superblend));
					}
					else {
						HyperLoopIndex++;
						if (HyperLoopIndex >= HyperLoopMaxIndex) {
							LastHyperIndex = (LastHyperIndex + 1) % hyperFullPalCount;
							HyperLoopIndex = 0;
						}
						uint32_t blendColor = G->ColorBlend(palHyper[LastHyperIndex], palHyperPulse[p], superblend);
						uint32_t blendColorHCZ = G->ColorBlend(palHyper[LastHyperIndex], palHyperPulseHCZ[p], superblend);
						Sprites[i]->SetPalette(palWhere + p, blendColor);
						Sprites[i]->SetPaletteAlt(palWhere + p, blendColorHCZ);
					}
				}
				else {
					Sprites[i]->SetPalette(palWhere + p, G->ColorBlend(palSuper[p], palSuperPulse[p], superblend));
					Sprites[i]->SetPaletteAlt(palWhere + p, G->ColorBlend(palSuperHCZ[p], palSuperPulseHCZ[p], superblend));
				}

				/*int ABGR = G->ColorBlend(palHyper[LastHyperIndex], palHyper[(LastHyperIndex - 1) % hyperFullPalCount], 100.0);
				uint8_t RGB[4] = { };
				G->ABGRToRGB(ABGR, RGB);

				App->Print(0, "Blended Color is: %02X, %02X, %02X, %02X", RGB[0], RGB[1], RGB[2], RGB[3]);
				//App->Print(0, "Blended Color is: %02X, %d, %d, %d", RGB[0], RGB[1], RGB[2], RGB[3]);

				ABGR = palHyper[LastHyperIndex];
				RGB[0] = 0x00;
				RGB[1] = 0x00;
				RGB[2] = 0x00;
				RGB[3] = 0x00;
				G->ABGRToRGB(ABGR, RGB);

				App->Print(0, "ABGR is: %02X, %02X, %02X, %02X", RGB[0], RGB[1], RGB[2], RGB[3]);
				//App->Print(0, "ABGR is: %02X, %d, %d, %d", RGB[0], RGB[1], RGB[2], RGB[3]);*/
			}
			Sprites[i]->UpdatePalette();
		}
	}
	else if (SuperFormAnim == SuperFormAnimType::Transforming) {
		if (SuperFormTimer < 40)
			SuperFormTimer++;

		double superblend = SuperFormTimer / 40.0;
		for (int i = 0; i < 4; i++) {
			if (!Sprites[i]) continue;

			for (int p = 0; p < palCount; p++) {
				for (int p = 0; p < palCount; p++) {
					if (HyperEnabled && palHyper != NULL) {
						if (!palHyperPulse || !palHyperPulseHCZ) {
							palHyperPulse = palSuperPulse;
							palHyperPulseHCZ = palSuperPulseHCZ;
						}
						if (OCMode) {
							Sprites[i]->SetPalette(palWhere + p, G->ColorBlend(palHyper[p], palSuperPulse[p], superblend));
							Sprites[i]->SetPaletteAlt(palWhere + p, G->ColorBlend(palHyper[p], palSuperPulseHCZ[p], superblend));
						}
						else {
							HyperLoopIndex++;
							if (HyperLoopIndex >= HyperLoopMaxIndex) {
								LastHyperIndex = (LastHyperIndex + 1) % hyperFullPalCount;
								HyperLoopIndex = 0;
							}
							uint32_t blendColor = G->ColorBlend(palHyper[LastHyperIndex], palHyperPulse[p], superblend);
							uint32_t blendColorHCZ = G->ColorBlend(palHyper[LastHyperIndex], palHyperPulseHCZ[p], superblend);
							Sprites[i]->SetPalette(palWhere + p, blendColor);
							Sprites[i]->SetPaletteAlt(palWhere + p, blendColorHCZ);
						}
					}
					else {
						Sprites[i]->SetPalette(palWhere + p, G->ColorBlend(palNormal[p], palSuper[p], superblend));
						Sprites[i]->SetPaletteAlt(palWhere + p, G->ColorBlend(palNormalHCZ[p], palSuperHCZ[p], superblend));
					}
				}
				Sprites[i]->UpdatePalette();
			}
		}
	}
	else if (SuperFormAnim == SuperFormAnimType::Deforming) {
		if (SuperFormTimer < 20)
			SuperFormTimer++;

		double superblend = SuperFormTimer / 20.0;
		if (HyperEnabled && OCMode && palHyper != NULL) {
			palCount = 17;
		}
		for (int i = 0; i < 4; i++) {
			if (!Sprites[i]) continue;

			for (int p = 0; p < palCount; p++) {
				if (HyperEnabled && palHyper != NULL) {
					if (!palHyperPulse || !palHyperPulseHCZ) {
						palHyperPulse = palSuperPulse;
						palHyperPulseHCZ = palSuperPulseHCZ;
					}
					if (OCMode) {
						Sprites[i]->SetPalette(palWhere + p, G->ColorBlend(palHyper[p], palNormal[p], superblend));
						Sprites[i]->SetPaletteAlt(palWhere + p, G->ColorBlend(palHyper[p], palNormalHCZ[p], superblend));
					} else {
						HyperLoopIndex++;
						if (HyperLoopIndex >= HyperLoopMaxIndex) {
							LastHyperIndex = (LastHyperIndex + 1) % hyperFullPalCount;
							HyperLoopIndex = 0;
						}
						uint32_t blendColor = G->ColorBlend(palHyper[LastHyperIndex], palNormal[p], superblend);
						uint32_t blendColorHCZ = G->ColorBlend(palHyper[LastHyperIndex], palNormalHCZ[p], superblend);
						Sprites[i]->SetPalette(palWhere + p, blendColor);
						Sprites[i]->SetPaletteAlt(palWhere + p, blendColorHCZ);
					}
				} else {
					Sprites[i]->SetPalette(palWhere + p, G->ColorBlend(palSuper[p], palNormal[p], superblend));
					Sprites[i]->SetPaletteAlt(palWhere + p, G->ColorBlend(palSuperHCZ[p], palNormalHCZ[p], superblend));
				}
			}
			Sprites[i]->UpdatePalette();
		}
	} else {
		for (int i = 0; i < 4; i++) {
			if (!Sprites[i]) break;

			for (int p = 0; p < palCount; p++) {
				Sprites[i]->SetPalette(palWhere + p, palNormal[p]);
				Sprites[i]->SetPaletteAlt(palWhere + p, palNormalHCZ[p]);
			}
			Sprites[i]->UpdatePalette();
		}
	}

	// Ease rotation
	int8_t shortestrot;
	int8_t FinalAngle = 0;
	if (IMath::abs((int8_t)Angle) >= 0x1C) {
		FinalAngle = (int8_t)Angle;
	}
	if (FinalAngle > 0x0) {
		FinalAngle = (FinalAngle - 0x10) & 0xE0;
	} else {
		FinalAngle = (FinalAngle + 0x10) & 0xE0;
    }
    
	shortestrot = (FinalAngle - ((uint16_t)DisplayAngle >> 8)) & 0xFF;
	if (DisplayAngle == 0 && shortestrot < 0) {
		DisplayAngle = -1;
		shortestrot = -1;
	}
	if (shortestrot < 0) {
		if (Ground) {
			DisplayAngle -= 0x600;
		} else {
			DisplayAngle -= 0x400;
        }

		DisplayAngle &= 0xFFFF;

		if (DisplayAngle < FinalAngle * 0x100) {
			DisplayAngle = FinalAngle * 0x100;
        }
	} else if (shortestrot > 0) {
		if (Ground) {
			DisplayAngle += 0x600;
		} else {
			DisplayAngle += 0x400;
        }

		DisplayAngle &= 0xFFFF;

		if ((DisplayAngle >> 8) > FinalAngle) {
			DisplayAngle = FinalAngle << 8;
        }
	}

	// For animations that don't rotate, set DisplayAngle to 0
	bool noRotate =
		Action != ActionType::Normal &&
		Action != ActionType::Grab;
	if (noRotate)
		DisplayAngle = 0;

	CameraX = 0;
	if (Action == ActionType::CrouchDown) {
		if (CameraLookTimer >= 60) {
			CameraY = IMath::min(CameraY + 2, 88);
		} else if (CameraY < 0) {
            CameraY = IMath::min(CameraY + 2, 0);
        } else if (CameraY > 0) {
            CameraY = IMath::max(CameraY - 2, 0);
		}
	} else if (Action == ActionType::LookUp) {
		if (CameraLookTimer >= 60) {
			CameraY = IMath::max(CameraY - 2, -104);
        } else if (CameraY < 0) {
            CameraY = IMath::min(CameraY + 2, 0);
        } else if (CameraY > 0) {
            CameraY = IMath::max(CameraY - 2, 0);
		}
	} else if (Action == ActionType::Rolling) {
		CameraX = (IMath::sinHex(Angle) * (H / 2 - 16)) >> 16;
		CameraY = (IMath::cosHex(Angle) * (H / 2 - 16)) >> 16;
	} else if (CameraLookTimer >= 60) {
        if (CameraY < 0) {
            CameraY = IMath::min(CameraY + 2, 0);
        } else if (CameraY > 0) {
            CameraY = IMath::max(CameraY - 2, 0);
        } else {
            CameraLookTimer = 0;
        }
    } else {
        CameraY = 0;
    }

	if (CameraLockTimer == 0) {
		if (Action == ActionType::CrouchDown) {
			CameraLookTimer += 1;
		} else if (Action == ActionType::LookUp) {
			CameraLookTimer += 1;
		}
	}

	PlayerStatus status;
	status.X = EZX;
	status.Y = EZY;
	status.InputUp = InputUp;
	status.InputDown = InputDown;
	status.InputLeft = InputLeft;
	status.InputLeftPress = InputLeftPress;
	status.InputRight = InputRight;
	status.InputRightPress = InputRightPress;
	status.InputJump = InputJump;
	status.InputJumpHold = InputJumpHold;
	status.Action = Action;
	status.XSpeed = XSpeed;
	status.YSpeed = YSpeed;
	PlayerStatusTable[PlayerStatusTableIndex] = status;
	PlayerStatusTableIndex = (PlayerStatusTableIndex + 1) & 0x1F;
}

void IPlayer::Render(int CamX, int CamY) {
	if (Hidden) return;

	// Invincibility stars:
	// 2 per sonic status position
	// 3 status positions + current pos to revolve around
	ISprite::Animation animation2 = Sprites[0]->Animations[CurrentAnimation];
	ISprite::AnimFrame currentFrame2 = animation2.Frames[CurrentFrame / 0x100];
	int myOffX = 0;
	int myOffY = 0;
	if (Action == ActionType::Conveyor)
		myOffY = currentFrame2.H / 2 + currentFrame2.OffY;
	if (CurrentAnimation == 38 || CurrentAnimation == 39)
		myOffY = 20;

	if (Action == ActionType::Rolling) {
		myOffX += (IMath::sinHex(Angle) * (H / 2 - 16)) >> 16;
		myOffY += (IMath::cosHex(Angle) * (H / 2 - 16)) >> 16;
	}

	// Draw water running waves
	if (WaterRunning) {
		G->SetDrawFunc(1);
		// G->DrawSprite(Scene->SpriteMapIDs[0x33], 17, (Scene->Frame >> 1) % Scene->SpriteMapIDs[0x33]->Animations[17].FrameCount, EZX - CamX, EZY + H / 2 - CamY, 0, XSpeed > 0 ? IE_NOFLIP : IE_FLIPX);
		G->SetDrawFunc(0);
	}

	// Draw shields (Behind player)
	if (!SuperForm && !HyperForm && Invincibility != InvincibilityType::Full) {
		if (Shield == ShieldType::Fire && ((ShieldFrame >> 8) & 1)) {
			if (ShieldAnimation == 0)
				G->DrawSprite(SpriteShields, 2, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_NOFLIP);
			else
				G->DrawSprite(SpriteShields, 6, 5 - ((ShieldAnimation - 1) / 2), EZX + myOffX - CamX, EZY + myOffY - CamY, 0, XSpeed < 0 ? IE_FLIPX : IE_NOFLIP);
		}
		else if (Shield == ShieldType::Electric && (Scene->Frame & 1)) {
			G->DrawSprite(SpriteShields, 3, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_NOFLIP);
		}
		else if (Shield == ShieldType::Bubble && !((ShieldFrame / 0x100) & 1) && !(Scene->Frame & 1)) {
			if (ShieldAction)
				G->DrawSprite(SpriteShields, 4, 2, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_FLIPY);
			else
				G->DrawSprite(SpriteShields, 1, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_FLIPY);
		}
		else if (Shield == ShieldType::Instashield) {
			G->DrawSprite(Scene->Objects3Sprite, 12, 8 - ShieldAnimation, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_NOFLIP);
		}
		else if (Shield == ShieldType::Basic && !(Scene->Frame & 1)) {
			G->DrawSprite(SpriteShields, 0, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, !(Scene->Frame & 1) ? IE_FLIPX : IE_NOFLIP);
		}
	}

	// Draw Player
	if (Invincibility != InvincibilityType::Temporary ||
		InvincibilityTimer % 6 < 3 ||
		Action == ActionType::Transform) {
		int FinalAngle = DisplayAngle >> 8;

		int x = 0;
		int y = 0;
		if (Action == ActionType::Rolling) {
			x = (IMath::sinHex(Angle) * (H / 2 - 16)) >> 16;
			y = (IMath::cosHex(Angle) * (H / 2 - 16)) >> 16;
		}
		if (Action == ActionType::Conveyor)
			y = currentFrame2.H / 2 + currentFrame2.OffY;
		if (CurrentAnimation == 38 || CurrentAnimation == 39)
			y = 20;

		/*
		"Sprites/Players/TailSprite.bin"
		"Tails 0" (55) (Flags: 04, FtL: 0, Spd: 64, Frames: 10)
		"Tails 1" (56) (Flags: 01, FtL: 0, Spd: 64, Frames: 6)
		"Tails 2" (57) (Flags: 00, FtL: 0, Spd: 128, Frames: 6)
		"Tails 3" (58) (Flags: 00, FtL: 0, Spd: 64, Frames: 6)
		"Tails 4" (59) (Flags: 00, FtL: 0, Spd: 64, Frames: 6)
		"Tails 5" (60) (Flags: 01, FtL: 0, Spd: 32, Frames: 6)
		"Tails 6" (61) (Flags: 01, FtL: 0, Spd: 64, Frames: 10)
		*/
		// Draw Tails' tails
		int Ani = 0;
		int Ang = 0;
		int Fli = 0;
		int Fra = 0;
		if (Character == CharacterType::Tails) {
			if (CurrentAnimation <= 3) {
				Ani = 55;
				Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
				Fra = (Scene->Frame >> 2) % 10;
				if (!Thremixed)
					Fra = (Scene->Frame >> 3) % 5;
			}
			else if (CurrentAnimation == 4) {
				Ani = 61;
				Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
				Fra = (Scene->Frame >> 2) % 10;
				if (!Thremixed)
					Fra = (Scene->Frame >> 3) % 5;
				Ang = FinalAngle;
			}
			else if (CurrentAnimation >= 5 && CurrentAnimation <= 9) {
				// Do nothing, as these tails are in-sprite.
				Ani = 0;
			}
			else if (CurrentAnimation == 10) {
				Ani = 56;
				Ang = IMath::atanHex(XSpeed, -YSpeed);
				Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPY;
				Fra = IMath::clamp(IMath::abs(GroundSpeed) >> 7, 1, 8);
				if (!Thremixed)
					Fra = ((Scene->Frame >> 2) * IMath::clamp(IMath::abs(GroundSpeed) >> 9, 1, 2)) % 4;
				else
					Fra = ((Scene->Frame >> 2) * Fra) % 6;
			}
			else if (CurrentAnimation >= 11 && CurrentAnimation <= 12) {
				// Do nothing, as these tails are in-sprite.
				Ani = 0;
			}
			else if (CurrentAnimation >= 13 && CurrentAnimation <= 14) {
				Ani = 57;
				Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
				Fra = (Scene->Frame >> 2) % 6;
				if (!Thremixed)
					Fra = (Scene->Frame >> 2) % 4;
				Ang = FinalAngle;
			}
			else if (CurrentAnimation == 15) {
				Ani = 55;
				Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
				Fra = (Scene->Frame >> 1) % 10;
				if (!Thremixed)
					Fra = (Scene->Frame >> 2) % 5;
			}
			else if (CurrentAnimation == 16) {
				// Tails does not have a drop dash, but just in case...
				Ani = 56;
				Ang = IMath::atanHex(XSpeed, -YSpeed);
				Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPY;
				Fra = ((Scene->Frame >> 2) * IMath::clamp(IMath::abs(GroundSpeed) >> 7, 1, 8)) % 6;
				if (!Thremixed)
					Fra = ((Scene->Frame >> 2) * IMath::clamp(IMath::abs(GroundSpeed) >> 7, 1, 8)) % 4;
			}
			else if (CurrentAnimation == 17) {
				// Pushing
				Ani = 55;
				Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
				Fra = (Scene->Frame >> 2) % 10;
				if (!Thremixed)
					Fra = (Scene->Frame >> 3) % 5;
			}
			else if (CurrentAnimation >= 18 && CurrentAnimation <= 27) {
				// Do nothing, as these tails are in-sprite.
				Ani = 0;
			}
			else if (CurrentAnimation == 28) {
				Ani = 58;
				Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
				Fra = (Scene->Frame >> 2) % 6;
				if (!Thremixed)
					Fra = (Scene->Frame >> 2) % 4;
				Ang = FinalAngle;
			}
			else if (CurrentAnimation >= (int)AnimationEnum::Fly) {
				Ani = 0;
				if (!Thremixed && CurrentAnimation <= (int)AnimationEnum::FlyLiftTired) {
					Ani = 62;
					Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
					Fra = (Scene->Frame) & 1;
					Ang = 0;
				}
			}

			if (Ani > 0)
				G->DrawSprite(Sprites[0], Ani, Fra, X + x - CamX, Y + y - CamY, Ang, Fli);
		}

		ISprite::Animation animation = Sprites[0]->Animations[CurrentAnimation];
		ISprite::AnimFrame currentFrame = animation.Frames[CurrentFrame / 0x100];

		if ((SuperForm && Thremixed) || HyperForm || (SpeedSneakersActive && Thremixed) || Action == ActionType::MightyStomp) {
			for (int i = -5 - 8; i <= -5; i += 4) {
				G->SetDrawAlpha(0xFF + i * 0xC);
				PlayerStatus status = PlayerStatusTable[(PlayerStatusTableIndex + 0x20 + i) & 0x1F];
				int status_Y = status.Y;
				if (Ground && Angle == 0)
					status_Y = EZY;

				if (Character == CharacterType::Tails) {
					if (Action == ActionType::Jumping || Action == ActionType::Rolling) {
						Ang = IMath::atanHex(status.XSpeed, -status.YSpeed);
					}

					if (Ani > 0)
						G->DrawSprite(Sprites[0], Ani, Fra, status.X + x - CamX, status_Y + y - CamY, Ang, Fli);
				}

				G->DrawSprite(Sprites[currentFrame.SheetNumber], CurrentAnimation, CurrentFrame / 0x100, status.X + x - CamX, status_Y + y - CamY, FinalAngle, DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX);
			}
		}

		G->SetDrawAlpha(0xFF);

		G->DrawSprite(Sprites[currentFrame.SheetNumber], CurrentAnimation, CurrentFrame / 0x100, EZX + x - CamX, EZY + y - CamY, FinalAngle, DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX);
	
		if (App->viewObjectCollision) {
			G->SetDrawAlpha(0x80);
			G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
			G->SetDrawAlpha(0xFF);
		}
}

	// Draw spindash dust
	if (Action == ActionType::Spindash)
		G->DrawSprite(SpriteDashDust, 1, DashFrame >> 8, EZX - CamX, EZY + H / 2 - CamY, 0, (DisplayFlip < 0) ? IE_FLIPX : IE_NOFLIP);

	// Draw shields (Above player)
	if (!SuperForm && !HyperForm && Invincibility != InvincibilityType::Full) {
		if (Shield == ShieldType::Fire && !((ShieldFrame >> 8) & 1)) {
			if (ShieldAnimation == 0)
				G->DrawSprite(SpriteShields, 2, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_NOFLIP);
			else
				G->DrawSprite(SpriteShields, 6, 5 - ((ShieldAnimation - 1) / 2), EZX + myOffX - CamX, EZY + myOffY - CamY, 0, XSpeed < 0 ? IE_FLIPX : IE_NOFLIP);
		}
		else if (Shield == ShieldType::Electric && !(Scene->Frame & 1)) {
			G->DrawSprite(SpriteShields, 3, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_NOFLIP);
		}
		else if (Shield == ShieldType::Bubble && (((ShieldFrame / 0x100) & 1) || (Scene->Frame & 1))) {
			if (ShieldAction)
				G->DrawSprite(SpriteShields, 4, 2, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_FLIPY);
			else
				G->DrawSprite(SpriteShields, 1, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_FLIPY);
		}
		else if (Shield == ShieldType::Basic && (Scene->Frame & 1)) {
			G->DrawSprite(SpriteShields, 0, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, !(Scene->Frame & 1) ? IE_FLIPX : IE_NOFLIP);
		}
	}

	// Draw Invincibility stars
	if (Invincibility == InvincibilityType::Full) {
		int star = 0;
		G->SetDrawFunc(1);
		for (int i = -5 - 8; i <= -1; i += 4) {
			G->SetDrawAlpha(0xFF + i * 0x8);
			PlayerStatus status = PlayerStatusTable[(PlayerStatusTableIndex + 0x20 + i) & 0x1F];
			ISprite::Animation animation = SpriteShields2->Animations[star];
			// ISprite::AnimFrame currentFrame = animation.Frames[Scene->Frame % animation.FrameCount];

			int x, y, ang;
			ang = (((Scene->Frame + star) % 16) * 0x2FE / 16 + (Scene->Frame << 2));
			x = (IMath::cosHex(ang) * 16) >> 16;
			y = (IMath::sinHex(ang) * 16) >> 16;

			G->DrawSprite(SpriteShields2, star, Scene->Frame % animation.FrameCount,
				status.X - x - CamX,
				status.Y + y - CamY,
				0, IE_NOFLIP);

			G->DrawSprite(SpriteShields2, star, Scene->Frame % animation.FrameCount,
				status.X + x - CamX,
				status.Y - y - CamY,
				0, IE_NOFLIP);

			star++;
		}
		G->SetDrawFunc(0);
		G->SetDrawAlpha(0xFF);
	}
}

void IPlayer::Jump() {
	for (int x = -9; x <= 9 && AngleMode == 0 && Action != ActionType::Climb; x++) {
		if (Scene->CollisionAt(EZX + x, EZY - 25, NULL, 2, this)) {
			return;
		}
	}

	int16_t jmp = 0x680;
	if (Character == CharacterType::Knuckles)
		jmp = 0x600;
	else if (Character == CharacterType::Ray)
		jmp = 0x6B8;

	if (Underwater)
		jmp -= 0x300;

	if (Character == CharacterType::Sonic && (SuperForm || HyperForm)) {
		jmp = 0x800;
		if (Underwater)
			jmp = 0x380;
	}

	XSpeed -= (jmp * IMath::sinHex(Angle)) >> 16;
	YSpeed -= (jmp * IMath::cosHex(Angle)) >> 16;

	Ground = false;
	Angle = 0;
	AngleMode = 0;
	ShieldUsable = true;

	AngleIslandFlag = false;

	JumpVariable = 1;

	Action = ActionType::Jumping;
	Sound::Play(Sound::SFX_JUMP);
}

void IPlayer::Hurt(int x, bool spike) {
	if (Action == ActionType::Hurt ||
		Shield == ShieldType::Instashield ||
		Action == ActionType::Dead ||
		Invincibility != InvincibilityType::None ||
		SuperForm || HyperForm ||
		Action == ActionType::Transform)
		return;

	if (Character == CharacterType::Mighty && Action == ActionType::Jumping) {
		Action = ActionType::MightyUncurl;
		YSpeed = -YSpeed;
		XSpeed = 0x360 * DisplayFlip;

		// Vibrate(VibrationType::DamageSmall);
		Sound::Play(Sound::SFX_MIGHTY_UNSPIN);
		return;
	}

	ObjectControlled = 0;
	DisplayAngle = 0;
	Angle = 0;

	if (Shield == ShieldType::None) {
		Vibrate(VibrationType::DamageSmall);
		if (Rings > 0 || Sidekick) {
			Action = ActionType::Hurt;
			//if (CollisionCSensor(-1, 6) == false && CollisionDSensor(-1, 6) == false)
			YSpeed = -0x400;
			//else
			//    YSpeed = 0;
			Ground = false;
			XSpeed = 0x200 * IMath::sign(EZX - x);
			if (XSpeed == 0) XSpeed = -0x200;
			if (Underwater) {
				XSpeed >>= 1;
				YSpeed >>= 1;
			}

			CreateRingLoss();
			/*
			if (!spike)
			Scene->aud_Spiked->Play(1); // aud_Spiked $AudioPlay(aud_RingLoss, 1);
			else
			Scene->aud_Spiked->Play(1);
			//*/
		}
		else {
			Die(false);
		}
	}
	else if (Invincibility == InvincibilityType::None) {
		Shield = ShieldType::None;
		SaveGame::CurrentShield = (byte)Shield;
		Action = ActionType::Hurt;
		Vibrate(VibrationType::DamageLarge);

		Sound::Play(Sound::SFX_SPIKE_DEATH);

		YSpeed = -0x400;
		Ground = false;
		XSpeed = 0x200 * IMath::sign(EZX - x);
		if (XSpeed == 0) XSpeed = -0x200;
		if (Underwater) {
			XSpeed >>= 1;
			YSpeed >>= 1;
		}
	}
}

void IPlayer::Die(bool drown) {
	Action = ActionType::Dead;
	XSpeed = 0;
	Angle = 0;
	AngleMode = 0;
	DisplayAngle = 0;
	Ground = false;
	SaveGame::Savefiles[SaveGame::CurrentSaveFile].Shield = 0;
	if (drown) {
		YSpeed = 0;
		Sound::Play(Sound::SFX_DROWN);
		if (!Sidekick)
			App->Audio->ClearMusic();
		UnderwaterTimer = 1800;
	}
	else {
		YSpeed = -0x700;
		Sound::Play(Sound::SFX_DEATH);
	}
	VisualLayer = 1;
	Invincibility = InvincibilityType::None;
}

void IPlayer::CreateRingLoss() {
	if (Cutscene) return;
	if (Sidekick) return;

	int t = 0;
	int angle = 72;
	bool n = false;
	int spd = 0x400;
	int LossRings = Rings;

	if (LoseAllRings) {
		if (Rings > 32) {
			LossRings = 32;
		}
		Rings = 0;
	}
	else if (!LoseAllRings) {
		if (Rings > 32) {
			Rings = Rings - 32;
			LossRings = 32;
		}
		else {
			Rings = 0;
		}
	}

	RingAlarm = 64;

	while (t < LossRings) {
		int xspd = (spd * IMath::cosHex(angle)) >> 16;
		int yspd = (spd * IMath::sinHex(angle)) >> 16;
		if (n) {
			xspd = -xspd;
			angle += 0x10;
		}
		Scene->AddActiveRing(EZX, EZY, xspd, yspd, -1);

		n = !n;
		t++;

		if (t == 16) {
			spd = 0x200;
			angle = 72;
		}
	}

	Sound::Play(Sound::SFX_RINGLOSS);
}

void IPlayer::Vibrate(VibrationType v) {
	double strengths[7] = {
		0.0,
		0.35,
		0.75,
		0.35,
		0.75,
		0.15,
		0.85,
	};
	int durations[7] = {
		0,
		200,
		200,
		650,
		650,
		150,
		350,
	};
	App->Input->Vibrate(0, strengths[(int)v], durations[(int)v]);
}

void IPlayer::Deform() {
	if (!SuperForm && !HyperForm) return;

	SuperForm = false;
	HyperForm = false;
	SuperFormTimer = 0;
	SuperFormAnim = SuperFormAnimType::Deforming;
	InvincibilityTimer = 0;
	Invincibility = InvincibilityType::None;
}

void IPlayer::CheckDespawn() {
	if (!Sidekick) return;
	if (Action == ActionType::Respawn) return;

	if (OnScreen) {
		RespawnTimer = 0;
	} else {
		RespawnTimer++;
		if (RespawnTimer >= 0x12C) {
			Action = ActionType::Respawn;
			RespawnTimer = 0;
			EZX = Scene->Player->EZX;
			if (Scene->CameraY - 0x60 > 0) {
				EZY = Scene->CameraY - 0x60;
			} else {
				EZY = 0;
            }
		}
	}
}

void IPlayer::GiveRing(int n) {
	if (Sidekick)
		Scene->Player->Rings += n;
	else
		Rings += n;

	if (Rings >= 200) App->Achievements->SetAchievement(0, true); //Ring Hog!

	if (Rings >= RingLifeValue) {
		RingLifeValue += 100;
		GiveLife(1);
	}
}
void IPlayer::GiveLife(int n) {
	if (!Sound::Audio->IsPlayingMusic(Sound::SoundBank[0xFB])) Sound::Audio->PushMusic(Sound::SoundBank[0xFB], false, 0);

	if (Sidekick)
		Scene->Player->Lives += n;
	else
		Lives += n;
}

void IPlayer::HandlePathSwitchers() {
	int sz_l = XSpeed >> 8;
	int sz_r = XSpeed >> 8;

	if (sz_l > 0)
		sz_l = 0;
	if (sz_r > 0)
		sz_r = 0;

	for (int i = 0; i < Scene->PlaneSwitchCount; i++) {
		int W = 8 * Scene->PlaneSwitchers[i].Size;
		int H = 8 * Scene->PlaneSwitchers[i].Size;
		int rnd = (Scene->PlaneSwitchers[i].Angle & 0xC0);
		if (rnd == 0x00 ||
			rnd == 0x80) {
			W = 0;
		}
		else {
			H = 0;
		}

		if (rnd != Scene->PlaneSwitchers[i].Angle)
			continue; // just don't even deal with angles like these tbh

		if (EZX + 10 + sz_l >= Scene->PlaneSwitchers[i].X - W &&
			EZX - 10 + sz_r < Scene->PlaneSwitchers[i].X + W &&
			EZY + 10 + 00 >= Scene->PlaneSwitchers[i].Y - H &&
			EZY - 10 - 00 < Scene->PlaneSwitchers[i].Y + H) {
			if (Scene->PlaneSwitchers[i].OnPath) {
				if (Ground) {
					int dot = 0;
					dot += XSpeed * ((IMath::cosHex(Scene->PlaneSwitchers[i].Angle) * IMath::abs(XSpeed)) >> 16);
					dot += YSpeed * ((IMath::sinHex(Scene->PlaneSwitchers[i].Angle) * IMath::abs(YSpeed)) >> 16);

					if (dot > 0) {
						Layer = (Scene->PlaneSwitchers[i].Flags >> 3) & 1;
						VisualLayer = (Scene->PlaneSwitchers[i].Flags >> 2) & 1;
					}
					else {
						Layer = (Scene->PlaneSwitchers[i].Flags >> 1) & 1;
						VisualLayer = (Scene->PlaneSwitchers[i].Flags >> 0) & 1;
					}
				}
			}
			else {
				int dot = 0;
				dot += XSpeed * ((IMath::cosHex(Scene->PlaneSwitchers[i].Angle) * IMath::abs(XSpeed)) >> 16);
				dot += YSpeed * ((IMath::sinHex(Scene->PlaneSwitchers[i].Angle) * IMath::abs(YSpeed)) >> 16);

				if (dot > 0) {
					Layer = (Scene->PlaneSwitchers[i].Flags >> 3) & 1;
					VisualLayer = (Scene->PlaneSwitchers[i].Flags >> 2) & 1;
				}
				else {
					Layer = (Scene->PlaneSwitchers[i].Flags >> 1) & 1;
					VisualLayer = (Scene->PlaneSwitchers[i].Flags >> 0) & 1;
				}
			}
		}
	}
}
void IPlayer::HandleMonitors() {
	ISprite::Animation animation2 = Sprites[0]->Animations[CurrentAnimation];
	ISprite::AnimFrame currentFrame2 = animation2.Frames[CurrentFrame / 0x100];
	int myOffY = 0;
	if (Action == ActionType::Conveyor)
		myOffY = currentFrame2.H / 2 + currentFrame2.OffY;
	if (CurrentAnimation == 38 || CurrentAnimation == 39)
		myOffY = 20;

	for (int o = 0; o < Scene->RingPropCount; o++) {
		LevelScene::ObjectProp obj = Scene->RingProps[o];
		bool Collided = (
			(int)obj.X + 8 >= EZX - W / 2 + (XSpeed >> 8) &&
			(int)obj.Y + 8 >= EZY - H / 2 + (YSpeed >> 8) + myOffY &&
			(int)obj.X - 8 < EZX + W / 2 + (XSpeed >> 8) &&
			(int)obj.Y - 8 < EZY + H / 2 + (YSpeed >> 8) + myOffY
			);

		if (Shield == ShieldType::Electric) {
			int diffX = (int)obj.X - (int)EZX;
			int diffY = (int)obj.Y - (int)EZY;

			if (diffX * diffX + diffY * diffY < 0x1000 && obj.ID) { // radius of 64, then squared
				Scene->AddActiveRing(obj.X, obj.Y, 0, 0, PlayerID);
				Scene->RingProps[o].ID = 0;
			}
		}

		if (Collided && obj.ID) {
			Scene->RingProps[o].ID = 0;
			GiveRing(1);
			Sound::Play(Sound::SFX_RING);

			int rx[3] = { -4, 1, 4 };
			int ry[3] = { 1, -2, 3 };
			if (SaveGame::CurrentMode == 1) {
				for (int i = 0; i < 3; i++) {
					Explosion* ringsparkle;
					ringsparkle = new Explosion();
					ringsparkle->G = G;
					ringsparkle->App = App;
					ringsparkle->CurrentAnimation = 9;
					ringsparkle->FlipX = false;
					ringsparkle->Active = true;
					ringsparkle->Sprite = Scene->ItemsSprite;
					ringsparkle->X = obj.X + rx[i];
					ringsparkle->Y = obj.Y + ry[i];
					Scene->Explosions.push_back(ringsparkle);
				}
			}
			else {
				Explosion* ringsparkle;
				ringsparkle = new Explosion();
				ringsparkle->G = G;
				ringsparkle->App = App;
				ringsparkle->CurrentAnimation = 9;
				ringsparkle->FlipX = false;
				ringsparkle->Active = true;
				ringsparkle->Sprite = Scene->ItemsSprite;
				ringsparkle->X = obj.X;
				ringsparkle->Y = obj.Y;
				Scene->Explosions.push_back(ringsparkle);
			}
		}
	}

	Rect EnemyHitbox;
	for (int o = 0; o < Scene->ObjectEnemiesCount; o++) {
		Enemy* obj = Scene->ObjectsEnemies[o];
		if (obj != NULL) {
			if (obj->Active && obj->HitCount > 0) {
				bool Bounceable = false;
				bool IsAttacking = false;
				bool IsAttackingAbsolute = false;
				bool ExtendedShieldHitbox = false;

				ExtendedShieldHitbox |= Shield == ShieldType::Instashield;
				ExtendedShieldHitbox |= obj->BounceOffShield && Shield != ShieldType::None;

				if (!obj->HitboxEnemy.Empty()) {
					EnemyHitbox = obj->HitboxEnemy;
					// EnemyHitbox = EnemyHitbox.FlipX(obj->FlipX).FlipY(obj->FlipY);
				}
				else {
					EnemyHitbox = { -obj->W / 2, obj->W / 2, -obj->H / 2, obj->H / 2 };
				}

				bool Collided = false;
				if (obj->Radius > 1) {
					if (ExtendedShieldHitbox) {
						int DeltaX = int(obj->X) - int(EZX);
						int DeltaY = int(obj->Y) - int(EZY);
						Collided = (DeltaX * DeltaX + DeltaY * DeltaY) < ((obj->Radius + 24) * (obj->Radius + 24));
					}
					else {
						int DeltaX = (int)obj->X - IMath::max(X - W / 2, IMath::min((int)obj->X, X + W / 2));
						int DeltaY = (int)obj->Y - IMath::max(Y - H / 2, IMath::min((int)obj->Y, Y + H / 2));
						Collided = (DeltaX * DeltaX + DeltaY * DeltaY) < (obj->Radius * obj->Radius);
					}
				}
				else {
					if (ExtendedShieldHitbox) {
						int DeltaX = EZX - IMath::max((int)obj->X + EnemyHitbox.Left, IMath::min(EZX, (int)obj->X + EnemyHitbox.Right));
						int DeltaY = EZY - IMath::max((int)obj->Y + EnemyHitbox.Top, IMath::min(EZY, (int)obj->Y + EnemyHitbox.Bottom));
						Collided = (DeltaX * DeltaX + DeltaY * DeltaY) < (24 * 24);
					}
					else {
						Collided =
							(int)obj->X + EnemyHitbox.Right >= X - W / 2 &&
							(int)obj->Y + EnemyHitbox.Bottom >= Y - H / 2 &&
							(int)obj->X + EnemyHitbox.Left < X + W / 2 &&
							(int)obj->Y + EnemyHitbox.Top < Y + H / 2;
					}
				}

				if (Collided) {
					Bounceable |= Shield != ShieldType::None;
					if ((obj->X < EZX && DisplayFlip < 0) ||
						(obj->X > EZX && DisplayFlip > 0))
						Bounceable |= Action == ActionType::Glide;
					if (obj->Y < EZY)
						Bounceable |= Action == ActionType::Fly && !Underwater;

					Bounceable |= Action == ActionType::Jumping && Character == CharacterType::Mighty && true;
					Bounceable |= Action == ActionType::MightyStomp;

					if (obj->BounceOffShield && Bounceable) {
						int angle = IMath::atanHex(EZX - int(obj->X), EZY - int(obj->Y));
						obj->XSpeed = (-0x800 * IMath::cosHex(angle)) >> 16;
						obj->YSpeed = (-0x800 * IMath::sinHex(angle)) >> 16;
						obj->Harmful = false;
						continue;
					}
					else if (obj->NegatedByFireShield && Shield == ShieldType::Fire) {
						obj->OnHit();
						continue;
					}
					else if (obj->NegatedByElectricShield && Shield == ShieldType::Electric) {
						obj->OnHit();
						continue;
					}
					else if (obj->NegatedByBubbleShield && Shield == ShieldType::Bubble) {
						obj->OnHit();
						continue;
					}

					IsAttacking |= SuperForm;
					IsAttacking |= HyperForm;
					IsAttacking |= Shield == ShieldType::Instashield;
					IsAttacking |= Invincibility == InvincibilityType::Full;
					IsAttacking |= Action == ActionType::MightyStomp;
					IsAttackingAbsolute = IsAttacking;

					if ((obj->X < EZX && DisplayFlip < 0) ||
						(obj->X > EZX && DisplayFlip > 0))
						IsAttacking |= Action == ActionType::Glide;
					if (obj->Y < EZY)
						IsAttacking |= Action == ActionType::Fly && !Underwater;
					IsAttacking |= Action == ActionType::Jumping;
					IsAttacking |= Action == ActionType::Rolling;
					IsAttacking |= Action == ActionType::Spindash;

					if (IsAttacking) {
						if (obj->Invincible) {
							if (obj->Harmful) {
								Hurt(obj->X, false);
								goto FinishBadnikBounce;
							}
							else
								continue;
						}
						else if (obj->Hurting && !IsAttackingAbsolute) {
							Hurt(obj->X, false);
							goto FinishBadnikBounce;
						}
						else if (obj->Hurting) {
							obj->OnHit();
							goto DoBadnikBounce;
						}
						else {
							obj->OnHit();
							goto DoBadnikBounce;
						}
					}
					else if (obj->Harmful) {
						Hurt(obj->X, false);
						goto FinishBadnikBounce;
					}
					else {
						continue;
					}

				DoBadnikBounce:
					if (obj->Boss) {
						if (IsAttacking) {
							Sound::Play(Sound::SFX_BOSSHIT);

							if (Action == ActionType::MightyStomp)
								goto FinishBadnikBounce;

							Vibrate(VibrationType::ImpactLarge);
							if (Ground) {
								GroundSpeed = -GroundSpeed;
							}
							else {
								if (Action == ActionType::Glide) {
									Action = ActionType::GlideFall;
								}
								XSpeed = -XSpeed;
								YSpeed = -YSpeed;
							}
						}
					}
					else {
						if (EnemyCombo == 0) {
							Scene->Score += 100;
						}
						else if (EnemyCombo == 1) {
							Scene->Score += 200;
						}
						else if (EnemyCombo == 2) {
							Scene->Score += 500;
						}
						else if (EnemyCombo == 15) {
							Scene->Score += 10000;
						}
						else {
							Scene->Score += 1000;
						}
						Scene->AddScoreGhost(EnemyCombo, obj->X, obj->Y);
						if (EnemyCombo < 15)
							EnemyCombo++;
						Vibrate(VibrationType::ImpactLarge);

						if (Action == ActionType::MightyStomp)
							goto FinishBadnikBounce;

						if (EZY < obj->Y && YSpeed > 0) {
							YSpeed = -YSpeed;
						}
						else {
							if (YSpeed < 0)
								YSpeed += 0x100;
							else
								YSpeed -= 0x100;
						}
					}
				FinishBadnikBounce:
					YSpeed += 0;
				}
			}
		}
	}

	if (Sidekick) return;

	for (int o = 0; o < Scene->ObjectBreakableCount; o++) {
		Object* obj = Scene->ObjectsBreakable[o];
		if (obj == NULL || obj == nullptr) {
			continue;
		}
		if (obj->Active) {
			if ((int)obj->X + obj->W / 2 >= EZX - (int)W / 2 + (XSpeed >> 8) - 2 &&
				(int)obj->Y + obj->H / 2 + 2 >= EZY - (int)H / 2 + (YSpeed >> 8) * (Action == ActionType::Spring) &&
				(int)obj->X - obj->W / 2 < EZX + (int)W / 2 + (XSpeed >> 8) + 2 &&
				(int)obj->Y - obj->H / 2 - 2 < EZY + (int)H / 2 + (YSpeed >> 8)) {
				int hitFrom = (int)CollideSide::RIGHT;
				int wy = (W + obj->W) * (int(EZY) - int(obj->Y));
				int hx = (H + obj->H) * (int(EZX) - int(obj->X));

				if (wy > hx)
					if (wy > -hx)
						hitFrom = (int)CollideSide::BOTTOM;
					else
						hitFrom = (int)CollideSide::LEFT;
				else
					if (wy > -hx)
						hitFrom = (int)CollideSide::RIGHT;
					else
						hitFrom = (int)CollideSide::TOP;

				bool Connect;
				int Side;

				Connect = false;
				if (obj->BreakableByRoll != CollideSide::NONE) {
					Side = (int)obj->BreakableByRoll;
					Connect |= (!!(Side & (int)CollideSide::RIGHT) && (hitFrom == CollideSide::RIGHT && GroundSpeed < -0x80));
					Connect |= (!!(Side & (int)CollideSide::LEFT) && (hitFrom == CollideSide::LEFT && GroundSpeed > 0x80));
					Connect |= (!!(Side & (int)CollideSide::TOP) && (hitFrom == CollideSide::TOP && YSpeed > 0));
					Connect |= (!!(Side & (int)CollideSide::BOTTOM) && (hitFrom == CollideSide::BOTTOM && YSpeed < 0));
				}

				if (Connect && Action == ActionType::Rolling) {
					if (hitFrom == CollideSide::TOP || hitFrom == CollideSide::BOTTOM) {
						obj->OnBreakVertical(PlayerID, hitFrom);
					}
					else {
						if (obj->OnBreakHorizontal(PlayerID, hitFrom)) {
							//Action = ActionType::Normal;
							Vibrate(VibrationType::ImpactSmall);
						}
						else {
							SubX -= IMath::abs(GroundSpeed) << 8;
							Vibrate(VibrationType::ImpactSmall);
						}
					}
				}

				bool NonSonicSuperCanBreak = true;

				Connect = false;
				if (obj->BreakableBySuper != CollideSide::NONE) {
					Side = (int)obj->BreakableBySuper;
					Connect |= (!!(Side & (int)CollideSide::RIGHT) && (hitFrom == CollideSide::RIGHT && XSpeed < -0x80));
					Connect |= (!!(Side & (int)CollideSide::LEFT) && (hitFrom == CollideSide::LEFT && XSpeed > 0x80));
					Connect |= (!!(Side & (int)CollideSide::TOP) && (hitFrom == CollideSide::TOP && YSpeed > 0));
					Connect |= (!!(Side & (int)CollideSide::BOTTOM) && (hitFrom == CollideSide::BOTTOM && YSpeed < 0));
				}

				if (Connect && (Character == CharacterType::Sonic || NonSonicSuperCanBreak) && (SuperForm || HyperForm)) {
					SubX -= IMath::abs(GroundSpeed) << 8;
					obj->OnBreakHorizontal(PlayerID, hitFrom);
				}

				Connect = false;
				if (obj->BreakableBySpring != CollideSide::NONE) {
					Side = (int)obj->BreakableBySpring;
					Connect |= (!!(Side & (int)CollideSide::RIGHT) && (hitFrom == CollideSide::RIGHT && XSpeed < -0x80));
					Connect |= (!!(Side & (int)CollideSide::LEFT) && (hitFrom == CollideSide::LEFT && XSpeed > 0x80));
					Connect |= (!!(Side & (int)CollideSide::TOP) && (hitFrom == CollideSide::TOP && YSpeed > 0));
					Connect |= (!!(Side & (int)CollideSide::BOTTOM) && (hitFrom == CollideSide::BOTTOM && YSpeed < 0));
				}

				if (Connect && Action == ActionType::Spring) {
					if (hitFrom == CollideSide::TOP || hitFrom == CollideSide::BOTTOM) {
						obj->OnBreakVertical(PlayerID, hitFrom);
					}
					else {
						obj->OnBreakHorizontal(PlayerID, hitFrom);
					}
				}

				Connect = false;
				if (obj->BreakableByGlide != CollideSide::NONE) {
					Side = (int)obj->BreakableByGlide;
					Connect |= (!!(Side & (int)CollideSide::RIGHT) && (hitFrom == CollideSide::RIGHT && XSpeed < -0x80));
					Connect |= (!!(Side & (int)CollideSide::LEFT) && (hitFrom == CollideSide::LEFT && XSpeed > 0x80));
					Connect |= (!!(Side & (int)CollideSide::TOP) && (hitFrom == CollideSide::TOP && YSpeed > 0));
					Connect |= (!!(Side & (int)CollideSide::BOTTOM) && (hitFrom == CollideSide::BOTTOM && YSpeed < 0));
				}

				if (Connect && Action == ActionType::Glide) {
					if (YSpeed > 0x600)
						Vibrate(VibrationType::ImpactLarge);
					else
						Vibrate(VibrationType::ImpactSmall);

					if (hitFrom == CollideSide::RIGHT || hitFrom == CollideSide::LEFT) {
						obj->OnBreakHorizontal(PlayerID, hitFrom);
					}
					else {
						if (EZY < obj->Y)
							YSpeed = -YSpeed;

						obj->OnBreakVertical(PlayerID, hitFrom);
					}
				}

				Connect = false;
				if (obj->BreakableByJump != CollideSide::NONE) {
					Side = (int)obj->BreakableByJump;
					Connect |= (!!(Side & (int)CollideSide::RIGHT) && (hitFrom == CollideSide::RIGHT && XSpeed < -0x80));
					Connect |= (!!(Side & (int)CollideSide::LEFT) && (hitFrom == CollideSide::LEFT && XSpeed > 0x80));
					Connect |= (!!(Side & (int)CollideSide::TOP) && (hitFrom == CollideSide::TOP && YSpeed > 0));
					Connect |= (!!(Side & (int)CollideSide::BOTTOM) && (hitFrom == CollideSide::BOTTOM && YSpeed < 0));
				}

				if (Connect && (Action == ActionType::Jumping || Action == ActionType::MightyStomp)) {
					if (EZY < obj->Y + 8) { // add "|| Settings_SonicKnucklesMonitorBehavior"
						if (obj->OnBreakVertical(PlayerID, hitFrom) == 1) {
							if (Action != ActionType::MightyStomp) {
								if (YSpeed > 0x600)
									Vibrate(VibrationType::ImpactLarge);
								else
									Vibrate(VibrationType::ImpactSmall);

								if(Action != ActionType::MightyStomp)  YSpeed = -YSpeed;
							}
						}
					}
					else if (hitFrom == CollideSide::BOTTOM) {
						obj->YSpeed = -0x300;
						YSpeed = 0x100;
						Vibrate(VibrationType::SpindashRev);
					}
				}

				Connect = false;
				if (obj->BreakableByKnuckles != CollideSide::NONE) {
					Side = (int)obj->BreakableByKnuckles;
					Connect |= (!!(Side & (int)CollideSide::RIGHT) && (hitFrom == CollideSide::RIGHT && XSpeed < -0x80));
					Connect |= (!!(Side & (int)CollideSide::LEFT) && (hitFrom == CollideSide::LEFT && XSpeed > 0x80));
					Connect |= (!!(Side & (int)CollideSide::TOP) && (hitFrom == CollideSide::TOP && YSpeed > 0));
					Connect |= (!!(Side & (int)CollideSide::BOTTOM) && (hitFrom == CollideSide::BOTTOM && YSpeed < 0));
				}

				if (Connect && Character == CharacterType::Knuckles) {
					SubX -= IMath::abs(GroundSpeed) << 8;
					obj->OnBreakHorizontal(PlayerID, hitFrom);
				}
			}
		}
	}
}
bool IPlayer::HandleSprings() {
	///*
	for (int o = 0; o < Scene->ObjectSpringCount; o++) {
		Object* obj = Scene->ObjectsSpring[o];
		if (obj != NULL) {
			if (obj->Active) {
				int si = IMath::abs((IMath::sinHex(obj->Rotation * 64 / 90) * 3) >> 16);
				int co = IMath::abs((IMath::cosHex(obj->Rotation * 64 / 90) * 3) >> 16);
				if (obj->X + obj->W / 2 + si - co * 2 >= EZX + (XSpeed >> 8) - W / 2 - 8 &&
					obj->Y + obj->H / 2 + co >= EZY - H / 2 &&
					obj->X - obj->W / 2 - si + co * 2 < EZX + (XSpeed >> 8) + W / 2 + 8 &&
					obj->Y - obj->H / 2 - co < EZY + H / 2) {
					int wy = (W + obj->W) * (int(EZY) - int(obj->Y));
					int hx = (H + obj->H) * (int(EZX) - int(obj->X));

					int hitFrom = (int)CollideSide::RIGHT;

					if (wy > hx)
						if (wy > -hx)
							hitFrom = (int)CollideSide::BOTTOM;
						else
							hitFrom = (int)CollideSide::LEFT;
					else
						if (wy > -hx)
							hitFrom = (int)CollideSide::RIGHT;
						else
							hitFrom = (int)CollideSide::TOP;

					if (obj->OnCollisionWithPlayer(PlayerID, hitFrom, 1)) {
						/*if (Action == ActionType::Hurt) {
						Invincibility = InvincibilityType::Temporary;
						InvincibilityTimer = 120;
						}*/
						return true;
					}
				}
			}
		}
	}
	return false;
	//*/
}

void IPlayer::DoVictory() {
	if (!Ground) return;

	bool DoJump = false;
	GroundSpeed = 0x0;
	XSpeed = 0x0;
	YSpeed = 0x0;
	if (Ground && Action != ActionType::Victory && DoJump) {
		if (Underwater) {
			YSpeed = -0x100;
			XSpeed = 0x80;
		}
		else {
			YSpeed = -0x200;
			XSpeed = 0x100;
		}
		Ground = false;
	}
	Action = ActionType::Victory;
	ControlLocked = true;
	ObjectControlled = 0x80;
	ChangeAnimation((int)AnimationEnum::Victory);
}
void IPlayer::DoSuperTransform() {
	if (Action == ActionType::Transform) return;
	if (SuperForm) return;
	if (HyperForm) return;

	Action = ActionType::Transform;
	SuperFormAnim = SuperFormAnimType::Transforming;
	SuperFormTimer = 0;

	GroundSpeed = 0x0;
	XSpeed = 0x0;
	YSpeed = 0x0;

	Sound::Play(Sound::SFX_TRANSFORM);
}