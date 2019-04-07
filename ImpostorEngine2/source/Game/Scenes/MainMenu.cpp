#if INTERFACE
#include <Engine/IScene.h>
#include <Engine/ISprite.h>

class Scene_MainMenu : public IScene {
public:
	int selected = 0;
	int subselected = -1;
	int ran = 0;
	bool opened = false;
	int openBlue = 15;
	int openRed = 15;
	int openTimer = 15;
	int prechange = 0;
	ISprite* MenuSprite = NULL;
	ISprite* SphereSprite = NULL;
	ISprite* SuperButtonsSprite = NULL;
	ISprite* TextSprite = NULL;
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
#include <Game/Levels/BonusStage.h>

#include <Game/Scenes/DataSelect.h>
#include <Game/Scenes/LevelSelect.h>
#include <Game/Scenes/SettingsMenu.h>
#include <Game/Scenes/ExtrasMenu.h>
#include <Game/Scenes/VSMenu.h>

#include <Game/Scenes/MainMenu.h>
#include <ctime>
#include <algorithm>
#include <Engine/Diagnostics/Memory.h>

int FrameCircle = 0;
int FrameZigzag = 0;
int FrameZigzagRed = 0;
int FrameZigzagBlue = 0;

int frame = 0;
int triframe = 0;
int palframe = 0;

int paletteindexes[9] = {
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
};
int paletteToCycle[18] = {
	0xEAD100,
	0xE4C700,
	0xE0BF00,
	0xDAB600,
	0xD6AE00,
	0xD1A500,
	0xCD9D00,
	0xC89400,
	0xC48C00,
	0xBE8200,
	0xB97A00,
	0xB47100,
	0xB06A00,
	0xAA6100,
	0xA65900,
	0xA15000,
	0x9D4800,
	0x993A00,
};

int MainMenu_at = 0;

PUBLIC Scene_MainMenu::Scene_MainMenu(IApp* app, IGraphics* g) {
	App = app;
	G = g;
}

PUBLIC void Scene_MainMenu::Init() {
	int at = 0;
	if (Sound::SoundBank[0]) {
		char* ct = strstr(Sound::SoundBank[0]->Name, "Menu");
		if (ct != NULL)
			at = Sound::SoundBank[0]->GetPosition();
		//free(ct);
	}
	App->Audio->ClearMusic();
	Sound::PlayStream(0, "Music/Menu1.ogg", true, 0, at, true);

	if (!MenuSprite) {
		MenuSprite = new ISprite("UI/MainMenu.gif", App, 1);
		MenuSprite->LoadAnimation("UI/MainMenu.bin");
		for (int i = 0; i < 9; i++)
			MenuSprite->SetPalette(paletteindexes[i], paletteToCycle[i]);
		MenuSprite->SetTransparentColorIndex(0x0);
		MenuSprite->UpdatePalette();
	}
	if (!SphereSprite) {
		SphereSprite = new ISprite("UI/MenuSpheres.gif", App, 1);
		ISprite::Animation an;
		an.Name = (char*)"Sign in GitLab.com";
		an.FrameCount = 5;
		an.Frames = (ISprite::AnimFrame*)malloc(an.FrameCount * sizeof(ISprite::AnimFrame));
		for (int i = 0; i < an.FrameCount; i++) {
			int fi = i;
			ISprite::AnimFrame ts_af;
			ts_af.X = (fi % 6) * 92 + 2;
			ts_af.Y = (fi / 6) * 92 + 2;
			ts_af.W = ts_af.H = 88; ts_af.OffX = ts_af.OffY = -44;
			an.Frames[i] = ts_af;
			G->MakeFrameBufferID(SphereSprite, an.Frames + i);
		}
		SphereSprite->Animations.push_back(an);

		SphereSprite->SetTransparentColorIndex(26);
	}
	if (!SuperButtonsSprite) {
		SuperButtonsSprite = new ISprite("UI/SuperButtons.gif", App, 1);
		SuperButtonsSprite->LoadAnimation("UI/SuperButtons.bin");
		SuperButtonsSprite->SetPalette(1, 0x282028);
		SuperButtonsSprite->UpdatePalette();
	}
	if (!TextSprite) {
		TextSprite = new ISprite("UI/CreditsText.gif", App, 1);
		TextSprite->LoadAnimation("UI/CreditsText.bin");
		TextSprite->UpdatePalette();
	}

	if (!App->Audio->IsPlayingMusic(Sound::SoundBank[0])) {
		App->Audio->ClearMusic();
		App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
	}

	App->Input->UseTouchController = false;

	FadeTimerMax = 30;
	FadeIn = true;
	Discord_UpdatePresence("Main Menu", "", "icon", false);
}

PUBLIC void Scene_MainMenu::Update() {
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
		openTimer -= 1;

		if (!FadeIn) {
			if (selected == 0) {
				Scene_DataSelect* NextScene = new Scene_DataSelect(App, G, subselected);
				NextScene->MenuSprite = MenuSprite;
				NextScene->SuperButtonsSprite = SuperButtonsSprite;
				NextScene->TextSprite = TextSprite;

				// Make these NULL so they don't get accidentally cleaned up later
				MenuSprite = NULL;
				SuperButtonsSprite = NULL;
				TextSprite = NULL;

				App->NextScene = NextScene;
			}
			else if (selected == 1) {
				Scene_VSMenu* NextScene = new Scene_VSMenu(App, G);

				App->NextScene = NextScene;
			}
			else if (selected == 2) {
				Scene_SettingsMenu* NextScene = new Scene_SettingsMenu(App, G);
				NextScene->MenuSprite = MenuSprite;
				NextScene->SuperButtonsSprite = SuperButtonsSprite;
				NextScene->TextSprite = TextSprite;
				std::copy(std::begin(paletteindexes), std::end(paletteindexes), std::begin(NextScene->paletteindexes));
				std::copy(std::begin(paletteToCycle), std::end(paletteToCycle), std::begin(NextScene->paletteToCycle));

				// Make these NULL so they don't get accidentally cleaned up later
				MenuSprite = NULL;
				SuperButtonsSprite = NULL;
				TextSprite = NULL;

				App->NextScene = NextScene;
			}
			else if (selected == 3) {
				Scene_ExtrasMenu* NextScene = new Scene_ExtrasMenu(App, G);

				App->NextScene = NextScene;
			}
			else
				App->NextScene = new Scene_LevelSelect(App, G);
		}
	}

