// Object ID: 0x34
// Object Name: StarPost.cpp

#include "StarPost.h"

typedef IMath Math;

CONSTRUCTER StarPost::StarPost() {
    if (SaveGame::CurrentMode == 0) {
        BinIndex = LevelScene::LoadSpriteBin("GlobalS3K/StarPost.bin");
    }
    else {
        BinIndex = LevelScene::LoadSpriteBin("Global/StarPost.bin");
    }
}

void StarPost::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    DoDeform = false;
    W = 16;
    H = 64;
    Rotation = 0;
    Activated = false;
    Spin = 0;
    Blinking = false;
    this->Frame = 0;
    CleanupInactiveObject = true;
    ShowStars = false;
    StarTimer = 0x200;
    Stars[0] = Scene->AddNewObject(Obj_WarpStars, 0, X, Y - 64, FlipX, false);
    Stars[1] = Scene->AddNewObject(Obj_WarpStars, 1, X, Y - 64, FlipX, false);
    Stars[2] = Scene->AddNewObject(Obj_WarpStars, 2, X, Y - 64, FlipX, false);
    Stars[3] = Scene->AddNewObject(Obj_WarpStars, 3, X, Y - 64, FlipX, false);
    Stars[0]->Active = false;
    Stars[1]->Active = false;
    Stars[2]->Active = false;
    Stars[3]->Active = false;
}

void StarPost::Update() {
    if (!isHeldDebugObject) {
        for (int i = 0; i < 20; i++)
{
            if (Scene->CollisionAt(this->X, this->Y + H / 2 - 1)) {
                this->Y -= 1;
            }

        }
        if (Scene->Checkpoint > this->SubType) {
            this->Blinking = true;
        }

        if (this->Activated && this->Spin < 32) {
            this->Spin++;
        }

        if (this->Spin == 32) {
            this->Blinking = true;
        }

        if (this->Blinking) {
            this->Frame = ((Scene->Frame >> 2) & 0x1);
        }

        if (ShowStars) {
            if (StarTimer == 0x200) {
                Stars[0]->Active = true;
                Stars[1]->Active = true;
                Stars[2]->Active = true;
                Stars[3]->Active = true;
            }

            if (StarTimer > 0) {
                StarTimer--;
            }
            else {
                StarTimer = 0;
                ShowStars = false;
            }
        }
		else
		{
			Stars[0]->Active = false;
			Stars[1]->Active = false;
			Stars[2]->Active = false;
			Stars[3]->Active = false;
		}

    }

    Object::Update();
}

int StarPost::OnLeaveScreen() {
    if (this->Activated && this->Spin < 32) this->Spin = 32;

    return 1;
}

void StarPost::DrawStar(int Rock, int Ang, int Side, int CamX, int CamY) {
    int cosval = (Math::cosHex(Rock) * 16) >> 16;
    int xx = (cosval * Math::cosHex(Ang)) >> 16;
    int yy = (cosval * Math::sinHex(Ang)) >> 16;
    if (Math::sinHex(Rock) * Side >= 0) {
        G->DrawSprite(Sprite, Sprite->Animations[5].Frames[0].X, Sprite->Animations[5].Frames[0].Y, Sprite->Animations[5].Frames[0].W, Sprite->Animations[5].Frames[0].H, X - CamX + xx, Y - CamY + yy, 0, IE_NOFLIP, Sprite->Animations[5].Frames[0].OffX, Sprite->Animations[5].Frames[0].OffY);
    }

}

void StarPost::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, 0, 0, this->X - CamX, this->Y - CamY, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, 1 + Frame, Frame, this->X - CamX + (Math::sinHex(this->Spin << 4) >> 13), this->Y - CamY - 16 - (Math::cosHex(this->Spin << 4) >> 13), 0, IE_NOFLIP);
    if (ShowStars) {
    }

    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int StarPost::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (!this->Blinking) this->Activated = true;

    if (Scene->Checkpoint < this->SubType) {
        Scene->Checkpoint = this->SubType;
        Scene->SavedPositionX = X;
        Scene->SavedPositionY = Y + H / 2 - 16;
        if (Scene->Players[PlayerID]->Rings >= 25) {
            ShowStars = true;
        }

        Sound::Play(Sound::SFX_STARPOST);
    }

    return 1;
}

