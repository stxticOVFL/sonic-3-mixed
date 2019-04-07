#if INTERFACE

#include <Engine/IScene.h>
#include <Engine/ISprite.h>

class Scene_SettingsMenu : public IScene {
public:
	int selected = 0;
	int subselected = -1;
	bool inselect = false;
	int frame = 0;
	int palframe = 0;
	int FrameCircle = 0;
	int FrameZigzag = 0;
	int FrameZigzagRed = 0;
	int FrameZigzagBlue = 0;
	int ElementY = 40;
	int ElementH = 150;
	int paletteindexes[9];
	int paletteToCycle[18];
	bool GoBack = false;
	int triframe = 0;
	ISprite* MenuSprite = NULL;
	ISprite* SuperButtonsSprite = NULL;
	ISprite* TextSprite = NULL;
	ISprite* SettingsSprite = NULL;
	IINI* Settings = NULL;
};

#endif

#include <Game/LevelScene.h>

#include <Game/Scenes/MainMenu.h>
#include <Game/Scenes/SettingsMenu.h>

//0: on/off, default
//1: leftright switch
//2: slider (limited)
//3: slider (0-100)
int SettingsType[9] = {
	//visual
	0, //fullscreen
	2, //window size
	1, //shaders
	//audio
	3, 3, 3, //global, music, sfx
	//controls
	0, 0, 0 // i have no fucking idea how we're gonna handle these
};

PUBLIC Scene_SettingsMenu::Scene_SettingsMenu(IApp* app, IGraphics* g) {
	App = app;
	G = g;
	Settings = App->Settings; //used mainly for graphics

	Sound::Audio = App->Audio;
	Sound::Init();	

	Discord_UpdatePresence("Main Menu", "Settings", "icon", false);
}

