#ifndef SCOREGHOST_H
#define SCOREGHOST_H

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
#include <Game/Explosion.h>
#include <Game/LevelScene.h>

class ScoreGhost : public Explosion {
public:
    int CurrentFrame = 0;
    int Hold = 60;
    int32_t SubY = 0;

    ScoreGhost();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* SCOREGHOST_H */
