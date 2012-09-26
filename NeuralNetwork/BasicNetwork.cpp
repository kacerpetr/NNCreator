#include "BasicNetwork.h"

namespace NeuralNetwork{

BasicNetwork::BasicNetwork(void) : INeuralNetwork(){

}

BasicNetwork::BasicNetwork(const BasicNetwork& obj) : INeuralNetwork(){

}

BasicNetwork::BasicNetwork(const std::string& obj) : INeuralNetwork(){

}

BasicNetwork::~BasicNetwork(void){

}

void BasicNetwork::setWeight(double value, int weight, int neuron, int layer){

}

void BasicNetwork::setNeuron(Neuron obj, int neuron, int layer){

}

void BasicNetwork::setInput(double value, int input){

}

void BasicNetwork::setBias(double value, int neuron, int layer){

}

void BasicNetwork::setBias(double value){

}

double BasicNetwork::getWeight(int weight, int neuron, int layer) const{

}

Neuron BasicNetwork::getNeuron(int neuron, int layer) const{

}

double BasicNetwork::getBias(int neuron, int layer) const{

}

double BasicNetwork::getInput(int input) const{

}

double BasicNetwork::getOutput(int output) const{

}

void BasicNetwork::insertLayer(int position){

}

void BasicNetwork::removeLayer(int position){

}

void BasicNetwork::appendNeuron(Neuron obj){

}

void BasicNetwork::insertNeuron(int position, Neuron obj){

}

void BasicNetwork::removeNeuron(int position){

}

int BasicNetwork::weightCount(int neuron, int layer) const{

}

int BasicNetwork::neuronCount(int layer) const{

}

int BasicNetwork::layerCount() const{

}

int BasicNetwork::inputCount() const{

}

int BasicNetwork::outputCount() const{

}

void BasicNetwork::randomizeWeights(void){

}

std::string BasicNetwork::toString(void) const{

}

}
