#include "Standard.h"
#include "Scene_Z_MSZ.h"

#include "Application.h"
#include "Resources.h"

#include "Engine/IO/IResources.h"
#include "Engine/IO/IStream.h"
#include "Engine/ITexture.h"
#include "Engine/IGraphics.h"
#include "Engine/ICrypt.h"
#include "Engine/IE.h"

#include "S3/LevelScene.h"
#include "S3/Object.h"
#include "S3/Player.h"
#include "S3/ObjectNames.h"

#include <zlib.h>
#include <time.h>

#define Z_MID 0
#define Z_FRONT -1
#define Z_BACK 1
#define T(name) App->Textures[name]
#define S(name) App->Sprites[name]

std::unordered_map<std::string, const char*> ObjectHashes;

int frame = 0;
int sceneIn = -2;

/*
Layer     layers[10];
TileCfg   tiles1[0x400];
TileCfg   tiles2[0x400];
ITexture* tileTex = NULL;
short     layerCount = 0;
int       cameraLayer = 0;
*/

IPlayer* player = NULL;
SceneData* data = new SceneData();

ISprite* buttons = NULL;

PlaneSwitch PlaneSwitchers[113];
int         PlaneSwitchCount = 0;

int FGLayer = 2;

bool CollisionAt(int probeX, int probeY, int layer, int* angle) {
    int tileX = probeX / 16;
    int tileY = probeY / 16;
    //int l = layer;
    for (int l = FGLayer + 1; l >= FGLayer; l--) {
        int tileID = data->layers[l].Tiles[tileX + tileY * data->layers[l].Width];
        if ((tileID & 0x3FF) != 0x3FF) {
            bool tileData1 = ((tileID >> 15) & 1) == 1;
            bool tileData2 = ((tileID >> 14) & 1) == 1;
            bool tileData3 = ((tileID >> 13) & 1) == 1;
            bool tileData4 = ((tileID >> 12) & 1) == 1;

            bool tileDatas[4] = { tileData4, tileData3, tileData2, tileData1 };

            bool flipX = ((tileID >> 10) & 1) == 1;
            bool flipY = ((tileID >> 11) & 1) == 1;

            tileID = tileID & 0x3FF;

            if (!tileDatas[player->Layer * 2] && !tileDatas[player->Layer * 2 + 1])
                continue;

            for (int c = 0; c < 16; c++) {
                int eex = c;
                if (flipX)
                    eex = 15 - c;

                int tX = tileX * 16;
                int tY = tileY * 16;

                unsigned int h1 = data->tiles1[tileID].Collision[c];
                unsigned int h2 = data->tiles2[tileID].Collision[c];

                if (flipY) {
                    h1 = 15 - h1;
                    h2 = 15 - h2;
                }

                int which = 0;
                if (player->AngleMode == 0)
                    which = 0 + flipY * 3;
                if (player->AngleMode == 2)
                    which = 3 - flipY * 3;

                if (player->AngleMode == 1)
                    which = 1 + flipX;
                if (player->AngleMode == 3)
                    which = 2 - flipX;

                if (data->tiles1[tileID].HasCollision[c] && player->Layer == 0) {
                    if (data->tiles1[tileID].IsCeiling ^ flipY) {
                        if (!tileDatas[player->Layer * 2 + 1] && (player->Y + 14 > tY))
                            continue;

                        if (probeX == tX + eex &&
                            probeY >= tY &&
                            probeY <  tY + 1 + h1) {
                            float tempAngle = data->tiles1[tileID].Config[which];
                            tempAngle = tempAngle * -45.f / 32;
                            if (tempAngle != 0) {
                                if (flipX) tempAngle = -tempAngle;
                                if (flipY) tempAngle = 180.f - tempAngle;
                            }
                            if (player->Y < tY)
                                tempAngle = 0;

                            *angle = (int)wrapAngle(tempAngle);

                            return true;
                        }
                    }
                    else {
                        if (!tileDatas[player->Layer * 2 + 1] && (player->Y + 14 > tY + h1))
                            continue;

                        if (probeX == tX + eex &&
                            probeY >= tY + h1 &&
                            probeY <  tY + 16) {
                            float tempAngle = data->tiles1[tileID].Config[which];
                            tempAngle = tempAngle * -45.f / 32;
                            if (tempAngle != 0) {
                                if (flipX) tempAngle = -tempAngle;
                                if (flipY) tempAngle = 180.f - tempAngle;
                            }

                            *angle = (int)wrapAngle(tempAngle);
                            return true;
                        }
                    }
                }
                if (data->tiles2[tileID].HasCollision[c] && player->Layer == 1) {
                    if (data->tiles2[tileID].IsCeiling ^ flipY) {
                        if (!tileDatas[player->Layer * 2 + 1] && (player->Y + 14 > tY))
                            continue;

                        if (probeX == tX + eex &&
                            probeY >= tY &&
                            probeY <  tY + 1 + h2) {
                            float tempAngle = data->tiles2[tileID].Config[which];
                            tempAngle = tempAngle * -45.f / 32;
                            if (tempAngle != 0) {
                                if (flipX) tempAngle = -tempAngle;
                                if (flipY) tempAngle = 180.f - tempAngle;
                            }

                            *angle = (int)wrapAngle(tempAngle);
                            return true;
                        }
                    }
                    else {
                        if (!tileDatas[player->Layer * 2 + 1] && (player->Y + 14 > tY + h2))
                            continue;

                        if (probeX == tX + eex &&
                            probeY >= tY + h2 &&
                            probeY <  tY + 16) {
                            float tempAngle = data->tiles2[tileID].Config[which];
                            tempAngle = tempAngle * -45.f / 32;
                            if (tempAngle != 0) {
                                if (flipX) tempAngle = -tempAngle;
                                if (flipY) tempAngle = 180.f - tempAngle;
                            }

                            *angle = (int)wrapAngle(tempAngle);
                            return true;
                        }
                    }
                }
            }

            //break;
        }
    }
    return false;
}

