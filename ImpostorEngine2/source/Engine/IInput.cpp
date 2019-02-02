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
        I_DENY = 2,
        I_CONFIRM = 3,
        I_RIGHT = 4,
        I_LEFT = 5,
        I_DOWN = 6,
        I_UP = 7,
        I_PAUSE_PRESSED = 8,
        I_EXTRA_PRESSED = 9,
        I_DENY_PRESSED = 10,
        I_CONFIRM_PRESSED = 11,
        I_RIGHT_PRESSED = 12,
        I_LEFT_PRESSED = 13,
        I_DOWN_PRESSED = 14,
        I_UP_PRESSED = 15,
    };

    int* ControllerMaps[4];

    bool UseTouchController = false;

    SDL_TouchID TouchDevice;
};
#endif

#include <Engine/IInput.h>

PUBLIC IInput::IInput(IApp* app) {
    App = app;

    for (int i = 0; i < 4; i++)
        Controllers[i] = (uint8_t*)calloc(1, 16);

    for (int i = 0; i < 4; i++)
        ControllerType[i] = 0xFF;

    ControllerType[ControllerCount++] = 0;
    #if NX
        ControllerType[0] = 0xCA;
    #endif

    for (int i = 0; i < 4; i++)
        ControllerMaps[i] = (int*)calloc(2, 16);

    struct tempStruct {
        const char* key;
        int where;
        int scancodeDefault;
    };

    tempStruct defaultKeys[8] = {
        { "up", I_UP, SDL_SCANCODE_UP },
        { "down", I_DOWN, SDL_SCANCODE_DOWN },
        { "left", I_LEFT, SDL_SCANCODE_LEFT },
        { "right", I_RIGHT, SDL_SCANCODE_RIGHT },

        { "confirm", I_CONFIRM, SDL_SCANCODE_A },
        { "deny", I_DENY, SDL_SCANCODE_S },
        { "extra", I_EXTRA, SDL_SCANCODE_Q },
        { "pause", I_PAUSE, SDL_SCANCODE_W },
    };

	if (IApp::Platform == Platforms::Switch) {
		tempStruct defaultKeysNx[8] = {
			{ "up", I_UP, SDL_SCANCODE_UP },
			{ "down", I_DOWN, SDL_SCANCODE_DOWN },
			{ "left", I_LEFT, SDL_SCANCODE_LEFT },
			{ "right", I_RIGHT, SDL_SCANCODE_RIGHT },

			{ "confirm", I_CONFIRM, SDL_SCANCODE_A },
			{ "deny", I_DENY, SDL_SCANCODE_S },
			{ "extra", I_EXTRA, SDL_SCANCODE_Q },
			{ "pause", I_PAUSE, SDL_SCANCODE_W },
		};
		memcpy(defaultKeys, defaultKeysNx, sizeof(defaultKeysNx));
	}

    for (int i = 0; i < 8; i++) {
        if (!App->Settings->GetInteger("input1", defaultKeys[i].key, &ControllerMaps[0][defaultKeys[i].where]))
            ControllerMaps[0][defaultKeys[i].where] = defaultKeys[i].scancodeDefault;
    }
}

PUBLIC void IInput::Cleanup() {
    for (int i = 0; i < 4; i++)
        free(Controllers[i]);
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
    else if (IApp::Platform != Platforms::Switch) {
        int mx, my;
        Uint32 button = SDL_GetMouseState(&mx, &my);
        MouseX = mx * App->WIDTH / App->G->WindowWidth;
        MouseY = my * App->HEIGHT / App->G->WindowHeight;

        MouseReleased = ((button & SDL_BUTTON(SDL_BUTTON_LEFT)) == 0) && MouseDown;
        MousePressed = ((button & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0) && !MouseDown;
        MouseDown = (button & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
    }

    for (int i = 0; i < ControllerCount; i++) {
        bool UP = false, DOWN = false, LEFT = false, RIGHT = false, CONFIRM = false, DENY = false, EXTRA = false, PAUSE = false;

        if (ControllerType[i] == 0x00) { // Keyboard
            const unsigned char *state = SDL_GetKeyboardState(NULL);

            UP = state[ControllerMaps[i][I_UP]];
            DOWN = state[ControllerMaps[i][I_DOWN]];
            LEFT = state[ControllerMaps[i][I_LEFT]];
            RIGHT = state[ControllerMaps[i][I_RIGHT]];

            CONFIRM = state[ControllerMaps[i][I_CONFIRM]];
            DENY = state[ControllerMaps[i][I_DENY]];
            EXTRA = state[ControllerMaps[i][I_EXTRA]];
            PAUSE = state[ControllerMaps[i][I_PAUSE]];
        }
        else if (ControllerType[i] == 0xCA) { // Joycons
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

        if (touchEnabled) {
            for (int t = 0; t < SDL_GetNumTouchFingers(touchID); t++) {
                SDL_Finger* finger = SDL_GetTouchFinger(touchID, t);
                int tx = int(finger->x * w);
                int ty = int(finger->y * h);

                int bx = 48;
                int by = h - 48;

                if ((tx - bx) * (tx - bx) + (ty - by) * (ty - by) < 150 * 150) {
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
                by = 20;
                if ((tx - bx) * (tx - bx) + (ty - by) * (ty - by) < 64 * 64) {
                    PAUSE = true;
                }
            }
        }

        Controllers[i][15] = UP && !Controllers[i][15 - 8];
        Controllers[i][14] = DOWN && !Controllers[i][14 - 8];
        Controllers[i][13] = LEFT && !Controllers[i][13 - 8];
        Controllers[i][12] = RIGHT && !Controllers[i][12 - 8];
        Controllers[i][11] = CONFIRM && !Controllers[i][11 - 8];
        Controllers[i][10] = DENY && !Controllers[i][10 - 8];
        Controllers[i][9] = EXTRA && !Controllers[i][9 - 8];
        Controllers[i][8] = PAUSE && !Controllers[i][8 - 8];

        Controllers[i][7] = UP;
        Controllers[i][6] = DOWN;
        Controllers[i][5] = LEFT;
        Controllers[i][4] = RIGHT;
        Controllers[i][3] = CONFIRM;
        Controllers[i][2] = DENY;
        Controllers[i][1] = EXTRA;
        Controllers[i][0] = PAUSE;

    }
}

PUBLIC void IInput::Vibrate(int c, double strength, int duration) {

}

PUBLIC uint8_t* IInput::GetControllerInput(int ControllerID) {
    return Controllers[ControllerID];
}
