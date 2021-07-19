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

#include "SoundManager.h"
#include "ShaderManager.h"
#include "SimpleShader.h"

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
#include "EnemySpawner.h"

#include "Boss.h"
#include "Boss2.h"
#include "BossState.h"

#include "FireBall.h"

#include "Chest.h"
#include "Item.h"
#include "Boom.h"

#include "PGaze.h"
#include "EGaze.h"
#include "UnitHp.h"
#include "Font.h"

#include "IEffect.h"
#include "Effect.h"
#include "CollisionEffect.h"
#include "Spectrum.h"

#include "Ranking.h"

#include "ResultScreen.h"
#include "MainBackground.h"
#include "Background.h"
#include "RankPage.h"
#include "HelpPage.h"
#include "EndPage.h"
#include "Fade.h"

#include "Scene.h"
#include "MainScene.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene3.h"
#include "RankingScene.h"
extern Scene* nowScene;

#include "Game.h"
