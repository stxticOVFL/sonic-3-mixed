#include <Utils/Standard.h>
#include <Engine/IGenesis.hh>
#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Game/Sound.h>
#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Player.h>

void Object::Create() {
    X = InitialX;
    Y = InitialY;
    VisW = W;
    VisH = H;
    Active = true;
}

void Object::DebugCreate() {
    Create();
}

void Object::Update() {
    MoveSprite();
    Animate();
}

void Object::UpdateSubType() {

}

void Object::OnPush(int PlayerID, int HitFrom) {
	if (((Scene->Players[PlayerID]->WallLeft && Scene->Players[PlayerID]->InputLeft) ||
		(Scene->Players[PlayerID]->Action == ActionType::Spindash && Scene->Players[PlayerID]->DisplayFlip < 0)) && HitFrom == CollideSide::RIGHT && (HitFrom & (int)PushableSide)) {
		// if (X <= InitialX - PushMaxLeft) return;

		X = SubX >> 16;
		SubX -= Scene->Players[PlayerID]->PushSpeed;

		Scene->Players[PlayerID]->X = X + W / 2 + Scene->Players[PlayerID]->W / 2 - 2;
	}

	if (((Scene->Players[PlayerID]->WallRight && Scene->Players[PlayerID]->InputRight) ||
		(Scene->Players[PlayerID]->Action == ActionType::Spindash && Scene->Players[PlayerID]->DisplayFlip > 0)) && HitFrom == CollideSide::LEFT && (HitFrom & (int)PushableSide)) {
		// if (X >= InitialX + PushMaxRight) return;

		X = SubX >> 16;
		SubX += Scene->Players[PlayerID]->PushSpeed;

		Scene->Players[PlayerID]->X = X - W / 2 - Scene->Players[PlayerID]->W / 2 + 2;
	}
}

uint8_t Object::GetSubTypeIncrement() {
	return 1;
}

uint8_t Object::GetSubTypeMax() {
	return 1;
}

void Object::Animate() {
    if (!AutoAnimate) return;
    if (!Sprite) return;
	if (CurrentAnimation < 0) return;

	//SDL_assert(CurrentAnimation < Sprite->Animations.size());

	if (Sprite->Animations.size() > CurrentAnimation)
	{
		if (AnimationFrame == -2)
			AnimationFrame = Sprite->Animations[CurrentAnimation].Frames[Frame].Duration;

		if (AnimationFrame > 0) {
			AnimationFrame -= Sprite->Animations[CurrentAnimation].AnimationSpeed;
			if (AnimationFrame <= 0) {
				Frame++;
				if (Frame >= Sprite->Animations[CurrentAnimation].FrameCount) {
					Frame = Sprite->Animations[CurrentAnimation].FrameToLoop;
					OnAnimationFinish();
				}
				AnimationFrame = Sprite->Animations[CurrentAnimation].Frames[Frame].Duration;
			}
		}
	}
}

void Object::AnimationProgress(int16_t animationData[]) {
	--Timer;
	if (Timer < 0)
	{
		++AnimationFrame;
		int OldAnimationFrame = AnimationFrame;
		int16_t dataAnimationFrame = animationData[AnimationFrame + 1];
		if (dataAnimationFrame < 0)
		{
			AnimationFrame = 0;
			//App->Print(0, "Object: dataAnimationFrame in AnimationProgress is: %d", dataAnimationFrame);
			switch (dataAnimationFrame) {
				// Each switch represents a case of a function from a base address of 0x084430, (0x084434, 0x084438, 0x08443c)
				// All of which are 4 bytes apart. 
				// Of course we don't use these addresses but it's a recreation on how the ASM worked.
				case -4:  // FC - AnimateRaw_Restart
					Frame = animationData[1];
					Timer = animationData[0];
					break;
				case -8:  // F8 - AnimateRaw_Jump
					//animationData += animationData[OldAnimationFrame + 2];
					//objA0.value30 = animationData;
					break;
				case -12:  // F4 - AnimateRaw_CustomCode
					Timer = 0;
					// TODO: Add a condition branch function? It's in the ASM but unsure if we even need it.
					break;
				default:
					break;
			}
		}
		else
		{
			Timer = animationData[0];
			Frame = dataAnimationFrame;
		}
	}
}

int Object::OnLeaveScreen() {
	if (isDebugModeObject && !isHeldDebugObject) {
		Active = false;
	}
	return 0; 
}

