// Object ID: 0x07
// Object Name: Spring.cpp

#include "Spring.h"

typedef IMath Math;

CONSTRUCTER Spring::Spring() {
    if (SaveGame::CurrentMode == 0) {
        BinIndex = LevelScene::LoadSpriteBin("GlobalS3K/Springs.bin");
    }
    else {
        BinIndex = LevelScene::LoadSpriteBin("Global/Springs.bin");
    }
}

void Spring::Create() {
    Object::Create();
    W = 32;
    H = 16;
    Active = true;
    Priority = false;
    Frame = 0;
    Diagonal = 0;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    Scene->AddSelfToRegistry(this, "Spring");
    SpringType = 1;
    if ((SubType & 0x2) != 0x0) SpringType = 0;

    CurrentAnimation = SpringType;
    Rotation = 0;
    DoAnimate = false;
    CleanupInactiveObject = true;
    SpringPower = 0x1000;
    if (SpringType == 0) SpringPower = 0xA00;

    Twirl = 0;
    KillTransverseSpeed = (SubType & 0x80) == 0x80;
    if ((SubType & 0xF0) == 0x10) {
        W = 18;
        H = 32;
        CurrentAnimation = SpringType + 2;
        Rotation = 270;
        if (FlipX) Rotation = 90;

    }
    else if ((SubType & 0xF0) == 0x20) {
        Rotation = 180;
        FlipY = true;
    }
    else if ((SubType & 0xF0) == 0x30) {
        Diagonal = -1;
        CurrentAnimation = SpringType + 4;
        Solid = false;
        W = 28;
        H = 28;
    }
    else if ((SubType & 0xF0) == 0x40) {
        Diagonal = 1;
        CurrentAnimation = SpringType + 4;
        Solid = false;
        FlipY = true;
        W = 28;
        H = 28;
    }

    if (Rotation == 0) {
        X += 1;
    }

}

void Spring::Update() {
    AutoAnimate = DoAnimate;
    Object::Update();
}

void Spring::OnAnimationFinish() {
    DoAnimate = false;
    Frame = 0;
}

int Spring::OnLeaveScreen() {
    DoAnimate = false;
    Frame = 0;
    return 1;
}

