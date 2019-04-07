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

	int playFieldLayerID;
	int ringCountLayerID;
	int backgroundLayerID;
	int globeLayerID;

	int StartMessageAnim;
	int PerfectMessageAnim;
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
int PlayerLastX = 0x0000;
int PlayerLastY = 0x0000;
int PlayerLastTouchedObjectX = 0x0000;
int PlayerLastTouchedObjectY = 0x0000;
int PlayerSteps = 0;
int StoredAngle = 0x0;

int PlayerDwordC0 = 0;
int PlayerMaxSpeed = 16;
int PlayerSpeed = 16;
int PlayerLastSpeed = 16;
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

bool ColourFlip = true;

int GameState = 0;

int BGScrollValue = 0;

Uint8* LayoutBackup = NULL;
Uint8* LayoutExtra = NULL;

int* PinkSphereX;
int* PinkSphereY;
int PinkSphereCount;

//Multi-use misc shit
int Timer1 = 0;
int Timer2 = 0;

enum {
	BSS_SPHERE_RED = 2,
	BSS_SPHERE_BLUE = 1,
	BSS_SPHERE_BUMPER = 3,
	BSS_SPHERE_RING = 7,
	BSS_SPHERE_YELLOW = 4,
	BSS_SPHERE_GREEN = 5,
	BSS_SPHERE_PINK = 6,
	BSS_SPHERE_EMERALD = 0x10,
	BSS_PLAYER_ANGLE_0 = 8,
	BSS_PLAYER_ANGLE_90 = 9,
	BSS_PLAYER_ANGLE_180 = 10,
	BSS_PLAYER_ANGLE_270 = 11,
};

enum {
	BSS_EVENT_NONE,
	BSS_EVENT_START,
	BSS_EVENT_PERFECT,
	BSS_EVENT_RESULTS,
};

bool useStageConfig = true;
Uint32 PaletteID = 0;
Uint8 SkyAlpha = 96;
Uint8 GlobeAlpha = 80;
Uint32 BGColour = 0x0044EE; // 'BGColour1'
Uint32 BGStarColour1 = 0x00; // 'BGColour2'
Uint32 BGStarColour2 = 0x00; // 'BGColour3'
Uint32 playFieldColourA = 0xEE8800;
Uint32 playFieldColourB = 0x662200;

int EventFlag = BSS_EVENT_START;

Sint32 MapThing[0x10][0x100];
int DropDash = -2;
int DropDashY = 0;
bool HitBlue = false;

PUBLIC Level_SpecialStage::Level_SpecialStage(IApp* app, IGraphics* g) : LevelScene(app, g) {
    ZoneID = 20;
    Act = 0;

	if (!LayoutBackup)
		LayoutBackup = (Uint8*)calloc(0x400, 1);

	if (!LayoutExtra)
		LayoutExtra = (Uint8*)calloc(0x400, 1);

    /*Globe = new ISprite("Special/Globe.gif", App);
	ISprite::Animation an;
	an.Name = "";
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
	Globe->Animations.push_back(an);*/

    GlobeSpin = new ISprite("Special/GlobeSpin.gif", App);
    GlobeSpin->LoadAnimation("Special/GlobeSpin.bin");

    Horizon = new ISprite("Special/Horizon.gif", App);
    Horizon->LoadAnimation("Special/Horizon.bin");

    Objects = new ISprite("Special/Objects.gif", App);
    Objects->LoadAnimation("Special/HUD.bin");
    Objects->LoadAnimation("Special/StageObjects.bin");
    Objects->LoadAnimation("Special/PaletteIcon.bin");

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
	Players->SetTransparentColorIndex(0x0);

	StartMessageAnim = Objects->FindAnimation("Start Message");
	PerfectMessageAnim = Objects->FindAnimation("Perfect Message");
}

