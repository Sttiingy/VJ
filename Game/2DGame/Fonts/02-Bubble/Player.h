#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void keyboard(unsigned char key, int x, int y);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	
private:
	bool bJumping, dashGodMode, bDashing, canDash, death, godMode, bBouncing, bClimbing, win, wallJumpLeft;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY, dashAngle, bounceAngle, actualLvl, bWallJumping;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};


#endif // _PLAYER_INCLUDE


