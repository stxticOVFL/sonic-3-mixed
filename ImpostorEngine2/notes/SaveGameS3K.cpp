#include "SaveGameS3K.h"

// SaveGameS3K.cpp
// This lib was created by Xeeynamo
// Please give me credits if you use this or part of this
// Version .25-09-10

// Offsets
#define TYPE      0
#define CHARACTER 2
#define LEVELS    3
#define EMERALDS  6
#define LIFES     8
#define CONTINUES 9 

HANDLE hFile;
LPBYTE saveBuffer;
int type, slot;
LPBYTE offset;

SaveGameS3K::~SaveGameS3K()
{
	if (hFile != NULL) // If we work on hFile when it's null, the editor will crash
	{
		SetFilePointer((HANDLE)hFile, 0, NULL, FILE_BEGIN); // Set position to 0
		DWORD dwBytesRead; // Damn, why I should use this? T.T
		WriteFile((HANDLE)hFile, saveBuffer, 0x400, &dwBytesRead, NULL); // ...Write on file? xD
		free(saveBuffer); // We've alloc saveBuffer and if we won't make memory leaks we should free it
		CloseHandle(hFile); // Close the handle to stay away from memory leaks and unuseful Handle opens
	}
}

bool SaveGameS3K::Init(LPCSTR path)
{
	type = 0xFF; // With this we say to the editor that the savegame and slots aren't selected yet
	OFSTRUCT fStruct;
	if ((hFile = (HANDLE)OpenFile(path, &fStruct, OF_READWRITE | OF_SHARE_DENY_WRITE)) == (HANDLE)-1) // Open file, it's clear.
	{
		hFile = NULL; // Ops, the file cannot be open. Set handle to NULL and escape from Init
		return false;
	}
	if (GetFileSize(hFile, NULL) != 0x400) // Okay, file loaded but it's the real savegame?
	{
CORRUPTED:
		CloseHandle(hFile); // No, isn't real savegame XD
		hFile = NULL;
		MessageBox(NULL, "The savegame is corrupted or not initialized.", "::Init", MB_ICONERROR);
		return false;
	}
	saveBuffer = (LPBYTE)malloc(0x400); // Ok, it's 1024 byte long, but we want to do more checks...
	DWORD dwBytesRead; // I hate you -.-
	ReadFile((HANDLE)hFile, saveBuffer, 0x400, &dwBytesRead, NULL); // Load savegame in RAM

	if (*((LPWORD)(saveBuffer + 0x050)) != 0x4C44 || // Verify the existence of DL
		*((LPWORD)(saveBuffer + 0x0F0)) != 0x4244 || // DC
		*((LPWORD)(saveBuffer + 0x1D0)) != 0x4244)   // DC
	{
		free(saveBuffer); // If the savegame hasn't pass the test, free memory and
		goto CORRUPTED; //  go to close the handle etc
	}
	return true; // Okay, savegame loaded! ;)
}
bool SaveGameS3K::SelectSaveGame(SaveGameType gametype)
{
	if (gametype > 2)
		return false;
	type = gametype;
	return true;
}
bool SaveGameS3K::SelectSlot(int selectslot)
{
	switch(type)
	{
	case SONIC3K:
		if (selectslot > 7) // S3K support a maximum of 8 slots
			return false;
		offset = saveBuffer + 0x180 + (selectslot * 0xA); // S3K segmet start to 0x180
		break;
	case SONIC3:
		if (selectslot > 5) // S3 support a maximum of 8 slots
			return false;
		offset = saveBuffer + 0xC0 + (selectslot * 0x8); // S3 segmet start to 0x0C0
		break;
	case TIMEATTACK:
		if (selectslot > 2)
			return false; // We can use a different way to edit timeattacks
		break;
	default:
		return false;
	}
	slot = selectslot;
	return true;
}