PUBLIC void Level_SpecialStage::LoadStage() {
	if (SaveGame::CurrentMode >= 1)
	{
		Str_TileConfigBin = "Mixed/Stages/Special/Tileconfig.bin";
		Str_StageBin = "Mixed/Stages/Special/Stageconfig.bin";
		Str_TileSprite = "Mixed/Stages/Special/16x16Tiles.gif";

		switch (Act) {
		case 0: Str_SceneBin = "Mixed/Stages/Special/Scene1.bin"; break;
		case 1: Str_SceneBin = "Mixed/Stages/Special/Scene2.bin"; break;
		case 2: Str_SceneBin = "Mixed/Stages/Special/Scene3.bin"; break;
		case 3: Str_SceneBin = "Mixed/Stages/Special/Scene4.bin"; break;
		case 4: Str_SceneBin = "Mixed/Stages/Special/Scene5.bin"; break;
		case 5: Str_SceneBin = "Mixed/Stages/Special/Scene6.bin"; break;
		case 6: Str_SceneBin = "Mixed/Stages/Special/Scene7.bin"; break;
		case 7: Str_SceneBin = "Mixed/Stages/Special/Scene8.bin"; break;
		case 8: Str_SceneBin = "Mixed/Stages/Special/Scene9.bin"; break;
		case 9: Str_SceneBin = "Mixed/Stages/Special/Scene10.bin"; break;
		case 10: Str_SceneBin = "Mixed/Stages/Special/Scene11.bin"; break;
		case 11: Str_SceneBin = "Mixed/Stages/Special/Scene12.bin"; break;
		case 12: Str_SceneBin = "Mixed/Stages/Special/Scene13.bin"; break;
		case 13: Str_SceneBin = "Mixed/Stages/Special/Scene14.bin"; break;
		case 14: Str_SceneBin = "Mixed/Stages/Special/Scene15.bin"; break;
		case 15: Str_SceneBin = "Mixed/Stages/Special/Scene16.bin"; break;
		default: Str_SceneBin = "Mixed/Stages/Special/SceneRandom.bin"; break;
		}
	}
	else
	{
		Str_TileConfigBin = "Classic/Stages/Special/Tileconfig.bin";
		Str_StageBin = "Classic/Stages/Special/Stageconfig.bin";
		Str_TileSprite = "Classic/Stages/Special/16x16Tiles.gif";

		switch (Act) {
		case 0: Str_SceneBin = "Classic/Stages/Special/Scene1.bin"; break;
		case 1: Str_SceneBin = "Classic/Stages/Special/Scene2.bin"; break;
		case 2: Str_SceneBin = "Classic/Stages/Special/Scene3.bin"; break;
		case 3: Str_SceneBin = "Classic/Stages/Special/Scene4.bin"; break;
		case 4: Str_SceneBin = "Classic/Stages/Special/Scene5.bin"; break;
		case 5: Str_SceneBin = "Classic/Stages/Special/Scene6.bin"; break;
		case 6: Str_SceneBin = "Classic/Stages/Special/Scene7.bin"; break;
		case 7: Str_SceneBin = "Classic/Stages/Special/Scene8.bin"; break;
		case 8: Str_SceneBin = "Classic/Stages/Special/Scene9.bin"; break;
		case 9: Str_SceneBin = "Classic/Stages/Special/Scene10.bin"; break;
		case 10: Str_SceneBin = "Classic/Stages/Special/Scene11.bin"; break;
		case 11: Str_SceneBin = "Classic/Stages/Special/Scene12.bin"; break;
		case 12: Str_SceneBin = "Classic/Stages/Special/Scene13.bin"; break;
		case 13: Str_SceneBin = "Classic/Stages/Special/Scene14.bin"; break;
		case 14: Str_SceneBin = "Classic/Stages/Special/Scene15.bin"; break;
		case 15: Str_SceneBin = "Classic/Stages/Special/Scene16.bin"; break;
		default: Str_SceneBin = "Classic/Stages/Special/SceneRandom.bin"; break;
		}
	}

	Data = new SceneData();

	TileSprite = new ISprite(Str_TileSprite, App);
	TileSprite->SetTransparentColorIndex(0x0);

	ISprite::Animation an;
	an.Name = "";
	an.FrameCount = 0x400;
	an.Frames = new ISprite::AnimFrame[an.FrameCount];
	if (TileSprite->Width > 16) {
		for (int i = 0; i < 0x400; i++) {
			ISprite::AnimFrame ts_af;
			ts_af.X = (i & 0x1F) << 4;
			ts_af.Y = (i >> 5) << 4;
			ts_af.W = ts_af.H = 16;
			ts_af.OffX = ts_af.OffY = -8;
			an.Frames[i] = ts_af;
			G->MakeFrameBufferID(TileSprite, an.Frames + i);
		}
	}
	else {
		for (int i = 0; i < 0x400; i++) {
			ISprite::AnimFrame ts_af;
			ts_af.X = 0;
			ts_af.Y = i << 4;
			ts_af.W = ts_af.H = 16;
			ts_af.OffX = ts_af.OffY = -8;
			an.Frames[i] = ts_af;
			G->MakeFrameBufferID(TileSprite, an.Frames + i);
		}
	}
	TileSprite->Animations.push_back(an);

	// Loading TileConfig
	IResource* TileConfig = IResources::Load(Str_TileConfigBin); // Stages/MSZ/TileConfig.bin
	if (TileConfig) {
		IStreamer tileReader(TileConfig);
		Memory::Free(tileReader.ReadByte4()); // Magic Word

		unsigned char* TileData = tileReader.ReadCompressed();
		IResources::Close(TileConfig);

		Data->tiles1 = new TileCfg[0x400];
		Data->tiles2 = new TileCfg[0x400];

		// Amount of bytes per Tile Definition
		int maxDataBytes = 0x26;
		// Collision Plane 1
		for (int i = 0; i < 0x400; i++) {
			int n = i * maxDataBytes;

			memcpy(Data->tiles1[i].Collision, TileData + n + 0x00, 0x10);
			memcpy(Data->tiles1[i].HasCollision, TileData + n + 0x10, 0x10);
			Data->tiles1[i].IsCeiling = TileData[n + 0x20];
			memcpy(Data->tiles1[i].Config, TileData + n + 0x21, 0x05);
		}
		// Collision Plane 2
		for (int i = 0; i < 0x400; i++) {
			int n = (i + 0x400) * maxDataBytes;

			memcpy(Data->tiles2[i].Collision, TileData + n + 0x00, 0x10);
			memcpy(Data->tiles2[i].HasCollision, TileData + n + 0x10, 0x10);
			Data->tiles2[i].IsCeiling = TileData[n + 0x20];
			memcpy(Data->tiles2[i].Config, TileData + n + 0x21, 0x05);
		}
		delete[] TileData;
	}
	else {
		App->Print(2, "TileConfig at '%s' could not be read.", Str_TileConfigBin);
		system("pause");
		exit(1);
	}

	// Loading StageConfig
	// Stageconfig has to be loaded before the scene file so we get the object names
	if (Str_StageBin) {
		App->Print(0, "Loading StageConfig...");
		IResource* StageBin = IResources::Load(Str_StageBin);
		if (StageBin) {
			IStreamer stageReader(StageBin);
			free(stageReader.ReadByte4()); // Magic CFG0
			stageReader.ReadByte(); // UseGameObjects

			//Free previous Object Names
			clearObjectNames();
			//for (int i = 0; i < ObjectNameList.size(); i++)
			//{
				//free(ObjectNameList.at(i));
			//}

			// Read objects names
			int object_count = stageReader.ReadByte();
			for (int i = 0; i < object_count; i++) {
				SetObjectName(stageReader.ReadRSDKString()); // Object name
				//free(stageReader.ReadRSDKString());
			}

			// Read palette
			TileSprite->PaletteSize = 0x100;
			int pp = 0;
			for (int i = 0; i < 8; i++) {
				// IApp::Print(0, "yup: %X", pp);
				int ii = 0;
				int bitmap = stageReader.ReadUInt16();

				int size = 0;
				for (int col = 0; col < 16; col++) {
					if ((bitmap & (1 << col)) != 0) {
						size += 0x10;
					}
				}
				// IApp::Print(0, "size: %X", size);
				for (int col = 0; col < 16; col++) {
					if ((bitmap & (1 << col)) != 0) {
						for (int d = 0; d < 16; d++) {
							uint8_t R = stageReader.ReadByte();
							uint8_t G = stageReader.ReadByte();
							uint8_t B = stageReader.ReadByte();

							if (i == 3) {
								TileSprite->SetPalette(ii + 0x80, R << 16 | G << 8 | B);
							}
							if (i >= 3) {
								TileSprite->SetPaletteAlt(pp - 0x40, R << 16 | G << 8 | B);
							}

							pp++;
							ii++;
						}
					}
				}
			}
			TileSprite->UpdatePalette();

			/*
			FILE* f;
			f = fopen(IFILE("Stages/HCZ/ManiaPalette.bin"), "wb");
			fwrite(TileSprite->Palette + 128, 4, 128, f);
			fwrite(TileSprite->PaletteAlt + 128, 4, 128, f);
			fwrite(TileSprite->PaletteAlt, 4, 96, f);
			fclose(f);
			//*/

			// Read WAV channel's max concurrent play
			int wavs_count = stageReader.ReadByte();
			for (int i = 0; i < wavs_count; i++) {
				stageReader.ReadRSDKString(); // WAV name
				stageReader.ReadByte(); // Max Concurrent Play
				//App->Print(0, "WAV: '%s' (max: %d)", wav_name, max_concurrent_play);
			}

			IResources::Close(StageBin);
		}
		else {
			App->Print(2, "StageConfig at '%s' could not be read.", Str_StageBin);
			exit(1);
		}
	}
	else {
		if ((TileSprite->GetPalette(0x81) & 0xFFFFFF) == 0x000000) {
			TileSprite->PaletteSize = 0x80;
		}
		TileSprite->SplitPalette();
		TileSprite->UpdatePalette();

		if (AnimTileSprite) {
			if ((AnimTileSprite->GetPalette(0x81) & 0xFFFFFF) == 0x000000)
				AnimTileSprite->PaletteSize = 0x80;
			AnimTileSprite->SplitPalette();
			AnimTileSprite->UpdatePalette();
		}

		ItemsSprite->SplitPalette();
		ObjectsSprite->SplitPalette();
		ExplosionSprite->SplitPalette();

		ItemsSprite->UpdatePalette();
		ObjectsSprite->UpdatePalette();
		ExplosionSprite->UpdatePalette();
	}

	// Loading SceneBin
	IResource* SceneBin = IResources::Load(Str_SceneBin); // Stages/MSZ/Scene2.bin
	if (SceneBin) {
		IStreamer reader(SceneBin);
		uint32_t mag = reader.ReadUInt32BE(); // magic
		if (mag == 0x4953434E) {
			std::string LevelTitle = reader.ReadRSDKString();
			strcpy(LevelNameDiscord, LevelTitle.c_str());
			strcpy(LevelName, LevelTitle.c_str());

			IApp::Print(2, "Loading '%s'...", LevelName);

			char* TitleCheck = LevelName;
			while (*TitleCheck) {
				if (*TitleCheck >= 'a' && *TitleCheck >= 'z') {
					*TitleCheck += 'A' - 'a';
				}
				else if (*TitleCheck == ' ') {
					*TitleCheck = ' ';
				}
				else {
					*TitleCheck = ' ';
				}
				//IApp::Print(2, "Invalid character '%c' in Level Title.", *LevelTitle);
				TitleCheck++;
			}

			ZoneID = reader.ReadByte();
			Act = reader.ReadByte();
			HUDVisible = reader.ReadByte();
			HUDAnim = (HUDVisible ^ 1) * 0x100;
			reader.ReadRSDKString(); // Song File
			reader.ReadUInt32(); // Loop Point
			reader.ReadUInt32(); // Background Colour
		}
		else {
			delete[] reader.ReadBytes(16);
			reader.ReadRSDKString();
			Data->CameraLayer = reader.ReadByte(); // UnknownByte2
		}

		Data->CameraLayer = -1;
		Data->layerCount = reader.ReadByte();
		for (int i = 0; i < Data->layerCount; i++) {
			reader.ReadByte(); // Ignored Byte

			Data->Layers[i].Name = reader.ReadRSDKString();
			Data->Layers[i].IsScrollingVertical = reader.ReadByte() == 1 ? true : false;
			Data->Layers[i].Flags = reader.ReadByte();
			if (Data->Layers[i].Flags & 0x10) {
				Data->Layers[i].Visible = false;
			}

			Data->Layers[i].Deform = (int8_t*)Memory::TrackedCalloc("LevelScene::Data->Layers[i].Deform", 1, App->HEIGHT);

			int Width = (int)reader.ReadUInt16();
			int Height = (int)reader.ReadUInt16();

			Data->Layers[i].RelativeY = reader.ReadUInt16();
			Data->Layers[i].ConstantY = (short)reader.ReadUInt16();

			Data->Layers[i].InfoCount = (int)reader.ReadUInt16();

			if (Data->Layers[i].InfoCount) {
				Data->Layers[i].Info = new ScrollingInfo[Data->Layers[i].InfoCount];
			}

			App->Print(3, "Layer %d (%s): Width (%d) Height (%d) Infos (%d) Vertical Scrolling (%d) UnknownFlags (%d) %s", i, Data->Layers[i].Name.c_str(), Width, Height, Data->Layers[i].InfoCount, Data->Layers[i].IsScrollingVertical, Data->Layers[i].Flags, i == Data->CameraLayer ? " IS CAMERA LAYER" : "");

			for (int g = 0; g < Data->Layers[i].InfoCount; g++) {
				Data->Layers[i].Info[g].RelativeX = reader.ReadUInt16(); // actually is Scrolling Multiplier X
				Data->Layers[i].Info[g].ConstantX = (short)reader.ReadUInt16(); // actually is Constant movement X

				Data->Layers[i].Info[g].Behaviour = reader.ReadByte();
				Data->Layers[i].Info[g].DrawLayer = reader.ReadByte();

				if (Data->CameraLayer == -1) {
					if (Data->Layers[i].RelativeY == 0x100 &&
						Data->Layers[i].ConstantY == 0x000 &&
						Data->Layers[i].Info[g].RelativeX == 0x100 &&
						Data->Layers[i].Info[g].ConstantX == 0x000 &&
						Data->Layers[i].Name[0] == 'F' &&
						Data->Layers[i].InfoCount == 1)
						Data->CameraLayer = i;
				}

				//App->Print(0, " > ScrollInfo %d: RelX (%X) ConstX (%X) %d %d", g, Data->Layers[i].Info[g].RelativeX, Data->Layers[i].Info[g].ConstantX, Data->Layers[i].Info[g].HeatWaveEnabled, Data->Layers[i].Info[g].Byte2);
			}

			if ((mag >> 24) == 'S') {
				Data->Layers[i].Flags = 0;
				if (Data->Layers[i].RelativeY == 0x100 &&
					Data->Layers[i].ConstantY == 0x000 &&
					Data->Layers[i].Info[0].RelativeX == 0x100 &&
					Data->Layers[i].Info[0].ConstantX == 0x000 &&
					Data->Layers[i].Name[0] == 'F' &&
					Data->Layers[i].InfoCount == 1)
					Data->Layers[i].Flags = 1;
			}

			// FUN FACT:
			// With all compressed data, we already know the size of the data. (using Width, Height, etc.)

			unsigned char* ScrollIndexes = reader.ReadCompressed();

			int cnt = 0;
			if (Height > 0) { // Just in case
				int s_start = 0;
				int value = ScrollIndexes[0];
				int s = 0;
				for (; s < Height * 16; s++) {
					int v = ScrollIndexes[s];
					if (v != value) {
						cnt++;
						s_start = s;
						value = v;
					}
				}
				cnt++;
				Data->Layers[i].ScrollIndexCount = cnt;
			}

			Data->Layers[i].ScrollIndexes = new ScrollingIndex[cnt];

			if (Height > 0) { // Just in case
				int sc = 0;
				int s_start = 0;
				int value = ScrollIndexes[0];
				int s = 0;
				for (; s < Height * 16; s++) {
					// ScrollingIndex
					int v = ScrollIndexes[s];
					// If we find a different value, cap it off and start anew.
					if (v != value) {
						Data->Layers[i].ScrollIndexes[sc].Index = value;
						Data->Layers[i].ScrollIndexes[sc].Size = s - s_start;
						//App->Print(0, " - ScrollIndex %d: Index %d Size %d", sc, Data->Layers[i].ScrollIndexes[sc].Index, Data->Layers[i].ScrollIndexes[sc].Size);

						sc++;
						s_start = s;
						value = v;
					}
				}
				// Data->Layers[i].ScrollIndexes[sc] = ScrollingIndex { value, s - s_start, NULL };
				Data->Layers[i].ScrollIndexes[sc].Index = value;
				Data->Layers[i].ScrollIndexes[sc].Size = s - s_start;
				//App->Print(0, " - ScrollIndex %d: Index %d Size %d", sc, Data->Layers[i].ScrollIndexes[sc].Index, Data->Layers[i].ScrollIndexes[sc].Size);
			}
			delete[] ScrollIndexes;

			Data->Layers[i].Width = Width;
			Data->Layers[i].Height = Height;
			unsigned char* Tilesss = reader.ReadCompressed();

			Data->Layers[i].Tiles = new short[Width * Height * sizeof(short)];
			Data->Layers[i].TilesBackup = new short[Width * Height * sizeof(short)];
			Data->Layers[i].TileOffsetY = (short*)Memory::TrackedCalloc("LevelScene::Data->Layers[i].TileOffsetY", sizeof(short), Width);


			IStreamer creader(Tilesss);
			for (int y = 0; y < Height; y++) {
				for (int x = 0; x < Width; x++) {
					Data->Layers[i].Tiles[x + y * Width] = creader.ReadUInt16();
				}
			}

			PatchLayer(i);

			memcpy(Data->Layers[i].TilesBackup, Data->Layers[i].Tiles, Width * Height * sizeof(short));
			delete[] Tilesss;
		}

		enum {
			OBJ_SPRING = 0x2802B89EU, //
			OBJ_STARPOST = 0xC8B337E6U, //
			OBJ_SPIKES = 0x44BC7B0EU, //
			OBJ_SPECIALRING = 0xABC2C658U, //

			OBJ_PLANESWITCHER = 0x91586422U, // 0x91586422U
			OBJ_PLAYER = 0xD68AF920U,
			OBJ_RING = 0x2EA61FD6U,
			OBJ_MONITOR = 0xD028F874U, // 0xB3C47F67U
		};

		enum {
			ATTRIBUTE_UINT8,
			ATTRIBUTE_UINT16,
			ATTRIBUTE_UINT32,
			ATTRIBUTE_INT8,
			ATTRIBUTE_INT16,
			ATTRIBUTE_INT32,
			ATTRIBUTE_VAR,
			ATTRIBUTE_BOOL,
			ATTRIBUTE_STRING,
			ATTRIBUTE_POSITION,
			ATTRIBUTE_UNKNOWN,
			ATTRIBUTE_COLOR,
		};

		PlaneSwitchers = (PlaneSwitch*)Memory::TrackedMalloc("LevelScene::PlaneSwitchers", 113 * sizeof(PlaneSwitch));

		Data->IsAnims = (short*)Memory::TrackedMalloc("LevelScene::Data->IsAnims", 0x400 * sizeof(short));
		std::memset(Data->IsAnims, 0xFF, 0x400 * sizeof(short));

		int BlankTile = 0x3FF;

		// Mania-type Object Loading
		if ((mag >> 24) == 'S') {
			ManiaLevel = true;

			unordered_map<string, const char*> ObjectHashes;
			for (int i = 0; i < 554; i++) {
				string Hash = MD5I(string(ObjectNames(i)));
				ObjectHashes[Hash] = ObjectNames(i);
			}

			for (int i = 0; i < GetObjectNamesSize(); i++) {
				string Hash = MD5I(string(GetObjectName(i))); // Create a hash for the name
				ObjectHashes[Hash] = GetObjectName(i); // Set the name to be associated with said hash
			}

			int AttributeTypes[0x40];
			AttributeValue Attributes[0x40];

			// Clear objects
			LevelScene::Objects.clear();
			ObjectCount = 0;
			ObjectNewCount = 0;

			Data->ObjectDefinitionCount = reader.ReadByte();
			for (int i = 0; i < Data->ObjectDefinitionCount; i++) {
				char str[16];
				char HashString[33];
				sprintf(HashString, "%s", "");

				// Read the Object's Hash
				for (int n = 0; n < 16; n++) {
					str[n] = reader.ReadByte();
					sprintf(HashString, "%s%02x", HashString, (unsigned char)str[n]);
				}

				// Get our object name
				const char* ObjectName = ObjectHashes[HashString];
				if (ObjectName == NULL) {
					ObjectName = "Unimplemented Object";
				}
				App->Print(0, ObjectName);
				uint32_t ObjHash = crc32((char*)str, 16);

				// Allocate our types.
				int AttributeCount = reader.ReadByte();

				// Clear out the Attributes we'll use.
				for (int n = 1; n < AttributeCount; n++)
				{
					AttributeTypes[n] = 0xFF;
					CreateAttributeValue(&Attributes[n]);
				}

				// Load Attribute Names
				// Skip 'filter' (it's handled weirdly)
				for (int n = 1; n < AttributeCount; ++n) {
					// Read our attribute hash into our array
					for (int n2 = 0; n2 < 16; n2++) {
						Attributes[n].NameHash[n2] = reader.ReadByte();
					}

					// Read what type this attribute is
					int AttributeType = reader.ReadByte();
					AttributeTypes[n] = AttributeType;
				}

				int EntityCount = reader.ReadUInt16();

				// Load all Entities
				for (int n = 0; n < EntityCount; ++n) {
					// Spawn in our entity
					Object* obj = GetNewObjectFromCRC32(ObjHash);

					if (obj == NULL) {
						obj = new BlankObject();
					}

					unsigned short SlotID = reader.ReadUInt16(); //SlotID
					if (obj) {
						obj->SlotID = SlotID;
					}

					unsigned short X_low = reader.ReadUInt16();
					short X_high = reader.ReadInt16();
					unsigned short Y_low = reader.ReadUInt16();
					short Y_high = reader.ReadInt16();

					if (obj) {
						obj->InitialX = X_high + ((float)X_low / 0x10000);
						obj->InitialY = Y_high + ((float)Y_low / 0x10000);
						obj->X = X_high + ((float)X_low / 0x10000);
						obj->Y = Y_high + ((float)Y_low / 0x10000);
					}

					// If we have more than one attribute
					if (AttributeCount > 1) {
						for (int a = 1; a < AttributeCount; a++) {
							switch (AttributeTypes[a]) {
							case ATTRIBUTE_INT8:
								Attributes[a].ValInt8 = (char)reader.ReadByte();
								break;
							case ATTRIBUTE_UINT8:
								Attributes[a].ValUint8 = (unsigned char)reader.ReadByte();
								break;
							case ATTRIBUTE_INT16:
								Attributes[a].ValInt16 = (short)reader.ReadInt16();
							case ATTRIBUTE_UINT16:
								Attributes[a].ValUint16 = (unsigned short)reader.ReadUInt16();
								break;
							case ATTRIBUTE_VAR:
								Attributes[a].ValVariable = (unsigned int)reader.ReadUInt32();
								break;
							case ATTRIBUTE_BOOL:
								Attributes[a].ValBool = reader.ReadUInt32() != 0;
								break;
							case ATTRIBUTE_COLOR:
								Attributes[a].ValColor.b = reader.ReadByte();
								Attributes[a].ValColor.g = reader.ReadByte();
								Attributes[a].ValColor.r = reader.ReadByte();
								Attributes[a].ValColor.a = reader.ReadByte();
								break;
							case ATTRIBUTE_INT32:
								Attributes[a].ValInt32 = (int)reader.ReadInt32();
								break;
							case ATTRIBUTE_UINT32:
								Attributes[a].ValUint32 = (unsigned int)reader.ReadUInt32();
								break;
							case ATTRIBUTE_STRING:
								Attributes[a].ValString = reader.ReadRSDKUnicodeString();
								break;
							case ATTRIBUTE_POSITION:
								short XHigh = reader.ReadInt16();
								unsigned short XLow = reader.ReadInt16();
								short YHigh = reader.ReadInt16();
								unsigned short YLow = reader.ReadInt16();

								// Remind me to make it better - RDC
								Attributes[a].ValPosition.X = XHigh + ((float)XLow / 0x10000);
								Attributes[a].ValPosition.Y = YHigh + ((float)YLow / 0x10000);
								break;
							}
							if (obj) {
								std::string HashString = std::string(Attributes[a].NameHash);
								if (HashString.size() > 16) {
									HashString.erase(16);
								}
								obj->ObjectAttributes.emplace(HashString, Attributes[a]);
							}
						}
					}

					if (obj && (ObjHash != OBJ_RING /*&& ObjHash != OBJ_PLANESWITCHER*/)) {
						obj->G = G;
						obj->App = App;
						obj->Scene = this;

						if (obj->BinIndex == 0xFFFFFFFF && (ObjectName != "BlankObject" && ObjectName != "PlayerSpawn")) {
							App->Print(1, "Object '%s' Sprite Not found!", ObjectName);
						}
						else {
							obj->Sprite = SpriteBinMapIDs.at(obj->BinIndex);
						}
						obj->DrawCollisions = App->viewObjectCollision;

						// Dunno what do to with filter so fuck it for now
						obj->ObjectAttributeCount = AttributeCount - 1;

						// Done for backwards compatibility, Returns 0 on error.
						obj->SubType = obj->GetAttribute("Subtype")->ValUint8;

						// Load our filter attribute, And if nothing return 0.
						obj->Filter = obj->GetAttribute("Filter")->ValUint8;

						//Setup object flags
						obj->S3Object = bool(obj->Filter >> 0 & 1);
						obj->SKObject = bool(obj->Filter >> 1 & 1);
						obj->MixedObject = bool(obj->Filter >> 2 & 1);
						obj->LockedOnObject = bool(obj->Filter >> 3 & 1);

						// Done for backwards compatibility, Returns false on error.
						obj->FlipX = obj->GetAttribute("FlipX")->ValBool;
						obj->FlipY = obj->GetAttribute("FlipY")->ValBool;

						// Add our object to the scene
						LevelScene::Objects.push_back(obj);
						ObjectCount++;
						//ObjectNewCount++;
					}
					else if (obj && ObjHash == OBJ_RING) {
						ObjectProp op;
						op.X = obj->X;
						op.Y = obj->Y;
						op.ID = 0xFF;
						op.LoadFlag = true;

						RingPropCount++;
						RingProps.push_back(op);
						delete obj;
					} if (obj && ObjHash == OBJ_PLANESWITCHER) {
						PlaneSwitchers[PlaneSwitchCount].X = obj->X;
						PlaneSwitchers[PlaneSwitchCount].Y = obj->Y;
						PlaneSwitchers[PlaneSwitchCount].Angle = obj->GetAttribute("Angle")->ValUint32;
						PlaneSwitchers[PlaneSwitchCount].Flags = obj->GetAttribute("Flags")->ValUint32;
						PlaneSwitchers[PlaneSwitchCount].OnPath = obj->GetAttribute("OnPath")->ValBool;
						PlaneSwitchers[PlaneSwitchCount].Size = obj->GetAttribute("Size")->ValUint32;
						if (PlaneSwitchers[PlaneSwitchCount].Size <= 0) PlaneSwitchers[PlaneSwitchCount].Size = 1;
						PlaneSwitchCount++;
					}
				}

				//Figure this out it crash :(
				if (AttributeCount > 1) {
					//free(AttributeTypes);
					//free(attributes);
				}
			}
			//delete[] AttributeTypes;
			//delete[] attributes;
		}

		for (int i = 0; i < Data->layerCount; i++) {
			// Build buffers for GL renderer
			if (Data->Layers[i].InfoCount) {
				int y = 0;
				int siT, x;
				int tile = 0, flipY = 0, flags = 0;//, wheree = 0;
				int heightSize = 0, tilindx = 0, tilindy = 0, tilindpos = 0, word = 0;
				Layer layer = Data->Layers[i];

				int bufHeight = 0;
				for (int s = 0; s < layer.ScrollIndexCount; s++) {
					for (siT = 0; siT < layer.ScrollIndexes[s].Size; siT += heightSize) {
						heightSize = 16;
						if (heightSize > layer.ScrollIndexes[s].Size - siT)
							heightSize = layer.ScrollIndexes[s].Size - siT;
						if (heightSize > ((y + siT + 0x10) & ~0xF) - (y + siT)) // Rounded-up
							heightSize = ((y + siT + 0x10) & ~0xF) - (y + siT);

						bufHeight++;
					}
					y += layer.ScrollIndexes[s].Size;
				}

				y = 0;
				int buf = 0;
				int fullFlip;
				// layer.Width * bufHeight
				layer.ScrollIndexes[0].TileBuffers = (int*)calloc(bufHeight, sizeof(int));
				for (int s = 0; s < layer.ScrollIndexCount; s++) {
					for (siT = 0; siT < layer.ScrollIndexes[s].Size; siT += heightSize) {
						heightSize = 16;
						if (heightSize > layer.ScrollIndexes[s].Size - siT)
							heightSize = layer.ScrollIndexes[s].Size - siT;
						if (heightSize > ((y + siT + 0x10) & ~0xF) - (y + siT)) // Rounded-up
							heightSize = ((y + siT + 0x10) & ~0xF) - (y + siT);

						G->BeginSpriteListBuffer();

						for (x = 0; x < layer.Width; x++) {
							tilindy = ((y + siT) >> 4);
							tilindx = x;
							tilindpos = x + (tilindy)* layer.Width;

							word = layer.Tiles[tilindpos];
							fullFlip = ((word >> 10) & 3);
							flipY = ((word >> 11) & 1);
							tile = word & 0x3FF;

							if (tile != BlankTile) {
								int anID = Data->IsAnims[tile] & 0xFF;

								flags = 0;
								if (flipY)
									flags |= IE_FLIPY;

								int wheree = (y + siT) & 0xF;
								if (flipY)
									wheree = 0x10 - wheree - heightSize;

								if (anID == 0xFF) {
									/*
									// Data->Layers[i].ScrollIndexes[0].TileBuffers[x + buf * layer.Width] =
									G->MakeFrameBufferID(TileSprite, &Data->Layers[i].ScrollIndexes[0].TileBuffers[x + buf * layer.Width], ((tile & 0x1F) << 4), ((tile >> 5) << 4) + wheree, 16, heightSize, -8, -heightSize / 2, fullFlip);
									//*/
									if (TileSprite->Width > 16)
										G->AddToSpriteListBuffer(TileSprite, ((tile & 0x1F) << 4), ((tile >> 5) << 4) + wheree, 16, heightSize, -8 + (x << 4), -heightSize / 2, fullFlip);
									else
										G->AddToSpriteListBuffer(TileSprite, 0, (tile << 4) + wheree, 16, heightSize, -8 + (x << 4), -heightSize / 2, fullFlip);
								}
							}
						}

						Data->Layers[i].ScrollIndexes[0].TileBuffers[buf] = G->FinishSpriteListBuffer();
						buf++;
					}

					y += layer.ScrollIndexes[s].Size;
				}
			}
		}

		IResources::Close(SceneBin);
	}
	else {
		App->Print(2, "Scene.bin at '%s' could not be read.", Str_SceneBin);
		exit(1);
	}
}

