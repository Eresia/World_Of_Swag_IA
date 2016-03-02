#include "Controller.hpp"

using namespace std;

Controller::Controller(Map& map, int nbCrea, int turnMax) : map(map), nbCrea(nbCrea), nbCreaMax(nbCrea*(nbCrea - 1)), nbGen(0), turn(0), turnMax(turnMax), idCounter(0){

	if(nbCrea < MIN_CREA){
		throw NotEnoughCreatureException(to_string(MIN_CREA) + " or more creature expected, " + to_string(nbCrea) + " given");
	}

	createCreatures();
	//printNbGen();
}

void Controller::update(){
	MapObjective& mapObj = (MapObjective&) map;
	Position obj(mapObj.getObjective().getX()*SIZE_IMAGE_H, mapObj.getObjective().getY()*SIZE_IMAGE_W);
	if(turn < turnMax){

		for(int i = 0; i < nbCreaMax; i++){
			creatures[i]->think();
		}
		turn++;
	}
	else{
		vector<NeuronNetwork> bestBrains;
		vector<NeuronNetwork> newBrains;
		Evolution* evolution;
		for(int i = 0; i < nbCreaMax; i++){
			creatures[i]->getPosition() -= obj;
		}

		partial_sort(creatures.begin(), creatures.begin() + nbCrea, creatures.end(), Creature::comparePosition);
		for(int i = 0; i < nbCrea; i++){
			bestBrains.push_back(creatures[i]->getBrain());
		}
		evolution = new Evolution(bestBrains);
		newBrains = evolution->evolve();
		createCreatures(newBrains);
		turn = 0;
		nbGen++;
		//printNbGen();
	}
}

bool Controller::doneObjective(){
	MapObjective& mapObj = (MapObjective&) map;
	int xObj = mapObj.getObjective().getX();
	int yObj = mapObj.getObjective().getY();
	bool result = false;
	for(int i = 0; i < nbCreaMax; i++){
		int x = creatures[i]->getPosition().getX() / SIZE_IMAGE_H;
		int y = creatures[i]->getPosition().getY() / SIZE_IMAGE_W;
		if((x == xObj) && (y == yObj)){
			result = true;
			break;
		}
	}
	return result;
}

void Controller::createCreatures(){
	creatures.clear();
	for(int i = 0; i < nbCreaMax; i++){
		Position pos;
		Creature* crea;
		pos = getSpawn(i);
		crea = new Creature(idCounter, pos);
		addFeatures(crea);
		idCounter++;
		creatures.push_back(crea);
	}
}

void Controller::createCreatures(vector<NeuronNetwork> brains){
	if((int) brains.size() != nbCreaMax){
		throw NotEnoughCreatureException("Evolution failed, " + to_string(brains.size()) + " brains given, " + to_string(nbCreaMax) + " attempt");
	}

	creatures.clear();
	for(int i = 0; i < nbCreaMax; i++){
		Position pos;
		Creature* crea;
		pos = getSpawn(i);

		crea = new Creature(idCounter, pos, brains[i]);
		addFeatures(crea);
		idCounter++;
		creatures.push_back(crea);
	}

}

void Controller::addFeatures(Creature* creature){
	MapObjective& mapObj = (MapObjective&) map;
	creature->addInputFeature(new ObjectiveDirection(mapObj.getObjective().getXRef(), SIZE_IMAGE_H, creature->getPosition().getXRef()));
	creature->addInputFeature(new ObjectiveDirection(mapObj.getObjective().getYRef(), SIZE_IMAGE_W, creature->getPosition().getYRef()));
	creature->addOutputFeature(new Movement());
	creature->addOutputFeature(new Movement());
}

Position Controller::getSpawn(int number){
	MapObjective& mapObj = (MapObjective&) map;
	Position pos;
	double spawnX;
	double spawnY;

	/*do{
		spawnY = rand() % (NB_CASE_W-1);
		spawnX = rand() % (NB_CASE_H-1);
	}while(map.getCaseMaterial(spawnX, spawnY) == FoodMaterial::getInstance());

	pos = Position(spawnX*SIZE_IMAGE_H, spawnY*SIZE_IMAGE_W);*/

	spawnX = (mapObj.getObjective().getX() + 10*sin(number*((M_PI/10) + (M_PI/20))))*SIZE_IMAGE_H;
	spawnY = (mapObj.getObjective().getY() + 10*cos(number*((M_PI/10) + (M_PI/20))))*SIZE_IMAGE_W;
	pos = Position(spawnX, spawnY);
	return pos;
}

int Controller::getNbCrea() const{
	return nbCrea;
}

int Controller::getNbCreaMax() const{
	return nbCreaMax;
}

Position& Controller::getPositionCrea(int crea){
	return creatures[crea]->getPosition();
}

int Controller::getRotationCrea(int crea) const{
	return creatures[crea]->getRotation();
}

void Controller::printNbGen(){
	cout << "Generation " << to_string(nbGen) << endl;
}

int Controller::getNbGen(){
	return nbGen;
}
