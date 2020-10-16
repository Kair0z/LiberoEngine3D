#include "Liber_pch.h"
#include "Texture2D.h"
#include "GraphicsMaster.h"

namespace Libero
{
	Texture2D::Texture2D()
		: m_pSRV{nullptr}
		, m_pTexture{nullptr}
		, m_Data{}
	{

	}

	Texture2D::~Texture2D()
	{
		SafeRelease(m_pSRV);
		SafeRelease(m_pTexture);
	}
	ID3D11ShaderResourceView* Texture2D::GetSRV() const
	{
		return m_pSRV;
	}
}