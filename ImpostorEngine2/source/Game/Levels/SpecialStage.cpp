#if INTERFACE
#include <Game/LevelScene.h>

class Level_SpecialStage : public LevelScene {
public:
    ISprite* Globe = NULL;
    ISprite* GlobeSpin = NULL;
    ISprite* Horizon = NULL;
    ISprite* Objects = NULL;
    ISprite* Players = NULL;

    uint8_t* Layout = NULL;
    uint8_t* LayoutCopy = NULL;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/SpecialStage.h>

#include <Game/Levels/AIZ.h>
#include <Game/Levels/HCZ.h>
#include <Game/Levels/MGZ.h>
#include <Game/Levels/CNZ.h>
#include <Game/Levels/ICZ.h>
#include <Game/Levels/LBZ.h>
#include <Game/Levels/MHZ.h>
#include <Game/Levels/FBZ.h>
#include <Game/Levels/SOZ.h>
#include <Game/Levels/LRZ.h>
#include <Game/Levels/HPZ.h>
#include <Game/Levels/SSZ.h>
#include <Game/Levels/DEZ.h>
#include <Game/Levels/TDZ.h>

#include <Game/Scenes/MainMenu.h>

#include <Game/SaveGame.h>

int PlayerAngle = 0x0000;
int PlayerX = 0x0000;
int PlayerY = 0x0000;
int PlayerLastTouchedObjectX = 0x0000;
int PlayerLastTouchedObjectY = 0x0000;
int PlayerSteps = 0;
int StoredAngle = 0x0;

int PlayerDwordC0 = 0;
int PlayerMaxSpeed = 16;
int PlayerSpeed = 16;
int PlayerAccelerationRate = 2;
int PlayerWaitMovementTimer = 0;
int PlayerIsMovingBackwards = false;
int PlayerIsMoveForwardLocked = false;
int PlayerTileSubPosition = 16;
int SpeedupTimer = 0;
int SpeedupTimerMax = 1800;

int PlayerZ = 0;
int PlayerZSpeed = 0;

int StartAngle = 0x0000;
int StartX = 0x0000;
int StartY = 0x0000;

int PerfectAmount = 0;

int NextAngle = -1;
int Direction = 0;
int DirectionStep = 0;

int BallCount = 0;
int RingCount = 0;

bool ColorFlip = true;

int GameState = 0;

Uint8* LayoutBackup = NULL;
Uint8* LayoutExtra = NULL;

enum {
	SPHERE_RED = 1,
	SPHERE_BLUE = 2,
	SPHERE_BUMPER = 3,
	SPHERE_RING = 4,
	SPHERE_YELLOW = 5,
	SPHERE_EMERALD,
};

Uint32 ColorBG = 0x0044EE;
Uint32 Color1 = 0xEE8800;
Uint32 Color2 = 0x662200;
Uint32 ColorSky = 0x00;
Uint32 ColorGlobe = 0x00;
Sint32 MapThing[0x10][0x100];

PUBLIC Level_SpecialStage::Level_SpecialStage(IApp* app, IGraphics* g) : LevelScene(app, g) {
    ZoneID = 20;
    Act = 0;

    Sound::SoundBank[0] = new ISound("Music/Mixed/BlueSpheresSPD.ogg", true);
    Sound::Audio->LoopPoint[0] = 5309957;

	if (!LayoutBackup)
		LayoutBackup = (Uint8*)calloc(0x400, 1);

	if (!LayoutExtra)
		LayoutExtra = (Uint8*)calloc(0x400, 1);

    Globe = new ISprite("Special/Globe.gif", App);
	ISprite::Animation an;
	an.Name = NULL;
	an.FrameCount = 1;
	an.Frames = (ISprite::AnimFrame*)calloc(1, sizeof(ISprite::AnimFrame));
	ISprite::AnimFrame ts_af;
	ts_af.X = 0;
	ts_af.Y = 0;
	ts_af.W = ts_af.H = 512;
	ts_af.OffX = -256;
	ts_af.OffY = 0;
	an.Frames[0] = ts_af;
	G->MakeFrameBufferID(Globe, an.Frames + 0);
	Globe->Animations.push_back(an);

    GlobeSpin = new ISprite("Special/GlobeSpin.gif", App);
    GlobeSpin->LoadAnimation("Special/GlobeSpin.bin");

    Horizon = new ISprite("Special/Horizon.gif", App);
    Horizon->LoadAnimation("Special/Horizon.bin");

    Objects = new ISprite("Special/Objects.gif", App);
    Objects->LoadAnimation("Special/HUD.bin");
    Objects->LoadAnimation("Special/StageObjects.bin");
    //Objects->LoadAnimation("Special/PaletteIcon.bin");

    Players = new ISprite("Special/Players.gif", App);

	switch (SaveGame::CurrentCharacterFlag)
	{
	case 0:
		Players->LoadAnimation("Special/Sonic.bin");
		break;
	case 1:
		Players->LoadAnimation("Special/Tails.bin");
		break;
	case 2:
		Players->LoadAnimation("Special/Knuckles.bin");
		break;
	case 3:
		Players->LoadAnimation("Special/Mighty.bin");
		break;
	case 4:
		Players->LoadAnimation("Special/Ray.bin");
		break;
	default:
		Players->LoadAnimation("Special/Sonic.bin");
		break;
	}

    Str_TileConfigBin = ":";
    Str_SceneBin = ":";
    Str_TileSprite = ":";
    Str_ObjectsList = ":";
    Str_RingsList = ":";
}

PUBLIC void Level_SpecialStage::Init() {
	PlayerCount = 0;

	//FadeTimer = 0;
	FadeTimerMax = 0x100;
	FadeAction = FadeActionType::FADEIN;
	G->FadeToWhite = true;

	if (!MobileButtonsSprite) {
		MobileButtonsSprite = new ISprite("UI/Mobile Buttons.gif", App);
		ISprite::Animation an;
		an.Name = NULL;
		an.FrameCount = 8;
		an.Frames = (ISprite::AnimFrame*)calloc(8, sizeof(ISprite::AnimFrame));
		for (int i = 0; i < 8; i++) {
			ISprite::AnimFrame ts_af;
			ts_af.X = i * 64;
			ts_af.Y = 0;
			ts_af.W = ts_af.H = 64;
			ts_af.OffX = ts_af.OffY = -32;
			an.Frames[i] = ts_af;
			G->MakeFrameBufferID(MobileButtonsSprite, an.Frames + i);
		}
		MobileButtonsSprite->Animations.push_back(an);
		MobileButtonsSprite->SetTransparentColorIndex(0x05);
		MobileButtonsSprite->UpdatePalette();
	}
	if (!PauseSprite) {
		PauseSprite = new ISprite("UI/PauseMenu.gif", App);
		PauseSprite->SetTransparentColorIndex(0);
		PauseSprite->LoadAnimation("UI/PauseMenu.bin");
	}

	if (!ItemsSprite) {
		//if (SaveGame::CurrentMode == 1) {
			ItemsSprite = new ISprite("Global/Items.gif", App);
			ItemsSprite->Print = true;
			ItemsSprite->LoadAnimation("Global/ItemBox.bin");
			ItemsSprite->LoadAnimation("Global/Ring.bin");
			ItemsSprite->LoadAnimation("Special/Ring.bin");
		/*}
		else {
			ItemsSprite = new ISprite("GlobalS3K/Items.gif", App);
			ItemsSprite->LoadAnimation("GlobalS3K/ItemBox.bin");
			ItemsSprite->LoadAnimation("GlobalS3K/Ring.bin");
			//ItemsSprite->LoadAnimation("Special/Ring.bin");
		}*/
	}

	IResource* BSS_Setup_Bin = IResources::Load("Stages/Special/OBJ_BSS_Setup.bin");
	if (BSS_Setup_Bin) {
		IStreamer reader(BSS_Setup_Bin);

		reader.ReadUInt32(); // Magic

		for (int p = 0; p < 0x10; p++) {
			for (int i = 0; i < 0x100; i++) {
				MapThing[p][i] = 0;
			}
		}

		for (int i = 0; i < 14; i++) {
			char bin[9];
			Uint8 a = reader.ReadByte();
			for (int b = 0; b < 8; b++) {
				bin[b] = '0' + (a >> (7 - b) & 1);
			}
			bin[8] = 0;

			int c = reader.ReadUInt32();
			App->Print(1, "Value %d: %s (%X) %X", i, bin, a, c);
		}

		reader.ReadByte();
		reader.ReadUInt32();
		int count = reader.ReadUInt32();
		for (int i = 0; i < count; i++) {
			reader.ReadUInt32();
		}

		for (int p = 0; p < 6; p++) {
			reader.ReadByte();
			reader.ReadUInt32();
			MapThing[p][0] = reader.ReadUInt32(); // Array Count

			for (int i = 0; i < MapThing[p][0]; i++) {
				MapThing[p][i + 1] = reader.ReadUInt32();
			}
		}

		IResources::Close(BSS_Setup_Bin);
	}

	IResource* LayoutBin = NULL;
	switch (Act) {
		case 0: LayoutBin = IResources::Load("Stages/Special/S3 1.bin"); break;
		case 1: LayoutBin = IResources::Load("Stages/Special/S3 2.bin"); break;
		case 2: LayoutBin = IResources::Load("Stages/Special/S3 3.bin"); break;
		case 3: LayoutBin = IResources::Load("Stages/Special/S3 4.bin"); break;
		case 4: LayoutBin = IResources::Load("Stages/Special/S3 5.bin"); break;
		case 5: LayoutBin = IResources::Load("Stages/Special/S3 6.bin"); break;
		case 6: LayoutBin = IResources::Load("Stages/Special/S3 7.bin"); break;
		case 7: LayoutBin = IResources::Load("Stages/Special/S3 8.bin"); break;
		case 8: LayoutBin = IResources::Load("Stages/Special/SK 1.bin"); break;
		case 9: LayoutBin = IResources::Load("Stages/Special/SK 2.bin"); break;
		case 10: LayoutBin = IResources::Load("Stages/Special/SK 3.bin"); break;
		case 11: LayoutBin = IResources::Load("Stages/Special/SK 4.bin"); break;
		case 12: LayoutBin = IResources::Load("Stages/Special/SK 5.bin"); break;
		case 13: LayoutBin = IResources::Load("Stages/Special/SK 6.bin"); break;
		case 14: LayoutBin = IResources::Load("Stages/Special/SK 7.bin"); break;
		case 15: LayoutBin = IResources::Load("Stages/Special/SK 8.bin"); break;
	}
	if (LayoutBin) {
		IStreamer reader(LayoutBin);
		Layout = (uint8_t*)malloc(0x400);
		LayoutCopy = reader.ReadBytes(0x400);
		StartAngle = reader.ReadUInt16BE();
		StartX = reader.ReadUInt16BE();
		StartY = reader.ReadUInt16BE();
		PerfectAmount = reader.ReadUInt16BE();
		IResources::Close(LayoutBin);
	}

	if (ZoneID == 20) {
		memset(Layout, 0, 0x400);
		for (int x = 0; x < 32; x++) {
			Layout[0x00 << 5 | x] = SPHERE_BUMPER;
			Layout[0x1F << 5 | x] = SPHERE_BUMPER;
			Layout[x << 5 | 0x00] = SPHERE_BUMPER;
			Layout[x << 5 | 0x1F] = SPHERE_BUMPER;
		}
		Layout[0x10 << 5 | 0x10] = SPHERE_BLUE;
		memcpy(LayoutCopy, Layout, 0x400);

		StartX = 0x1200;
		StartY = 0x1200;
		PerfectAmount = 4;
	}

	LayoutBin = IResources::Load("Stages/Special/Colors.bin");
	if (LayoutBin) {
		IStreamer reader(LayoutBin);
		reader.Seek(Act * 0x10);

		Color1 = G->GetRetroColor(reader.ReadUInt16BE());
		Color2 = G->GetRetroColor(reader.ReadUInt16BE());

		ColorBG = G->GetRetroColor(reader.ReadUInt16BE());
		reader.ReadUInt16BE();
		reader.ReadUInt16BE();

		reader.ReadUInt16(); // 0x0000
		ColorSky = reader.ReadUInt16(); // Sky Alpha
		ColorGlobe = reader.ReadUInt16(); // Globe Alpha
		IResources::Close(LayoutBin);
	}
	RestartStage(true, true);

	char levelname[50];
	if (true) {
		sprintf(levelname, "%s%s%d", "Special Stage", " ", Act + 1);
		const char* ModeName;
		if (SaveGame::CurrentMode == 0)
			ModeName = "Classic Mode";
		else if (SaveGame::CurrentMode == 1)
			ModeName = "Mixed Mode";
		else if (SaveGame::CurrentMode == 2)
			ModeName = "Locked On";
		Discord_UpdatePresence(ModeName, levelname, "11", true);
	}
	else {
		sprintf(levelname, "%s%s%d", "Blue Spheres", " Level ", Act + 1);
		Discord_UpdatePresence("Extras", levelname, "11", true);
	}
}

PUBLIC void Level_SpecialStage::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    memcpy(Layout, LayoutCopy, 0x400);
    PlayerX = StartX >> 8;
    PlayerY = StartY >> 8;
	PlayerLastTouchedObjectX = PlayerX;
	PlayerLastTouchedObjectY = PlayerY;
    PlayerAngle = StartAngle;
	PlayerSteps = 0;
    StoredAngle = PlayerAngle >> 12;