	bool CONFIRM_PRESSED = false;
	if (FadeTimer == -1) {
		CONFIRM_PRESSED = App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED];

		int cenX = App->WIDTH / 2;
		int cenY = App->HEIGHT / 2;

		int mx = App->Input->MouseX;
		int my = App->Input->MouseY;
		bool Changed = false;

		if (App->Input->MousePressed) {
			int sel = selected;
			int tosel = -1;
			if (mx >= cenX - 129 && my >= cenY - 79 &&
				mx < cenX - 129 + 100 && my < cenY - 79 + 50)
				tosel = 0;
			else if (mx >= cenX + 29 && my >= cenY - 79 &&
				mx < cenX + 29 + 100 && my < cenY - 79 + 50)
				tosel = 1;
			else if (mx >= cenX - 129 && my >= cenY + 29 &&
				mx < cenX - 129 + 100 && my < cenY + 29 + 50)
				tosel = 2;
			else if (mx >= cenX + 29 && my >= cenY + 29 &&
				mx < cenX + 29 + 100 && my < cenY + 29 + 50)
				tosel = 3;

			if (tosel >= 0) {
				selected = tosel;
				if (sel == selected) {
					CONFIRM_PRESSED = true;
				}
				else {
					Changed = true;
					Sound::Play(Sound::SFX_MENUBLEEP);
				}
			}
		}

