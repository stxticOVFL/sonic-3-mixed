#if INTERFACE
#include <Engine/IScene.h>
#include <Engine/ISprite.h>

class Scene_DataSelect : public IScene {
public:
	int selected = 0;
	int viewOffX = 0;
	ISprite* MenuSprite = NULL;
	ISprite* SaveIconsSprite = NULL;
	ISprite* SaveSelectSprite = NULL;
	ISprite* SuperButtonsSprite = NULL;
	ISprite* TextSprite = NULL;

	int frame = 0;
	int FrameCircle = 0;
	int FrameZigzag = 0;
	int FrameZigzagRed = 0;
	int FrameZigzagBlue = 0;
	int CharacterFlag = 0;
	int PartnerFlag = 0xFF;
    int Mode = 0;
	const char* ModeName = "Classic Mode";
};
#endif

#include <Game/LevelScene.h>
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

#include <Game/Levels/SpecialStage.h>

#include <Game/Levels/ALZ.h>
#include <Game/Levels/BPZ.h>
#include <Game/Levels/CGZ.h>
#include <Game/Levels/DPZ.h>
#include <Game/Levels/EMZ.h>
#include <Game/Levels/ASZ.h>

#include <Game/Scenes/MainMenu.h>
#include <Game/Scenes/LevelSelect.h>

#include <Game/Scenes/DataSelect.h>

#include <Game/SaveGame.h>

const char* LevelLabels[20] = {
	"AIZ",
	"HCZ",
	"MGZ",
	"CNZ",
	"ICZ",
	"LBZ",

	"MHZ",
	"FBZ",
	"SOZ",
	"LRZ",
	"HPZ",
	"SSZ",
	"DEZ",
	"TDZ",

	"ALZ",
	"BPZ",
	"CGZ",
	"DPZ",
	"EMZ",

	"SSZ",
};

bool GoBack = false;

bool PhantomSavefileStates[36];

PUBLIC Scene_DataSelect::Scene_DataSelect(IApp* app, IGraphics* g, int m) {
	App = app;
	G = g;
	Mode = m;
	Sound::Audio = App->Audio;
	Sound::Init();
	SaveGame::Init();

	//Please don't hate me for this bruddas - Ducky wucky
	if (Mode >= 1)
	{
		if (!Sound::SoundBank[0xFF] || strcmp(Sound::SoundBank[0xFF]->Name, "Mixed/Music/Invincible.ogg")) Sound::SoundBank[0xFF] = new ISound("Mixed/Music/Invincible.ogg", true);
		if (!Sound::SoundBank[0xFE] || strcmp(Sound::SoundBank[0xFE]->Name, "Mixed/Music/Sneakers.ogg")) Sound::SoundBank[0xFE] = new ISound("Mixed/Music/Sneakers.ogg", true);
		if (!Sound::SoundBank[0xFD] || strcmp(Sound::SoundBank[0xFD]->Name, "Mixed/Music/Drowning.ogg")) Sound::SoundBank[0xFD] = new ISound("Mixed/Music/Drowning.ogg", true);
		if (!Sound::SoundBank[0xFC] || strcmp(Sound::SoundBank[0xFC]->Name, "Mixed/Music/ActComplete.ogg")) Sound::SoundBank[0xFC] = new ISound("Mixed/Music/ActComplete.ogg", true);
		if (!Sound::SoundBank[0xFB] || strcmp(Sound::SoundBank[0xFB]->Name, "Mixed/Music/1up.ogg")) Sound::SoundBank[0xFB] = new ISound("Mixed/Music/1up.ogg", false);

		if (!Sound::SoundBank[0xF2] || strcmp(Sound::SoundBank[0xF2]->Name, "Mixed/Music/Knuckles.ogg")) Sound::SoundBank[0xF2] = new ISound("Mixed/Music/Knuckles.ogg", true);
		if (!Sound::SoundBank[0xF1] || strcmp(Sound::SoundBank[0xF1]->Name, "Mixed/Music/Miniboss.ogg")) Sound::SoundBank[0xF1] = new ISound("Mixed/Music/Miniboss.ogg", true);
		if (!Sound::SoundBank[0xF0] || strcmp(Sound::SoundBank[0xF0]->Name, "Mixed/Music/Boss.ogg")) Sound::SoundBank[0xF0] = new ISound("Mixed/Music/Boss.ogg", true);
	}
	else
	{
		if (!Sound::SoundBank[0xFF] || strcmp(Sound::SoundBank[0xFF]->Name, "Classic/Music/Invincible.ogg")) Sound::SoundBank[0xFF] = new ISound("Classic/Music/Invincible.ogg", true);
		if (!Sound::SoundBank[0xFE] || strcmp(Sound::SoundBank[0xFE]->Name, "Classic/Music/Sneakers.ogg")) Sound::SoundBank[0xFE] = new ISound("Classic/Music/Sneakers.ogg", true);
		if (!Sound::SoundBank[0xFD] || strcmp(Sound::SoundBank[0xFD]->Name, "Classic/Music/Drowning.ogg")) Sound::SoundBank[0xFD] = new ISound("Classic/Music/Drowning.ogg", true);
		if (!Sound::SoundBank[0xFC] || strcmp(Sound::SoundBank[0xFC]->Name, "Classic/Music/ActComplete.ogg")) Sound::SoundBank[0xFC] = new ISound("Classic/Music/ActComplete.ogg", true);
		if (!Sound::SoundBank[0xFB] || strcmp(Sound::SoundBank[0xFB]->Name, "Classic/Music/1up.ogg")) Sound::SoundBank[0xFB] = new ISound("Classic/Music/1up.ogg", false);

		if (!Sound::SoundBank[0xF2] || strcmp(Sound::SoundBank[0xF2]->Name, "Classic/Music/Knuckles.ogg")) Sound::SoundBank[0xF2] = new ISound("Classic/Music/Knuckles.ogg", true);
		if (!Sound::SoundBank[0xF1] || strcmp(Sound::SoundBank[0xF1]->Name, "Classic/Music/Miniboss.ogg")) Sound::SoundBank[0xF1] = new ISound("Classic/Music/Miniboss.ogg", true);
		if (!Sound::SoundBank[0xF0] || strcmp(Sound::SoundBank[0xF0]->Name, "Classic/Music/Boss.ogg")) Sound::SoundBank[0xF0] = new ISound("Classic/Music/Boss.ogg", true);
	}
}

