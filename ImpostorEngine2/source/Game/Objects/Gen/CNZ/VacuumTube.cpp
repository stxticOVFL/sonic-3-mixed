// Object ID: 0x48
// Object Name: VacuumTube.cpp

#include "VacuumTube.h"

typedef IMath Math;

void VacuumTube::Create() {
    Object::Create();
    Priority = true;
    Vertical = SubType != 0;
    if (Vertical) {
        W = 48;
        H = 64 + (SubType << 4) + 128;
        Y += 32 - H / 2 + 64;
    }
    else {
        W = 160;
        H = 64;
    }
    for (int i = 0; i < 8; i++)
{
        PlayerIn[i] = false;
        PlayerTimer[i] = 0;
    }
    SoundTimer = 0;
}

void VacuumTube::Update() {
    if (SoundTimer > 0) SoundTimer--;

    Object::Update();
}

int VacuumTube::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player->Action == ActionType::Dead) return false;

    if (Player->ObjectControlled) return false;

    if (Vertical) {
        if (PlayerIn[PlayerID] == false) {
            int PlayerDisX = Player->X - X + 0x18;
            if (PlayerDisX < 0x30) {
                int PlayerDisY = Player->Y - InitialY;
                if (PlayerDisY < 0x50) {
                    PlayerDisY = 0x50 - PlayerDisY;
                    if (PlayerDisY >= 0x40) {
                        PlayerIn[PlayerID] = true;
                        PlayerTimer[PlayerID] = SubType << 1;
                        Sound::Play(Sound::SFX_73);
                    }

                    PlayerDisY >>= 2;
                    PlayerDisY >>= 1;
                    Player->Y -= PlayerDisY;
                    Player->X += Math::sign(X - Player->X);
                    Player->Ground = false;
                    Player->Action = ActionType::Fan;
                }

            }

        }
        else if (PlayerIn[PlayerID] == true) {
            PlayerTimer[PlayerID]--;
            if (PlayerTimer[PlayerID] > 0) {
                Player->Y -= 8;
                Player->X += Math::sign(X - Player->X);
                Player->XSpeed = 0;
                Player->GroundSpeed = 0;
                Player->YSpeed = 0;
                Player->Ground = false;
                Player->Action = ActionType::Fan;
            }
            else {
                Player->YSpeed = -0x800;
                PlayerIn[PlayerID] = 0;
            }
        }

    }
    else {
        int PlayerDis = Player->X - X;
        if (!FlipX) PlayerDis = -PlayerDis;

        PlayerDis += 0x50;
        if (PlayerDis < 0xA0) {
            PlayerDis -= 0x50;
            if (PlayerDis < 0) {
                Player->GroundSpeed = 0x1000;
                if (!FlipX) Player->GroundSpeed = -Player->GroundSpeed;

                Player->XSpeed = Player->GroundSpeed;
                return true;
            }

            PlayerDis = 0x60 + PlayerDis * 2 * -1;
            if (!FlipX) PlayerDis = -PlayerDis;

            PlayerDis >>= 4;
            Player->X += PlayerDis;
            if (SoundTimer == 0) Sound::Play(Sound::SFX_VACUUM_TUBE);

        }

        SoundTimer = 32;
    }
    return true;
}

