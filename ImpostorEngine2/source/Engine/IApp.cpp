#if INTERFACE
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
    uint32_t MetricUpdateTime = -1;
    uint32_t MetricRenderTime = -1;
    bool UnlockedFramerate = false;
};
#endif

#include <Engine/IApp.h>
#include <Engine/IGLGraphics.h>
#include <Game/LevelScene.h>
#include <Game/Levels/AIZ.h>
#include <Game/Levels/HCZ.h>
#include <Game/Levels/MGZ.h>
//#include <Game/Levels/CNZ.h>
//#include <Game/Levels/ICZ.h>
#include <Game/Levels/LBZ.h>
#include <Game/Levels/MHZ.h>
//#include <Game/Levels/FBZ.h>
//#include <Game/Levels/SOZ.h>
//#include <Game/Levels/LRZ.h>
//#include <Game/Levels/HPZ.h>
//#include <Game/Levels/SSZ.h>
//#include <Game/Levels/DEZ.h>
//#include <Game/Levels/TDZ.h>
#include <Game/Levels/SpecialStage.h>

#include <Game/Scenes/MainMenu.h>
#include <Game/Scenes/LevelSelect.h>

#if MSVC
    #include <windows.h>
#elif NX
    #include "switch.h"
#endif

PUBLIC IApp::IApp() {
    IMath::Init();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        Print(0, "SDL_Init failed with error: %s", SDL_GetError());
        //return;
    }
    Print(0, "SDL_Init succeeded!");

    SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight");

    LoadSettings();

    char iniRenderer[256];
    if (Settings->GetString("display", "renderer", iniRenderer)) {
        if (!strcmp(iniRenderer, "GL"))
            G = new IGLGraphics(this);
        else
            G = new IGraphics(this);
    }

    int desW, desH;
    if (Settings->GetInteger("display", "width", &desW) && Settings->GetInteger("display", "height", &desH)) { }
    else {
        #if NX
            desW = 1280;
            desH = 720;
        #else
            desW = WIDTH * 3;
            desH = HEIGHT * 3;
    	#endif
    }
	G->SetDisplay(desW, desH, 1);

    Input = new IInput(this);
    Audio = new IAudio(this);

    Running = true;
}

PUBLIC void IApp::LoadSettings() {
    Settings = new IINI("config.ini");
}

PUBLIC void IApp::OnEvent(Uint32 event) {

}

PUBLIC void IApp::Run() {
    if (!Running)
        return;

    unsigned long frameTimeMillis;
    unsigned long beginFrameBatch;
    int benchmarkFrameCount = 0;

    Print(0, "Starting scene");
    Scene = new Scene_MainMenu(this, G);
    // Scene = new Scene_LevelSelect(this, G);
    // Scene = new Level_SpecialStage(this, G);
    // Scene = new Level_AIZ(this, G, 1);
    // Scene = new Level_HCZ(this, G, 1);
    // Scene = new Level_MGZ(this, G, 1);
    // Scene = new LevelScene(this, G);
    Scene->Init();

    beginFrameBatch = SDL_GetTicks();

    bool Stepper = false;
    bool Step = false;

    bool DevMenu = false;
    Settings->GetBool("dev", "devMenu", &DevMenu);

    int MetricFrameCounterTime = 0;

    Print(0, "Running...");
    SDL_Event e;
    while (Running) {
        frameTimeMillis = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                Running = false;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        if (DevMenu)
                            Running = false;
                        break;
                    case SDLK_BACKQUOTE:
                        if (DevMenu) {
                            Stepper = !Stepper;
                            MetricFrameCounterTime = 0;
                        }
                        break;
                    case SDLK_1:
                        if (DevMenu) {
                            UnlockedFramerate = !UnlockedFramerate;
                            SDL_GL_SetSwapInterval(!UnlockedFramerate);
                        }
                        break;
                    case SDLK_TAB:
                        if (DevMenu) {
                            Step = true;
                            MetricFrameCounterTime++;
                        }
                        break;
                    case SDLK_f:
                        G->SetDisplay(1024, 576, 0);
                        break;
                }
            }
        }

        //Input->Poll();
        if ((Stepper && Step) || !Stepper) {
            // Poll for inputs
            Input->Poll();

            // Update scene
            MetricUpdateTime = SDL_GetTicks();
            Scene->Update();
            MetricUpdateTime = SDL_GetTicks() - MetricUpdateTime;
        }

        Step = false;

        // Then render it
        MetricRenderTime = SDL_GetTicks();
        Scene->Render();
        MetricRenderTime = SDL_GetTicks() - MetricRenderTime;

        if (NextScene != NULL) {
            delete Scene;
            Scene = NextScene;
            NextScene = NULL;

            Scene->Init();
        }

        // Show FPS counter
        bool ShowFPS = false;
        Settings->GetBool("dev", "viewPerformance", &ShowFPS);
        if (ShowFPS) {
            int Y = 3;
            char fpstext[35];
            sprintf(fpstext, "%.1f FPS", FPS);
            G->DrawText(WIDTH - 67, Y, fpstext, 0xFFFFFF);
            Y += 8;

            sprintf(fpstext, "Upd: %03u ms", MetricUpdateTime);
            G->DrawTextShadow(WIDTH - 91, Y, fpstext, 0xFFFFFF);
            Y += 8;

            sprintf(fpstext, "Ren: %03u ms", MetricRenderTime);
            G->DrawTextShadow(WIDTH - 91, Y, fpstext, 0xFFFFFF);
            Y += 8;

            sprintf(fpstext, "Frm: %03d", MetricFrameCounterTime);
            G->DrawTextShadow(WIDTH - 91, Y, fpstext, 0xFFFFFF);
            Y += 8;
        }

        /*
        // Dev Menu
        G->DrawRectangle(200 - 150, 32, 300, 56, Color { 0xF2 / 2, 0xD1 / 2, 0x41 / 2 });
        G->DrawRectangle(200 - 150, 92, 300, 100, Color { 0xF2 / 2, 0xD1 / 2, 0x41 / 2 });

        G->DrawText(200 - strlen("IMPOSTOR ENGINE 2") * 4, 36, "IMPOSTOR ENGINE 2", 0xFFFFFF);
        G->DrawText(200 - strlen("Debug Menu") * 4, 46, "Debug Menu", 0xC0C0C0);

        G->DrawText(200 - strlen("Sonic 3 Remastered") * 4, 66, "Sonic 3 Remastered", 0xF2D141);
        G->DrawText(200 - strlen("0.00.001") * 4, 76, "0.00.001", 0xC0C0C0);
        // Version Numbering
        // #1.#2.#3
        // #1: MAJOR - a major overhaul, so basically never for a finished product
        // #2: MINOR - Sizeable feature addition
        // #3: PATCH - bug fix or patch

        G->DrawText(54,  96, "Resume", 0xF2D141);
        G->DrawText(54, 106, "Restart Scene", 0xFFFFFF);
        G->DrawText(54, 116, "Scene List", 0xFFFFFF);
        G->DrawText(54, 126, "Options", 0xFFFFFF);
        G->DrawText(54, 136, "Exit", 0xFFFFFF);
        //*/

        G->Present();

        if (!UnlockedFramerate) {
            unsigned long lenghtFrame = SDL_GetTicks() - frameTimeMillis;
            if (benchmarkFrameCount < 40) {
                if (lenghtFrame < 16) SDL_Delay(16 - lenghtFrame);
            }
            else {
                if (lenghtFrame < 15) SDL_Delay(15 - lenghtFrame);
            }
        }

        benchmarkFrameCount++;
        if (benchmarkFrameCount >= 60) {
            benchmarkFrameCount = 0;

            unsigned long now = SDL_GetTicks();
            FPS = 1000.f / (now - beginFrameBatch) * 60;
            beginFrameBatch = now;
        }
    }
}

