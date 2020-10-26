#include "EmptyScene.h"
#include "Libero/Entities/GameObject.h"
#include "Libero/Components/MeshRenderComponent.h"
#include "Libero/Components/CameraComponent.h"
#include "Libero/Components/TransformComponent.h"
#include "Libero/Components/MeshFilterComponent.h"
#include "Libero/Content/ContentMaster.h"
#include "Libero/Graphics/Mesh.h"
#include "Libero/Graphics/Materials/MaterialMaster.h"
#include "Libero/Graphics/Materials/MatDefaultShaded.h"
#include "Libero/Components/SkyDomeRenderComponent.h"
#include "Libero/Components/InputComponent.h"
#include "Libero/Math/Random.h"

#include "SysPlayerMovement.h"
#include "GeometryPrefabs.h"

using namespace Libero;

void EmptyScene::Load()
{
	LoadSystem<SysPlayerMovement>();

	SetupCamera();
	SetupSkybox();
	//SetupVehicle();
	//SetupBoxes();
	SetupCharacter();
	SetupGround();
}

void EmptyScene::SetupSkybox()
{
	GameObject* pSky = NewGameObject();
	pSky->SetName("Sky");
	SkyDomeRenderComponent* pComp = pSky->AddComponent<SkyDomeRenderComponent>();
	pComp->SetBaseColor({ 0.0f, 0.5f, 0.8f });
	pComp->SetApexColor({ 0.0f, 0.05f, 0.6f });
}	

void EmptyScene::SetupVehicle()
{
	MatDefaultShaded* pMat = MaterialLocator::Get()->CreateMaterial<MatDefaultShaded>("DefaultShaded_0");
	pMat->SetTexColor("../Resources/Assets/Textures/vehicle_diffuse.png");
	pMat->SetTexNormals("../Resources/Assets/Textures/vehicle_normal.png");
	pMat->SetDefaultColor({ 0.5f, 0.5f, 0.5f });

	GameObject* pObj = NewGameObject();
	pObj->SetName("Object");

	MeshRenderComponent* pRender = pObj->AddComponent<MeshRenderComponent>();
	pRender->SetMaterial(pMat);
	Mesh* pMesh = ContentLocator::Get()->Load<Mesh>("../Resources/Assets/Meshes/vehicle.fbx");
	pObj->AddComponent<MeshFilterComponent>(pMesh);
	pObj->GetTransform()->Rotate({ -3.14f / 2.f, 0.f, 0.f });
}

void EmptyScene::SetupBoxes()
{
	GameObject* pBox = BoxPrefab::Create(this);
	pBox->GetTransform()->SetPosition({});

	MatDefaultShaded* pMaterial = MaterialLocator::Get()->CreateMaterial<MatDefaultShaded>("Random");
	pMaterial->SetDefaultColor({ Libero::Random::ColorRand() });
	pBox->GetComponent<MeshRenderComponent>()->SetMaterial(pMaterial);

	GameObject* pCylinder = CylinderPrefab::Create(this);
	pCylinder->GetTransform()->SetPosition({5.0f, 0.0f, 0.0f});

	GameObject* pCone = ConePrefab::Create(this);
	pCone->GetTransform()->SetPosition({-5.0f, 0.0f, 0.0f});

	GameObject* pPlane = PlanePrefab::Create(this);
	pPlane->GetTransform()->SetScale({ 10.0f });
}

void EmptyScene::SetupCharacter()
{
	GameObject* pChar = NewGameObject();
	pChar->SetName("Ralts");
	pChar->AddComponent<MeshFilterComponent>(ContentLocator::Get()->Load<Mesh>("../Resources/Assets/Meshes/Ralts/Ralts.fbx"));
	MeshRenderComponent* pMeshRender = pChar->AddComponent<MeshRenderComponent>();
	MatDefaultShaded* pCharMat = MaterialLocator::Get()->CreateMaterial<MatDefaultShaded>("RaltsMaterial");
	pCharMat->SetTexColor("../Resources/Assets/Meshes/Ralts/images/pm0280_00_Body1.png");
	pMeshRender->SetMaterial(pCharMat);
	pChar->GetTransform()->Translate({ 0.0f, 4.0f, 0.0f });
	pChar->GetTransform()->Rotate({ -3.14f / 2.f, -3.14f, 0.0f });
}

void EmptyScene::SetupCamera()
{
	GameObject* pCamera = NewGameObject();
	pCamera->SetName("Camera");
	CameraComponent* pCam = pCamera->AddComponent<CameraComponent>();
	pCam->SetFOV(60.0f);
	pCam->SetActive(true);
	pCamera->GetTransform()->SetPosition({ 0.f, 30.f, -30.f });
	pCamera->GetTransform()->Rotate({ 3.14f / 4.0f, 0.0f, 0.0f });
	pCamera->AddComponent<InputComponent>();
}

void EmptyScene::SetupGround()
{
	GameObject* pPlane = PlanePrefab::Create(this);
	pPlane->GetTransform()->SetScale({ 10.0f });
}
