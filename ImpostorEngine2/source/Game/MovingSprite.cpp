#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Game/Object.h>
#include <Game/Explosion.h>
#include <Game/LevelScene.h>

class MovingSprite : public Explosion {
public:
    int Hold = 0;
    uint32_t SubX = 0;
    uint32_t SubY = 0;

    int16_t Gravity = 0x38;

    int Left = 0;
    int Top = 0;
    int Width = 1;
    int Height = 1;

    int OffX = 0;
    int OffY = 0;

    int bufferID = -2;

    int LifeSpan = -1;
};

#endif

#include <Game/MovingSprite.h>

PUBLIC MovingSprite::MovingSprite() {
    XSpeed = 0;
    YSpeed = 0;
    VisualLayer = 1;
    Frame = 0;
    AutoAnimate = true;
}

PUBLIC void MovingSprite::Update() {
    if (Left >= 0) {
        if (bufferID == -2) {
            bufferID = -1;
            G->MakeFrameBufferID(Sprite, &bufferID, Left, Top, Width, Height, OffX, OffY, FlipX | FlipY << 1);
            G->MakeAllTexturesAndFrameBuffers();
        }
    }

    if (Hold > 0) {
        YSpeed = 0;
        Hold--;
    }

    SubX += XSpeed << 8;
    SubY += YSpeed << 8;

    YSpeed += Gravity;

    X = SubX >> 16;
    Y = SubY >> 16;

    if (LifeSpan > 0) {
        LifeSpan--;
    }

    int ext = -Height / 2;
    if (Left < 0) {
        Animate();
		if (CurrentAnimation < Sprite->Animations.size())
		{
			ext = Sprite->Animations[CurrentAnimation].Frames[Frame].OffY;
		}
		else
		{
			ext = App->NullSprite->Animations[0].Frames[0].OffY;
		}
    }

    if (Y + ext >= Scene->CameraY + App->HEIGHT || LifeSpan == 0) {
        Active = false;

        if (bufferID >= 0) {
            G->DeleteBufferID(bufferID);
            bufferID = -1;
        }
    }
}

PUBLIC void MovingSprite::OnAnimationFinish() {
	
}

PUBLIC void MovingSprite::Render(int CamX, int CamY) {
    if (Left >= 0) {
        if (bufferID >= 0) {
            G->DrawSpriteBuffered(Sprite, bufferID, X - CamX, Y - CamY, 0, 1);
        }
        else {
            G->DrawSprite(Sprite, Left, Top, Width, Height, X - CamX, Y - CamY, 0, FlipX | FlipY << 1, OffX, OffY);
        }
    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX | FlipY << 1);
    }
}
