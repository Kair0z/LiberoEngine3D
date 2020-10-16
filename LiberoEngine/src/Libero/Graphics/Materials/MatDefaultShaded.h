#pragma once
#include "Libero/Graphics/Materials/Material.h"
#include <string>

struct ID3DX11EffectMatrixVariable;
using DXMatrixVar = ID3DX11EffectMatrixVariable;
struct ID3DX11EffectShaderResourceVariable;
using DXSRVVar = ID3DX11EffectShaderResourceVariable;
struct ID3DX11EffectScalarVariable;
using DXValueVar = ID3DX11EffectScalarVariable;
struct ID3DX11EffectVectorVariable;
using DXVectorVar = ID3DX11EffectVectorVariable;

namespace Libero
{
	class Texture2D;
	class MatDefaultShaded final : public IMaterial
	{
	public:
		MatDefaultShaded() : IMaterial("../Resources/Assets/Effects/LiberoShader.fx"){}
		virtual void LoadEffectVariables() override;
		virtual void UpdateEffectVariables(TransformComponent* pTransform) override;

		bool SetTexColor(const std::string& path);
		bool SetTexNormals(const std::string& path);
		bool SetTexEmmisive(const std::string& path);
		bool SetTexOpacity(const std::string& path);
		void SetAmbient(const ColorRGB& col, float intensity);
		void SetDefaultColor(const ColorRGB& col);

		~MatDefaultShaded();

	private:
		DXMatrixVar* m_pWorld = nullptr;
		DXMatrixVar* m_pWorldViewProjection = nullptr;

		DXVectorVar* m_pColorDefault = nullptr;
		ColorRGB m_ColorDefault = { 1.f, 1.f, 1.f };
		DXSRVVar* m_pTexColor = nullptr;
		Texture2D* m_pTexColorRef = nullptr;
		DXValueVar* m_pUseTexColor = nullptr;
		bool m_UseTexColor = false;

		DXSRVVar* m_pTexNormals = nullptr;
		Texture2D* m_pTexNormalsRef = nullptr;
		DXValueVar* m_pUseTexNormals = nullptr;
		bool m_UseTexNormals = false;

		DXSRVVar* m_pTexOpacity = nullptr;
		Texture2D* m_pTexOpacityRef = nullptr;
		DXValueVar* m_pUseTexOpacity = nullptr;
		bool m_UseTexOpacity = false;
		DXValueVar* m_pOpacityIntensity = nullptr;
		float m_OpacityIntensity = 1.f;

		DXSRVVar* m_pTexEmmisive = nullptr;
		Texture2D* m_pTexEmmisiveRef = nullptr;
		DXValueVar* m_pUseTexEmmisive = nullptr;
		bool m_UseTexEmmisive = false;
		DXValueVar* m_pEmmisiveIntensity = nullptr;
		float m_EmmisiveIntensity = 0.f;

		DXVectorVar* m_pColorAmbient = nullptr;
		ColorRGB m_ColorAmbient = { 0.2f, 0.2f, 0.2f };
		DXValueVar* m_pAmbientIntensity = nullptr;
		float m_AmbientIntensity = 0.f;
	};
}


