#if INTERFACE
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
    IScene*	Scene = NULL;
    IScene*	NextScene = NULL;

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
};
#endif

#include <Engine/IApp.h>
#include <Engine/IGLGraphics.h>
#include <Game/LevelScene.h>
#include <Game/Levels/AIZ.h>
#include <Game/Levels/HCZ.h>
#include <Game/Levels/MGZ.h>
#include <Game/Levels/CNZ.h>
#include <Game/Levels/ICZ.h>
#include <Game/Levels/LBZ.h>
#include <Game/Levels/FBZ.h>
#include <Game/Levels/MHZ.h>
#include <Game/Levels/SOZ.h>
#include <Game/Levels/LRZ.h>
#include <Game/Levels/HPZ.h>
#include <Game/Levels/SSZ.h>
#include <Game/Levels/DEZ.h>
#include <Game/Levels/TDZ.h>
#include <Game/Levels/SpecialStage.h>

#include <Game/Scenes/TitleScreen.h>
#include <Game/Scenes/MainMenu.h>
#include <Game/Scenes/DataSelect.h>
#include <Game/Scenes/LevelSelect.h>

#if   MSVC
    #include <windows.h>
#elif NX
    #include "switch.h"
#endif

#if   MSVC
    Platforms IApp::Platform = Platforms::Windows;
	bool      IApp::Mobile   = false;
#elif MACOSX
    Platforms IApp::Platform = Platforms::MacOSX;
	bool      IApp::Mobile = false;
#elif LINUX
    Platforms IApp::Platform = Platforms::Linux;
	bool      IApp::Mobile = false;
#elif UBUNTU
    Platforms IApp::Platform = Platforms::Ubuntu;
	bool      IApp::Mobile = false;
#elif NX
    Platforms IApp::Platform = Platforms::Switch;
	bool      IApp::Mobile = false;
#elif IOS
    Platforms IApp::Platform = Platforms::iOS;
	bool      IApp::Mobile = true;
#elif ANDROID
    Platforms IApp::Platform = Platforms::Android;
	bool      IApp::Mobile = true;
#else
    Platforms IApp::Platform = Platforms::Default;
#endif

IApp* IApp::GlobalApp = NULL;

PUBLIC IApp::IApp() {
    IMath::Init();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        Print(0, "SDL_Init failed with error: %s", SDL_GetError());
        //return;
    }
    Print(0, "SDL_Init succeeded!");

    SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight");
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
    // SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH, "1");
    // SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING, 0);

    LoadSettings();

    // HACK:
    if (IApp::Platform == Platforms::Android) {
        WIDTH = HEIGHT * 2;
    }

    char iniRenderer[256];
    if (Settings->GetString("display", "renderer", iniRenderer)) {
        if (!strcmp(iniRenderer, "GL"))
            G = new IGLGraphics(this);
        else
            G = new IGraphics(this);
    }
    else {
        G = new IGLGraphics(this);
    }

    int desW, desH,scale;
    int isSharp = 1;
    if (Settings->GetInteger("display", "width", &desW) && Settings->GetInteger("display", "height", &desH) && Settings->GetInteger("display", "scale", &scale)) { }
    else {
        #if NX
            desW = 1280;
            desH = 720;
			scale = 1;
        #elif IOS
            desW = 1138;
            desH = 640;
            isSharp = 0;
			scale = 1;
        #elif ANDROID
            desW = WIDTH * 3;
            desH = HEIGHT * 3;
            isSharp = 0;
			scale = 1;
        #else
            desW = WIDTH * 3;
            desH = HEIGHT * 3;
			scale = 1;
    	#endif
    }
	desW *= scale;
	desH *= scale;
	Settings->GetInteger("display", "shader", &isSharp);
	G->SetDisplay(desW, desH, isSharp);
    SDL_SetWindowTitle(G->Window, "Sonic 3'Mixed");
	int full = 0;
	Settings->GetInteger("display", "fullscreen", &full);
	SDL_SetWindowFullscreen(G->Window, full);

    Input = new IInput(this);
    Audio = new IAudio(this);
    Achievements = new IAchievement(this);

	NullSprite = new ISprite("Classic/Sprites/Dev/NullGfx.gif", this);
	ISprite::Animation an;
	an.Name = "";
	an.FrameCount = 1;
	an.Frames = new ISprite::AnimFrame[an.FrameCount];
	ISprite::AnimFrame ts_af;
	ts_af.X = 0;
	ts_af.Y = 0;
	ts_af.W = ts_af.H = 16;
	ts_af.OffX = ts_af.OffY = -8;
	an.Frames[0] = ts_af;
	G->MakeFrameBufferID(NullSprite, an.Frames);
	NullSprite->Animations.push_back(an);


    Running = true;
}

