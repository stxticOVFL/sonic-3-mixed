// Object ID: 0x85
// Object Name: SpecialRing.cpp

#include "SpecialRing.h"

typedef IMath Math;

void SpecialRing::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    W = 8;
    H = 64;
    VisW = 64;
    VisH = 64;
	Scale = 0;
    HyperColor = 0xFFFF00;
    HyperRing = true;
    percent = 0;
    if (Scene->ZoneID >= 7 && (SaveGame::GetEmeralds() & 0x7F) == 0x7F) {
        HyperRing = 1;
    }
    else {
        HyperRing = 0;
    }
    GoTimer = -1;
    StoredX = 0;
    StoredY = 0;
    RingID = SubType & 0x7F;
    Used = (SaveGame::CurrentUsedZoneRings >> RingID & 1) == 1;
    CleanupInactiveObject = true;
}

void SpecialRing::Update() {
	if (OnScreen)
	{
		if (Scale < 1) Scale += 0.01;

		if (this->HyperRing) {
			Timer = Scene->Frame << 5 & 0x7FF;
			if (Timer < 0x200) {
				percent = (Timer - 0x000) & 0x1FF;
				if (percent >= 0x100) percent = (percent & 0xFF) ^ 0xFF;

				HyperColor = G->ColorBlendHex(0xF2D141, 0x6181F2, percent);
			}
			else if (Timer < 0x400) {
				percent = (Timer - 0x200) & 0x1FF;
				if (percent >= 0x100) percent = (percent & 0xFF) ^ 0xFF;

				HyperColor = G->ColorBlendHex(0xF2D141, 0x41C241, percent);
			}
			else if (Timer < 0x600) {
				percent = (Timer - 0x400) & 0x1FF;
				if (percent >= 0x100) percent = (percent & 0xFF) ^ 0xFF;

				HyperColor = G->ColorBlendHex(0xF2D141, 0xF28141, percent);
			}
			else if (Timer < 0x800) {
				percent = (Timer - 0x600) & 0x1FF;
				if (percent >= 0x100) percent = (percent & 0xFF) ^ 0xFF;

				HyperColor = G->ColorBlendHex(0xF2D141, 0x8141F2, percent);
			}

		}

		if (GoTimer > 0) {
			Scene->Player->EZX = StoredX;
			Scene->Player->EZY = StoredY;
			GoTimer--;
		}

		if (GoTimer == 0) {
			Scene->FadeAction = 7;
			Scene->FadeTimerMax = 48 + 48;
			Scene->FadeMax = 0x200;
			G->FadeToWhite = true;
			Sound::Play(Sound::SFX_SS_WARP);
			GoTimer = -1;
			Active = false;
		}

		if (GoTimer > 0) {
			Sprite = Scene->Objects3Sprite;
			int LoopPoint = Sprite->Animations[CurrentAnimation].FrameToLoop;
			int FrameCount = Sprite->Animations[CurrentAnimation].FrameCount;
			if (Sprite->Animations[CurrentAnimation].AnimationSpeed > 0 && Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration != 0) Frame += ((0x100 * Sprite->Animations[CurrentAnimation].AnimationSpeed * 0x100) >> 8) / Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration;

			if (Frame >= FrameCount * 0x100) {
				Frame = FrameCount * 0x100 - 0x100;
			}

		}
	}
	else
	{
		Scale = 0.05;
	}
	Object::Update();
}

void SpecialRing::Render(int CamX, int CamY) {
    if (GoTimer >= 0) {
        G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, (Frame >> 8) < 8);
        return;
    }

    if (Used) {
        G->DrawModelOn2D(Scene->GiantRingModel, this->X - CamX, this->Y - CamY, Scale, 0, Scene->Frame & 0xFF, (Scene->Frame / 5) & 0xFF, 0x999999, true);
    }
    else {
        G->DrawModelOn2D(Scene->GiantRingModel, this->X - CamX, this->Y - CamY, Scale, 0, Scene->Frame & 0xFF, (Scene->Frame / 5) & 0xFF, HyperColor, false);
    }
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int SpecialRing::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (PlayerID != 0) return 0;

    if (GoTimer >= 0) return 0;

    if (Used) return 0;

    if ((SaveGame::GetEmeralds() >= 0x3FFF && HyperRing) || ((SaveGame::GetEmeralds() & 0x7F) == 0x7F && !HyperRing)) {
        Scene->Player->GiveRing(50);
        Active = false;
    }
    else if (HyperRing) {
		if (SaveGame::SuperEmeraldRoomActivated) {

		}
        else if ((SaveGame::GetEmeralds() & 0x7F) != 0x7F) {
            Scene->Player->ObjectControlled = 0xFF;
            Scene->Player->Hidden = true;
            Scene->StopTimer = true;
            GoTimer = 48;
            StoredX = Scene->Player->EZX;
            StoredY = Scene->Player->EZY;
            App->Audio->FadeMusic(1.0);
            Scene->SaveState();
            SaveGame::SetUsedZoneRings(RingID);
            SaveGame::Flush();
			App->Print(0, "Hyper");
            Frame = 0;
            CurrentAnimation = 0;
        }
    }
    else {
        Scene->Player->ObjectControlled = 0xFF;
        Scene->Player->Hidden = true;
        Scene->StopTimer = true;
        GoTimer = 48;
        StoredX = Scene->Player->EZX;
        StoredY = Scene->Player->EZY;
        App->Audio->FadeMusic(1.0);
        Scene->SaveState();
        SaveGame::SetUsedZoneRings(RingID);
        SaveGame::Flush();
        Frame = 0;
        CurrentAnimation = 0;
    }
    Sound::Play(Sound::SFX_ENTER_SS_RING);
    return 1;
}

