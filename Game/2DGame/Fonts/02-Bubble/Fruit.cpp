#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Fruit.h"
#include "Game.h"
#include "Sound.h"
#include "Player.h"




enum FruitAnims
{
	PLAYER_GETS, DISAPPEAR, STAND
};

int anime_count = 0;

void Fruit::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/Beer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(PLAYER_GETS, 8);
	sprite->addKeyframe(PLAYER_GETS, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(PLAYER_GETS, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(PLAYER_GETS, glm::vec2(0.5f, 0.25f));
	sprite->addKeyframe(PLAYER_GETS, glm::vec2(0.75f, 0.25f));
	sprite->addKeyframe(PLAYER_GETS, glm::vec2(0.75f, 0.25f));
	sprite->addKeyframe(PLAYER_GETS, glm::vec2(0.75f, 0.25f));

	sprite->setAnimationSpeed(DISAPPEAR, 8);
	sprite->addKeyframe(DISAPPEAR, glm::vec2(0.75f, 0.5f));

	sprite->setAnimationSpeed(STAND, 8);
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(STAND);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFruit.x), float(tileMapDispl.y + posFruit.y)));
}

void Fruit::setPosition(const glm::vec2 &pos)
{
	posFruit = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFruit.x), float(tileMapDispl.y + posFruit.y)));
}

void Fruit::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Fruit::render() {
	sprite->render();
}

void Fruit::update(int deltaTime, Player *player) {
	sprite->update(deltaTime);
	if (posFruit.x / 16 == player->getPlayerX() && posFruit.y / 16 == player->getPlayerY()) {
		if (sprite->animation() == STAND && sprite->animation() != PLAYER_GETS) sprite->changeAnimation(PLAYER_GETS);
	}
	if (posFruit.x / 16 == player->getPlayerX() && posFruit.y / 16 == player->getPlayerY() - 1) {
		if (sprite->animation() == STAND && sprite->animation() != PLAYER_GETS) sprite->changeAnimation(PLAYER_GETS);
	}
	if(sprite->animation() == PLAYER_GETS) ++anime_count;
	if(anime_count == 1) Sound::instance().BeerEffect();
	if (anime_count == 32) {
		sprite->changeAnimation(DISAPPEAR);
		anime_count = 0;
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFruit.x), float(tileMapDispl.y + posFruit.y)));
}

