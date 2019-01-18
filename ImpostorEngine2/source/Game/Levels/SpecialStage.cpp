#if INTERFACE
#include <Game/LevelScene.h>

class Level_SpecialStage : public LevelScene {
public:
    ISprite* Globe = NULL;
    ISprite* GlobeSpin = NULL;
    ISprite* Horizon = NULL;
    ISprite* Objects = NULL;
    ISprite* Players = NULL;

    uint8_t* Layout = NULL;
    uint8_t* LayoutCopy = NULL;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/SpecialStage.h>

int PlayerAngle = 0x0000;
int PlayerX = 0x0000;
int PlayerY = 0x0000;
int PlayerSteps = 0;
int StoredAngle = 0x0;

int StartAngle = 0x0000;
int StartX = 0x0000;
int StartY = 0x0000;

int PerfectAmount = 0;

int NextAngle = -1;
int Direction = 0;
int DirectionStep = 0;

int BallCount = 0;

PUBLIC Level_SpecialStage::Level_SpecialStage(IApp* app, IGraphics* g) : LevelScene(app, g) {
    ZoneID = 20;
    Act = 1;

    Sound::SoundBank[0] = new ISound("Music/Mixed/BlueSpheresSPD.ogg");
    Sound::Audio->LoopPoint[0] = 5309957;

    Globe = new ISprite("Stages/Special/Globe.gif", App);

    GlobeSpin = new ISprite("Stages/Special/GlobeSpin.gif", App);
    GlobeSpin->LoadAnimation("Stages/Special/GlobeSpin.bin");

    Horizon = new ISprite("Stages/Special/Horizon.gif", App);
    Horizon->LoadAnimation("Stages/Special/Horizon.bin");

    Objects = new ISprite("Stages/Special/Objects.gif", App);
    Objects->LoadAnimation("Stages/Special/HUD.bin");
    Objects->LoadAnimation("Stages/Special/StageObjects.bin");
    //Objects->LoadAnimation("Stages/Special/PaletteIcon.bin");

    Players = new ISprite("Stages/Special/Players.gif", App);
    Players->LoadAnimation("Stages/Special/Sonic.bin");
    Players->LoadAnimation("Stages/Special/Tails.bin");
    Players->LoadAnimation("Stages/Special/Knuckles.bin");

    Str_TileConfigBin = ":";
    Str_SceneBin = ":";
    Str_TileSprite = ":";
    Str_ObjectsList = ":";
    Str_RingsList = ":";

    IResource* LayoutBin = IResources::Load("Stages/Special/S3 1.bin");
    if (LayoutBin) {
        IStreamer reader(LayoutBin);
        Layout = (uint8_t*)malloc(0x400);
        LayoutCopy = reader.ReadBytes(0x400);
        StartAngle = reader.ReadUInt16E();
        StartX = reader.ReadUInt16E();
        StartY = reader.ReadUInt16E();
        PerfectAmount = reader.ReadUInt16E();
        IResources::Close(LayoutBin);
    }
}

Sint32 MapThing[0x10][0x100];

vector<pair<int,int>> dots[9][32];

PUBLIC void Level_SpecialStage::Init() {
    PlayerCount = 0;

    IResource* PerspectiveMapBin = IResources::Load("Stages/Special/Perspective Maps.bin");
    if (PerspectiveMapBin) {
        IStreamer reader(PerspectiveMapBin);
        PerspectiveMap = reader.ReadBytes(0x54BC);
        IResources::Close(PerspectiveMapBin);
    }

    IResource* BSS_Setup_Bin = IResources::Load("Stages/Special/OBJ_BSS_Setup.bin");
    if (BSS_Setup_Bin) {
        IStreamer reader(BSS_Setup_Bin);

        reader.ReadUInt32(); // MAGIC

        for (int p = 0; p < 0x10; p++) {
            for (int i = 0; i < 0x100; i++) {
                MapThing[p][i] = 0;
            }
        }


        for (int i = 0; i < 15; i++) {
            reader.ReadByte();
            /*
            char bin[9];
            Uint8 a = reader.ReadByte();
            for (int b = 0; b < 8; b++) {
                bin[b] = '0' + (a >> 7 & 1);
                a <<= 1;
            }
            bin[8] = 0;
            //*/

            reader.ReadUInt32();
            //App->Print(1, "Value %d: %s %X", i, bin, b);
        }

        int count = reader.ReadUInt32();
        for (int i = 0; i < count; i++) {
            reader.ReadUInt32();
            //App->Print(1, "Value %d: %X", i, reader.ReadUInt32());
        }

        for (int p = 0; p < 6; p++) {
            reader.ReadByte();
            reader.ReadUInt32();
            int jimmy = reader.ReadUInt32();
            MapThing[p][0] = jimmy;

            //App->Print(0, "Count [%d]: %X (%X)", p, MapThing[p][0], jimmy);

            for (int i = 0; i < MapThing[p][0]; i++) {
                MapThing[p][i + 1] = reader.ReadUInt32();

                //App->Print(2, "%X: %X", i, MapThing[p][i + 1]);
            }
        }

        IResources::Close(BSS_Setup_Bin);
    }

    //exit(0);

    RestartStage(true, true);
}

PUBLIC void Level_SpecialStage::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    memcpy(Layout, LayoutCopy, 0x400);
    PlayerX = StartX >> 4;
    PlayerY = StartY >> 4;
    PlayerAngle = StartAngle;
    StoredAngle = PlayerAngle >> 12;