PUBLIC void Scene_DataSelect::Init() {
	int at = 0;
	if (Sound::SoundBank[0]) {
		char* ct = strstr(Sound::SoundBank[0]->Name, "Menu");
		if (ct != NULL)
			at = Sound::SoundBank[0]->GetPosition();
		//free(ct);
	}
	App->Audio->ClearMusic();
	Sound::PlayStream(0, "Music/Menu3.ogg", true, 0, at, true);

	App->Input->UseTouchController = false;

	if (!MenuSprite) {
		MenuSprite = new ISprite("Sprites/UI/MainMenu.gif", App);
		MenuSprite->LoadAnimation("Sprites/UI/MainMenu.bin");
		MenuSprite->SetTransparentColorIndex(0x0);
		MenuSprite->UpdatePalette();
	}
	if (!SuperButtonsSprite) {
		SuperButtonsSprite = new ISprite("Sprites/UI/SuperButtons.gif", App);
		SuperButtonsSprite->LoadAnimation("Sprites/UI/SuperButtons.bin");
		SuperButtonsSprite->SetPalette(1, 0x282028);
		SuperButtonsSprite->UpdatePalette();
	}
	if (!TextSprite) {
		TextSprite = new ISprite("Sprites/UI/CreditsText.gif", App);
		TextSprite->LoadAnimation("Sprites/UI/CreditsText.bin");
		TextSprite->UpdatePalette();
	}
	if (!SaveIconsSprite) {
		ISprite::Animation an;
		SaveIconsSprite = new ISprite("Sprites/UI/SaveIcons.gif", App);

		an.Name = (char*)"Static";
		an.FrameCount = 4;
		an.Frames = (ISprite::AnimFrame*)malloc(an.FrameCount * sizeof(ISprite::AnimFrame));
		for (int i = 0; i < an.FrameCount; i++) {
			int fi = i + 1;
			ISprite::AnimFrame ts_af;
			ts_af.X = (fi % 6) * 80;
			ts_af.Y = (fi / 6) * 56;
			ts_af.W = 80; ts_af.H = 56; ts_af.OffX = -40; ts_af.OffY = -28;
			an.Frames[i] = ts_af;
			G->MakeFrameBufferID(SaveIconsSprite, an.Frames + i);
		}
		SaveIconsSprite->Animations.push_back(an);

		an.Name = (char*)"New";
		an.FrameCount = 1;
		an.Frames = (ISprite::AnimFrame*)malloc(an.FrameCount * sizeof(ISprite::AnimFrame));
		for (int i = 0; i < an.FrameCount; i++) {
			int fi = i + 0;
			ISprite::AnimFrame ts_af;
			ts_af.X = (fi % 6) * 80;
			ts_af.Y = (fi / 6) * 56;
			ts_af.W = 80; ts_af.H = 56; ts_af.OffX = -40; ts_af.OffY = -28;
			an.Frames[i] = ts_af;
			G->MakeFrameBufferID(SaveIconsSprite, an.Frames + i);
		}
		SaveIconsSprite->Animations.push_back(an);

		an.Name = (char*)"Zone Images (Classic)";
		an.FrameCount = 14;
		an.Frames = (ISprite::AnimFrame*)malloc(an.FrameCount * sizeof(ISprite::AnimFrame));
		for (int i = 0; i < an.FrameCount; i++) {
			int fi = i + 5;
			if (fi == 12) fi = 26;
			ISprite::AnimFrame ts_af;
			ts_af.X = (fi % 6) * 80;
			ts_af.Y = (fi / 6) * 56;
			ts_af.W = 80; ts_af.H = 56; ts_af.OffX = -40; ts_af.OffY = -28;
			an.Frames[i] = ts_af;
			G->MakeFrameBufferID(SaveIconsSprite, an.Frames + i);
		}
		SaveIconsSprite->Animations.push_back(an);

		an.Name = (char*)"Zone Images (Original)";
		an.FrameCount = 14;
		an.Frames = (ISprite::AnimFrame*)malloc(an.FrameCount * sizeof(ISprite::AnimFrame));
		for (int i = 0; i < an.FrameCount; i++) {
			int fi = i + 5;
			ISprite::AnimFrame ts_af;
			ts_af.X = (fi % 6) * 80;
			ts_af.Y = (fi / 6) * 56;
			ts_af.W = 80; ts_af.H = 56; ts_af.OffX = -40; ts_af.OffY = -28;
			an.Frames[i] = ts_af;
			G->MakeFrameBufferID(SaveIconsSprite, an.Frames + i);
		}
		SaveIconsSprite->Animations.push_back(an);

		an.Name = (char*)"Clear Images";
		an.FrameCount = 7;
		an.Frames = (ISprite::AnimFrame*)malloc(an.FrameCount * sizeof(ISprite::AnimFrame));
		for (int i = 0; i < an.FrameCount; i++) {
			int fi = i + 19;
			ISprite::AnimFrame ts_af;
			ts_af.X = (fi % 6) * 80;
			ts_af.Y = (fi / 6) * 56;
			ts_af.W = 80; ts_af.H = 56; ts_af.OffX = -40; ts_af.OffY = -28;
			an.Frames[i] = ts_af;
			G->MakeFrameBufferID(SaveIconsSprite, an.Frames + i);
		}
		SaveIconsSprite->Animations.push_back(an);
	}
	if (!SaveSelectSprite) {
		SaveSelectSprite = new ISprite("Sprites/UI/SaveSelectEN.gif", App);
		SaveSelectSprite->LoadAnimation("Sprites/UI/SaveSelect.bin");
	}

	FadeTimerMax = 30;
	FadeIn = true;

	if (Mode == 0)
		ModeName = "Classic Mode";
	else if (Mode == 1)
		ModeName = "Mixed Mode";
	else if (Mode == 2)
		ModeName = "Locked On";

	Discord_UpdatePresence("Data Select", ModeName, "icon", false);
}

