#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "Sound.h"

#define DASH_ANGLE_STEP 4
#define JUMP_ANGLE_STEP 4
#define DASH_HEGIHT 96
#define JUMP_HEIGHT 96
#define FALL_STEP 4

int counter = 0;


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, DEATH_LEFT, DEATH_RIGHT, LOOK_UP, WIN, CLIMB
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	bJumping = false;
	bDashing = false;
	bBouncing = false;
	death = false;
	godMode = false;
	dashGodMode = false;
	win = false;
	bWallJumping = false;
	wallJumpLeft = false;
	spritesheet.loadFromFile("images/Texture.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(22, 32), glm::vec2(0.2f, 0.1f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(9);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.1f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.4f, 0.1f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f, 0.0f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.4f, 0.0f));

		sprite->setAnimationSpeed(DEATH_LEFT, 8);
		sprite->addKeyframe(DEATH_LEFT, glm::vec2(0.f, 0.2f));
		sprite->addKeyframe(DEATH_LEFT, glm::vec2(0.2f, 0.2f));
		sprite->addKeyframe(DEATH_LEFT, glm::vec2(0.4f, 0.2f));
		sprite->addKeyframe(DEATH_LEFT, glm::vec2(0.6f, 0.2f));
		sprite->addKeyframe(DEATH_LEFT, glm::vec2(0.8f, 0.2f));


		sprite->setAnimationSpeed(DEATH_RIGHT, 8);
		sprite->addKeyframe(DEATH_RIGHT, glm::vec2(0.f, 0.3f));
		sprite->addKeyframe(DEATH_RIGHT, glm::vec2(0.2f, 0.3f));
		sprite->addKeyframe(DEATH_RIGHT, glm::vec2(0.4f, 0.3f));
		sprite->addKeyframe(DEATH_RIGHT, glm::vec2(0.6f, 0.3f));
		sprite->addKeyframe(DEATH_RIGHT, glm::vec2(0.8f, 0.3f));

		sprite->setAnimationSpeed(LOOK_UP, 8);
		sprite->addKeyframe(LOOK_UP, glm::vec2(0.f, 0.4f));

		sprite->setAnimationSpeed(WIN, 8);
		sprite->addKeyframe(WIN, glm::vec2(0.0f, 0.5f));
		sprite->addKeyframe(WIN, glm::vec2(0.2f, 0.5f));
		sprite->addKeyframe(WIN, glm::vec2(0.4f, 0.5f));
		sprite->addKeyframe(WIN, glm::vec2(0.6f, 0.5f));
		sprite->addKeyframe(WIN, glm::vec2(0.6f, 0.5f));

		sprite->setAnimationSpeed(CLIMB, 8);
		sprite->addKeyframe(CLIMB, glm::vec2(0.2f, 0.4f));
		sprite->addKeyframe(CLIMB, glm::vec2(0.4f, 0.4f));
		sprite->addKeyframe(CLIMB, glm::vec2(0.6f, 0.4f));

		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));	
}

