#pragma once
#include <string>
#include <raylib.h>
#include "Cube.h"
class Game
{
public:
	Game(int width, int height, std::string title);
	~Game() noexcept;
	/// RULE OF 5, copy constructor and copy assignment deleted so move deleted aswell
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	bool GameShouldClose() const;
	void Tick();
private:
	void Draw();
	void Update();
	void checkKeyPressed();
	Camera3D camera;
	Cube cube;

	bool pressed;
};