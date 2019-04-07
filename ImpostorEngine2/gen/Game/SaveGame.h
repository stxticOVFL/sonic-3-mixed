#ifndef SAVEGAME_H
#define SAVEGAME_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Utils/Standard.h>
#include <Engine/iachievement.h>

class SaveGame {
public:
    struct SaveFile {
    uint8_t  State;
    uint8_t  Mode;
    uint16_t CharacterFlag;
    uint16_t PartnerFlag;
    uint8_t  Shield;
    uint8_t  BlueRing;
    uint8_t  LastZoneID;
    uint16_t Emeralds;
    uint8_t  Lives;
    uint8_t  Continues;
    uint32_t Score;
    uint32_t TargetScore;
    uint16_t UsedZoneRings[16];
    }; 
    static SaveFile Savefiles[36];
    static int32_t  CurrentSaveFile;
    static int8_t   CurrentMode;
    static int8_t   CurrentShield;
    static int8_t   CurrentBRingState;
    static int32_t  CurrentZoneID;
    static uint8_t  CurrentCharacterFlag;
    static uint8_t  CurrentPartnerFlag;
    static uint16_t CurrentUsedZoneRings;
    static uint16_t CurrentEmeralds;
    static bool		SuperEmeraldRoomActivated;
    static bool AchievementData[0x40];

    static void Init();
    static void InitializeSaveGame();
    static void InitializeSaveGame(int s);
    static void Flush();
    static void SetUsedZoneRings(int id);
    static void SetZone(int ZID);
    static int GetLives();
    static void SetLives(int Lives);
    static int GetEmerald(int id);
    static int GetEmeralds();
    static void SetEmerald(int id);
    static void SetEmerald(int id, int value);
    static void SetEmeralds(int value);
    static bool SuperEmeraldsActive();
    static void SetSuperEmeraldFlag(bool state);
};

#endif /* SAVEGAME_H */
