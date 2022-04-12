#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Fruit.h"
//#include "Walk.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(string lvl);
	void update(int deltaTime);
	void render();
	int getInitialX();
	int getInitialY();
	int getActualLvl();
	void changeGodModeState();
	void changeDashGodModeState();
	void chgpyrpos(int x, int y);
	void setFruitPos(int x, int y);
	void setWalkPos(int x, int y);

private:
	void initShaders();

	

private:
	TileMap *map;
	Player *player;
	Fruit *fruit;
	//Walk *walk;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

