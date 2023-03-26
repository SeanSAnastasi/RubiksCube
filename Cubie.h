#pragma once
#pragma once
#include <raylib.h>
#include "raymath.h"

class Cubie {
public:
	Cubie();
	Cubie(int x, int y, int z, float size, Color color[], Color stroke);
	void Draw();
	void SetPosition(int x, int y, int z);
	Vector3 GetPosition();
	void RotateAroundPoint(char axis, bool clockwise);
	bool isProperRotation();

private:
	int x;
	int y;
	int z;
	int animationFrames = 600;
	int currentFrame = 0;

	Matrix prevRotationMatrix = MatrixIdentity();
	Matrix rotationMatrix = MatrixIdentity();

	float size;
	Color colors[6];
	Color stroke;
	void DrawCubeFaces();
	Vector3 RotateVertex(const Vector3& vertex);
	Vector3 MultiplyVector3ByMatrix(const Vector3& v, const Matrix& m);

	bool MatrixEqual(const Matrix& mat1, const Matrix& mat2);
};