	PlayerDwordC0 = 0;
	PlayerMaxSpeed = 16;
	PlayerSpeed = 16;
	PlayerAccelerationRate = 2;
	PlayerWaitMovementTimer = 0;
	PlayerIsMovingBackwards = false;
	PlayerIsMoveForwardLocked = false;
	PlayerTileSubPosition = 16;
	SpeedupTimer = 0;
	SpeedupTimerMax = 1800;
	ColorFlip = true;

	LevelCardTimer = 1.0;

	PlayerZ = 0;
	PlayerZSpeed = 0;

	NextAngle = -1;
	Direction = 0;
	DirectionStep = 0;

	GameState = 0;

    BallCount = 0;
	RingCount = 0;
    for (int i = 0; i < 0x400; i++) {
        if (Layout[i] == 2)
            BallCount++;
    }

	PlayerWaitMovementTimer = 300;
}

PUBLIC Uint8* Level_SpecialStage::LayoutAt(int ox, int oy) {
	ox &= 0x1F; oy &= 0x1F;
	return &Layout[oy << 5 | ox];
}
PUBLIC Uint8* Level_SpecialStage::LayoutBackupAt(int ox, int oy) {
	ox &= 0x1F; oy &= 0x1F;
	return &LayoutBackup[oy << 5 | ox];
}
PUBLIC Uint8* Level_SpecialStage::LayoutExtraAt(int ox, int oy) {
	ox &= 0x1F; oy &= 0x1F;
	return &LayoutExtra[oy << 5 | ox];
}
PUBLIC bool   Level_SpecialStage::HasAllNonBlueNeighbors(int ox, int oy) {
	if ((*LayoutAt(ox - 1, oy - 1) & 0x7F) == SPHERE_BLUE) return false;
	if ((*LayoutAt(ox + 1, oy - 1) & 0x7F) == SPHERE_BLUE) return false;
	if ((*LayoutAt(ox - 1, oy) & 0x7F) == SPHERE_BLUE) return false;
	if ((*LayoutAt(ox + 1, oy) & 0x7F) == SPHERE_BLUE) return false;
	if ((*LayoutAt(ox - 1, oy + 1) & 0x7F) == SPHERE_BLUE) return false;
	if ((*LayoutAt(ox + 1, oy + 1) & 0x7F) == SPHERE_BLUE) return false;
	if ((*LayoutAt(ox, oy - 1) & 0x7F) == SPHERE_BLUE) return false;
	if ((*LayoutAt(ox, oy + 1) & 0x7F) == SPHERE_BLUE) return false;
	return true;
}

