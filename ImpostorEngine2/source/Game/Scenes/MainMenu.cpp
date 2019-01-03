#if INTERFACE
#include <Engine/IScene.h>
#include <Engine/ISprite.h>

class Scene_MainMenu : public IScene {
public:
    int selected = 0;
    ISprite* MenuSprite = NULL;
    ISprite* SuperButtonsSprite = NULL;
};
#endif

#include <Game/LevelScene.h>
#include <Game/Levels/AIZ.h>
#include <Game/Levels/HCZ.h>
#include <Game/Levels/MGZ.h>
//#include <Game/Levels/CNZ.h>
//#include <Game/Levels/ICZ.h>
#include <Game/Levels/LBZ.h>
#include <Game/Levels/MHZ.h>
//#include <Game/Levels/FBZ.h>
//#include <Game/Levels/SOZ.h>
//#include <Game/Levels/LRZ.h>
//#include <Game/Levels/HPZ.h>
//#include <Game/Levels/SSZ.h>
//#include <Game/Levels/DEZ.h>
//#include <Game/Levels/TDZ.h>
#include <Game/Levels/SpecialStage.h>

#include <Game/Scenes/LevelSelect.h>

#include <Game/Scenes/MainMenu.h>

int FrameCircle = 0;
int FrameZigzag = 0;
int FrameZigzagRed = 0;
int FrameZigzagBlue = 0;

