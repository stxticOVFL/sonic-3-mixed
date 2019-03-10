#if NO
#include <Utils/Standard.h>
#include <Utils/StandardSDL2.h>
#include <Engine/IApp.h>
class IAchievement {
public:
	struct Achievement {
		char Name[0x40];
		bool Achieved;
	};
	Achievement AchievementList[0x40];
	uint8_t AchievementCount = 0;
	void CreateAchievement(char* name);
	void CreateAchievement(char* name, int ID);
	void SetAchievement(int AchievementID, bool State);
	void OnAchievementGet(int AchievementID);
	IAchievement();
};
#endif

#include <Engine/iachievement.h>

PUBLIC IAchievement::IAchievement()
{
	//Setup Achievements
	//AchievementList = (Achievement*)calloc(256, sizeof(Achievement));
	//memset(AchievementList, 0, 256 * sizeof(Achievement));

	for (int i = 0; i < 0x40; i++)
	{
		SetAchievement(i, false);
	}
}

PUBLIC STATIC void IAchievement::CreateAchievement(char* name)
{
	sprintf(AchievementList[AchievementCount].Name, name);
	AchievementList[AchievementCount].Achieved = false;
	AchievementCount++;
}

PUBLIC STATIC void IAchievement::CreateAchievement(char* name, int ID)
{
	sprintf(AchievementList[ID].Name, name);
	AchievementList[ID].Achieved = false;
	AchievementCount++;
}

PUBLIC STATIC void IAchievement::SetAchievement(int AchievementID, bool State)
{
	if (State && !AchievementList[AchievementID].Achieved) OnAchievementGet(AchievementID);
	AchievementList[AchievementID].Achieved = State;
}

PUBLIC STATIC void IAchievement::OnAchievementGet(int AchievementID)
{
	printf("Got achievement: %s\n", AchievementList[AchievementID].Name);
}