void Spring::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, (FlipX ? IE_FLIPX : IE_NOFLIP) | (FlipY ? IE_FLIPY : IE_NOFLIP));
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int Spring::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Data != 1) return 0;

    if (SpringType == 0) {
        Twirl = (SubType & 0x1);
    }

    if (Scene->Players[PlayerID]->Underwater) Twirl = 1 - Twirl;

    if (Diagonal != 0) {
        Scene->Players[PlayerID]->YSpeed = Diagonal * SpringPower;
        Scene->Players[PlayerID]->Ground = false;
        Scene->Players[PlayerID]->InputAlarm = 16;
        Scene->Players[PlayerID]->Action = ActionType::Spring;
        Scene->Players[PlayerID]->SpringFlip = Twirl;
        Scene->Players[PlayerID]->AngleMode = 0;
        Scene->Players[PlayerID]->Angle = 0;
        Scene->Players[PlayerID]->Vibrate(VibrationType::ImpactSmall);
        Sound::Play(Sound::SFX_SPRING);
        DoAnimate = true;
        if (SubType & 0xC) Scene->Players[PlayerID]->Layer = 1 - ((SubType >> 2) & 0x1);

        if (FlipX) SpringPower = -SpringPower;

        Scene->Players[PlayerID]->XSpeed = SpringPower;
        return 1;
    }

    if (HitFrom == CollideSide::TOP && Rotation == 0 && Scene->Players[PlayerID]->YSpeed >= 0) {
        Scene->Players[PlayerID]->YSpeed = -SpringPower;
        Scene->Players[PlayerID]->Ground = false;
        Scene->Players[PlayerID]->InputAlarm = 16;
        Scene->Players[PlayerID]->Action = ActionType::Spring;
        Scene->Players[PlayerID]->SpringFlip = Twirl;
        Scene->Players[PlayerID]->AngleMode = 0;
        Scene->Players[PlayerID]->Angle = 0;
        Scene->Players[PlayerID]->EZY += 4;
        Scene->Players[PlayerID]->Vibrate(VibrationType::ImpactSmall);
        Sound::Play(Sound::SFX_SPRING);
        DoAnimate = true;
        if (SubType & 0xC) Scene->Players[PlayerID]->Layer = 1 - ((SubType >> 2) & 0x1);

        return 1;
    }
    else if (HitFrom == CollideSide::BOTTOM && Rotation == 180) {
        Scene->Players[PlayerID]->YSpeed = SpringPower;
        Scene->Players[PlayerID]->Ground = false;
        if (SpringType) Scene->Players[PlayerID]->InputAlarm = 16;

        Scene->Players[PlayerID]->Action = ActionType::Jumping;
        Scene->Players[PlayerID]->SpringFlip = Twirl;
        Scene->Players[PlayerID]->AngleMode = 0;
        Scene->Players[PlayerID]->Angle = 0;
        Scene->Players[PlayerID]->EZY += 4;
        Scene->Players[PlayerID]->Vibrate(VibrationType::ImpactSmall);
        Sound::Play(Sound::SFX_SPRING);
        DoAnimate = true;
        if (SubType & 0xC) Scene->Players[PlayerID]->Layer = 1 - ((SubType >> 2) & 0x1);

        return 1;
    }
    else if ((Rotation == 90 && HitFrom == CollideSide::LEFT) || (Rotation == 270 && HitFrom == CollideSide::RIGHT)) {
        if (Scene->Players[PlayerID]->Y + 20 - 4 - 4 <= Y - 16 || !Scene->Players[PlayerID]->Ground) return 0;

        int ToFlip = -Math::sign(Math::cosHex(Scene->Players[PlayerID]->AngleMode * 0x40 - Rotation + 0x40));
        Scene->Players[PlayerID]->Flip = ToFlip;
        if (Scene->Players[PlayerID]->AngleMode == 0 || Scene->Players[PlayerID]->AngleMode == 2) {
            if (HitFrom == CollideSide::RIGHT) {
                Scene->Players[PlayerID]->GroundSpeed = SpringPower;
                Scene->Players[PlayerID]->DisplayFlip = 1;
            }
            else {
                Scene->Players[PlayerID]->GroundSpeed = -SpringPower;
                Scene->Players[PlayerID]->DisplayFlip = -1;
            }
        }

        Scene->Players[PlayerID]->InputAlarm = 16;
        if (SubType & 0xC) Scene->Players[PlayerID]->Layer = 1 - ((SubType >> 2) & 0x1);

        Scene->Players[PlayerID]->Vibrate(VibrationType::ImpactSmall);
        Sound::Play(Sound::SFX_SPRING);
        DoAnimate = true;
        return 1;
    }

    return 0;
}

void Spring::UpdateSubType() {
    Diagonal = 0;
    SpringType = 1;
    if ((SubType & 0x2) != 0x0) SpringType = 0;

    CurrentAnimation = SpringType;
    Rotation = 0;
    DoAnimate = false;
    SpringPower = 0x1000;
    if (SpringType == 0) SpringPower = 0xA00;

    KillTransverseSpeed = (SubType & 0x80) == 0x80;
    if ((SubType & 0xF0) == 0x10) {
        W = 18;
        H = 32;
        CurrentAnimation = SpringType + 2;
        Rotation = 270;
        if (FlipX) Rotation = 90;

    }
    else if ((SubType & 0xF0) == 0x20) {
        Rotation = 180;
        FlipY = true;
    }
    else if ((SubType & 0xF0) == 0x30) {
        Diagonal = -1;
        CurrentAnimation = SpringType + 4;
        Solid = false;
        W = 28;
        H = 28;
    }
    else if ((SubType & 0xF0) == 0x40) {
        Diagonal = 1;
        CurrentAnimation = SpringType + 4;
        Solid = false;
        FlipY = true;
        W = 28;
        H = 28;
    }

}

uint8_t Spring::GetSubTypeIncrement() {
    return 0x10;
}

uint8_t Spring::GetSubTypeMax() {
    return 0x40;
}

