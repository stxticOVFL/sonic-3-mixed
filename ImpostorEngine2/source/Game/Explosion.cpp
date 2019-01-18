#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Game/Object.h>

class Explosion : public Object {
public:
    int CurrentFrame = 0;
    int CurrentAnimation = 0;
};

#endif

#include <Game/Explosion.h>

#include <Game/Objects/Gen/ObjectListing.h>

PUBLIC Explosion::Explosion() {

}

PUBLIC void Explosion::Update() {
    ISprite::Animation ani = Sprite->Animations[CurrentAnimation];

    if (ani.AnimationSpeed == 4)
        ani.FrameCount /= 2;

    if (CurrentFrame / 0x100 >= ani.FrameCount - 1) {
        //CurrentFrame = ani.FrameToLoop * 0x100;
        Active = false;
    }

    if (CurrentAnimation == 5)
        VisualLayer = 1;


    if (ani.AnimationSpeed == 4)
        CurrentFrame += 0x100;
    else if (ani.AnimationSpeed > 2)
        CurrentFrame += ani.AnimationSpeed;
    else if (ani.Frames[CurrentFrame / 0x100].Duration != 0)
        CurrentFrame += 0x100 / ani.Frames[CurrentFrame / 0x100].Duration;
}

PUBLIC void Explosion::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, CurrentFrame >> 8, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
}
