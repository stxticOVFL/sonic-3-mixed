#if INTERFACE
#include <Game/LevelScene.h>

class Level_BonusStage : public LevelScene {
public:
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/AIZ.h>
#include <Game/Levels/HCZ.h>
#include <Game/Levels/MGZ.h>
#include <Game/Levels/CNZ.h>
#include <Game/Levels/ICZ.h>
#include <Game/Levels/LBZ.h>
#include <Game/Levels/MHZ.h>
#include <Game/Levels/FBZ.h>
#include <Game/Levels/SOZ.h>
#include <Game/Levels/LRZ.h>
#include <Game/Levels/HPZ.h>
#include <Game/Levels/SSZ.h>
#include <Game/Levels/DEZ.h>
#include <Game/Levels/TDZ.h>

#include <Game/Scenes/MainMenu.h>

#include <Game/SaveGame.h>

#include <Game/Levels/BonusStage.h>

PUBLIC Level_BonusStage::Level_BonusStage(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 0xFF;
    Act = act;

	if (SaveGame::CurrentMode >= 1)
	{
		if (Act == 1) {
			Str_TileConfigBin = "Mixed/Stages/ItemBall/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/ItemBall/Scene.bin";
			Str_TileSprite = "Mixed/Stages/ItemBall/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/ItemBall/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/ItemBall/Stageconfig.bin";
			sprintf(LevelName, "ITEMBALL BONUS");
			sprintf(LevelNameDiscord, "ItemBall Bonus");
		}
		else if (Act == 2) {
			Str_TileConfigBin = "Mixed/Stages/Pachinko/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/Pachinko/Scene.bin";
			Str_TileSprite = "Mixed/Stages/Pachinko/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/Pachinko/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/Pachinko/Stageconfig.bin";
			sprintf(LevelName, "PACHINKO BONUS");
			sprintf(LevelNameDiscord, "Pachinko Bonus");
		}
		else {
			Str_TileConfigBin = "Mixed/Stages/Slots/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/Slots/Scene.bin";
			Str_TileSprite = "Mixed/Stages/Slots/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/Slots/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/Slots/Stageconfig.bin";
			sprintf(LevelName, "SLOTS BONUS");
			sprintf(LevelNameDiscord, "Slots Bonus");
		}
	}
	else
	{
		if (Act == 1) {
			Str_TileConfigBin = "Classic/Stages/ItemBall/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/ItemBall/Scene.bin";
			Str_TileSprite = "Classic/Stages/ItemBall/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/ItemBall/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/ItemBall/Stageconfig.bin";
			sprintf(LevelName, "ITEMBALL BONUS");
			sprintf(LevelNameDiscord, "ItemBall Bonus");
		}
		else if (Act == 2) {
			Str_TileConfigBin = "Classic/Stages/Pachinko/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/Pachinko/Scene.bin";
			Str_TileSprite = "Classic/Stages/Pachinko/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/Pachinko/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/Pachinko/Stageconfig.bin";
			sprintf(LevelName, "PACHINKO BONUS");
			sprintf(LevelNameDiscord, "Pachinko Bonus");
		}
		else {
			Str_TileConfigBin = "Classic/Stages/Slots/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/Slots/Scene.bin";
			Str_TileSprite = "Classic/Stages/Slots/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/Slots/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/Slots/Stageconfig.bin";
			sprintf(LevelName, "Slots Bonus");
			sprintf(LevelNameDiscord, "SLOTS BONUS");
		}
	}

}

PUBLIC void Level_BonusStage::LoadZoneSpecificSprites() {
	if (!KnuxSprite[0]) {
		if (SaveGame::CurrentMode >= 1)
		{
			KnuxSprite[0] = new ISprite("PlayersMixed/Knux1.gif", App);
			KnuxSprite[1] = new ISprite("PlayersMixed/Knux2.gif", App);
			KnuxSprite[2] = new ISprite("PlayersMixed/Knux3.gif", App);
			KnuxSprite[3] = new ISprite("PlayersMixed/KnuxCutsceneAIZ.gif", App);
			KnuxSprite[4] = new ISprite("PlayersMixed/KnuxCutsceneHPZ.gif", App);

			KnuxSprite[0]->LoadAnimation("PlayersMixed/Knux.bin");
		}
		else
		{
			KnuxSprite[0] = new ISprite("PlayersClassic/Knux1.gif", App);
			KnuxSprite[1] = new ISprite("PlayersClassic/Knux2.gif", App);
			KnuxSprite[2] = new ISprite("PlayersClassic/Knux3.gif", App);
			KnuxSprite[3] = new ISprite("PlayersClassic/KnuxCutsceneAIZ.gif", App);
			KnuxSprite[4] = new ISprite("PlayersClassic/KnuxCutsceneHPZ.gif", App);

			KnuxSprite[0]->LoadAnimation("PlayersClassic/Knux.bin");
		}
        KnuxSprite[1]->LinkAnimation(KnuxSprite[0]->Animations);
        KnuxSprite[2]->LinkAnimation(KnuxSprite[0]->Animations);
        KnuxSprite[3]->LinkAnimation(KnuxSprite[0]->Animations);
        KnuxSprite[4]->LinkAnimation(KnuxSprite[0]->Animations);
    }
}

PUBLIC void Level_BonusStage::Init() {
	LevelScene::Init();

	if (Act == 1) {
		if (SaveGame::CurrentMode >= 1)
		{
			PlayMusic("Mixed/Music/ItemBall.ogg", 0, -1);
		}
		else
		{
			PlayMusic("Classic/Music/ItemBall.ogg", 0, -1);
		}
	}
	if (Act == 2) {
		if (SaveGame::CurrentMode >= 1)
		{
			PlayMusic("Mixed/Music/Pachinko.ogg", 0, -1);
		}
		else
		{
			PlayMusic("Classic/Music/Pachinko.ogg", 0, -1);
		}
	}
	else {
		if (SaveGame::CurrentMode >= 1)
		{
			PlayMusic("Mixed/Music/Slots.ogg", 0, -1);
		}
		else
		{
			PlayMusic("Classic/Music/Slots.ogg", 0, -1);
		}
	}
}

PUBLIC void Level_BonusStage::RestartStage(bool doActTransition, bool drawBackground) {
	App->Audio->ClearMusic();
	App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
	
	LevelScene::RestartStage(doActTransition, drawBackground);


    if (Act == 1) {

    }
}

PUBLIC void Level_BonusStage::EarlyUpdate() {
	if (Player)
	{
		//Yeet the player out if they're out of bounds
		Layer layer = Data->Layers[FindLayer("FG Low")];
		//is the player on the map?
		if (Player->Y > (layer.Height * 16) || Player->Y < 0 || Player->X >(layer.Width * 16) || Player->X < 0)
		{
			FadeAction = FadeActionType::CUSTOM_FADE_ACTION;
			FadeTimerMax = 30;
		}
	}

    LevelScene::EarlyUpdate();
}
PUBLIC void Level_BonusStage::Subupdate() {
    LevelScene::Subupdate();
}

PUBLIC void Level_BonusStage::HandleCamera() {
    LevelScene::HandleCamera();
}

PUBLIC void Level_BonusStage::DoCustomFadeAction() {
	if (ZoneID >= 0x100) {
		int Acto = ZoneID & 0xF;
		switch (SaveGame::CurrentZoneID) {
		case 0:
			App->NextScene = new Level_AIZ(App, G, Acto);
			break;
		case 1:
			App->NextScene = new Level_HCZ(App, G, Acto);
			break;
		case 2:
			App->NextScene = new Level_MGZ(App, G, Acto);
			break;
		case 3:
			App->NextScene = new Level_CNZ(App, G, Acto);
			break;
		case 4:
			App->NextScene = new Level_ICZ(App, G, Acto);
			break;
		case 5:
			App->NextScene = new Level_LBZ(App, G, Acto);
			break;
		case 6:
			App->NextScene = new Level_MHZ(App, G, Acto);
			break;
		case 7:
			App->NextScene = new Level_FBZ(App, G, Acto);
			break;
		case 8:
			App->NextScene = new Level_SOZ(App, G, Acto);
			break;
		case 9:
			App->NextScene = new Level_LRZ(App, G, Acto);
			break;
		case 10:
			App->NextScene = new Level_HPZ(App, G, Acto);
			break;
		case 11:
			App->NextScene = new Level_SSZ(App, G, Acto);
			break;
		case 12:
			App->NextScene = new Level_DEZ(App, G, Acto);
			break;
		case 13: //dont know why this would ever happen but lets put it here anyway
			App->NextScene = new Level_TDZ(App, G, Acto);
			break;
		default:
			App->NextScene = new Scene_MainMenu(App, G);
		}
		return;
	}

	App->NextScene = new Scene_MainMenu(App, G);
}

PUBLIC void Level_BonusStage::RenderEverything() {
	// TODO: Optimize

	G->DrawRectangle(0, 0, App->WIDTH, App->HEIGHT, BackgroundColor);
	G->WaterPaletteStartLine = VisualWaterLevel - CameraY;

	int highlightedTile = -1;

	Layer layer;
	int fullFlip;
	int s, siT, x, y;
	int tile, flipX, flipY, baseX, baseY, wheree;
	int index, TileBaseX, TileBaseY;
	// int EndTileBaseX, EndTileBaseY;

	//Lazy but works
	TileSprite->SetTransparentColorIndex(0);

	Uint16 BlankTile = 0x3FFF;

	for (int l = 0; l < Data->layerCount; l++) {
		y = 0;

		layer = Data->Layers[l];

		// Draw Tiles
		if (layer.Visible) {
			G->DoDeform = true;
			memcpy(G->Deform, layer.Deform, App->HEIGHT);
			if (layer.InfoCount > 1) {
				int buf = 0;
				for (s = 0; s < layer.ScrollIndexCount; s++) {
					index = layer.ScrollIndexes[s].Index;

					int heightSize, tilindx, tilindy, tilindpos, word, fBX;
					for (siT = 0; siT < layer.ScrollIndexes[s].Size; siT += heightSize) {
						heightSize = 16;
						if (heightSize > layer.ScrollIndexes[s].Size - siT)
							heightSize = layer.ScrollIndexes[s].Size - siT;
						if (heightSize > ((y + siT + 0x10) & ~0xF) - (y + siT)) // Rounded-up
							heightSize = ((y + siT + 0x10) & ~0xF) - (y + siT);

						if (layer.UseDeltaCameraX)
							TileBaseX = (CameraDeltaX * layer.Info[index].RelativeX + layer.Info[index].ConstantX * Frame) >> 8;
						else
							TileBaseX = (CameraX * layer.Info[index].RelativeX + layer.Info[index].ConstantX * Frame) >> 8;

						TileBaseY = y + siT;
						if (layer.UseDeltaCameraY)
							TileBaseY -= (CameraDeltaY * layer.RelativeY + layer.ConstantY * Frame) >> 8;
						else
							TileBaseY -= (CameraY * layer.RelativeY + layer.ConstantY * Frame) >> 8;

						TileBaseX -= layer.OffsetX;
						TileBaseY -= layer.OffsetY;

						int bufVal = 0;
						if (TileBaseY + heightSize > 0 && TileBaseY < App->HEIGHT) {
							bufVal = layer.Width * 16;
							fBX = (((-TileBaseX) % bufVal + bufVal) % bufVal);

							for (x = (TileBaseX >> 4) - 1; x < 2 + ((TileBaseX + App->WIDTH) >> 4); x++) {
								tilindy = ((y + siT) >> 4);
								tilindy = (tilindy % layer.Height + layer.Height) % layer.Height; // so it loops
								tilindx = ((x % layer.Width + layer.Width) % layer.Width);
								tilindpos = tilindx + (tilindy)* layer.Width;

								baseX = (x << 4) - TileBaseX;
								baseY = TileBaseY;

								word = layer.Tiles[tilindpos];
								fullFlip = (word >> 10) & 3;
								tile = word & 0x3FF;

								if (tile != BlankTile) {
									int anID = Data->IsAnims[tile] & 0xFF;

									if (anID != 0xFF) {
										G->DrawSprite(AnimTileSprite, Data->IsAnims[tile] >> 8, Data->animatedTileFrames[anID], baseX + 8, baseY + 8, 0, fullFlip);
									}
									else {
										// tilindx + buf * layer.Width
										if (layer.ScrollIndexes[0].TileBuffers && layer.ScrollIndexes[0].TileBuffers[buf] > 0) {
											if (bufVal != 0)
												G->DrawSpriteListBuffer(TileSprite,
													layer.ScrollIndexes[0].TileBuffers[buf], layer.Width,
													fBX + 8, baseY + heightSize / 2);
											G->DrawSpriteListBuffer(TileSprite,
												layer.ScrollIndexes[0].TileBuffers[buf], layer.Width,
												fBX + 8 - bufVal, baseY + heightSize / 2);
											// G->DrawSpriteListBuffer(TileSprite,
											//     layer.ScrollIndexes[0].TileBuffers[buf], layer.Width,
											//     fBX + 8 + bufVal, baseY + heightSize / 2);

											// G->DrawSpriteBuffered(TileSprite,
											//     layer.ScrollIndexes[0].TileBuffers[buf], // bufVal,
											//     // baseX + 8, baseY + heightSize / 2, 0, bufVal);//fullFlip);
											//     TileBaseX + 8, baseY + heightSize / 2, 0, bufVal);//fullFlip);

											bufVal = 0;
										}
										else {
											flipY = ((fullFlip >> 1) & 1);

											wheree = (y + siT) & 0xF;
											if (flipY)
												wheree = 0x10 - wheree - heightSize;

											if (TileSprite->Width > 16)
												G->DrawSprite(TileSprite, ((tile & 0x1F) << 4), wheree + ((tile >> 5) << 4), 16, heightSize, baseX + 8, baseY + heightSize / 2, 0, fullFlip, -8, -heightSize / 2 - (heightSize & flipY));
											else
												G->DrawSprite(TileSprite, 0, wheree + (tile << 4), 16, heightSize, baseX + 8, baseY + heightSize / 2, 0, fullFlip, -8, -heightSize / 2 - (heightSize & flipY));
										}
									}
								}
							}
						}

						buf++;
					}
					y += layer.ScrollIndexes[s].Size;
				}
			}
			else {
				if (layer.Info[0].Behaviour == 1) {
					if (ManiaLevel)
						G->DoDeform = true;
				}

				if (layer.UseDeltaCameraX)
					TileBaseX = (CameraDeltaX * layer.Info[0].RelativeX + layer.Info[0].ConstantX * Frame) >> 8;
				else
					TileBaseX = (CameraX * layer.Info[0].RelativeX + layer.Info[0].ConstantX * Frame) >> 8;

				if (layer.UseDeltaCameraY)
					TileBaseY = (CameraDeltaY * layer.RelativeY + layer.ConstantY * Frame) >> 8;
				else
					TileBaseY = (CameraY * layer.RelativeY + layer.ConstantY * Frame) >> 8;

				TileBaseX -= layer.OffsetX;
				TileBaseY -= layer.OffsetY;

				// EndTileBaseX = 2 + ((TileBaseX + App->WIDTH) >> 4);
				// EndTileBaseY = 2 + ((TileBaseY + App->HEIGHT) >> 4);

				//int lWid = layer.Width;

				// int j;
				// int bufVal;
				int tBX = (TileBaseX >> 4) - 1;
				int tBW = 3 + (App->WIDTH >> 4);
				int tBH = 2 + (App->HEIGHT >> 4);
				int ix = tBX,
					iy = (TileBaseY >> 4),
					fx = 0,
					fy = 0,
					// th = (TileBaseY >> 4) + tBH,
					tw = tBX + tBW;
				int fullSize = tBW * tBH;
				int anID;
				for (int w = 0; w < fullSize; w++) {
					fx = ix;
					fy = iy;
					if (layer.Flags & 0x2) {
						if (fx < 0) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
						if (fx >= layer.Width) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
					}
					if (layer.Flags & 0x4) {
						if (fy < 0) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
						if (fy >= layer.Height) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
					}

					while (fx < 0) fx += layer.Width;
					while (fx >= layer.Width) fx -= layer.Width;

					while (fy < 0) fy += layer.Height;
					while (fy >= layer.Height) fy -= layer.Height;

					baseX = (ix << 4) - TileBaseX;
					baseY = (iy << 4) - TileBaseY + layer.TileOffsetY[fx];

					tile = layer.Tiles[fx + fy * layer.Width];

					bool ColFlipX = ((tile >> 10) & 1) == 1;
					bool ColFlipY = ((tile >> 11) & 1) == 1;
					bool SolidTopA = ((tile >> 12) & 1) == 1;
					bool SolidLrbA = ((tile >> 13) & 1) == 1;
					bool SolidTopB = ((tile >> 14) & 1) == 1;
					bool SolidLrbB = ((tile >> 15) & 1) == 1;

					int colTypeA = ((tile >> 12) & 3);
					int colTypeB = ((tile >> 14) & 3);

					fullFlip = (tile >> 10) & 3;
					tile = tile & 0x3FF;

					if (tile != BlankTile) {
						anID = Data->IsAnims[tile] & 0xFF;
						if (anID != 0xFF) {
							G->DrawSprite(AnimTileSprite, Data->IsAnims[tile] >> 8, Data->animatedTileFrames[anID], baseX + 8, baseY + 8, 0, fullFlip);
						}
						else {
							G->DrawSprite(TileSprite, 0, tile, baseX + 8, baseY + 8, 0, fullFlip);
						}

						if (ViewTileCollision) {
							for (int c = 0; c < 16; c++) {
								int eex = c;
								if (ColFlipX) {
									eex = 15 - c;
								}

								int h1 = Data->tiles1[tile].Collision[c];
								int h2 = Data->tiles2[tile].Collision[c];

								if (BlankTile == 0x3FF && (Data->tiles1[tile].IsCeiling || Data->tiles2[tile].IsCeiling)) {
									h1 = 15 - h1;
									h2 = 15 - h2;
								}

								// Yellow - Tiles that are solid from the top. Used for platforms.
								// Red - Tiles that are solid from the bottom and sides. Usually for walls and ceilings.
								// White - Tiles that are solid all over. Usually for the ground.

								if (Player->Layer == 0 && (colTypeA & 1)) {
									//uint32_t col = colTypeB == 3 ? 0 : colTypeB == 2 ? 0xFFFF00 : 0xFFFFFF;
									uint32_t col = (SolidTopA && SolidLrbA) ? 0xFFFFFF : (SolidLrbA && !SolidTopA) ? 0xFF0000 : 0xFFFF00;

									if (Data->tiles1[tile].HasCollision[c]) {
										if (Data->tiles1[tile].IsCeiling ^ ColFlipY) {
											G->DrawRectangle(baseX + eex, baseY, 1, 16 - h1, col);
										}
										else {
											G->DrawRectangle(baseX + eex, baseY + h1, 1, 16 - h1, col);
										}
									}
								}
								else if (Player->Layer == 1 && (colTypeB & 1)) {
									if (Data->tiles2[tile].HasCollision[c]) {
										uint32_t col = (SolidTopB && SolidLrbB) ? 0xFFFFFF : (SolidLrbB && !SolidTopB) ? 0xFF0000 : 0xFFFF00;

										if (Data->tiles2[tile].IsCeiling ^ ColFlipY) {
											G->DrawRectangle(baseX + eex, baseY, 1, 16 - h2, col);
										}
										else {
											G->DrawRectangle(baseX + eex, baseY + h2, 1, 16 - h2, col);
										}
									}
								}
							}

							int mx = App->Input->MouseX;
							int my = App->Input->MouseY;
							if (mx >= baseX && my >= baseY && mx < baseX + 16 && my < baseY + 16) {
							}
						}
					}

					ix++;
					if (ix >= tw) {
						ix = tBX;
						iy++;
					}
				}

				if (layer.Info[0].Behaviour) {
					if (ManiaLevel)
						G->DoDeform = false;
				}
			}
		}


		G->DoDeform = DeformObjects;

		// Rendering objects
		for (int i = 0; i < ObjectCount; i++) {
			Object* obj = Objects[i];
			if (obj == NULL) continue;

			if (obj->Active && obj->OnScreen) {
				if (l == Data->CameraLayer + obj->VisualLayer) {
					obj->DrawCollisions = App->viewObjectCollision;
					if ((obj->BinIndex >= 0 && obj->BinIndex < SpriteBinMapIDs.size()) && SpriteBinMapIDs.at(obj->BinIndex) != obj->Sprite) {
						obj->Sprite = SpriteBinMapIDs.at(obj->BinIndex);
					}
					obj->Render(CameraX, CameraY);
				}
			}
		}

		// Rendering rings
		if (l == Data->CameraLayer) {
			RenderRings();
		}

		// Rendering temporary sprites
		for (vector<Object*>::iterator it = TempObjects.begin(); it != TempObjects.end(); ++it) {
			if ((*it)->Active) {
				if (l == Data->CameraLayer + (*it)->VisualLayer) {
					(*it)->Render(CameraX, CameraY);
				}
			}
		}

		// Rendering temporary tile sprites
		for (vector<Object*>::iterator it = TempObjectTiles.begin(); it != TempObjectTiles.end(); ++it) {
			if ((*it)->Active) {
				if (l == Data->CameraLayer + (*it)->VisualLayer) {
					(*it)->Render(CameraX, CameraY);
				}
			}
		}

		G->DoDeform = DeformPlayer;

		// Rendering players
		for (int p = PlayerCount - 1; p >= 0; p--) {
			if (l == Data->CameraLayer + Players[p]->VisualLayer)
				Players[p]->Render(CameraX, CameraY);
		}

		// Rendering above foreground
		/*
		if (l == Data->layerCount - 1)
			RenderAboveForeground();
		//*/
	}

	G->DoDeform = false;

	RenderHUD();

	if (!ViewPlayerUpdateStats && !maxLayer) {
		int Y = 0;
		size_t strSize1, strSize2, strSizeFinal;
		char tempStr1_X[128], tempStr1_Y[128], tempStr2_X[128], tempStr2_Y[128];

		sprintf(tempStr1_X, "%04X", (Player->EZX < 0) ? -Player->EZX : Player->EZX);
		sprintf(tempStr1_Y, "%04X", (Player->EZY < 0) ? -Player->EZY : Player->EZY);
		strSize1 = strlen(tempStr1_X) + strlen(tempStr1_Y);

		sprintf(tempStr2_X, "%04X", CameraX < 0 ? -CameraX : CameraX);
		sprintf(tempStr2_Y, "%04X", CameraY < 0 ? -CameraY : CameraY);
		strSize2 = strlen(tempStr2_X) + strlen(tempStr2_Y);

		strSizeFinal = std::max(strSize1, strSize2);

		if (Player->EZY >= WaterLevel) {
			G->DrawRectangle(59, 10, 8 * strSizeFinal, 16, TileSprite->GetPaletteAlt(31));
		}
		else {
			G->DrawRectangle(59, 10, 8 * strSizeFinal, 16, TileSprite->GetPalette(31));
		}

		G->DrawTextShadow(59, Y + 10, tempStr1_X, (Player->EZX < 0) ? 0xFF0000 : 0xFFFFFF);
		G->DrawTextShadow(59 + (8 * strlen(tempStr1_X)), Y + 10, tempStr1_Y, (Player->EZY < 0) ? 0xFF0000 : 0xFFFFFF);
		Y += 8;
		G->DrawTextShadow(59, Y + 10, tempStr2_X, (CameraX < 0) ? 0xFF0000 : 0xFFFFFF);
		G->DrawTextShadow(59 + (8 * strlen(tempStr2_X)), Y + 10, tempStr2_Y, (CameraY < 0) ? 0xFF0000 : 0xFFFFFF);
	}

	if (ViewPalettes) {
		char palettetitle[16];
		sprintf(palettetitle, "Normal");
		G->DrawTextShadow(App->WIDTH - 132, App->HEIGHT - 74, palettetitle, 0xFFFFFF);

		sprintf(palettetitle, "Alt");
		G->DrawTextShadow(App->WIDTH - 64, App->HEIGHT - 74, palettetitle, 0xFFFFFF);

		for (int i = 0; i < 256; i++) {
			G->DrawRectangle(App->WIDTH - 132 + ((i & 0xF) << 2), App->HEIGHT - 64 + ((i >> 4) << 2), 4, 4, TileSprite->GetPalette(i));

			G->DrawRectangle(App->WIDTH - 64 + ((i & 0xF) << 2), App->HEIGHT - 64 + ((i >> 4) << 2), 4, 4, TileSprite->GetPaletteAlt(i));
		}

		for (int i = 0; i < 256; i++) {
			G->DrawRectangle(App->WIDTH - 132 + ((i & 0xF) << 2), App->HEIGHT - 64 + ((i >> 4) << 2) - 96, 4, 4, Player->Sprites[0]->GetPalette(i));

			G->DrawRectangle(App->WIDTH - 64 + ((i & 0xF) << 2), App->HEIGHT - 64 + ((i >> 4) << 2) - 96, 4, 4, Player->Sprites[0]->GetPaletteAlt(i));
		}
	}

	if (highlightedTile > 0) {
		int which[4];

		which[0] = Data->tiles1[highlightedTile].Config[0];
		which[1] = Data->tiles1[highlightedTile].Config[1];
		which[2] = Data->tiles1[highlightedTile].Config[2];
		which[3] = Data->tiles1[highlightedTile].Config[3];

		if (which[1] >= 0xC0 && which[1] > 0xD0) which[1] = 0xC0;

		char tex[7];
		sprintf(tex, "%02X %02X %02X %02X",
			which[0],
			which[1],
			which[2],
			which[3]);
		G->DrawTextShadow(64, 64, tex, (Data->tiles1[highlightedTile].IsCeiling ? 0xF2D141 : 0xFFFFFF) - (flipY ? 0xD100 : 0));
	}

	//RenderResults();

	int filTemp = G->GetFilter();
	G->SetFilter(0);
	//RenderTitleCard();
	G->SetFilter(filTemp);
}