Scene_MSZ::Scene_MSZ(Application* app, int data1, int data2) {
    App = app;
    G = app->g;

    sceneIn = 40;

    aud_BGM_TitleScreen = newMusic(snd_BGM_TitleScreen_ogg, "snd/BGM_MSZ2.ogg");

    aud_C_ShortBeep = newSound(snd_C_ShortBeep_ogg, "snd/C_ShortBeep.ogg");

    App->Stack->Push("Act 2", aud_BGM_TitleScreen, 0, 0, 0, true, false, false, 179390 / 44100.f);

    //T("Common") = new ITexture(IResources::Load("Sprites/Common/Texture.png"), false);

    //T("Player") = ;

    S("Background") = new ISprite(IResources::Load("Sprites/Common/Title_BG.spr"), T("Common"));
    S("SmallFont") = new ISprite(IResources::Load("Sprites/Common/Font40x2.spr"), T("Common"));

    if (!S("Buttons"))
        S("Buttons") = new ISprite(IResources::Load("Sprites/Common/HUD_Buttons6.spr"), T("Common"));
    buttons = S("Buttons");

    //S("Sonic") = new ISprite(IResources::Load("Sprites/Player/Sonic.spr"), new ITexture(IResources::Load("Sprites/Player/Texture.png"), false));

    S("Sonic") = new ISprite(IResources::Load("Sprites/Player/ManiaSonic.spr"), new ITexture(IResources::Load("Sprites/Player/ManiaSonic.png"), false));
    S("Tails") = new ISprite(IResources::Load("Sprites/Player/ManiaTails.spr"), new ITexture(IResources::Load("Sprites/Player/ManiaTails.png"), false));
    S("Knuckles") = new ISprite(IResources::Load("Sprites/Player/ManiaKnux.spr"), new ITexture(IResources::Load("Sprites/Player/ManiaKnux.png"), false));

    for (int i = 0; i < 554; i++) {
        std::string hash = MD5I(std::string(ObjectNames(i)));
        ObjectHashes[hash] = ObjectNames(i);
    }

    player = new IPlayer();
    player->App = App;
    player->G = G;
    //player->CollisionAt = CollisionAt;
    player->ForegroundLayer = FGLayer;

    srand((unsigned int)time(NULL));

    if (App->input->mouseX < App->renderWidth / 3) {
        player->Sprite = S("Sonic");
        player->Character = CharacterType::Sonic;
    }
    else if (App->input->mouseX < 2 * App->renderWidth / 3) {
        player->Sprite = S("Tails");
        player->Character = CharacterType::Tails;
    }
    else {
        player->Sprite = S("Knuckles");
        player->Character = CharacterType::Knuckles;
    }

    player->Create();


    // Loading TileConfig
    unsigned char TileConfigData[0x1000];
    IResource* TileConfig = IResources::Load("Sprites/MSZ/TileConfig.bin");
    SDL_RWread(TileConfig->RW, TileConfigData, 1, 0x1000);
    IResources::Close(TileConfig);

    IStream tileReader(TileConfigData);
    tileReader.ReadByte4(); // Magic Word

    unsigned char* TileData = tileReader.ReadCompressed();

    // Amount of bytes per Tile Definition
    int maxDataBytes = 0x26;
    // Collision Plane 1
    for (int i = 0; i < 0x400; i++) {
        int n = i * maxDataBytes;

        memcpy(data->tiles1[i].Collision, TileData + n + 0x00, 0x10);
        memcpy(data->tiles1[i].HasCollision, TileData + n + 0x10, 0x10);
        data->tiles1[i].IsCeiling = TileData[n + 0x20];
        memcpy(data->tiles1[i].Config, TileData + n + 0x21, 0x05);
    }
    // Collision Plane 2
    for (int i = 0; i < 0x400; i++) {
        int n = i * maxDataBytes;

        memcpy(data->tiles2[i].Collision, TileData + n + 0x00, 0x10);
        memcpy(data->tiles2[i].HasCollision, TileData + n + 0x10, 0x10);
        data->tiles2[i].IsCeiling = TileData[n + 0x20];
        memcpy(data->tiles2[i].Config, TileData + n + 0x21, 0x05);
    }

    unsigned char SceneBinData[0x20000];
    IResource* SceneBin = IResources::Load("Sprites/MSZ/Scene2.bin");
    size_t size = (size_t)SDL_RWsize(SceneBin->RW);
    SDL_RWread(SceneBin->RW, SceneBinData, size, 1);
    IResources::Close(SceneBin);

    long long unsigned int start = SceneBinData[0x14] + 1 + 4 + 1 + 4 + 4 + 7 + 1;

    data->cameraLayer = SceneBinData[SceneBinData[0x14] + 0x15]; // value is 0x03, possibly 4th layer? (FG_High)

    IStream reader(SceneBinData);
    for (int i = 0; i < start; i++)
        reader.ReadByte();

    data->layerCount = reader.ReadByte();
    for (int i = 0; i < data->layerCount; i++) {
        //char  IgnoredByte =
            reader.ReadByte();
        char* Name = reader.ReadRSDKString();
        if (strcmp(Name, "FG Low") == 0)
            FGLayer = i;

        strcpy(data->layers[i].Name, Name);

        /*
        char  IsScrollingVertical = reader.ReadByte();
        char  UnknownByte2 = reader.ReadByte();
        */
        reader.ReadByte();
        reader.ReadByte();

        int   Width = (int)reader.ReadUInt16();
        int   Height = (int)reader.ReadUInt16();

        /*
        int   UnknownWord1 = (int)reader.ReadUInt16();
        int   UnknownWord2 = (int)reader.ReadUInt16();
        */
        reader.ReadUInt16();
        reader.ReadUInt16();

        data->layers[i].InfoCount = (int)reader.ReadUInt16();

        App->print(0, "Layer %d (%s): Width (%d) Height (%d) Infos (%d)", i, Name, Width, Height, data->layers[i].InfoCount);

        for (int g = 0; g < data->layers[i].InfoCount; g++) {
            data->layers[i].Info[g].X = reader.ReadUInt16();
            data->layers[i].Info[g].Y = reader.ReadUInt16();

            data->layers[i].Info[g].Byte1 = reader.ReadByte();
            data->layers[i].Info[g].Byte2 = reader.ReadByte();

            //App->print(0, " > ScrollInfo %d: Width (%d) Height (%d) %d %d", g, data->layers[i].Info[g].X, data->layers[i].Info[g].Y, data->layers[i].Info[g].Byte1, data->layers[i].Info[g].Byte2);
        }

        // FUN FACT:
        // With all compressed data, we already know the size of the data. (using Width, Height, etc.)

        unsigned char* ScrollIndexes = reader.ReadCompressed();
        if (Height > 0) { // Just in case
            int sc = 0;
            int s_start = 0;
            int value = ScrollIndexes[0];
            int s = 0;
            for (; s < Height * 16; s++) {
                // ScrollingIndex
                int v = ScrollIndexes[s];
                // If we find a different value, cap it off and start anew.
                if (v != value) {
                    data->layers[i].ScrollIndexes[sc] = ScrollingIndex { value, s - s_start };
                    //App->print(0, " - ScrollIndex %d: Index %d Size %d", sc, data->layers[i].ScrollIndexes[sc].Index, data->layers[i].ScrollIndexes[sc].Size);

                    sc++;
                    s_start = s;
                    value = v;
                }
            }
            data->layers[i].ScrollIndexes[sc] = ScrollingIndex { value, s - s_start };
            sc++;

            data->layers[i].ScrollIndexCount = sc;
        }

        unsigned char* Tilesss = reader.ReadCompressed();

        data->layers[i].Width = Width;
        data->layers[i].Height = Height;

        IStream creader(Tilesss);
        for (int y = 0; y < Height; y++) {
            for (int x = 0; x < Width; x++) {
                data->layers[i].Tiles[x + y * Width] = creader.ReadUInt16();
            }
        }
    }

    data->objectDefinitionCount = reader.ReadByte();
    App->print(3, "Object Definition Count %d", data->objectDefinitionCount);
    for (int i = 0; i < data->objectDefinitionCount; i++) {
        char str[16];
        char hashString[33];
        sprintf(hashString, "%s", "");
        for (int n = 0; n < 16; n++) {
            str[n] = reader.ReadByte();
            sprintf(hashString, "%s%02x", hashString, (unsigned char)str[n]);
        }
        //printf("LOG: Object #%d (%s) Hash: %s\n", i, ObjectHashes[std::string(hashString)], hashString);

        int ArgumentCount = reader.ReadByte();
        //printf("LOG: Argument Count: %d\n", ArgumentCount);

        int ArgumentTypes[ArgumentCount];
        ArgumentTypes[0] = 0;

        for (int n = 1; n < ArgumentCount; n++) {
            //App->print(1, "Argument %d", n);

            //printf("IMPORTANT: Argument Hash: ");
            char str2[17];
            for (int n = 0; n < 16; n++) {
                str2[n] = reader.ReadByte();
                //printf("%02X", (unsigned char)str2[n]);
                fflush(stdout);
            }
            //printf("\n");
            fflush(stdout);
            str2[16] = 0;


            int ArgType = reader.ReadByte();
            //App->print(3, "Argument type: %02X", ArgType);
            ArgumentTypes[n] = ArgType;
        }

        int EntityCount = reader.ReadUInt16();
        //App->print(0, "Entity Count: %d", EntityCount);

        if (i == 22) {
            PlaneSwitchCount = 0;
        }

        for (int n = 0; n < EntityCount; n++) {
            /*int SlotID = */reader.ReadUInt16();

            unsigned int X1 = reader.ReadUInt16();
            unsigned int X2 = reader.ReadUInt16();
            unsigned int Y1 = reader.ReadUInt16();
            unsigned int Y2 = reader.ReadUInt16();

            //App->print(1, "Entity %d (%d) %04X %04X, %04X %04X     %d   %d", n, SlotID, X1, X2, Y1, Y2, PlaneSwitchCount, i);
            if (i == 22) {
                PlaneSwitchers[PlaneSwitchCount].X = X2 + (float)X1 / 0x10000;
                PlaneSwitchers[PlaneSwitchCount].Y = Y2 + (float)Y1 / 0x10000;
            }

            for (int a = 1; a < ArgumentCount; a++) {
                //App->print(3, "   Argument Type: %04X", ArgumentTypes[a]);
                int value = 0;
                switch (ArgumentTypes[a]) {
                    case 0x0:
                    case 0x3:
                        value = (unsigned char)reader.ReadByte();//App->print(3, "   Argument Value (Type: %02X): %02X", ArgumentTypes[a], (unsigned char)reader.ReadByte());
                        break;
                    case 0x1:
                    case 0x4:
                        value = (unsigned short)reader.ReadUInt16();//App->print(3, "   Argument Value (Type: %02X): %04X", ArgumentTypes[a], (unsigned short)reader.ReadUInt16());
                        break;
                    case 0x2:
                    case 0x5:
                    case 0x6:
                    case 0x7:
                    case 0xB:
                        value = (unsigned int)reader.ReadUInt32();//App->print(3, "   Argument Value (Type: %02X): %08X", ArgumentTypes[a], (unsigned int)reader.ReadUInt32());
                        break;
                    case 0x8: {
                        int WordCount = reader.ReadUInt16();
                        //App->print(3, "   Argument Value (Type: %02X): %04X", ArgumentTypes[a], WordCount);
                        for (int wc = 0; wc < WordCount; wc++) {
                            reader.ReadUInt16();//App->print(3, "      Value (Type: %02X): %04X", ArgumentTypes[a], (unsigned short)reader.ReadUInt16());
                        }
                    }
                        break;
                    case 0x9:
                        value = (unsigned int)reader.ReadUInt32();
						reader.ReadUInt32();//App->print(3, "   Argument Value (Type: %02X): %08X %08X", ArgumentTypes[a], (unsigned int)reader.ReadUInt32(), (unsigned int)reader.ReadUInt32());
                        break;
                }
                if (i == 22) {
                    if (a == 1) {
                        PlaneSwitchers[PlaneSwitchCount].Flags = value;
                    }
                    else if (a == 2) {
                        PlaneSwitchers[PlaneSwitchCount].Size = value;
                    }
                    else if (a == 3) {
                        PlaneSwitchers[PlaneSwitchCount].Angle = value / 256.f * 360;
                    }
                    else if (a == 4) {
                        PlaneSwitchers[PlaneSwitchCount].OnPath = value == 1;
                    }

                    //App->print(1, "%d", value);
                }
            }

            PlaneSwitchCount++;
        }
    }

    data->tileTex = new ITexture(IResources::Load("Sprites/MSZ/16x16Tiles.png"), false);
}