PUBLIC void Level_SpecialStage::Init() {
	PlayerCount = 0;

	if (SaveGame::CurrentMode >= 1)
	{
		PlayMusic("Mixed/Music/SpecialStage.ogg", 5309957, -1);
	}
	else
	{
		PlayMusic("Classic/Music/SpecialStage.ogg", 5309957, -1);
	}

	//Load BSS Scene Files
	LoadStage();

	//Used for playField data
	playFieldLayerID = FindLayer("Playfield");
	ringCountLayerID = FindLayer("Ring Count");
	backgroundLayerID = FindLayer("Background");
	globeLayerID = FindLayer("Globe");

	if (LevelScene::ObjectCount > 0)
	{
		Object* obj = LevelScene::Objects[0];
		useStageConfig = obj->GetAttribute("useStageConfig")->ValBool;
		PaletteID = obj->GetAttribute("paletteID")->ValVariable;
		SkyAlpha = obj->GetAttribute("skyAlpha")->ValUint8;
		GlobeAlpha = obj->GetAttribute("globeAlpha")->ValUint8;
		playFieldColourA = obj->AttribColourToUint32(obj->GetAttribute("playfieldA")->ValColor, false);
		playFieldColourB = obj->AttribColourToUint32(obj->GetAttribute("playfieldB")->ValColor, false);
		BGColour = obj->AttribColourToUint32(obj->GetAttribute("bgColor1")->ValColor, false);
		BGStarColour1 = obj->AttribColourToUint32(obj->GetAttribute("bgColor2")->ValColor, false);
		BGStarColour2 = obj->AttribColourToUint32(obj->GetAttribute("bgColor3")->ValColor, false);
	}

	//FadeTimer = 0;
	FadeTimerMax = 0x100;
	FadeAction = FadeActionType::FADEIN;
	G->FadeToWhite = true;

	if (!MobileButtonsSprite) {
		MobileButtonsSprite = new ISprite("UI/Mobile Buttons.gif", App);
		ISprite::Animation an;
		an.Name = "";
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
		if (SaveGame::CurrentMode == 1) {
			ItemsSprite = new ISprite("Global/Items.gif", App);
			ItemsSprite->Print = true;
			ItemsSprite->LoadAnimation("Global/ItemBox.bin");
			ItemsSprite->LoadAnimation("Global/Ring.bin");
			ItemsSprite->LoadAnimation("Special/Ring.bin");
		}
		else {
			ItemsSprite = new ISprite("GlobalS3K/Items.gif", App);
			ItemsSprite->LoadAnimation("GlobalS3K/ItemBox.bin");
			ItemsSprite->LoadAnimation("GlobalS3K/Ring.bin");
			ItemsSprite->LoadAnimation("Special/Ring.bin");
		}
	}

	IResource* SetupBin;
	SetupBin = IResources::Load("Objects/BSS_Setup.bin");
	if (SetupBin) {
		IStreamer reader(SetupBin);

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

		/*//Jump to colour data
		reader.Seek(0x8E1 + (Act * 0x10));

		playFieldColourA = G->GetRetroColour(reader.ReadUInt16BE());
		playFieldColourB = G->GetRetroColour(reader.ReadUInt16BE());

		BGColour = G->GetRetroColour(reader.ReadUInt16BE());
		reader.ReadUInt16BE();
		reader.ReadUInt16BE();

		reader.ReadUInt16(); // 0x0000
		ColourSky = reader.ReadUInt16(); // Sky Alpha
		ColourGlobe = reader.ReadUInt16(); // Globe Alpha*/
		IResources::Close(SetupBin);
	}

	if (Data)
	{
		Layout = (uint8_t*)Memory::TrackedMalloc("BSS::Layout",0x400);
		LayoutCopy = (uint8_t*)Memory::TrackedMalloc("BSS::LayoutCopy", 0x400);
		PinkSphereX = (int*)Memory::TrackedMalloc("BSS::LayoutPinkSphereX", 0x80);
		PinkSphereY = (int*)Memory::TrackedMalloc("BSS::LayoutLayoutPinkSphereY", 0x80);

		int ringCount = 0;

		int i = 0;

		for (int y = 0; y < 0x20; y++)
		{
			for (int x = 0; x < 0x20; x++)
			{
				LayoutCopy[i] = Data->Layers[playFieldLayerID].Tiles[i] & 0x3FF;
				if ((Data->Layers[ringCountLayerID].Tiles[i] & 0x3FF) == 7)
				{
					ringCount++;
				}
				if (LayoutCopy[i] == BSS_PLAYER_ANGLE_0)
				{
					StartAngle = (0xC000);
					StartX = x * 256;
					StartY = y * 256;
					LayoutCopy[i] = 0;
				}
				if (LayoutCopy[i] == BSS_PLAYER_ANGLE_90)
				{
					StartAngle = (0x8000);
					StartX = x * 256;
					StartY = y * 256;
					LayoutCopy[i] = 0;
				}
				if (LayoutCopy[i] == BSS_PLAYER_ANGLE_180)
				{
					StartAngle = (0x4000);
					StartX = x * 256;
					StartY = y * 256;
					LayoutCopy[i] = 0;
				}
				if (LayoutCopy[i] == BSS_PLAYER_ANGLE_270)
				{
					StartAngle = (0x0000);
					StartX = x * 256;
					StartY = y * 256;
					LayoutCopy[i] = 0;
				}

				if (LayoutCopy[i] == BSS_SPHERE_PINK)
				{
					PinkSphereX[PinkSphereCount] = x * 256;
					PinkSphereY[PinkSphereCount] = y * 256;
					PinkSphereCount++;
				}

				i++;
			}
		}

		PerfectAmount = ringCount;
	}

	TileSprite->SetPalette(160, BGColour);
	TileSprite->SetPalette(161, BGStarColour1);
	TileSprite->SetPalette(162, BGStarColour2);

	if (ZoneID == 20) {
		memset(Layout, 0, 0x400);
		for (int x = 0; x < 32; x++) {
			Layout[0x00 << 5 | x] = BSS_SPHERE_BUMPER;
			Layout[0x1F << 5 | x] = BSS_SPHERE_BUMPER;
			Layout[x << 5 | 0x00] = BSS_SPHERE_BUMPER;
			Layout[x << 5 | 0x1F] = BSS_SPHERE_BUMPER;
		}
		Layout[0x10 << 5 | 0x10] = BSS_SPHERE_BLUE;
		memcpy(LayoutCopy, Layout, 0x400);

		StartX = 0x1200;
		StartY = 0x1200;
		PerfectAmount = 4;
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

	EventFlag = BSS_EVENT_START;

    memcpy(Layout, LayoutCopy, 0x400);
    PlayerX = StartX >> 8;
    PlayerY = StartY >> 8;
	PlayerLastX = PlayerX;
	PlayerLastY = PlayerY;
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
	ColourFlip = true;

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
        if (Layout[i] == BSS_SPHERE_BLUE)
            BallCount++;
    }

	//Startup timer
	PlayerWaitMovementTimer = Timer2 = 300;
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
	if ((*LayoutAt(ox - 1, oy - 1) & 0x7F) == BSS_SPHERE_BLUE) return false;
	if ((*LayoutAt(ox + 1, oy - 1) & 0x7F) == BSS_SPHERE_BLUE) return false;
	if ((*LayoutAt(ox - 1, oy) & 0x7F) == BSS_SPHERE_BLUE) return false;
	if ((*LayoutAt(ox + 1, oy) & 0x7F) == BSS_SPHERE_BLUE) return false;
	if ((*LayoutAt(ox - 1, oy + 1) & 0x7F) == BSS_SPHERE_BLUE) return false;
	if ((*LayoutAt(ox + 1, oy + 1) & 0x7F) == BSS_SPHERE_BLUE) return false;
	if ((*LayoutAt(ox, oy - 1) & 0x7F) == BSS_SPHERE_BLUE) return false;
	if ((*LayoutAt(ox, oy + 1) & 0x7F) == BSS_SPHERE_BLUE) return false;
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

		if ((*LayoutAt(x, y) & 0x7F) != BSS_SPHERE_RED)
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
		if ((*LayoutAt(x + SCD_X[dirSide1], y + SCD_Y[dirSide1]) & 0x7F) == BSS_SPHERE_RED)
			isAnything |= SphereCheckDirection(x, y, dirSide1);
		if ((*LayoutAt(x + SCD_X[dirSide2], y + SCD_Y[dirSide2]) & 0x7F) == BSS_SPHERE_RED)
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

		if ((*LayoutAt(dataStartX, dataStartY) & 0x7F) != BSS_SPHERE_RED)
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
		if ((*LayoutAt((ox + 1) & 0x1F, dataStartY) & 0x7F) == BSS_SPHERE_RED)
			isAnything |= SphereCheckRight(ox, dataStartY);
		if ((*LayoutAt((ox - 1) & 0x1F, dataStartY) & 0x7F) == BSS_SPHERE_RED)
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

		if ((*LayoutAt(dataStartX, dataStartY) & 0x7F) != BSS_SPHERE_RED)
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
		if ((*LayoutAt((ox - 1) & 0x1F, dataStartY) & 0x7F) == BSS_SPHERE_RED)
			isAnything |= SphereCheckLeft(ox, dataStartY);
		if ((*LayoutAt((ox + 1) & 0x1F, dataStartY) & 0x7F) == BSS_SPHERE_RED)
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

		if ((*LayoutAt(dataStartX, dataStartY) & 0x7F) != BSS_SPHERE_RED)
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
		if ((*LayoutAt(dataStartX, oy - 1) & 0x7F) == BSS_SPHERE_RED)
			isAnything |= SphereCheckUp(dataStartX, oy);
		if ((*LayoutAt(dataStartX, oy + 1) & 0x7F) == BSS_SPHERE_RED)
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

		if ((*LayoutAt(dataStartX, dataStartY) & 0x7F) != BSS_SPHERE_RED)
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
		if ((*LayoutAt(dataStartX, oy + 1) & 0x7F) == BSS_SPHERE_RED)
			isAnything |= SphereCheckDown(ox, dataStartY);
		if ((*LayoutAt(dataStartX, oy - 1) & 0x7F) == BSS_SPHERE_RED)
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
		if (!sphere || sphere == BSS_SPHERE_RED || sphere == 0)
			return 0;

		sY = (sY - 1) & 0x1F;
	}

	sX = ox;
	sY = (oy + 1) & 0x1F;
	for (int i = 0; i < 32; i++) {
		if (*LayoutExtraAt(sX, sY) == 1)
			break;

		int sphere = *LayoutAt(sX, sY) & 0x7F;
		if (!sphere || sphere == BSS_SPHERE_RED || sphere == 0)
			return 0;

		sY = (sY + 1) & 0x1F;
	}

	sX = (ox - 1) & 0x1F;
	sY = oy;
	for (int i = 0; i < 32; i++) {
		if (*LayoutExtraAt(sX, sY) == 1)
			break;

		int sphere = *LayoutAt(sX, sY) & 0x7F;
		if (!sphere || sphere == BSS_SPHERE_RED || sphere == 0)
			return 0;

		sX = (sX - 1) & 0x1F;
	}

	sX = (ox + 1) & 0x1F;
	sY = oy;
	for (int i = 0; i < 32; i++) {
		if (*LayoutExtraAt(sX, sY) == 1)
			break;

		int sphere = *LayoutAt(sX, sY) & 0x7F;
		if (!sphere || sphere == BSS_SPHERE_RED || sphere == 0)
			return 0;

		sX = (sX + 1) & 0x1F;
	}

	/*(int sphere = *LayoutExtraAt(ox, oy);

	if (!sphere || sphere == BSS_SPHERE_RED || sphere == 0)
		return 0;*/

	*LayoutExtraAt(ox, oy) = 1;

	return 1;
}