void Player::update(int deltaTime){
	sprite->update(deltaTime);
	if (win) {
		if (counter == 0) Sound::instance().back2LifeEffect();
		if (sprite->animation() != WIN) sprite->changeAnimation(WIN);
		counter++;
		if (counter == 32) {
			win = false;
			Game::instance().goNextLvl(Game::instance().getActualLvl());
			posPlayer.x = Game::instance().getInitialX();
			posPlayer.y = Game::instance().getInitialY();
			sprite->changeAnimation(STAND_RIGHT);
			Sound::instance().back2LifeEffect();
			counter = 0;
		}
	}
	else {
		if (Game::instance().getKey('g')) godMode = !godMode;
		if (Game::instance().getKey('d')) dashGodMode = !dashGodMode;
		if (godMode) death = false;
		if (death) {
			if(counter == 0)Sound::instance().DeathEffect();
			if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT) {
				if (sprite->animation() != DEATH_LEFT) sprite->changeAnimation(DEATH_LEFT);
			}
			else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT) {
				if (sprite->animation() != DEATH_RIGHT) sprite->changeAnimation(DEATH_RIGHT);
			}
			else if (sprite->animation() == LOOK_UP)sprite->animation() != DEATH_RIGHT;
			
			counter++;
			if (counter == 32) {
				death = false;
				posPlayer.x = Game::instance().getInitialX();
				posPlayer.y = Game::instance().getInitialY();
				sprite->changeAnimation(STAND_RIGHT);
				Sound::instance().back2LifeEffect();
				counter = 0;
			}
		}
		else {
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				if (sprite->animation() != LOOK_UP && !bClimbing) sprite->changeAnimation(LOOK_UP);
				if (bDashing) {
					posPlayer.y -= 6;
				}
				if (map->collisionMoveUp(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bDashing, win)) {
					posPlayer.y += 6;
					if (bDashing) {
						bDashing = false;
					}
				}
			}
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !bWallJumping) {
				if (sprite->animation() != MOVE_LEFT && !bClimbing) sprite->changeAnimation(MOVE_LEFT);
				posPlayer.x -= 2;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(22, 32), death, bDashing)) {
					posPlayer.x += 2;
					if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing)) {
						if (!bClimbing) sprite->changeAnimation(STAND_LEFT);
						if (bDashing) {
							bDashing = false;
						}
						bClimbing = false;
					}
					else if(!bBouncing){
						if (sprite->animation() != CLIMB) sprite->changeAnimation(CLIMB);
						bClimbing = true;
						wallJumpLeft = true;
						bounceAngle = 0;
					}
				}
			}
			if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !bWallJumping) {
				if (sprite->animation() != MOVE_RIGHT && !bClimbing) sprite->changeAnimation(MOVE_RIGHT);
				posPlayer.x += 2;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(22, 32), death, bDashing)) {
					posPlayer.x -= 2;
					if(!bClimbing) sprite->changeAnimation(STAND_RIGHT);
					if (bDashing) {
						bDashing = false;
					}
					else if(!bBouncing){
						if (sprite->animation() != CLIMB) sprite->changeAnimation(CLIMB);
						bClimbing = true;
						wallJumpLeft = false;
						bounceAngle = 0;
					}
				}
			}

			if (sprite->animation() == MOVE_LEFT && !Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !bClimbing) sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT && !Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !bClimbing) sprite->changeAnimation(STAND_RIGHT);
			else if(sprite->animation() == LOOK_UP && !Game::instance().getSpecialKey(GLUT_KEY_UP) && !bClimbing) sprite->changeAnimation(STAND_RIGHT);

			if (bJumping) {
				jumpAngle += JUMP_ANGLE_STEP;
				int currentY = posPlayer.y;
				if (jumpAngle == 180)
				{
					bJumping = false;
					posPlayer.y = startY;
				}
				else {
					posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
					if (jumpAngle > 90) {
						bJumping = false;
						if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing)) {
							posPlayer.y = currentY;
						}
					}
					else bJumping = !map->collisionMoveUp(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bDashing, win);
				}
			}
			if (bDashing) {
				if (dashAngle == 48) {
					bDashing = false;
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
					posPlayer.y -= 6;
					dashAngle += DASH_ANGLE_STEP;
					if (map->collisionMoveUp(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bDashing, win)) {
						posPlayer.y += DASH_ANGLE_STEP;
						bDashing = false;
					}
				}
				else if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT) {
					posPlayer.x -= DASH_ANGLE_STEP;
					dashAngle += DASH_ANGLE_STEP;
					if (map->collisionMoveLeft(posPlayer, glm::ivec2(22, 32), death, bDashing)) {
						posPlayer.x += DASH_ANGLE_STEP;
						dashAngle += DASH_ANGLE_STEP;
					}
				}
				else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT) {
					posPlayer.x += DASH_ANGLE_STEP;
					dashAngle += DASH_ANGLE_STEP;
					if (map->collisionMoveRight(posPlayer, glm::ivec2(22, 32), death, bDashing)) {
						posPlayer.x -= DASH_ANGLE_STEP;
					}
				}
			}
			if (bBouncing) {
				bounceAngle += JUMP_ANGLE_STEP;
				int currentY = posPlayer.y;
				if (bounceAngle == 180)
				{
					bBouncing = false;
					posPlayer.y = startY;
				}
				else {
					posPlayer.y = int(startY - 96 * sin(3.14159f * bounceAngle / 180.f));
					if (bounceAngle > 90) {
						bBouncing = false;
						if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing)) {
							posPlayer.y = currentY;
						}
					}
					else bBouncing = !map->collisionMoveUp(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bDashing, win);
				}
			}
			if (bWallJumping) {
				bounceAngle += JUMP_ANGLE_STEP;
				if (wallJumpLeft) posPlayer.x += 2;
				else posPlayer.x -= 2;
				int currentY = posPlayer.y;
				if (bounceAngle == 180)
				{
					bWallJumping = false;
					posPlayer.y = startY;
				}
				else {
					posPlayer.y = int(startY - 96 * sin(3.14159f * bounceAngle / 180.f));
					if (bounceAngle > 90) {
						bWallJumping = false;
						if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing)) {
							posPlayer.y = currentY;
						}
					}
					else bWallJumping = !map->collisionMoveUp(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bDashing, win);
					if (map->collisionMoveRight(posPlayer, glm::ivec2(22, 32), death, bDashing)) {
						bWallJumping = false;
					}
					if (map->collisionMoveLeft(posPlayer, glm::ivec2(22, 32), death, bDashing)) {
						bWallJumping = false;
					}
				}
			}
			else {//Estoy cayendo
				if (bClimbing && !bBouncing) {
					if (sprite->animation() != CLIMB) sprite->changeAnimation(CLIMB);
					posPlayer.y += 1;
					if(map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing)) posPlayer.y -= 1;
					if (Game::instance().getKey('x') && !bBouncing) {
						Sound::instance().jumpEffect();
						bClimbing = false;
						bWallJumping = true;
						jumpAngle = 0;
						startY = posPlayer.y;
					}
				}
				if (!bDashing && !bClimbing) posPlayer.y += FALL_STEP;
				if (Game::instance().getKey('c') && canDash) {
					Sound::instance().dashEffect();
					bDashing = true;
					dashAngle = 0;
					if (!dashGodMode) canDash = false;
					bJumping = false;
				}
				if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing)) {
					//bClimbing = false;
					if (bBouncing) {
						bounceAngle = 0;
						startY = posPlayer.y;
						canDash = true;
					}
					canDash = true;
					posPlayer.y -= FALL_STEP;
					if (Game::instance().getKey('x') && !bBouncing) {
						Sound::instance().jumpEffect();
						bJumping = true;
						jumpAngle = 0;
						startY = posPlayer.y;
					}
					if (Game::instance().getKey('c') && canDash) {
						Sound::instance().dashEffect();
						bDashing = true;
						dashAngle = 0;
						canDash = false;
						startY = posPlayer.y;
						bJumping = false;
					}
				}
				if (!Game::instance().getSpecialKey(GLUT_KEY_LEFT) && bClimbing) {
					if (!map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing)) {
						bClimbing = false;
					}
					else if (sprite->animation() != CLIMB) sprite->changeAnimation(CLIMB);
				}
				if (!Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && bClimbing) {
					if (!map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing)) {
						bClimbing = false;
					}
					else if (sprite->animation() != CLIMB) sprite->changeAnimation(CLIMB);
				}
			}
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