#if NO
#include <Utils/Standard.h>
#include <Utils/StandardSDL2.h>
#include <Engine/IApp.h>

#define TOTAL_ACHIEVEMENT_COUNT (0x40)

class IAchievement {
public:
	struct Achievement {
		char Name[0x40];
		bool Achieved = false;
		bool Hidden = false;
		bool Initialised = false;
		//ISprite Icon;
	};
	Achievement AchievementList[TOTAL_ACHIEVEMENT_COUNT];
	uint8_t AchievementCount = 0;
	bool AchievementGet = false;
	int GotAchievement = 0;
	void CreateAchievement(char* name);
	void CreateAchievement(char* name, int ID);
	void SetAchievement(int AchievementID, bool State);
	void OnAchievementGet(int AchievementID);
	IAchievement();
	IAchievement(IApp* app);
	IApp* App = NULL;
	IGraphics* G = NULL;
};
#endif

#include <Engine/iachievement.h>

PUBLIC IAchievement::IAchievement()
{
}

PUBLIC IAchievement::IAchievement(IApp* app)
{
	App = app;
	G = App->G;
}

PUBLIC STATIC void IAchievement::CreateAchievement(char* name)
{
	sprintf(AchievementList[AchievementCount].Name, name);
	AchievementList[AchievementCount].Achieved = false;
	AchievementList[AchievementCount].Initialised = true;
	AchievementCount++;
}

PUBLIC STATIC void IAchievement::CreateAchievement(char* name, int ID)
{
	sprintf(AchievementList[ID].Name, name);
	AchievementList[ID].Achieved = false;
	if (!AchievementList[ID].Initialised) 	AchievementCount++;
	else AchievementList[ID].Initialised = true;
}

int PoopTimer = 0;
bool PoopGot = false;

PUBLIC STATIC void IAchievement::SetAchievement(int AchievementID, bool State)
{
	if (State && !AchievementList[AchievementID].Achieved) 
	{ 
		GotAchievement = AchievementID; 
		AchievementGet = true;
		PoopTimer = 0;
		PoopGot = false;
		printf("Got achievement: %s\n", AchievementList[AchievementID].Name);
	}
	AchievementList[AchievementID].Achieved = State;
}

PUBLIC STATIC void IAchievement::OnAchievementGet(int AchievementID)
{
	//TO-DO: MAKE THIS FUCKING WORK HOLY SHIT
	App->G->DrawRectangle(40, 40, 80, 80, 0xFFFFFF);

	App->G->DrawText(30, 30, AchievementList[AchievementID].Name, 0xFFFFFF);

	if (!PoopGot) PoopTimer++;
	else PoopTimer--;
	if (PoopTimer >= 40) PoopGot = true;

	if (PoopGot && PoopTimer < 0) AchievementGet = false;
}
