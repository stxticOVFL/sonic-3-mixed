// Object ID: 0x0C
// Object Name: SwingVine.cpp

#include "SwingVine.h"

typedef IMath Math;

void SwingVine::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    RopeLength = SubType & 0xF;
    AngleOffset = SubType & 0xF0;
    Oscello = 0;
    LastX = X;
    LastY = Y;
    VisW = RopeLength << 4;
    VisH = RopeLength << 4;
    PlayersControlled = 0;
    ClassicStyle = !Scene->Thremixed;
    ClassicStyle = false;
    Timer = 0;
    CurrentAnimation = 26;
}

void SwingVine::Update() {
    int nX;
    int nY;
    int framedAngle;
    int frame;
    Oscello = (Scene->Frame * 168 / 128) & 0xFF;
    nX = InitialX;
    nY = InitialY;
    Rotation = Math::sinHex(Oscello + AngleOffset) * 0x2C;
    framedAngle = Rotation / 8;
    if (ClassicStyle) {
        frame = ((Rotation >> 16) + 4 * Math::sign(Rotation)) / 8;
        for (int i = 0; i < RopeLength; i++)
{
            nX += Math::sinHex((frame & 0x1F) * 8) >> 12;
            nY += Math::cosHex((frame & 0x1F) * 8) >> 12;
            Rotation = Rotation + framedAngle;
            frame = ((Rotation >> 16) + 4 * Math::sign(Rotation)) / 8;
        }
    }
    else {
        frame = Rotation / 0x10000;
        for (int i = 0; i < RopeLength; i++)
{
            nX += Math::sinHex(frame) / 0x1000;
            nY += Math::cosHex(frame) / 0x1000;
            Rotation = Rotation + framedAngle;
            frame = Rotation / 0x10000;
        }
    }
    if (Math::abs(X - nX) > 0) LastX = X;

    if (Math::abs(Y - nY) > 0) LastY = Y;

    X = nX;
    Y = nY;
    for (int i = 0; i < 8; i++)
{
        if (PlayersControlled & (1 << i)) {
            if (!Scene->Players[i]->OnScreen) {
                Scene->Players[i]->ObjectControlled = 0;
                PlayersControlled &= (1 << i) ^ 0xFF;
                Timer = 60;
            }

            if (Scene->Players[i]->Action == ActionType::Dead) {
                Scene->Players[i]->ObjectControlled = 0;
                PlayersControlled &= (1 << i) ^ 0xFF;
                Timer = 60;
                continue;
            }

            if (Scene->Players[i]->InputJump && !Scene->CollisionAt(X - 10, Y - H / 2) && !Scene->CollisionAt(X + 10, Y - H / 2) && !Scene->CollisionAt(X - 10, Y + H / 2) && !Scene->CollisionAt(X + 10, Y + H / 2)) {
                Scene->Players[i]->XSpeed = (X - LastX) * 0x80;
                Scene->Players[i]->YSpeed = (Y - LastY) * 0x80;
                if (Scene->Players[i]->InputLeft) Scene->Players[i]->XSpeed = -0x200;

                if (Scene->Players[i]->InputRight) Scene->Players[i]->XSpeed = 0x200;

                Scene->Players[i]->YSpeed -= 0x380;
                Scene->Players[i]->ObjectControlled = 0;
                Scene->Players[i]->Action = ActionType::Jumping;
                Scene->Players[i]->JumpVariable = 1;
                PlayersControlled &= (1 << i) ^ 0xFF;
                Timer = 60;
            }
            else {
                Scene->Players[i]->EZX = X;
                Scene->Players[i]->EZY = Y - 3 + Scene->Players[i]->H / 2;
                Scene->Players[i]->XSpeed = 0;
                Scene->Players[i]->YSpeed = 0;
                Scene->Players[i]->GrabSwingValue = ((-framedAngle + 0x58000) / 0xB) >> 8;
                if (Scene->Players[i]->GrabSwingValue == 0x100) Scene->Players[i]->GrabSwingValue = 0XFF;

                Scene->Players[i]->Action = ActionType::Grab;
                Scene->Players[i]->ObjectControlled = 0xFF;
            }
        }

    }
    if (Timer > 0) Timer--;

    Object::Update();
}

void SwingVine::Render(int CamX, int CamY) {
    int nX;
    int nY;
    int framedAngle;
    G->DrawSprite(Sprite, CurrentAnimation, 0x21, InitialX - CamX, InitialY - CamY, 0, IE_NOFLIP);
    nX = InitialX;
    nY = InitialY;
    Rotation = Math::sinHex(Oscello + AngleOffset) * 0x2C;
    if (ClassicStyle) {
        if (Rotation < 0) {
            framedAngle = Rotation / 8;
            Frame = ((Rotation >> 16) - 4) / 8;
            G->DrawSprite(Sprite, CurrentAnimation, Frame & 0x1F, nX - CamX, nY - CamY, 0, IE_NOFLIP);
            for (int i = 0; i < RopeLength - 1; i++)
{
                nX += Math::sinHex((Frame & 0x1F) * 8) >> 12;
                nY += Math::cosHex((Frame & 0x1F) * 8) >> 12;
                Rotation = Rotation + framedAngle;
                Frame = ((Rotation >> 16) - 4) / 8;
                G->DrawSprite(Sprite, CurrentAnimation, Frame & 0x1F, nX - CamX, nY - CamY, 0, IE_NOFLIP);
            }
        }
        else {
            framedAngle = Rotation / 8;
            Frame = ((Rotation >> 16) + 4) / 8;
            G->DrawSprite(Sprite, CurrentAnimation, Frame & 0x1F, nX - CamX, nY - CamY, 0, IE_NOFLIP);
            for (int i = 0; i < RopeLength - 1; i++)
{
                nX += Math::sinHex((Frame & 0x1F) * 8) >> 12;
                nY += Math::cosHex((Frame & 0x1F) * 8) >> 12;
                Rotation = Rotation + framedAngle;
                Frame = ((Rotation >> 16) + 4) / 8;
                G->DrawSprite(Sprite, CurrentAnimation, Frame & 0x1F, nX - CamX, nY - CamY, 0, IE_NOFLIP);
            }
        }
    }
    else {
        framedAngle = Rotation / 8;
        Frame = Rotation / 0x10000;
        G->DrawSprite(Sprite, CurrentAnimation, (Frame / 8) & 0x1F, nX - CamX, nY - CamY, Frame - ((Frame / 8) * 8), IE_NOFLIP);
        for (int i = 0; i < RopeLength - 1; i++)
{
            nX += Math::sinHex(Frame) / 0x1000;
            nY += Math::cosHex(Frame) / 0x1000;
            Rotation = Rotation + framedAngle;
            Frame = Rotation / 0x10000;
            G->DrawSprite(Sprite, CurrentAnimation, (Frame / 8) & 0x1F, nX - CamX, nY - CamY, Frame - ((Frame / 8) * 8), IE_NOFLIP);
        }
    }
    G->DrawSprite(Sprite, CurrentAnimation, 0x20, X - CamX, Y - CamY, 0, IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int SwingVine::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Timer == 0 && !(PlayersControlled & (1 << PlayerID))) {
        PlayersControlled |= 1 << PlayerID;
        Sound::Play(Sound::SFX_GRAB);
    }

    return 1;
}

