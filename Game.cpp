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
	camera.target = { 1.5f, 1.5f, 1.5f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
	DisableCursor();
	SetTargetFPS(60);

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
	DrawRectangle(10, 10, 100, 133, Fade(SKYBLUE, 0.5f));
	DrawRectangleLines(10, 10, 100, 133, BLUE);

	DrawText("Front: 1", 20, 20, 10, BLACK);
	DrawText("Back: 2", 20, 40, 10, BLACK);
	DrawText("Up: 3", 20, 60, 10, BLACK);
	DrawText("Down: 4", 20, 80, 10, BLACK);
	DrawText("Left: 5", 20, 100, 10, BLACK);
	DrawText("Right: 6", 20, 120, 10, BLACK);


}

void Game::Update()
{
	if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_D))
	{
		UpdateCamera(&camera, CAMERA_THIRD_PERSON);
	}
	if (IsKeyDown('Z')) camera.target = Vector3{ 0.0f, 0.0f, 0.0f };

	if (rotateUpTimer > 0.0f) {
		rotateUpTimer -= GetFrameTime();
	}

	// Call RotateUp function if key is pressed and cooldown has elapsed
	if (IsKeyDown('1') && rotateUpTimer <= 0.0f) {
		if (IsKeyDown(KEY_LEFT_CONTROL)) {
			cube.RotateFront(true);
		}
		else {
			cube.RotateFront(false);
		}
		rotateUpTimer = rotateUpCooldown;
	}

	if (IsKeyDown('2') && rotateUpTimer <= 0.0f) {
		if (IsKeyDown(KEY_LEFT_CONTROL)) {
			cube.RotateBack(true);
		}
		else {
			cube.RotateBack(false);
		}
		rotateUpTimer = rotateUpCooldown;
	}

	if (IsKeyDown('3') && rotateUpTimer <= 0.0f) {
		if (IsKeyDown(KEY_LEFT_CONTROL)) {
			cube.RotateUp(true);
		}
		else {
			cube.RotateUp(false);
		}
		rotateUpTimer = rotateUpCooldown;
	}

	if (IsKeyDown('4') && rotateUpTimer <= 0.0f) {
		if (IsKeyDown(KEY_LEFT_CONTROL)) {
			cube.RotateDown(true);
		}
		else {
			cube.RotateDown(false);
		}
		rotateUpTimer = rotateUpCooldown;
	}

	if (IsKeyDown('5') && rotateUpTimer <= 0.0f) {
		if (IsKeyDown(KEY_LEFT_CONTROL)) {
			cube.RotateRight(true);
		}
		else {
			cube.RotateRight(false);
		}
		rotateUpTimer = rotateUpCooldown;
	}

	if (IsKeyDown('6') && rotateUpTimer <= 0.0f) {
		if (IsKeyDown(KEY_LEFT_CONTROL)) {
			cube.RotateLeft(true);
		}
		else {
			cube.RotateLeft(false);
		}
		rotateUpTimer = rotateUpCooldown;
	}

}
