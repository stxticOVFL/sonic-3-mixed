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
//#include <Game/Levels/FBZ.h>
//#include <Game/Levels/SOZ.h>
//#include <Game/Levels/LRZ.h>
//#include <Game/Levels/HPZ.h>
//#include <Game/Levels/SSZ.h>
//#include <Game/Levels/DEZ.h>
//#include <Game/Levels/TDZ.h>
#include <Game/Levels/SpecialStage.h>

#include <Game/Scenes/MainMenu.h>
#include <Game/Scenes/LevelSelect.h>

#include <Game/Scenes/DataSelect.h>

#include <Game/SaveGame.h>

const char* LevelLabels[15] = {
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
	"SSZ",
};

bool GoBack = false;

PUBLIC Scene_DataSelect::Scene_DataSelect(IApp* app, IGraphics* g) {
	App = app;
	G = g;
	Sound::Audio = App->Audio;
	Sound::Init();
	SaveGame::Init();

	// Sound::SoundBank[0] = new ISound("Music/Mixed/SaveSelectTria.ogg", true);
	// Sound::Audio->LoopPoint[0] = 131859;
	if (!Sound::SoundBank[0] || strcmp(Sound::SoundBank[0]->Name, "Music/Data Select.ogg")) {
		Sound::SoundBank[0] = new ISound("Music/Data Select.ogg", true);
		Sound::Audio->LoopPoint[0] = 40308;
	}
}

