#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Game/Object.h>
#include <Game/Explosion.h>
#include <Game/LevelScene.h>

class Animal : public Explosion {
public:
    int CurrentFrame = 0;
    bool Escaping = false;
    bool HitGround = false;
    uint32_t SubX = 0;
    uint32_t SubY = 0;
	uint32_t Gravity = 0;
    int32_t  JumpSpeed = 0;
};

#endif

#include <Game/Animal.h>

PUBLIC Animal::Animal() {

}

PUBLIC void Animal::Update() {

    if (YSpeed > 0) {
        if (Scene->CollisionAt(X, Y + 8)) {
            Y -= YSpeed >> 8;
            SubY = Y << 16;
            YSpeed = JumpSpeed;

            if (!HitGround) {
                CurrentAnimation++;
                HitGround = true;
            }
        }
    }

    if (HitGround)
        SubX += XSpeed << 8;

    if (HitGround)
        YSpeed += 0x18;
    else
        YSpeed += 0x38;
    SubY += YSpeed << 8;

    X = SubX >> 16;
    Y = SubY >> 16;

    if (X > Scene->CameraX + App->WIDTH + 8)
        Active = false;

    if (X < Scene->CameraX - 8)
        Active = false;

    if (HitGround) {
        if (YSpeed < 0) {
            if (CurrentAnimation == 1 || CurrentAnimation == 11)
                CurrentFrame = (Scene->Frame >> 1) & 1;
            else
                CurrentFrame = 1;
        }
        else
            CurrentFrame = 0;
    }
}

PUBLIC void Animal::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, CurrentFrame, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);

	if (App->viewObjectCollision) {
		G->SetDrawAlpha(0x80);
		G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
		G->SetDrawAlpha(0xFF);
	}
}
