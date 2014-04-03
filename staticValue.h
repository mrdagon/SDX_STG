#pragma once
#include "Scene.h"
#include "Menu.h"
#include "EnemyData.h"

namespace SDX
{
	Scene* Scene::sceneNow;
	Menu* Menu::menuNow;
	EnemyData EnemyData::data[(int)EnemyID::MAX];
}