		if (App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED]) {
			if (subselected > -1 && opened) {
				subselected -= 1;
				if (subselected == -1)
					subselected = 0;
			}
			else if (selected >= 2) {
				selected -= 2;
				//if (selected / 2 == 0)
					//subselected = 0;
			}
			Changed = true;
			Sound::Play(Sound::SFX_MENUBLEEP);
		}
		if (App->Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED]) {
			if (subselected > -1 && opened) {
				if ((subselected == 2 && selected == 0) || (subselected == 1 && selected == 1)) {
					selected += 2;
					subselected = -1;
				}
				subselected += 1;
			}
			else if (selected <= 1) {
				selected += 2;
				//if (selected / 2 == 0)
					//subselected = -1;
			}
			Changed = true;
			Sound::Play(Sound::SFX_MENUBLEEP);
		}

		if (App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED]) {
			if ((selected & 1) == 1)
				selected--;
			//if (selected / 2 == 0)
				//subselected = -1;
			Changed = true;
			Sound::Play(Sound::SFX_MENUBLEEP);
		}
		if (App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED]) {
			if ((selected & 1) == 0)
				selected++;
			//if (selected / 2 == 0)
				//subselected = -1;
			Changed = true;
			Sound::Play(Sound::SFX_MENUBLEEP);
		}
		if (Changed) {
			ran = selected;
			if (prechange != selected) {
				openTimer = 20;
				opened = false;
				subselected = -1;
			}
			prechange = selected;
			if (ran == 1) {
				std::srand(std::time(nullptr));
				if (std::rand() % 1024 == 0) {
					ran = 4;
				}
			}
		}

		if (App->Input->GetControllerInput(0)[IInput::I_EXTRA_PRESSED])
		{
			App->NextScene = new Scene_LevelSelect(App, G);
			CONFIRM_PRESSED = true;
		}
	}

	if (CONFIRM_PRESSED) {
		Sound::Play(Sound::SFX_MENUACCEPT);
		if (selected / 2 != 0 || subselected > -1) {
			FadeIn = false;
			FadeTimerMax = 30;
		}
		else {
			openTimer = 15;
			opened = true;
			subselected = 0;
			if (selected == 0) {
				openBlue = 0;
			}
			else {
				openRed = 0;
			}
		}
	}

	FrameCircle = (FrameCircle + 1) & 0xFF;
	FrameZigzag = (FrameZigzag + 1) % (40 * 4);
	FrameZigzagRed = (FrameZigzagRed + 1) % (117 * 4);
	FrameZigzagBlue = (FrameZigzagBlue + 1) % (110 * 4);
	openBlue = openRed = 15;
	if (opened) {
		openTimer = openTimer > 0 ? openTimer - 1 : 0;
		if (selected == 0) {
			openBlue = openTimer;
		}
		else {
			openRed = openTimer;
		}
	}

	//TEMP, Tally the total score
	if (App->Input->GetControllerInput(0)[IInput::I_EXTRA2_PRESSED])
	{
		//Big ass value
		unsigned long long TotalScore = 0;

		for (int i = 0; i < 36; i++)
		{
			if (SaveGame::Savefiles[i].State > 0)
			{
				TotalScore += SaveGame::Savefiles[i].Score;
			}
		}

		//lu more like
		//loser
		App->Print(0, "Total Score = %lu", TotalScore);
	}

	if (FrameCircle & 1) return;

	// Palette rotating
	palframe += 1 + 18;
	palframe %= 18;

	frame++;
	if (frame > (20 << 1))
		frame = 0;

	triframe = frame >> 1;
	if (triframe < 6)
		triframe = 0;
	else if (triframe < 10)
		triframe = 1;
	else if (triframe < 16)
		triframe = 2;
	else
		triframe = 3;
}