float viewX = 0;
float viewY = 0;

void Scene_MSZ::Update() {
    if (App->input->jump2Pressed[0])
        player->Layer = 1 - player->Layer;
    if (App->input->jump3Pressed[0])
        player->VisualLayer = 1 - player->VisualLayer;

    if (App->realPaused) return;

    frame++;
    frame = (frame) % 4800000;

    /*
    if (App->input->left[0])
        viewX -= 16;
    if (App->input->right[0])
        viewX += 16;
    if (App->input->up[0])
        viewY -= 16;
    if (App->input->down[0])
        viewY += 16;
    */

    for (int i = 0; i < PlaneSwitchCount; i++) {
        int Size = 16 * PlaneSwitchers[i].Size + 16;
        if (player->X + 11 >= PlaneSwitchers[i].X - 2 &&
            player->X - 11 <  PlaneSwitchers[i].X + 2 &&
            player->Y + 11 >= PlaneSwitchers[i].Y - Size / 2 &&
            player->Y - 11 <  PlaneSwitchers[i].Y + Size / 2) {
            if (PlaneSwitchers[i].OnPath) {
                if (player->Ground) {
                    if (player->Speed * player->Cos[(int)PlaneSwitchers[i].Angle % 360] < 0) {
                        player->Layer = (PlaneSwitchers[i].Flags >> 3) & 1;
                        player->VisualLayer = (PlaneSwitchers[i].Flags >> 2) & 1;
                    }
                    else {
                        player->Layer = (PlaneSwitchers[i].Flags >> 1) & 1;
                        player->VisualLayer = (PlaneSwitchers[i].Flags >> 0) & 1;
                    }
                }
            }
            else {
                if (player->Speed * player->Cos[(int)PlaneSwitchers[i].Angle % 360] > 0) {
                    player->Layer = (PlaneSwitchers[i].Flags >> 3) & 1;
                    player->VisualLayer = (PlaneSwitchers[i].Flags >> 2) & 1;
                }
                else {
                    player->Layer = (PlaneSwitchers[i].Flags >> 1) & 1;
                    player->VisualLayer = (PlaneSwitchers[i].Flags >> 0) & 1;
                }
            }
        }
    }

    player->Update();

    viewX = (int)(player->X + player->CameraX) - App->renderWidth / 2;
    viewY = (int)(player->Y + player->CameraY) - App->renderHeight / 2;

    if (viewX < 0)
        viewX = 0;
    if (viewY < 0)
        viewY = 0;

    if (viewX > data->layers[data->cameraLayer].Width * 16 - App->renderWidth)
        viewX = data->layers[data->cameraLayer].Width * 16 - App->renderWidth;
    if (viewY > data->layers[data->cameraLayer].Height * 16 - App->renderHeight)
        viewY = data->layers[data->cameraLayer].Height * 16 - App->renderHeight;

    if (sceneIn > -2) {
        sceneIn--;
    }
}
void Scene_MSZ::Render() {
    if (sceneIn > -2) {
        G->SetFade(sceneIn / 40.f);
    }

    player->Render((int)viewX, (int)viewY);

    for (int l = 0; l < data->layerCount; l++) {
        if ((true)) { // if MSZ
            if (l == 4)
                continue;
        }
        else {
            if (l == 1 || l == 2)
                continue;
        }


        int y = 0;
        for (int s = 0; s < data->layers[l].ScrollIndexCount; s++) {
            int index = data->layers[l].ScrollIndexes[s].Index;
            float mult = data->layers[l].Info[index].X / 256.f;
            float multY = 1.f;
            float offX = data->layers[l].Info[index].Y / 256.f * frame;

            if (l < 2)
                //multY = 2 / 32.f;
                multY = 5 / 32.f;

            for (int siT = 0; siT < data->layers[l].ScrollIndexes[s].Size; siT += 16) {
                int tileHeight = 16;
                if (siT + tileHeight > data->layers[l].ScrollIndexes[s].Size)
                    tileHeight = data->layers[l].ScrollIndexes[s].Size - siT;

                if (y + siT - viewY * multY + tileHeight > 0 &&
                    y + siT - viewY * multY < App->renderHeight) {
                    for (int x = (viewX * mult + offX) / 16; x < 1 + (viewX * mult + offX) / 16 + App->renderWidth / 16; x++) {
                        int tile = data->layers[l].Tiles[(x % data->layers[l].Width) + ((y + siT) / 16) * data->layers[l].Width];
                        int flipX = ((tile >> 10) & 1) == 1 ? -1 : 1;
                        int flipY = ((tile >> 11) & 1) == 1 ? -1 : 1;
                        tile = tile & 0x3FF;

                        if (tile != 0x3FF)
                            G->DrawTexture(data->tileTex, (tile % 32) * 16, (tile / 32) * 16 + (y + siT) % 16, 16, tileHeight, x * 16 - (viewX * mult + offX), y + siT - viewY * multY, Z_FRONT * l * 0.1f, 16 * flipX, tileHeight * flipY);
                    }
                }
            }
            y += data->layers[l].ScrollIndexes[s].Size;
        }
    }

    if (!App->Mobile) {
        IColor color = IColor(1.f, 0.f, 0.f, 0.5f);

        int ang = -1;
        if (CollisionAt((int)App->input->mouseX + (int)viewX, (int)App->input->mouseY + (int)viewY, player->Layer + 2, &ang)) {
            color = IColor(0.f, 1.f, 1.f, 0.5f);

            char sup[60];
            sprintf(sup, "%d", ang);
            DrawSmallFont(S("SmallFont"), sup, (int)App->input->mouseX + 8, (int)App->input->mouseY - 12, 0);
        }

        G->DrawRectangle((int)App->input->mouseX, (int)App->input->mouseY - 8, Z_FRONT * 4.5, 1, 17, color);
        G->DrawRectangle((int)App->input->mouseX - 8, (int)App->input->mouseY, Z_FRONT * 4.5, 17, 1, color);

        char sup[60];
        sprintf(sup, "%d %d", (int)App->input->mouseX + (int)viewX, (int)App->input->mouseY + (int)viewY);
        //DrawSmallFont(S("SmallFont"), sup, (int)App->input->mouseX + 8, (int)App->input->mouseY + 8, 0);

        sprintf(sup, "X %d Y %d ANGLE %d MODE %d GROUND %d FRAME %d", (int)player->X, (int)player->Y, player->Angle, player->AngleMode, player->Ground, (int)player->Frame);
        DrawSmallFont(S("SmallFont"), sup, 8, 225 - 8 - 32, 0);
    }


    if (!App->Mobile) {
        for (int i = 0; i < PlaneSwitchCount; i++) {
            int Size = 16 * PlaneSwitchers[i].Size + 16;
            int Width = 8;
            G->DrawRectangle((int)PlaneSwitchers[i].X - (int)viewX - Width / 2, (int)PlaneSwitchers[i].Y - (int)viewY - Size / 2, Z_FRONT * 0.2f - 0.05f, Width, Size, IColor(0.0f, 1.0f, 1.0f, 1.0f));
        }

        #if 1
        //int l = player->Layer + 2;
        int tileX = ((int)App->input->mouseX + (int)viewX) / 16;
        int tileY = ((int)App->input->mouseY + (int)viewY) / 16;

        for (int l = FGLayer + 1 - player->Layer; l < FGLayer + 1 - player->Layer + 1; l++) {
            int tileID = data->layers[l].Tiles[tileX + tileY * data->layers[l].Width];
            if ((tileID & 0x3FF) != 0x3FF) {
                bool tileData1 = ((tileID >> 15) & 1) == 1;
                bool tileData2 = ((tileID >> 14) & 1) == 1;
                bool tileData3 = ((tileID >> 13) & 1) == 1;
                bool tileData4 = ((tileID >> 12) & 1) == 1;

                bool flipX = ((tileID >> 10) & 1) == 1;
                bool flipY = ((tileID >> 11) & 1) == 1;

                tileID = tileID & 0x3FF;

                if (App->input->mouseDown) {
                    if (App->input->mousePrimary) {
                        char sup[100];
                        sprintf(sup, "%03X %d:%d    %02X %02X %02X %02X %02X     %d %d %d",
                            tileID, tileID % 32, tileID / 32,
                            data->tiles1[tileID].Config[0], data->tiles1[tileID].Config[1], data->tiles1[tileID].Config[2], data->tiles1[tileID].Config[3], data->tiles1[tileID].Config[4],
                            flipX, flipY, data->tiles1[tileID].IsCeiling);
                        DrawSmallFont(S("SmallFont"), sup, 8, 12 + (l - 2) * 32, 0);
                        sprintf(sup, "BITS: %d %d %d %d", tileData1, tileData2, tileData3, tileData4);
                        DrawSmallFont(S("SmallFont"), sup, 8, 28 + (l - 2) * 32, 0);
                    }
                    else {
                        char sup[100];
                        sprintf(sup, "%03X %d:%d    %02X %02X %02X %02X %02X     %d %d %d",
                            tileID, tileID % 32, tileID / 32,
                            data->tiles2[tileID].Config[0], data->tiles2[tileID].Config[1], data->tiles2[tileID].Config[2], data->tiles2[tileID].Config[3], data->tiles2[tileID].Config[4],
                            flipX, flipY, data->tiles2[tileID].IsCeiling);
                        DrawSmallFont(S("SmallFont"), sup, 8, 12 + (l - 2) * 32, 0);
                        sprintf(sup, "BITS: %d %d %d %d", tileData1, tileData2, tileData3, tileData4);
                        DrawSmallFont(S("SmallFont"), sup, 8, 28 + (l - 2) * 32, 0);
                    }
                }
                //*/


                for (int c = 0; c < 16; c++) {
                    int eex = c;
                    if (flipX)
                        eex = 15 - c;

                    int tX = tileX * 16 - (int)viewX;
                    int tY = tileY * 16 - (int)viewY;

                    unsigned int h1 = data->tiles1[tileID].Collision[c];
                    unsigned int h2 = data->tiles2[tileID].Collision[c];

                    if (flipY) {
                        h1 = 15 - h1;
                        h2 = 15 - h2;
                    }

                    if (App->input->mouseDown) {
                        if (App->input->mousePrimary) {
                            if (data->tiles1[tileID].IsCeiling ^ flipY) {
                                if (data->tiles1[tileID].HasCollision[c])
                                    G->DrawRectangle(tX + eex, tY, Z_FRONT * 2.5f, 1, h1, IColor(1.f, 0.f, 0.f, 1.0f));
                            }
                            else {
                                if (data->tiles1[tileID].HasCollision[c])
                                    G->DrawRectangle(tX + eex, tY + h1, Z_FRONT * 2.5f, 1, 16 - h1, IColor(1.f, 0.f, 0.f, 1.0f));
                            }
                        }
                        else {
                            if (data->tiles2[tileID].IsCeiling ^ flipY) {
                                if (data->tiles2[tileID].HasCollision[c])
                                    G->DrawRectangle(tX + eex, tY, Z_FRONT * 2.6f, 1, h2, IColor(0.f, 0.f, 1.f, 1.0f));
                            }
                            else {
                                if (data->tiles2[tileID].HasCollision[c])
                                    G->DrawRectangle(tX + eex, tY + h2, Z_FRONT * 2.6f, 1, 16 - h2, IColor(0.f, 0.f, 1.f, 1.0f));
                            }
                        }
                    }
                }
            }
        }
        #endif
    }

    if (!App->Mobile) {
        char jumper[100];
        sprintf(jumper, "COLLIS LAYER: %s", player->Layer ? "HIGH" : "LOW");
        DrawSmallFont(S("SmallFont"), jumper, 8, 225 - 8 - 16, 0);
        sprintf(jumper, "VISUAL LAYER: %s", player->VisualLayer ? "HIGH" : "LOW");
        DrawSmallFont(S("SmallFont"), jumper, 8, 225 - 8, 0);
    }

    if (App->Mobile)
        App->input->DrawControls(buttons);
}
void Scene_MSZ::Free() {
    FreeAudio();
}






