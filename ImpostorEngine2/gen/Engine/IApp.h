#ifndef IAPP_H
#define IAPP_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL

class IScene;
class IScene;
class IGraphics;
class IInput;
class IAudio;
class IINI;

#include <Utils/Standard.h>
#include <Engine/IGraphics.h>
#include <Engine/IInput.h>
#include <Engine/IAudio.h>
#include <Engine/IScene.h>
#include <Engine/IMath.h>
#include <Engine/IINI.h>

class IApp {
public:
    IScene* Scene = NULL;
    IScene* NextScene = NULL;
    IGraphics* G = NULL;
    IInput*    Input = NULL;
    IAudio*    Audio = NULL;
    IINI*      Settings = NULL;
    float FPS = 60.f;
    bool Running = false;
    int WIDTH = 424;
    int HEIGHT = 240;
    const bool DEBUG = true;
    const bool DEV = true;
    uint32_t MetricUpdateTime = -1;
    uint32_t MetricRenderTime = -1;
    bool UnlockedFramerate = false;
    static Platforms Platform; //
    static bool      Mobile;

    IApp();
    void LoadSettings();
    void OnEvent(Uint32 event);
    void ExecuteCommand(char* cmd);
    void Run();
    void Cleanup();
    static void Print(int sev, const char* string, ...);
};

#endif /* IAPP_H */
