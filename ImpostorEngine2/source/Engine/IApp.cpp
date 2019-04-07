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
	Uint32 DevMenuColour = 0x000084;
	Uint8 DevMenuSelected = 0;
	Uint8 DevMenuCurMenu = 0;
	Uint8 DevMenuFlagA = 0;
	Uint8 DevMenuFlagB = 0;
	Uint8 DevMenuFlagC = 0;
	
	Uint8 Major = 0;
	Uint8 Minor = 0;
	short Build = 1;
	char VersionString[9];

	char Title[256];

	int isSharp = 1;
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

	IResource* DevConfig = IResources::Load("Objects/DevConfig.bin");
	IStreamer DevRead(DevConfig);

	Major = DevRead.ReadByte();
	Minor = DevRead.ReadByte();
	Build = DevRead.ReadInt16();
	sprintf(VersionString, "%.1d.%.2d.%.3d", Major, Minor, Build);
	sprintf(Title, DevRead.ReadRSDKString().c_str());

    // HACK:
    if (IApp::Platform == Platforms::Android) {
        WIDTH = HEIGHT * 2;
    }

	int desW, desH, scale;
	if (Settings->GetInteger("display", "width", &desW) &&
		Settings->GetInteger("display", "height", &desH) &&
		Settings->GetInteger("display", "scale", &scale))
	{
		WIDTH = desW;
		HEIGHT = desH;
	}
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
		desW = WIDTH;
		desH = HEIGHT;
		isSharp = 1;
		scale = 3;
