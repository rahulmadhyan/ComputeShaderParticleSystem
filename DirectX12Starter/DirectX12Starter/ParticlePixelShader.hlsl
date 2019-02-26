#include "ParticleInclude.hlsl"

cbuffer objectData : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
	float aspectRatio;
};

cbuffer timeData : register(b1)
{
	float deltaTime;
	float TotalTime;
}

cbuffer particleData : register(b2)
{
	int emitCount;
	int maxParticles;
	int gridSize;
	int verticesPerParticle;
	float lifeTime;
}

struct GS_OUTPUT
{
	float4 Position		: SV_POSITION;
	float4 Color		: COLOR;
	float2 UV			: TEXCOORD;
};

float4 main(GS_OUTPUT input) : SV_TARGET
{
	input.UV = input.UV * 2 - 1;

	float fade = saturate(distance(float2(0, 0), input.UV));
	float3 color = lerp(input.Color.rgb, float3(0, 0, 0), fade * fade);

	return float4(color, 1);
}