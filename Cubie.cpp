#include "Cube.h"
#include "Cubie.h"
#include <rlgl.h>
#include <math.h>
#include "raymath.h"

Cubie::Cubie(int x, int y, int z, float size, Color colors[], Color stroke)
    : x(x), y(y), z(z), size(size), stroke(stroke), rotationX(0), rotationZ(0), rotationY(0)
{
    for (int i = 0; i < 6; i++) {
        this->colors[i] = colors[i];
    }
}

Cubie::Cubie()
    : x(0), y(0), z(0), size(2.0f), stroke(BLACK), rotationX(0), rotationZ(0), rotationY(0)
{
    for (int i = 0; i < 6; i++) {
        this->colors[i] = WHITE;
    }
}



void Cubie::Draw()
{
    DrawCubeFaces();
    DrawCubeWires(Vector3{ x * size, y * size, z * size }, size, size, size, stroke);
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
    float x_ = 0.0f;
    float y_ = 0.0f;
    float z_ = 0.0f;

    rlPushMatrix();

    // First, translate to the center of the cubie
    rlTranslatef(x * size, y * size, z * size);
    rlRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    rlRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    rlRotatef(rotationZ, 0.0f, 0.0f, 1.0f);
    // Then, translate back to the original position
    rlTranslatef(-x * size, -y * size, -z * size);

    rlTranslatef(x * size, y * size, z * size);

    rlBegin(RL_TRIANGLES);
    if (colors[0].a != 0) {
        // Front face
        rlColor4ub(colors[0].r, colors[0].g, colors[0].b, colors[0].a);

        rlVertex3f(x_ - size / 2, y_ - size / 2, z_ + size / 2);  // Bottom Left
        rlVertex3f(x_ + size / 2, y_ - size / 2, z_ + size / 2);  // Bottom Right
        rlVertex3f(x_ - size / 2, y_ + size / 2, z_ + size / 2);  // Top Left

        rlVertex3f(x_ + size / 2, y_ + size / 2, z_ + size / 2);  // Top Right
        rlVertex3f(x_ - size / 2, y_ + size / 2, z_ + size / 2);  // Top Left
        rlVertex3f(x_ + size / 2, y_ - size / 2, z_ + size / 2);  // Bottom Right

    }
    if (colors[1].a != 0) {
        // Back face
        rlColor4ub(colors[1].r, colors[1].g, colors[1].b, colors[1].a);

        rlVertex3f(x_ - size / 2, y_ - size / 2, z_ - size / 2);  // Bottom Left
        rlVertex3f(x_ - size / 2, y_ + size / 2, z_ - size / 2);  // Top Left
        rlVertex3f(x_ + size / 2, y_ - size / 2, z_ - size / 2);  // Bottom Right

        rlVertex3f(x_ + size / 2, y_ + size / 2, z_ - size / 2);  // Top Right
        rlVertex3f(x_ + size / 2, y_ - size / 2, z_ - size / 2);  // Bottom Right
        rlVertex3f(x_ - size / 2, y_ + size / 2, z_ - size / 2);  // Top Left
    }
    if (colors[2].a != 0) {
        // Top face
        rlColor4ub(colors[2].r, colors[2].g, colors[2].b, colors[2].a);

        rlVertex3f(x_ - size / 2, y_ + size / 2, z_ - size / 2);  // Top Left
        rlVertex3f(x_ - size / 2, y_ + size / 2, z_ + size / 2);  // Bottom Left
        rlVertex3f(x_ + size / 2, y_ + size / 2, z_ + size / 2);  // Bottom Right

        rlVertex3f(x_ + size / 2, y_ + size / 2, z_ - size / 2);  // Top Right
        rlVertex3f(x_ - size / 2, y_ + size / 2, z_ - size / 2);  // Top Left
        rlVertex3f(x_ + size / 2, y_ + size / 2, z_ + size / 2);  // Bottom Right
    }
    if (colors[3].a != 0) {
        // Bottom face
        rlColor4ub(colors[3].r, colors[3].g, colors[3].b, colors[3].a);

        rlVertex3f(x_ - size / 2, y_ - size / 2, z_ - size / 2);  // Top Left
        rlVertex3f(x_ + size / 2, y_ - size / 2, z_ + size / 2);  // Bottom Right
        rlVertex3f(x_ - size / 2, y_ - size / 2, z_ + size / 2);  // Bottom Left

        rlVertex3f(x_ + size / 2, y_ - size / 2, z_ - size / 2);  // Top Right
        rlVertex3f(x_ + size / 2, y_ - size / 2, z_ + size / 2);  // Bottom Right
        rlVertex3f(x_ - size / 2, y_ - size / 2, z_ - size / 2);  // Top Left
    }
    if (colors[4].a != 0) {
        // Right face
        rlColor4ub(colors[4].r, colors[4].g, colors[4].b, colors[4].a);

        rlVertex3f(x_ + size / 2, y_ - size / 2, z_ - size / 2);  // Bottom Right
        rlVertex3f(x_ + size / 2, y_ + size / 2, z_ - size / 2);  // Top Right
        rlVertex3f(x_ + size / 2, y_ + size / 2, z_ + size / 2);  // Top Left

        rlVertex3f(x_ + size / 2, y_ - size / 2, z_ + size / 2);  // Bottom Left
        rlVertex3f(x_ + size / 2, y_ - size / 2, z_ - size / 2);  // Bottom Right
        rlVertex3f(x_ + size / 2, y_ + size / 2, z_ + size / 2);  // Top Left
    }
    if (colors[5].a != 0) {
        // Left face
        rlColor4ub(colors[5].r, colors[5].g, colors[5].b, colors[5].a);

        rlVertex3f(x_ - size / 2, y_ - size / 2, z_ - size / 2);  // Bottom Right
        rlVertex3f(x_ - size / 2, y_ + size / 2, z_ + size / 2);  // Top Left
        rlVertex3f(x_ - size / 2, y_ + size / 2, z_ - size / 2);  // Top Right

        rlVertex3f(x_ - size / 2, y_ - size / 2, z_ + size / 2);  // Bottom Left
        rlVertex3f(x_ - size / 2, y_ + size / 2, z_ + size / 2);  // Top Left
        rlVertex3f(x_ - size / 2, y_ - size / 2, z_ - size / 2);  // Bottom Right
    }

    rlEnd();
    rlPopMatrix();
}