PUBLIC void IApp::Cleanup() {
    Input->Cleanup(); delete Input;
    Audio->Cleanup(); delete Audio;
    G->Cleanup(); delete G;

    SDL_Quit();
}

PUBLIC STATIC void IApp::Print(int sev, const char* string, ...) {
    // if (sev < 1) return;

    va_list args;
    va_start(args, string);
    char str[4000];
    vsprintf(str, string, args);

    #if ANDROID
        if (sev == 0) {
            __android_log_print(ANDROID_LOG_INFO, "IE2", "%s", str);
            return;
        }
        else if (sev == 1) {
            __android_log_print(ANDROID_LOG_WARN, "IE2", "%s", str);
            return;
        }
        else if (sev == 2) {
            __android_log_print(ANDROID_LOG_ERROR, "IE2", "%s", str);
            return;
        }
        else if (sev == 3) {
            __android_log_print(ANDROID_LOG_FATAL, "IE2", "%s", str);
            return;
        }
    #endif

    int ForgC = 0;
    bool WriteToFile = false;
    char fullLine[4116];

    #if NX | MSVC
    WriteToFile = true;
    #endif

    FILE* f = NULL;
    if (WriteToFile)
        f = fopen("ImpostorEngine2.log", "a");

    sprintf(fullLine, "%s", "");

    #if MACOSX || LINUX
        if (!WriteToFile) {
            if (sev == 0) // LOG
                sprintf(fullLine, "%s", "\x1b[0;1m");
            else if (sev == 1) // WARNING
                sprintf(fullLine, "%s", "\x1b[93;1m");
            else if (sev == 2) // ERROR
                sprintf(fullLine, "%s", "\x1b[91;1m");
            else if (sev == 3) // IMPORTANT
                sprintf(fullLine, "%s", "\x1b[96;1m");
            else if (sev == -1) // VERBOSE
                sprintf(fullLine, "%s", "\x1b[94;1m");
        }
    #endif

    if (sev == 0) { // LOG
        sprintf(fullLine, "%s%s", fullLine, "LOG: ");
        ForgC = 8;
    }
    else if (sev == 1) { // WARNING
        sprintf(fullLine, "%s%s", fullLine, "WARNING: ");
        ForgC = 14;
    }
    else if (sev == 2) { // ERROR
        sprintf(fullLine, "%s%s", fullLine, "ERROR: ");
        ForgC = 12;
    }
    else if (sev == 3) { // IMPORTANT
        sprintf(fullLine, "%s%s", fullLine, "IMPORTANT: ");
        ForgC = 11;
    }
    else if (sev == -1) { // VERBOSE
        sprintf(fullLine, "%s%s", fullLine, "VERBOSE: ");
        ForgC = 11;
    }

    #if MACOSX || LINUX
        if (!WriteToFile)
            sprintf(fullLine, "%s%s", fullLine, "\x1b[0m");
    #endif

    #if MSVC
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
            WORD wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
            SetConsoleTextAttribute(hStdOut, wColor);
        }
    #endif

    printf("%s", fullLine);
    if (WriteToFile && f)
        fprintf(f, "%s", fullLine);

    #if MSVC
		WORD wColor = (csbi.wAttributes & 0xF0) + (7 & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    #endif

    printf("%s\n", str);
    fflush(stdout);

    if (WriteToFile && f) {
        fprintf(f, "%s\r\n", str);
        fclose(f);
    }
}