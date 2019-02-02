#ifndef SAVEGAME_H
#define SAVEGAME_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL


#include <Utils/Standard.h>

class SaveGame {
public:
    struct SaveFile {
    uint8_t  State;
    uint16_t CharacterFlag;
    uint8_t  LastZoneID;
    uint16_t Emeralds;
    uint8_t  Lives;
    uint8_t  Continues;
    uint32_t Score;
    uint32_t TargetScore;
    uint16_t UsedZoneRings[16];
    }; 
    static SaveFile Savefiles[8];
    static int32_t  CurrentSaveFile;
    static int32_t  CurrentZoneID;
    static uint8_t  CurrentCharacterFlag;
    static uint16_t CurrentUsedZoneRings;

    static void Init();
    static void Flush();
    static void SetZone(int ZID);
    static int GetLives();
    static void SetLives(int Lives);
};

#endif /* SAVEGAME_H */