    BallCount = 0;
    for (int i = 0; i < 0x400; i++) {
        if (Layout[i] == 2)
            BallCount++;
    }
}

PUBLIC bool Level_SpecialStage::CheckSurround(int startX, int startY, int lastX, int lastY, int nX, int nY, int chkFor) {
    if (Layout[nY << 5 | nX] == chkFor) {

    }
    return false;
}

PUBLIC void Level_SpecialStage::EarlyUpdate() {
    if ((PlayerX & 0xF) == 0 && (PlayerY & 0xF) == 0) {
        int XIndex = PlayerX >> 4;
        int YIndex = PlayerY >> 4;

        if (Layout[YIndex << 5 | XIndex] == 2) {
            Layout[YIndex << 5 | XIndex] = 1;
            BallCount--;
        }
    }

    if (Direction == 0) {
        if (App->Input->GetControllerInput(0)[5]) {
            Direction = 1;

            if ((PlayerX & 0xF) != 0 || (PlayerY & 0xF) != 0) {
                GlobeSpin->SetPalette(128, Globe->GetPalette(1));
                GlobeSpin->SetPalette(144, Globe->GetPalette(17));
            }
            else {
                GlobeSpin->SetPalette(128, Globe->GetPalette(17));
                GlobeSpin->SetPalette(144, Globe->GetPalette(1));
            }
        }
        if (App->Input->GetControllerInput(0)[4]) {
            Direction = -1;

            if ((PlayerX & 0xF) != 0 || (PlayerY & 0xF) != 0) {
                GlobeSpin->SetPalette(128, Globe->GetPalette(17));
                GlobeSpin->SetPalette(144, Globe->GetPalette(1));
            }
            else {
                GlobeSpin->SetPalette(128, Globe->GetPalette(1));
                GlobeSpin->SetPalette(144, Globe->GetPalette(17));
            }
        }
    }

    if ((PlayerX & 0xF) == 0 && (PlayerY & 0xF) == 0 && Direction != 0) {
        if (DirectionStep == 0) {
            StoredAngle = PlayerAngle >> 12;
        }
        if (Direction > 0) {
            PlayerAngle = (PlayerAngle + 0x400) & 0xFFFF;
            DirectionStep++;
        }
        else {
            PlayerAngle = (PlayerAngle + 0xFC00) & 0xFFFF;
            DirectionStep++;
        }
        if ((PlayerAngle & 0xC000) == PlayerAngle) {
            Direction = 0;
            DirectionStep = 0;
        }
    }
}
PUBLIC void Level_SpecialStage::Subupdate() {
    if ((PlayerAngle & 0xC000) == PlayerAngle) {
        switch (PlayerAngle >> 12) {
            case 0x0:
                PlayerY = (PlayerY - 1 + 0x200) & 0x1FF;
                break;
            case 0x4:
                PlayerX = (PlayerX - 1 + 0x200) & 0x1FF;
                break;
            case 0x8:
                PlayerY = (PlayerY + 1) & 0x1FF;
                break;
            case 0xC:
                PlayerX = (PlayerX + 1) & 0x1FF;
                break;
        }
        PlayerSteps = (PlayerSteps + 1) & 0x1F;
    }
}
PUBLIC void Level_SpecialStage::HandleCamera() {

}

PUBLIC int Level_SpecialStage::GetPushDownY(int ScreenY, int X) {
    return ((X * X) / (820 + 16 * (ScreenY - 38))) + ScreenY;
}