PUBLIC void Scene_DataSelect::Init() {
	if (!App->Audio->IsPlayingMusic(Sound::SoundBank[0])) {
		App->Audio->ClearMusic();
		App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
	}

	App->Input->UseTouchController = false;

	if (!MenuSprite) {
		MenuSprite = new ISprite("UI/MainMenu.gif", App);
		MenuSprite->LoadAnimation("UI/MainMenu.bin");
		MenuSprite->SetTransparentColorIndex(0x2C);
		MenuSprite->UpdatePalette();
	}
	if (!SuperButtonsSprite) {
		SuperButtonsSprite = new ISprite("UI/SuperButtons.gif", App);
		SuperButtonsSprite->LoadAnimation("UI/SuperButtons.bin");
		SuperButtonsSprite->SetPalette(1, 0x282028);
		SuperButtonsSprite->UpdatePalette();
	}
	if (!TextSprite) {
		TextSprite = new ISprite("UI/CreditsText.gif", App);
		TextSprite->LoadAnimation("UI/CreditsText.bin");
		TextSprite->UpdatePalette();
	}
	if (!SaveIconsSprite) {
		ISprite::Animation an;
		SaveIconsSprite = new ISprite("UI/SaveIcons.gif", App);

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
		SaveSelectSprite = new ISprite("UI/SaveSelectEN.gif", App);
		SaveSelectSprite->LoadAnimation("UI/SaveSelect.bin");
	}

	FadeTimerMax = 30;
	FadeIn = true;

	Discord_UpdatePresence("Main Menu:", "Classic Mode", "icon");
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

PUBLIC void Scene_DataSelect::Update() {
	bool CONFIRM_PRESSED = App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED];
	bool CONFIRM_DOWN = App->Input->GetControllerInput(0)[IInput::I_CONFIRM] || App->Input->MouseDown;
	bool BACK_PRESSED = App->Input->GetControllerInput(0)[IInput::I_DENY_PRESSED];

	int mx = App->Input->MouseX;
	int my = App->Input->MouseY;
	if (App->Input->MouseReleased && mx < 128 && my > App->HEIGHT - 40)
		BACK_PRESSED = true;

	if (App->Input->MouseDown && !MobileScrollStart && my >= 40 && my < App->HEIGHT - 40) {
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
				selected = (*MobileScrollVariable + 5000) / 10000;
				if (selected < 0)
					selected = 0;
				if (selected > 7)
					selected = 7;
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
				App->NextScene = new Scene_MainMenu(App, G);
			}
			else {
				SaveGame::CurrentSaveFile = selected;

				int i = SaveGame::CurrentSaveFile;
				if (SaveGame::Savefiles[i].State == 0) {
					SaveGame::InitializeSaveGame();
					if (CharacterFlag == 0)
						CharacterFlag = 0x10 | CharacterFlag;
					SaveGame::CurrentCharacterFlag = CharacterFlag;
					if (i >= 0)
						SaveGame::Savefiles[i].CharacterFlag = CharacterFlag;

					SaveGame::Savefiles[i].State = 1;
					SaveGame::Flush();
				}
				else {
					SaveGame::CurrentCharacterFlag = SaveGame::Savefiles[i].CharacterFlag;
				}

				SaveGame::Flush();
				switch (SaveGame::Savefiles[i].LastZoneID) {
					LevelScene* ls;
					case 0: App->NextScene = new Level_AIZ(App, G, 1); break;
					case 1:
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
						ls->Thremixed = true;
						ls->ZoneID = 1;
						ls->VisualAct = 2;
						sprintf(ls->LevelName, "BENT LETTUCE");
						sprintf(ls->LevelNameDiscord, "Bent Lettuce Zone");
						App->NextScene = ls;
						break;
					//case 1:
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
				}

				/*
				SaveGame::CurrentEmeralds = 0x0000;
				LevelScene* ls = new LevelScene(App, G);
				Sound::SoundBank[0] = new ISound("Stages/MSZ/Act2.ogg", true);
				Sound::Audio->LoopPoint[0] = 179390 / 4;
				ls->Str_TileConfigBin = "Stages/MSZ/TileConfig.bin";
				ls->Str_SceneBin = "Stages/MSZ/Scene2.bin";
				ls->Str_TileSprite = "Stages/MSZ/16x16Tiles.gif";
				ls->PlayerStartX = 160;
				ls->PlayerStartY = 1328;
				ls->Thremixed = true;
				ls->ZoneID = 1;
				ls->VisualAct = 1;
				SaveGame::CurrentCharacterFlag = (int)CharacterType::Ray;
				sprintf(ls->LevelName, "TEST BENIS");
				sprintf(ls->LevelNameDiscord, "Mirage Saloon");
				App->NextScene = ls;
				//*/
			}
		}
	}
	else if (FadeTimer < 0) {
		if (App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED]) {
			if (selected > 0) {
				selected--;
				CharacterFlag = 0;
			}

			Sound::Play(Sound::SFX_MENUBLEEP);

			MobileScrolling = true;
		}
		if (App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED]) {
			if (selected < 7) {
				selected++;
				CharacterFlag = 0;
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

	// BG
	G->DrawRectangle(0, 0, App->WIDTH, App->HEIGHT, 0xF0F0F0);

	// Zigzags
	int pX = 186 - 5;
	int pY = 223 - 5;
	G->SetClip(App->WIDTH - 293, App->HEIGHT - 60, 293, 60);
	G->DrawSprite(MenuSprite, 16, 0, pX - (FrameZigzag / 4), pY - (FrameZigzag / 4), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 16, 0, pX - (FrameZigzag / 4) + 40, pY - (FrameZigzag / 4) + 40, 0, IE_NOFLIP);
	G->ClearClip();

	G->SetClip(131, 0, 100, 84);
	pX = 180 + FrameZigzagBlue / 4;
	pY = 32 + FrameZigzagBlue / 4;
	G->DrawSprite(MenuSprite, 16, 1, pX, pY, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 16, 1, pX - 110, pY - 110, 0, IE_NOFLIP);
	G->ClearClip();

	pX = 322 + FrameZigzagRed / 4;
	pY = 80 - FrameZigzagRed / 4;
	G->DrawSprite(MenuSprite, 16, 2, pX, pY, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 16, 2, pX - 117, pY + 117, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 16, 2, pX - 234, pY + 234, 0, IE_NOFLIP);

	/// Decorations
	int yup;
	// Red/Black Ovals
	yup = IMath::sinHex(FrameCircle);
	G->DrawSprite(MenuSprite, 11, 0, 116 + (yup >> 14), 25, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 11, 1, 116 - (yup >> 14), 25, 0, IE_NOFLIP);
	// Green/Black Ovals
	yup = IMath::sinHex(FrameCircle * 2 + 0x35);
	G->DrawSprite(MenuSprite, 11, 2, 246 + (yup >> 14), 185, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 11, 3, 246 - (yup >> 14), 185, 0, IE_NOFLIP);
	// Dotted circles
	G->DrawSprite(MenuSprite, 15, 0, App->WIDTH, 24, FrameCircle, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 15, 0, App->WIDTH, App->HEIGHT - 24, FrameCircle, IE_NOFLIP);
	// Dotted lines
	yup = IMath::sinHex(FrameCircle * 2 + 0x29);
	G->DrawSprite(MenuSprite, 14, 0, 323 - (yup >> 14), 94 + (yup >> 13), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 14, 1, 317 + (yup >> 14), 88 - (yup >> 13), 0, IE_NOFLIP);

	// Diamonds
	yup = IMath::sinHex(FrameCircle * 2 + 0x37);
	G->DrawSprite(MenuSprite, 12, 2, 134, 131 + (yup >> 15), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 12, 1, 124, 131 - (yup >> 15), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 12, 0, 114, 131 + (yup >> 15), 0, IE_NOFLIP);
	// Tilted Squares
	G->DrawSprite(MenuSprite, 13, 0, 253, 51 - (yup >> 15), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 13, 2, 265, 47 - (yup >> 15), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 13, 1, 259, 49 + (yup >> 15), 0, IE_NOFLIP);

	// Black
	G->DrawSprite(MenuSprite, 1, 0, App->WIDTH - 424, 0, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 1, 1, App->WIDTH - 424, App->HEIGHT, 0, IE_NOFLIP);
	// G->DrawSprite(MenuSprite, 1, 2, 0, 0, 0, IE_NOFLIP);
	G->DrawRectangle(0, 0, App->WIDTH - 424 + 128, 16, 0);
	G->DrawRectangle(0, App->HEIGHT - 24, App->WIDTH - 424 + 128, 24, 0);
	// Menu Title
	G->DrawSprite(MenuSprite, 9, 1, App->WIDTH, 12, 0, IE_NOFLIP);
	//G->DrawSprite(MenuSprite, 10, 0, App->WIDTH - 12, 12, 0, IE_NOFLIP);
	/// Triangles
	// for (int i = 0; i <= 12; i++) G->DrawSprite(MenuSprite, 1, 3, 96, i * 20 - 20 + (frame >> 1), 0, IE_NOFLIP);


	// For shape masking, make a separate framebuffer and when applying pixel, compare to that buffer
	for (int i = 0; i < 8; i++) {
		int myX = App->WIDTH / 2 - 40 + i * 100 - (viewOffX + 50) / 100;
		int myY = 38;

		// Shadow
		myX += 3;
		myY += 3;
		G->SetDrawAlpha(0x80);
		G->DrawRectangle(myX - 2, myY - 2, 80 + 4, 56 + 6, 0x000000);
		G->DrawRectangleStroke(myX - 5, myY - 5, 80 + 10, 160 + 10, 0x000000);
		G->DrawRectangleStroke(myX - 4, myY - 4, 80 + 8, 160 + 8, 0x000000);
		G->DrawRectangleStroke(myX - 3, myY - 3, 80 + 6, 160 + 6, 0x000000);
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
				if (i == selected)
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
		if (i != selected || SaveGame::Savefiles[i].State > 0)
			cf = SaveGame::Savefiles[i].CharacterFlag;

		cf &= 0xF;

		if (cf >= 3)
			cf++;

		G->DrawSprite(SaveSelectSprite, 2, cf, myX + 80 / 2 + 4, myY + 100 + 4, 0, 0);
		G->DrawSprite(SaveSelectSprite, 1, cf, myX + 80 / 2, myY + 100, 0, 0);

		if (SaveGame::Savefiles[i].State > 0) {
			G->DrawSprite(SaveSelectSprite, 3, SaveGame::Savefiles[i].CharacterFlag & 0xF, myX + 80 / 2 - 10, myY + 150, 0, 0);
			char lives[3];
			snprintf(lives, 3, "%d", SaveGame::Savefiles[i].Lives);
			G->DrawTextSprite(TextSprite, 6, '0' - 37, myX + 80 / 2 + 4, myY + 151, lives);
		}

		// Border
		G->DrawRectangleStroke(myX - 5, myY - 5, 80 + 10, 160 + 10, 0x000000);
		G->DrawRectangleStroke(myX - 4, myY - 4, 80 + 8, 160 + 8, 0x000000);
		G->DrawRectangleStroke(myX - 3, myY - 3, 80 + 6, 160 + 6, 0x000000);
	}

	// Border
	int myX = App->WIDTH / 2 - 40;
	int myY = 38;
	if ((frame >> 4) & 1) {
		G->DrawRectangleStroke(myX - 5, myY - 5, 80 + 10, 160 + 10, 0xE00000);
		G->DrawRectangleStroke(myX - 4, myY - 4, 80 + 8, 160 + 8, 0xE00000);
		G->DrawRectangleStroke(myX - 3, myY - 3, 80 + 6, 160 + 6, 0xE00000);
	}


	// TODO: When making controllers mappable, use those
	// 1 - Keyboard
	// 2 - Xbox
	// 3 - PS4
	// 4 - Switch
	// 5 - Saturn (Black)
	// 6 - Saturn (White)

	// Buttons 

	if (IApp::Mobile) {
		G->DrawTextSprite(TextSprite, 6, 'A', 14, App->HEIGHT - 12, "BACK");
	}
	else {
		int CurrAni = 1;
		if (IApp::Platform == Platforms::Switch) {
			CurrAni = 4;
		}
		if (CurrAni == 1) {
			G->DrawSprite(SuperButtonsSprite, CurrAni, App->Input->ControllerMaps[0][IInput::I_CONFIRM], 104, App->HEIGHT - 12, 0, IE_NOFLIP);
			G->DrawSprite(SuperButtonsSprite, CurrAni, App->Input->ControllerMaps[0][IInput::I_DENY], 14, App->HEIGHT - 12, 0, IE_NOFLIP);
		}
		else {
			G->DrawSprite(SuperButtonsSprite, CurrAni, 1, 104, App->HEIGHT - 12, 0, IE_NOFLIP);
			G->DrawSprite(SuperButtonsSprite, CurrAni, 0, 14, App->HEIGHT - 12, 0, IE_NOFLIP);
		}

		G->DrawTextSprite(TextSprite, 6, 'A', 14 + 16, App->HEIGHT - 12, "BACK");
		G->DrawTextSprite(TextSprite, 6, 'A', 104 + 16, App->HEIGHT - 12, "ACCEPT");
	}
}
