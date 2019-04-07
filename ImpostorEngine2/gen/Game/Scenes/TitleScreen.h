#ifndef SCENE_TITLESCREEN_H
#define SCENE_TITLESCREEN_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;
class ISprite;
class ISprite;

#include <Engine/IScene.h>

class Scene_TitleScreen : public IScene {
public:
    int selected = 0;
    bool GoBack = false;
    int character = 0;
    ISprite* TitleBGSprite = NULL;
    ISprite* TitleSprite = NULL;
    ISprite* TitleSegaSprite = NULL;
    int fingerFrame = 0;
    int eyeFrame = 0;
    int fingerTimer = 0x10;
    int eyeTimer = 0;
    int fingerCycle = 0;
    int pressFrame = 2;
    int pressTimer = 0;
    int TailsPos = -0x20;
    int TailsFrame = 0;
    int TailsTimer = 0;
    bool TailsMoveLeft = 0;

    Scene_TitleScreen(IApp* app, IGraphics* g);
    void Init();
    void Update();
    void Render();
    void Cleanup();
};

#endif /* SCENE_TITLESCREEN_H */
