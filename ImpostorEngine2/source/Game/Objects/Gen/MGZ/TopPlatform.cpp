// Object ID: 0x5B
// Object Name: TopPlatform.cpp

#include "TopPlatform.h"

typedef IMath Math;

void TopPlatform::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    CurrentAnimation = 11;
    W = 48;
    H = 24;
    VisW = 48;
    VisH = 24;
    InUse = false;
    Gravity = 0x50;
    PlayerUsed = -1;
}

void TopPlatform::Update() {
    if (PlayerUsed == -1) {
        Player = NULL;
        return;
    }

    Player = Scene->Players[PlayerUsed];
    if (Player->Action == ActionType::Hurt || Player->InputJump) {
        Gravity = 0xFF;
        PlayerUsed = -1;
        InUse = false;
    }

    Player->SubX = SubX;
    Player->SubY = (Y - 32) << 16;
    Player->Ground = true;
    YSpeed = (Math::abs(Player->XSpeed) / 3) * -1;
    if (Math::abs(XSpeed / 7 + (XFriction / 1.1)) > 0x250) {
        XSpeed = XSpeed > 0 ? 0x250 : -0x250;
        XFriction /= 1.1;
    }
    else {
        XSpeed = Player->XSpeed / 7 + (XFriction / 1.1);
        XFriction = XSpeed;
    }
    if (Player->Action == ActionType::CrouchDown) {
        Gravity = 0xE0;
    }
    else if (Player->Action == ActionType::LookUp) {
        Gravity = -0x40;
    }
    else {
        Gravity = 0x50;
    }
    Object::Update();
}

void TopPlatform::MoveSprite() {
    YSpeed += Gravity;
    SubX += XSpeed << 8;
    SubY += YSpeed << 8;
    if (InUse) {
        Player->SubX = SubX;
        Player->SubY = (Y - 32) << 16;
        if (YSpeed > 0) {
            if (Scene->CollisionAt(X - (W / 2), Y + (H / 2), this)) {
                SubY -= YSpeed << 8;
            }

        }

        if (YSpeed < 0) {
            if (Scene->CollisionAt(Player->X - (Player->W / 2), Player->Y - (Player->H / 2))) {
                SubY -= YSpeed << 8;
            }
            else if (Scene->CollisionAt(X - (W / 2), Y - (H / 2), this)) {
                SubY -= YSpeed << 8;
            }

        }

        if (XSpeed > 0) {
            if (Scene->CollisionAt(X + (W / 2), Y - (H / 2), this)) {
                SubX -= XSpeed << 8;
            }
            else if (Scene->CollisionAt(Player->X + (Player->W / 2), Player->Y - (Player->H / 2))) {
                SubX -= XSpeed << 8;
            }

        }

        if (XSpeed < 0) {
            if (Scene->CollisionAt(X - (W / 2), Y - (H / 2), this)) {
                SubX -= XSpeed << 8;
            }
            else if (Scene->CollisionAt(Player->X - (Player->W / 2) - 2, Y - (Player->H / 2))) {
                SubX -= XSpeed << 8;
            }

        }

    }

}

void TopPlatform::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, IE_NOFLIP);
    if (true) {
        G->DrawRectangle((X - (W / 2)) - CamX, (Y + (H / 2)) - CamY, W, 2, DrawCollisionsColor);
        G->DrawRectangle((X - (W / 2)) - CamX, (Y - (H / 2)) - CamY, W, 2, DrawCollisionsColor);
        G->DrawRectangle((X + (W / 2)) - CamX, (Y - (H / 2)) - CamY, 2, H, DrawCollisionsColor);
        G->DrawRectangle((X - (W / 2)) - CamX, (Y - (H / 2)) - CamY, 2, H, DrawCollisionsColor);
        if (InUse) {
            G->DrawRectangle((Player->X - (Player->W / 2)) - CamX, (Player->Y - (Player->H / 2)) - CamY, Player->W, 2, DrawCollisionsColor);
            G->DrawRectangle((Player->X + (Player->W / 2)) - CamX, (Player->Y - (Player->H / 2)) - CamY, 2, Player->H, DrawCollisionsColor);
            G->DrawRectangle(((Player->X - (Player->W / 2)) - 2) - CamX, (Player->Y - (Player->H / 2)) - CamY, 2, Player->H, DrawCollisionsColor);
        }

    }

    }

int TopPlatform::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (HitFrom == CollideSide::TOP && !InUse) {
        InUse = true;
        PlayerUsed = PlayerID;
        Y -= 2;
    }

    return 1;
}

