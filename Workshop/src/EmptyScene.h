#pragma once
#include <Libero/Scene/Scene.h>

class EmptyScene final : public Libero::Scene
{
public:
	EmptyScene() = default;

	void Load() override;

private:
	void SetupSkybox();
	void SetupVehicle();
	void SetupBoxes();
	void SetupCamera();
};

