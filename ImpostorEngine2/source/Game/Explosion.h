#ifndef EXPLOSION_H
#define EXPLOSION_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Utils/Standard.h>
#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Game/Object.h>

class Explosion : public Object {
public:
    Explosion();
    void OnAnimationFinish();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* EXPLOSION_H */