void Cubie::RotateAroundPoint(char axis, bool clockwise)
{
    Matrix currentRotationMatrix = MatrixIdentity();

    // Calculate current rotation matrix
    currentRotationMatrix = MatrixMultiply(currentRotationMatrix, MatrixRotateX(DEG2RAD * rotationX));
    currentRotationMatrix = MatrixMultiply(currentRotationMatrix, MatrixRotateY(DEG2RAD * rotationY));
    currentRotationMatrix = MatrixMultiply(currentRotationMatrix, MatrixRotateZ(DEG2RAD * rotationZ));

    // Apply the necessary rotation along the global axis
    float angle = clockwise ? -90.0f : 90.0f;
    Matrix globalRotationMatrix;
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

    // Calculate the new rotation matrix
    Matrix newRotationMatrix = MatrixMultiply(MatrixInvert(currentRotationMatrix), globalRotationMatrix);
    newRotationMatrix = MatrixMultiply(newRotationMatrix, currentRotationMatrix);

    // Convert the new rotation matrix to a quaternion and then to Euler angles
    Quaternion rotationQuaternion = QuaternionFromMatrix(newRotationMatrix);
    Vector3 eulerRotation = QuaternionToEuler(rotationQuaternion);

    // Apply Euler angles to the local rotation variables
    rotationX += RAD2DEG * eulerRotation.x;
    rotationY += RAD2DEG * eulerRotation.y;
    rotationZ += RAD2DEG * eulerRotation.z;

    DrawCubeFaces();
}
