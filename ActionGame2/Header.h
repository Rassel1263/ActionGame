#pragma once

#define IntEnum(p) static_cast<int>(p)
#define PluseEnum(a, b, c) static_cast<a>(IntEnum(b) + IntEnum(c))

#include <map>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>
#include <functional>
#include <algorithm>
#include <limits>

#include "Singleton.h"

#include "Texture.h"
#include "Sprite.h"

#include "Camera.h"
#include "Input.h"

#include "ShaderManager.h"
#include "ColorShader.h"

#include "Collider.h"
#include "Object.h"

#include "CState.h"

#include "Unit.h"
#include "Player.h"
#include "PlayerState.h"

#include "CEnemy.h"
#include "Enemy1.h"
#include "EnemyState.h"

#include "PlayerBullet.h"

#include "Effect.h"
#include "AfterImage.h"

#include "Map.h"

#include "Scene.h"
extern Scene* nowScene;
#include "GameScene.h"

#include "Game.h"