int SCD_X[4] = { 1, 0, -1, 0};
int SCD_Y[4] = { 0, -1, 0, 1 };

PUBLIC bool Level_SpecialStage::SphereCheckDirection(int ox, int oy, int dir) {
	int    x = ox;
	int    y = oy;
	bool   isAnything;
	int    sphereCount = 0, sphereCountTemp;
	int    dirSide1 = (dir - 1) & 3, dirSide2 = (dir + 1) & 3;

	if (PlayerDwordC0)
		return true;

	// Right
	while (true) {
		x = (x + SCD_X[dir]) & 0x1F;
		y = (y + SCD_Y[dir]) & 0x1F;

		if ((*LayoutAt(x, y) & 0x7F) != SPHERE_RED)
			break;

		if (*LayoutBackupAt(x, y) == 1)
			break;

		if (HasAllNonBlueNeighbors(x, y))
			break;

		sphereCountTemp = sphereCount + 1;
		*LayoutExtraAt(x, y) = 1;
		*LayoutBackupAt(x, y) = 1;

		if (x == PlayerLastTouchedObjectX && y == PlayerLastTouchedObjectY) {
			PlayerDwordC0 = true;
			return true;
		}

		isAnything = false;
		if ((*LayoutAt(x + SCD_X[dirSide1], y + SCD_Y[dirSide1]) & 0x7F) == SPHERE_RED)
			isAnything |= SphereCheckDirection(x, y, dirSide1);
		if ((*LayoutAt(x + SCD_X[dirSide2], y + SCD_Y[dirSide2]) & 0x7F) == SPHERE_RED)
			isAnything |= SphereCheckDirection(x, y, dirSide2);

		sphereCount = 0;
		if (!isAnything)
			sphereCount = sphereCountTemp;

		if (PlayerDwordC0)
			return true;
	}
	while (sphereCount > 0) {
		x = (x - SCD_X[dir]) & 0x1F;
		y = (y - SCD_Y[dir]) & 0x1F;
		*LayoutExtraAt(x, y) = 0;
		sphereCount--;
	}
	return false;
}

