#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Flag.h"
#include "Game.h"
#include "Sound.h"
#include "Player.h"




enum FlagAnims
{
	STAND, WIN
};

int anime_count_win = 0;

void Flag::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/Flag.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.25f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(STAND, 8);
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.75f, 0.f));

	sprite->setAnimationSpeed(WIN, 8);
	sprite->addKeyframe(WIN, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(WIN, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(WIN, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(WIN, glm::vec2(0.75f, 0.f));

	sprite->changeAnimation(STAND);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFlag.x), float(tileMapDispl.y + posFlag.y)));
}

void Flag::setPosition(const glm::vec2 &pos)
{
	posFlag = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFlag.x), float(tileMapDispl.y + posFlag.y)));
}

void Flag::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Flag::render() {
	sprite->render();
}

void Flag::update(int deltaTime, Player *player) {
	sprite->update(deltaTime);
	if (posFlag.x / 16 == player->getPlayerX() && posFlag.y / 16 == player->getPlayerY()) {
		Sound::instance().stopMusic();
		if (sprite->animation() != WIN) sprite->changeAnimation(WIN);
	}
	if (posFlag.x / 16 == player->getPlayerX() && posFlag.y / 16 == player->getPlayerY() + 1) {
		Sound::instance().stopMusic();
		if (sprite->animation() != WIN) sprite->changeAnimation(WIN);
	}
	if (sprite->animation() == WIN) anime_count_win++;
	if (anime_count_win == 1) Sound::instance().GameOverEffect();;
	if (anime_count_win == 350) {
		player->GameOver();
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFlag.x), float(tileMapDispl.y + posFlag.y)));
}

