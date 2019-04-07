#ifndef SCENE_EXTRASMENU_H
#define SCENE_EXTRASMENU_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Engine/IScene.h>

class Scene_ExtrasMenu : public IScene {
public:
    int selected = 0;
    bool GoBack = false;
    int character = 0;

    Scene_ExtrasMenu(IApp* app, IGraphics* g);
    void Init();
    void Update();
    void Render();
    void Cleanup();
};

#endif /* SCENE_EXTRASMENU_H */