bool MobileScrolling = false;
bool MobileScrollStart = false;
bool MobileScrollMoved = false;
int  MobileScrollSpeed = 0x00;
int  MobileScrollTouchStart = 0;
int  MobileScrollLastTouch = 0;
int* MobileScrollVariable = NULL;
int  MobileScrollLeftBound = 0;
int  MobileScrollRightBound = 7 * 10000;

int  ElementY = 40;
int  ElementH = 150;

PUBLIC void Scene_DataSelect::Update() {
	bool CONFIRM_PRESSED = App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED];
	bool CONFIRM_DOWN = App->Input->GetControllerInput(0)[IInput::I_CONFIRM] || App->Input->MouseDown;
	bool BACK_PRESSED = App->Input->GetControllerInput(0)[IInput::I_DENY_PRESSED];

	int mx = App->Input->MouseX;
	int my = App->Input->MouseY;
	if (App->Input->MouseReleased && mx < 128 && my > ElementY + ElementH)
		BACK_PRESSED = true;

	if (App->Input->MouseDown && !MobileScrollStart && my >= ElementY && my < ElementY + ElementH) {
		MobileScrollVariable = &viewOffX;
		MobileScrollStart = true;
		MobileScrollTouchStart = *MobileScrollVariable;
		MobileScrollLastTouch = mx;
		MobileScrollMoved = false;
	}
	if (MobileScrollVariable) {
		if (MobileScrollStart) {
			if (App->Input->MouseDown) {
				MobileScrollSpeed = (MobileScrollLastTouch - mx) << 8;
				MobileScrollLastTouch = mx;

				if (*MobileScrollVariable < MobileScrollLeftBound)
					MobileScrollSpeed /= IMath::abs(MobileScrollLeftBound - *MobileScrollVariable) / 32;
				if (*MobileScrollVariable > MobileScrollRightBound)
					MobileScrollSpeed /= IMath::abs(MobileScrollRightBound - *MobileScrollVariable) / 32;

				if (IMath::abs(MobileScrollTouchStart - *MobileScrollVariable) >= 0x8)
					MobileScrollMoved = true;
			}
			else {
				MobileScrollStart = false;

				if (!MobileScrollMoved) {
					CONFIRM_PRESSED = true;
				}
			}
		}
		if (MobileScrolling && !App->Input->MouseDown) {
			MobileScrollSpeed += (0 - MobileScrollSpeed) / 16;
			if (IMath::abs(MobileScrollSpeed) < 0x100)
				MobileScrollSpeed = 0;

			if (*MobileScrollVariable < 0)
				MobileScrollSpeed = (0 - *MobileScrollVariable) / 8;
		}

		*MobileScrollVariable += MobileScrollSpeed;
		if (IMath::abs(MobileScrollLeftBound - *MobileScrollVariable) < 0x100)
			*MobileScrollVariable = MobileScrollLeftBound;
		if (IMath::abs(MobileScrollRightBound - *MobileScrollVariable) < 0x100)
			*MobileScrollVariable = MobileScrollRightBound;

		if (MobileScrolling && App->Input->MouseDown) {
			if (selected != (*MobileScrollVariable + 5000) / 10000) {
				CharacterFlag = 0;
				PartnerFlag = 0xFF;
				selected = (*MobileScrollVariable + 5000) / 10000;
				if (selected < 0)
					selected = 0;
				if (selected > 11)
					selected = 11;
			}
		}
	}

	if (FadeTimer == -1 && FadeTimerMax > 1)
		FadeTimer = FadeTimerMax;
	if (FadeTimer > 0) {
		FadeTimer--;
		if (!FadeIn)
			G->SetFade(int((1.0 - float(FadeTimer - 1) / FadeTimerMax) * FadeMax));
		else
			G->SetFade(int((float(FadeTimer) / FadeTimerMax) * FadeMax));
	}

	// Do Fade actions
	if (FadeTimer == 0) {
		FadeTimer = -1;
		FadeTimerMax = 0;

		if (!FadeIn) {
			if (GoBack) {
				Scene_MainMenu* NextScene = new Scene_MainMenu(App, G);
				NextScene->MenuSprite = MenuSprite;
				NextScene->SuperButtonsSprite = SuperButtonsSprite;
				NextScene->TextSprite = TextSprite;

				// Make these NULL so they don't get accidentally cleaned up later
				MenuSprite = NULL;
				SuperButtonsSprite = NULL;
				TextSprite = NULL;

				App->NextScene = NextScene;
			}
			else {
				SaveGame::CurrentSaveFile = selected + (12 * (Mode));

				int i = SaveGame::CurrentSaveFile;
				if (SaveGame::Savefiles[i].State == 0) {
					SaveGame::InitializeSaveGame();
					SaveGame::CurrentCharacterFlag = CharacterFlag;
					SaveGame::CurrentPartnerFlag = PartnerFlag;
					SaveGame::Savefiles[i].CharacterFlag = CharacterFlag;
					SaveGame::Savefiles[i].PartnerFlag = PartnerFlag;

					SaveGame::Savefiles[i].State = 1;
					SaveGame::Flush();
				}
				else {
					SaveGame::CurrentCharacterFlag = SaveGame::Savefiles[i].CharacterFlag;
					SaveGame::CurrentPartnerFlag = SaveGame::Savefiles[i].PartnerFlag;
				}

				SaveGame::CurrentUsedZoneRings = SaveGame::Savefiles[i].UsedZoneRings[SaveGame::Savefiles[i].LastZoneID];
				SaveGame::CurrentEmeralds = SaveGame::Savefiles[i].Emeralds;

				if (SaveGame::CurrentSaveFile < 12)
				{
					//Classic
					SaveGame::Savefiles[i].Mode = 0;
				}
				else if (SaveGame::CurrentSaveFile >= 12 && SaveGame::CurrentSaveFile < 24)
				{
					//Mixed
					SaveGame::Savefiles[i].Mode = 1;
				}
				else
				{
					//Locked on
					SaveGame::Savefiles[i].Mode = 2;
				}

				SaveGame::CurrentMode = SaveGame::Savefiles[i].Mode;

				SaveGame::Flush();
				switch (SaveGame::Savefiles[i].LastZoneID) {
					LevelScene* ls;
				case 0:
					App->NextScene = new Level_AIZ(App, G, 1);
					break;
				case 1:
					App->NextScene = new Level_HCZ(App, G, 1);
					break;
				case 2:
					App->NextScene = new Level_MGZ(App, G, 1);
					break;
				case 3:
					App->NextScene = new Level_CNZ(App, G, 1);
					break;
				case 4:
					App->NextScene = new Level_ICZ(App, G, 1);
					break;
				case 5:
					App->NextScene = new Level_LBZ(App, G, 1);
					break;
				case 6:
					App->NextScene = new Level_MHZ(App, G, 1);
					break;
				case 7:
					App->NextScene = new Level_FBZ(App, G, 1);
					break;
				case 8:
					App->NextScene = new Level_SOZ(App, G, 1);
					break;
				case 9:
					App->NextScene = new Level_LRZ(App, G, 1);
					break;
				case 10:
					App->NextScene = new Level_HPZ(App, G, 1);
					break;
				case 11:
					App->NextScene = new Level_SSZ(App, G, 1);
					break;
				case 12:
					App->NextScene = new Level_DEZ(App, G, 1);
					break;
				case 13:
					App->NextScene = new Level_TDZ(App, G, 1);
					break;
				case 14:
					App->NextScene = new Level_ALZ(App, G, 1);
					break;
				case 15:
					App->NextScene = new Level_BPZ(App, G, 1);
					break;
				case 16:
					App->NextScene = new Level_CGZ(App, G, 1);
					break;
				case 17:
					App->NextScene = new Level_DPZ(App, G, 1);
					break;
				case 18:
					App->NextScene = new Level_EMZ(App, G, 1);
					break;
				default:
					SaveGame::CurrentEmeralds = 0x0000;
					ls = new LevelScene(App, G);
					Sound::SoundBank[0] = new ISound("Stages/MSZ/Act2.ogg", true);
					Sound::Audio->LoopPoint[0] = 179390 / 4;
					ls->Str_StageBin = "Stages/MSZ/StageConfig.bin";
					ls->Str_TileConfigBin = "Stages/MSZ/TileConfig.bin";
					ls->Str_SceneBin = "Stages/MSZ/Scene2.bin";
					ls->Str_TileSprite = "Stages/MSZ/16x16Tiles.gif";
					ls->PlayerStartX = 160;
					ls->PlayerStartY = 1328;
					SaveGame::CurrentMode = 1; //Force it to mixed mode
					ls->ZoneID = 1;
					ls->VisualAct = 2;
					sprintf(ls->LevelName, "BENT LETTUCE");
					sprintf(ls->LevelNameDiscord, "Bent Lettuce Zone");
					App->NextScene = ls;
					break;
				}
			}
		}
	}
	else if (FadeTimer < 0) {
		if (App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED]) {
			if (selected > 0) {
				selected--;
				CharacterFlag = 0;
				PartnerFlag = 0xFF;
			}

			Sound::Play(Sound::SFX_MENUBLEEP);

			MobileScrolling = true;
		}
		if (App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED]) {
			if (selected < 11) {
				selected++;
				CharacterFlag = 0;
				PartnerFlag = 0xFF;
			}

			Sound::Play(Sound::SFX_MENUBLEEP);

			MobileScrolling = true;
		}

		if (App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED]) {
			if (CharacterFlag < 4)
				CharacterFlag++;
			else
				CharacterFlag = 0;

			Sound::Play(Sound::SFX_MENUBLEEP);

			MobileScrolling = true;
		}
		if (App->Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED]) {
			if (CharacterFlag > 0)
				CharacterFlag--;
			else
				CharacterFlag = 4;

			Sound::Play(Sound::SFX_MENUBLEEP);

			MobileScrolling = true;
		}

		//Deleting a Save
		//Big Anus bad but stfu it works
		if (App->Input->GetControllerInput(0)[IInput::I_PAUSE_PRESSED]) {
			SaveGame::Savefiles[selected + (12 * Mode)].CharacterFlag = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].Continues = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].Emeralds = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].LastZoneID = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].Lives = 3;
			SaveGame::Savefiles[selected + (12 * Mode)].Mode = Mode;
			SaveGame::Savefiles[selected + (12 * Mode)].PartnerFlag = 0xFF;
			SaveGame::Savefiles[selected + (12 * Mode)].Score = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].State = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].TargetScore = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[0] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[1] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[2] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[3] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[4] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[5] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[6] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[7] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[8] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[9] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[10] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[11] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[12] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[13] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[14] = 0;
			SaveGame::Savefiles[selected + (12 * Mode)].UsedZoneRings[15] = 0;
			SaveGame::Flush();
			Sound::Play(Sound::SFX_SPECIALSTAGE_EXIT);
		}

		if (App->Input->GetControllerInput(0)[IInput::I_EXTRA_PRESSED]) {
			if (PartnerFlag < 4 && PartnerFlag != 0xFF)
			{
				PartnerFlag++;
			}
			else
			{
				if (PartnerFlag == 0xFF)
				{
					PartnerFlag = 0;
				}
				else
				{
					PartnerFlag = 0xFF;
				}
			}

			Sound::Play(Sound::SFX_MENUBLEEP);

			MobileScrolling = true;
		}
		if (App->Input->GetControllerInput(0)[IInput::I_EXTRA2_PRESSED]) {
			if (PartnerFlag > 0 && PartnerFlag != 0xFF)
			{
				PartnerFlag--;
			}
			else
			{
				if (PartnerFlag == 0xFF)
				{
					CharacterFlag = 4;
				}
				else
				{
					PartnerFlag = 0xFF;
				}
			}

			Sound::Play(Sound::SFX_MENUBLEEP);

			MobileScrolling = true;
		}

		if (CONFIRM_PRESSED) {
			if (!MobileScrolling) {
				MobileScrolling = true;
			}
			else {
				Sound::Play(Sound::SFX_MENUACCEPT);

				FadeIn = false;
				FadeTimerMax = 30;
				App->Audio->FadeMusic(0.5);
				GoBack = false;
			}
		}
		if (BACK_PRESSED) {
			GoBack = true;
			FadeIn = false;
			FadeTimerMax = 30;
		}
	}

	if (!MobileScrolling || !App->Input->MouseDown)
		viewOffX += (selected * 10000 - viewOffX) / 2;

	FrameCircle = (FrameCircle + 1) & 0xFF;
	FrameZigzag = (FrameZigzag + 1) % (40 * 4);
	FrameZigzagRed = (FrameZigzagRed + 1) % (117 * 4);
	FrameZigzagBlue = (FrameZigzagBlue + 1) % (110 * 4);

	frame++;
	if (frame > (32 << 1))
		frame = 0;

	if (App->Input->MousePressed)
		MobileScrolling = true;
}

