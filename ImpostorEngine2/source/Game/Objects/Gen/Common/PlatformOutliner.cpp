// Object ID: 0xFFFFFFFF
// Object Name: PlatformOutliner.cpp

#include "PlatformOutliner.h"

typedef IMath Math;

CONSTRUCTER PlatformOutliner::PlatformOutliner() {
    BinIndex = LevelScene::LoadSpriteBin("Global/TicMark.bin");
}

void PlatformOutliner::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    DoDeform = false;
    VisualLayer = 1;
    CurrentAnimation = Sprite->FindAnimation("TickMark");
    W = 16;
    H = 16;
}

void PlatformOutliner::Update() {
    if (Parent == NULL) {
        return;
    }

    MoveWithParent();
    if (IsParentFloatingPlatform()) {
        if (Scene->ZoneID == 1 || Scene->ZoneID == 3) {
            Y -= 2;
        }

    }

    Object::Update();
}

void PlatformOutliner::OnAnimationFinish() {
}

void PlatformOutliner::Render(int CamX, int CamY) {
    if (!Visible) {
        return;
    }

    if (Parent == NULL) {
        return;
    }

    int32_t widthPixels = W;
    int32_t heightPixels = H;
    int32_t x0 = (X + widthPixels / -2) - CamX;
    int32_t x1 = (X + widthPixels / 2) - CamX;
    int32_t y0 = (Y + heightPixels / -2) - CamY;
    int32_t y1 = (Y + heightPixels / 2) - CamY;
    int32_t FlipYOnly = 0 | 1 << 1;
    int32_t FlipBoth = 1 | 1 << 1;
    G->DrawLine(x0, y0, x0, y1, 0xFFFFFFFF);
    G->DrawLine(x0, y0, x1, y0, 0xFFFFFFFF);
    G->DrawLine(x1, y1, x0, y1, 0xFFFFFFFF);
    G->DrawLine(x1, y1, x1, y0, 0xFFFFFFFF);
    G->DrawSprite(Sprite, CurrentAnimation, 0, x0 + 1, y0 + 1, 0, 0);
    G->DrawSprite(Sprite, CurrentAnimation, 0, x0 + 1, y1, 0, FlipYOnly);
    G->DrawSprite(Sprite, CurrentAnimation, 0, x1, y0 + 1, 0, 1);
    G->DrawSprite(Sprite, CurrentAnimation, 0, x1, y1, 0, FlipBoth);
    }

