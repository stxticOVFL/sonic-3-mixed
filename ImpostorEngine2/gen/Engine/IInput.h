#ifndef IINPUT_H
#define IINPUT_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL

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

    IInput(IApp* app);
    void Cleanup();
    void Poll();
    void Vibrate(int c, double strength, int duration);
    uint8_t* GetControllerInput(int ControllerID);
};

#endif /* IINPUT_H */
