#pragma once

#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
class Globo
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	//void keyboard(unsigned char key, int x, int y);
	void render();
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void update(int deltaTime, Player *player);

private:
	glm::ivec2 tileMapDispl, posGlobo;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};