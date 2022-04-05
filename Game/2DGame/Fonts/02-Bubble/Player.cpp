#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define DASH_ANGLE_STEP 4
#define JUMP_ANGLE_STEP 4
#define DASH_HEGIHT 96
#define JUMP_HEIGHT 96
#define FALL_STEP 4

int vy = 0;


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	bDashing = false;
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	//Me muvo izquierda
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if (bDashing) posPlayer.x -= 2;
		//Colisiono
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			if(bDashing) posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	//Me muevo derecha
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if (bDashing) posPlayer.x += 2;
		//Colisiono
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			if (bDashing) posPlayer.x -= 2;
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	//Dasheo si puedo
	else if (Game::instance().getSpecialKey(GLUT_KEY_F1) && canDash) {
		canDash = false;
		bDashing = true;
		dashAngle = 0;
		startY = posPlayer.y;
	}
	//Estoy quieto
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	//Estoy saltando
	if (bJumping) {
		//Dasheo si puedo
		if (Game::instance().getSpecialKey(GLUT_KEY_F1) && canDash) {
			canDash = false;
			bDashing = true;
			dashAngle = 0;
			bJumping = false;
			startY = posPlayer.y;
		}
		//Sigo con el salto
		else {
			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180)
			{
				bJumping = false;
				posPlayer.y = startY;
			}
			else {
				posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
				if (jumpAngle > 90) {
					bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
				}

				else if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 8), &posPlayer.y)) {
					jumpAngle = 180 - jumpAngle;
					bJumping = false;
					if (Game::instance().getSpecialKey(GLUT_KEY_F1) && canDash) {
						canDash = false;
						bDashing = true;
						dashAngle = 0;
						bJumping = false;
						startY = posPlayer.y;
					}
				}
			}
		}
		
	}	
	//Estoy dasheando
	if (bDashing) {
		dashAngle += DASH_ANGLE_STEP;
		if (dashAngle == 210)
		{
			bDashing = false;
			posPlayer.y = startY;
		}
		else {
			posPlayer.y = int(startY - 96 * sin(3.14159f * dashAngle / 210.f));
			if (dashAngle > 90) {
				bDashing = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
			}

			else if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 8), &posPlayer.y)) {
				dashAngle = 180 - dashAngle;
				bDashing = false;
			}
		}
	}
	//Estoy cayendo
	else { 
		posPlayer.y += FALL_STEP;
		//vy++;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
			canDash = true;
			vy = 0;
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
			if (Game::instance().getSpecialKey(GLUT_KEY_F1) && canDash) {
				canDash = false;
				bDashing = true;
				dashAngle = 0;
				startY = posPlayer.y;
			}
		}
		if (Game::instance().getSpecialKey(GLUT_KEY_F1) && canDash) {
			canDash = false;
			bDashing = true;
			dashAngle = 0;
			startY = posPlayer.y;
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




