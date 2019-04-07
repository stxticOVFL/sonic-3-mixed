#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IApp.h>

class IInput {
private:
    int ControllerCount = 0;
    uint8_t* Controllers[4];
    uint8_t  ControllerType[4];

public:
    IApp* App;
    int MouseX = 0;
    int MouseY = 0;
    bool MouseDown = false;
    bool MousePressed = false;
    bool MouseReleased = false;

    enum {
        I_PAUSE = 0,
        I_EXTRA = 1,
        I_EXTRA2 = 2,
        I_DENY = 3,
        I_CONFIRM = 4,
        I_RIGHT = 5,
        I_LEFT = 6,
        I_DOWN = 7,
        I_UP = 8,
        I_PAUSE_PRESSED = 9,
        I_EXTRA_PRESSED = 10,
        I_EXTRA2_PRESSED = 11,
        I_DENY_PRESSED = 12,
        I_CONFIRM_PRESSED = 13,
        I_RIGHT_PRESSED = 14,
        I_LEFT_PRESSED = 15,
        I_DOWN_PRESSED = 16,
        I_UP_PRESSED = 17,
		I_ANY_PRESSED = 18,
		I_ANY = 19,
    };

    int* ControllerMaps[4];

    bool UseTouchController = false;
	bool CenterPauseButton = false;

    SDL_TouchID TouchDevice;
};
#endif

#include <Engine/IInput.h>
#include <Engine/Diagnostics/Memory.h>

enum {
	NX_KEY_A = 0,
	NX_KEY_B,
	NX_KEY_X,
	NX_KEY_Y,
	NX_KEY_LSTICK, NX_KEY_RSTICK,
	NX_KEY_L, NX_KEY_R,
	NX_KEY_ZL, NX_KEY_ZR,
	NX_KEY_PLUS, NX_KEY_MINUS,
	NX_KEY_DLEFT, NX_KEY_DUP, NX_KEY_DRIGHT, NX_KEY_DDOWN,
	NX_KEY_LSTICK_LEFT, NX_KEY_LSTICK_UP, NX_KEY_LSTICK_RIGHT, NX_KEY_LSTICK_DOWN,
	NX_KEY_RSTICK_LEFT, NX_KEY_RSTICK_UP, NX_KEY_RSTICK_RIGHT, NX_KEY_RSTICK_DOWN,
	NX_KEY_SL_LEFT, NX_KEY_SR_LEFT, NX_KEY_SL_RIGHT, NX_KEY_SR_RIGHT
};

namespace ControllerType {
	enum {
		None,
		Keyboard,
		Controller,
		Touchscreen,
		JoyconLibNX,
	};
}

PUBLIC IInput::IInput(IApp* app) {
    App = app;

    for (int i = 0; i < 4; i++)
        Controllers[i] = (uint8_t*)Memory::TrackedCalloc("IInput::Controllers[i]", 1, 20);

    for (int i = 0; i < 4; i++)
        ControllerType[i] = ControllerType::None;

    ControllerType[ControllerCount++] = ControllerType::Keyboard;
    #if NX
        ControllerType[0] = ControllerType::JoyconLibNX;
    #endif

	if (IApp::Mobile) {
		ControllerType[0] = ControllerType::Touchscreen;
	}

    for (int i = 0; i < 4; i++)
        ControllerMaps[i] = (int*)Memory::TrackedCalloc("IInput::ControllerMaps[i]", 2, 18);

    struct tempStruct {
        const char* key;
        int where;
        int scancodeDefault;
    };

    tempStruct defaultKeys[9] = {
        { "up", I_UP, SDL_SCANCODE_UP },
        { "down", I_DOWN, SDL_SCANCODE_DOWN },
        { "left", I_LEFT, SDL_SCANCODE_LEFT },
        { "right", I_RIGHT, SDL_SCANCODE_RIGHT },

        { "confirm", I_CONFIRM, SDL_SCANCODE_A },
        { "deny", I_DENY, SDL_SCANCODE_S },
		{ "extra2", I_EXTRA2, SDL_SCANCODE_D },
        { "extra", I_EXTRA, SDL_SCANCODE_Q },
        { "pause", I_PAUSE, SDL_SCANCODE_RETURN },
    };

	if (IApp::Platform == Platforms::Switch) {
		tempStruct defaultKeysOverride[9] = {
			{ "up", I_UP, NX_KEY_DUP },
			{ "down", I_DOWN, NX_KEY_DDOWN },
			{ "left", I_LEFT, NX_KEY_DLEFT },
			{ "right", I_RIGHT, NX_KEY_DRIGHT },

			{ "confirm", I_CONFIRM, NX_KEY_A },
			{ "deny", I_DENY, NX_KEY_B },
			{ "extra2", I_EXTRA2, NX_KEY_Y },
			{ "extra", I_EXTRA, NX_KEY_X },
			{ "pause", I_PAUSE, NX_KEY_PLUS },
		};
		memcpy(defaultKeys, defaultKeysOverride, sizeof(defaultKeysOverride));
	}
	else if (IApp::Platform == Platforms::Android) {
		tempStruct defaultKeysOverride[9] = {
			{ "up", I_UP, SDL_SCANCODE_UP },
			{ "down", I_DOWN, SDL_SCANCODE_DOWN },
			{ "left", I_LEFT, SDL_SCANCODE_LEFT },
			{ "right", I_RIGHT, SDL_SCANCODE_RIGHT },

			{ "confirm", I_CONFIRM, SDL_SCANCODE_A },
			{ "deny", I_DENY, SDL_SCANCODE_AC_BACK },
			{ "extra2", I_EXTRA2, SDL_SCANCODE_D },
			{ "extra", I_EXTRA, SDL_SCANCODE_Q },
			{ "pause", I_PAUSE, SDL_SCANCODE_W },
		};
		memcpy(defaultKeys, defaultKeysOverride, sizeof(defaultKeysOverride));
	}

    for (int i = 0; i < sizeof(defaultKeys) / sizeof(tempStruct); i++) {
        if (!App->Settings->GetInteger("input1", defaultKeys[i].key, &ControllerMaps[0][defaultKeys[i].where]))
            ControllerMaps[0][defaultKeys[i].where] = defaultKeys[i].scancodeDefault;
    }
}

