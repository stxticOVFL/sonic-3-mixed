// Object ID: 0xFFFFFFFF
// Object Name: WarpStars.cpp

#include "WarpStars.h"

typedef IMath Math;

CONSTRUCTER WarpStars::WarpStars() {
	if (SaveGame::CurrentMode == 0) {
		BinIndex = LevelScene::LoadSpriteBin("GlobalS3K/StarPost.bin");
	}
	else {
		BinIndex = LevelScene::LoadSpriteBin("Global/StarPost.bin");
	}
}

void WarpStars::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    DoDeform = false;
    W = 16;
    H = 16;
    Rotation = 0;
    Activated = true;
    Frame = 0;
	CurrentAnimation = Sprite->FindAnimation("Stars 1");
    CleanupInactiveObject = false;
}

void WarpStars::Update() {
    Object::Update();
}

void WarpStars::Render(int CamX, int CamY) {
	if (Active)
	{
		//Draw Star
		G->DrawSprite(Sprite, CurrentAnimation, 0, this->X - CamX, this->Y - CamY, 0, IE_NOFLIP);

		if (App->viewObjectCollision) {
			G->SetDrawAlpha(0x80);
			G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
			G->SetDrawAlpha(0xFF);
		}
	}
   }

int WarpStars::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
	if (PlayerID != 0) return 0;
	if (!Active) return 0;

	Scene->Player->ObjectControlled = 0xFF;
	Scene->Player->Hidden = true;
	Scene->StopTimer = true;
	//GoTimer = 48;
	//StoredX = Scene.Player.EZX;
	//StoredY = Scene.Player.EZY;
	App->Audio->FadeMusic(1.0);

	Scene->SaveState();

	Scene->NextBonusStage = Math::randRange(0, 2);
	Scene->FadeAction = 5;

	Scene->FadeTimerMax = 48 + 48;
	Scene->FadeMax = 0x200;

	return 1;
}

