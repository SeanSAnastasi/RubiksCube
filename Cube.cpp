#include "Cube.h"
#include "Cubie.h"
#include <vector>
#include <time.h>

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

                // Make inner faces black
                if (i != 0 && i != dimension - 1) colors[4] = colors[5] = BLACK; // Right and Left faces
                if (j != 0 && j != dimension - 1) colors[2] = colors[3] = BLACK; // Top and Bottom faces
                if (k != 0 && k != dimension - 1) colors[0] = colors[1] = BLACK; // Front and Back faces

                cubies[i][j][k] = Cubie(i, j, k, cubieSize, colors, BLACK);
                cubieIndex[i][j][k] = i * 9 + j * 3 + k;
            }
        }
    }
}

void Cube::RotateLayer(int layer, char axis, bool clockwise)
{
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            switch (axis) {
            case 'x':
                cubies[layer][i][j].RotateAroundPoint(axis, clockwise);
                break;
            case 'y':
                cubies[i][layer][j].RotateAroundPoint(axis, clockwise);
                break;
            case 'z':
                cubies[i][j][layer].RotateAroundPoint(axis, clockwise);
                break;
            }
        }
    }

    // Create a temporary array to store the cubies during the swap
    std::vector<std::vector<Cubie>> temp(dimension, std::vector<Cubie>(dimension));
    std::vector<std::vector<int>> tempSolved(dimension, std::vector<int>(dimension));


    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            int srcRow = clockwise ? j : (dimension - 1 - j);
            int srcCol = clockwise ? (dimension - 1 - i) : i;

            switch (axis) {
            case 'x':
                temp[i][j] = cubies[layer][srcRow][srcCol];
                tempSolved[i][j] = cubieIndex[layer][srcRow][srcCol];
                break;
            case 'y':
                temp[i][j] = cubies[srcCol][layer][srcRow];
                tempSolved[i][j] = cubieIndex[srcCol][layer][srcRow];
                break;
            case 'z':
                temp[i][j] = cubies[srcRow][srcCol][layer];
                tempSolved[i][j] = cubieIndex[srcRow][srcCol][layer];
                break;
            }
        }
    }

    // Update the cubies array with the new positions
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            switch (axis) {
            case 'x':
                cubies[layer][i][j] = temp[i][j];
                cubieIndex[layer][i][j] = tempSolved[i][j];
                break;
            case 'y':
                cubies[i][layer][j] = temp[j][i];
                cubieIndex[i][layer][j] = tempSolved[j][i];
                break;
            case 'z':
                cubies[i][j][layer] = temp[i][j];
                cubieIndex[i][j][layer] = tempSolved[i][j];
                break;
            }
        }
    }
    updateSolved();
}

void Cube::ShuffleCube(int numMoves)
{
    char axes[3]{ 'x', 'y', 'z' };
    int layers[2]{ 0,2 };
    bool clockwises[2]{ true, false };
    srand((unsigned int)time(NULL));
    for (int i = 0; i < numMoves; i++) {
        int randIndex = rand() % 3;
        char axis = axes[randIndex];
        randIndex = rand() % 2;
        int layer = layers[randIndex];
        randIndex = rand() % 2;
        bool clockwise = clockwises[randIndex];

        RotateLayer(layer, axis, clockwise);
    }
}

bool Cube::isSolved()
{
    return solved;
}

void Cube::updateSolved()
{
    bool tempSolved = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (cubieIndex[i][j][k] != i * 9 + j * 3 + k) {
                    tempSolved = false;
                }
                if (!cubies[i][j][k].isProperRotation()) {
                    tempSolved = false;

                }
            }
        }
    }
    solved = tempSolved;
}


