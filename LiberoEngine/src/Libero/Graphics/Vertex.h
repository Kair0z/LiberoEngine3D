#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace Libero
{
	struct VertexPosCol
	{
		VertexPosCol() = default;
		VertexPosCol(XMFLOAT3 pos, XMFLOAT4 color)
			: m_Position{ pos }, m_Color{ color }{};

		XMFLOAT3 m_Position{};
		XMFLOAT4 m_Color{};
	};

	struct VertexPosTexCol
	{
		VertexPosTexCol() = default;
		VertexPosTexCol(XMFLOAT3 pos, XMFLOAT2 uv, XMFLOAT4 color)
			: m_Position{ pos }, m_UV{ uv }, m_Color{ color }{};

		XMFLOAT3 m_Position{};
		XMFLOAT2 m_UV{};
		XMFLOAT4 m_Color{};
	};

	struct VertexPosTexColNormTan
	{
		VertexPosTexColNormTan() = default;
		VertexPosTexColNormTan(XMFLOAT3 pos, XMFLOAT2 uv, XMFLOAT4 color, XMFLOAT3 norm, XMFLOAT3 tan)
			: m_Position{ pos }, m_UV{ uv }, m_Color{ color }, m_Norm{ norm }, m_Tangent{ tan }{};
		XMFLOAT3 m_Position{};
		XMFLOAT2 m_UV{};
		XMFLOAT4 m_Color{};
		XMFLOAT3 m_Norm{};
		XMFLOAT3 m_Tangent{};

		static D3D11_INPUT_ELEMENT_DESC m_StatVertexLayout[5];
	};

	inline D3D11_INPUT_ELEMENT_DESC VertexPosTexColNormTan::m_StatVertexLayout[5]
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0 * 4, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, (3) * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, (3 + 2) * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, (3 + 2 + 3) * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, (3 + 2 + 3 + 3) * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};


	struct TrianglePosCol
	{
		TrianglePosCol() = default;
		TrianglePosCol(VertexPosCol v0, VertexPosCol v1, VertexPosCol v2)
			: m_V0{ v0 }, m_V1{ v1 }, m_V2{ v2 }{};

		VertexPosCol m_V0{};
		VertexPosCol m_V1{};
		VertexPosCol m_V2{};
	};

	struct TrianglePosTexCol
	{
		TrianglePosTexCol() = default;
		TrianglePosTexCol(VertexPosTexCol v0, VertexPosTexCol v1, VertexPosTexCol v2)
			: m_V0{ v0 }, m_V1{ v1 }, m_V2{ v2 }{};

		VertexPosTexCol m_V0{};
		VertexPosTexCol m_V1{};
		VertexPosTexCol m_V2{};
	};
}