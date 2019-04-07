#if INTERFACE
#include <Engine/IScene.h>

class Scene_VSMenu : public IScene {
public:
    int selected = 0;
	bool GoBack = false;
	int character = 0;
};
#endif

#include <Game/Sound.h>
#include <Game/Scenes/VSMenu.h>
#include <Game/Scenes/MainMenu.h>

PUBLIC Scene_VSMenu::Scene_VSMenu(IApp* app, IGraphics* g) {
    App = app;
    G = g;

	Discord_UpdatePresence("Main Menu", "VS Menu", "icon", false);

    selected = 1;
}

PUBLIC void Scene_VSMenu::Init() {
	int at = 0;
	if (Sound::SoundBank[0]) {
		char* ct = strstr(Sound::SoundBank[0]->Name, "Menu");
		if (ct != NULL)
			at = Sound::SoundBank[0]->GetPosition();
		//free(ct);
	}
	App->Audio->ClearMusic();
	Sound::PlayStream(0, "Music/Menu2.ogg", true, 0, at, true);

    App->Input->UseTouchController = true;

    FadeTimerMax = 30;
    FadeIn = true;
}


PUBLIC void Scene_VSMenu::Update() {
    if (FadeTimer == -1 && FadeTimerMax > 1)
        FadeTimer = FadeTimerMax;
    if (FadeTimer > 0) {   
        FadeTimer--;
        if (!FadeIn)
            G->SetFade(int((1.0 - float(FadeTimer - 1) / FadeTimerMax) * FadeMax));
        else
            G->SetFade(int((float(FadeTimer) / FadeTimerMax) * FadeMax));
    }

    // Do Fade actions
    if (FadeTimer == 0) {
        FadeTimer = -1;
        FadeTimerMax = 0;

		if (!FadeIn)
		{
			if (GoBack) {
				Scene_MainMenu* NextScene = new Scene_MainMenu(App, G);
				/*NextScene->MenuSprite = MenuSprite;
				NextScene->SuperButtonsSprite = SuperButtonsSprite;
				NextScene->TextSprite = TextSprite;

				// Make these NULL so they don't get accidentally cleaned up later
				MenuSprite = NULL;
				SuperButtonsSprite = NULL;
				TextSprite = NULL;*/

				App->NextScene = NextScene;
			}
		}
    }

    if (FadeTimer == -1) {
        if (App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED]) {
            selected--;
			if (selected < 0)
				selected = 1;

            Sound::Play(Sound::SFX_MENUBLEEP);
        }
		if (App->Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED]) {
			selected++;
				if (selected > 1)
					selected = 0;

            Sound::Play(Sound::SFX_MENUBLEEP);
        }

        if (App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED] && !App->Input->GetControllerInput(0)[IInput::I_EXTRA]) {
            character--;
            if (character < 0)
                character = 4;

            Sound::Play(Sound::SFX_MENUBLEEP);
        }
        if (App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED] && !App->Input->GetControllerInput(0)[IInput::I_EXTRA]) {
            character++;

            Sound::Play(Sound::SFX_MENUBLEEP);
        }

    }

    character = character % 5;

    if (App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED]) {
        bool acc = false;
        if (acc) {
            Sound::Play(Sound::SFX_MENUACCEPT);	
            FadeIn = false;
            FadeTimerMax = 30;
            App->Audio->FadeMusic(0.5);
        }
        else {
            Sound::Play(Sound::SFX_MENUFAIL);
        }
    }

	if (App->Input->GetControllerInput(0)[IInput::I_DENY_PRESSED]) {
		GoBack = true;
		FadeIn = false;
		FadeTimerMax = 30;
	}
}

PUBLIC void Scene_VSMenu::Render() {

    G->SetFilter(IE_FILTER_FADEABLE);

	//BG
    G->DrawRectangle(0, 0, App->WIDTH, App->HEIGHT, 0x0022EE);

	G->DrawTextShadow(180, 112, "VS Mode", 0xFFFFFF);
}

PUBLIC void Scene_VSMenu::Cleanup() {
#define CLEANUP(name) if (name) { name->Cleanup(); delete name; name = NULL; }

	App->Audio->ClearMusic();
	CLEANUP(Sound::SoundBank[0]);
}