PUBLIC bool Level_SpecialStage::SphereCheckUp(int ox, int oy) {
	int    dataStartX = ox;
	int    dataStartY = oy;
	bool   isAnything;
	int    sphereCount = 0, sphereCountTemp;

	if (PlayerDwordC0)
		return true;

	for (int i = ox; ; dataStartX = i) {
		dataStartY = (dataStartY - 1) & 0x1F;

		if ((*LayoutAt(dataStartX, dataStartY) & 0x7F) != SPHERE_RED)
			break;

		if (*LayoutBackupAt(dataStartX, dataStartY) == 1)
			break;

		if (HasAllNonBlueNeighbors(ox, dataStartY)) {
			dataStartX = i;
			break;
		}

		sphereCountTemp = sphereCount + 1;
		*LayoutExtraAt(i, dataStartY) = 1;
		*LayoutBackupAt(dataStartX, dataStartY) = 1;

		if (ox == PlayerLastTouchedObjectX && dataStartY == PlayerLastTouchedObjectY) {
			PlayerDwordC0 = true;
			return true;
		}

		isAnything = false;
		if ((*LayoutAt((ox + 1) & 0x1F, dataStartY) & 0x7F) == SPHERE_RED)
			isAnything |= SphereCheckRight(ox, dataStartY);
		if ((*LayoutAt((ox - 1) & 0x1F, dataStartY) & 0x7F) == SPHERE_RED)
			isAnything |= SphereCheckLeft(ox, dataStartY);

		sphereCount = 0;
		if (!isAnything)
			sphereCount = sphereCountTemp;

		if (PlayerDwordC0)
			return true;
	}
	while (sphereCount > 0) {
		dataStartY = (dataStartY + 1) & 0x1F;
		*LayoutExtraAt(dataStartX, dataStartY) = 0;
		sphereCount--;
	}
	return false;
}
PUBLIC bool Level_SpecialStage::SphereCheckDown(int ox, int oy) {
	int    dataStartX = ox;
	int    dataStartY = oy;
	bool   isAnything;
	int    sphereCount = 0, sphereCountTemp;

	if (PlayerDwordC0)
		return true;

	for (int i = ox; ; dataStartX = i) {
		dataStartY = (dataStartY + 1) & 0x1F;

		if ((*LayoutAt(dataStartX, dataStartY) & 0x7F) != SPHERE_RED)
			break;

		if (*LayoutBackupAt(dataStartX, dataStartY) == 1)
			break;

		if (HasAllNonBlueNeighbors(ox, dataStartY)) {
			dataStartX = i;
			break;
		}

		sphereCountTemp = sphereCount + 1;
		*LayoutExtraAt(i, dataStartY) = 1;
		*LayoutBackupAt(dataStartX, dataStartY) = 1;

		if (ox == PlayerLastTouchedObjectX && dataStartY == PlayerLastTouchedObjectY) {
			PlayerDwordC0 = true;
			return true;
		}

		isAnything = false;
		if ((*LayoutAt((ox - 1) & 0x1F, dataStartY) & 0x7F) == SPHERE_RED)
			isAnything |= SphereCheckLeft(ox, dataStartY);
		if ((*LayoutAt((ox + 1) & 0x1F, dataStartY) & 0x7F) == SPHERE_RED)
			isAnything |= SphereCheckRight(ox, dataStartY);

		sphereCount = 0;
		if (!isAnything)
			sphereCount = sphereCountTemp;

		if (PlayerDwordC0)
			return true;
	}
	while (sphereCount > 0) {
		dataStartY = (dataStartY - 1) & 0x1F;
		*LayoutExtraAt(dataStartX, dataStartY) = 0;
		sphereCount--;
	}
	return false;
}
PUBLIC bool Level_SpecialStage::SphereCheckLeft(int ox, int oy) {
	int    dataStartX = ox;
	int    dataStartY = oy;
	bool   isAnything;
	int    sphereCount = 0, sphereCountTemp;

	if (PlayerDwordC0)
		return true;

	for (;;) {
		dataStartX = (dataStartX - 1) & 0x1F;

		if ((*LayoutAt(dataStartX, dataStartY) & 0x7F) != SPHERE_RED)
			break;

		if (*LayoutBackupAt(dataStartX, dataStartY) == 1)
			break;

		if (HasAllNonBlueNeighbors(dataStartX, oy)) {
			dataStartY = oy;
			break;
		}

		sphereCountTemp = sphereCount + 1;
		*LayoutExtraAt(dataStartX, oy) = 1;
		*LayoutBackupAt(dataStartX, oy) = 1;

		if (dataStartX == PlayerLastTouchedObjectX && oy == PlayerLastTouchedObjectY) {
			PlayerDwordC0 = true;
			return true;
		}

		isAnything = false;
		if ((*LayoutAt(dataStartX, oy - 1) & 0x7F) == SPHERE_RED)
			isAnything |= SphereCheckUp(dataStartX, oy);
		if ((*LayoutAt(dataStartX, oy + 1) & 0x7F) == SPHERE_RED)
			isAnything |= SphereCheckDown(ox, dataStartY);

		sphereCount = 0;
		if (!isAnything)
			sphereCount = sphereCountTemp;

		if (PlayerDwordC0)
			return true;
	}
	while (sphereCount > 0) {
		dataStartX = (dataStartX + 1) & 0x1F;
		*LayoutExtraAt(dataStartX, dataStartY) = 0;
		sphereCount--;
	}
	return false;
}
PUBLIC bool Level_SpecialStage::SphereCheckRight(int ox, int oy) {
	int    dataStartX = ox;
	int    dataStartY = oy;
	bool   isAnything;
	int    sphereCount = 0, sphereCountTemp;

	if (PlayerDwordC0)
		return true;

	for (;;) {
		dataStartX = (dataStartX + 1) & 0x1F;

		if ((*LayoutAt(dataStartX, dataStartY) & 0x7F) != SPHERE_RED)
			break;

		if (*LayoutBackupAt(dataStartX, dataStartY) == 1)
			break;

		if (HasAllNonBlueNeighbors(dataStartX, oy)) {
			dataStartY = oy;
			break;
		}

		sphereCountTemp = sphereCount + 1;
		*LayoutExtraAt(dataStartX, oy) = 1;
		*LayoutBackupAt(dataStartX, oy) = 1;

		if (dataStartX == PlayerLastTouchedObjectX && oy == PlayerLastTouchedObjectY) {
			PlayerDwordC0 = true;
			return true;
		}

		isAnything = false;
		if ((*LayoutAt(dataStartX, oy + 1) & 0x7F) == SPHERE_RED)
			isAnything |= SphereCheckDown(ox, dataStartY);
		if ((*LayoutAt(dataStartX, oy - 1) & 0x7F) == SPHERE_RED)
			isAnything |= SphereCheckUp(dataStartX, oy);

		sphereCount = 0;
		if (!isAnything)
			sphereCount = sphereCountTemp;

		if (PlayerDwordC0)
			return true;
	}
	while (sphereCount > 0) {
		dataStartX = (dataStartX - 1) & 0x1F;
		*LayoutExtraAt(dataStartX, dataStartY) = 0;
		sphereCount--;
	}
	return false;
}

PUBLIC int Level_SpecialStage::SomethingUsefulMaybe(int ox, int oy) {
	int sX, sY;

	sX = ox;
	sY = (oy - 1) & 0x1F;
	for (int i = 0; i < 32; i++) {
		if (*LayoutExtraAt(sX, sY) == 1)
			break;

		int sphere = *LayoutAt(sX, sY) & 0x7F;
		if (!sphere || sphere == SPHERE_RED)
			return 0;

		sY = (sY - 1) & 0x1F;
	}

	sX = ox;
	sY = (oy + 1) & 0x1F;
	for (int i = 0; i < 32; i++) {
		if (*LayoutExtraAt(sX, sY) == 1)
			break;

		int sphere = *LayoutAt(sX, sY) & 0x7F;
		if (!sphere || sphere == SPHERE_RED)
			return 0;

		sY = (sY + 1) & 0x1F;
	}

	sX = (ox - 1) & 0x1F;
	sY = oy;
	for (int i = 0; i < 32; i++) {
		if (*LayoutExtraAt(sX, sY) == 1)
			break;

		int sphere = *LayoutAt(sX, sY) & 0x7F;
		if (!sphere || sphere == SPHERE_RED)
			return 0;

		sX = (sX - 1) & 0x1F;
	}

	sX = (ox + 1) & 0x1F;
	sY = oy;
	for (int i = 0; i < 32; i++) {
		if (*LayoutExtraAt(sX, sY) == 1)
			break;

		int sphere = *LayoutAt(sX, sY) & 0x7F;
		if (!sphere || sphere == SPHERE_RED)
			return 0;

		sX = (sX + 1) & 0x1F;
	}

	*LayoutExtraAt(ox, oy) = 1;
	return 1;
}

