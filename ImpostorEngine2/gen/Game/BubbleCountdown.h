#ifndef BUBBLECOUNTDOWN_H
#define BUBBLECOUNTDOWN_H

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
#include <Game/Explosion.h>

class BubbleCountdown : public Explosion {
public:
    int Number = 0;
    int Timer1 = -1;
    int Timer2 = -1;
    int Off = 0;

    BubbleCountdown();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* BUBBLECOUNTDOWN_H */
