#pragma once

struct ID3DX11EffectTechnique;
struct ID3D11InputLayout;
struct ID3DX11Effect;

namespace Libero
{
	class TransformComponent;
	class IMaterial
	{
	public:
		struct DXData
		{
			ID3DX11Effect* m_pEffect = nullptr;
			ID3DX11EffectTechnique* m_pTechnique = nullptr;
			ID3D11InputLayout* m_pInputLayout = nullptr;

			~DXData()
			{
				SafeRelease(m_pEffect);
				SafeRelease(m_pInputLayout);
			}
		};

		IMaterial(const std::string& effectFile, const std::string& techName = "DefaultTechnique");
		virtual ~IMaterial() = default;

		void Initialize();
		const DXData& GetDX() const;

		virtual void UpdateEffectVariables(TransformComponent* pTransform) = 0;

	protected:
		void LoadEffect();
		virtual void LoadEffectVariables() = 0;

		DXData m_DXData{};
		std::string m_EffectPath;
		std::string m_TechniqueName;
	};
}