PUBLIC void IApp::LoadSettings() {
    Settings = new IINI("config.ini");
}

PUBLIC void IApp::OnEvent(Uint32 event) {
	if (!Scene) return;

	Scene->OnEvent(event);
}

PUBLIC void IApp::ExecuteCommand(char* cmd) {
    if (Scene && Scene->ExecuteCommand(cmd))
        return;

    bool isUnknown = true;
    switch (*cmd) {
        case 'S':
            if (!strcmp(cmd, "STARTSCENE ")) {
                printf("sorry lol\n");
            }
            isUnknown = false; break;
        case 'H':
            if (!strcmp(cmd, "HELP ")) {
                printf("sorry lol\n");
                printf("in level scenes:\n");
                printf("still none lol\n");
            }
            isUnknown = false; break;
        default:
            break;
    }

    if (isUnknown)
        Print(2, "Unrecognized command '%s'.", cmd);
}

#include <Game/SaveGame.h>

PUBLIC void IApp::Run() {
    if (!Running)
        return;

    unsigned long frameTimeMillis;
    unsigned long beginFrameBatch;
    int benchmarkFrameCount = 0;

    IApp::GlobalApp = this;

	SaveGame::Init();

    Print(0, "Starting scene");
    if (!Scene) {
        Scene = new Scene_TitleScreen(this, G);
		// Scene = new Scene_DataSelect(this, G);
        // Scene = new Scene_LevelSelect(this, G);
        // Scene = new Level_SpecialStage(this, G);
        // Scene = new Level_AIZ(this, G, 2);
        // Scene = new Level_ICZ(this, G, 1);
        // Scene = new Level_HCZ(this, G, 1);
        // Scene = new Level_MGZ(this, G, 1);
        // Scene = new LevelScene(this, G);

		// SaveGame::CurrentEmeralds = 0xFFFF;
		// SaveGame::CurrentCharacterFlag = (int)CharacterType::Mighty;
		/*
		SaveGame::CurrentEmeralds = 0x0000;
		LevelScene* ls = new LevelScene(this, G);
		Sound::SoundBank[0] = new ISound("Stages/MSZ/Act2.ogg", true);
		Sound::Audio->LoopPoint[0] = 179390 / 4;
		ls->Str_TileConfigBin = "Stages/MSZ/TileConfig.bin";
		ls->Str_SceneBin = "Stages/MSZ/Scene2.bin";
		ls->Str_NullSprite = "Stages/MSZ/16x16Tiles.gif";
		ls->PlayerStartX = 160;
		ls->PlayerStartY = 1328;
		ls->Thremixed = true;
		ls->ZoneID = 1;
		ls->VisualAct = 1;
		SaveGame::CurrentCharacterFlag = (int)CharacterType::Mighty;
		sprintf(ls->LevelName, "MIRAGE SALOON");
		sprintf(ls->LevelNameDiscord, "Mirage Saloon");
		Scene = ls;
		//*/

        Scene->Init();
    }

    beginFrameBatch = SDL_GetTicks();

    bool Stepper = false;
    bool Step = false;

    Settings->GetBool("dev", "devMenu", &DevMenuEnabled);

	//Audio be like *wiggly air noises*
	int audiopoop;
	Settings->GetInteger("audio", "global", &audiopoop);
	Audio->GlobalVolume = (float)audiopoop / 100;
	Settings->GetInteger("audio", "music", &audiopoop);
	Audio->MusicVolume = (float)audiopoop / 100;
	Settings->GetInteger("audio", "sfx", &audiopoop);
	Audio->SoundFXVolume = (float)audiopoop / 100;

	Settings->GetBool("dev", "viewObjectCollision", &viewObjectCollision);

    int MetricFrameCounterTime = 0;
    int UpdatesPerFrame = 1;

    Print(0, "Running...");
    SDL_Event e;

    G->Present();

    while (Running) {
        frameTimeMillis = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    Running = false;
                    break;
                case SDL_FINGERDOWN:
                case SDL_FINGERMOTION:
                    // Set IInput device ID here.
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
							if (!DevMenuEnabled)
								Running = false;
							else
								DevMenuActive = !DevMenuActive;
                            break;
                        case SDLK_BACKQUOTE:
                            if (DevMenuEnabled) {
                                Stepper = !Stepper;
                                MetricFrameCounterTime = 0;
                            }
                            break;
                        /*
                        case SDLK_1: {
                            char* end;
                            char buffer2[420];
                            printf("\x1b[1;91m%s\x1b[m > ", "Enter a command");
                            if (fgets(buffer2, 420, stdin) != NULL) {
                                end = buffer2 + strlen(buffer2);
                                do {
                                    *end-- = 0;
                                }
                                while (*end == '\r' || *end == '\n');
                            }
                            ExecuteCommand(buffer2);
                            break; }
                        */
                        case SDLK_BACKSPACE:
                            if (DevMenuEnabled) {
                                UnlockedFramerate = !UnlockedFramerate;
                                SDL_GL_SetSwapInterval(!UnlockedFramerate);
                            }
                            break;
                        case SDLK_BACKSLASH:
                            if (DevMenuEnabled) {
                                Stepper = true;
                                Step = true;
                                MetricFrameCounterTime++;
                            }
                            break;
                        case SDLK_f:
                            G->SetDisplay(1272, 720, 1);
                            break;
                    }
                    break;
            }
        }

        UpdatesPerFrame = 1;
        if (UnlockedFramerate) UpdatesPerFrame = 4;

        for (int m = 0; m < UpdatesPerFrame; m++) {
            if ((Stepper && Step) || !Stepper) {
                // Poll for inputs
                Input->Poll();

                // Update scene
                MetricUpdateTime = SDL_GetTicks();
				if (!DevMenuActive) Scene->Update();
                MetricUpdateTime = SDL_GetTicks() - MetricUpdateTime;
            }
        }

        Step = false;

        // Then render it
        MetricRenderTime = SDL_GetTicks();
		if (NextScene == NULL)
		{
			Scene->Render();
			if (Achievements->AchievementGet) {
				Achievements->OnAchievementGet(Achievements->GotAchievement);
			}
		}
        MetricRenderTime = SDL_GetTicks() - MetricRenderTime;

        // If there's a new scene to go to
        if (NextScene != NULL) {
			unsigned long now = SDL_GetTicks();

			IScene* OldScene = Scene;
            Scene = NextScene;
            NextScene = NULL;
			OldScene->Cleanup();
			delete OldScene;
			OldScene = NULL;

            Scene->Init();
            Input->Poll();
			if (!DevMenuActive) Scene->Update();
            Scene->Render();
			if (Achievements->AchievementGet) {
				Achievements->OnAchievementGet(Achievements->GotAchievement);
			}
			beginFrameBatch += now - SDL_GetTicks();
        }

        // Show FPS counter
        bool ShowFPS = false;
        Settings->GetBool("dev", "viewPerformance", &ShowFPS);
		if (Platform == Platforms::Android)
			ShowFPS = true;
        if (ShowFPS) {
            int Y = 3;
            char fpstext[35];
            sprintf(fpstext, "%.1f FPS", FPS);
            G->DrawTextShadow(WIDTH - 67, Y, fpstext, 0xFFFFFF);
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

		int MaxButtons = 5;
        // Dev Menu
		if (DevMenuActive && DevMenuEnabled)
		{
			//Main
			G->DrawRectangle(200 - 150, 32, 300, 56, DevMenuColour);
			//Menus
			G->DrawRectangle(200 - 150, 92, 300, 75, DevMenuColour);
			//Stats
			G->DrawRectangle(200 - 150, 170, 300, 56, DevMenuColour);

			G->DrawText(200 - strlen("IMPOSTOR ENGINE 2") * 4, 36, "IMPOSTOR ENGINE 2", 0xFFFFFF);
			G->DrawText(200 - strlen("Dev Menu") * 4, 46, "Dev Menu", 0xFFFFFF);

			G->DrawText(200 - strlen("Sonic 3'Mixed") * 4, 66, "Sonic 3'Mixed", 0xC0C0C0);
			G->DrawText(200 - strlen("0.00.001") * 4, 76, "0.00.001", 0xC0C0C0);

			//STATS AND SHIT
			char buffer[0x40];
			sprintf(buffer, "Global Volume: %d", (int)(Audio->GlobalVolume * 100));
			G->DrawText(200 - strlen(buffer) * 4, 175, buffer, 0xFFFFFF);
			sprintf(buffer, "Music Volume: %d", (int)(Audio->MusicVolume * 100));
			G->DrawText(200 - strlen(buffer) * 4, 175 + 16, buffer, 0xFFFFFF);
			sprintf(buffer, "SoundFX Volume: %d", (int)(Audio->SoundFXVolume * 100));
			G->DrawText(200 - strlen(buffer) * 4, 175 + 32, buffer, 0xFFFFFF);
			switch (DevMenuCurMenu)
			{
			default:
				MaxButtons = 5;
				// Version Numbering
				// #1.#2.#3
				// #1: MAJOR - a major overhaul, so basically never for a finished product
				// #2: MINOR - Sizeable feature addition
				// #3: PATCH - bug fix or patch

				G->DrawText(200 - strlen("Resume") * 4, 96, "Resume", DevMenuSelected == 0 ? 0xF2D141 : 0);
				G->DrawText(200 - strlen("Restart Scene") * 4, 106, "Restart Scene", DevMenuSelected == 1 ? 0xF2D141 : 0);
				G->DrawText(200 - strlen("Scene List") * 4, 116, "Scene List", DevMenuSelected == 2 ? 0xF2D141 : 0);
				G->DrawText(200 - strlen("Options") * 4, 126, "Options", DevMenuSelected == 3 ? 0xF2D141 : 0);
				G->DrawText(200 - strlen("Exit") * 4, 136, "Exit", DevMenuSelected == 4 ? 0xF2D141 : 0);

				switch (DevMenuSelected)
				{
				case 1:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						//Restart Scene
						Print(1, "Scene Restart not implemented yet!");
					}
					break;
				case 2:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						Print(1, "Scene Select Menu not implemented yet!");
					}
					break;
				case 3:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						Print(1, "Options Menu not implemented yet!");
					}
					break;
				case 4:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						Running = false;
					}
					break;
				default:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuActive = false;
					}
					break;
				}
				break;
			}

			if (Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED])
			{
				if (DevMenuSelected < MaxButtons)
				{
					DevMenuSelected++;
				}
				else
				{
					DevMenuSelected = 0;
				}
			}
			if (Input->GetControllerInput(0)[IInput::I_UP_PRESSED])
			{
				if (DevMenuSelected > 0)
				{
					DevMenuSelected--;
				}
				else
				{
					DevMenuSelected = MaxButtons-1;
				}
			}
		}

        G->Present();

        unsigned long lenghtFrame = SDL_GetTicks() - frameTimeMillis;
        if (benchmarkFrameCount < 40) {
            if (lenghtFrame < 16) SDL_Delay(16 - lenghtFrame);
        }
        else {
            if (lenghtFrame < 15) SDL_Delay(15 - lenghtFrame);
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
	if (Scene) {
		Scene->Cleanup();
		delete Scene;
	}
	delete Achievements;
    Input->Cleanup(); delete Input;
    Audio->Cleanup(); delete Audio;
	Settings->Cleanup(); delete Settings;
    G->Cleanup(); delete G;

    SDL_Quit();
}

