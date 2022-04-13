#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"




#define SCREEN_X 36
#define SCREEN_Y 28

int INIT_PLAYER_X_TILES = 2;
int INIT_PLAYER_Y_TILES = 20;

int INIT_FRUIT_X_TILES = 31;
int INIT_FRUIT_Y_TILES = 14;

int INIT_FLAG_X_TILES = 16;
int INIT_FLAG_Y_TILES = 12;

int INIT_GLOBO_X_TILES = 0;
int INIT_GLOBO_Y_TILES = 0;

int INIT_GLOBO2_X_TILES = 0;
int INIT_GLOBO2_Y_TILES = 0;


string currentLvl;


Scene::Scene()
{
	map = NULL;
	player = NULL;
	fruit = NULL;
	//walk = NULL;
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
	currentLvl = lvl;
	initShaders();
	map = TileMap::createTileMap("levels/level"+lvl+".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	if (currentLvl != "Menu" && currentLvl != "Inicio" && currentLvl != "Credits"  && currentLvl != "Ins") {
		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		player->setTileMap(map);
	}
	if (lvl == "11") {
		flag = new Flag();
		flag->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		flag->setPosition(glm::vec2(INIT_FLAG_X_TILES * map->getTileSize(), INIT_FLAG_Y_TILES * map->getTileSize()));
		flag->setTileMap(map);
	}

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	fruit = new Fruit();
	fruit->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	fruit->setPosition(glm::vec2(INIT_FRUIT_X_TILES * map->getTileSize(), INIT_FRUIT_Y_TILES * map->getTileSize()));
	fruit->setTileMap(map);

	globo = new Globo();
	globo->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	globo->setPosition(glm::vec2(INIT_GLOBO_X_TILES * map->getTileSize(), INIT_GLOBO_Y_TILES * map->getTileSize()));
	globo->setTileMap(map);

	globo2 = new Globo();
	globo2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	globo2->setPosition(glm::vec2(INIT_GLOBO2_X_TILES * map->getTileSize(), INIT_GLOBO2_Y_TILES * map->getTileSize()));
	globo2->setTileMap(map);

	//walk = new Walk();
	//walk->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	//walk->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	//walk->setTileMap(map);

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
	if (currentLvl != "Menu" && currentLvl != "Inicio" && currentLvl != "Credits"  && currentLvl != "Ins") {
		player->render();
	}
	if (currentLvl != "11" && currentLvl != "Inicio" && currentLvl != "Ins" && currentLvl != "Menu" && currentLvl != "Credits") {
		fruit->render();
	}
	if (currentLvl == "11") flag->render();
	if (currentLvl == "08" || currentLvl == "09" || currentLvl == "10") {
		globo->render();
		globo2->render();
	}
	//walk->render();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (currentLvl != "Menu" && currentLvl != "Inicio" && currentLvl != "Credits"  && currentLvl != "Ins") {
		player->update(deltaTime);
		fruit->update(deltaTime, player);
		if (currentLvl == "08" || currentLvl == "09" || currentLvl == "10") {
			globo->update(deltaTime, player);
			globo2->update(deltaTime, player);
		}
	}
	if (currentLvl == "11") {
		flag->update(deltaTime, player);
	}
	//walk->update(deltaTime, player);

}

void Scene::chgpyrpos(int x, int y) {
	INIT_PLAYER_X_TILES = x;
	INIT_PLAYER_Y_TILES = y;
}

void Scene::setFruitPos(int x, int y) {
	INIT_FRUIT_X_TILES = x;
	INIT_FRUIT_Y_TILES = y;
}

void Scene::setFlagPos(int x, int y) {
	INIT_FLAG_X_TILES = x;
	INIT_FLAG_Y_TILES = y;
}

void Scene::setGloboPos(int x, int y) {
	INIT_GLOBO_X_TILES = x;
	INIT_GLOBO_Y_TILES = y;
}

void Scene::setGlobo2Pos(int x, int y) {
	INIT_GLOBO2_X_TILES = x;
	INIT_GLOBO2_Y_TILES = y;
}

/*
void Scene::setWalkPos(int x, int y) {
	INIT_WALK_X_TILES = INIT_PLAYER_X_TILES;
	INIT_WALK_Y_TILES = INIT_PLAYER_X_TILES;
}
*/

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

string Scene::getActualLvl() {
	return currentLvl;
}

void Scene::changeGodModeState() {
	player->changeGodMode();
}


void Scene::changeDashGodModeState() {
	player->changeDashGodMode();
}


