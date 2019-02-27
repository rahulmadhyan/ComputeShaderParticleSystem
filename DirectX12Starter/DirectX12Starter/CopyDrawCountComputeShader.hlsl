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
	float4 startColor;
	float4 endColor;
	float3 velocity;
	float lifeTime;
	float3 acceleration;
	float pad;
	int emitCount;
	int maxParticles;
	int gridSize;
}

RWStructuredBuffer<Particle> ParticlePool		: register(u0);
AppendStructuredBuffer<uint> ADeadList			: register(u1);
RWStructuredBuffer<ParticleDraw> DrawList		: register(u2);
RWStructuredBuffer<uint> DrawArgs				: register(u3);

[numthreads(1, 1, 1)]
void main(uint3 id : SV_DispatchThreadID)
{
	// increment the counter to get the previous value, which happens to be how many particles we want to draw
	DrawArgs[0] = DrawList.IncrementCounter(); // vertexCountPerInstance (or index count if using an index buffer)
	DrawArgs[1] = 1; // instanceCount
	DrawArgs[2] = 0; // offsets
	DrawArgs[3] = 0; // offsets
	DrawArgs[4] = 0; // offsets
	DrawArgs[5] = 0; // offsets
	DrawArgs[6] = 0; // offsets
	DrawArgs[7] = 0; // offsets
	DrawArgs[8] = 0; // offsets
}