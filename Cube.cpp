#include "Cube.h"
#include "Cubie.h"

Cube::Cube(Vector3 position, float cubieSize)
{
	this->position = position;
	this->cubieSize = cubieSize;
	PopulateCube();
}

void Cube::Draw()
{
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			for (int k = 0; k < dimension; k++) {
				cubies[i][j][k].Draw();
			}
		}
	}
}

void Cube::PopulateCube()
{
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			for (int k = 0; k < dimension; k++) {
				Color colors[6] = { WHITE, YELLOW , GREEN, BLUE , ORANGE , RED };
				cubies[i][j][k] = Cubie(i, j, k, cubieSize, colors, BLACK);
			}
		}
	}
}

void Cube::RotateUp(bool clockwise)
{
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			cubies[i][2][j].RotateAroundPoint('y', clockwise);
		}
	}
}
void Cube::RotateDown(bool clockwise)
{
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			cubies[i][0][j].RotateAroundPoint('y', clockwise);
		}
	}
}
void Cube::RotateFront(bool clockwise)
{
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			cubies[2][i][j].RotateAroundPoint('x', clockwise);
		}
	}
}
void Cube::RotateBack(bool clockwise)
{
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			cubies[0][i][j].RotateAroundPoint('x', clockwise);
		}
	}
}
void Cube::RotateLeft(bool clockwise)
{
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			cubies[i][j][0].RotateAroundPoint('z', clockwise);
		}
	}
}
void Cube::RotateRight(bool clockwise)
{
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			cubies[i][j][2].RotateAroundPoint('z', clockwise);
		}
	}
}

