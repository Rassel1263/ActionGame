#pragma once

#define SAFE_RELEASE(p) { if (p) { p->Release(); p = NULL; }}
#define SAFE_DELETE(p) { if (p) {delete p; p = NULL; } }

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

#include "Collider.h"
#include "Object.h"

#include "Player.h"

#include "Scene.h"
extern Scene* nowScene;
#include "GameScene.h"

#include "Game.h"