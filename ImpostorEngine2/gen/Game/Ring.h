#ifndef RING_H
#define RING_H

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
#include <unordered_map>

class Ring : public Object {
public:
    uint32_t MyX = 0;
    uint32_t MyY = 0;
    int CurrentFrame = 0;
    int MagnetizedTo = -1;
    bool ShouldRingFall = true;

    Ring();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* RING_H */