PUBLIC void Scene_SettingsMenu::Init() {
	int at = 0;
	if (Sound::SoundBank[0]) {
		char* ct = strstr(Sound::SoundBank[0]->Name, "Menu");
		if (ct != NULL)
			at = Sound::SoundBank[0]->GetPosition();
		//free(ct);
	}
	App->Audio->ClearMusic();
	Sound::PlayStream(0, "Music/Menu3.ogg", true, 0, at, true);

	if (!MenuSprite) {
		MenuSprite = new ISprite("Sprites/UI/MainMenu.gif", App);
		MenuSprite->LoadAnimation("Sprites/UI/MainMenu.bin");
		for (int i = 0; i < 9; i++)
			MenuSprite->SetPalette(paletteindexes[i], paletteToCycle[i]);
		MenuSprite->SetTransparentColorIndex(0x0);
		MenuSprite->UpdatePalette();
	}
	if (!SettingsSprite) {
		SettingsSprite = new ISprite("Sprites/UI/Settings.gif", App);
		SettingsSprite->LoadAnimation("Sprites/UI/Settings.bin");
		for (int i = 0; i < 9; i++)
			SettingsSprite->SetPalette(paletteindexes[i], paletteToCycle[i]);
		SettingsSprite->SetTransparentColorIndex(0x0);
		SettingsSprite->UpdatePalette();
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

	App->Input->UseTouchController = false;

	FadeTimerMax = 30;
	FadeIn = true;
	Discord_UpdatePresence("Main Menu", "", "icon", false);
}

PUBLIC void Scene_SettingsMenu::Update() {
	bool CONFIRM_PRESSED = App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED];
	bool CONFIRM_DOWN = App->Input->GetControllerInput(0)[IInput::I_CONFIRM] || App->Input->MouseDown;
	bool BACK_PRESSED = App->Input->GetControllerInput(0)[IInput::I_DENY_PRESSED];

	int mx = App->Input->MouseX;
	int my = App->Input->MouseY;
	if (App->Input->MouseReleased && mx < 128 && my > ElementY + ElementH)
		BACK_PRESSED = true;
	if (FadeTimer == -1 && FadeTimerMax > 1)
		FadeTimer = FadeTimerMax;
	if (FadeTimer > 0) {
		FadeTimer--;
		if (!FadeIn)
			G->SetFade(int((1.0 - float(FadeTimer - 1) / FadeTimerMax) * FadeMax));
		else
			G->SetFade(int((float(FadeTimer) / FadeTimerMax) * FadeMax));
	}

	palframe += 1;
	palframe %= 288;

	// Do Fade actions
	if (FadeTimer == 0) {
		FadeTimer = -1;
		FadeTimerMax = 0;

		if (!FadeIn) {
			if (GoBack) {
				int f, w, h, s;
				for (int i = 0; i < 4; i++) {
					char name[11];
					if (i == 0)
						sprintf(name, "fullscreen");
					if (i == 1)
						sprintf(name, "width");
					if (i == 2)
						sprintf(name, "height");
					if (i == 3)
						sprintf(name, "shader");
					int buffer;
					Settings->GetInteger("display", name, &buffer);
					if (i == 0)
						Settings->GetInteger("display", name, &f);
					if (i == 1)
						Settings->GetInteger("display", name, &w);
					if (i == 2)
						Settings->GetInteger("display", name, &h);
					if (i == 3)
						Settings->GetInteger("display", name, &s);
					App->Print(0, "%x %x", &buffer, buffer);
					App->Settings->SetInteger("display", name, buffer);
				}
				App->Settings->Write("config.ini");
				//how does this work but not when its used
				//what fucking wizardry is c++
				//int s[4];
				//for (int i = 0; i < 4; i++)
					//s[i] = *p[i];
				App->Print(0, "%d %d %d %d", f, w, h, s);
				SDL_SetWindowFullscreen(G->Window, f);
				if (s == 0)
					SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
				else
					SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
				G->WindowWidth = w;
				G->WindowHeight = h;
				
				//someone else can fix i have no fucking idea what happened*/
				Scene_MainMenu* NextScene = new Scene_MainMenu(App, G);
				NextScene->MenuSprite = MenuSprite;
				NextScene->SuperButtonsSprite = SuperButtonsSprite;
				NextScene->TextSprite = TextSprite;
				App->NextScene = NextScene;
			}
		}
	}

	//controlll ,. .
	if (FadeTimer == -1) {
		bool Changed = false;
		if (!inselect) {
			if (BACK_PRESSED) {
				GoBack = true;
				FadeIn = false;
				FadeTimerMax = 30;
			}
			if (App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED]) {
				selected--;
				if (selected < 0)
					selected = 0;

				Sound::Play(Sound::SFX_MENUBLEEP);
				Changed = true;
			}
			if (App->Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED]) {
				selected++;
				if (selected > 2)
					selected = 2;

				Sound::Play(Sound::SFX_MENUBLEEP);
				Changed = true;
			}
			if (CONFIRM_PRESSED) {
				Sound::Play(Sound::SFX_MENUACCEPT);
				inselect = true;
				subselected = 0;
			}
		}
		if (inselect) {
			if (BACK_PRESSED) {
				Sound::Play(Sound::SFX_MENUBLEEP);
				inselect = false;
				subselected = -1;
			}
			if (App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED]) {
				subselected--;
				if (subselected < 0)
					subselected = 0;

				Sound::Play(Sound::SFX_MENUBLEEP);
				Changed = true;
			}
			if (App->Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED]) {
				subselected++;
				if (subselected > 2)
					subselected = 2;

				Sound::Play(Sound::SFX_MENUBLEEP);
				Changed = true;
			}
			if (App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED] || App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED]) {
				HandleChange(App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED]);
				Sound::Play(Sound::SFX_MENUBLEEP);
			}
		}
	}

	FrameCircle = (FrameCircle + 1) & 0xFF;
	FrameZigzag = (FrameZigzag + 1) % (40 * 4);
	FrameZigzagRed = (FrameZigzagRed + 1) % (117 * 4);
	FrameZigzagBlue = (FrameZigzagBlue + 1) % (110 * 4);

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
PUBLIC void Scene_SettingsMenu::RenderBack() {
	G->SetFilter(IE_FILTER_FADEABLE);

	int cenX = App->WIDTH / 2;
	int cenY = App->HEIGHT / 2;

	// BG
	G->DrawRectangle(0, 0, App->WIDTH, App->HEIGHT, 0xF0F0F0);

	// Zigzags
	int pX = cenX - (260 - 186) - 5;
	int pY = 223 - 5;
	G->SetClip(0, App->HEIGHT - 58, 293, 60);
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
	G->DrawSprite(MenuSprite, 9, 6, App->WIDTH, 12, 0, IE_NOFLIP);
	G->DrawSprite(MenuSprite, 10, 3, App->WIDTH - 12, 12, 0, IE_NOFLIP);
}

PUBLIC void Scene_SettingsMenu::HandleChange(bool up) {
	if (selected == 0) {
		bool full;
		if (subselected == 0) {
			Settings->GetBool("display", "fullscreen", &full);
			Settings->SetBool("display", "fullscreen", !full);
		}
		if (subselected == 1) {
			int cW, cH, mult;
			Settings->GetInteger("display", "width", &cW);
			Settings->GetInteger("display", "height", &cH);
			mult = sqrt((cW * cH) / (424 * 240)) + up ? 1 : -1; //current / internal
			App->Print(0, "%d %d %d", mult, cW, cH);
			if (mult >= 5 || mult <= 0)
				return; //no less than 1, no more than 4
			Settings->SetInteger("display", "width", 424 * mult);
			Settings->SetInteger("display", "height", 240 * mult);
		}
		if (subselected == 2) {
			int current;
			Settings->GetInteger("display", "shader", &current);
			current += up ? 1 : -1;
			App->Print(0, "%d %d %d", current);
			if (current > 2)
				current = 0;
			if (current < 0)
				current = 2;
			Settings->SetInteger("display", "shader", current);
		}
	}
	if (selected == 1) {
		char name[7];
		if (subselected == 0)
			sprintf(name, "global");
		if (subselected == 1)
			sprintf(name, "music");
		if (subselected == 2)
			sprintf(name, "sfx");
		int current = 0;
		App->Settings->GetInteger("audio", name, &current);
		current += up ? 10 : -10;
		if (current < 0)
			current = 0;
		if (current > 100)
			current = 100;
		App->Settings->SetInteger("audio", name, current);
	}
}

