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
	float3 velocity;
	float3 acceleration;
	float4 startColor;
	float4 endColor;
	float lifeTime;
}

struct VS_OUTPUT
{
	float3 Position		: POSITION;
	float Size			: SIZE;
	float4 Color		: COLOR;
};

StructuredBuffer<Particle> ParticlePool		: register(t0);
StructuredBuffer<ParticleDraw> DrawList		: register(t1);

VS_OUTPUT main(uint id : SV_VertexID)
{
	VS_OUTPUT output;

	ParticleDraw draw = DrawList.Load(id);
	Particle particle = ParticlePool.Load(draw.Index);

	// pass through
	output.Position = particle.Position;
	output.Size = particle.Size;
	output.Color = particle.Color;

	return output;
}