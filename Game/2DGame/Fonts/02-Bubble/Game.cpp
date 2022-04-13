#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Sound.h"
#include <irrKlang.h>

void Game::init()
{
	bPlay = true;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	scene.init("Inicio");
	Sound::instance().playMusic("sounds/MenuTheme.wav");
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
		scene.setFruitPos(31, 14);
		scene.setFlowerPos(20, 19);
		Sound::instance().playMusic("sounds/SongTheme.wav");
		scene.init("01");
	}
	if (key == 50) {//lvl 2
		scene.chgpyrpos(2, 22);
		scene.setFruitPos(3, 9);
		scene.setFlowerPos(18, 8);
		Sound::instance().playMusic("sounds/SongTheme.wav");
		scene.init("02");
	}
	if (key == 51) {//lvl 3
		scene.chgpyrpos(2, 21);
		scene.setFruitPos(12, 9);
		scene.setFlowerPos(32, 13);
		Sound::instance().playMusic("sounds/SongTheme.wav");
		scene.init("03");
	}
	if (key == 52) {//lvl 4
		scene.chgpyrpos(3, 18);
		scene.setFruitPos(6, 5);
		scene.setFlowerPos(32, 18);
		Sound::instance().playMusic("sounds/SongTheme.wav");
		scene.init("04");
	}
	if (key == 53) {//lvl 5
		scene.chgpyrpos(2, 19);
		scene.setFruitPos(31, 10);
		scene.setFlowerPos(11, 5);
		Sound::instance().playMusic("sounds/SongTheme.wav");
		scene.init("05");
	}
	if (key == 54) {//lvl 6
		scene.chgpyrpos(2, 19);
		scene.setFruitPos(31, 10);
		scene.setFlowerPos(33, 22);
		Sound::instance().playMusic("sounds/SongTheme.wav");
		scene.init("06");
	}
	if (key == 55) {//lvl 7
		scene.chgpyrpos(2, 18);
		scene.setFruitPos(14, 10);
		scene.setFlowerPos(14, 22);
		Sound::instance().playMusic("sounds/SongTheme.wav");
		scene.init("07");
	}
	if (key == 56) {//lvl 8
		scene.chgpyrpos(3, 22);
		scene.setFruitPos(4, 3);
		scene.setGloboPos(28, 12);
		scene.setFlowerPos(22, 5);
		Sound::instance().playMusic("sounds/SongTheme.wav");
		scene.init("08");
	}
	if (key == 57) {//lvl 9
		scene.chgpyrpos(3, 22);
		Sound::instance().playMusic("sounds/SongTheme.wav");
		scene.setFruitPos(31, 21);
		scene.setGloboPos(5, 8);
		scene.setFlowerPos(28, 8);
		scene.init("09");
	}
	if (key == 48) {//lvl 10
		scene.chgpyrpos(3, 22);
		scene.setFruitPos(8, 7);
		scene.setGloboPos(16, 20);
		scene.setFlowerPos(23, 22);
		Sound::instance().playMusic("sounds/SongTheme.wav");
		scene.init("10");
	}
	keys[key] = true;
	if (Game::instance().getKey('g') && Game::instance().getActualLvl() != "Menu" && Game::instance().getActualLvl() != "Inicio"
		&& Game::instance().getActualLvl() != "Ins" && Game::instance().getActualLvl() != "Credits") scene.changeGodModeState();

	if (Game::instance().getKey('d') && Game::instance().getActualLvl() != "Menu" && Game::instance().getActualLvl() != "Inicio"
		&& Game::instance().getActualLvl() != "Ins" && Game::instance().getActualLvl() != "Credits") scene.changeDashGodModeState();

	if (Game::instance().getKey('i') && Game::instance().getActualLvl() == "Menu") {
		scene.init("Ins");
		Sound::instance().SelectEffect();
	}
	if (Game::instance().getKey('x') && Game::instance().getActualLvl() == "Inicio") {
		Sound::instance().SelectEffect();
		scene.init("Menu");
	}
	if (Game::instance().getKey('i') && Game::instance().getActualLvl() == "Credits") {
		Sound::instance().SelectEffect();
		scene.init("Inicio");
		Sound::instance().playMusic("sounds/MenuTheme.wav");
	}
	if (Game::instance().getKey('a') && Game::instance().getActualLvl() == "Menu") {
		scene.chgpyrpos(2, 20);
		scene.setFruitPos(31, 14);
		scene.setFlowerPos(20, 19);
		scene.init("01");
		Sound::instance().SelectEffect();
		Sound::instance().playMusic("sounds/SongTheme.wav");
	}

	if (Game::instance().getKey('c') && Game::instance().getActualLvl() == "Menu") {
		Sound::instance().SelectEffect();
		scene.init("Credits");
	}
	if (Game::instance().getKey('b') && Game::instance().getActualLvl() == "Ins") {
		Sound::instance().SelectEffect();
		scene.init("Menu");
	}

	if (Game::instance().getKey('b') && Game::instance().getActualLvl() == "Credits") {
		Sound::instance().SelectEffect();
		scene.init("Menu");
	}
}

string Game::getActualLvl() {
	return scene.getActualLvl();
}

void Game::goNextLvl(string actualLvl) {
	if (actualLvl == "01") {
		scene.chgpyrpos(2, 22);
		scene.setFruitPos(3, 9);
		scene.setFlowerPos(18, 8);
		scene.init("02");
	}
	else if (actualLvl == "02") {
		scene.chgpyrpos(2, 21);
		scene.setFruitPos(12, 9);
		scene.setFlowerPos(32, 13);
		scene.init("03");
	}
	else if (actualLvl == "03") {
		scene.chgpyrpos(3, 18);
		scene.setFruitPos(6, 5);
		scene.setFlowerPos(32, 18);
		scene.init("04");
	}
	else if (actualLvl == "04") {
		scene.chgpyrpos(2, 19);
		scene.setFruitPos(31, 10);
		scene.setFlowerPos(11, 5);
		scene.init("05");
	}
	else if (actualLvl == "05") {
		scene.chgpyrpos(2, 19);
		scene.setFruitPos(31, 10);
		scene.setFlowerPos(33, 22);
		scene.init("06");
	}
	else if (actualLvl == "06") {
		scene.chgpyrpos(2, 18);
		scene.setFruitPos(14, 10);
		scene.setFlowerPos(14, 22);
		scene.init("07");
	}
	else if (actualLvl == "07") {
		scene.chgpyrpos(1, 22);
		scene.setFruitPos(4, 3);
		scene.setGloboPos(28, 12);
		scene.setFlowerPos(22, 5);
		scene.init("08");
	}
	else if (actualLvl == "08") {
		scene.chgpyrpos(3, 22);
		scene.setFruitPos(31, 21);
		scene.setGloboPos(5, 9);
		scene.setFlowerPos(28, 8);
		scene.init("09");
	}
	else if (actualLvl == "09") {
		scene.chgpyrpos(3, 22);
		scene.setFruitPos(8, 7);
		scene.setGloboPos(16, 20);
		scene.setFlowerPos(23, 22);
		scene.init("10");
	}
	else if (actualLvl == "10") {
		scene.setFlowerPos(25, 20);
		scene.init("11");
	}
	else if (actualLvl == "11") {
		scene.chgpyrpos(3, 21);
		Sound::instance().playMusic("sounds/CreditsTheme.wav");
		scene.init("Credits");
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





