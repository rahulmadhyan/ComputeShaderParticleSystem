#pragma once

#include <d3d12.h>
#include <DirectXMath.h>
#include "InputManager.h"

using namespace DirectX;

class Camera
{
public:
	Camera();
	Camera(unsigned int width, unsigned int height);
	~Camera();

	XMFLOAT4X4 GetViewMatrix();
	XMFLOAT4X4 GetProjectionMatrix();

	void SetXRotation(float amount);
	void SetYRotation(float amount);
	void SetProjectionMatrix(unsigned int newWidth, unsigned int newHeight);

	void Update();
	void ResetCamera();

private:
	unsigned int screenWidth;
	unsigned int screenHeight;

	float xRotation;
	float yRotation;

	XMFLOAT3 position;
	XMFLOAT3 direction;

	XMFLOAT4X4 viewMatrix;
	XMFLOAT4X4 projectionMatrix;

	void CreateMatrices();
};

