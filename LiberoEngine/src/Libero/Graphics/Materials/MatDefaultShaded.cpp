#include "Liber_pch.h"
#include "MatDefaultShaded.h"
#include "Libero/Graphics/CameraMaster.h"
#include "Libero/Components/CameraComponent.h"
#include "Libero/Components/TransformComponent.h"
#include "Libero/Content/ContentMaster.h"
#include "Libero/Graphics/Texture2D.h"

namespace Libero
{
	void MatDefaultShaded::LoadEffectVariables()
	{
		if (!m_pWorld)
			m_pWorld = m_DXData.m_pEffect->GetVariableByName("gWorld")->AsMatrix();

		if (!m_pWorldViewProjection)
			m_pWorldViewProjection = m_DXData.m_pEffect->GetVariableByName("gWVP")->AsMatrix();

		if (!m_pTexColor)
			m_pTexColor = m_DXData.m_pEffect->GetVariableByName("gTexDiffuse")->AsShaderResource();

		if (!m_pTexNormals)
			m_pTexNormals = m_DXData.m_pEffect->GetVariableByName("gTexNormals")->AsShaderResource();

		if (!m_pTexEmmisive)
			m_pTexEmmisive = m_DXData.m_pEffect->GetVariableByName("gTexEmmisive")->AsShaderResource();

		if (!m_pTexOpacity)
			m_pTexOpacity = m_DXData.m_pEffect->GetVariableByName("gTexOpacity")->AsShaderResource();

		if (!m_pUseTexEmmisive)
			m_pUseTexEmmisive = m_DXData.m_pEffect->GetVariableByName("gUseTexEmmisive")->AsScalar();

		if (!m_pUseTexOpacity)
			m_pUseTexOpacity = m_DXData.m_pEffect->GetVariableByName("gUseTexOpacity")->AsScalar();

		if (!m_pUseTexNormals)
			m_pUseTexNormals = m_DXData.m_pEffect->GetVariableByName("gUseTexNormals")->AsScalar();

		if (!m_pUseTexColor)
			m_pUseTexColor = m_DXData.m_pEffect->GetVariableByName("gUseTexDiffuse")->AsScalar();

		if (!m_pColorAmbient)
			m_pColorAmbient = m_DXData.m_pEffect->GetVariableByName("gColorAmbient")->AsVector();

		if (!m_pAmbientIntensity)
			m_pAmbientIntensity = m_DXData.m_pEffect->GetVariableByName("gAmbientIntensity")->AsScalar();

		if (!m_pOpacityIntensity)
			m_pOpacityIntensity = m_DXData.m_pEffect->GetVariableByName("gOpacityIntensity")->AsScalar();

		if (!m_pEmmisiveIntensity)
			m_pEmmisiveIntensity = m_DXData.m_pEffect->GetVariableByName("gEmmisiveIntensity")->AsScalar();

		if (!m_pColorDefault)
			m_pColorDefault = m_DXData.m_pEffect->GetVariableByName("gColorDiffuse")->AsVector();
	}

	void MatDefaultShaded::UpdateEffectVariables(TransformComponent* pTransform)
	{
		const CameraComponent& cam = (*CameraMasterLocator::Get()->GetActiveCamera());
		
		XMMATRIX world = pTransform->GetWorldMatrix();
		XMMATRIX ViewProj = cam.GetViewProjection();
		m_pWorld->SetMatrix((float*)&world);
		auto wvp = world * ViewProj;

		m_pWorldViewProjection->SetMatrix((float*)&wvp);

		// Textures
		if (m_pTexColor && m_pTexColorRef) m_pTexColor->SetResource(m_pTexColorRef->GetSRV());
		if (m_pTexNormals && m_pTexNormalsRef) m_pTexNormals->SetResource(m_pTexNormalsRef->GetSRV());
		if (m_pTexEmmisive && m_pTexEmmisiveRef) m_pTexEmmisive->SetResource(m_pTexEmmisiveRef->GetSRV());
		if (m_pTexOpacity && m_pTexOpacityRef) m_pTexOpacity->SetResource(m_pTexOpacityRef->GetSRV());

		// Usage:
		if (m_pUseTexColor) m_pUseTexColor->SetBool(m_UseTexColor);
		if (m_pUseTexEmmisive) m_pUseTexEmmisive->SetBool(m_UseTexEmmisive);
		if (m_pUseTexNormals) m_pUseTexNormals->SetBool(m_UseTexNormals);
		if (m_pUseTexOpacity) m_pUseTexOpacity->SetBool(m_UseTexOpacity);

		// Ambient:
		if (m_pColorAmbient) m_pColorAmbient->SetFloatVector(&m_ColorAmbient.r);
		if (m_pAmbientIntensity) m_pAmbientIntensity->SetFloat(m_AmbientIntensity);
		
		// Default color:
		if (m_pColorDefault) m_pColorDefault->SetFloatVector(&m_ColorDefault.r);

		// Intensities:
		if (m_pEmmisiveIntensity) m_pEmmisiveIntensity->SetFloat(m_EmmisiveIntensity);
		if (m_pOpacityIntensity) m_pOpacityIntensity->SetFloat(m_OpacityIntensity);
	}

	bool MatDefaultShaded::SetTexColor(const std::string& path)
	{
		Texture2D* pTexture = ContentLocator::Get()->Load<Texture2D>(path);
		if (pTexture) m_pTexColorRef = pTexture;

		bool res = pTexture != nullptr;
		m_UseTexColor = res;

		return res;
	}
	bool MatDefaultShaded::SetTexNormals(const std::string& path)
	{
		Texture2D* pTexture = ContentLocator::Get()->Load<Texture2D>(path);
		if (pTexture) m_pTexNormalsRef = pTexture;
		
		bool res = pTexture != nullptr;
		m_UseTexNormals = res;

		return res;
	}
	bool MatDefaultShaded::SetTexEmmisive(const std::string& path)
	{
		Texture2D* pTexture = ContentLocator::Get()->Load<Texture2D>(path);
		if (pTexture) m_pTexEmmisiveRef = pTexture;
		
		bool res = pTexture != nullptr;
		m_UseTexEmmisive = res;

		return res;
	}
	bool MatDefaultShaded::SetTexOpacity(const std::string& path)
	{
		Texture2D* pTexture = ContentLocator::Get()->Load<Texture2D>(path);
		if (pTexture) m_pTexOpacityRef = pTexture;
		
		bool res = pTexture != nullptr;
		m_UseTexOpacity = res;

		return res;
	}

	void MatDefaultShaded::SetAmbient(const ColorRGB& col, float intensity)
	{
		m_AmbientIntensity = intensity;
		m_ColorAmbient = col;
	}

	void MatDefaultShaded::SetDefaultColor(const ColorRGB& col)
	{
		m_ColorDefault = col;
	}

	MatDefaultShaded::~MatDefaultShaded()
	{
		SafeRelease(m_pWorld);
		SafeRelease(m_pWorldViewProjection);
	}
}