PUBLIC bool Level_SpecialStage::CheckSurround() {
	memset(LayoutBackup, 0, 0x400);
	memset(LayoutExtra, 0, 0x400);
	*LayoutAt(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY) = SPHERE_RED;
	*LayoutExtraAt(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY) = 1;

	PlayerDwordC0 = false;

	SphereCheckDirection(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY, 1); // Up
	SphereCheckDirection(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY, 3); // Down
	SphereCheckDirection(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY, 0); // Left
	SphereCheckDirection(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY, 2); // Right

	*LayoutAt(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY) = SPHERE_BLUE;
	if (PlayerDwordC0 != 1)
		return false;

	int v7 = 0;
	int v29 = 0;
	for (int sx = 0; sx < 32; sx++) {
		for (int sy = 0; sy < 32; sy++) {
			if ((*LayoutAt(sx, sy) & 0x7F) == SPHERE_BLUE) {
				int v12 = SomethingUsefulMaybe(sx, sy);
				v29 += v12;
				v7 = v29;
			}
		}
	}

	if (v7 <= 0) {
		PlayerDwordC0 = false;
		return false;
	}

	for (int sy = 0; sy < 32; sy++) {
		for (int sx = 0; sx < 32; sx++) {
			if (*LayoutExtraAt(sx, sy) == 1)
				if (HasAllNonBlueNeighbors(sx, sy))
					*LayoutExtraAt(sx, sy) = 0;
		}
	}

	for (int sx = 0; sx < 32; sx++) {
		for (int sy = 0; sy < 32; sy++) {
			if (*LayoutExtraAt(sx, sy) == 1)
				*LayoutAt(sx, sy) = SPHERE_RING;
		}
	}

	BallCount -= v29;
	Sound::Play(Sound::SFX_RINGLOSS);

	return false;
}