PUBLIC void IInput::Cleanup() {
    for (int i = 0; i < 4; i++) {
        Memory::Free(Controllers[i]);
    }
	for (int i = 0; i < 4; i++) {
		Memory::Free(ControllerMaps[i]);
    }
}

PUBLIC void IInput::Poll() {
    bool touchEnabled = false;
    SDL_TouchID touchID;
    int w = App->WIDTH;
    int h = App->HEIGHT;

    if (IApp::Platform == Platforms::iOS || IApp::Platform == Platforms::Android) {
        for (int d = SDL_GetNumTouchDevices() - 1; d >= 0; d--) {
            if ((touchID = SDL_GetTouchDevice(d))) {
                if (UseTouchController) {
                    touchEnabled = true;
                    break;
                }
                else {
                    touchEnabled = false;

                    bool Down = false;
                    for (int t = 0; t < SDL_GetNumTouchFingers(touchID) && t < 1; t++) {
                        SDL_Finger* finger = SDL_GetTouchFinger(touchID, t);
                        int tx = int(finger->x * w);
                        int ty = int(finger->y * h);

                        MouseX = tx;
                        MouseY = ty;

                        Down = true;
                    }
                    MouseReleased = !Down && MouseDown;
                    MousePressed = Down && !MouseDown;
                    MouseDown = Down;
                    break;
                }
            }
        }
    }
    else {
        int mx, my;
        Uint32 button = SDL_GetMouseState(&mx, &my);
        MouseX = mx * App->WIDTH / App->G->WindowWidth;
        MouseY = my * App->HEIGHT / App->G->WindowHeight;

        MouseReleased = ((button & SDL_BUTTON(SDL_BUTTON_LEFT)) == 0) && MouseDown;
        MousePressed = ((button & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0) && !MouseDown;
        MouseDown = (button & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
    }

    for (int i = 0; i < ControllerCount; i++) {
        bool UP = false, DOWN = false, LEFT = false, RIGHT = false, CONFIRM = false, DENY = false, EXTRA = false, EXTRA2 = false, PAUSE = false;

        if (ControllerType[i] == ControllerType::Keyboard) { // Keyboard
            const unsigned char *state = SDL_GetKeyboardState(NULL);

            UP = state[ControllerMaps[i][I_UP]];
            DOWN = state[ControllerMaps[i][I_DOWN]];
            LEFT = state[ControllerMaps[i][I_LEFT]];
            RIGHT = state[ControllerMaps[i][I_RIGHT]];

            CONFIRM = state[ControllerMaps[i][I_CONFIRM]];
            DENY = state[ControllerMaps[i][I_DENY]];
			EXTRA2 = state[ControllerMaps[i][I_EXTRA2]];
            EXTRA = state[ControllerMaps[i][I_EXTRA]];
            PAUSE = state[ControllerMaps[i][I_PAUSE]];
        }
        else if (ControllerType[i] == ControllerType::JoyconLibNX) { // Joycons
            #if NX
                hidScanInput();
                //mainLoop = appletMainLoop();
                u64 hid = hidKeysHeld(CONTROLLER_P1_AUTO);

                UP = (hid & KEY_DUP) != 0 || (hid & KEY_LSTICK_UP) != 0;
                DOWN = (hid & KEY_DDOWN) != 0 || (hid & KEY_LSTICK_DOWN) != 0;
                LEFT = (hid & KEY_DLEFT) != 0 || (hid & KEY_LSTICK_LEFT) != 0;
                RIGHT = (hid & KEY_DRIGHT) != 0 || (hid & KEY_LSTICK_RIGHT) != 0;

                CONFIRM = (hid & KEY_A) != 0;
                DENY = (hid & KEY_B) != 0;
                EXTRA = (hid & KEY_X) != 0;
                PAUSE = (hid & KEY_PLUS) != 0 || (hid & KEY_MINUS) != 0;
            #endif
        }
		else if (ControllerType[i] == ControllerType::Touchscreen) {
			if (touchEnabled) {
				for (int t = 0; t < SDL_GetNumTouchFingers(touchID); t++) {
					SDL_Finger* finger = SDL_GetTouchFinger(touchID, t);
					int tx = int(finger->x * w);
					int ty = int(finger->y * h);

					int bx = 48;
					int by = h - 48;
					int dis = (tx - bx) * (tx - bx) + (ty - by) * (ty - by);

					if (dis >= 10 * 10 && dis < 150 * 150) {
						int ang = IMath::atanHex(tx - bx, ty - by);
						if ((ang >= 0x00 && ang < 0x10) || (ang >= 0xF0 && ang <= 0xFF))
							RIGHT = true;
						else if (ang >= 0x10 && ang < 0x30)
							UP = RIGHT = true;
						else if (ang >= 0x30 && ang < 0x50)
							UP = true;
						else if (ang >= 0x50 && ang < 0x70)
							LEFT = UP = true;
						else if (ang >= 0x70 && ang < 0x90)
							LEFT = true;
						else if (ang >= 0x90 && ang < 0xB0)
							DOWN = LEFT = true;
						else if (ang >= 0xB0 && ang < 0xD0)
							DOWN = true;
						else if (ang >= 0xD0 && ang < 0xF0)
							RIGHT = DOWN = true;
					}

					bx = w - 48;
					if ((tx - bx) * (tx - bx) + (ty - by) * (ty - by) < 64 * 64) {
						CONFIRM = true;
					}

					bx = w - 20;
					if (CenterPauseButton)
						bx = w / 2;
					by = 20;
					if ((tx - bx) * (tx - bx) + (ty - by) * (ty - by) < 64 * 64) {
						PAUSE = true;
					}
				}
			}
		}

        Controllers[i][I_UP_PRESSED] = UP && !Controllers[i][I_UP];
        Controllers[i][I_DOWN_PRESSED] = DOWN && !Controllers[i][I_DOWN];
        Controllers[i][I_LEFT_PRESSED] = LEFT && !Controllers[i][I_LEFT];
        Controllers[i][I_RIGHT_PRESSED] = RIGHT && !Controllers[i][I_RIGHT];
        Controllers[i][I_CONFIRM_PRESSED] = CONFIRM && !Controllers[i][I_CONFIRM];
        Controllers[i][I_DENY_PRESSED] = DENY && !Controllers[i][I_DENY];
		Controllers[i][I_EXTRA2_PRESSED] = EXTRA2 && !Controllers[i][I_EXTRA2];
        Controllers[i][I_EXTRA_PRESSED] = EXTRA && !Controllers[i][I_EXTRA];
        Controllers[i][I_PAUSE_PRESSED] = PAUSE && !Controllers[i][I_PAUSE];

		Controllers[i][I_ANY_PRESSED] = false;
		Controllers[i][I_ANY] = false;

		if (Controllers[i][I_UP_PRESSED] ||
			Controllers[i][I_DOWN_PRESSED] ||
			Controllers[i][I_LEFT_PRESSED] ||
			Controllers[i][I_RIGHT_PRESSED] ||
			Controllers[i][I_CONFIRM_PRESSED] ||
			Controllers[i][I_DENY_PRESSED] ||
			Controllers[i][I_EXTRA2_PRESSED] ||
			Controllers[i][I_EXTRA_PRESSED] ||
			Controllers[i][I_PAUSE_PRESSED] ||
			MouseDown)
		{
			Controllers[i][I_ANY_PRESSED] = true;
		}

        Controllers[i][I_UP] = UP;
        Controllers[i][I_DOWN] = DOWN;
        Controllers[i][I_LEFT] = LEFT;
        Controllers[i][I_RIGHT] = RIGHT;
        Controllers[i][I_CONFIRM] = CONFIRM;
        Controllers[i][I_DENY] = DENY;
		Controllers[i][I_EXTRA2] = EXTRA2;
        Controllers[i][I_EXTRA] = EXTRA;
        Controllers[i][I_PAUSE] = PAUSE;

		for (int ii = 0; ii < 17; ii++)
		{
			if (Controllers[i][ii])
			{
				Controllers[i][I_ANY] = true;
				break;
			}
		}
    }
}

PUBLIC void IInput::Vibrate(int c, double strength, int duration) {

}

PUBLIC uint8_t* IInput::GetControllerInput(int ControllerID) {
	if (ControllerID < 0) return NULL;
    return Controllers[ControllerID];
}

PUBLIC bool IInput::GetControllerInput(int ControllerID, int Button) {
	if (ControllerID < 0) return false;
	return !!Controllers[ControllerID][Button];
}
