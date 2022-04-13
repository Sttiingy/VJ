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
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, DEATH_LEFT, DEATH_RIGHT, LOOK_UP, WIN, JUMP_LEFT, JUMP_RIGHT, JUMP_UP, CLIMB_LEFT, CLIMB_RIGHT
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
	sprite->setNumberAnimations(13);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.4f, 0.6f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.4f, 0.6f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.6f, 0.6f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.6f, 0.6f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.6f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.6f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.2f, 0.6f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.2f, 0.6f));
		
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

		sprite->setAnimationSpeed(JUMP_LEFT, 8);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.4f, 0.4f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 8);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.2f, 0.4f));

		sprite->setAnimationSpeed(JUMP_UP, 8);
		sprite->addKeyframe(JUMP_UP, glm::vec2(0.6f, 0.4f));	

		sprite->setAnimationSpeed(CLIMB_LEFT, 8);
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(0.2f, 0.7f));

		sprite->setAnimationSpeed(CLIMB_RIGHT, 8);
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(0.f, 0.7f));




	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));	
}

void Player::update(int deltaTime){
	sprite->update(deltaTime);
	if (win) {
		if (counter == 0) Sound::instance().WinEffect();
		if (sprite->animation() != WIN) sprite->changeAnimation(WIN);
		counter++;
		if (counter == 32) {
			win = false;
			Game::instance().goNextLvl(Game::instance().getActualLvl());
			posPlayer.x = Game::instance().getInitialX();
			posPlayer.y = Game::instance().getInitialY();
			sprite->changeAnimation(STAND_RIGHT);
			counter = 0;
		}
	}
	else {
		if (godMode) death = false;
		if (death) {
			bDashing = false;
			bJumping = false;
			bWallJumping = false;
			bClimbing = false;
			if (counter == 0)Sound::instance().DeathEffect();
			if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT) {
				if (sprite->animation() != DEATH_LEFT) sprite->changeAnimation(DEATH_LEFT);
			}
			else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT || sprite->animation() != DEATH_RIGHT) {
				if (sprite->animation() != DEATH_RIGHT) sprite->changeAnimation(DEATH_RIGHT);
			}
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
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !bWallJumping) {
				posPlayer.x -= 2;
				if (sprite->animation() != MOVE_LEFT && !bJumping && !bClimbing) sprite->changeAnimation(MOVE_LEFT);
				if (bJumping && sprite->animation() != JUMP_LEFT)sprite->changeAnimation(JUMP_LEFT);
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(22, 32), death, bDashing)) {
					posPlayer.x += 2;
					if (sprite->animation() != STAND_LEFT && !bClimbing)sprite->changeAnimation(STAND_LEFT);
					if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing, godMode)) {
						if (bDashing) {
							bDashing = false;
						}
						if (bClimbing) bClimbing = false;
					}
					else if (!bBouncing) {
						bClimbing = true;
						wallJumpLeft = true;
						bounceAngle = 0;
					}
				}
			}
			if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !bWallJumping) {
				posPlayer.x += 2;
				if (sprite->animation() != MOVE_RIGHT && !bJumping && !bClimbing) sprite->changeAnimation(MOVE_RIGHT);
				if (bJumping && sprite->animation() != JUMP_RIGHT)sprite->changeAnimation(JUMP_RIGHT);
				if (map->collisionMoveRight(posPlayer, glm::ivec2(22, 32), death, bDashing)) {
					posPlayer.x -= 2;
					if(sprite->animation() != STAND_RIGHT && !bClimbing)sprite->changeAnimation(STAND_RIGHT);
					if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing, godMode)) {
						if (!bClimbing) sprite->changeAnimation(STAND_RIGHT);
						if (bDashing) {
							bDashing = false;
						}
						if (bClimbing) bClimbing = false;
					}
					else if (!bBouncing) {
						bClimbing = true;
						wallJumpLeft = false;
						bounceAngle = 0;
					}
				}
			}
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				if(bJumping && sprite->animation() != JUMP_UP && sprite->animation() != JUMP_LEFT && sprite->animation() != JUMP_RIGHT) sprite->changeAnimation(JUMP_UP);
				if (!Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !Game::instance().getSpecialKey(GLUT_KEY_LEFT) && sprite->animation() != LOOK_UP && !bJumping)
					sprite->changeAnimation(LOOK_UP);
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
			if(!Game::instance().getSpecialKey(GLUT_KEY_UP) && sprite->animation() == LOOK_UP) sprite->changeAnimation(STAND_RIGHT);
			if(!Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && sprite->animation() == MOVE_RIGHT) sprite->changeAnimation(STAND_RIGHT);
			if (!Game::instance().getSpecialKey(GLUT_KEY_LEFT) && sprite->animation() == MOVE_LEFT) sprite->changeAnimation(STAND_LEFT);
			if (!Game::instance().getSpecialKey(GLUT_KEY_UP) && sprite->animation() == JUMP_UP) sprite->changeAnimation(STAND_RIGHT);
			if (bWallJumping) {
				bounceAngle += JUMP_ANGLE_STEP;
				if (wallJumpLeft) {
					posPlayer.x += 2;
					if (sprite->animation() != JUMP_RIGHT)sprite->changeAnimation(JUMP_RIGHT);
				}
				else {
					posPlayer.x -= 2;
					if (sprite->animation() != JUMP_LEFT)sprite->changeAnimation(JUMP_LEFT);
				}
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
						if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing, godMode)) {
							posPlayer.y = currentY;
						}
					}
					else if (map->collisionMoveUp(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, godMode, win)) {
						posPlayer.y = currentY;
						bWallJumping = false;
					}
					if (map->collisionMoveRight(posPlayer, glm::ivec2(22, 32), death, godMode)) {
						bWallJumping = false;
						if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
							bClimbing = true;
						}
					}
					if (map->collisionMoveLeft(posPlayer, glm::ivec2(22, 32), death, godMode)) {
						bWallJumping = false;
						if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
							bClimbing = true;
						}
					}
				}
			}
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
						if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing, godMode)) {
							posPlayer.y = currentY;
						}
					}
					else if (map->collisionMoveUp(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, godMode, win)) {
						posPlayer.y = currentY;
						bJumping = false;
					}
				}
			}
			if (bDashing) {
				if (dashAngle == 48) {
					bDashing = false;
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
					posPlayer.y -= 4;
					dashAngle += DASH_ANGLE_STEP;
					if (map->collisionMoveUp(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, godMode, win)) {
						posPlayer.y += DASH_ANGLE_STEP;
						bDashing = false;
					}
				}
				else if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT || sprite->animation() == JUMP_LEFT) {
					posPlayer.x -= DASH_ANGLE_STEP;
					dashAngle += DASH_ANGLE_STEP;
					if (map->collisionMoveLeft(posPlayer, glm::ivec2(22, 32), death, godMode)) {
						if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
							bClimbing = true;
						}
						posPlayer.x += DASH_ANGLE_STEP;
						bDashing = false;
					}
				}
				else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT || sprite->animation() == JUMP_RIGHT) {
					posPlayer.x += DASH_ANGLE_STEP;
					dashAngle += DASH_ANGLE_STEP;
					if (map->collisionMoveRight(posPlayer, glm::ivec2(22, 32), death, godMode)) {
						if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
							bClimbing = true;
						}
						posPlayer.x -= DASH_ANGLE_STEP;
						bDashing = false;
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
						if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing, godMode)) {
							posPlayer.y = currentY;
						}
					}
					else if (map->collisionMoveUp(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, godMode, win)) {
						posPlayer.y = currentY;
						bBouncing = false;
					}
				}
			}
			else {//Estoy cayendo
				if (bClimbing && !bBouncing) {
					posPlayer.y += 1;
					if (sprite->animation() != CLIMB_RIGHT && wallJumpLeft) {
						sprite->changeAnimation(CLIMB_RIGHT);
						//sprite climb
					}
					if (sprite->animation() != CLIMB_LEFT && !wallJumpLeft) {
						sprite->changeAnimation(CLIMB_LEFT);
						//sprite climb
					}
					if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing, godMode)) posPlayer.y -= 1;
					if (Game::instance().getKey('x')) {
						Sound::instance().jumpEffect();
						bClimbing = false;
						bWallJumping = true;
						jumpAngle = 0;
						startY = posPlayer.y;
					}
				}
				if (!bDashing && !bClimbing && !bWallJumping && !bJumping) posPlayer.y += FALL_STEP;
				if (Game::instance().getKey('c') && canDash) {
					Sound::instance().dashEffect();
					bDashing = true;
					dashAngle = 0;
					if(!dashGodMode) canDash = false;
					bJumping = false;
				}
				if (map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing, godMode)) {
					if (bBouncing) {
						bounceAngle = 0;
						startY = posPlayer.y;
						canDash = true;
					}
					if (!bDashing) canDash = true;
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
						if(!dashGodMode) canDash = false;
						startY = posPlayer.y;
						bJumping = false;
					}
				}
				if (!Game::instance().getSpecialKey(GLUT_KEY_LEFT) && bClimbing) {
					if (!map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing, godMode)) {
						bClimbing = false;
					}
				}
				if (!Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && bClimbing) {
					if (!map->collisionMoveDown(posPlayer, glm::ivec2(22, 32), &posPlayer.y, death, bBouncing, godMode)) {
						bClimbing = false;
					}
				}
			}
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render() {
	sprite->render();
}

void Player::GameOver() {
	Game::instance().goNextLvl(Game::instance().getActualLvl());
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

int Player::getPlayerX() {
	return (posPlayer.x + 16)  / 16;
}

int Player::getPlayerY() {
	return (posPlayer.y) / 16;
}

bool Player::isDead() {
	return death;
}

void Player::changeGodMode() {
	if(!godMode) Sound::instance().godModeOn();
	else Sound::instance().godModeOff();
	godMode = !godMode;
}

void Player::changeDashGodMode() {
	if (!dashGodMode) Sound::instance().dashGodModeOn();
	else Sound::instance().dashGodModeOff();
	dashGodMode = !dashGodMode;
}

void Player::setCanDashTrue() {
	canDash = true;
}