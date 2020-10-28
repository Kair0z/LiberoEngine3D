// Global Data:
float4x4 gWVP;
float3 gCameraPosition;

float3 gColorApex;
float3 gColorBase;

// States:
RasterizerState gRS
{
	CullMode = FRONT;
};

DepthStencilState gDSS
{
	DepthEnable = false;
};

// Structs:
struct VS_IN
{
	float3 Position : POSITION;
};
struct VS_OUT
{
	float4 Position : SV_POSITION;
	float4 DomePosition : TEXCOORD0;
};

// *******
// Main VS
// *******
VS_OUT MainVS(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;
	
	float4 newPos = float4(input.Position + gCameraPosition, 1);
	output.Position = mul(newPos, gWVP);
	output.DomePosition = float4(input.Position, 1);

	return output;
}

// *******
// Main PS
// *******
float4 MainPS(VS_OUT input) : SV_TARGET
{
	float height;
	float3 res;

	// Dome height is pretty high! (50)
	height = input.DomePosition.y / 25.f;
	if (height < 0) height = 0.0f;

	res = lerp(gColorBase, gColorApex, height);

	return float4(res, 1.f);
}

// Techniques	
technique10 Default
{
	pass P0
	{
		SetRasterizerState(gRS);
		SetDepthStencilState(gDSS, 0);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}