int columnIDX = 0;
int dotFrame = 0;

PUBLIC void Level_SpecialStage::RenderEverything() {
	int idx = 0;
    switch (PlayerAngle >> 12) {
        case 0x0:
            idx = (0x20 - PlayerY) & 0x1F;
            break;
        case 0x4:
            idx = (0x20 - PlayerX) & 0x1F;
            break;
        case 0x8:
            idx = (PlayerY) & 0x1F;
            break;
        case 0xC:
            idx = (PlayerX) & 0x1F;
            break;
    }

	int n = idx & 0x1F;

    G->DrawRectangle(0, 0, App->WIDTH, 128, 0x0044EE);

    if ((PlayerAngle & 0xC000) == PlayerAngle) {
        int t = PlayerSteps;
        if (PlayerAngle >> 14 & 1) {
            for (int i = 0; i < 16; i++) {
                Globe->SetPalette(1  + i, (t >= i) ^ (t - 16 < i) ? 0xEE8800 : 0x662200);
                Globe->SetPalette(17 + i, (t >= i) ^ (t - 16 < i) ? 0x662200 : 0xEE8800);
            }
        }
        else {
            for (int i = 0; i < 16; i++) {
                Globe->SetPalette(17 + i, (t >= i) ^ (t - 16 < i) ? 0xEE8800 : 0x662200);
                Globe->SetPalette(1  + i, (t >= i) ^ (t - 16 < i) ? 0x662200 : 0xEE8800);
            }
        }

        G->DrawSprite(Globe, 0, 0, 512, 240, App->WIDTH / 2, 0, 0, IE_NOFLIP, -256, 0);
    }
    else {
        bool fl = false;
        int fr = (PlayerAngle & 0x3F00) >> 10;
        if (fr >= 8) {
            fr = 7 - (fr - 8);
            fl = true;
        }

        G->DrawSprite(GlobeSpin,
            GlobeSpin->Animations[0].Frames[fr].X,
            GlobeSpin->Animations[0].Frames[fr].Y,
            GlobeSpin->Animations[0].Frames[fr].W,
            GlobeSpin->Animations[0].Frames[fr].H,
            App->WIDTH / 2,
            0,
            0,
            fl ? IE_FLIPX : IE_NOFLIP,
            -256,
            0);
    }

    G->DrawModeOverlay = true;
    G->DrawAlpha = 0x80;
    G->DrawSprite(Horizon, 0, 144, 256, 112, App->WIDTH / 2, 38, 0, IE_NOFLIP, -256, 0);
    G->DrawSprite(Horizon, 0, 144, 256, 112, App->WIDTH / 2, 38, 0, IE_FLIPX, 0, 0);
    G->DrawAlpha = 0x40;
    G->DrawSprite(Horizon, 0, 0, 256, 143, App->WIDTH / 2, 0, 0, IE_NOFLIP, -256, 0);
    G->DrawSprite(Horizon, 0, 0, 256, 143, App->WIDTH / 2, 0, 0, IE_FLIPX, 0, 0);
    G->DrawModeOverlay = false;
    G->DrawAlpha = 0xFF;

    idx = (idx >> 1) & 0xF;

    uint32_t index = (PerspectiveMap[idx * 4 + 0] << 24 | PerspectiveMap[idx * 4 + 1] << 16 | PerspectiveMap[idx * 4 + 2] << 8 | PerspectiveMap[idx * 4 + 3]) - 0xFF0000;
    if ((PlayerAngle & 0xC000) != PlayerAngle && DirectionStep < 14) {
        idx = 16 + DirectionStep / 2;
        index = (PerspectiveMap[idx * 4 + 0] << 24 | PerspectiveMap[idx * 4 + 1] << 16 | PerspectiveMap[idx * 4 + 2] << 8 | PerspectiveMap[idx * 4 + 3]) - 0xFF0000;
    }

    /*
    for (int i = 0xEF; i >= 0x0; i--) {
        int j = i / 0xF;
        if (j > 0xB)
            continue;

        int k = i % 0xF;
        if (k <= 3)
            continue;
        if (k >= 13)
            continue;

        int16_t x = (int16_t)((PerspectiveMap[index + 2 + i * 6] << 8 | PerspectiveMap[index + 3 + i * 6]));
        int16_t y = (int16_t)((PerspectiveMap[index + 4 + i * 6] << 8 | PerspectiveMap[index + 5 + i * 6]));

		if ((inx & 1) && (in & 0xF) != 1) {
			idx = (in >> 1) & 0xF;
            int index2 = (PerspectiveMap[idx * 4 + 0] << 24 | PerspectiveMap[idx * 4 + 1] << 16 | PerspectiveMap[idx * 4 + 2] << 8 | PerspectiveMap[idx * 4 + 3]) - 0xFF0000;
            x += (int16_t)((PerspectiveMap[index2 + 2 + i * 6] << 8 | PerspectiveMap[index2 + 3 + i * 6]));
            y += (int16_t)((PerspectiveMap[index2 + 4 + i * 6] << 8 | PerspectiveMap[index2 + 5 + i * 6]));
            x /= 2;
            y /= 2;
        }

		j -= 5;
		j *= 16;
		j -= inx & 0xF;
		j = j * 2 / 7;
		j -= 1;

		if (j < 0)
			continue;

        x -= 0x120;
        y -= 0x74;

		int fr = 0x1F - j;
		j = i / 0xF;

        int XIndex, YIndex;

        int relX = k - 8;
        int relY = j - 6;

        if ((PlayerAngle & 0xC000) == PlayerAngle) {
            switch (PlayerAngle >> 12) {
                case 0x0:
                    XIndex = (relX + (PlayerX >> 4)) & 0x1F;
            		YIndex = (((0xF + PlayerY) >> 4) - relY) & 0x1F;
                    break;
                case 0x4:
                    // moving left
                    XIndex = (((0xF + PlayerX) >> 4) - relY) & 0x1F;
            		YIndex = ((PlayerY >> 4) - relX) & 0x1F;
                    break;
                case 0x8: // correct
                    XIndex = (((0xF + PlayerX) >> 4) - relX) & 0x1F;
            		YIndex = (relY + (PlayerY >> 4)) & 0x1F;
                    break;
                case 0xC: // correct
                    // moving right
                    XIndex = (relY + (PlayerX >> 4)) & 0x1F;
            		YIndex = (relX + (PlayerY >> 4)) & 0x1F;
                    break;
            }
        }
        else {
            XIndex = 2;
            YIndex = 2;
        }

        int a = 0;
        if (Layout[YIndex << 5 | XIndex] == 1)
            a = 5;
        else if (Layout[YIndex << 5 | XIndex] == 2)
            a = 4;
        else if (Layout[YIndex << 5 | XIndex] == 3)
            a = 6;
        else if (Layout[YIndex << 5 | XIndex] == 4)
            a = 13;
        else if (Layout[YIndex << 5 | XIndex] == 5)
            a = 7;

        if (a > 0 && false)
    		G->DrawSprite(Objects,
    			Objects->Animations[a].Frames[fr].X,
    			Objects->Animations[a].Frames[fr].Y,
    			Objects->Animations[a].Frames[fr].W,
    			Objects->Animations[a].Frames[fr].H,
    			x + App->WIDTH / 2,
    			y + 2,
    			0,
    			IE_NOFLIP,
    			-Objects->Animations[a].Frames[fr].W / 2,
    			Objects->Animations[a].Frames[fr].OffY);

		// Blue Spheres Layout
		// 1 byte per sphere, 32 x 32 total (0x400)
		// 0x400 (word): Player Start Angle
		// 0x402 (word): Player Start X
		// 0x404 (word): Player Start Y
		// 0x406 (word): Ring Perfect Amount
		// Sphere Type:
		// 0: Empty
		// 1: Red
		// 2: Blue
		// 3: Bumper
		// 4: Ring
		// 5: Yellow
    }
    //*/


    // 2: distances (Y-position)
    // 3: ???
    // 4: column width at distance index (curvature)!!!!!!!!!!!

    // 5: is the sprite index at distance index


    // Draw order
    int sh[9] = { -4, 4, -3, 3, -2, 2, -1, 1, 0 };
    for (int s = 0; s < 9 && ((PlayerAngle & 0xC000) == PlayerAngle); s++) {
        int c = sh[s];
        for (int i = MapThing[2][0] - 1; i >= 0; i--) {

            if ((i & 0xF) != ((n & 0xF) ^ 0xF))
                continue;

            if (i >= 0x60)
                continue;

            // 5 visible at a time

            int x = c * MapThing[4][i + 1];
            int y = MapThing[2][i + 1]; //(MapThing[3][i + 1] >> 8);
            int fr = MapThing[5][i + 1];
            int j = i >> 4;
            //int dis = ((y << 8) / MapThing[3][i + 1]) >> 8;

			y = GetPushDownY(y, x);

            int XIndex = 2;
            int YIndex = 2;
            int PA = PlayerAngle >> 12;
            if ((PlayerAngle & 0xC000) != PlayerAngle) {
                PA = StoredAngle;
            }
            switch (PA) {
                case 0x0:
                    XIndex = (c + (PlayerX >> 4)) & 0x1F;
            		YIndex = (((0xF + PlayerY) >> 4) - j) & 0x1F;
                    break;
                case 0x4:
                    // moving left
                    XIndex = (((0xF + PlayerX) >> 4) - j) & 0x1F;
            		YIndex = ((PlayerY >> 4) - c) & 0x1F;
                    break;
                case 0x8: // correct
                    XIndex = (((0xF + PlayerX) >> 4) - c) & 0x1F;
            		YIndex = (j + (PlayerY >> 4)) & 0x1F;
                    break;
                case 0xC: // correct
                    // moving right
                    XIndex = (j + (PlayerX >> 4)) & 0x1F;
            		YIndex = (c + (PlayerY >> 4)) & 0x1F;
                    break;
            }

            //if ((PlayerAngle & 0xC000) != PlayerAngle)
            //rotate_point(&x, &y, ((StoredAngle << 12) - PlayerAngle + 0xC000) * 3.14159265f / 0x8000, 0, 0xA0);

            int a = 0;
            ///*
            if (Layout[YIndex << 5 | XIndex] == 1)
                a = 5;
            else if (Layout[YIndex << 5 | XIndex] == 2)
                a = 4;
            else if (Layout[YIndex << 5 | XIndex] == 3)
                a = 6;
            else if (Layout[YIndex << 5 | XIndex] == 4)
                a = 13;
            else if (Layout[YIndex << 5 | XIndex] == 5)
                a = 7;
            else
                continue;
            //*/

            ///*
            G->DrawSprite(Objects,
                Objects->Animations[a].Frames[fr].X,
                Objects->Animations[a].Frames[fr].Y,
                Objects->Animations[a].Frames[fr].W,
                Objects->Animations[a].Frames[fr].H,
                x + App->WIDTH / 2,
                y,
                0,
                IE_NOFLIP,
                -Objects->Animations[a].Frames[fr].W / 2,
                Objects->Animations[a].Frames[fr].OffY);
            //*/
        }
    }


    for (int i = 0; i < MapThing[3][0]; i++) {
        //G->DrawRectangle(2 + i * 2, 2, 2, (MapThing[3][i + 1] >> 5), 0);
    }


	char poop[40];
    sprintf(poop, "Direction: %d", Direction);
    G->DrawText(4, App->HEIGHT - 45 + 4, poop, 0x000000);
    G->DrawText(3, App->HEIGHT - 45 + 3, poop, 0xFFFFFF);

    sprintf(poop, "Player X: %X", PlayerX);
    G->DrawText(4, App->HEIGHT - 45 + 14, poop, 0x000000);
	G->DrawText(3, App->HEIGHT - 45 + 13, poop, 0xFFFFFF);

	sprintf(poop, "Player Y: %X", PlayerY);
	G->DrawText(4, App->HEIGHT - 45 + 24, poop, 0x000000);
	G->DrawText(3, App->HEIGHT - 45 + 23, poop, 0xFFFFFF);

	sprintf(poop, "Column: %d", columnIDX);
	G->DrawText(4, App->HEIGHT - 45 + 34, poop, 0x000000);
	G->DrawText(3, App->HEIGHT - 45 + 33, poop, 0xFFFFFF);

    int mx, my;
    mx = App->Input->MouseX;
    my = App->Input->MouseY;
    sprintf(poop, "%d,%d", mx, my);
    G->DrawText(mx + 1, my + 1, poop, 0x000000);
	G->DrawText(mx, my, poop, 0xFFFFFF);

    if (App->Input->MousePressed) {
        dots[dotFrame][columnIDX + 4].push_back(pair<int,int>{ mx, my });
    }

    sprintf(poop, "%d", columnIDX);
    for (int i = 0; i < dots[dotFrame][columnIDX + 4].size(); i++) {
        G->DrawText(dots[dotFrame][columnIDX + 4][i].first, dots[dotFrame][columnIDX + 4][i].second, poop, 0xFFFFFF);
        G->DrawRectangle(dots[dotFrame][columnIDX + 4][i].first - 2, dots[dotFrame][columnIDX + 4][i].second - 2, 4, 4, 0);
    }
    if (App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED]) {
        columnIDX--;
        if (columnIDX < -4)
            columnIDX = 4;
    }
    if (App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED]) {
        columnIDX++;
        if (columnIDX > 4)
            columnIDX = -4;
    }
    if (App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED]) {
        dotFrame++;
        if (dotFrame > 31)
            dotFrame = 31;
    }
    if (App->Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED]) {
        dotFrame--;
        if (dotFrame < 0)
            dotFrame = 0;
    }
    if (App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED]) {
        dots[dotFrame][columnIDX + 4].pop_back();
    }

    if (App->Input->GetControllerInput(0)[IInput::I_PAUSE_PRESSED]) {
        for (int d = 0; d < dotFrame; d++) {
            int sz = 0;
            for (int c = 0; c < 9; c++) {
                sz += dots[d][c].size() * 2;
            }

            printf("int DotFrame_%d[%d] = int[%d] {\n", d, sz, sz);
            for (int c = 0; c < 9; c++) {
                printf("    // %d\n", c);
                for (int i = 0; i < dots[d][c].size(); i++) {
                    printf("    %d, %d,\n", dots[d][c][i].first, dots[d][c][i].second);
                }
            }
            printf("};\n");
        }
    }

    // Player
    G->DrawAlpha = 0x80;
    G->DrawSprite(GlobeSpin,
        GlobeSpin->Animations[1].Frames[0].X,
        GlobeSpin->Animations[1].Frames[0].Y,
        GlobeSpin->Animations[1].Frames[0].W,
        GlobeSpin->Animations[1].Frames[0].H,
        App->WIDTH / 2,
        0xA0,
        0,
        IE_NOFLIP,
        GlobeSpin->Animations[1].Frames[0].OffX,
        GlobeSpin->Animations[1].Frames[0].OffY);
    G->DrawAlpha = 0xFF;

    G->DrawSprite(Players,
        Players->Animations[0].Frames[0].X,
        Players->Animations[0].Frames[0].Y,
        Players->Animations[0].Frames[0].W,
        Players->Animations[0].Frames[0].H,
        App->WIDTH / 2,
        0xAA,
        0,
        IE_NOFLIP,
        Players->Animations[0].Frames[0].OffX,
        Players->Animations[0].Frames[0].OffY);

    ///*

    // Blue Sphere Count
    G->DrawSprite(Objects,
        Objects->Animations[0].Frames[0].X,
        Objects->Animations[0].Frames[0].Y,
        Objects->Animations[0].Frames[0].W,
        Objects->Animations[0].Frames[0].H,
        App->WIDTH / 2,
        13,
        0,
        IE_NOFLIP,
        -Objects->Animations[0].Frames[0].W - 64,
        Objects->Animations[0].Frames[0].OffY);

    // Number
    int nn;
    n = BallCount;
    for (int i = 2; i >= 0; i--) {
        nn = n % 10;
        G->DrawSprite(Objects,
            Objects->Animations[1].Frames[nn].X,
            Objects->Animations[1].Frames[nn].Y,
            Objects->Animations[1].Frames[nn].W,
            Objects->Animations[1].Frames[nn].H,
            App->WIDTH / 2 - 136 + 16 * i,
            17,
            0,
            IE_NOFLIP,
            0,
            Objects->Animations[1].Frames[nn].OffY);

        n /= 10;
    }

    // Ring Count
    G->DrawSprite(Objects,
        Objects->Animations[0].Frames[1].X,
        Objects->Animations[0].Frames[1].Y,
        Objects->Animations[0].Frames[1].W,
        Objects->Animations[0].Frames[1].H,
        App->WIDTH / 2,
        13,
        0,
        IE_NOFLIP,
        64,
        Objects->Animations[0].Frames[1].OffY);

    // Number
    for (int i = 0; i < 3; i++) {
        G->DrawSprite(Objects,
            Objects->Animations[1].Frames[0].X,
            Objects->Animations[1].Frames[0].Y,
            Objects->Animations[1].Frames[0].W,
            Objects->Animations[1].Frames[0].H,
            App->WIDTH / 2 + 88 + 16 * i,
            17,
            0,
            IE_NOFLIP,
            0,
            Objects->Animations[1].Frames[1].OffY);
    }

    //*/
}