void SaveGameS3K::InitializeSlot()
{
	*offset = 0x00; // Initially the main flag of saveslot it's 0x80 (that means that the slot isn't initialized) and we turn it to 0x00
}
bool SaveGameS3K::SaveErased()
{
	if (type != TIMEATTACK)
		return *(offset) == 0x80; // If the mainflag is 0x80, the slot is empty
	return false;
}
void SaveGameS3K::EraseSave()
{
	if (type == SONIC3K)
	{
		ZeroMemory(offset + 1, 9); // Clear all data,
		*(offset + TYPE) = 0x80; // set the mainflag to 0x80
		*(offset + LIFES) = 0x03; // and set 3 lifes
	}
	else if (type == SONIC3)
	{
		ZeroMemory(offset + 1, 7); // Same concept.
		*(offset + 0) = 0x80;
	}
}
UCHAR SaveGameS3K::GetLevel()
{
	if (type != TIMEATTACK)
		return *(offset + LEVELS);
	return -1;
}
void SaveGameS3K::SetLevel(int level)
{
	if (type != TIMEATTACK)
		*(offset + LEVELS) = level;
}
UCHAR SaveGameS3K::GetCharacter()
{
	if (type == SONIC3K)
		return *(offset + CHARACTER) >> 4; // S3K use 0x00, 0x10, 0x20, 0x30 etc character index
	else if (type == SONIC3)
		return *(offset + CHARACTER); // S3 use 0, 1, 2, 3 etc character index
	return -1;

}
void SaveGameS3K::SetCharacter(int character)
{
	if (type == SONIC3K)
		*(offset + CHARACTER) = character << 4; // Set for example 0x01 to 0x10
	else if (type == SONIC3)
		*(offset + CHARACTER) = character;
}
WORD SaveGameS3K::GetEmeralds()
{
	if (type == SONIC3K)
		return *(LPWORD)(offset + EMERALDS); // S3K use 2 bytes for emeralds
	else if (type == SONIC3)
		return *(offset + EMERALDS);
	return -1;

}
void  SaveGameS3K::SetEmeralds(WORD emeralds)
{
	if (type == SONIC3K)
		*(LPWORD)(offset + EMERALDS) = emeralds;
	else if (type == SONIC3)
	{
		*(offset + EMERALDS) = (BYTE)emeralds;
		*(offset + EMERALDS-1) = 0;
		for(int i=0; i<8; i++) // The game want to know how emeralds you have
			if ((emeralds>>i)&1)
				*(offset + EMERALDS-1) += 1;
	}
}

UCHAR SaveGameS3K::GetLifes()
{
	if (type == SONIC3K)
		return *(offset + LIFES);
	return -1;
}
void  SaveGameS3K::SetLifes(UCHAR lifes)
{
	if (type == SONIC3K)
		*(offset + LIFES) = lifes;
}
UCHAR SaveGameS3K::GetContinues()
{
	if (type == SONIC3K)
		return *(offset + CONTINUES);
	return -1;
}
void  SaveGameS3K::SetContinues(UCHAR continues)
{
	if (type == SONIC3K)
		*(offset + CONTINUES) = continues;
}
UCHAR SaveGameS3K::GetEnding()
{
	if (type == SONIC3K)
		return *(offset + TYPE) & 0x3; // The game check only first 2 bits to know what "Ending" there is
	return -1;
}
void SaveGameS3K::SetEnding(unsigned int ending)
{
	if (type == SONIC3K)
		if (ending < 4)
			*(offset + TYPE) = ending & 0x3;
}
void SaveGameS3K::EraseTimeRecord(TimeAttackLevel level)
{
	*((LPDWORD)(saveBuffer + level * 0x10) + 0) = 0x80000000;
	*((LPDWORD)(saveBuffer + level * 0x10) + 1) = 0x80000000;
	*((LPDWORD)(saveBuffer + level * 0x10) + 2) = 0x80000000;
	*((LPDWORD)(saveBuffer + level * 0x10) + 3) = 0x80000000;
}
Character SaveGameS3K::GetTimeCharacter(TimeAttackLevel level, int place)
{
	return (Character)*(saveBuffer + level * 0x10 + 0xC + (place % 3));
}
void SaveGameS3K::SetTimeCharacter(TimeAttackLevel level, int place, Character character)
{
	*(saveBuffer + level * 0x10 + 0xC + (place % 3)) = character;
}
TimeRecord SaveGameS3K::GetTimeRecord(TimeAttackLevel level, int place)
{
	TimeRecord timerecord;
	memcpy(&timerecord, saveBuffer + (level * 0x10) + ((place%3) * 3), 3);
	return timerecord;
}
void SaveGameS3K::SetTimeRecord(TimeAttackLevel level, int place, TimeRecord timerecord)
{
	memcpy(saveBuffer + (level * 0x10) + ((place%3) * 3), &timerecord, 3);
}