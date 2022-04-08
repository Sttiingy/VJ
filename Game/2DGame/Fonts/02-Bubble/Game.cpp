#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init("01");
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	if (key == 49) {
		scene.chgpyrpos(1, 22);
		scene.init("01");
	}
	if (key == 50) {
		scene.chgpyrpos(1, 22);
		scene.init("02");
	}
	if (key == 51) {
		scene.chgpyrpos(1, 23);
		scene.init("03");
	}
	if (key == 52) {
		scene.chgpyrpos(1, 21);
		scene.init("04");
	}
	if (key == 53) {
		scene.chgpyrpos(1, 19);
		scene.init("05");
	}
	if (key == 54) {
		scene.chgpyrpos(1, 19);
		scene.init("06");
	}
	if (key == 55) {
		scene.chgpyrpos(1, 18);
		scene.init("07");
	}
	if (key == 56) {
		scene.chgpyrpos(3, 22);
		scene.init("08");
	}
	if (key == 57) {
		scene.chgpyrpos(3, 22);
		scene.init("09");
	}
	if (key == 48) {
		scene.chgpyrpos(3, 22);
		scene.init("10");
	}

	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





