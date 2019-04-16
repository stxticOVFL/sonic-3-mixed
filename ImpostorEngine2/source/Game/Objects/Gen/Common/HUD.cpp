// Object ID: 0xFFFFFFFF
// Object Name: HUD.cpp

#include "HUD.h"

typedef IMath Math;

void HUD::Create() {
    Object::Create();
}

void HUD::Update() {
    if (Scene->Player) {
        if (Scene->LevelCardTimer >= 1.5 && Scene->Player->Action != ActionType::Dead && !Scene->StopTimer) {
            Scene->Timer++;
        }

    }

    if (Scene->Timer > 10 * 60 * 60 - 1) Scene->Timer = 10 * 60 * 60 - 1;

    Object::Update();
}

void HUD::Render(int CamX, int CamY) {
    bool Mobile;
    Mobile = IApp::Mobile;
    int value;
    int valen;
    int STR_X;
    STR_X = 16 - (Scene->HUDAnim >> 1);
    if (SaveGame::CurrentMode == 0) {
    }

    G->DrawSprite(Scene->GlobalDisplaySprite, 0, 0, STR_X, 12, 0, IE_NOFLIP);
    G->DrawSprite(Scene->GlobalDisplaySprite, 0, 1, STR_X, 28, 0, IE_NOFLIP);
    int CurrentFrame;
    CurrentFrame = 3;
    if (Scene->Player->Rings == 0 && (Scene->Frame & 0xF) < 8) CurrentFrame = 4;

    G->DrawSprite(Scene->GlobalDisplaySprite, 0, CurrentFrame, STR_X, 44, 0, IE_NOFLIP);
    value = Scene->Score;
    for (int i = 0; i < 7 && (value > 0 || (value == 0 && i == 0)); i++)
{
        G->DrawSprite(Scene->GlobalDisplaySprite, 1, value % 10, STR_X + 48 + 8 * 7 - 8 * i - 8, 12 + 14, 0, IE_NOFLIP);
        value /= 10;
    }
    G->DrawSprite(Scene->GlobalDisplaySprite, 0, 12, STR_X + 48 + 8 * 1 - 8 + 3, 28 + 14 - 16, 0, IE_NOFLIP);
    value = (Scene->Timer % 60) * 100 / 60;
    if (Scene->Timer >= 10 * 60 * 60 - 3) value = 99;

    for (int i = 0; i < 2; i++)
{
        G->DrawSprite(Scene->GlobalDisplaySprite, 1, value % 10, STR_X + 48 + 8 * 7 - 8 * i - 8, 28 + 14, 0, IE_NOFLIP);
        value /= 10;
    }
    value = (Scene->Timer / 60) % 60;
    for (int i = 0; i < 2; i++)
{
        G->DrawSprite(Scene->GlobalDisplaySprite, 1, value % 10, STR_X + 48 + 8 * 4 - 8 * i - 9, 28 + 14, 0, IE_NOFLIP);
        value /= 10;
    }
    value = (Scene->Timer / 60 / 60);
    if (value > 9) value = 9;

    G->DrawSprite(Scene->GlobalDisplaySprite, 1, value % 10, STR_X + 48 + 8 * 1 - 10, 28 + 14, 0, IE_NOFLIP);
    if (!Scene->maxLayer) {
        value = Scene->ObjectCount;
    }
    else {
        value = Scene->Player->Rings;
    }
    for (int i = 0; i < 7 && (value > 0 || (value == 0 && i == 0)); i++)
{
        G->DrawSprite(Scene->GlobalDisplaySprite, 1, value % 10, STR_X + 48 + 8 * 7 - 8 * i - 8, 44 + 14, 0, IE_NOFLIP);
        value /= 10;
    }
    int iconX;
    iconX = STR_X;
    int iconY;
    iconY = App->HEIGHT - 12;
    if (Mobile) {
        iconX = App->WIDTH - 64 - 8 - STR_X;
        iconY = 12 + 17;
    }

    G->DrawSprite(Scene->GlobalDisplaySprite, 2, int(Scene->Player->Character), iconX, iconY, 0, IE_NOFLIP);
    if (SaveGame::CurrentMode == 1) G->DrawSprite(Scene->GlobalDisplaySprite, 0, 14, iconX, iconY, 0, IE_NOFLIP);

    int LifeNumberAnim;
    LifeNumberAnim = 1;
    if (!SaveGame::CurrentMode == 1) LifeNumberAnim = 10;

    valen = 1;
    value = Scene->Player->Lives;
    if (value >= 10) valen = 2;

    if (value >= 99) value = 99;

    for (int i = 0; i < valen; i++)
{
        G->DrawSprite(Scene->GlobalDisplaySprite, LifeNumberAnim, value % 10, iconX + 32 + 2 * 8 - i * 8, iconY, 0, IE_NOFLIP);
        value /= 10;
    }
    }

