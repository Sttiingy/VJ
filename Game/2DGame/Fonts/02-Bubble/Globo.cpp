#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Globo.h"
#include "Game.h"
#include "Sound.h"
#include "Player.h"




enum GloboAnims
{
	PLAYER_GETS, DISAPPEAR, STAND
};

int anime_count_globo = 0;

void Globo::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/Globo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.2f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(PLAYER_GETS, 8);
	sprite->addKeyframe(PLAYER_GETS, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(PLAYER_GETS, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(PLAYER_GETS, glm::vec2(0.4f, 0.f));
	sprite->addKeyframe(PLAYER_GETS, glm::vec2(0.6f, 0.f));
	sprite->addKeyframe(PLAYER_GETS, glm::vec2(0.8f, 0.f));

	sprite->setAnimationSpeed(DISAPPEAR, 8);
	sprite->addKeyframe(DISAPPEAR, glm::vec2(0.8f, 0.f));

	sprite->setAnimationSpeed(STAND, 8);
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.2f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.2f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.2f, 0.f));

	sprite->changeAnimation(STAND);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGlobo.x), float(tileMapDispl.y + posGlobo.y)));
}

void Globo::setPosition(const glm::vec2 &pos)
{
	posGlobo = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGlobo.x), float(tileMapDispl.y + posGlobo.y)));
}

void Globo::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Globo::render() {
	sprite->render();
}

void Globo::update(int deltaTime, Player *player) {
	sprite->update(deltaTime);
	if (posGlobo.x / 16 == player->getPlayerX() && posGlobo.y / 16 == player->getPlayerY()) {
		if (sprite->animation() == STAND && sprite->animation() != PLAYER_GETS) sprite->changeAnimation(PLAYER_GETS);
	}
	if (posGlobo.x / 16 == player->getPlayerX() && posGlobo.y / 16 == player->getPlayerY() - 1) {
		if (sprite->animation() == STAND && sprite->animation() != PLAYER_GETS) sprite->changeAnimation(PLAYER_GETS);
	}
	if (sprite->animation() == PLAYER_GETS) ++anime_count_globo;
	if (anime_count_globo == 1) {
		Sound::instance().BaloonEffect();
		player->setCanDashTrue();
	}
	if (player->isDead()) {
		if (sprite->animation() != STAND) sprite->changeAnimation(STAND);
	}
	if (anime_count_globo == 32) {
		sprite->changeAnimation(DISAPPEAR);
		anime_count_globo = 0;
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGlobo.x), float(tileMapDispl.y + posGlobo.y)));
}

