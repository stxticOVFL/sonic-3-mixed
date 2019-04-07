#ifndef IINPUT_H
#define IINPUT_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class IApp;

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

    IInput(IApp* app);
    void Cleanup();
    void Poll();
    void Vibrate(int c, double strength, int duration);
    uint8_t* GetControllerInput(int ControllerID);
    bool GetControllerInput(int ControllerID, int Button);
};

#endif /* IINPUT_H */
