#include "GeometryPrefabs.h"
#include "Libero/Components/MeshFilterComponent.h"
#include "Libero/Components/MeshRenderComponent.h"
#include "Libero/Graphics/Materials/Materials.h"

#include "Libero/Content/ContentMaster.h"

using namespace Libero;
GameObject* BoxPrefab::Create(Libero::Scene* pScene)
{
	GameObject* pBox = pScene->NewGameObject();
	pBox->SetName("Box");

	pBox->AddComponent<MeshFilterComponent>(MeshFilterComponent(ContentLocator::Get()->Load<Mesh>("../Resources/Core/Meshes/Cube.fbx")));
	MeshRenderComponent* pMeshRenderer = pBox->AddComponent<MeshRenderComponent>();
	pMeshRenderer->SetMaterial(LiberoMaterials::DefaultMaterial());

	return pBox;
}

Libero::GameObject* CylinderPrefab::Create(Libero::Scene* pScene)
{
	GameObject* pCylinder = pScene->NewGameObject();
	pCylinder->SetName("Cylinder");

	pCylinder->AddComponent<MeshFilterComponent>(MeshFilterComponent(ContentLocator::Get()->Load<Mesh>("../Resources/Core/Meshes/Cylinder.fbx")));
	MeshRenderComponent* pMeshRenderer = pCylinder->AddComponent<MeshRenderComponent>();
	pMeshRenderer->SetMaterial(LiberoMaterials::DefaultMaterial());

	return pCylinder;
}

Libero::GameObject* SpherePrefab::Create(Libero::Scene* pScene)
{
	GameObject* pSphere = pScene->NewGameObject();
	pSphere->SetName("Sphere");
	pSphere->AddComponent<MeshFilterComponent>(MeshFilterComponent(ContentLocator::Get()->Load<Mesh>("../Resources/Core/Meshes/Sphere.fbx")));
	MeshRenderComponent* pMeshRenderer = pSphere->AddComponent<MeshRenderComponent>();
	pMeshRenderer->SetMaterial(LiberoMaterials::DefaultMaterial());

	return pSphere;
}

Libero::GameObject* PlanePrefab::Create(Libero::Scene* pScene)
{
	GameObject* pPlane = pScene->NewGameObject();
	pPlane->SetName("Plane");
	pPlane->AddComponent<MeshFilterComponent>(MeshFilterComponent(ContentLocator::Get()->Load<Mesh>("../Resources/Core/Meshes/Plane.fbx")));
	MeshRenderComponent* pMeshRenderer = pPlane->AddComponent<MeshRenderComponent>();
	pMeshRenderer->SetMaterial(LiberoMaterials::DefaultMaterial());

	return pPlane;
}

Libero::GameObject* ConePrefab::Create(Libero::Scene* pScene)
{
	GameObject* pCone = pScene->NewGameObject();
	pCone->SetName("Cone");
	pCone->AddComponent<MeshFilterComponent>(MeshFilterComponent(ContentLocator::Get()->Load<Mesh>("../Resources/Core/Meshes/Cone.fbx")));
	MeshRenderComponent* pMeshRenderer = pCone->AddComponent<MeshRenderComponent>();
	pMeshRenderer->SetMaterial(LiberoMaterials::DefaultMaterial());

	return pCone;
}