int16_t Object::DelayedAnimationProgress(int16_t animationData[]) {
	int16_t retValue = 0;

	Timer -= 1;
	if (Timer < 0) {
		int NewAnimationFrame = AnimationFrame += 2;
		AnimationFrame = NewAnimationFrame;
		int16_t dataAnimationFrame = animationData[NewAnimationFrame];

		if (dataAnimationFrame < 0) {
			AnimationFrame = 0;

			switch (dataAnimationFrame) {
				case -4: // FC - AnimateRawNoSSTMultiDelay_Restart
					Frame = animationData[0];
					Timer = animationData[1];
					retValue = 1;
					break;
				case -8: // F8 - AnimateRawNoSSTMultiDelay_Jump
					//animationData += animationData[AnimationFrame + 1];
					//objA0.value30 = animationData;
					break;
				case -12: // F4 - AnimateRawNoSSTMultiDelay_CustomCode
					retValue = -1;
					break;
				default:
					break;
			}
		} else {
			Frame = dataAnimationFrame;
			Timer = animationData[NewAnimationFrame + 1];
			retValue = 1;
		}
		//App->Print(0, "Object::DelayedAnimationProgress: %d, %d, %d", dataAnimationFrame, Frame, AnimationFrame);
	} else {
		retValue = 0;
	}
	return retValue;
}

int16_t Object::DelayedAnimationProgress(int16_t animationData[], ISprite::Animation Animation) {
	int16_t retValue = 0;

	Timer -= 1;
	if (Timer < 0) {
		int NewAnimationFrame = AnimationFrame += 2;
		AnimationFrame = NewAnimationFrame;
		int16_t dataAnimationFrame = animationData[NewAnimationFrame];

		if (dataAnimationFrame < 0) {
			AnimationFrame = 0;

			switch (dataAnimationFrame) {
				case -4: // FC - AnimateRawNoSSTMultiDelay_Restart
					Frame = animationData[0] % Animation.FrameCount;
					Timer = animationData[1];
					retValue = 1;
					break;
				case -8: // F8 - AnimateRawNoSSTMultiDelay_Jump
					//animationData += animationData[AnimationFrame + 1];
					//objA0.value30 = animationData;
					break;
				case -12: // F4 - AnimateRawNoSSTMultiDelay_CustomCode
					retValue = -1;
					break;
				default:
					break;
			}
		} else {
			Frame = dataAnimationFrame % Animation.FrameCount;
			Timer = animationData[NewAnimationFrame + 1];
			retValue = 1;
		}
		//App->Print(0, "Object::DelayedAnimationProgress: %d, %d, %d", dataAnimationFrame, Frame, AnimationFrame);
	} else {
		retValue = 0;
	}
	return retValue;
}

void Object::OnAnimationFinish() {

}

Object* Object::GetObjectParent() {
    Object *host = (Object *)Parent;
    if (host == NULL) {
        return NULL;
    }
    
    return host;
}

bool Object::IsParentFloatingPlatform() {
    Object *host = (Object *)Parent;
    if (host == NULL) {
        return false;
    }
    
    return host->IsFloatingPlatform;
}

void Object::Render(int CamX, int CamY) {
    if (CurrentAnimation == -1) return;
    if (Frame < 0) return;
    if (!Visible) return;

	if (DrawCollisions) {
		G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
	} else {
		G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, Rotation, FlipX | FlipY << 1);
	}
}

void Object::MoveSprite() {
    YSpeed += Gravity;
    SubX += XSpeed << 8;
    SubY += YSpeed << 8;
}

void Object::MoveWithParent() {
    Object *host = (Object *)Parent;
    if (host == NULL) {
        return;
    }
    
    X = host->X;
    Y = host->Y;
}

int Object::Swing_UpAndDown() {
    // MaxAccel is the maximum acceleration before "swinging"
    int NewYSpeed = YSpeed; // New Velocity
    bool HasChanged = 0; // If there was a change

    // Add upward acceleration
    if (SwingDirection == 0) {
		NewYSpeed -= Acceleration;
        if (NewYSpeed > -MaxAccel) {
            YSpeed = NewYSpeed;
            return HasChanged;
        }
        SwingDirection = 1;
        HasChanged = 1;
    }
    // Add downward acceleration
    NewYSpeed += Acceleration;
    if (NewYSpeed < MaxAccel) {
        YSpeed = NewYSpeed;
        if (HasChanged) {
            SwingCounter--;
            if (SwingCounter == -1) {
                SwingCounter = -2;
                OnSwingFinish();
            }
        }
        return HasChanged;
    }
    NewYSpeed -= Acceleration;
    SwingDirection = 0;
    HasChanged = 1;

    YSpeed = NewYSpeed;
    if (HasChanged) { 
        SwingCounter--;
        if (SwingCounter == -1) {
            SwingCounter = -2;
            OnSwingFinish();
        }
    }
    return HasChanged;
}

void Enemy::Create() {
    Object::Create();
    Scene->AddSelfToRegistry(this, "Enemies");
};

