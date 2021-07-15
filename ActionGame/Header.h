#pragma once

#include <iostream>
#include <istream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <queue>
#include <map>

#include "Singleton.h"
#include "Input.h"

#include "Texture.h"
#include "Sprite.h"

#include "Object.h"
#include "Collider.h"

#include "CState.h"

#include "Units.h"
#include "AttackCollider.h"

#include "Player.h"
#include "PlayerState.h"

#include "EnemyRange.h"
#include "Enemy.h"
#include "EnemyState.h"

#include "PGaze.h"
#include "UnitHp.h"

#include "Effect.h"

#include "Background.h"

#include "Scene.h"
#include "GameScene.h"
extern Scene* nowScene;

#include "Game.h"
