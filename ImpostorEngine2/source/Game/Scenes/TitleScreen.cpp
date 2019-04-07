#if INTERFACE
#include <Engine/IScene.h>

class Scene_TitleScreen : public IScene {
public:
	int selected = 0;
	bool GoBack = false;
	int character = 0;
	ISprite* TitleBGSprite = NULL;
	ISprite* TitleSprite = NULL;
	ISprite* TitleSegaSprite = NULL;

	int fingerFrame = 0;
	int eyeFrame = 0;
	int fingerTimer = 0x10;
	int eyeTimer = 0;
	int fingerCycle = 0;
	int pressFrame = 2;
	int pressTimer = 0;

	int TailsPos = -0x20;
	int TailsFrame = 0;
	int TailsTimer = 0;
	bool TailsMoveLeft = 0;
};
#endif

#include <Game/Sound.h>
#include <Game/Scenes/TitleScreen.h>
#include <Game/Scenes/MainMenu.h>

PUBLIC Scene_TitleScreen::Scene_TitleScreen(IApp* app, IGraphics* g) {
	App = app;
	G = g;

	Sound::Audio = App->Audio;
	Sound::Init();

	if (!Sound::SoundBank[0] || strcmp(Sound::SoundBank[0]->Name, "Classic/Music/Title.ogg")) {
		Sound::SoundBank[0] = new ISound("Classic/Music/Title.ogg", true);
		Sound::Audio->LoopPoint[0] = 0;
		Sound::Audio->Loop[0] = false;
		App->Audio->PushMusicAt(Sound::SoundBank[0], 0, false, 0);
	}
	selected = 1;

	Discord_UpdatePresence("Title Screen", "", "icon", false);

	//Simulate the startup
	//aka "I'm too lazy to make one and we also don't have one"
	FadeTimerMax = 30;
}

PUBLIC void Scene_TitleScreen::Init() {
	if (!App->Audio->IsPlayingMusic(Sound::SoundBank[0])) {
		App->Audio->ClearMusic();
		App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
	}

	if (!TitleSprite)
	{
		TitleSprite = new ISprite("Sprites/Title/Title.gif", App);
		TitleSprite->LoadAnimation("Sprites/Title/Title.bin");
		TitleSprite->SetTransparentColorIndex(0);
		//TitleSprite->SetTransparentColorIndex(0x20);
		TitleSprite->UpdatePalette();
	}

	if (!TitleBGSprite)
	{
		TitleBGSprite = new ISprite("Sprites/Title/BG.gif", App);
		TitleBGSprite->LoadAnimation("Sprites/Title/Background.bin");
		TitleBGSprite->SetTransparentColorIndex(0xFF);
		TitleBGSprite->UpdatePalette();
	}

	if (!TitleSegaSprite)
	{
		TitleSegaSprite = new ISprite("Sprites/Title/Sega.gif", App);
		TitleSegaSprite->LoadAnimation("Sprites/Title/Sega.bin");
		TitleSegaSprite->SetTransparentColorIndex(0x0);
		TitleSegaSprite->UpdatePalette();
	}

	App->Input->UseTouchController = true;

	FadeTimerMax = 30;
	FadeIn = true;
}


