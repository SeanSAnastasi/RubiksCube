#pragma once
#include <raylib.h>
#include "Cube.h"
#include "Cubie.h"
class Cube {
public:
	Cube(Vector3 position, float cubieSize);
	void Draw();
	void RotateLayer(int layer, char axis, bool clockwise);
	void ShuffleCube(int numMoves);
	bool isSolved();
	void updateSolved();
private:
	Vector3 position;
	int dimension = 3;
	float cubieSize;
	Cubie cubies[3][3][3];
	int cubieIndex[3][3][3];
	bool solved;

	void PopulateCube();
};