PUBLIC bool Level_SpecialStage::CheckSurround() {
	memset(LayoutBackup, 0, 0x400);
	memset(LayoutExtra, 0, 0x400);
	*LayoutAt(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY) = BSS_SPHERE_RED;
	*LayoutExtraAt(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY) = 1;

	PlayerDwordC0 = false;

	SphereCheckDirection(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY, 1); // Up
	SphereCheckDirection(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY, 3); // Down
	SphereCheckDirection(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY, 0); // Left
	SphereCheckDirection(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY, 2); // Right

	*LayoutAt(PlayerLastTouchedObjectX, PlayerLastTouchedObjectY) = BSS_SPHERE_BLUE;
	if (PlayerDwordC0 != 1)
		return false;

	int v7 = 0;
	int ComboSphereCount = 0;
	for (int sx = 0; sx < 32; sx++) {
		for (int sy = 0; sy < 32; sy++) {
			if ((*LayoutAt(sx, sy) & 0x7F) == BSS_SPHERE_BLUE) {
				int v12 = SomethingUsefulMaybe(sx, sy);
				ComboSphereCount += v12;
				v7 = ComboSphereCount;
			}
			/*//Hopefully this works
			if ((*LayoutAt(sx, sy) & 0x7F) == BSS_SPHERE_GREEN) {
				int v12 = SomethingUsefulMaybe(sx, sy);
				ComboSphereCount += v12;
				v7 = ComboSphereCount;
				*LayoutAt(sx, sy) = BSS_SPHERE_BLUE;
			}*/
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
			if (*LayoutExtraAt(sx, sy) == BSS_SPHERE_BLUE)
				*LayoutAt(sx, sy) = BSS_SPHERE_RING;
		}
	}

	BallCount -= ComboSphereCount;
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
			ColourFlip = !ColourFlip;
		DirectionStep &= 0xF;
		Direction = 1;
		return;
	}
	if (GameState == 2 || GameState == 3) { // Completed
		Timer1 = 0;
		EventFlag = BSS_EVENT_RESULTS;
		if (SpeedupTimerMax > 0x80) {
			SpeedupTimerMax = 0; // Reset and reuse SpeedupTimerMax because lazy
		}

		PlayerSteps += PlayerSpeed;
		if (PlayerSteps >= 0x100) {
			PlayerSteps -= 0x100;
			if (Direction != 0)
				PlayerSteps = 0;
			PlayerLastX = PlayerX;
			PlayerLastY = PlayerY;
			PlayerX = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			PlayerY = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			ColourFlip = !ColourFlip;
		}
		if (PlayerSteps <  0x0) {
			PlayerSteps += 0x100;
			PlayerLastX = PlayerX;
			PlayerLastY = PlayerY;
			PlayerX = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			PlayerY = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			ColourFlip = !ColourFlip;
		}
		PlayerZSpeed += PlayerMaxSpeed << 12;
		PlayerZ += PlayerZSpeed;
		if (PlayerZ > 0)
			PlayerZ = PlayerZSpeed = 0;

		if (GameState == 2) {
			if (++SpeedupTimerMax >= 0x80) {
				SpeedupTimerMax = 0;
				PlayerLastSpeed = PlayerSpeed;
				PlayerSpeed = 8;
				PlayerMaxSpeed = 8;
				PlayerIsMovingBackwards = false;
				GameState = 3;
				memset(Layout, 0, 0x400);

				int ThingX = (PlayerX + IMath::sign(-IMath::sinHex(PlayerAngle >> 8)) * 8) & 0x1F;
				int ThingY = (PlayerY + IMath::sign(-IMath::cosHex(PlayerAngle >> 8)) * 8) & 0x1F;

				*LayoutAt(ThingX, ThingY) = BSS_SPHERE_EMERALD;
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

			if (*LayoutAt(XIndex, YIndex) == BSS_SPHERE_EMERALD) {
				if ((PlayerIsMovingBackwards && PlayerSteps < 0x10) ||
					(!PlayerIsMovingBackwards && PlayerSteps > 0xF0)) {
					PlayerSteps = 0x00;
					if (!PlayerIsMovingBackwards) {
						ColourFlip = !ColourFlip;
						PlayerLastX = PlayerX;
						PlayerLastY = PlayerY;
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
		{
			PlayerLastSpeed = PlayerSpeed;
			PlayerSpeed += PlayerAccelerationRate;
		}
	}

	if ((PlayerAngle & 0x3FFF) == 0 && PlayerWaitMovementTimer == 0) {
		PlayerSteps = PlayerSteps + PlayerSpeed;

		if (PlayerSteps >= 0x100) {
			PlayerSteps -= 0x100;
			if (Direction != 0)
				PlayerSteps = 0;
			PlayerLastX = PlayerX;
			PlayerLastY = PlayerY;
			PlayerX = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			PlayerY = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			ColourFlip = !ColourFlip;
		}
		if (PlayerSteps <  0x0) {
			PlayerSteps += 0x100;
			PlayerLastX = PlayerX;
			PlayerLastY = PlayerY;
			PlayerX = (PlayerX + (IMath::sign(-IMath::sinHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			PlayerY = (PlayerY + (IMath::sign(-IMath::cosHex(PlayerAngle >> 8) * PlayerSpeed)) + 0x20) & 0x1F;
			ColourFlip = !ColourFlip;
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
		if (*LayoutAt(XIndex, YIndex) == BSS_SPHERE_RED) {
			if ((PlayerIsMovingBackwards && PlayerSteps < 0x20) ||
				(!PlayerIsMovingBackwards && PlayerSteps > 0xE0) &&
				!HitBlue) {
				PlayerLastTouchedObjectX = XIndex;
				PlayerLastTouchedObjectY = YIndex;
				PlayerSteps = 0x00;
				if (!PlayerIsMovingBackwards) {
					ColourFlip = !ColourFlip;
					PlayerLastX = PlayerX;
					PlayerLastY = PlayerY;
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
		else if (*LayoutAt(XIndex, YIndex) == (0x80 | BSS_SPHERE_RED)) {
			if ((PlayerIsMovingBackwards && PlayerSteps > 0x20) ||
				(!PlayerIsMovingBackwards && PlayerSteps < 0xE0)) {
				PlayerLastTouchedObjectX = XIndex;
				PlayerLastTouchedObjectY = YIndex;
				*LayoutAt(XIndex, YIndex) = BSS_SPHERE_RED;
			}
		}
		else if (*LayoutAt(XIndex, YIndex) == BSS_SPHERE_BLUE) {
			if ((PlayerIsMovingBackwards && PlayerSteps < 0x80) ||
				(!PlayerIsMovingBackwards && PlayerSteps > 0x80)) {
				PlayerLastTouchedObjectX = XIndex;
				PlayerLastTouchedObjectY = YIndex;
				CheckSurround();
				BallCount--;
				HitBlue = true;
				if (!PlayerDwordC0) {
					*LayoutAt(XIndex, YIndex) = BSS_SPHERE_RED;
				}
				if (BallCount <= 0) {
					BallCount = 0;
					GameState = 2; // 2
					SaveGame::SetEmerald(Act);
					if (SaveGame::CurrentEmeralds >= 0x7F) //All chaos emeralds!
					{
						App->Achievements->SetAchievement(2, true);
					}
					if (SaveGame::CurrentEmeralds >= 0x7FFF) //All Super and chaos emeralds!
					{
						App->Achievements->SetAchievement(3, true);
					}
					if (RingCount >= PerfectAmount)
					{
						SaveGame::Savefiles[SaveGame::CurrentSaveFile].Score += 50000;
					}
					EventFlag = BSS_EVENT_RESULTS;
					SaveGame::Flush();
					Sound::Play(Sound::SFX_SPECIALSTAGE_FLYAWAY);
					App->Audio->FadeMusic(1.0);
				}
				else {
					Sound::Play(Sound::SFX_BLUEBALL);
				}
			}
		}
		else if (*LayoutAt(XIndex, YIndex) == BSS_SPHERE_BUMPER) {
			if (PlayerIsMoveForwardLocked)
				goto RETURN;

			bool go = false;
			//DropDash = -2;
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
				PlayerLastSpeed = PlayerSpeed;
				PlayerSpeed = -PlayerSpeed;
				PlayerIsMovingBackwards = !PlayerIsMovingBackwards;
				Sound::Play(Sound::SFX_BUMPER);
			}
		}
		else if (*LayoutAt(XIndex, YIndex) == BSS_SPHERE_YELLOW) {
			if ((PlayerIsMovingBackwards && PlayerSteps < 0x80) ||
				(!PlayerIsMovingBackwards && PlayerSteps > 0x80)) {

				PlayerZSpeed = -0x180000;
				PlayerSpeed = PlayerLastSpeed;
				PlayerSpeed = (int)(PlayerSpeed * 1.5);
				PlayerAccelerationRate = 4;
				Direction = 0;
				Sound::Play(Sound::SFX_SPRING);
			}
		}
		else if (*LayoutAt(XIndex, YIndex) == BSS_SPHERE_GREEN) {
		if ((PlayerIsMovingBackwards && PlayerSteps < 0x80) ||
			(!PlayerIsMovingBackwards && PlayerSteps > 0x80)) {
			PlayerLastTouchedObjectX = XIndex;
			PlayerLastTouchedObjectY = YIndex;
			if (!PlayerDwordC0) {
				*LayoutAt(XIndex, YIndex) = BSS_SPHERE_BLUE;
			}
		}
		}
		else if (*LayoutAt(XIndex, YIndex) == BSS_SPHERE_PINK) {
		if ((PlayerIsMovingBackwards && PlayerSteps < 0x80) ||
			(!PlayerIsMovingBackwards && PlayerSteps > 0x80)) {
			PlayerWaitMovementTimer = 0xFF;
			int PinkID = IMath::randRange(0, PinkSphereCount - 1);
			PlayerX = PinkSphereX[PinkID];
			PlayerY = PinkSphereY[PinkID];
		}
		}
		else if (*LayoutAt(XIndex, YIndex) == BSS_SPHERE_RING) {
			if ((PlayerIsMovingBackwards && PlayerSteps < 0x80) ||
				(!PlayerIsMovingBackwards && PlayerSteps > 0x80)) {

				RingCount++;
				Sound::Play(Sound::SFX_RING);

				//Got a perfect!
				if (RingCount >= PerfectAmount)
				{
					Sound::Play(Sound::SFX_ENTER_SS_RING);
					EventFlag = BSS_EVENT_PERFECT;
					Timer2 = 300;
					Timer1 = 20 * 8;
				}

				*LayoutAt(XIndex, YIndex) = 0;
			}
		}
		if (PlayerSteps == 0) {
			HitBlue = false;
		}
		/*if (DropDash == -1 && PlayerZ == 0) {
			PlayerSpeed *= 1.5;
			DropDash = XIndex;
			DropDashY = YIndex;
			Sound::Play(Sound::SFX_DROPDASH);
			if (PlayerIsMovingBackwards) {
				PlayerIsMoveForwardLocked = true;
				PlayerSpeed = -PlayerSpeed;
				PlayerIsMovingBackwards = !PlayerIsMovingBackwards;
			}
		}
		if (DropDash > -1) {
			if (IMath::abs((int)IMath::pythag(XIndex, YIndex) - (int)IMath::pythag(DropDash, DropDashY)) >= 3) {
				PlayerSpeed = PlayerMaxSpeed;
				DropDash = -2;
			}
			/*if (PlayerSpeed > PlayerMaxSpeed)
				PlayerSpeed -= PlayerMaxSpeed * .1;
			else {
				PlayerSpeed = PlayerMaxSpeed;
				DropDash = -2;
			}
		}*/
	} RETURN:

    if (Direction == 0) {
        if (App->Input->GetControllerInput(0)[IInput::I_LEFT] /*&& DropDash == -2*/) {
            Direction = 1;
        }
        if (App->Input->GetControllerInput(0)[IInput::I_RIGHT] /*&& /*DropDash == -2*/) {
            Direction = -1;
        }
    }

	//Startup
	if (PlayerWaitMovementTimer > 0) {
		PlayerWaitMovementTimer--;
		if (App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED]) {
			PlayerWaitMovementTimer = 0;
		}
	}

	if (PlayerZ == 0 && (PlayerAngle & 0x3FFF) == 0 && App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED] && DropDash == -2) {
		PlayerZSpeed = -0x100000;
		Sound::Play(Sound::SFX_JUMP);
	}
	PlayerZSpeed += PlayerMaxSpeed << 12;
	PlayerZ += PlayerZSpeed;
	if (PlayerZ > 0)
		PlayerZ = PlayerZSpeed = 0;

	/*if (SaveGame::CurrentCharacterFlag == 0) {
		if (IMath::abs(PlayerZ) > 0x100000 && (PlayerAngle & 0x3FFF) == 0 && App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED] && PlayerSpeed != 0 && DropDash == -2) {
			Sound::Play(Sound::SFX_DROPDASHREADY);
			DropDash = -1;
			IApp::Print(1, std::to_string(PlayerZ).c_str());
		}
	}*/

	//Turning
    if ((PlayerSteps & 0xF0) == 0 && Direction != 0 && PlayerZ == 0) {
        if (DirectionStep == 0) {
            StoredAngle = PlayerAngle >> 12;

			if (Direction < 0)
				ColourFlip = !ColourFlip;

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
				ColourFlip = !ColourFlip;
            Direction = 0;
            DirectionStep = 0;
        }
    }

	//BG Scroll Handling
	if (DirectionStep == 0) {

		if (PlayerX != PlayerLastX || PlayerY != PlayerLastY)
		{
			if (PlayerSpeed > 0)
			{
				BGScrollValue = -2;
			}
			else
			{
				BGScrollValue = 2;
			}
		}

		BGScrollValue *= (IMath::abs(PlayerSpeed) /16) + 1;

		Data->Layers[backgroundLayerID].OffsetY += BGScrollValue;
	}
	else
	{
		Data->Layers[backgroundLayerID].OffsetX += 16 * (Direction);
	}

	if (EventFlag == BSS_EVENT_START)
	{	
		if (Timer2 <= 20)
		{
			Timer1 += 8;
			if (Timer1 >= App->WIDTH / 2)
			{
				EventFlag = BSS_EVENT_NONE;
				Timer1 = 0;
				Timer2 = 0;
			}
		}
		Timer2--;
	}

	if (EventFlag == BSS_EVENT_PERFECT)
	{
		if (Timer2 >= 300 - 20)
		{
			if (Timer1 > 0) Timer1 -= 8;
			Timer2--;
		}
		else if ( Timer2 <= 20)
		{
			Timer1 += 8;
			Timer2--;
		}
		else if (Timer2 == 0)
		{
			EventFlag = BSS_EVENT_NONE;
			Timer1 = 0;
			Timer2 = 0;
		}
		else
		{
			Timer2--;
		}
	}

}
PUBLIC void Level_SpecialStage::Subupdate() {

}
PUBLIC void Level_SpecialStage::HandleCamera() {

}

PUBLIC void Level_SpecialStage::RenderEverything() {
	G->DrawRectangle(0, 0, App->WIDTH, 128, BGColour);

	for (int l = 0; l < Data->layerCount; l++) {
		Data->Layers[l].Visible = false;
	}

	Data->Layers[backgroundLayerID].Visible = true;
	Data->Layers[globeLayerID].Visible = DirectionStep == 0;

	//Update Palettes
	if (DirectionStep == 0) {
		int t = PlayerSteps >> 4;
		for (int i = 0; i < 16; i++) {
			TileSprite->SetPalette(128 + i, (t > i) ^ ColourFlip ? playFieldColourA : playFieldColourB);
			TileSprite->SetPalette(128 + 16 + i, (t > i) ^ ColourFlip ? playFieldColourB : playFieldColourA);
		}
		TileSprite->UpdatePalette();
	}
	else {
		GlobeSpin->SetPalette(128, ColourFlip ? playFieldColourA : playFieldColourB);
		GlobeSpin->SetPalette(144, ColourFlip ? playFieldColourB : playFieldColourA);
		GlobeSpin->UpdatePalette();

		Data->Layers[globeLayerID].Visible = false;
	}

	Layer layer;
	int fullFlip;
	int s, siT, x, y;
	int tile, flipX, flipY, baseX, baseY, wheree;
	int index, TileBaseX, TileBaseY;

	Uint16 BlankTile = 0x3FFF;

	for (int l = 0; l < Data->layerCount; l++) {
		y = 0;
		layer = Data->Layers[l];

		// Draw Tiles
		if (layer.Visible) {
			G->DoDeform = true;
			memcpy(G->Deform, layer.Deform, App->HEIGHT);
			if (layer.InfoCount > 1) {
				int buf = 0;
				for (s = 0; s < layer.ScrollIndexCount; s++) {
					index = layer.ScrollIndexes[s].Index;

					int heightSize, tilindx, tilindy, tilindpos, word, fBX;
					for (siT = 0; siT < layer.ScrollIndexes[s].Size; siT += heightSize) {
						heightSize = 16;
						if (heightSize > layer.ScrollIndexes[s].Size - siT)
							heightSize = layer.ScrollIndexes[s].Size - siT;
						if (heightSize > ((y + siT + 0x10) & ~0xF) - (y + siT)) // Rounded-up
							heightSize = ((y + siT + 0x10) & ~0xF) - (y + siT);

						if (layer.UseDeltaCameraX)
							TileBaseX = (CameraDeltaX * layer.Info[index].RelativeX + layer.Info[index].ConstantX * Frame) >> 8;
						else
							TileBaseX = (CameraX * layer.Info[index].RelativeX + layer.Info[index].ConstantX * Frame) >> 8;

						TileBaseY = y + siT;
						if (layer.UseDeltaCameraY)
							TileBaseY -= (CameraDeltaY * layer.RelativeY + layer.ConstantY * Frame) >> 8;
						else
							TileBaseY -= (CameraY * layer.RelativeY + layer.ConstantY * Frame) >> 8;

						TileBaseX -= layer.OffsetX;
						TileBaseY -= layer.OffsetY;

						int bufVal = 0;
						if (TileBaseY + heightSize > 0 && TileBaseY < App->HEIGHT) {
							bufVal = layer.Width * 16;
							fBX = (((-TileBaseX) % bufVal + bufVal) % bufVal);

							for (x = (TileBaseX >> 4) - 1; x < 2 + ((TileBaseX + App->WIDTH) >> 4); x++) {
								tilindy = ((y + siT) >> 4);
								tilindy = (tilindy % layer.Height + layer.Height) % layer.Height; // so it loops
								tilindx = ((x % layer.Width + layer.Width) % layer.Width);
								tilindpos = tilindx + (tilindy)* layer.Width;

								baseX = (x << 4) - TileBaseX;
								baseY = TileBaseY;

								word = layer.Tiles[tilindpos];
								fullFlip = (word >> 10) & 3;
								tile = word & 0x3FF;

								if (tile != BlankTile) {
									int anID = Data->IsAnims[tile] & 0xFF;

									if (anID != 0xFF) {
										G->DrawSprite(AnimTileSprite, Data->IsAnims[tile] >> 8, Data->animatedTileFrames[anID], baseX + 8, baseY + 8, 0, fullFlip);
									}
									else {
										// tilindx + buf * layer.Width
										if (layer.ScrollIndexes[0].TileBuffers && layer.ScrollIndexes[0].TileBuffers[buf] > 0) {
											if (bufVal != 0)
												G->DrawSpriteListBuffer(TileSprite,
													layer.ScrollIndexes[0].TileBuffers[buf], layer.Width,
													fBX + 8, baseY + heightSize / 2);
											G->DrawSpriteListBuffer(TileSprite,
												layer.ScrollIndexes[0].TileBuffers[buf], layer.Width,
												fBX + 8 - bufVal, baseY + heightSize / 2);
											// G->DrawSpriteListBuffer(TileSprite,
											//     layer.ScrollIndexes[0].TileBuffers[buf], layer.Width,
											//     fBX + 8 + bufVal, baseY + heightSize / 2);

											// G->DrawSpriteBuffered(TileSprite,
											//     layer.ScrollIndexes[0].TileBuffers[buf], // bufVal,
											//     // baseX + 8, baseY + heightSize / 2, 0, bufVal);//fullFlip);
											//     TileBaseX + 8, baseY + heightSize / 2, 0, bufVal);//fullFlip);

											bufVal = 0;
										}
										else {
											flipY = ((fullFlip >> 1) & 1);

											wheree = (y + siT) & 0xF;
											if (flipY)
												wheree = 0x10 - wheree - heightSize;

											if (TileSprite->Width > 16)
												G->DrawSprite(TileSprite, ((tile & 0x1F) << 4), wheree + ((tile >> 5) << 4), 16, heightSize, baseX + 8, baseY + heightSize / 2, 0, fullFlip, -8, -heightSize / 2 - (heightSize & flipY));
											else
												G->DrawSprite(TileSprite, 0, wheree + (tile << 4), 16, heightSize, baseX + 8, baseY + heightSize / 2, 0, fullFlip, -8, -heightSize / 2 - (heightSize & flipY));
										}
									}
								}
							}
						}

						buf++;
					}
					y += layer.ScrollIndexes[s].Size;
				}
			}
			else {
				if (layer.Info[0].Behaviour == 1) {
					if (ManiaLevel)
						G->DoDeform = true;
				}

				if (layer.UseDeltaCameraX)
					TileBaseX = (CameraDeltaX * layer.Info[0].RelativeX + layer.Info[0].ConstantX * Frame) >> 8;
				else
					TileBaseX = (CameraX * layer.Info[0].RelativeX + layer.Info[0].ConstantX * Frame) >> 8;

				if (layer.UseDeltaCameraY)
					TileBaseY = (CameraDeltaY * layer.RelativeY + layer.ConstantY * Frame) >> 8;
				else
					TileBaseY = (CameraY * layer.RelativeY + layer.ConstantY * Frame) >> 8;

				TileBaseX -= layer.OffsetX;
				TileBaseY -= layer.OffsetY;

				// EndTileBaseX = 2 + ((TileBaseX + App->WIDTH) >> 4);
				// EndTileBaseY = 2 + ((TileBaseY + App->HEIGHT) >> 4);

				//int lWid = layer.Width;

				// int j;
				// int bufVal;
				int tBX = (TileBaseX >> 4) - 1;
				int tBW = 3 + (App->WIDTH >> 4);
				int tBH = 2 + (App->HEIGHT >> 4);
				int ix = tBX,
					iy = (TileBaseY >> 4),
					fx = 0,
					fy = 0,
					// th = (TileBaseY >> 4) + tBH,
					tw = tBX + tBW;
				int fullSize = tBW * tBH;
				int anID;
				for (int w = 0; w < fullSize; w++) {
					fx = ix;
					fy = iy;
					if (layer.Flags & 0x2) {
						if (fx < 0) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
						if (fx >= layer.Width) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
					}
					if (layer.Flags & 0x4) {
						if (fy < 0) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
						if (fy >= layer.Height) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
					}

					while (fx < 0) fx += layer.Width;
					while (fx >= layer.Width) fx -= layer.Width;

					while (fy < 0) fy += layer.Height;
					while (fy >= layer.Height) fy -= layer.Height;

					baseX = (ix << 4) - TileBaseX;
					baseY = (iy << 4) - TileBaseY + layer.TileOffsetY[fx];

					tile = layer.Tiles[fx + fy * layer.Width];

					bool ColFlipX = ((tile >> 10) & 1) == 1;
					bool ColFlipY = ((tile >> 11) & 1) == 1;
					bool SolidTopA = ((tile >> 12) & 1) == 1;
					bool SolidLrbA = ((tile >> 13) & 1) == 1;
					bool SolidTopB = ((tile >> 14) & 1) == 1;
					bool SolidLrbB = ((tile >> 15) & 1) == 1;

					int colTypeA = ((tile >> 12) & 3);
					int colTypeB = ((tile >> 14) & 3);

					fullFlip = (tile >> 10) & 3;
					tile = tile & 0x3FF;

					if (tile != BlankTile) {
						//G->DrawSprite(TileSprite, 0, tile, baseX + 8, baseY + 8, 0, fullFlip);
						G->DrawSprite(TileSprite, 0, tile, baseX - 36, baseY + 8, 0, fullFlip);

						if (ViewTileCollision) {
							for (int c = 0; c < 16; c++) {
								int eex = c;
								if (ColFlipX) {
									eex = 15 - c;
								}

								int h1 = Data->tiles1[tile].Collision[c];
								int h2 = Data->tiles2[tile].Collision[c];

								if (BlankTile == 0x3FF && (Data->tiles1[tile].IsCeiling || Data->tiles2[tile].IsCeiling)) {
									h1 = 15 - h1;
									h2 = 15 - h2;
								}

								// Yellow - Tiles that are solid from the top. Used for platforms.
								// Red - Tiles that are solid from the bottom and sides. Usually for walls and ceilings.
								// White - Tiles that are solid all over. Usually for the ground.

								if (Player->Layer == 0 && (colTypeA & 1)) {
									//uint32_t col = colTypeB == 3 ? 0 : colTypeB == 2 ? 0xFFFF00 : 0xFFFFFF;
									uint32_t col = (SolidTopA && SolidLrbA) ? 0xFFFFFF : (SolidLrbA && !SolidTopA) ? 0xFF0000 : 0xFFFF00;

									if (Data->tiles1[tile].HasCollision[c]) {
										if (Data->tiles1[tile].IsCeiling ^ ColFlipY) {
											G->DrawRectangle(baseX + eex, baseY, 1, 16 - h1, col);
										}
										else {
											G->DrawRectangle(baseX + eex, baseY + h1, 1, 16 - h1, col);
										}
									}
								}
								else if (Player->Layer == 1 && (colTypeB & 1)) {
									if (Data->tiles2[tile].HasCollision[c]) {
										uint32_t col = (SolidTopB && SolidLrbB) ? 0xFFFFFF : (SolidLrbB && !SolidTopB) ? 0xFF0000 : 0xFFFF00;

										if (Data->tiles2[tile].IsCeiling ^ ColFlipY) {
											G->DrawRectangle(baseX + eex, baseY, 1, 16 - h2, col);
										}
										else {
											G->DrawRectangle(baseX + eex, baseY + h2, 1, 16 - h2, col);
										}
									}
								}
							}

							int mx = App->Input->MouseX;
							int my = App->Input->MouseY;
							if (mx >= baseX && my >= baseY && mx < baseX + 16 && my < baseY + 16) {
							}
						}
					}

					ix++;
					if (ix >= tw) {
						ix = tBX;
						iy++;
					}
				}

				if (layer.Info[0].DrawLayer == 1) {
					if (ManiaLevel)
						G->DoDeform = false;
				}
			}
		}
	}

	 if (DirectionStep != 0) {
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



	G->SetDrawFunc(1);
	// Sky
	G->SetDrawAlpha(SkyAlpha);
    G->DrawSprite(Horizon, 0, 1, App->WIDTH / 2, 0, 0, IE_NOFLIP);
    G->DrawSprite(Horizon, 0, 1, App->WIDTH / 2, 0, 0, IE_FLIPX);
	// Globe
    G->SetDrawAlpha(GlobeAlpha);
    G->DrawSprite(Horizon, 0, 0, App->WIDTH / 2, 0, 0, IE_NOFLIP);
    G->DrawSprite(Horizon, 0, 0, App->WIDTH / 2, 0, 0, IE_FLIPX);
    G->SetDrawFunc(0);
    G->SetDrawAlpha(0xFF);


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
			if (collectableType == (0x80 | BSS_SPHERE_RED)) {
				 transparent = true;
				collectableType  &= 0x7F;
			}

			if (collectableType == BSS_SPHERE_RED)
				collectableType = 5;
			else if (collectableType == BSS_SPHERE_BLUE)
				collectableType = 4;
			else if (collectableType == BSS_SPHERE_BUMPER)
				collectableType = 6;
			else if (collectableType == BSS_SPHERE_YELLOW)
				collectableType = 7;
			else if (collectableType == BSS_SPHERE_GREEN)
				collectableType = 8;
			else if (collectableType == BSS_SPHERE_PINK	)
				collectableType = 9;
			else if (collectableType == BSS_SPHERE_RING)
				needsResize = collectableType = 12;
			else if (collectableType == BSS_SPHERE_EMERALD)
				collectableType = 11;

			if (transparent)
				G->SetDrawAlpha(0x80);
			else
				G->SetDrawAlpha(0xFF);

			//'Fix'
			if (collectableType >= 0x10) collectableType = 0;

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

				if (GameState == 3 && collectableType != 11) {
					finalPosY += Timer1;
					Timer1++;
				}

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

	//Player Shadows
	G->SetDrawAlpha(0x80);
	G->DrawSprite(GlobeSpin, 1, 0, App->WIDTH / 2, 0xA0, 0, IE_NOFLIP);
	G->SetDrawAlpha(0xFF);

	//Player Sprites
	if (PlayerZ == 0 && DropDash == -2) {
		if (PlayerMaxSpeed == 0 || PlayerWaitMovementTimer != 0) //Still
			G->DrawSprite(Players, 0, 0, App->WIDTH / 2, 0xAA, 0, IE_NOFLIP);
		else //Moving
			G->DrawSprite(Players, 1, ((Frame * IMath::sign(PlayerSpeed) / 2) % 12 + 12) % 12, App->WIDTH / 2, 0xAA, 0, IE_NOFLIP);
	}
	else { //Ball
		G->DrawSprite(Players, 2, ((Frame * IMath::max(16, IMath::abs(PlayerSpeed)) / 32) % 12 + 12) % 12, App->WIDTH / 2, 0xAA + (PlayerZ >> 17), 0, IE_NOFLIP);
	}

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

	if (EventFlag == BSS_EVENT_START)
	{
		G->DrawSprite(Objects, StartMessageAnim, 0, App->WIDTH / 2 - Timer1, App->HEIGHT / 2, 0, IE_NOFLIP);
		G->DrawSprite(Objects, StartMessageAnim, 1, App->WIDTH / 2 + Timer1, App->HEIGHT / 2, 0, IE_NOFLIP);
	}
	if (EventFlag == BSS_EVENT_PERFECT)
	{
		G->DrawSprite(Objects, PerfectMessageAnim, 0, App->WIDTH / 2 - Timer1, App->HEIGHT / 2, 0, IE_NOFLIP);
		G->DrawSprite(Objects, PerfectMessageAnim, 1, App->WIDTH / 2 + Timer1, App->HEIGHT / 2, 0, IE_NOFLIP);
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

PUBLIC void Level_SpecialStage::Cleanup() {
#define CLEANUP(name) if (name) { printf("%s\n", #name); name->Cleanup(); delete name; name = NULL; }

	LevelScene::Cleanup();

	Memory::Free(PinkSphereX);
	Memory::Free(PinkSphereY);
	Memory::Free(Layout);
	Memory::Free(LayoutBackup);
	Memory::Free(LayoutCopy);
	Memory::Free(LayoutExtra);

}
