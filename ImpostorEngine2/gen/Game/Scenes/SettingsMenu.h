#ifndef SCENE_SETTINGSMENU_H
#define SCENE_SETTINGSMENU_H

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
#include <Engine/ISprite.h>

class Scene_SettingsMenu : public IScene {
public:
    int selected = 0;
    int ran = 0;
    int frame = 0;
    int FrameCircle = 0;
    int FrameZigzag = 0;
    int FrameZigzagRed = 0;
    int FrameZigzagBlue = 0;
    ISprite* MenuSprite = NULL;
    ISprite* SuperButtonsSprite = NULL;
    ISprite* TextSprite = NULL;

    Scene_SettingsMenu(IApp* app, IGraphics* g);
    void Render();
};

#endif /* SCENE_SETTINGSMENU_H */
