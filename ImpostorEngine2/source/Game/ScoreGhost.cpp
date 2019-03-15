#if INTERFACE
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
};

#endif

#include <Game/ScoreGhost.h>

PUBLIC ScoreGhost::ScoreGhost() {

}

PUBLIC void ScoreGhost::Update() {
	Y += (SubY - Y) / 8;

    if (Y >= Scene->CameraY + App->HEIGHT)
        Active = false;

    if (Hold > 0)
        Hold--;
    else
        Active = false;
}

PUBLIC void ScoreGhost::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, CurrentFrame, X - CamX, Y - CamY, 0, IE_NOFLIP);
}
