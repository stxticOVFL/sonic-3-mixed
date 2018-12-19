#include <Windows.h>

// SaveGameS3K.h
// This lib was created by Xeeynamo
// Please give me credits if you use this or part of this
// Version .25-09-10

struct TimeRecord
{
	char centiSeconds;
	char seconds;
	char minutes;
};
enum SaveGameType
{
	SONIC3K, SONIC3, TIMEATTACK
};
enum Ending
{
	STANDARD = 0, // < 7 chaos emerals
	ALLCHAOS = 1, //
	ALLSUPER = 2, // All emerdoods
	FULLGAME = 3,
	EMPTY    = 0x80
};
enum Character
{
	SONICTAILS = 0,
	SONIC      = 1,
	TAILS      = 2,
	KNUCKLES   = 3,
	BLUEKNUX   = 4
};
enum Sonic3Level
{
	ANGELISLAND, HYDROCITY, MARBLEGARDEN,
	CARNIVALNIGHT, FLYINGBATTERYS3, ICECAPS3,
	LAUNCHBASES3, CREDITS
};
enum Sonic3KLevel
{
	ICECAP3K = 4, LAUNCHBASES3K,
	MUSHROOMHILL, FLYINGBATTERY, SANDPOLIS,
	LAVAREEF, HIDDENPALACE, SKYSANCTUARY,
	DEATHEGG, THEDOOMSDAY
};
enum Emerald
{ // YELLOW Emerald is unused
	YELLOW = 0x01, CYAN = 0x02, RED = 0x04, GREY = 0x08,
	BLUE = 0x10, MAGENTA = 0x20, ORANGE = 0x40, GREEN = 0x80
};
enum TimeAttackCharacter
{
	TSONIC    = 0,
	TTAILS    = 1,
	TKNUCKLES = 2
};
enum TimeAttackLevel
{
	AZURELAKE, BALLONPARK, CHROMEGADGET, DESERTPALACE, ENDLESSMINE
};

class SaveGameS3K
{
public:
	~SaveGameS3K();
	bool Init(LPCSTR path);
	bool SelectSaveGame(SaveGameType);
	bool SelectSlot(int slot);

	// SONIC3(K)
	void  InitializeSlot();
	bool  SaveErased();
	void  EraseSave();
	UCHAR GetLevel();
	void  SetLevel(int);
	UCHAR GetCharacter();
	void  SetCharacter(int);
	WORD  GetEmeralds();
	void  SetEmeralds(WORD emeralds);

	// SONIC3K
	UCHAR GetLifes();
	void  SetLifes(UCHAR lifes);
	UCHAR GetContinues();
	void  SetContinues(UCHAR continues);
	UCHAR GetEnding();
	void  SetEnding(unsigned int ending);

	// TIMEATTACK
	void       EraseTimeRecord(TimeAttackLevel);
	Character  GetTimeCharacter(TimeAttackLevel, int place);
	void       SetTimeCharacter(TimeAttackLevel, int place, Character);
	TimeRecord GetTimeRecord(TimeAttackLevel, int place);
	void       SetTimeRecord(TimeAttackLevel, int place, TimeRecord);
};
