#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Walk.h"
#include "Game.h"
#include "Sound.h"
#include "Player.h"




enum WalkAnims
{
	WALK_LEFT, DISAPPEAR, WALK_RIGHT
};

int lastY = 0;
int lastX = 0;

void Walk::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/Assets.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(WALK_RIGHT, 8);
	sprite->addKeyframe(WALK_RIGHT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(WALK_RIGHT, glm::vec2(0.25f, 0.5f));
	sprite->addKeyframe(WALK_RIGHT, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(DISAPPEAR, 8);
	sprite->addKeyframe(DISAPPEAR, glm::vec2(0.75f, 0.5f));

	sprite->setAnimationSpeed(WALK_LEFT, 8);
	sprite->addKeyframe(WALK_LEFT, glm::vec2(0.f, 0.75f));
	sprite->addKeyframe(WALK_LEFT, glm::vec2(0.25f, 0.75f));
	sprite->addKeyframe(WALK_LEFT, glm::vec2(0.5f, 0.75f));

	sprite->changeAnimation(WALK_LEFT);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posWalk.x), float(tileMapDispl.y + posWalk.y)));
}

void Walk::setPosition(const glm::vec2 &pos)
{
	posWalk = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posWalk.x), float(tileMapDispl.y + posWalk.y)));
}

void Walk::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Walk::render() {
	sprite->render();
}

void Walk::update(int deltaTime, Player *player) {
	sprite->update(deltaTime);
	if (lastY == player->getPlayerY()) {
		if (lastX < player->getPlayerX()) {
			if (sprite->animation() != WALK_RIGHT) sprite->changeAnimation(WALK_RIGHT);
			posWalk.x = player->getPlayerX();
			posWalk.y = player->getPlayerY() + 1;
		}
		else if (lastX > player->getPlayerX()) {
			if (sprite->animation() != WALK_LEFT) sprite->changeAnimation(WALK_LEFT);
			posWalk.x = player->getPlayerX();
			posWalk.y = player->getPlayerY() + 1;
		}
		else if(lastX == player->getPlayerX() || lastX - 1 == player->getPlayerX() || lastX - 1 == player->getPlayerX() + 1){
			//if (sprite->animation() != DISAPPEAR) sprite->changeAnimation(DISAPPEAR);
		}
		
	}
	else {
		//if (sprite->animation() != DISAPPEAR) sprite->changeAnimation(DISAPPEAR);
	}
	lastX = player->getPlayerX();
	lastY= player->getPlayerY();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posWalk.x * 16), float(tileMapDispl.y + posWalk.y * 16)));
}