PUBLIC void Scene_TitleScreen::Update() {
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
				App->NextScene = NextScene;
			}
		}
	}

	character = character % 5;

	if (App->Input->GetControllerInput(0)[IInput::I_ANY_PRESSED]) {
		bool acc = true;
		if (acc) {
			Sound::Play(Sound::SFX_MENUACCEPT);
			FadeIn = false;
			FadeTimerMax = 30;
			App->Audio->FadeMusic(0.5);
			GoBack = true;
		}
		else {
			Sound::Play(Sound::SFX_MENUFAIL);
		}
	}

	bool Go = IMath::randRange(1, 10) == 5;

	fingerTimer++;

	switch (fingerFrame)
	{
	default:
		if (fingerTimer > 0x60 && fingerCycle == 0)
		{
			fingerTimer = 0;
			fingerFrame++;
		}
		else if (fingerTimer > 0x6 && fingerCycle > 0)
		{
			fingerTimer = 0;
			fingerFrame++;
		}
		break;
	case 1:
		if (fingerTimer > 0x6)
		{
			fingerTimer = 0;
			fingerFrame++;
		}
		break;
	case 2:
		if (fingerTimer > 0x6)
		{
			fingerTimer = 0;
			fingerFrame++;
			fingerCycle++;
		}
		if (fingerCycle > 2) fingerCycle = 0;
		break;
	}

	if (fingerFrame > 2) fingerFrame = 0;

	eyeTimer++;

	switch (eyeFrame)
	{
	default:
		if (eyeTimer > 0x6A)
		{
			eyeTimer = 0;
			eyeFrame++;
		}
		break;
	case 1:
		if (eyeTimer > 0x6)
		{
			eyeTimer = 0;
			eyeFrame++;
		}
		break;
	case 2:
		if (eyeTimer > 0x8)
		{
			eyeTimer = 0;
			eyeFrame++;
		}
		break;
	case 3:
		if (eyeTimer > 0x2)
		{
			eyeTimer = 0;
			eyeFrame++;
		}
		break;
	}
	if (eyeFrame > 3) {
		eyeFrame = 0;
	}

	TailsTimer++;
	if (TailsTimer > 0x8)
	{
		TailsTimer = 0;
		TailsFrame++;
	}
	if (TailsFrame > 3)
	{
		TailsFrame = 0;
	}

	if (TailsMoveLeft)
	{
		TailsPos--;
		if (TailsPos < -0x40)
		{
			TailsMoveLeft = false;
		}
	}
	else
	{
		TailsPos++;
		if (TailsPos > App->WIDTH + 0x40)
		{
			TailsMoveLeft = true;
		}
	}
}

PUBLIC void Scene_TitleScreen::Render() {

	G->SetFilter(IE_FILTER_FADEABLE);

	//BG
	G->DrawRectangle(0, 0, App->WIDTH, App->HEIGHT, 0x0022EE);

	//BG
	G->DrawSprite(TitleBGSprite, 0, 0, 0, 0, 0, 0);
	G->DrawSprite(TitleBGSprite, 0, 1, 240, 0, 0, 0);

	//Tails
	G->DrawSprite(TitleSprite, 3, TailsFrame, TailsPos, App->HEIGHT / 2 - 0x20, 0, TailsMoveLeft == true ? true : false);

	//Sonic Main
	G->DrawSprite(TitleSprite, 0, 0, App->WIDTH / 2, App->HEIGHT / 2, 0, 0);
	//'Sonic 3'
	G->DrawSprite(TitleSprite, 0, 1, App->WIDTH / 2, App->HEIGHT / 2 + 0x40, 0, 0);

	//Eye
	G->DrawSprite(TitleSprite, 1, eyeFrame, App->WIDTH / 2 - 44, App->HEIGHT / 2 - 18, 0, 0);

	//Finger
	G->DrawSprite(TitleSprite, 2, fingerFrame, App->WIDTH / 2 + 36, App->HEIGHT / 2, 0, 0);

	//'Press Any Button'
	pressTimer++;
	if (pressTimer > 59)	pressTimer = 0;
	if (pressTimer > 29) 	G->DrawSprite(TitleSprite, 0, pressFrame, App->WIDTH / 2, App->HEIGHT / 2 + 0x60, 0, 0);

	if (!App->Audio->IsPlayingMusic())
	{
		if (pressTimer > 29) G->DrawTextShadow(0, 0, "Dev Note: Fade to demo now!", 0xFFFFFF);
	}
}

PUBLIC void Scene_TitleScreen::Cleanup() {
	#define CLEANUP(name) if (name) { name->Cleanup(); delete name; name = NULL; }

	App->Audio->ClearMusic();
	CLEANUP(Sound::SoundBank[0]);
}