#include "Cube.h"
#include "Cubie.h"
#include <rlgl.h>
#include <math.h>
#include "raymath.h"
#include <iostream>
#include "raylib.h"
#include <cmath>
#include <algorithm>

Cubie::Cubie(int x, int y, int z, float size, Color colors[], Color stroke)
    : x(x), y(y), z(z), size(size), stroke(stroke)
{
    for (int i = 0; i < 6; i++) {
        this->colors[i] = colors[i];
    }
    
}

Cubie::Cubie()
    : x(0), y(0), z(0), size(2.0f), stroke(BLACK)
{
    for (int i = 0; i < 6; i++) {
        this->colors[i] = WHITE;
    }
}



void Cubie::Draw()
{
    DrawCubeFaces();
    DrawCubeWires(Vector3{ (x-1) * size, (y-1) * size, (z-1) * size }, size, size, size, stroke);
}

void Cubie::SetPosition(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Cubie::GetPosition()
{
    return { float(x),float(y),float(z) };
}

void Cubie::DrawCubeFaces()
{
    float x_ = (x-1) * size;
    float y_ = (y-1) * size;
    float z_ = (z-1) * size;
    const Vector3 faceVertices[6][6] = {
    {{-1, -1, 1}, {1, -1, 1}, {-1, 1, 1}, {1, 1, 1}, {-1, 1, 1}, {1, -1, 1}}, // Front face
    {{-1, -1, -1}, {-1, 1, -1}, {1, -1, -1}, {1, 1, -1}, {1, -1, -1}, {-1, 1, -1}}, // Back face
    {{-1, 1, -1}, {-1, 1, 1}, {1, 1, 1}, {1, 1, -1}, {-1, 1, -1}, {1, 1, 1}}, // Top face
    {{-1, -1, -1}, {1, -1, 1}, {-1, -1, 1}, {1, -1, -1}, {1, -1, 1}, {-1, -1, -1}}, // Bottom face
    {{1, -1, -1}, {1, 1, -1}, {1, 1, 1}, {1, -1, 1}, {1, -1, -1}, {1, 1, 1}}, // Right face
    {{-1, -1, -1}, {-1, 1, 1}, {-1, 1, -1}, {-1, -1, 1}, {-1, 1, 1}, {-1, -1, -1}}, // Left face
    };


    rlPushMatrix();

    rlBegin(RL_TRIANGLES);
    for (int i = 0; i < 6; ++i) {
        if (colors[i].a != 0) {
            rlColor4ub(colors[i].r, colors[i].g, colors[i].b, colors[i].a);

            for (int j = 0; j < 6; ++j) {
                Vector3 originalVertex = {
                    x_ + faceVertices[i][j].x * size / 2,
                    y_ + faceVertices[i][j].y * size / 2,
                    z_ + faceVertices[i][j].z * size / 2
                };
                Vector3 rotatedVertex = RotateVertex(originalVertex);
                rlVertex3f(rotatedVertex.x, rotatedVertex.y, rotatedVertex.z);
            }
        }
    }

    rlEnd();
    rlPopMatrix();
}

void Cubie::RotateAroundPoint(char axis, bool clockwise)
{
    // Calculate the necessary rotation matrix based on the global axis
    float angle = clockwise ? 90.0f : -90.0f;
    Matrix globalRotationMatrix{};
    switch (axis)
    {
    case 'x':
        globalRotationMatrix = MatrixRotateX(DEG2RAD * angle);
        break;
    case 'y':
        globalRotationMatrix = MatrixRotateY(DEG2RAD * angle);
        break;
    case 'z':
        globalRotationMatrix = MatrixRotateZ(DEG2RAD * angle);
        break;
    default:
        break;
    }

    // Update the rotation matrix by multiplying with the global rotation matrix
    rotationMatrix = MatrixMultiply(rotationMatrix, globalRotationMatrix);
    currentFrame = 0;
}

Vector3 Cubie::RotateVertex(const Vector3& vertex)
{
    Matrix lerped = QuaternionToMatrix(QuaternionSlerp(QuaternionFromMatrix(prevRotationMatrix), QuaternionFromMatrix(rotationMatrix), (float)currentFrame / animationFrames));
        Vector3 vec = MultiplyVector3ByMatrix(vertex, lerped);    
        currentFrame = std::min(currentFrame+1, animationFrames);
        if (currentFrame == animationFrames) {
            prevRotationMatrix = rotationMatrix;
        }
        return vec;
    
}

Vector3 Cubie::MultiplyVector3ByMatrix(const Vector3& v, const Matrix& m) {
    Vector3 result;
    result.x = v.x * m.m0 + v.y * m.m4 + v.z * m.m8 + m.m12;
    result.y = v.x * m.m1 + v.y * m.m5 + v.z * m.m9 + m.m13;
    result.z = v.x * m.m2 + v.y * m.m6 + v.z * m.m10 + m.m14;
    return result;
}

bool Cubie::isProperRotation()
{
    Matrix identityMatrix = MatrixIdentity();

    // Check if the rotationMatrix is equal to the identity matrix
    if (MatrixEqual(rotationMatrix, identityMatrix))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Cubie::MatrixEqual(const Matrix& mat1, const Matrix& mat2)
{
    float epsilon = 1e-6;
    return (fabs(mat1.m0 - mat2.m0) <= epsilon) && (fabs(mat1.m1 - mat2.m1) <= epsilon) &&
        (fabs(mat1.m2 - mat2.m2) <= epsilon) && (fabs(mat1.m3 - mat2.m3) <= epsilon) &&
        (fabs(mat1.m4 - mat2.m4) <= epsilon) && (fabs(mat1.m5 - mat2.m5) <= epsilon) &&
        (fabs(mat1.m6 - mat2.m6) <= epsilon) && (fabs(mat1.m7 - mat2.m7) <= epsilon) &&
        (fabs(mat1.m8 - mat2.m8) <= epsilon) && (fabs(mat1.m9 - mat2.m9) <= epsilon) &&
        (fabs(mat1.m10 - mat2.m10) <= epsilon) && (fabs(mat1.m11 - mat2.m11) <= epsilon) &&
        (fabs(mat1.m12 - mat2.m12) <= epsilon) && (fabs(mat1.m13 - mat2.m13) <= epsilon) &&
        (fabs(mat1.m14 - mat2.m14) <= epsilon) && (fabs(mat1.m15 - mat2.m15) <= epsilon);
}
