// Global Data:
float4x4 gTransform : WorldViewProjection;
Texture2D gSpriteTexture;
float2 gTextureSize;

// States:
RasterizerState gRS
{
	CullMode = BACK;
};

DepthStencilState gDSS_NoDepth
{
	DepthEnable = false;
};

BlendState gBS_EnableBlending
{
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
};

SamplerState gSS_Point
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = WRAP;
	AddressV = WRAP;
};

// Structs:
struct VS_IN
{
	float4 TransformData : POSITION;
	float4 TransformData2 : DATA;
};

struct GS_OUT
{
	float4 Position : SV_POSITION;
	float2 UV: TEXCOORD0;
};

// *******
// Main VS
// *******
VS_IN MainVS(VS_IN input)
{
	return input;
}

void CreateVertex(inout TriangleStream<GS_OUT> triStream, float3 pos, float2 uv, float rot, float2 rotCosSin, float2 offset, float2 pivotOffset)
{
	if (rot != 0)
	{
		float2 finalPos = pos;

		// Transform to origin:
		finalPos -= offset + pivotOffset;

		// Rotate:
		pos.x = finalPos.x * rotCosSin.x - finalPos.y * rotCosSin.y;
		pos.y = finalPos.y * rotCosSin.x + finalPos.x * rotCosSin.y;

		// Retransform to pos: no pivot...
		pos.x += offset.x;
		pos.y += offset.y;
	}
	else pos -= float3(pivotOffset.x, pivotOffset.y, 0.0f); // Else just apply pivot...

	GS_OUT newVertex = (GS_OUT)0;
	newVertex.Position = mul(float4(pos, 1.0f), gTransform);
	newVertex.UV = uv;
	triStream.Append(newVertex);
}
[maxvertexcount(4)]
void MainGS(point VS_IN vertex[1], inout TriangleStream<GS_OUT> triStream)
{
	float3 position = vertex[0].TransformData.xyz;
	float2 offset = vertex[0].TransformData.xy;
	float rotation = vertex[0].TransformData.w;
	float2 pivot = vertex[0].TransformData2.xy;
	float2 scale = vertex[0].TransformData2.zw;
	float2 uv = float2(0, 0);

	// LT----------RT //TriangleStrip >> (LT > RT > LB, LB > RB > RT)
	// |          / |
	// |       /    |
	// |    /       |
	// | /          |
	// LB----------RB

	pivot *= gTextureSize * scale; // transform pivot with scalings:
	float2 rotCosSin = float2(cos(rotation), sin(rotation));

	float3 vertPos = position;
	CreateVertex(triStream, vertPos, float2(0, 0), rotation, rotCosSin, offset, pivot);
	vertPos = float3(position.x + (gTextureSize.x * scale.x), position.y, position.z);
	CreateVertex(triStream, vertPos, float2(1, 0), rotation, rotCosSin, offset, pivot);
	vertPos = float3(position.x, position.y + (gTextureSize.y * scale.y), position.z);
	CreateVertex(triStream, vertPos, float2(0, 1), rotation, rotCosSin, offset, pivot);
	vertPos = float3(position.x + (gTextureSize.x * scale.x), position.y + (gTextureSize.y * scale.y), position.z);
	CreateVertex(triStream, vertPos, float2(1, 1), rotation, rotCosSin, offset, pivot);
}

// *******
// Main PS
// *******
float4 MainPS(GS_OUT input) : SV_TARGET
{
	return gSpriteTexture.Sample(gSS_Point, input.UV);
}

// Techniques	
technique10 Default
{
	pass P0
	{
		SetRasterizerState(gRS);
		SetBlendState(gBS_EnableBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetDepthStencilState(gDSS_NoDepth,0);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetGeometryShader(CompileShader(gs_4_0, MainGS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}