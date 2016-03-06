#ifndef EVOLUTION
#define EVOLUTION

#include <iostream>
#include <string>
#include <vector>
#include "../neuronNetwork/NeuronNetwork.hpp"

#define EGALITARY
//#define FAVORITISM

class Evolution{

	private:
		std::vector<NeuronNetwork> brains;
		int nbCreaMax;

		vector<NeuronNetwork> egalitary();
		vector<NeuronNetwork> favoritism();

	public:
		Evolution(std::vector<NeuronNetwork> brains, int nbCreaMax);
		vector<NeuronNetwork> evolve();
};

#endif
