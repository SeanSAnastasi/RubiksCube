#pragma once
#pragma once
#include <raylib.h>
class Cubie {
public:
	Cubie(int x, int y, int z, float size, Color color[], Color stroke);
	Cubie();
	void Draw();
	void SetPosition(int x, int y, int z);
	Vector3 GetPosition();
	void RotateAroundPoint(char axis, bool clockwise);
private:
	int x;
	int y;
	int z;

	int rotationX;
	int rotationY;
	int rotationZ;

	float size;
	Color colors[6];
	Color stroke;
	void DrawCubeFaces();
};