PUBLIC void Scene_SettingsMenu::Render() {
	RenderBack();
	for (int i = 0; i < 9; i++)
		SettingsSprite->SetPalette(paletteindexes[i], paletteToCycle[(palframe - i + 18) % 18]);
	SettingsSprite->UpdatePalette();

	int cenX = App->WIDTH / 2;
	int cenY = App->HEIGHT / 2;

	bool nowSelected = false;
	for (int i = 0; i < 3; i++) {
		int add = 0;
		if (nowSelected)
			add = 3;
		G->DrawSprite(SettingsSprite, 0, 0, cenX, cenY + ((i + add) * 32), 0, IE_NOFLIP);
		G->DrawSprite(SettingsSprite, 2, i, cenX, cenY + 32 * add, 0, IE_NOFLIP);
		G->DrawSprite(SettingsSprite, 3, i, cenX, cenY + 32 * add, 0, IE_NOFLIP);

		if (i == selected) {
			G->DrawSprite(SettingsSprite, 1, 0, cenX, cenY + (i * 32), 0, IE_NOFLIP);
			nowSelected = true;
		}
	}
	if (!inselect) {
		for (int i = 0; i < 9; i++)
			SettingsSprite->SetPalette(paletteindexes[i], paletteToCycle[i + 9]);
		SettingsSprite->UpdatePalette();
	}

	G->DrawSprite(SettingsSprite, 0, 1, cenX, cenY + (selected * 32), 0, IE_NOFLIP);
	for (int i = 0; i < 3; i++) {
		//G->DrawSprite(SettingsSprite, 4, selected * 3 + i, cenX, cenY, 0, IE_NOFLIP);
		int fl = 0;
		if (selected == 0) {
			if (i == 0)
				Settings->GetInteger("display", "fullscreen", &fl);
			if (i == 1) {
				int cW, cH, mult;
				Settings->GetInteger("display", "width", &cW);
				Settings->GetInteger("display", "height", &cH);
				mult = (cW * cH) / (424 * 240); //current / internal
				fl = sqrt(mult);
			}
			if (i == 2) {
				//int crt = 0;
				App->Settings->GetInteger("display", "shader", &fl);
				//fl = fl + crt;
			}	
		}
		if (selected == 1) {
			App->Settings->GetInteger("audio", i == 0 ? "global" : (i == 1 ? "music" : "sfx"), &fl);
		}
		RenderTypes(SettingsType[selected * 3 + i], 64 + (selected * 32) + i * 32, fl, i);
	}
}

PUBLIC void Scene_SettingsMenu::RenderTypes(int t, int y, int fl, int i) {
	G->DrawSprite(SettingsSprite, 5 + (t < 2 ? t : 2), 0, 76, y, 0, IE_NOFLIP);
	switch (t) {
		case 0: { //onoff
			G->DrawSprite(SettingsSprite, 5, fl == 1 ? 3 : 1, 77, y + 1, 0, IE_NOFLIP);
			G->DrawSprite(SettingsSprite, 5, fl == 0 ? 4 : 2, 77 + 25, y + 1, 0, IE_NOFLIP);
		} break;
		case 1: { //leftright
			if (i == subselected)
				G->DrawSprite(SettingsSprite, 6, 1, 76, y, 0, IE_NOFLIP);
			else {
				G->DrawSprite(SettingsSprite, 6, 2, 76, y, 0, IE_NOFLIP);
				G->DrawSprite(SettingsSprite, 6, 3, 76, y, 0, IE_NOFLIP);
			}
			G->DrawSprite(SettingsSprite, 8, i == subselected ? fl + 3 : fl, 76, y, 0, IE_NOFLIP);
			if (i == subselected && frame > 20) {
				G->DrawSprite(SettingsSprite, 6, 2, 76, y, 0, IE_NOFLIP);
				G->DrawSprite(SettingsSprite, 6, 3, 76, y, 0, IE_NOFLIP);
			}
		} break;
		case 2:
		case 3: { //slider
			//App->Print(0, "%d", t);	
			int x = t == 2 ? (fl + 1) * 11 : (fl / 1.5);
			G->DrawSprite(SettingsSprite, 7, i == subselected ? 2 : 1, 76 + x, y, 0, IE_NOFLIP);
		} break;
	}
}