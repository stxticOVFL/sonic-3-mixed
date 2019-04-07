#if NO //TODO: Figure out why this freaks out MakeHeaders.
#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class IApp;
class IGraphics;
class IAchievement;

#include <Utils/Standard.h>
#include <Engine/IApp.h>
#include <Engine/IGraphics.h>

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

#include <Engine/IAchievement.h>
#include <Game/SaveGame.h>

PUBLIC IAchievement::IAchievement() {

}

PUBLIC IAchievement::IAchievement(IApp* app) {
	App = app;
	G = App->G;
}

PUBLIC STATIC void IAchievement::CreateAchievement(char* name) {
	sprintf(AchievementList[AchievementCount].Name, name);
	AchievementList[AchievementCount].Achieved = false;
	AchievementList[AchievementCount].Initialised = true;
	AchievementCount++;
}

PUBLIC STATIC void IAchievement::CreateAchievement(char* name, int ID) {
	sprintf(AchievementList[ID].Name, name);
	AchievementList[ID].Achieved = false;
	if (!AchievementList[ID].Initialised) {
		AchievementCount++;
	} else {
		AchievementList[ID].Initialised = true;
	}
}

int PoopTimer = 0;
int PoopHold = 0;
bool PoopGot = false;

PUBLIC STATIC void IAchievement::SetAchievement(int AchievementID, bool State) {
	if (State && !AchievementList[AchievementID].Achieved)  { 		
		GotAchievement = AchievementID; 
		AchievementGet = true;
		PoopTimer = 0;
		PoopGot = false;
		printf("Got achievement: %s\n", AchievementList[AchievementID].Name);
		//Play a SFX
	}
	AchievementList[AchievementID].Achieved = State;
	SaveGame::AchievementData[AchievementID] = State;
}

PUBLIC STATIC void IAchievement::OnAchievementGet(int AchievementID) {
	//TO-DO: MAKE THIS FUCKING WORK HOLY SHIT
	App->G->DrawRectangle(App->WIDTH - PoopTimer - 10, App->HEIGHT - 60, 120, 60, 0x0000FF);

	App->G->DrawTextShadow(App->WIDTH - PoopTimer, App->HEIGHT - 50, AchievementList[AchievementID].Name, 0xFFFFFF);

	if (!App->DevMenuActive)
	{
		if (!PoopGot && PoopHold < 1) {
			PoopTimer += 4;
		}
		else if (PoopGot) {
			PoopTimer -= 4;
		}

		if (!PoopGot && PoopTimer >= 100) {
			PoopHold++;
		}

		if (PoopHold >= 0x80) {
			PoopGot = true;
		}

		if (PoopGot && PoopTimer < 0) {
			AchievementGet = false;
		}
	}
}
