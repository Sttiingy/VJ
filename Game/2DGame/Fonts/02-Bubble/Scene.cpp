#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"




#define SCREEN_X 36
#define SCREEN_Y 28

int INIT_PLAYER_X_TILES = 1;
int INIT_PLAYER_Y_TILES = 20;

int INIT_FRUIT_X_TILES = 31;
int INIT_FRUIT_Y_TILES = 14;

int INIT_WALK_X_TILES = 0;
int INIT_WALK_Y_TILES = 0;


int currentLvl;


Scene::Scene()
{
	map = NULL;
	player = NULL;
	fruit = NULL;
	walk = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (fruit != NULL)
		delete fruit;
}


void Scene::init(string lvl)
{
	initShaders();
//<<<<<<< HEAD
	//map = TileMap::createTileMap("levels/level04.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
//=======
	map = TileMap::createTileMap("levels/level"+lvl+".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	currentLvl = atoi(lvl.c_str());
//>>>>>>> cf757dd9cd1d45c37b559c0828dd30072d267fd2
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	fruit = new Fruit();
	fruit->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	fruit->setPosition(glm::vec2(INIT_FRUIT_X_TILES * map->getTileSize(), INIT_FRUIT_Y_TILES * map->getTileSize()));
	fruit->setTileMap(map);

	walk = new Walk();
	walk->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	walk->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	walk->setTileMap(map);

}

void Scene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	fruit->render();
	walk->render();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	fruit->update(deltaTime, player);
	walk->update(deltaTime, player);

}

void Scene::chgpyrpos(int x, int y) {
	INIT_PLAYER_X_TILES = x;
	INIT_PLAYER_Y_TILES = y;
}

void Scene::setFruitPos(int x, int y) {
	INIT_FRUIT_X_TILES = x;
	INIT_FRUIT_Y_TILES = y;
}

void Scene::setWalkPos(int x, int y) {
	INIT_WALK_X_TILES = INIT_PLAYER_X_TILES;
	INIT_WALK_Y_TILES = INIT_PLAYER_X_TILES;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

int Scene::getInitialX() {
	return INIT_PLAYER_X_TILES * map->getTileSize();
}

int Scene::getInitialY() {
	return INIT_PLAYER_Y_TILES * map->getTileSize();
}

int Scene::getActualLvl() {
	return currentLvl;
}