PUBLIC void Scene_DataSelect::Render() {
	G->SetFilter(IE_FILTER_FADEABLE);

	int cenX = App->WIDTH / 2;
	int cenY = App->HEIGHT / 2;

	// BG
	G->DrawRectangle(0, 0, App->WIDTH, App->HEIGHT, 0xF0F0F0);

	// Zigzags
	int pX = cenX - (260 - 186) - 5;
	int pY = 223 - 5;
	G->SetClip(0, App->HEIGHT - 60, 293, 60);
	G->DrawSprite(MenuSprite, 16, 0, pX - (FrameZigzag / 4), pY - (FrameZigzag / 4), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 16, 0, pX - (FrameZigzag / 4) + 40, pY - (FrameZigzag / 4) + 40, 0, IE_NOFLIP);
	G->ClearClip();

	G->SetClip(cenX - (260 - 131), 0, 100, 84);
	pX = cenX - (260 - 180) + FrameZigzagBlue / 4;
	pY = 32 + FrameZigzagBlue / 4;
	G->DrawSprite(MenuSprite, 16, 1, pX, pY, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 16, 1, pX - 110, pY - 110, 0, IE_NOFLIP);
	G->ClearClip();

	pX = cenX - (260 - 322) + FrameZigzagRed / 4;
	pY = 80 - FrameZigzagRed / 4;
	G->DrawSprite(MenuSprite, 16, 2, pX, pY, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 16, 2, pX - 117, pY + 117, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 16, 2, pX - 234, pY + 234, 0, IE_NOFLIP);

	// Decorations
	int yup;

	// Red/Black Ovals
	yup = IMath::sinHex(FrameCircle);
	G->DrawSprite(MenuSprite, 11, 0, cenX - (260 - 116) + (yup >> 14), 25, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 11, 1, cenX - (260 - 116) - (yup >> 14), 25, 0, IE_NOFLIP);
	// Green/Black Ovals
	yup = IMath::sinHex(FrameCircle * 2 + 0x35);
	G->DrawSprite(MenuSprite, 11, 2, cenX - (260 - 246) + (yup >> 14), 185, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 11, 3, cenX - (260 - 246) - (yup >> 14), 185, 0, IE_NOFLIP);
	// Dotted circles
	G->DrawSprite(MenuSprite, 15, 0, App->WIDTH, 24, FrameCircle, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 15, 0, App->WIDTH, App->HEIGHT - 24, FrameCircle, IE_NOFLIP);

	// Dotted lines
	yup = IMath::sinHex(FrameCircle * 2 + 0x29);
	G->DrawSprite(MenuSprite, 14, 0, cenX - (260 - 323) - (yup >> 14), 94 + (yup >> 13), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 14, 1, cenX - (260 - 317) + (yup >> 14), 88 - (yup >> 13), 0, IE_NOFLIP);

	// Diamonds
	yup = IMath::sinHex(FrameCircle * 2 + 0x37);
	G->DrawSprite(MenuSprite, 12, 2, cenX - (260 - 134), 131 + (yup >> 15), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 12, 1, cenX - (260 - 124), 131 - (yup >> 15), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 12, 0, cenX - (260 - 114), 131 + (yup >> 15), 0, IE_NOFLIP);
	// Tilted Squares
	G->DrawSprite(MenuSprite, 13, 0, cenX - (260 - 253), 51 - (yup >> 15), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 13, 2, cenX - (260 - 265), 47 - (yup >> 15), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 13, 1, cenX - (260 - 259), 49 + (yup >> 15), 0, IE_NOFLIP);

	int blackGirth = 32;

	// Black
	G->DrawSprite(MenuSprite, 1, 0, App->WIDTH - 424, 0, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 1, 1, App->WIDTH - 424, App->HEIGHT, 0, IE_NOFLIP);
	//G->DrawSprite(MenuSprite, 1, 2, 0, 0, 0, IE_NOFLIP);

	G->DrawRectangle(0, 0, App->WIDTH - 424 + 128, 16, 0);
	G->DrawRectangle(0, App->HEIGHT - 24, App->WIDTH - 424 + 128, 24, 0);
	/*
	G->DrawRectangle(0, 0, blackGirth, App->HEIGHT, 0x000000);
	G->DrawRectangle(App->WIDTH - blackGirth, 0, blackGirth, App->HEIGHT, 0x000000);
	// Triangles
	for (int i = 0; i <= 12; i++) G->DrawSprite(MenuSprite, 1, 3, blackGirth, i * 20 - 20 + (frame >> 1), 0, IE_NOFLIP);
	for (int i = 0; i <= 12; i++) G->DrawSprite(MenuSprite, 1, 3, App->WIDTH - blackGirth, i * 20 - (frame >> 1), 0, IE_FLIPX);
	//*/

	// Menu Title
	G->DrawSprite(MenuSprite, 9, (1 + Mode), App->WIDTH, 12, 0, IE_NOFLIP);
	//G->DrawSprite(MenuSprite, 10, 0, App->WIDTH - 12, 12, 0, IE_NOFLIP);

	// For shape masking, make a separate framebuffer and when applying pixel, compare to that buffer
	int j = 0;
	for (int i = (12 * Mode); i < (12 * Mode) + 12; i++) {
		int myX = App->WIDTH / 2 - 40 + j * 100 - (viewOffX + 50) / 100;
		int myY = ElementY;

		// Shadow
		myX += 3;
		myY += 3;
		G->SetDrawAlpha(0x80);
		G->DrawRectangle(myX - 2, myY - 2, 80 + 4, 56 + 6, 0x000000);
		G->DrawRectangleStroke(myX - 5, myY - 5, 80 + 10, ElementH + 10, 0x000000);
		G->DrawRectangleStroke(myX - 4, myY - 4, 80 + 8, ElementH + 8, 0x000000);
		G->DrawRectangleStroke(myX - 3, myY - 3, 80 + 6, ElementH + 6, 0x000000);
		G->SetDrawAlpha(0xFF);
		myX -= 3;
		myY -= 3;

		// Zone Image
		G->DrawRectangle(myX - 2, myY - 2, 80 + 4, 56 + 6, 0x000000);
		switch (SaveGame::Savefiles[i].State) {
			int txtW;
			const char* lvlN;
		case 0:
			G->DrawSprite(SaveIconsSprite, 1, 0, myX + 80 / 2, myY + 56 / 2, 0, 0);
			break;
		case 1:
			//G->DrawRectangle(myX, myY, 80, 56, 0x4141F2);
			if (i == (selected + (12 * Mode)))
				G->DrawSprite(SaveIconsSprite, 2, SaveGame::Savefiles[i].LastZoneID, myX + 80 / 2, myY + 56 / 2, 0, IE_NOFLIP);
			else
				G->DrawSprite(SaveIconsSprite, 0, (frame >> 2) % 3, myX + 80 / 2, myY + 56 / 2, 0, ((frame >> 2)) % 3);
			///*
			lvlN = LevelLabels[SaveGame::Savefiles[i].LastZoneID];
			txtW = G->MeasureTextSprite(TextSprite, 6, 'A', lvlN);
			G->DrawRectangle(myX + 80 - txtW - 6, myY + 56 - 17, txtW + 6, 17, 0x000000);
			G->DrawTextSprite(TextSprite, 6, 'A', myX + 80 - txtW - 2, myY + 56 - 8, lvlN);
			//*/
			break;
		case 2:
			G->DrawSprite(SaveIconsSprite, 4, 6, myX + 80 / 2, myY + 56 / 2, 0, 0);
			break;
		}

		int cf = CharacterFlag;
		int pf = PartnerFlag;
		if (i != (selected + (12 * Mode)) || SaveGame::Savefiles[i].State > 0)
		{
			if (!PhantomSavefileStates[i] && SaveGame::Savefiles[i].State <= 0)
			{
				pf = SaveGame::Savefiles[i].PartnerFlag = 0xFF;
			}
			PhantomSavefileStates[i] = true;
			cf = SaveGame::Savefiles[i].CharacterFlag;
			pf = SaveGame::Savefiles[i].PartnerFlag;
		}

		//if we have a buddy
		if (pf != 0xFF)
		{
			//Partner Shadow
			G->DrawSprite(SaveSelectSprite, 20, pf, myX + 110 / 2 + 4, myY + 85 + 4, 0, IE_FLIPX);
			//Main Character Shadow
			G->DrawSprite(SaveSelectSprite, 20, cf, myX + 40 / 2 + 4, myY + 85 + 4, 0, 0);

			//Partner Character
			G->DrawSprite(SaveSelectSprite, 19, pf, myX + 110 / 2, myY + 85, 0, IE_FLIPX);
			//Main Character
			G->DrawSprite(SaveSelectSprite, 19, cf, myX + 40 / 2, myY + 85, 0, 0);
		}
		else //no buddy
		{
			//Main Char Shadow
			G->DrawSprite(SaveSelectSprite, 20, cf, myX + 80 / 2 + 4, myY + 85 + 4, 0, 0);
			//Main Character
			G->DrawSprite(SaveSelectSprite, 19, cf, myX + 80 / 2, myY + 85, 0, 0);
		}
		// 4 - emeralds
		if (SaveGame::Savefiles[i].State > 0) {
			//Main Character
			G->DrawSprite(SaveSelectSprite, 3, SaveGame::Savefiles[i].CharacterFlag, myX + 80 / 2 - 10, myY + ElementH - 10, 0, 0);
			char lives[3];
			snprintf(lives, 3, "%d", SaveGame::Savefiles[i].Lives);
			G->DrawTextSprite(TextSprite, 6, '0' - 37, myX + 80 / 2 + 4, myY + ElementH - 10 + 1, lives);
		}

		// Emeralds
		G->DrawRectangle(myX - 2, myY + 110, 80 + 4, 20, 0x000000);
		for (int v = 0; v < 7; v++) {
			if (SaveGame::Savefiles[i].Emeralds >> v & 1)
				G->DrawSprite(SaveSelectSprite, 4, v, myX + 3 + v * 12, myY + 120, 0, 0);
			else
				G->DrawSprite(SaveSelectSprite, 4, 7, myX + 3 + v * 12, myY + 120, 0, 0);
		}

		// Border
		G->DrawRectangleStroke(myX - 5, myY - 5, 80 + 10, ElementH + 10, 0x000000);
		G->DrawRectangleStroke(myX - 4, myY - 4, 80 + 8, ElementH + 8, 0x000000);
		G->DrawRectangleStroke(myX - 3, myY - 3, 80 + 6, ElementH + 6, 0x000000);
		j++;
	}

	// Border
	int myX = App->WIDTH / 2 - 40;
	int myY = ElementY;
	if ((frame >> 4) & 1) {
		G->DrawRectangleStroke(myX - 5, myY - 5, 80 + 10, ElementH + 10, 0xE00000);
		G->DrawRectangleStroke(myX - 4, myY - 4, 80 + 8, ElementH + 8, 0xE00000);
		G->DrawRectangleStroke(myX - 3, myY - 3, 80 + 6, ElementH + 6, 0xE00000);
	}

	// TODO: When making controllers mappable, use those
	// 1 - Keyboard
	// 2 - Xbox
	// 3 - PS4
	// 4 - Switch
	// 5 - Saturn (Black)
	// 6 - Saturn (White)

	// Buttons
	bool Back = true;
	if (IApp::Mobile) {
		if (Back) {
			int ax = 8;
			int ay = App->HEIGHT - 8;
			int aheadsize = 32;
			Uint32 col = 0xFF3434;
			G->DrawTriangle(ax, ay, ax + aheadsize, ay - aheadsize, ax + aheadsize, ay, col);
			G->DrawRectangle(ax + aheadsize, ay - 20, 64, 20, col);
			G->DrawRectangle(ax + aheadsize + 64 - 24, ay - aheadsize + 4, 24, aheadsize - 4, col);
			G->DrawTextSprite(TextSprite, 6, 'A', ax + aheadsize / 2 + 32 - 16, ay - 10, "BACK");
		}
	}
	else {
		int drawX = 14;
		int CurrAni = 1;
		if (IApp::Platform == Platforms::Switch) {
			CurrAni = 4;
		}

		if (Back) {
			G->DrawSprite(SuperButtonsSprite, CurrAni, App->Input->ControllerMaps[0][IInput::I_DENY], drawX, App->HEIGHT - 12, 0, IE_NOFLIP);
			G->DrawTextSprite(TextSprite, 6, 'A', drawX + 16, App->HEIGHT - 12, "BACK");
			drawX += 16 + G->MeasureTextSprite(TextSprite, 6, 'A', "BACK") + 24;
		}

		G->DrawSprite(SuperButtonsSprite, CurrAni, App->Input->ControllerMaps[0][IInput::I_CONFIRM], drawX, App->HEIGHT - 12, 0, IE_NOFLIP);
		G->DrawTextSprite(TextSprite, 6, 'A', drawX + 16, App->HEIGHT - 12, "ACCEPT");
		drawX += 16 + G->MeasureTextSprite(TextSprite, 6, 'A', "ACCEPT") + 24;
	}
}

PUBLIC void Scene_DataSelect::Cleanup() {
#define CLEANUP(name) if (name) { name->Cleanup(); delete name; name = NULL; }

	// Do not clear music so we can keep it through menus
	// App->Audio->ClearMusic();
	// CLEANUP(Sound::SoundBank[0]);

	CLEANUP(MenuSprite);
	CLEANUP(SaveIconsSprite);
	CLEANUP(SaveSelectSprite);
	CLEANUP(SuperButtonsSprite);
	CLEANUP(TextSprite);
}