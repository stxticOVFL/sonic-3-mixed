#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Game/Object.h>
#include <unordered_map>

class Ring : public Object {
public:
    uint32_t MyX = 0;
    uint32_t MyY = 0;
    int CurrentFrame = 0;
    int MagnetizedTo = -1;
    bool ShouldRingFall = true;
};

#endif

#include <Game/Ring.h>
#include <Game/Sound.h>
#include <Game/Explosion.h>

#include <Game/Objects/Gen/ObjectListing.h>

PUBLIC Ring::Ring() {
    Timer = 0xFF;
    CleanupInactiveObject = true;
}

PUBLIC void Ring::Update() {
    // If bouncing ring:
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

        ISprite::Animation ani = Scene->ItemsSprite->Animations[7];

        if (CurrentFrame / 0x100 >= ani.FrameCount - 1) {
            CurrentFrame = ani.FrameToLoop * 0x100;
        }

        if (ani.AnimationSpeed == 4) {
            CurrentFrame += 0x100;
        } else if (ani.AnimationSpeed > 2) {
            CurrentFrame += ani.AnimationSpeed;
        } else if (ani.Frames[CurrentFrame / 0x100].Duration != 0) {
            CurrentFrame += 0x100 / ani.Frames[CurrentFrame / 0x100].Duration;
        }
    }
    // If magnetized to a player
    else {
        int PX = (Scene->Players[MagnetizedTo]->EZX);
        int PY = (Scene->Players[MagnetizedTo]->EZY);

        if (Scene->Players[MagnetizedTo]->Shield != ShieldType::Electric) {
            MagnetizedTo = -1;
        }

        if (PX < X) {
            if (XSpeed < 0) {
                XSpeed -= 0x30;
            } else {
                XSpeed -= 0xC0;
            }
        } else {
            if (XSpeed > 0) {
                XSpeed += 0x30;
            } else {
                XSpeed += 0xC0;
            }
        }
        if (PY < Y) {
            if (YSpeed < 0) {
                YSpeed -= 0x30;
            } else {
                YSpeed -= 0xC0;
            }
        } else {
            if (YSpeed > 0) {
                YSpeed += 0x30;
            } else {
                YSpeed += 0xC0;
            }
        }

        if (SaveGame::CurrentMode == 1) {
            CurrentFrame = Scene->RingAnimationFrame;
        } else {
            CurrentFrame = Scene->RingAnimationFrame >> 2;
        }
    }

    MyX += XSpeed;
    MyY += YSpeed;
    
    if (ShouldRingFall) {
        X = MyX >> 8;
        Y = MyY >> 8;
    }

    if (Timer == 0)
        Active = false;
}

PUBLIC void Ring::Render(int CamX, int CamY) {
    if (ShouldRingFall && Timer < 64 && ((Timer >> 1) & 1) == 0) return;

    G->DrawSprite(Scene->ItemsSprite, 7, CurrentFrame >> 8, X - CamX, Y - CamY, 0, IE_NOFLIP);

	if (App->viewObjectCollision) {
		G->SetDrawAlpha(0x80);
		G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawNoCollisionsColor);
		G->SetDrawAlpha(0xFF);
	}
}

PUBLIC int Ring::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Scene->Players[PlayerID]->RingAlarm > 0) return 0;

    Scene->Players[PlayerID]->GiveRing(1);
    Sound::Play(Sound::SFX_RING);

    int rx[3] = { -4, 1, 4 };
    int ry[3] = { 1, -2, 3 };
    if (SaveGame::CurrentMode == 1) {
        for (int i = 0; i < 3; i++) {
            Explosion* ringsparkle;
            ringsparkle = new Explosion();
            ringsparkle->G = G;
            ringsparkle->App = App;
            ringsparkle->CurrentAnimation = 9;
            ringsparkle->FlipX = false;
            ringsparkle->Active = true;
            ringsparkle->Sprite = Scene->ItemsSprite;
            ringsparkle->X = X + rx[i];
            ringsparkle->Y = Y + ry[i];
            Scene->TempObjects.push_back(ringsparkle);
        }
    } else {
        Explosion* ringsparkle;
        ringsparkle = new Explosion();
        ringsparkle->G = G;
        ringsparkle->App = App;
        ringsparkle->CurrentAnimation = 9;
        ringsparkle->FlipX = false;
        ringsparkle->Active = true;
        ringsparkle->Sprite = Scene->ItemsSprite;
        ringsparkle->X = X;
        ringsparkle->Y = Y;
        Scene->TempObjects.push_back(ringsparkle);
    }

    Active = false;
    return 1;
}