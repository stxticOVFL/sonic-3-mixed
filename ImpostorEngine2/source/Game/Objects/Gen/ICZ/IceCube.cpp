// Object ID: 0xB6
// Object Name: IceCube.cpp

#include "IceCube.h"

typedef IMath Math;

void IceCube::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    Scene->AddSelfToRegistry(this, "Breakable");
    BreakableByJump = CollideSide::TOP;
    CurrentAnimation = Sprite->FindAnimation("Ice Cube");
}

void IceCube::Render(int CamX, int CamY) {
    if (!Visible) return;

    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

int IceCube::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (!Solid) return 0;

    if (HitFrom == CollideSide::TOP) {
        Solid = false;
        Visible = false;
        Scene->Players[PlayerID]->YSpeed -= 0x80;
        Scene->Players[PlayerID]->Action = ActionType::Jumping;
        Sound::Play(Sound::SFX_COLLAPSE);
    }

    return 1;
}