#endif
	}

	char iniRenderer[256];
	if (Settings->GetString("display", "renderer", iniRenderer)) {
		if (!strcmp(iniRenderer, "GL"))
			G = new IGLGraphics(this);
		else
			G = new IGraphics(this);
	}
	else {
		G = new IGraphics(this);
	}

	desW *= scale;
	desH *= scale;
	DevMenuFlagB = scale;
	Settings->GetInteger("display", "shader", &isSharp);
	G->SetDisplay(desW, desH, isSharp);
    SDL_SetWindowTitle(G->Window, Title);
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
							{
								DevMenuActive = !DevMenuActive;
								DevMenuCurMenu = 0;
							}
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
			int filTemp = G->GetFilter();
			G->SetFilter(0);
			int DrawY = 36;

			char* numbers[10] = {
					"0",
					"1",
					"2",
					"3",
					"4",
					"5",
					"6",
					"7",
					"8",
					"9",
			};

			int values[0xA];
			int valueCount = 0;

			int value = 0;
			int valueID = 0;

			int XPos = WIDTH / 2 - 150 + 300 - 0x30;

			//Main
			G->DrawRectangle(WIDTH/2 - 150, 32, 300, 56, DevMenuColour);
			//Menus
			G->DrawRectangle(WIDTH / 2 - 150, 92, 300, 75, DevMenuColour);
			//Stats
			G->DrawRectangle(WIDTH / 2 - 150, 170, 300, 56, DevMenuColour);

			G->DrawText(WIDTH / 2 - strlen("IMPOSTOR ENGINE 2") * 4, DrawY, "IMPOSTOR ENGINE 2", 0xFFFFFF);
			DrawY += 8;
			G->DrawText(WIDTH / 2 - strlen("Dev Menu") * 4, DrawY, "Dev Menu", 0xFFFFFF);
			DrawY += 16;

			G->DrawText(WIDTH / 2 - strlen(Title) * 4, DrawY, Title, 0x848294);
			DrawY += 8;
			G->DrawText(WIDTH / 2 - 8 * 4, DrawY, VersionString, 0x848294);

			//STATS AND SHIT
			char buffer[0x40];
			sprintf(buffer, "Global Volume: %d", (int)(Audio->GlobalVolume * 100));
			G->DrawText(WIDTH / 2 - strlen(buffer) * 4, 175, buffer, 0xFFFFFF);
			sprintf(buffer, "Music Volume: %d", (int)(Audio->MusicVolume * 100));
			G->DrawText(WIDTH / 2 - strlen(buffer) * 4, 175 + 16, buffer, 0xFFFFFF);
			sprintf(buffer, "SoundFX Volume: %d", (int)(Audio->SoundFXVolume * 100));
			G->DrawText(WIDTH / 2 - strlen(buffer) * 4, 175 + 32, buffer, 0xFFFFFF);
			switch (DevMenuCurMenu)
			{
			default:
				MaxButtons = 5;
				// Version Numbering
				// #1.#2.#3
				// #1: MAJOR - a major overhaul, so basically never for a finished product
				// #2: MINOR - Sizeable feature addition
				// #3: PATCH - bug fix or patch

				G->DrawText(WIDTH / 2 - strlen("Resume") * 4, 96, "Resume", DevMenuSelected == 0 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Restart Scene") * 4, 106, "Restart Scene", DevMenuSelected == 1 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Scene List") * 4, 116, "Scene List", DevMenuSelected == 2 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Options") * 4, 126, "Options", DevMenuSelected == 3 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Exit") * 4, 136, "Exit", DevMenuSelected == 4 ? 0xF0F0F0 : 0x848294);

				switch (DevMenuSelected)
				{
				case 1:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						//Restart Scene
						//Print(1, "Scene Restart not implemented yet!");
						Scene->Cleanup();
						Scene->Init();
						DevMenuActive = 0;
					}
					break;
				case 2:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuCurMenu = 1;
						DevMenuSelected = 0;
					}
					break;
				case 3:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuCurMenu = 2;
						DevMenuSelected = 0;
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
						DevMenuCurMenu = 0;
					}
					break;
				}
				break;
			case 1: //Select Scene
				MaxButtons = 4; //TO-DO: ALL OF THIS
				G->DrawText(WIDTH / 2 - strlen("Title Screen") * 4, 96, "Title Screen", DevMenuSelected == 0 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Main Menu") * 4, 106, "Main Menu", DevMenuSelected == 1 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Angel Island 1") * 4, 116, "Angel Island 1", DevMenuSelected == 2 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Angel Island 2") * 4, 126, "Angel Island 2", DevMenuSelected == 3 ? 0xF0F0F0 : 0x848294);
				break;
			case 2: //Options General
				MaxButtons = 5;
				G->DrawText(WIDTH / 2 - strlen("Video Settings") * 4, 96, "Video Settings", DevMenuSelected == 0 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Audio Settings") * 4, 106, "Audio Settings", DevMenuSelected == 1 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Input Settings") * 4, 116, "Input Settings", DevMenuSelected == 2 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Debug Settings") * 4, 126, "Debug Settings", DevMenuSelected == 3 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Back") * 4, 136, "Back", DevMenuSelected == 4 ? 0xF0F0F0 : 0x848294);

				switch (DevMenuSelected)
				{
				default:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuCurMenu = 0;
						DevMenuSelected = 0;
					}
					break;
				case 0:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuCurMenu = 3;
						DevMenuSelected = 0;
					}
					break;
				case 1:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuCurMenu = 4;
						DevMenuSelected = 0;
					}
					break;
				case 2:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuCurMenu = 5;
						DevMenuSelected = 0;
					}
					break;
				case 3:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuCurMenu = 6;
						DevMenuSelected = 0;
					}
					break;
				}
				break;
			case 3: //Options Video
				MaxButtons = 4;
				G->DrawText(WIDTH / 2 - strlen("Window Size:") * 4, 96, "Window Size:", DevMenuSelected == 0 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("FullScreen:") * 4, 106, "FullScreen:", DevMenuSelected == 1 ? 0xF0F0F0 : 0x848294);

				G->DrawText(WIDTH / 2 - strlen("Confirm") * 4, 126, "Confirm", DevMenuSelected == 2 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Cancel") * 4, 136, "Cancel", DevMenuSelected == 3 ? 0xF0F0F0 : 0x848294);
				
				value = DevMenuFlagB;

				for (int i = 0; i < 7 && (value > 0 || (value == 0 && i == 0)); i++) {
					values[i] = value % 10;
					value /= 10;
					valueCount = i;
				}

				valueID = 0;

				for (int i = valueCount; i >= 0; i--)
				{
					G->DrawText(XPos + (8 * valueID++), 96, numbers[values[i]], DevMenuSelected == 0 ? 0xF0F0F0 : 0x848294);
				}

				G->DrawText(XPos, 106, DevMenuFlagA == 1 ? "YES" : "NO", DevMenuSelected == 1 ? 0xF0F0F0 : 0x848294);

				switch (DevMenuSelected)
				{
				default: //'Cancel'
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuCurMenu = 2;
						DevMenuSelected = 0;
					}
					break;
				case 0: 
					if (Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED])
					{
						if (DevMenuFlagB > 1)
						{
							DevMenuFlagB--;
						}
					}
					else if (Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED])
					{
						DevMenuFlagB++;
					}
					break;
				case 1://Fullscreen
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuFlagA = DevMenuFlagA != 0 ? 0 : 1;
					}
					break;
				case 2: //'Confirm'
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						G->SetDisplay(WIDTH * DevMenuFlagB, HEIGHT * DevMenuFlagB, isSharp);
						SDL_SetWindowFullscreen(G->Window, DevMenuFlagA);
						DevMenuCurMenu = 2;
						DevMenuSelected = 0;
					}
					break;
				}
				break;
			case 4: //Options Audio
				MaxButtons = 4;
				G->DrawText(WIDTH / 2 - strlen("Master Volume") * 4, 96, "Master Volume", DevMenuSelected == 0 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Music Volume") * 4, 106, "Music Volume", DevMenuSelected == 1 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("SoundFX Volume") * 4, 116, "SoundFX Volume", DevMenuSelected == 2 ? 0xF0F0F0 : 0x848294);

				value = Audio->GlobalVolume * 100;

				for (int i = 0; i < 7 && (value > 0 || (value == 0 && i == 0)); i++) {
					values[i] = value % 10;
					value /= 10;
					valueCount = i;
				}

				valueID = 0;

				for (int i = valueCount; i >= 0; i--)
				{
					G->DrawText(XPos + (8 * valueID++), 96, numbers[values[i]], DevMenuSelected == 0 ? 0xF0F0F0 : 0x848294);
				}

				value = Audio->MusicVolume * 100;
				for (int i = 0; i < 7 && (value > 0 || (value == 0 && i == 0)); i++) {
					values[i] = value % 10;
					value /= 10;
					valueCount = i;
				}

				valueID = 0;

				for (int i = valueCount; i >= 0; i--)
				{
					G->DrawText(XPos + (8 * valueID++), 106, numbers[values[i]], DevMenuSelected == 1 ? 0xF0F0F0 : 0x848294);
				}

				value = Audio->SoundFXVolume * 100;
				for (int i = 0; i < 7 && (value > 0 || (value == 0 && i == 0)); i++) {
					values[i] = value % 10;
					value /= 10;
					valueCount = i;
				}

				valueID = 0;

				for (int i = valueCount; i >= 0; i--)
				{
					G->DrawText(XPos + (8 * valueID++), 116, numbers[values[i]], DevMenuSelected == 2 ? 0xF0F0F0 : 0x848294);
				}

				G->DrawText(WIDTH / 2 - strlen("Back") * 4, 136, "Back", DevMenuSelected == 3 ? 0xF0F0F0 : 0x848294);

				switch (DevMenuSelected)
				{
				default:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuCurMenu = 2;
						DevMenuSelected = 0;
					}
					break;
				case 0: //Master Volume
					if (Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED])
					{
						if (Audio->GlobalVolume > 0.1)
						{
							Audio->GlobalVolume -= 0.1;
						}
					}
					else if (Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED])
					{
						if (Audio->GlobalVolume < 1)
						{
							Audio->GlobalVolume += 0.1;
						}
					}
					break;
				case 1: //Music Volume
					if (Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED])
					{
						if (Audio->MusicVolume > 0.1)
						{
							Audio->MusicVolume -= 0.1;
						}
					}
					else if (Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED])
					{
						if (Audio->MusicVolume < 1)
						{
							Audio->MusicVolume += 0.1;
						}
					}
					break;
				case 2: //SoundFX Volume
					if (Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED])
					{
						if (Audio->SoundFXVolume > .10)
						{
							Audio->SoundFXVolume -= 0.1;
						}
					}
					else if (Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED])
					{
						if (Audio->SoundFXVolume < 1)
						{
							Audio->SoundFXVolume += 0.1;
						}
					}
					break;
				}
				break;
			case 5: //Options Input
				MaxButtons = 5;
				G->DrawText(WIDTH / 2 - strlen("Set Keys For Input 1") * 4, 96, "Set Keys For Input 1", DevMenuSelected == 0 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Set Keys For Input 2") * 4, 106, "Set Keys For Input 2", DevMenuSelected == 1 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Set Keys For Input 3") * 4, 116, "Set Keys For Input 3", DevMenuSelected == 2 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Set Keys For Input 4") * 4, 126, "Set Keys For Input 4", DevMenuSelected == 3 ? 0xF0F0F0 : 0x848294);
				G->DrawText(WIDTH / 2 - strlen("Back") * 4, 136, "Back", DevMenuSelected == 4 ? 0xF0F0F0 : 0x848294);
				
				switch (DevMenuSelected)
				{
				default:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuCurMenu = 2;
						DevMenuSelected = 0;
					}
					break;
				case 0: //Input 1
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{

					}
					break;
				case 1: //Input 2
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{

					}
					break;
				case 2: //Input 3
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{

					}
					break;
				case 3: //Input 4
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{

					}
					break;
				}
				break;
			case 6: //Options Debug
				MaxButtons = 4;
				G->DrawText(WIDTH / 2 - strlen("Debug Mode") * 4, 96, "Debug Mode", DevMenuSelected == 0 ? 0xF0F0F0 : 0x848294);

				G->DrawText(WIDTH / 2 - strlen("Back") * 4, 136, "Back", DevMenuSelected == 3 ? 0xF0F0F0 : 0x848294);

				switch (DevMenuSelected)
				{
				default:
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{
						DevMenuCurMenu = 2;
						DevMenuSelected = 0;
					}
					break;
				case 0: //Debug Mode
					if (Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED])
					{

					}
					break;
				}
				break;
			}

			if (Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED])
			{
				if (DevMenuSelected < MaxButtons-1)
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

			G->SetFilter(filTemp);
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
