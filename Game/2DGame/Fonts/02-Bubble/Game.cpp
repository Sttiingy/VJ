#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Sound.h"
#include <irrKlang.h>

void Game::init()
{
	//Sound::instance().playMusic("sounds/SongTheme.wav");
	bPlay = true;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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
		scene.chgpyrpos(1, 20);
		scene.setFruitPos(31, 14);
		scene.setWalkPos(10, 10);
		scene.init("01");
	}
	if (key == 50) {
		scene.chgpyrpos(1, 22);
		scene.setFruitPos(3, 9);
		scene.init("02");
	}
	if (key == 51) {
		scene.chgpyrpos(1, 21);
		scene.init("03");
	}
	if (key == 52) {
		scene.chgpyrpos(3, 18);
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

int Game::getActualLvl() {
	return scene.getActualLvl();
}

void Game::goNextLvl(int actualLvl) {
	if (actualLvl == 1) {
		scene.chgpyrpos(1, 22);
		scene.setFruitPos(3, 9);
		scene.init("02");
	}
	else if (actualLvl == 2) {
		scene.chgpyrpos(1, 21);
		scene.init("03");
	}
	else if (actualLvl == 3) {
		scene.chgpyrpos(3, 19);
		scene.init("04");
	}
	else if (actualLvl == 4) {
		scene.chgpyrpos(1, 19);
		scene.init("05");
	}
	else if (actualLvl == 5) {
		scene.chgpyrpos(1, 19);
		scene.init("06");
	}
	else if (actualLvl == 6) {
		scene.chgpyrpos(1, 18);
		scene.init("07");
	}
	else if (actualLvl == 7) {
		scene.chgpyrpos(1, 22);
		scene.init("08");
	}
	else if (actualLvl == 8) {
		scene.chgpyrpos(3, 22);
		scene.init("09");
	}
	else if (actualLvl == 9) {
		scene.chgpyrpos(3, 22);
		scene.init("10");
	}
	else if (actualLvl == 10) {
		scene.chgpyrpos(3, 22);
		scene.init("10");
	}
}

int Game::getInitialX() {
	return scene.getInitialX();
}

int Game::getInitialY() {
	return scene.getInitialY();
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





