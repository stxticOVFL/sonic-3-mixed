// Object ID: 0xFFFFFFFF
// Object Name: StarPointerOrbs.cpp

#include "StarPointerOrbs.h"

typedef IMath Math;

CONSTRUCTER StarPointerOrbs::StarPointerOrbs() {
    BinIndex = LevelScene::LoadSpriteBin("ICZ/Star Pointer.bin");
}

void StarPointerOrbs::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Frame = 1;
    W = 32;
    H = 32;
}

void StarPointerOrbs::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    }

int StarPointerOrbs::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (!Scene->Players[PlayerID]) return 0;

    if (Scene->Players[PlayerID]->Shield == ShieldType::None) Scene->Players[PlayerID]->Hurt(Scene->Players[PlayerID]->X, false);
    else Active = false;
    return 1;
}