PUBLIC void Scene_MainMenu::Render() {
	G->SetFilter(IE_FILTER_FADEABLE);

	G->DrawRectangle(0, 0, App->WIDTH, App->HEIGHT, 0xF0F0F0);

	int cenX = App->WIDTH / 2;
	int cenY = App->HEIGHT / 2;

	// BG
	G->DrawSprite(MenuSprite, 0, 0, 0, 0, 0, IE_NOFLIP);

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
	G->DrawRectangle(0, 0, blackGirth, App->HEIGHT, 0x000000);
	G->DrawRectangle(App->WIDTH - blackGirth, 0, blackGirth, App->HEIGHT, 0x000000);

	G->DrawRectangle(0, 0, App->WIDTH - 424 + 128, 16, 0);
	G->DrawRectangle(0, App->HEIGHT - 24, App->WIDTH - 424 + 128, 24, 0);
	// Triangles
	for (int i = 0; i <= 12; i++) G->DrawSprite(MenuSprite, 1, 3, blackGirth, i * 20 - 20 + (frame >> 1), 0, IE_NOFLIP);
	for (int i = 0; i <= 12; i++) G->DrawSprite(MenuSprite, 1, 3, App->WIDTH - blackGirth, i * 20 - (frame >> 1), 0, IE_FLIPX);
	// Menu Title
	G->DrawSprite(MenuSprite, 9, 0, App->WIDTH, 12, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 10, 0, App->WIDTH - 12, 12, 0, IE_NOFLIP);


	// Submenus for Blue
	//Boxes
	G->DrawSprite(MenuSprite, 18, 0, cenX, cenY - (openBlue * 3), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 18, 0, cenX, cenY - (openBlue * 3) + 11, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 18, 0, cenX, cenY - (openBlue * 3) + 22, 0, IE_NOFLIP);
	//Triangles
	G->DrawSprite(MenuSprite, 19, 0, cenX, cenY - (openBlue * 3), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 19, 0, cenX, cenY - (openBlue * 3) + 11, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 19, 0, cenX, cenY - (openBlue * 3) + 22, 0, IE_NOFLIP);
	//Names
	G->DrawSprite(MenuSprite, 20, 0, cenX, cenY - (openBlue * 3), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 20, 1, cenX, cenY - (openBlue * 3), 0, IE_NOFLIP);
	//if (LockedOnNotUnlocked)
	G->DrawSprite(MenuSprite, 20, 2, cenX, cenY - (openBlue * 3), 0, IE_NOFLIP);
	//else
	//G->DrawSprite(MenuSprite, 20, 3, cenX, cenY, 0, IE_NOFLIP);

	// Submenus for Red
	//Boxes
	G->DrawSprite(MenuSprite, 18, 1, cenX, cenY - (openRed * 3), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 18, 1, cenX, cenY - (openRed * 3) + 11, 0, IE_NOFLIP);
	//Triangles
	G->DrawSprite(MenuSprite, 19, 2, cenX, cenY - (openRed * 3), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 19, 2, cenX, cenY - (openRed * 3) + 11, 0, IE_NOFLIP);
	//Names
	G->DrawSprite(MenuSprite, 20, 4, cenX, cenY - (openRed * 3), 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 20, 5, cenX, cenY - (openRed * 3), 0, IE_NOFLIP);
	// Selection
	for (int i = 0; i < 9; i++)
		MenuSprite->SetPalette(paletteindexes[i], paletteToCycle[(palframe - i + 18) % 18]);
	MenuSprite->UpdatePalette();
	//Submenu Select Triangle
	if (subselected != -1) {
		if (selected == 0)
			G->DrawSprite(MenuSprite, 19, 1, cenX, (cenY - (openBlue * 3)) + (subselected * 11), 0, IE_NOFLIP);
		else
			G->DrawSprite(MenuSprite, 19, 3, cenX, (cenY - (openRed * 3)) + (subselected * 11), 0, IE_NOFLIP);
	}
	//else
		//G->DrawSprite(MenuSprite, 19, 1, cenX, App->WIDTH + 10, 0, IE_NOFLIP); //atleast hide it

	// Blue Button
	G->DrawSprite(MenuSprite, 3, 0, cenX, cenY, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 8, 0, cenX - 50 - 29, cenY - 25 - 29 - 3, 0, IE_NOFLIP);
	// Red Button
	G->DrawSprite(MenuSprite, 4, 0, cenX, cenY, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 8, 1, cenX + 50 + 29, cenY - 25 - 29 - 3, 0, IE_NOFLIP);


	// Yellow Button
	G->DrawSprite(MenuSprite, 5, 0, cenX, cenY, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 8, 2, cenX - 50 - 29, cenY + 25 + 29 - 3, 0, IE_NOFLIP);

	// Green Button
	G->DrawSprite(MenuSprite, 6, 0, cenX, cenY, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 8, 3, cenX + 50 + 29, cenY + 25 + 29 - 3, 0, IE_NOFLIP);

	// Circle

	G->DrawSprite(SphereSprite, 0, ran, cenX, cenY, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 17, 0, cenX, cenY, 0, IE_NOFLIP);

	G->DrawSprite(MenuSprite, 3 + selected, 3, cenX, cenY, 0, IE_NOFLIP);

	for (int i = 0; i < 9; i++)
		MenuSprite->SetPalette(paletteindexes[i], paletteToCycle[i]);
	MenuSprite->UpdatePalette();

	// Spinny Triangle
	G->DrawRectangle(cenX + (-129 + 2), cenY + (-39), 12, 9, 0x000000);
	if (selected == 0&& subselected > -1)
		G->DrawSprite(MenuSprite, 2, triframe, cenX + (-129 + 2), cenY + (-39), 0, IE_NOFLIP);
	else
		G->DrawSprite(MenuSprite, 2, 0, cenX + (-129 + 2), cenY + (-39), 0, IE_NOFLIP);

	G->DrawRectangle(cenX + (117 - 2), cenY + (-39), 12, 9, 0x000000);
	if (selected == 1 && subselected > -1)
		G->DrawSprite(MenuSprite, 2, triframe, cenX + (117 - 2), cenY + (-39), 0, IE_NOFLIP);
	else
		G->DrawSprite(MenuSprite, 2, 0, cenX + (117 - 2), cenY + (-39), 0, IE_NOFLIP);


	/*
	if (selected == 0) {
		G->DrawTextSprite(TextSprite, 6, 'A', 4, 32, "PICK\nBETWEEN\nDIFFERENT\nGAMEPLAY\nMODES AND\nEXPERIENCE\nSONIC i AND\nKNUCKLES\nIN ANY WAY\nYOU CHOOSEr");
	}
	else if (selected == 1) {
		G->DrawTextSprite(TextSprite, 6, 'A', 4, 32, "DUKE IT OUT\nWITH\nFRIENDS IN\nTWO\nDIFFERENT\nWAYSr");
	}
	else if (selected == 2) {
		G->DrawTextSprite(TextSprite, 6, 'A', 4, 32, "ADJUST\nVARIOUS\nAUDIO AND\nVISUAL\nOPTIONS]\nAND REMAP\nYOUR\nCONTROLSr");
	}
	else if (selected == 3) {
		G->DrawTextSprite(TextSprite, 6, 'A', 4, 32, "VARIOUS\nADDITIONAL\nFEATURES\nAND\nUNLOCKABLESr");
	}
	//*/

	// Buttons
	bool Back = false;
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

PUBLIC void Scene_MainMenu::Cleanup() {
#define CLEANUP(name) if (name) { name->Cleanup(); delete name; name = NULL; }

	// Do not clear music so we can keep it through menus
	// App->Audio->ClearMusic();
	// CLEANUP(Sound::SoundBank[0]);

	CLEANUP(MenuSprite);
	CLEANUP(SphereSprite);
	CLEANUP(SuperButtonsSprite);
	CLEANUP(TextSprite);
}
