#if INTERFACE
#include <Utils/Standard.h>

class SaveGame {
public:
    struct SaveFile {
        uint8_t  State;
        uint16_t CharacterFlag;
        uint16_t PartnerFlag;
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
	static int32_t  CurrentZoneID;
	static uint8_t  CurrentCharacterFlag;
    static uint8_t  CurrentPartnerFlag;
	static uint16_t CurrentUsedZoneRings;
	static uint16_t CurrentEmeralds;
};
#endif

#include <Engine/IApp.h>
#include <Engine/IStreamer.h>
#include <Engine/IResources.h>

#include <Game/SaveGame.h>

/*
States:
0: New
1: Continue from Zone	
2: Clear

Starting a State 0 file initalizes all the scores and target scores etc..
*/
int32_t             SaveGame::CurrentSaveFile = -1;
int8_t				SaveGame::CurrentMode = 0;
int32_t             SaveGame::CurrentZoneID = -1;
uint8_t             SaveGame::CurrentCharacterFlag = 0;
uint8_t             SaveGame::CurrentPartnerFlag = 0xFF;
uint16_t            SaveGame::CurrentUsedZoneRings = 0x0000; // resets on every zone
uint16_t            SaveGame::CurrentEmeralds = 0xFFFF;

SaveGame::SaveFile  SaveGame::Savefiles[36];

int StartingLives = 3;
bool InitializedSaveGame = false;

PUBLIC STATIC void SaveGame::Init() {
	if (InitializedSaveGame) return;
	InitializedSaveGame = true;

	memset(SaveGame::Savefiles, 0, sizeof(SaveGame::Savefiles));
    IResource* SaveBin = IResources::Load("../Save.bin");
    if (SaveBin) {
        IStreamer reader(SaveBin);
        for (int s = 0; s < 36; s++) {
            Savefiles[s].State = reader.ReadByte();
            Savefiles[s].Mode = reader.ReadByte();
            Savefiles[s].CharacterFlag = reader.ReadUInt16();
            Savefiles[s].PartnerFlag = reader.ReadUInt16();
            Savefiles[s].LastZoneID = reader.ReadByte();
            Savefiles[s].Emeralds = reader.ReadUInt16();
            Savefiles[s].Lives = reader.ReadByte();
            Savefiles[s].Continues = reader.ReadByte();
            Savefiles[s].Score = reader.ReadUInt32();
            Savefiles[s].TargetScore = reader.ReadUInt32();
            reader.ReadBytesTo((uint8_t*)&Savefiles[s].UsedZoneRings[0], 16 << 1);
        }
        IResources::Close(SaveBin);
    }
    // If file does not exist, create one.
    else {
		SaveGame::Flush();
    }
}

PUBLIC STATIC void SaveGame::InitializeSaveGame() {
    if (SaveGame::CurrentSaveFile == -1) return;
    SaveGame::InitializeSaveGame(SaveGame::CurrentSaveFile);
}
PUBLIC STATIC void SaveGame::InitializeSaveGame(int s) {
    SaveGame::Savefiles[s].Lives = StartingLives;
    // Savefiles[s].Continues = reader.ReadByte();
    // Savefiles[s].Score = reader.ReadUInt32();
    // Savefiles[s].TargetScore = reader.ReadUInt32();
}

PUBLIC STATIC void SaveGame::Flush() {
    IResource* SaveBin = IResources::Open("../Save.bin");
    if (SaveBin) {
        IStreamer writer(SaveBin);
        for (int s = 0; s < 32; s++) {
			writer.WriteByte(Savefiles[s].State);
			writer.WriteByte(Savefiles[s].Mode);
            writer.WriteUInt16(Savefiles[s].CharacterFlag);
            writer.WriteUInt16(Savefiles[s].PartnerFlag);
            writer.WriteByte(Savefiles[s].LastZoneID);
            writer.WriteUInt16(Savefiles[s].Emeralds);
            writer.WriteByte(Savefiles[s].Lives);
            writer.WriteByte(Savefiles[s].Continues);
            writer.WriteUInt32(Savefiles[s].Score);
            writer.WriteUInt32(Savefiles[s].TargetScore);
            writer.WriteBytes((uint8_t*)&Savefiles[s].UsedZoneRings[0], 16 << 1);
        }
        IResources::Close(SaveBin);
    }
}

PUBLIC STATIC void SaveGame::SetUsedZoneRings(int id) {
	SaveGame::CurrentUsedZoneRings |= 1 << id;

	if (SaveGame::CurrentSaveFile == -1) return;
	
	SaveGame::Savefiles[SaveGame::CurrentSaveFile].UsedZoneRings[SaveGame::CurrentZoneID] = SaveGame::CurrentUsedZoneRings;
}

PUBLIC STATIC void SaveGame::SetZone(int ZID) {
	if (SaveGame::CurrentZoneID != ZID) {
		SaveGame::CurrentUsedZoneRings = 0x0000;
	}

	SaveGame::CurrentZoneID = ZID;
	if (SaveGame::CurrentSaveFile == -1) return;

	SaveGame::Savefiles[SaveGame::CurrentSaveFile].LastZoneID = ZID;
}

PUBLIC STATIC int SaveGame::GetLives() {
	if (SaveGame::CurrentSaveFile == -1) return StartingLives;

	return SaveGame::Savefiles[SaveGame::CurrentSaveFile].Lives;
}
PUBLIC STATIC void SaveGame::SetLives(int Lives) {
	if (SaveGame::CurrentSaveFile == -1) return;

	SaveGame::Savefiles[SaveGame::CurrentSaveFile].Lives = Lives;
}

PUBLIC STATIC int SaveGame::GetEmerald(int id) {
	if (SaveGame::CurrentSaveFile == -1) return SaveGame::CurrentEmeralds >> id & 1;

	return SaveGame::Savefiles[SaveGame::CurrentSaveFile].Emeralds >> id & 1;
}
PUBLIC STATIC int SaveGame::GetEmeralds() {
	if (SaveGame::CurrentSaveFile == -1) return SaveGame::CurrentEmeralds;

	return SaveGame::Savefiles[SaveGame::CurrentSaveFile].Emeralds;
}
PUBLIC STATIC void SaveGame::SetEmerald(int id) {
	SaveGame::SetEmerald(id, 1);
}
PUBLIC STATIC void SaveGame::SetEmerald(int id, int value) {
	SaveGame::CurrentEmeralds |= (value & 1) << id;
	if (SaveGame::CurrentSaveFile == -1) return;

	SaveGame::Savefiles[SaveGame::CurrentSaveFile].Emeralds = SaveGame::CurrentEmeralds;
}
PUBLIC STATIC void SaveGame::SetEmeralds(int value) {
	SaveGame::CurrentEmeralds = value;
	if (SaveGame::CurrentSaveFile == -1) return;

	SaveGame::Savefiles[SaveGame::CurrentSaveFile].Emeralds = SaveGame::CurrentEmeralds;
}