PUBLIC void Level_SpecialStage::DoCustomFadeAction() {
	if (ZoneID >= 0x100) {
		int Acto = ZoneID & 0xF;
		switch (SaveGame::CurrentZoneID) {
			case 0:
				App->NextScene = new Level_AIZ(App, G, Acto);
				break;
			case 1:
				App->NextScene = new Level_HCZ(App, G, Acto);
				break;
			case 2:
				App->NextScene = new Level_MGZ(App, G, Acto);
				break;
			case 3:
				App->NextScene = new Level_CNZ(App, G, Acto);
				break;
			case 4:
				App->NextScene = new Level_ICZ(App, G, Acto);
				break;
			case 5:
				App->NextScene = new Level_LBZ(App, G, Acto);
				break;
			case 6:
				App->NextScene = new Level_MHZ(App, G, Acto);
				break;
			case 7:
				App->NextScene = new Level_FBZ(App, G, Acto);
				break;
			case 8:
				App->NextScene = new Level_SOZ(App, G, Acto);
				break;
			case 9:
				App->NextScene = new Level_LRZ(App, G, Acto);
				break;
			case 10:
				App->NextScene = new Level_HPZ(App, G, Acto);
				break;
			case 11:
				App->NextScene = new Level_SSZ(App, G, Acto);
				break;
			case 12:
				App->NextScene = new Level_DEZ(App, G, Acto);
				break;
			case 13: //dont know why this would ever happen but lets put it here anyway
				App->NextScene = new Level_TDZ(App, G, Acto);
				break;
			default:
				App->NextScene = new Scene_MainMenu(App, G);
		}
		return;
	}

	App->NextScene = new Scene_MainMenu(App, G);
}
PUBLIC void Level_SpecialStage::EarlyUpdate() {
	if (LevelCardTimer >= 1.5) LevelCardTimer = 6.0;

	if (GameState == 1) { // Stepped on a Red
		PlayerAngle = (PlayerAngle + 0x800) & 0xFFFF;
		DirectionStep += 2;
		if (DirectionStep > 0xF)
			ColorFlip = !ColorFlip;
		DirectionStep &= 0xF;
		Direction = 1;
		return;
	}
	if (GameState == 2 || GameState == 3) { // Completed
		if (SpeedupTimerMax > 0x80) {
			SpeedupTimerMax = 0; // Reset and reuse SpeedupTimerMax because lazy
		}

		PlayerSteps += PlayerSpeed;
		if (PlayerSteps >= 0x100) {
			PlayerSteps -= 0x100;
			if (Direction != 0)
				PlayerSteps = 0;
			PlayerX = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			PlayerY = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			ColorFlip = !ColorFlip;
		}
		if (PlayerSteps <  0x0) {
			PlayerSteps += 0x100;
			PlayerX = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			PlayerY = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			ColorFlip = !ColorFlip;
		}
		PlayerZSpeed += PlayerMaxSpeed << 12;
		PlayerZ += PlayerZSpeed;
		if (PlayerZ > 0)
			PlayerZ = PlayerZSpeed = 0;

		if (GameState == 2) {
			if (++SpeedupTimerMax >= 0x80) {
				SpeedupTimerMax = 0;
				PlayerSpeed = 8;
				PlayerMaxSpeed = 8;
				PlayerIsMovingBackwards = false;
				GameState = 3;
				memset(Layout, 0, 0x400);

				int ThingX = (PlayerX + IMath::sign(-IMath::sinHex(PlayerAngle >> 8)) * 8) & 0x1F;
				int ThingY = (PlayerY + IMath::sign(-IMath::cosHex(PlayerAngle >> 8)) * 8) & 0x1F;

				*LayoutAt(ThingX, ThingY) = SPHERE_EMERALD;
			}
		}
		else if (GameState == 3) {
			if (++SpeedupTimerMax == 0x78) {
				// SpeedupTimerMax = 0;
				// PlayerSpeed = 8;
				// PlayerMaxSpeed = 8;
				Sound::Play(Sound::SFX_EMERALD);
			}

			int XIndex = PlayerX;
			int YIndex = PlayerY;
			if (!PlayerIsMovingBackwards) {
				XIndex = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8))) + 0x20) & 0x1F;
				YIndex = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8))) + 0x20) & 0x1F;
			}

			if (*LayoutAt(XIndex, YIndex) == SPHERE_EMERALD) {
				if ((PlayerIsMovingBackwards && PlayerSteps < 0x10) ||
					(!PlayerIsMovingBackwards && PlayerSteps > 0xF0)) {
					PlayerSteps = 0x00;
					if (!PlayerIsMovingBackwards) {
						ColorFlip = !ColorFlip;
						PlayerX = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8))) + 0x20) & 0x1F;
						PlayerY = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8))) + 0x20) & 0x1F;
					}

					FadeAction = FadeActionType::CUSTOM_FADE_ACTION;
					FadeTimer = -1;
					FadeTimerMax = 64 + 48;
					FadeMax = 0x100 + 0xC0;
					G->FadeToWhite = false;
					Sound::Play(Sound::SFX_SPECIALSTAGE_EXIT);
					GameState = 1;
				}
			}

		}

		return;
	}

	if (PlayerMaxSpeed < 32) {
		SpeedupTimer++;
		if (SpeedupTimer >= SpeedupTimerMax) {
			SpeedupTimer = 0;

			PlayerMaxSpeed += 4;
		}
	}

	if (PlayerIsMovingBackwards) {
		if (!PlayerIsMoveForwardLocked && App->Input->GetControllerInput(0)[IInput::I_UP])
			PlayerIsMovingBackwards = false;
	}
	else {
		if (PlayerSpeed < PlayerMaxSpeed)
			PlayerSpeed += PlayerAccelerationRate;
	}

	if ((PlayerAngle & 0x3FFF) == 0 && PlayerWaitMovementTimer == 0) {
		PlayerSteps = PlayerSteps + PlayerSpeed;

		if (PlayerSteps >= 0x100) {
			PlayerSteps -= 0x100;
			if (Direction != 0)
				PlayerSteps = 0;
			PlayerX = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			PlayerY = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			ColorFlip = !ColorFlip;
		}
		if (PlayerSteps <  0x0) {
			PlayerSteps += 0x100;
			PlayerX = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			PlayerY = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			ColorFlip = !ColorFlip;
		}
	}

	if (PlayerSteps < 0x20)
		PlayerIsMoveForwardLocked = false;
	if (PlayerSteps > 0xE0)
		PlayerIsMoveForwardLocked = false;

    int XIndex = PlayerX;
    int YIndex = PlayerY;
	if (!PlayerIsMovingBackwards) {
		XIndex = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8))) + 0x20) & 0x1F;
		YIndex = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8))) + 0x20) & 0x1F;
	}

	if (PlayerZ == 0) {
		if (*LayoutAt(XIndex, YIndex) == SPHERE_RED) {
			if ((PlayerIsMovingBackwards && PlayerSteps < 0x20) ||
				(!PlayerIsMovingBackwards && PlayerSteps > 0xE0)) {
				PlayerLastTouchedObjectX = XIndex;
				PlayerLastTouchedObjectY = YIndex;
				PlayerSteps = 0x00;
				if (!PlayerIsMovingBackwards) {
					ColorFlip = !ColorFlip;
					PlayerX = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8))) + 0x20) & 0x1F;
					PlayerY = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8))) + 0x20) & 0x1F;
				}
				DirectionStep = 0;
				GameState = 1;
				// player->FuncMainMovement = sub_49BF30;
				FadeAction = FadeActionType::CUSTOM_FADE_ACTION;
				FadeTimer = -1;
				FadeTimerMax = 64 + 48;
				FadeMax = 0x100 + 0xC0;
				G->FadeToWhite = false;
				Sound::Play(Sound::SFX_SPECIALSTAGE_EXIT);
				App->Audio->FadeMusic(1.0);
			}
		}
		else if (*LayoutAt(XIndex, YIndex) == (0x80 | SPHERE_RED)) {
			/*if ((PlayerIsMovingBackwards && PlayerSteps > 0x20) ||
				(!PlayerIsMovingBackwards && PlayerSteps < 0xE0)) {
				PlayerLastTouchedObjectX = XIndex;
				PlayerLastTouchedObjectY = YIndex;
				*LayoutAt(XIndex, YIndex) = SPHERE_RED;
			}*/
		}
		else if (*LayoutAt(XIndex, YIndex) == SPHERE_BLUE) {
			if ((PlayerIsMovingBackwards && PlayerSteps < 0x80) ||
				(!PlayerIsMovingBackwards && PlayerSteps > 0x80)) {
				PlayerLastTouchedObjectX = XIndex;
				PlayerLastTouchedObjectY = YIndex;
				CheckSurround();
				BallCount--;
				if (!PlayerDwordC0) {
					*LayoutAt(XIndex, YIndex) = 0x80 | SPHERE_RED;
				}
				if (BallCount <= 0) {
					BallCount = 0;
					GameState = 2; // 2
					SaveGame::SetEmerald(Act);
					SaveGame::Flush();
					Sound::Play(Sound::SFX_SPECIALSTAGE_FLYAWAY);
					App->Audio->FadeMusic(1.0);
				}
				else {
					Sound::Play(Sound::SFX_BLUEBALL);
				}
			}
		}
		else if (*LayoutAt(XIndex, YIndex) == SPHERE_BUMPER) {
			if (PlayerIsMoveForwardLocked)
				goto RETURN;

			bool go = false;
			if (PlayerIsMovingBackwards)  {
				if (PlayerSteps < 0x70) {
					if (PlayerSteps > 0x10 && PlayerSpeed < 0) {
						go = true;
					}
					else if (Direction == 0 && PlayerSpeed < 0) {
						PlayerSteps = 0x10;
						go = true;
					}
				}
			}
			else {
				if (PlayerSteps > 0x90) {
					if (PlayerSteps >= 0xF0) {
						if (Direction == 0 && PlayerSpeed > 0) {
							PlayerSteps = 0xF0;
							go = true;
						}
					}
					else {
						if (PlayerSpeed > 0) {
							go = true;
						}
					}
				}
			}

			if (go) {
				PlayerIsMoveForwardLocked = true;
				PlayerSpeed = -PlayerSpeed;
				PlayerIsMovingBackwards = !PlayerIsMovingBackwards;
				Sound::Play(Sound::SFX_BUMPER);
			}
		}
		else if (*LayoutAt(XIndex, YIndex) == SPHERE_YELLOW) {
			if ((PlayerIsMovingBackwards && PlayerSteps < 0x80) ||
				(!PlayerIsMovingBackwards && PlayerSteps > 0x80)) {

				PlayerZSpeed = -0x180000;
				PlayerSpeed *= 2;
				Direction = 0;
				PlayerAccelerationRate = 4;
				Sound::Play(Sound::SFX_SPRING);
			}
		}
		else if (*LayoutAt(XIndex, YIndex) == SPHERE_RING) {
			if ((PlayerIsMovingBackwards && PlayerSteps < 0x80) ||
				(!PlayerIsMovingBackwards && PlayerSteps > 0x80)) {

				RingCount++;
				Sound::Play(Sound::SFX_RING);

				*LayoutAt(XIndex, YIndex) = 0;
			}
		}
	} RETURN:

    if (Direction == 0) {
        if (App->Input->GetControllerInput(0)[IInput::I_LEFT]) {
            Direction = 1;
        }
        if (App->Input->GetControllerInput(0)[IInput::I_RIGHT]) {
            Direction = -1;
        }
    }

	if (PlayerWaitMovementTimer > 0) {
		PlayerWaitMovementTimer--;
		if (App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED]) {
			PlayerWaitMovementTimer = 0;
		}
	}

	if (PlayerZ == 0 && (PlayerAngle & 0x3FFF) == 0 && App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED]) {
		PlayerZSpeed = -0x100000;

		Sound::Play(Sound::SFX_JUMP);
	}
	PlayerZSpeed += PlayerMaxSpeed << 12;
	PlayerZ += PlayerZSpeed;
	if (PlayerZ > 0)
		PlayerZ = PlayerZSpeed = 0;

    if ((PlayerSteps & 0xF0) == 0 && Direction != 0) {
        if (DirectionStep == 0) {
            StoredAngle = PlayerAngle >> 12;

			if (Direction < 0)
				ColorFlip = !ColorFlip;

			PlayerSteps = 0;
        }
        if (Direction > 0) {
            PlayerAngle = (PlayerAngle + 0x400) & 0xFFFF;
            DirectionStep++;
        }
        else {
            PlayerAngle = (PlayerAngle + 0xFC00) & 0xFFFF;
            DirectionStep++;
        }
        if ((PlayerAngle & 0xC000) == PlayerAngle) {
			if (Direction > 0)
				ColorFlip = !ColorFlip;
            Direction = 0;
            DirectionStep = 0;
        }
    }
}
PUBLIC void Level_SpecialStage::Subupdate() {

}
PUBLIC void Level_SpecialStage::HandleCamera() {

}

