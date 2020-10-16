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

#include "SysPlayerMovement.h"

using namespace Libero;

void EmptyScene::Load()
{
	LoadSystem<SysPlayerMovement>();

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
	pObj->GetTransform()->Rotate({-3.14f / 2.f, 0.f, 0.f });



	GameObject* pCamera = NewGameObject();
	pCamera->SetName("Camera");
	CameraComponent* pCam = pCamera->AddComponent<CameraComponent>();
	pCam->SetActive(true);
	pCamera->GetTransform()->SetPosition({ 0.f, 0.f, -60.f });
	pCamera->AddComponent<InputComponent>();

	GameObject* pSky = NewGameObject();
	pSky->SetName("Sky");
	SkyDomeRenderComponent* pComp = pSky->AddComponent<SkyDomeRenderComponent>();
	
	//pComp->SetBaseColor({ 0.0f, 0.5f, 0.8f });
	//pComp->SetApexColor({ 0.0f, 0.05f, 0.6f});

	
	pComp->SetBaseColor({0.5f, 0.5f, 0.5f});
	pComp->SetApexColor({ 1.0f / 218.0f, 1.0f / 165.0f, 1.0f / 32.0f });
}
