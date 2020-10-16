#pragma once
#include "Libero/ECS/Core/Component.h"

#include <vector>

namespace Libero
{
	class SkyDomeRenderComponent final : public Component<SkyDomeRenderComponent>
	{
		using DomeVertex = Vector3f;
	public:
		SkyDomeRenderComponent(const std::string& effectFile = "../Resources/Core/Effects/SkyDomeShader.fx");
		~SkyDomeRenderComponent();

		void UpdateEffectVariables();
		void Initialize();

		void SetBaseColor(const ColorRGB& col);
		void SetApexColor(const ColorRGB& col);
		ColorRGB GetBaseColor() const;
		ColorRGB GetApexColor() const;

		void Render();

	private:
		class SkyDome* m_pSkyDome = nullptr;

		void InitMeshData();
		void InitBuffer();

		void InitEffect();

		std::vector<DomeVertex> m_VertexBuffer;
		std::vector<uint32_t> m_IndexBuffer;
		struct ID3D11Buffer* m_pVertexBuffer = nullptr;
		struct ID3D11Buffer* m_pIndexBuffer = nullptr;

		std::string m_EffectPath;
		struct ID3DX11Effect* m_pEffect = nullptr;
		struct ID3DX11EffectTechnique* m_pTechnique = nullptr;
		struct ID3D11InputLayout* m_pInputLayout = nullptr;

		struct ID3DX11EffectVectorVariable* m_pCameraPosition = nullptr;
		Vector3f m_CameraPosition;

		struct ID3DX11EffectVectorVariable* m_pApexColor = nullptr;
		struct ID3DX11EffectVectorVariable* m_pBaseColor = nullptr;
		struct ID3DX11EffectMatrixVariable* m_pWVP = nullptr;

		bool m_IsInitialized = false;
	};
}


