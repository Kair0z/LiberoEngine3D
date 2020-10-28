// Global Data:
float4x4 gWorld : WORLD;
float4x4 gWVP : WORLDVIEWPROJECTION;
float3 gLightDirection = float3(-0.577f, -0.577f, 0.577f);

float3 gColorAmbient = float3(1, 0, 0);
float gAmbientIntensity = 0.0f;
float gOpacityIntensity = 1.0f;
float gEmmisiveIntensity = 0.0f;
float3 gColorDiffuse = float3(1, 1, 1);

bool gUseTexNormals = false;
bool gUseTexDiffuse = false;
bool gUseTexEmmisive = false;
bool gUseTexOpacity = false;

Texture2D gTexDiffuse : TEXDIFFUSE;
Texture2D gTexNormals : TEXNORMAL;
Texture2D gTexOpacity : TEXOPACITY;
Texture2D gTexEmmisive : TEXEMMISIVE;

// States:
RasterizerState gRS
{
	CullMode = BACK;
};
BlendState gBS
{
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
};
SamplerState gSS_Tex
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
	AddressW = WRAP;
};
DepthStencilState gDSS
{
	DepthEnable = true;
};

// Structs:
struct VS_IN
{
	float3 Position : POSITION;
	float2 UV : TEXCOORD;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
};
struct VS_OUT
{
	float4 Position : SV_POSITION;
	float4 WorldPosition : WORLDPOS;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
};

// Math:
float3 CalcDiffuse(float3 normal, float2 uv)
{
	float3 color = gColorDiffuse;
	if (gUseTexDiffuse) color = gTexDiffuse.Sample(gSS_Tex, uv).rgb;

	float dotResult = dot(-normal, gLightDirection);

	return color * dotResult;
}
float3 GetNormalFromSample(float3 sampleVal, float3 planeNormal, float3 tangent)
{
	float3 realNormal = { 2 * sampleVal.r - 1, 2 * sampleVal.g - 1, 2 * sampleVal.b - 1 };
	float3 binormal = cross(planeNormal, tangent);
	float3x3 tangentSpaceAxis =
	{
		tangent.x, tangent.y, tangent.z,
		binormal.x, binormal.y, binormal.z,
		planeNormal.x, planeNormal.y, planeNormal.z
	};

	return mul(realNormal, tangentSpaceAxis);
}
float3 CalcNormal(float3 tangent, float3 normal, float2 uv)
{
	if (gUseTexNormals)
	{
		float3 sampleVal = gTexNormals.Sample(gSS_Tex, uv);
		return GetNormalFromSample(sampleVal, normal, tangent);
	}
	else return normal;
}
float CalcOpacity(float2 uv)
{
	float result = gOpacityIntensity;
	if (gUseTexOpacity) result *= gTexOpacity.Sample(gSS_Tex, uv);
	
	return result;
}
float3 CalcEmmisive(float2 uv)
{
	float result = gEmmisiveIntensity;
	if (gUseTexEmmisive) result *= gTexEmmisive.Sample(gSS_Tex, uv);

	return result;
}

// *******
// Main VS
// *******
VS_OUT MainVS(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	output.Position = mul(float4(input.Position, 1.0), gWVP);
	output.WorldPosition = mul(float4(input.Position, 1.0), gWorld);
	output.Normal = mul(input.Normal, (float3x3)gWorld);
	output.Tangent = mul(input.Tangent, (float3x3)gWorld);
	output.UV = input.UV;
	output.Color = input.Color;

	return output;
}

// *******
// Main PS
// *******
float4 MainPS(VS_OUT input) : SV_TARGET
{
	input.Normal = normalize(input.Normal);
	input.Tangent = normalize(input.Tangent);

	// Normal:
	float3 normal = CalcNormal(input.Tangent, input.Normal, input.UV);

	// Diffuse:
	float3 diffuse = CalcDiffuse(normal, input.UV);

	// Ambient:
	float3 ambient = gColorAmbient * gAmbientIntensity;

	// Final:
	float3 finalColor = diffuse + ambient;

	// Opacity:
	float opacity = CalcOpacity(input.UV);

	return float4(finalColor, 1.f);
}

// Techniques
technique10 Default
{
	pass P0
	{
		SetRasterizerState(gRS);
		SetDepthStencilState(gDSS, 0);
		SetBlendState(gBS, float4(0, 0, 0, 0), 0xFFFFFFFF);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}