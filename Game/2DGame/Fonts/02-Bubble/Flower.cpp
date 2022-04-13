#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Flower.h"
#include "Game.h"
#include "Sound.h"
#include "Player.h"




enum FlowerAnims
{
	STAND, PASS
};

int anime_count_pass = 0;

void Flower::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/Flower.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(25, 32), glm::vec2(0.5f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(STAND, 8);
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.0f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(STAND, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(PASS, 8);
	sprite->addKeyframe(PASS, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(PASS, glm::vec2(0.0f, 0.f));
	sprite->addKeyframe(PASS, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(PASS, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(PASS, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(PASS, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(PASS, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(PASS, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(PASS, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(PASS, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(PASS, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(PASS, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(STAND);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFlower.x), float(tileMapDispl.y + posFlower.y)));
}

void Flower::setPosition(const glm::vec2 &pos)
{
	posFlower = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFlower.x), float(tileMapDispl.y + posFlower.y)));
}

void Flower::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Flower::render() {
	sprite->render();
}

void Flower::update(int deltaTime, Player *player) {
	sprite->update(deltaTime);
	if (posFlower.x / 16 == player->getPlayerX() && posFlower.y / 16 == player->getPlayerY()) {
		if (sprite->animation() != PASS) sprite->changeAnimation(PASS);
	}
	if (posFlower.x / 16 == player->getPlayerX() && posFlower.y / 16 == player->getPlayerY() + 1) {
		if (sprite->animation() != PASS) sprite->changeAnimation(PASS);
	}
	if (sprite->animation() == PASS) {
		anime_count_pass++;
	}
	if (anime_count_pass == 1) {
		Sound::instance().FlowerEffect();
	}
	if (anime_count_pass == 70) {
		anime_count_pass = 0;
		sprite->changeAnimation(STAND);
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFlower.x), float(tileMapDispl.y + posFlower.y)));
}

