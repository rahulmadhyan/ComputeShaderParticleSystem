
struct Particle
{
	float4 Color;
	float3 Position;
	float Age;
	float3 Velocity;
	float Size;
	float Alive;
	float3 Padding;
};

struct ParticleDraw
{
	uint Index;
};

float CalculateGridPosition(uint index, int gridSize)
{
	float3 gridPosition;

	gridSize += 1;

	gridPosition.x = index % gridSize;

	index /= gridSize;
	gridPosition.y = index % gridSize;

	index /= gridSize;
	gridPosition.z = index;

	return gridPosition;
}