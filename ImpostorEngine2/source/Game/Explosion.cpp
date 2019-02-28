#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Game/Object.h>

class Explosion : public Object {
public:

};

#endif

#include <Game/Explosion.h>

#include <Game/Objects/Gen/ObjectListing.h>

PUBLIC Explosion::Explosion() {
    AutoAnimate = true;
	XSpeed = 0;
	YSpeed = 0;
}

PUBLIC void Explosion::OnAnimationFinish() {
    Active = false;
}

PUBLIC void Explosion::Update() {
    Animate();
	MoveSprite();
}

PUBLIC void Explosion::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX | FlipY << 1);
}
