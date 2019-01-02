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

    int bufferID = -1;
};

#endif

#include <Game/MovingSprite.h>

PUBLIC MovingSprite::MovingSprite() {
    XSpeed = 0;
    YSpeed = 0;
    VisualLayer = 1;
}

PUBLIC void MovingSprite::Update() {
    if (bufferID == -1) {
        bufferID = G->MakeFrameBufferID(Sprite, Left, Top, Width, Height, OffX, OffY);
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

    ISprite::Animation ani = Sprite->Animations[CurrentAnimation];

    if (CurrentFrame / 0x100 >= ani.FrameCount - 1) {
        CurrentFrame = ani.FrameToLoop * 0x100;
    }

    if (ani.AnimationSpeed == 4)
        CurrentFrame += 0x100;
    else if (ani.AnimationSpeed > 2)
        CurrentFrame += ani.AnimationSpeed;
    else if (ani.Frames[CurrentFrame / 0x100].Duration != 0)
        CurrentFrame += 0x100 / ani.Frames[CurrentFrame / 0x100].Duration;

    if (Y + ani.Frames[CurrentFrame / 0x100].OffY >= Scene->CameraY + App->HEIGHT) {
        Active = false;

        if (bufferID >= 0) {
            G->DeleteBufferID(bufferID);
            bufferID = -1;
        }
    }
}

PUBLIC void MovingSprite::Render(int CamX, int CamY) {
    if (Left) {
        if (bufferID >= 0) {
            G->DrawSpriteBuffered(Sprite, bufferID, X - CamX, Y - CamY, 0, (FlipX ? IE_FLIPX : IE_NOFLIP) | (FlipY ? IE_FLIPY : IE_NOFLIP));
        }
        else {
            G->DrawSprite(Sprite, Left, Top, Width, Height, X - CamX, Y - CamY, 0, (FlipX ? IE_FLIPX : IE_NOFLIP) | (FlipY ? IE_FLIPY : IE_NOFLIP), OffX, OffY);
        }
    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, CurrentFrame >> 8, X - CamX, Y - CamY, 0, (FlipX ? IE_FLIPX : IE_NOFLIP) | (FlipY ? IE_FLIPY : IE_NOFLIP));
    }
}