PUBLIC STATIC void IApp::Print(int sev, const char* string, ...) {
#if !ANDROID
    if (sev < 0)
		return;
#endif

    if (string == nullptr) {
        return;
    }

    va_list args;
    va_start(args, string);
    char str[4000];
    vsprintf(str, string, args);

    #if ANDROID
        if (sev == -1) {
            __android_log_print(ANDROID_LOG_VERBOSE, "IE2", "%s", str);
            return;
        }
        else if (sev == 0) {
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

    #if NX
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
		strcat(fullLine, "      LOG: ");
        ForgC = 8;
    }
    else if (sev == 1) { // WARNING
		strcat(fullLine, "  WARNING: ");
        ForgC = 14;
    }
    else if (sev == 2) { // ERROR
		strcat(fullLine, "    ERROR: ");
        ForgC = 12;
    }
    else if (sev == 3) { // IMPORTANT
		strcat(fullLine, "IMPORTANT: ");
        ForgC = 11;
    }
    else if (sev == -1) { // VERBOSE
		strcat(fullLine, "  VERBOSE: ");
        ForgC = 11;
    }

    #if MACOSX || LINUX
        if (!WriteToFile)
            sprintf(fullLine, "%s%s", fullLine, "\x1b[0m");
    #endif

		ForgC = ForgC & 0xF;
    #if MSVC
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
            WORD wColor = (csbi.wAttributes & 0xF0) + ForgC;
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
