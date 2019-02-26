#include "ParticleInclude.hlsl"
#include "SimplexNoise.hlsl"

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
	float lifeTime;
	float3 velocity;
	float3 acceleration;
	float4 startColor;
	float4 endColor;
}

RWStructuredBuffer<Particle> ParticlePool		: register(u0);
AppendStructuredBuffer<uint> ADeadList			: register(u1);
RWStructuredBuffer<ParticleDraw> DrawList		: register(u2);
RWStructuredBuffer<uint> DrawArgs				: register(u3);

[numthreads(32, 1, 1)]
void main(uint id : SV_DispatchThreadID)
{
	// outside range?
	if (id.x >= (uint)maxParticles) 
		return;

	// add the index to the dead list
	ADeadList.Append(id.x);
}