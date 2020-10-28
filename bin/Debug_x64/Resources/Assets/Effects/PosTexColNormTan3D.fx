//--------------------------------------------------------------------------------------
// Global Data
//--------------------------------------------------------------------------------------
float4x4 gWorld : WORLD;
float4x4 gWVP : WORLDVIEWPROJECTION; 
float3 gLightDirection = float3(-0.577f, -0.577f, 0.577f);

Texture2D gDiffuse : DIFFUSE;
Texture2D gNormalmap : NORMALMAP;

//--------------------------------------------------------------------------------------
// States
//--------------------------------------------------------------------------------------

DepthStencilState EnableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
};
RasterizerState NoCulling
{
	CullMode = NONE;
};
BlendState EnableBlending
{
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
};
SamplerState DefaultSample;

//--------------------------------------------------------------------------------------
// Structs
//--------------------------------------------------------------------------------------
struct VS_INPUT{
	float3 pos : POSITION;
	float2 uv : UV;
	float4 color : COLOR;
	float3 norm : NORMAL;
	float3 tan : TANGENT;
};
struct VS_OUTPUT{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float4 color : COLOR;
	float3 norm : NORMAL;
	float3 tan : TANGENT;
};

//--------------------------------------------------------------------------------------
// Math
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.pos = mul(float4(input.pos,1.0f), gWVP );
	output.color = input.color;
	output.uv = input.uv;
	output.norm = normalize(mul(input.norm, (float3x3)gWorld));
	
	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 diffColor = float4(gDiffuse.Sample(DefaultSample, input.uv).rgb, 1.f);
	float diffStrength
}

//--------------------------------------------------------------------------------------
// Technique
//--------------------------------------------------------------------------------------
technique11 Default
{
    pass P0
    {
		SetRasterizerState(NoCulling);
		SetDepthStencilState(EnableDepth, 0);

        SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}
