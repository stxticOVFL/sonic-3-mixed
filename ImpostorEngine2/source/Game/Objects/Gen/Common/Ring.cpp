// Object ID: 0x00
// Object Name: Ring.cpp

#include "Ring.h"

typedef IMath Math;

CONSTRUCTER Ring::Ring() {
    if (SaveGame::CurrentMode == 0) {
        Sprite = LevelScene::LoadSpriteFromBin("GlobalS3K/Ring.bin");
    }
    else {
        Sprite = LevelScene::LoadSpriteFromBin("Global/Ring.bin");
    }
    ShouldRingFall = false;
}

void Ring::Create() {
    Object::Create();
    Active = true;
    Timer = 0xFF;
    CleanupInactiveObject = true;
    MyX = 0;
    MyY = 0;
    CurrentAnimation = Sprite->FindAnimation("Normal Ring");
    CurrentFrame = 0;
    MagnetizedTo = -1;
}

void Ring::Update() {
    if (!isHeldDebugObject) {
        if (MagnetizedTo < 0) {
            YSpeed += 0x18;
            if (YSpeed > 0) {
                if (Scene->CollisionAt(X, Y + 8)) {
                    Y -= YSpeed >> 8;
                    YSpeed = -YSpeed * 3 / 4;
                }

            }

            if (YSpeed < 0) {
                if (Scene->CollisionAt(X, Y - 8)) {
                    Y -= YSpeed >> 8;
                    YSpeed = 0;
                }

            }

            if (XSpeed > 0) {
                if (Scene->CollisionAt(X + 8, Y)) {
                    X -= XSpeed >> 8;
                    XSpeed = -XSpeed / 4;
                }

            }

            if (XSpeed < 0) {
                if (Scene->CollisionAt(X - 8, Y)) {
                    X -= XSpeed >> 8;
                    XSpeed = -(XSpeed / 4);
                }

            }

            if (ShouldRingFall) {
                Timer--;
            }

            if (CurrentAnimation < Sprite->Animations.size()) {
                if (CurrentFrame / 0x100 >= Sprite->Animations[CurrentAnimation].FrameCount - 1) {
                    CurrentFrame = Sprite->Animations[CurrentAnimation].FrameToLoop * 0x100;
                }

                if (Sprite->Animations[CurrentAnimation].AnimationSpeed == 4) {
                    CurrentFrame += 0x100;
                }
                else if (Sprite->Animations[CurrentAnimation].AnimationSpeed > 2) {
                    CurrentFrame += Sprite->Animations[CurrentAnimation].AnimationSpeed;
                }
                else if (Sprite->Animations[CurrentAnimation].Frames[CurrentFrame / 0x100].Duration != 0) {
                    CurrentFrame += 0x100 / Sprite->Animations[CurrentAnimation].Frames[CurrentFrame / 0x100].Duration;
                }

            }

        }
        else {
            int PX;
            int PY;
            PX = (Scene->Players[MagnetizedTo]->EZX);
            PY = (Scene->Players[MagnetizedTo]->EZY);
            if (Scene->Players[MagnetizedTo]->Shield != ShieldType::Electric) {
                MagnetizedTo = -1;
            }

            if (PX < X) {
                if (XSpeed < 0) {
                    XSpeed -= 0x30;
                }
                else {
                    XSpeed -= 0xC0;
                }
            }
            else {
                if (XSpeed > 0) {
                    XSpeed += 0x30;
                }
                else {
                    XSpeed += 0xC0;
                }
            }
            if (PY < Y) {
                if (YSpeed < 0) {
                    YSpeed -= 0x30;
                }
                else {
                    YSpeed -= 0xC0;
                }
            }
            else {
                if (YSpeed > 0) {
                    YSpeed += 0x30;
                }
                else {
                    YSpeed += 0xC0;
                }
            }
            if (SaveGame::CurrentMode == 1) {
                CurrentFrame = Scene->RingAnimationFrame;
            }
            else {
                CurrentFrame = Scene->RingAnimationFrame >> 2;
            }
        }
        MyX += XSpeed;
        MyY += YSpeed;
        if (ShouldRingFall) {
            X = MyX >> 8;
            Y = MyY >> 8;
        }

        if (Timer == 0) {
            Active = false;
        }

    }

    Object::Update();
}

void Ring::Render(int CamX, int CamY) {
    if (ShouldRingFall && Timer < 64 && ((Timer >> 1) & 1) == 0) {
        return;
    }

    if (CurrentAnimation <= -1) {
        return;
    }

    G->DrawSprite(Sprite, CurrentAnimation, CurrentFrame >> 8, X - CamX, Y - CamY, 0, IE_NOFLIP);
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawNoCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int Ring::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Scene->Players[PlayerID]->RingAlarm > 0) return 0;

    Scene->Players[PlayerID]->GiveRing(1);
    Sound::Play(Sound::SFX_RING);
    int rx[3];
    int ry[3];
    rx[0] = -4;
    rx[1] = 1;
    rx[2] = 4;
    ry[0] = 1;
    ry[1] = -2;
    ry[2] = 3;
    Active = false;
    return 1;
}

