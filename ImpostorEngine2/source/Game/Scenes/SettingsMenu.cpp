#if INTERFACE

#include <Engine/IScene.h>
#include <Engine/ISprite.h>

class Scene_SettingsMenu : public IScene {
public:
	int selected = 0;
	int ran = 0;
	int frame = 0;
	int FrameCircle = 0;
	int FrameZigzag = 0;
	int FrameZigzagRed = 0;
	int FrameZigzagBlue = 0;
	ISprite* MenuSprite = NULL;
	ISprite* SuperButtonsSprite = NULL;
	ISprite* TextSprite = NULL;
};

#endif

#include <Game/LevelScene.h>

#include <Game/Scenes/MainMenu.h>
#include <Game/Scenes/SettingsMenu.h>

PUBLIC Scene_SettingsMenu::Scene_SettingsMenu(IApp* app, IGraphics* g) {
	App = app;
	G = g;

	Sound::Audio = App->Audio;
	Sound::Init();

	// Sound::SoundBank[0] = new ISound("Music/Mixed/SaveSelectTria.ogg", true);
	// Sound::Audio->LoopPoint[0] = 131859;
	if (!Sound::SoundBank[0] || strcmp(Sound::SoundBank[0]->Name, "Music/Data Select.ogg")) {
		Sound::SoundBank[0] = new ISound("Music/Data Select.ogg", true);
		Sound::Audio->LoopPoint[0] = 40308;
	}
	Discord_UpdatePresence("Main Menu", "Settings", "icon", false);
}


PUBLIC void Scene_SettingsMenu::Render() {
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
	G->DrawSprite(MenuSprite, 9, (1 + 0), App->WIDTH, 12, 0, IE_NOFLIP);
}