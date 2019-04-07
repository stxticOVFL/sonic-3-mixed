#ifndef IAPP_H
#define IAPP_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class IScene;
class IScene;
class ISprite;
class IGraphics;
class IInput;
class IAudio;
class IINI;

#include <Utils/Standard.h>
#include <Engine/IGraphics.h>
#include <Engine/IAchievement.h>
#include <Engine/IInput.h>
#include <Engine/IAudio.h>
#include <Engine/IScene.h>
#include <Engine/IMath.h>
#include <Engine/IINI.h>

class IApp {
public:
    IScene* Scene = NULL;
    IScene* NextScene = NULL;
    ISprite* NullSprite = NULL;
    IGraphics* G = NULL;
    IInput* Input = NULL;
    IAudio* Audio = NULL;
    IINI* Settings = NULL;
    IAchievement* Achievements = NULL;
    float FPS = 60.f;
    bool Running = false;
    int WIDTH = 424;
    int HEIGHT = 240;
    int SCALE = 1;
    const bool DEBUG = true;
    const bool DEV = true;
    bool viewObjectCollision = false;
    uint32_t MetricUpdateTime = -1;
    uint32_t MetricRenderTime = -1;
    bool UnlockedFramerate = false;
    static Platforms Platform; //
    static bool Mobile;
    static IApp* GlobalApp;
    //DEV MENU
    bool DevMenuEnabled;
    bool DevMenuActive = false;
    Uint32 DevMenuColour = 0x0000FF;
    Uint8 DevMenuSelected = 0;
    Uint8 DevMenuCurMenu = 0;

    IApp();
    void LoadSettings();
    void OnEvent(Uint32 event);
    void ExecuteCommand(char* cmd);
    void Run();
    void Cleanup();
    static void Print(int sev, const char* string, ...);
};

#endif /* IAPP_H */
