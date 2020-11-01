#pragma once
#include <Libero/Scene/Scene.h>

class EmptyScene final : public Libero::Scene
{
public:
	void Load() override;

private:
	void SetupSkybox();
	void SetupVehicle();
	void SetupBoxes();
	void SetupCharacter();
	void SetupCamera();
	void SetupGround();
};

