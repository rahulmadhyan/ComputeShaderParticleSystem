#include "Emitter.h"

Emitter::Emitter(int maxParticles, int gridSize, float emissionRate, float lifeTime) :
	maxParticles(maxParticles),
	gridSize(gridSize),
	emissionRate(emissionRate),
	lifeTime(lifeTime)
{
	emitTimeCounter = 0.0f;
	timeBetweenEmit = 1.0f / emissionRate;
}

Emitter::~Emitter()
{

}

int Emitter::GetEmitCount()
{
	return emitCount;
}

int Emitter::GetMaxParticles()
{
	return maxParticles;
}

int Emitter::GetGridSize()
{
	return gridSize;
}

int Emitter::GetVerticesPerParticle()
{
	return 1;
}

float Emitter::GetLifeTime()
{
	return lifeTime;
}

float Emitter::GetEmitTimeCounter()
{
	return emitTimeCounter;
}

float Emitter::GetTimeBetweenEmit()
{
	return timeBetweenEmit;
}

void Emitter::SetEmitCount(int value)
{
	emitCount = value;
}

void Emitter::SetEmitTimeCounter(float value)
{
	emitTimeCounter = value;
}

void Emitter::Update(float TotalTime, float deltaTime)
{
	emitTimeCounter += deltaTime;
}