/*

/////////////////////////////////////////////////////
// Code to draw collision of tile under the mouse. //
/////////////////////////////////////////////////////

int tileX = ((int)App->input->mouseX + (int)viewX) / 16;
int tileY = ((int)App->input->mouseY + (int)viewY) / 16;
int l = data->cameraLayer - 1;

int tileID = data->layers[l].Tiles[tileX + tileY * data->layers[l].Width];
if ((tileID & 0x3FF) != 0x3FF) {
    bool flipX = ((tileID >> 10) & 1) == 1;
    bool flipY = ((tileID >> 11) & 1) == 1;

    tileID = tileID & 0x3FF;

    //char sup[20];
    //sprintf(sup, "%d:%d %d %d %d", tileID % 32, tileID / 32, flipX, flipY, data->tiles1[tileID].IsCeiling);
    //DrawSmallFont(S("SmallFont"), sup, (int)App->input->mouseX + 8, (int)App->input->mouseY - 12, 0);


    for (int c = 0; c < 16; c++) {
        int eex = c;
        if (flipX)
            eex = 15 - c;

        int tX = tileX * 16 - (int)viewX;
        int tY = tileY * 16 - (int)viewY;

        unsigned int h1 = data->tiles1[tileID].Collision[c];
        unsigned int h2 = data->tiles2[tileID].Collision[c];

        if (flipY) {
            h1 = 15 - h1;
            h2 = 15 - h2;
        }

        if (data->tiles1[tileID].IsCeiling ^ flipY) {
            if (data->tiles1[tileID].HasCollision[c])
                G->DrawRectangle(tX + eex, tY + 1, Z_FRONT * 2.5f, 1, h1, IColor(1.f, 0.f, 0.f, 1.0f));
        }
        else {
            if (data->tiles1[tileID].HasCollision[c])
                G->DrawRectangle(tX + eex, tY + h1, Z_FRONT * 2.5f, 1, 16 - h1, IColor(1.f, 0.f, 0.f, 1.0f));
        }

        if (data->tiles2[tileID].IsCeiling ^ flipY) {
            if (data->tiles2[tileID].HasCollision[c])
                G->DrawRectangle(tX + eex, tY + 1, Z_FRONT * 2.5f, 1, h2, IColor(0.f, 0.f, 1.f, 1.0f));
        }
        else {
            if (data->tiles2[tileID].HasCollision[c])
                G->DrawRectangle(tX + eex, tY + h2, Z_FRONT * 2.5f, 1, 16 - h2, IColor(0.f, 0.f, 1.f, 1.0f));
        }
    }
}
*/