void Enemy::CheckDistanceToPlayers() {
	// Outputs:
	//  - Enemy::ClosetPlayer: Pointer to closest player to the enemy.
	//  - Enemy::PlayerRelativeXDirection: Relative position-x of the player: 0 = left, 1 = right
	//  - Enemy::PlayerRelativeYDirection: Relative position-y of the player: 0 = above, 1 = below
	//  - Enemy::PlayerXDistance: Distance-x to closest player (abs value)
	//  - Enemy::PlayerYDistance: Distance-y to closest player (abs value)
    
    IPlayer *CurrentClosetPlayer = 0;
    
    bool playerRelXDirection = 0;
    bool playerRelYDirection = 0;
    int16_t playerXDistance = 0;
    int16_t playerYDistance = 0;
    
    bool otherRelXDirection = 0;
    bool otherRelYDirection = 0;
    int16_t otherXDistance = 0;
    int16_t otherYDistance = 0;
    
    if (Scene->PlayerCount == 1) {
        CurrentClosetPlayer = Scene->Player;
        int16_t playerXDiff = X - Scene->Player->EZX;
        int16_t playerYDiff = Y - Scene->Player->EZX;
        
        playerRelXDirection = (playerXDiff < 0) ? 1 : 0;
        playerRelYDirection = (playerYDiff < 0) ? 1 : 0;
        playerXDistance = std::abs(playerXDiff);
        playerYDistance = std::abs(playerYDiff);
    } else if (Scene->PlayerCount >= 2) {
        CurrentClosetPlayer = Scene->Player;
        
        int16_t playerXDiff = X - Scene->Player->EZX;
        int16_t playerYDiff = Y - Scene->Player->EZX;
        
        playerRelXDirection = (playerXDiff < 0) ? 1 : 0;
        playerRelYDirection = (playerYDiff < 0) ? 1 : 0; 
        
        playerXDistance = std::abs(playerXDiff);
        playerYDistance = std::abs(playerYDiff);
        
        // We cycle through every player in the game. The closet is chosen.
        for (int i = 0; i < Scene->PlayerCount; i++) {
            IPlayer *otherPlayer = Scene->Players[i];
            
            int16_t otherPlayerXDiff = X - otherPlayer->EZX;
            int16_t otherPlayerYDiff = Y - otherPlayer->EZY;
            
            otherRelXDirection = (otherPlayerXDiff < 0) ? 1 : 0;
            otherRelYDirection = (otherPlayerYDiff < 0) ? 1 : 0;
            
            otherXDistance = std::abs(otherPlayerXDiff);
            otherYDistance = std::abs(otherPlayerYDiff);
            
            if (otherXDistance < playerXDistance) {
                CurrentClosetPlayer = otherPlayer;
                playerXDiff = otherPlayerXDiff;
                playerYDiff = otherPlayerYDiff;
                playerRelXDirection = otherRelXDirection;
                playerRelYDirection = otherRelYDirection;
                playerXDistance = otherXDistance;
                playerYDistance = otherYDistance;
            }
        }
    }
    
    ClosetPlayer = CurrentClosetPlayer;
    PlayerRelativeXDirection = playerRelXDirection;
    PlayerRelativeYDirection = playerRelYDirection;
    PlayerXDistance = playerXDistance;
    PlayerYDistance = playerYDistance;
};

void Enemy::MoveTowardsTargetPosition(IPlayer *Player, int16_t maxSpeed, int16_t speed) {
	int16_t oldSpeed = speed;
    bool dontApplySpeed = 0;
    
	if (X == Player->EZX) {
		dontApplySpeed = true;
	} else {
		dontApplySpeed = false;
		if (X > Player->EZX) {
			speed = -speed;
        }

		int16_t newSpeed = XSpeed + speed;
		if (newSpeed >= -maxSpeed && newSpeed <= maxSpeed) {
			XSpeed = newSpeed;
		}
	}

	if (Y != Player->EZY) {
		if (Y >= Player->EZY) {
			oldSpeed = -oldSpeed;
        }

		int16_t newSpeed = YSpeed + oldSpeed;
		if (newSpeed >= -maxSpeed && newSpeed <= maxSpeed) {
			YSpeed = newSpeed;
		}
		return;
	}

	if (dontApplySpeed != false) {
		XSpeed = 0;
		YSpeed = 0;
	}
}

int Enemy::OnHit() {
	if (Parent != NULL && IsBodyExtension) {
		Enemy *parent = (Enemy *)Parent;
		return parent->OnHit();
	}
    HitCount--;
    if (HitCount <= 0)
        return OnDeath();
    return 0;
};

int Enemy::OnDeath() {
    Scene->AddAnimal(X, Y, false, false, 0, 0, true);
    Scene->AddExplosion(4, false, X, Y);
    Sound::Play(Sound::SFX_DESTROY);
    Active = false;
    return 1;
}

Enemy* Enemy::GetEnemyParent() {
    Enemy *host = (Enemy *)Parent;
    if (host == NULL) {
        return NULL;
    }
    
    return host;
}

void Solid::Create() {
    Object::Create();
    Scene->AddSelfToRegistry(this, "Solid");
};

bool operator==(const CollideSide& left, const int& right) {
    return (int)left == right;
}
bool operator==(const int& left, const CollideSide& right) {
    return left == (int)right;
}
bool operator!=(const CollideSide& left, const int& right) {
    return (int)left != right;
}
bool operator!=(const int& left, const CollideSide& right) {
    return left != (int)right;
}
