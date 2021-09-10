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

#include "AttackCollider.h"

#include "EnemyUI.h"
#include "PlayerUI.h"

#include "Unit.h"
#include "Player.h"
#include "PlayerState.h"

#include "Range.h"

#include "CEnemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "EnemyState.h"

#include "Boss1.h"

#include "Bullet.h"

#include "Effect.h"
#include "BossIntro.h"
#include "AfterImage.h"
#include "Spectrum.h"
#include "SkillDirecting.h"
#include "Warning.h"
#include "Mp.h"

#include "Map.h"

#include "Scene.h"
extern Scene* nowScene;
#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene3.h"

#include "Game.h"