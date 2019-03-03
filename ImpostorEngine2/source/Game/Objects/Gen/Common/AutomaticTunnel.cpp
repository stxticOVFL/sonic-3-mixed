// Object ID: 0x24
// Object Name: AutomaticTunnel.cpp

#include "AutomaticTunnel.h"

typedef IMath Math;

void AutomaticTunnel::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    W = 32;
    H = 32;
    PlayersGrabbed = 0;
    PathID = SubType & 0x1F;
    Reverse = (SubType & 0x80) == 0x80;
    Launch = (SubType & 0x40) == 0x40;
    int i = 0;
    AutoTunnel_Data[i++] = 0x38;
    AutoTunnel_Data[i++] = 0xD40;
    AutoTunnel_Data[i++] = 0x770;
    AutoTunnel_Data[i++] = 0xD48;
    AutoTunnel_Data[i++] = 0x770;
    AutoTunnel_Data[i++] = 0xD50;
    AutoTunnel_Data[i++] = 0x770;
    AutoTunnel_Data[i++] = 0xD58;
    AutoTunnel_Data[i++] = 0x770;
    AutoTunnel_Data[i++] = 0xD60;
    AutoTunnel_Data[i++] = 0x770;
    AutoTunnel_Data[i++] = 0xDB0;
    AutoTunnel_Data[i++] = 0x770;
    AutoTunnel_Data[i++] = 0xDD0;
    AutoTunnel_Data[i++] = 0x77C;
    AutoTunnel_Data[i++] = 0xDE0;
    AutoTunnel_Data[i++] = 0x79C;
    AutoTunnel_Data[i++] = 0xDD6;
    AutoTunnel_Data[i++] = 0x7BC;
    AutoTunnel_Data[i++] = 0xDB6;
    AutoTunnel_Data[i++] = 0x7CE;
    AutoTunnel_Data[i++] = 0xD96;
    AutoTunnel_Data[i++] = 0x7CE;
    AutoTunnel_Data[i++] = 0xD86;
    AutoTunnel_Data[i++] = 0x7C8;
    AutoTunnel_Data[i++] = 0xD70;
    AutoTunnel_Data[i++] = 0x7A8;
    AutoTunnel_Data[i++] = 0xD70;
    AutoTunnel_Data[i++] = 0x688;
}

void AutomaticTunnel::Update() {
    int d0;
    int d1;
    int d2;
    int d3;
    int d4;
    int d5;
    for (int i = 0; i < Scene->PlayerCount; i++)
{
        if (PlayersGrabbed >> i & 1) {
            Scene->Players[i]->YSpeed -= 0x38;
            PlayerTimers[i]--;
            if (PlayerTimers[i] > 0) continue;

            if (PlayerPathSize[i] == 0) continue;

            if (PlayerIndex[i] == 0) {
                PlayerPathSize[i] = AutoTunnel_Data[0] - 4;
                Scene->Players[i]->X = AutoTunnel_Data[1 + PlayerIndex[i]];
                Scene->Players[i]->Y = AutoTunnel_Data[2 + PlayerIndex[i]];
            }

            d4 = AutoTunnel_Data[3 + PlayerIndex[i]];
            d5 = AutoTunnel_Data[4 + PlayerIndex[i]];
            d0 = Math::abs(d4 - Scene->Players[i]->X);
            d1 = Math::abs(d5 - Scene->Players[i]->Y);
            d2 = Math::sign(d4 - Scene->Players[i]->X) * 0x1000;
            d3 = Math::sign(d5 - Scene->Players[i]->Y) * 0x1000;
            if (d2 == 0) d2 = 0x1000;

            if (d3 == 0) d3 = 0x1000;

            if (d1 >= d0) {
                d1 = (d5 - Scene->Players[i]->Y) << 16;
                d1 /= d3;
                if (!d1) d1 = 1;

                d0 = (d4 - Scene->Players[i]->X) << 16;
                d0 /= d3;
                Scene->Players[i]->XSpeed = d0;
                Scene->Players[i]->YSpeed = d3;
                PlayerTimers[i] = d1;
            }
            else {
                d0 = (d4 - Scene->Players[i]->X) << 16;
                d0 /= d2;
                if (!d0) d0 = 1;

                d1 = (d5 - Scene->Players[i]->Y) << 16;
                d1 /= d2;
                Scene->Players[i]->XSpeed = d2;
                Scene->Players[i]->YSpeed = d1;
                PlayerTimers[i] = d0;
            }
            PlayerIndex[i] += 2;
            PlayerPathSize[i] -= 4;
        }

    }
    Object::Update();
}

void AutomaticTunnel::Render(int CamX, int CamY) {
    if (!Scene->maxLayer) {
        G->DrawSprite(Scene->EditorSprite, 1, 4, X - CamX, Y - CamY, 0, 0);
    }

    }

int AutomaticTunnel::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* player = Scene->Players[PlayerID];
    if (!player->Ground) return 0;

    if (player->Action == ActionType::Dead) return 0;

    return 0;
    player->XSpeed = 0;
    player->YSpeed = 0;
    player->GroundSpeed = 0;
    player->X = X;
    player->Y = Y;
    player->DoCollision = false;
    player->ObjectControlled = 0xFF;
    player->Action = ActionType::Rolling;
    PlayerTimers[PlayerID] = 0;
    PlayerIndex[PlayerID] = 0;
    PlayersGrabbed |= 1 << PlayerID;
    Sound::Play(Sound::SFX_ROLL);
    return 1;
}

