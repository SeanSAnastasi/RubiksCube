#include "Game.h"
#include <raylib.h>
#include <assert.h>
Game::Game(int width, int height, std::string title)
	:
	cube({ 0.0f, 0.0f, 0.0f }, 2.0f)
{
	assert(!GetWindowHandle());
	InitWindow(width, height, title.c_str());

	camera = { 0 };
	camera.position = { 15.0f, 10.0f, 15.0f }; // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
	DisableCursor();
	SetTargetFPS(60);

	pressed = false;
}

Game::~Game() noexcept
{
	assert(GetWindowHandle());
	CloseWindow();
}

bool Game::GameShouldClose() const
{
	return WindowShouldClose();
}

void Game::Tick()
{
	BeginDrawing();
	Update();
	Draw();
	EndDrawing();
}

void Game::Draw()
{
	ClearBackground(RAYWHITE);




	BeginMode3D(camera);
	// Draw the x, y, and z axis arrows
	DrawLine3D(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 100.0f, 0.0f, 0.0f }, RED);   // x axis
	DrawLine3D(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 100.0f, 0.0f }, GREEN); // y axis
	DrawLine3D(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 100.0f }, BLUE);  // z axis
		cube.Draw();
	EndMode3D();
	if (cube.isSolved()) {
		DrawRectangle(10, 10, 100, 153, Fade(GREEN, 0.5f));
		DrawRectangleLines(10, 10, 100, 153, DARKGREEN);
	}
	else {
		DrawRectangle(10, 10, 100, 153, Fade(RED, 0.5f));
		DrawRectangleLines(10, 10, 100, 153, BLACK);
	}


	DrawText("Front: 1", 20, 20, 10, BLACK);
	DrawText("Back: 2", 20, 40, 10, BLACK);
	DrawText("Up: 3", 20, 60, 10, BLACK);
	DrawText("Down: 4", 20, 80, 10, BLACK);
	DrawText("Left: 5", 20, 100, 10, BLACK);
	DrawText("Right: 6", 20, 120, 10, BLACK);
	DrawText("Shuffle: Space", 20, 140, 10, BLACK);
    DrawFPS(650, 20);

}

void Game::Update()
{
	if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_D))
	{
		UpdateCamera(&camera, CAMERA_THIRD_PERSON);
	}
	checkKeyPressed();
}

void Game::checkKeyPressed()
{
    static float lastKeyPressTime = 0.0f;
    float currentTime = GetTime();

    if (currentTime - lastKeyPressTime < 0.5f)
    {
        return; // Do not process key presses if less than 1 second has passed
    }
    bool keyPressed = false;
    if (IsKeyDown('1')) {
        if (!pressed) {
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                cube.RotateLayer(2, 'x', true);
            }
            else {
                cube.RotateLayer(2, 'x', false);
            }
            pressed = true;
        }
        keyPressed = true;
    }

    if (IsKeyDown('2')) {
        if (!pressed) {
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                cube.RotateLayer(0, 'x', true);
            }
            else {
                cube.RotateLayer(0, 'x', false);
            }
            pressed = true;
        }
        keyPressed = true;

    }

    if (IsKeyDown('3')) {
        if (!pressed) {
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                cube.RotateLayer(2, 'y', true);
            }
            else {
                cube.RotateLayer(2, 'y', false);
            }
            pressed = true;
        }
        keyPressed = true;

    }

    if (IsKeyDown('4')) {
        if (!pressed) {
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                cube.RotateLayer(0, 'y', true);
            }
            else {
                cube.RotateLayer(0, 'y', false);
            }
            pressed = true;
        }
        keyPressed = true;

    }

    if (IsKeyDown('5')) {
        if (!pressed) {
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                cube.RotateLayer(2, 'z', true);
            }
            else {
                cube.RotateLayer(2, 'z', false);
            }
            pressed = true;
        }
        keyPressed = true;

    }

    if (IsKeyDown('6')) {
        if (!pressed) {
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                cube.RotateLayer(0, 'z', true);
            }
            else {
                cube.RotateLayer(0, 'z', false);
            }
            pressed = true;
        }
        keyPressed = true;

    }

    if (IsKeyDown(KEY_SPACE)) {
        if (!pressed) {
            cube.ShuffleCube(100);
            pressed = true;
        }
        keyPressed = true;

    }
    if (keyPressed) {
        lastKeyPressTime = currentTime;
        return;
    }
	pressed = false;
}
