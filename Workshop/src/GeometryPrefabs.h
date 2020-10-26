#pragma once
#include "Libero/Entities/GameObject.h"
#include "Libero/Scene/Scene.h"

struct BoxPrefab
{
	static Libero::GameObject* Create(Libero::Scene* pScene);
};

struct CylinderPrefab
{
	static Libero::GameObject* Create(Libero::Scene* pScene);
};

struct SpherePrefab
{
	static Libero::GameObject* Create(Libero::Scene* pScene);
};

struct PlanePrefab
{
	static Libero::GameObject* Create(Libero::Scene* pScene);
};

struct ConePrefab
{
	static Libero::GameObject* Create(Libero::Scene* pScene);
};
