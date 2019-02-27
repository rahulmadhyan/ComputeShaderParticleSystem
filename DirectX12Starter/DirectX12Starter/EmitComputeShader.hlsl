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
ConsumeStructuredBuffer<uint> CDeadList			: register(u1);
RWStructuredBuffer<ParticleDraw> DrawList		: register(u2);
RWStructuredBuffer<uint> DrawArgs				: register(u3);

[numthreads(32, 1, 1)]
void main(uint id : SV_DispatchThreadID )
{
	if (id.x >= (uint)emitCount)
		return;

	uint emitIndex = CDeadList.Consume();

	float3 gridPosition;
	uint gridIndex = emitIndex;
	gridPosition.x = gridIndex % (gridSize + 1);
	gridIndex /= (gridSize + 1);
	gridPosition.y = gridIndex % (gridSize + 1);
	gridIndex /= (gridSize + 1);
	gridPosition.z = gridIndex;

	// update it in ParticlePool
	Particle emitParticle = ParticlePool.Load(emitIndex);

	//color and position depend on the grid position and size
	emitParticle.Position = gridPosition / 10.0f - float3(gridSize / 20.0f, gridSize / 20.0f, -gridSize / 10.0f);
	emitParticle.Velocity = float3(0.0f, 0.0f, 0.0f);
	//emitParticle.Color = float4(gridPosition / gridSize, 1);
	emitParticle.Color = startColor;
	emitParticle.Age = 0.0f;
	emitParticle.Size = 0.05f;
	emitParticle.Alive = 1.0f;

	//Put it back
	ParticlePool[emitIndex] = emitParticle;
}