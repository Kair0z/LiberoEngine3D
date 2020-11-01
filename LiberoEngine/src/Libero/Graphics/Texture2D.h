#pragma once
#include <string>

struct ID3D11ShaderResourceView;
struct ID3D11Texture2D;

namespace Libero
{
	using namespace Math;
	struct Texture2D_Desc
	{
		Vector2f m_Dimensions = { 512, 512 };
		std::string m_Filename = "";
	};

	class Texture2D final
	{
	public:
		~Texture2D();

		ID3D11ShaderResourceView* GetSRV() const;

	private:
		Texture2D();

		ID3D11ShaderResourceView* m_pSRV;
		ID3D11Texture2D* m_pTexture;
		Texture2D_Desc m_Data;

		// Only graphicsmaster should create Textures!
		friend class GraphicsMaster;
	};
}


