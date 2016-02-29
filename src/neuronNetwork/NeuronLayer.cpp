#include "NeuronLayer.hpp"

using namespace std;

NeuronLayer::NeuronLayer(int nbNeuron, int nbInputPerNeuron) : nbNeuron(nbNeuron){
	for(int i = 0; i < nbNeuron; i++){
		neurons.push_back(Neuron(nbInputPerNeuron));
	}
}

vector<double> NeuronLayer::stimule(vector<double> stim){
	vector<double> results;
	for(int i = 0; i < nbNeuron; i++){
		results.push_back(neurons[i].stimule(stim));
	}

	return results;
}
