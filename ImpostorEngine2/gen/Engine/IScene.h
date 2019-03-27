#ifndef ISCENE_H
#define ISCENE_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class IApp;
class IGraphics;

#include <Utils/Standard.h>
#include <Engine/IApp.h>
#include <Engine/IGraphics.h>

class IScene {
public:
    IApp* App = NULL;
    IGraphics* G = NULL;
    int FadeTimer = -1;
    int FadeTimerMax = 1;
    int FadeMax = 0xFF;
    bool FadeIn = false;

    virtual ~IScene();
    virtual void OnEvent(Uint32 event);
    virtual void Init();
    virtual void Update();
    virtual void Render();
    virtual void Cleanup();
    virtual bool ExecuteCommand(char* cmd);
};

#endif /* ISCENE_H */
