#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Sound.h"
#include <irrKlang.h>

void Game::init()
{
	Sound::instance().playMusic("sounds/SongTheme.wav");
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
	if (key == 49) {//lvl 1
		scene.chgpyrpos(2, 20);
		//scene.setFruitPos(31, 14);
		scene.init("12");
	}
	if (key == 50) {//lvl 2
		scene.chgpyrpos(2, 22);
		scene.setFruitPos(3, 9);
		scene.init("02");
	}
	if (key == 51) {//lvl 3
		scene.chgpyrpos(2, 21);
		scene.setFruitPos(12, 9);
		scene.init("03");
	}
	if (key == 52) {//lvl 4
		scene.chgpyrpos(3, 18);
		scene.setFruitPos(6, 5);
		scene.init("04");
	}
	if (key == 53) {//lvl 5
		scene.chgpyrpos(2, 19);
		scene.setFruitPos(31, 10);
		scene.init("05");
	}
	if (key == 54) {//lvl 6
		scene.chgpyrpos(2, 19);
		scene.setFruitPos(31, 10);
		scene.init("06");
	}
	if (key == 55) {//lvl 7
		scene.chgpyrpos(2, 18);
		scene.setFruitPos(14, 10);
		scene.init("07");
	}
	if (key == 56) {//lvl 8
		scene.chgpyrpos(3, 22);
		scene.setFruitPos(4, 3);
		scene.init("08");
	}
	if (key == 57) {//lvl 9
		scene.chgpyrpos(3, 22);
		scene.init("09");
	}
	if (key == 48) {//lvl 10
		scene.chgpyrpos(3, 22);
		scene.init("10");
	}
	keys[key] = true;
	if (Game::instance().getKey('g')) scene.changeGodModeState();
	if (Game::instance().getKey('d')) scene.changeDashGodModeState();
}

int Game::getActualLvl() {
	return scene.getActualLvl();
}

void Game::goNextLvl(int actualLvl) {
	if (actualLvl == 0) {
		scene.chgpyrpos(2, 20);
		scene.setFruitPos(31, 14);
		scene.init("12");
	}
	else if (actualLvl == 1) {
		scene.chgpyrpos(2, 22);
		scene.setFruitPos(3, 9);
		scene.init("02");
	}
	else if (actualLvl == 2) {
		scene.chgpyrpos(2, 21);
		scene.setFruitPos(12, 9);
		scene.init("03");
	}
	else if (actualLvl == 3) {
		scene.chgpyrpos(3, 18);
		scene.setFruitPos(6, 5);
		scene.init("04");
	}
	else if (actualLvl == 4) {
		scene.chgpyrpos(2, 19);
		scene.setFruitPos(31, 10);
		scene.init("05");
	}
	else if (actualLvl == 5) {
		scene.chgpyrpos(2, 19);
		scene.setFruitPos(31, 10);
		scene.init("06");
	}
	else if (actualLvl == 6) {
		scene.chgpyrpos(2, 18);
		scene.setFruitPos(14, 10);
		scene.init("07");
	}
	else if (actualLvl == 7) {
		scene.chgpyrpos(1, 22);
		scene.setFruitPos(4, 3);
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
		scene.init("11");
	}
	else if (actualLvl == 11) {
		scene.chgpyrpos(3, 22);
		scene.init("12");
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





