#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Game/Object.h>
#include <unordered_map>

#include <Game/Explosion.h>

class BubbleCountdown : public Explosion {
public:
    int Number = 0;
    int Timer1 = -1;
    int Timer2 = -1;

    int Off = 0;
};

#endif

#include <Game/BubbleCountdown.h>
#include <Game/Objects/Gen/ObjectListing.h>

PUBLIC BubbleCountdown::BubbleCountdown() {
    CurrentAnimation = 7;
    CurrentFrame = 0;
}

PUBLIC void BubbleCountdown::Update() {
    ISprite::Animation ani = Sprite->Animations[CurrentAnimation];

    if (CurrentAnimation == 7) {
        if ((CurrentFrame >> 8) >= ani.FrameCount - 1) {
            CurrentAnimation = 8 + Number;
            Timer1 = 88;
            CurrentFrame = 0;
        }

        if (ani.AnimationSpeed == 4)
            CurrentFrame += 0x100;
        else if (ani.AnimationSpeed > 2)
            CurrentFrame += ani.AnimationSpeed;
        else if (ani.Frames[CurrentFrame >> 8].Duration != 0)
            CurrentFrame += 0x100 / ani.Frames[CurrentFrame >> 8].Duration;
    }
    else if (CurrentAnimation > 7) {
        if ((CurrentFrame >> 8) >= ani.FrameCount - 1) {
            CurrentFrame = (ani.FrameCount - 1) << 8;
        }

        if (ani.AnimationSpeed == 4)
            CurrentFrame += 0x100;
        else if (ani.AnimationSpeed > 2)
            CurrentFrame += ani.AnimationSpeed;
        else if (ani.Frames[CurrentFrame >> 8].Duration != 0)
            CurrentFrame += 0x100 / ani.Frames[CurrentFrame >> 8].Duration;

        if (Timer1 == 0) {
            Timer2 = 54;
            Timer1--;
        }
        if (Timer2 == 0)
            Active = false;
    }

    if (Timer1 > 0)
        Timer1--;
    if (Timer2 > 0)
        Timer2--;

    Off = (int)(Scene->Player->Cos[(Scene->Frame << 3) & 0xFF] * 3);
}

PUBLIC void BubbleCountdown::Render(int CamX, int CamY) {
    G->DrawModeOverlay = true;
    G->DrawAlpha = 0xFF;
    ISprite::Animation animation = Sprite->Animations[CurrentAnimation];
    ISprite::AnimFrame currentFrame = animation.Frames[CurrentFrame >> 8];
    if (Timer2 >= 0) {
        G->DrawSprite(Sprite,
            currentFrame.X,
            currentFrame.Y,
            currentFrame.W,
            currentFrame.H, X, Y, 0, FlipX ? IE_FLIPX : IE_NOFLIP,
            currentFrame.OffX,
            currentFrame.OffY, currentFrame.W * Timer2 / 54, currentFrame.H * Timer2 / 54);
    }
    else {
        G->DrawSprite(Sprite,
            currentFrame.X,
            currentFrame.Y,
            currentFrame.W,
            currentFrame.H, X, Y, 0, FlipX ? IE_FLIPX : IE_NOFLIP,
            currentFrame.OffX,
            currentFrame.OffY, currentFrame.W + Off, currentFrame.H - Off);
    }
    G->DrawModeOverlay = false;
    G->DrawAlpha = 0xFF;
}
