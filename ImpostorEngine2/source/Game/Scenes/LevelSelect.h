#ifndef SCENE_LEVELSELECT_H
#define SCENE_LEVELSELECT_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Engine/IScene.h>

class Scene_LevelSelect : public IScene {
public:
    int selected = 0;
    bool GoBack = false;

    Scene_LevelSelect(IApp* app, IGraphics* g);
    void Init();
    void Update();
    void Render();
    void Cleanup();
};

#endif /* SCENE_LEVELSELECT_H */