PUBLIC void Level_SpecialStage::RenderEverything() {
	G->DrawRectangle(0, 0, App->WIDTH, 128, ColorBG);

    if (DirectionStep == 0) {
        int t = PlayerSteps >> 4;
        for (int i = 0; i < 16; i++) {
            Globe->SetPalette(1  + i, (t > i) ^ ColorFlip ? Color1 : Color2);
            Globe->SetPalette(17 + i, (t > i) ^ ColorFlip ? Color2 : Color1);
        }
		Globe->UpdatePalette();

        G->DrawSprite(Globe, 0, 0, App->WIDTH / 2, 0, 0, IE_NOFLIP);
    }
    else {
		GlobeSpin->SetPalette(128, ColorFlip ? Color1 : Color2);
		GlobeSpin->SetPalette(144, ColorFlip ? Color2 : Color1);
		GlobeSpin->UpdatePalette();

        bool fl = false;
        int fr = DirectionStep - 1;
		if (Direction < 0)
			fr = fr ^ 0xF;

        if (fr >= 8) {
            fr = 6 - (fr - 8);
			if (fr < 0) fr = 0;
            fl = true;
        }

        G->DrawSprite(GlobeSpin, 0, fr,
            App->WIDTH / 2, 0, 0, fl ? IE_FLIPX : IE_NOFLIP);
    }

	/*
	G->SetDrawFunc(1);
	// Sky
	G->SetDrawAlpha(ColorSky);
    G->DrawSprite(Horizon, 0, 1, App->WIDTH / 2, 0, 0, IE_NOFLIP);
    G->DrawSprite(Horizon, 0, 1, App->WIDTH / 2, 0, 0, IE_FLIPX);
	// Globe
    G->SetDrawAlpha(ColorGlobe);
    G->DrawSprite(Horizon, 0, 0, App->WIDTH / 2, 0, 0, IE_NOFLIP);
    G->DrawSprite(Horizon, 0, 0, App->WIDTH / 2, 0, 0, IE_FLIPX);
    G->SetDrawFunc(0);
    G->SetDrawAlpha(0xFF);
	//*/

    // Draw spheres
    int sh[9] = { -4, 4, -3, 3, -2, 2, -1, 1, 0 };
    for (int s = 0; s < 9; s++) {
		int c = sh[s];
		for (int i = -7; i < 7; i++) {
			int j = i;

			int dwordA4 = 0;
			int dwordA8 = 0;
			int playerAngleMode = PlayerAngle >> 14;
			switch (playerAngleMode) {
				case 0:
					dwordA4 = c;
					dwordA8 = j;
					break;
				case 1:
					dwordA4 = -j;
					dwordA8 = c;
					break;
				case 2:
					dwordA4 = c;
					dwordA8 = -j;
					break;
				case 3:
					dwordA4 = j;
					dwordA8 = c;
					break;
				default:
					break;
			}

			int StepsOff = 7;
			if (IMath::sinHex((PlayerAngle >> 14) << 6) + IMath::cosHex((PlayerAngle >> 14) << 6) < 0)
				StepsOff = 8;
			StepsOff = 0;
			int RoundedX = PlayerX;
			int RoundedY = PlayerY;
			int TilePosition = ((PlayerSteps >> 4) + StepsOff) & 0xF;

			int needsResize = 0;
			bool transparent = false;
			int collectableType = *LayoutAt((dwordA4 + RoundedX + 0x20) & 0x1F, (dwordA8 + RoundedY + 0x20) & 0x1F);
			if (collectableType == (0x80 | SPHERE_RED)) {
				// transparent = true;
				collectableType  &= 0x7F;
			}

			if (collectableType == SPHERE_RED)
				collectableType = 5;
			else if (collectableType == SPHERE_BLUE)
				collectableType = 4;
			else if (collectableType == SPHERE_BUMPER)
				collectableType = 6;
			else if (collectableType == SPHERE_YELLOW)
				collectableType = 7;
			else if (collectableType == SPHERE_RING)
				needsResize = collectableType = 12;
			else if (collectableType == SPHERE_EMERALD)
				collectableType = 11;

			if (transparent)
				G->SetDrawAlpha(0x80);
			else
				G->SetDrawAlpha(0xFF);

			if (collectableType) {
				int downPos, v20;
				int finalPosX = 0;
				int finalPosY = 0;
				int frameAtPosition = 5;

				finalPosX = (dwordA4 * -IMath::cosHex(PlayerAngle >> 8) + dwordA8 * IMath::sinHex(PlayerAngle >> 8)) >> 12;
				finalPosY = (dwordA4 * IMath::sinHex(PlayerAngle >> 8) + dwordA8 * IMath::cosHex(PlayerAngle >> 8)) >> 12;
				finalPosY = -finalPosY - TilePosition + 16 + StepsOff;

				if (finalPosY < 0) continue;
				if (finalPosY >= 0x70) continue;

				frameAtPosition = IMath::max(MapThing[5][finalPosY + 1] - (IMath::abs(finalPosX) >> 5), 0);

				if (collectableType == 10 || collectableType == 11)
					frameAtPosition >>= 1;

				finalPosX = MapThing[4][finalPosY + 1] * finalPosX;

				v20 = 0;
				downPos = finalPosX * finalPosX >> 16;
				if (finalPosX <= 0)
					v20 = downPos + finalPosX;
				else
					v20 = finalPosX - downPos;
				finalPosX = v20 >> 4;

				// v3 = (finalPosX * finalPosX) % MapThing[3][i + 1];
				finalPosY = MapThing[2][finalPosY + 1] + (finalPosX * finalPosX) / MapThing[3][finalPosY + 1];

				finalPosX += App->WIDTH / 2;

				// 0xE4  = 2 (Count: 70)    On-screen Y
				// 0x2A4 = 3 (Count: 70)    Divisor
				// 0x464 = 4 (Count: 70)    X Multiplier
				// 0x624 = 5 (Count: 80)    Frame at position

				if (needsResize) {
					int frm = RingAnimationFrame >> 10;
					if (SaveGame::CurrentMode == 1)
						frm = RingAnimationFrame >> 8;

					ISprite::AnimFrame animframe = ItemsSprite->Animations[collectableType].Frames[frm];
					int w = animframe.W * frameAtPosition / 0x28; // / 0x20
					int h = animframe.H * frameAtPosition / 0x28;

					G->DrawSpriteSized(ItemsSprite, collectableType, frm,
						finalPosX - animframe.OffX - w / 2,
						finalPosY - animframe.OffY - h * 22 / 32 - h / 8,
						0,
						IE_NOFLIP, w, h);
				}
				else {
					G->DrawSprite(Objects, collectableType, frameAtPosition,
						finalPosX,
						finalPosY,
						0,
						IE_NOFLIP);
				}
			}
		}
	}

	if (!IApp::Mobile) {
		char poop[40];
		sprintf(poop, "Player Angle: %X", PlayerAngle);
		G->DrawTextShadow(4, App->HEIGHT - 45 + 4, poop, 0xFFFFFF);

		sprintf(poop, "Player X: %X", PlayerX);
		G->DrawTextShadow(4, App->HEIGHT - 45 + 14, poop, 0xFFFFFF);

		sprintf(poop, "Player Y: %X", PlayerY);
		G->DrawTextShadow(4, App->HEIGHT - 45 + 24, poop, 0xFFFFFF);

		sprintf(poop, "Player Steps: %X", PlayerSteps);
		G->DrawTextShadow(4, App->HEIGHT - 45 + 34, poop, 0xFFFFFF);
	}

    // Player
    G->SetDrawAlpha(0x80);
    G->DrawSprite(GlobeSpin, 1, 0, App->WIDTH / 2, 0xA0, 0, IE_NOFLIP);
    G->SetDrawAlpha(0xFF);

	if (PlayerZ == 0) {
		if (PlayerMaxSpeed == 0 || PlayerWaitMovementTimer != 0)
			G->DrawSprite(Players, 0, 0, App->WIDTH / 2, 0xAA, 0, IE_NOFLIP);
		else
			G->DrawSprite(Players, 1, ((Frame * IMath::sign(PlayerSpeed) / 2) % 12 + 12) % 12, App->WIDTH / 2, 0xAA, 0, IE_NOFLIP);
	}
	else {
		G->DrawSprite(Players, 2, ((Frame * IMath::max(16, IMath::abs(PlayerSpeed)) / 32) % 12 + 12) % 12, App->WIDTH / 2, 0xAA + (PlayerZ >> 17), 0, IE_NOFLIP);
	}

    ///*

	int nn, n;
    // Blue Sphere Count
    G->DrawSprite(Objects, 0, 0, App->WIDTH / 2 - Objects->Animations[0].Frames[0].W - 64, 13, 0, IE_NOFLIP);
    // Number
    n = BallCount;
    for (int i = 2; i >= 0; i--) {
        nn = n % 10;
		n /= 10;
        G->DrawSprite(Objects, 1, nn, App->WIDTH / 2 - 136 + 16 * i, 17, 0, IE_NOFLIP);
    }

    // Ring Count
    G->DrawSprite(Objects, 0, 1, App->WIDTH / 2 + 64, 13, 0, IE_NOFLIP);
    // Number
	n = PerfectAmount - RingCount;
	if (n < 0) n = 0;
	for (int i = 2; i >= 0; i--) {
		nn = n % 10;
		n /= 10;
		G->DrawSprite(Objects, 1, nn, App->WIDTH / 2 + 88 + 16 * i, 17, 0, IE_NOFLIP);
    }



    //*/

	App->Input->UseTouchController = true;
	App->Input->CenterPauseButton = true;
	if (IApp::Mobile) {
		G->SetDrawAlpha(0xC0 - (0xC0 * ControlsAnim >> 8));
		int bX = 48;
		int bY = App->HEIGHT - 48;
		if (App->Input->GetControllerInput(0)[IInput::I_UP])
			G->DrawSprite(MobileButtonsSprite, 0, 1, bX, bY, 0, IE_NOFLIP);
		else if (App->Input->GetControllerInput(0)[IInput::I_DOWN])
			G->DrawSprite(MobileButtonsSprite, 0, 2, bX, bY, 0, IE_NOFLIP);
		else if (App->Input->GetControllerInput(0)[IInput::I_LEFT])
			G->DrawSprite(MobileButtonsSprite, 0, 3, bX, bY, 0, IE_FLIPX);
		else if (App->Input->GetControllerInput(0)[IInput::I_RIGHT])
			G->DrawSprite(MobileButtonsSprite, 0, 3, bX, bY, 0, IE_NOFLIP);
		else
			G->DrawSprite(MobileButtonsSprite, 0, 0, bX, bY, 0, IE_NOFLIP);

		// A button
		if (App->Input->GetControllerInput(0)[IInput::I_CONFIRM])
			G->SetDrawAlpha(0xFF);

		G->DrawSprite(MobileButtonsSprite, 0, 4, App->WIDTH - 48, bY, 0, IE_NOFLIP);
		G->SetDrawAlpha(0xFF);

		// Pause
		G->DrawSprite(MobileButtonsSprite, 0, 5, App->WIDTH / 2, 22, 0, IE_NOFLIP);
	}
}
