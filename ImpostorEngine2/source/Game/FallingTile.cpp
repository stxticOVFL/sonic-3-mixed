#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Game/Object.h>
#include <Game/Explosion.h>
#include <Game/LevelScene.h>

class FallingTile : public Explosion {
public:
    int Tile = 0;
    int Hold = 0;

    int16_t grv = 0x38;
};

#endif

#include <Game/FallingTile.h>

PUBLIC FallingTile::FallingTile() {
    XSpeed = 0;
    YSpeed = 0;
    VisualLayer = 1;
}

PUBLIC void FallingTile::Update() {
    YSpeed += grv;

    if (Hold > 0) {
        YSpeed = 0;
        Hold--;
    }

    X += XSpeed >> 8;
    Y += YSpeed >> 8;

    if (Y >= Scene->CameraY + App->HEIGHT + 64)
        Active = false;
}

PUBLIC void FallingTile::Render(int CamX, int CamY) {
    G->DrawSprite(Scene->TileSprite, 0, Tile, X - CamX + 8, Y - CamY + 8, 0, (FlipX ? IE_FLIPX : IE_NOFLIP) | (FlipY ? IE_FLIPY : IE_NOFLIP));

	if (App->viewObjectCollision) {
		G->SetDrawAlpha(0x80);
		G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
		G->SetDrawAlpha(0xFF);
	}
}
