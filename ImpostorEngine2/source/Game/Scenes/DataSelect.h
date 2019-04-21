#ifndef SCENE_DATASELECT_H
#define SCENE_DATASELECT_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;

#include <Engine/IScene.h>
#include <Engine/ISprite.h>

class Scene_DataSelect : public IScene {
public:
    int selected = 0;
    int viewOffX = 0;
    ISprite* MenuSprite = NULL;
    ISprite* SaveIconsSprite = NULL;
    ISprite* SaveSelectSprite = NULL;
    ISprite* SuperButtonsSprite = NULL;
    ISprite* TextSprite = NULL;
    int frame = 0;
    int FrameCircle = 0;
    int FrameZigzag = 0;
    int FrameZigzagRed = 0;
    int FrameZigzagBlue = 0;
    int CharacterFlag = 0;
    int PartnerFlag = 0xFF;
    int Mode = 0;
    const char* ModeName = "Classic Mode";

    Scene_DataSelect(IApp* app, IGraphics* g, int m);
    void Init();
    void Update();
    void Render();
    void Cleanup();
};

#endif /* SCENE_DATASELECT_H */
