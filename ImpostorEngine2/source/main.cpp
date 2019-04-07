/*
 *
 * Pwease don't steal my code >:3
 *
 */

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>
#include <Engine/IGraphics.h>
#include <Engine/IInput.h>

#include <Game/LevelScene.h>
#include <Game/Player.h>
#include <ctime>

#if MSVC | MACOSX
    #include "discord_rpc.h"

    bool Inited = false;

    void Discord_Ready(const DiscordUser* connectedUser) {
    	//printf("\nDiscord: connected to user %s#%s - %s\n", connectedUser->username, connectedUser->discriminator, connectedUser->userId);
    }
    void Discord_Disconnected(int errcode, const char* message) {
    	//printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
    }
    void Discord_Error(int errcode, const char* message) {
    	//printf("\nDiscord: error (%d: %s)\n", errcode, message);
        Inited = false;
    }
    void Discord_Spectate(const char* secret) {
    	//printf("\nDiscord: spectate (%s)\n", secret);
    }
    void Discord_Init() {
    	DiscordEventHandlers handlers;
    	memset(&handlers, 0, sizeof(handlers));
    	handlers.ready = Discord_Ready;
    	handlers.errored = Discord_Error;
    	handlers.disconnected = Discord_Disconnected;

    	Discord_Initialize("379010971139702784", &handlers, 1, "");

        Inited = true;
    }
	void Discord_UpdatePresence(const char* header, const char* state, const char* imgkey) {
		//Discord_UpdatePresence(header, state, imgkey, false);
	}
    void Discord_UpdatePresence(const char* header, const char* state, const char* imgkey, bool time) {
        if (!Inited) return;

        DiscordRichPresence discordPresence;
    	memset(&discordPresence, 0, sizeof(discordPresence));
    	discordPresence.details = header;
    	discordPresence.state = state;
		if (imgkey)
    		discordPresence.largeImageKey = imgkey;
    	bool multiplayer = false;
    	if (multiplayer) {
    		//discordPresence.partyId = 0;
    		discordPresence.partySize = 1;
    		discordPresence.partyMax = 4;
    	}
    	discordPresence.instance = 1;
		if (time) {
			discordPresence.startTimestamp = std::time(nullptr);
		}
    	Discord_UpdatePresence(&discordPresence);
    }
#else
void Discord_UpdatePresence(const char* header, const char* state, const char* imgkey) {

}
void Discord_UpdatePresence(const char* header, const char* state, const char* imgkey, bool time) {

}
#endif

int HandleAppEvents(void* data, SDL_Event* event) {
    IApp* app = (IApp*)data;
    switch (event->type) {
        case SDL_APP_TERMINATING:
            app->OnEvent(event->type);
            return 0;
        case SDL_APP_LOWMEMORY:
            app->OnEvent(event->type);
            return 0;
        case SDL_APP_WILLENTERBACKGROUND:
            app->OnEvent(event->type);
            return 0;
        case SDL_APP_DIDENTERBACKGROUND:
            app->OnEvent(event->type);
            return 0;
        case SDL_APP_WILLENTERFOREGROUND:
            app->OnEvent(event->type);
            return 0;
        case SDL_APP_DIDENTERFOREGROUND:
            app->OnEvent(event->type);
            return 0;
        default:
            return 1;
    }
}

int main(int argc, char* args[]) {
#if MSVC | MACOSX
		Discord_Init();
#endif

#if NX
		/*
		"333 MHz (underclocked, very slow)", 
		"710 MHz (underclocked, slow)", 
		"1020 MHz (standard, not overclocked)", 
		"1224 MHz (slightly overclocked)", 
		"1581 MHz (overclocked)", 
		"1785 MHz (strong overclock)"
		*/
		int clock_rates[] = { 333000000, 710000000, 1020000000, 1224000000, 1581000000, 1785000000 };

		pcvInitialize();
		pcvSetClockRate(PcvModule_Cpu, clock_rates[4]);
#endif

    IApp* app = new IApp();
    SDL_SetEventFilter(HandleAppEvents, app);
    app->Run();
    app->Cleanup();

#if NX
	pcvExit();
#endif

#if MSVC | MACOSX
		Discord_Shutdown();
#endif

#ifndef NDEBUG
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		printf("Was there a leak? %d\n", _CrtDumpMemoryLeaks());

		system("pause");
#endif

    return 0;
}
