#pragma once
#include <raylib.h>
#include "Cube.h"
#include "Cubie.h"
class Cube {
public:
	Cube(Vector3 position, float cubieSize);
	void Draw();
	void RotateUp(bool clockwise);
	void RotateDown(bool clockwise);
	void RotateLeft(bool clockwise);
	void RotateRight(bool clockwise);
	void RotateFront(bool clockwise);
	void RotateBack(bool clockwise);

private:
	Vector3 position;
	int dimension = 3;
	float cubieSize;
	Cubie cubies[3][3][3];

	void PopulateCube();
};