int frame = 0;
int triframe = 0;
int palframe = 0;
int paletteindexes[9] = {
    68,
    50,
    48,
    23,
    22,
    0x0B,
    0x0A,
    0x09,
    0x07,
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

PUBLIC Scene_MainMenu::Scene_MainMenu(IApp* app, IGraphics* g) {
    App = app;
    G = g;

    Sound::Audio = App->Audio;
    Sound::Init();

	Sound::SoundBank[0] = new ISound("Music/SaveSelectTria.ogg", true);
    Sound::Audio->LoopPoint[0] = 131859;

    MenuSprite = new ISprite("UI/MainMenu.gif", App);
    MenuSprite->LoadAnimation("UI/MainMenu.bin");
    for (int i = 0; i < 9; i++)
        MenuSprite->Palette[paletteindexes[i]] = paletteToCycle[i];
    MenuSprite->TransparentColorIndex = 0x2C;
    MenuSprite->UpdatePalette();

    SuperButtonsSprite = new ISprite("UI/SuperButtons.gif", App);
    SuperButtonsSprite->LoadAnimation("UI/SuperButtons.bin");
    SuperButtonsSprite->Palette[1] = 0x282028;
    SuperButtonsSprite->UpdatePalette();
}

PUBLIC void Scene_MainMenu::Init() {
    App->Audio->ClearMusic();
    App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
    // App->Audio->PushMusic(Sound::SoundBank[0], false, Sound::Audio->LoopPoint[0]);
}

PUBLIC void Scene_MainMenu::Update() {
    if (App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED]) {
        if (selected >= 2)
            selected -= 2;

        Sound::Play(Sound::SFX_MENUBLEEP);
    }
    if (App->Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED]) {
        if (selected <= 1)
            selected += 2;

        Sound::Play(Sound::SFX_MENUBLEEP);
    }

    if (App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED]) {
        if ((selected & 1) == 1)
            selected--;

        Sound::Play(Sound::SFX_MENUBLEEP);
    }
    if (App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED]) {
        if ((selected & 1) == 0)
            selected++;

        Sound::Play(Sound::SFX_MENUBLEEP);
    }

    if (App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED]) {
        App->NextScene = new Scene_LevelSelect(App, G);
    }

    FrameCircle = (FrameCircle + 1) & 0xFF;
    FrameZigzag = (FrameZigzag + 1) % (40 * 4);
    FrameZigzagRed = (FrameZigzagRed + 1) % (117 * 4);
    FrameZigzagBlue = (FrameZigzagBlue + 1) % (110 * 4);

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
    G->DrawRectangle(0, 0, App->WIDTH, App->HEIGHT, 0x0022EE);

    int cenX = App->WIDTH - 164;
    int cenY = App->HEIGHT / 2;

    // BG
    G->DrawSprite(MenuSprite, 0, 0, 0, 0, 0, IE_NOFLIP);

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
    G->DrawSprite(MenuSprite, 1, 0, 0, 0, 0, IE_NOFLIP);
    G->DrawSprite(MenuSprite, 1, 1, 0, App->HEIGHT, 0, IE_NOFLIP);
    G->DrawSprite(MenuSprite, 1, 2, 0, 0, 0, IE_NOFLIP);
    // Menu Title
    G->DrawSprite(MenuSprite, 9, 0, App->WIDTH, 12, 0, IE_NOFLIP);
    G->DrawSprite(MenuSprite, 10, 0, App->WIDTH - 12, 12, 0, IE_NOFLIP);
    /// Triangles
    for (int i = 0; i <= 12; i++)
        G->DrawSprite(MenuSprite, 1, 3, 96, i * 20 - 20 + (frame >> 1), 0, IE_NOFLIP);

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
    G->DrawSprite(MenuSprite, 7, selected, cenX, cenY, 0, IE_NOFLIP);
    G->DrawSprite(MenuSprite, 17, 0, cenX, cenY, 0, IE_NOFLIP);

    // Selection
    for (int i = 0; i < 9; i++)
        MenuSprite->Palette[paletteindexes[i]] = paletteToCycle[(palframe - i + 18) % 18];
    MenuSprite->UpdatePalette();

    G->DrawSprite(MenuSprite, 3 + selected, 3, cenX, cenY, 0, IE_NOFLIP);

    for (int i = 0; i < 9; i++)
        MenuSprite->Palette[paletteindexes[i]] = paletteToCycle[i];
    MenuSprite->UpdatePalette();

    // Spinny Triangle
    G->DrawRectangle(cenX + (-129 + 2), cenY + (-39), 12, 9, 0x000000);
    if (selected == 0)
        G->DrawSprite(MenuSprite, 2, triframe, cenX + (-129 + 2), cenY + (-39), 0, IE_NOFLIP);
    else
        G->DrawSprite(MenuSprite, 2, 0, cenX + (-129 + 2), cenY + (-39), 0, IE_NOFLIP);

    G->DrawRectangle(cenX + (117 - 2), cenY + (-39), 12, 9, 0x000000);
    if (selected == 1)
        G->DrawSprite(MenuSprite, 2, triframe, cenX + (117 - 2), cenY + (-39), 0, IE_NOFLIP);
    else
        G->DrawSprite(MenuSprite, 2, 0, cenX + (117 - 2), cenY + (-39), 0, IE_NOFLIP);

    // Buttons
    G->DrawRectangle(6, App->HEIGHT - 42, 16, 38, 0x000000);
    if (true) {
        G->DrawSprite(SuperButtonsSprite, 1, App->Input->ControllerMaps[0][IInput::I_CONFIRM], 14, App->HEIGHT - 32, 0, IE_NOFLIP);
        G->DrawSprite(SuperButtonsSprite, 1, App->Input->ControllerMaps[0][IInput::I_DENY], 14, App->HEIGHT - 12, 0, IE_NOFLIP);
    }
    else {
        // TODO: When making controllers mappable, use those
        // 2 - Xbox
        // 3 - PS4
        // 4 - Switch
        // 5 - Saturn (Black)
        // 6 - Saturn (White)
        G->DrawSprite(SuperButtonsSprite, 4, 0, 14, App->HEIGHT - 34, 0, IE_NOFLIP);
        G->DrawSprite(SuperButtonsSprite, 4, 1, 14, App->HEIGHT - 12, 0, IE_NOFLIP);
    }
}
