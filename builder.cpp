#include <iostream>
#include <string>
#include <vector>


using namespace std;


class Network {
public:
    vector<string> layers;
    void showAllLayers() const {
        cout << "All layers in network: ";
        for (auto& i : layers)
            cout << i << " ";
        cout << endl;
    }
};


class Builder {
public:
    virtual ~Builder() { cout << "Builder destroyed" << endl; }
    virtual void createLinearLayer() const = 0;
    virtual void createConvLayer() const = 0;
    virtual void createLossLayer() const = 0;
};


class ClassificationBuilder : public Builder {
private:
    Network* network;
public:
    ClassificationBuilder() {
        this->reset();
    }
    ~ClassificationBuilder() {
        delete network;
    }

    void reset() {
        this->network = new Network();
    }
    Network* getNetwork() {
        Network* network = this->network;
        this->reset();
        return network;
    }

    void createLinearLayer() const override {
        this->network->layers.push_back("Linear");
    }

    void createConvLayer() const override {
        this->network->layers.push_back("Conv");
    }

    void createLossLayer() const override {
        this->network->layers.push_back("Loss");
    }
};


class Director {
private:
    Builder* builder;
public:
    void setBuilder(Builder* builder) {
        this->builder = builder;
    }

    void buildLinearModel() {
        this->builder->createLinearLayer();
        this->builder->createLossLayer();
    }

    void buildCNNModel() {
        this->builder->createConvLayer();
        this->builder->createConvLayer();
        this->builder->createLinearLayer();
        this->builder->createLinearLayer();
        this->builder->createLossLayer();
    }
};


void train_api(Director& director) {
    ClassificationBuilder* builder = new ClassificationBuilder();
    director.setBuilder(builder);

    cout << "I want to train a linear model:" << endl;
    director.buildLinearModel();

    Network* net = builder->getNetwork();
    net->showAllLayers();
    delete net;

    cout << "I want to train a CNN model:" << endl;
    director.buildCNNModel();

    net = builder->getNetwork();
    net->showAllLayers();
    delete net;

    cout << "I want to train a MLP model:" << endl;
    builder->createLinearLayer();
    builder->createLinearLayer();
    builder->createLinearLayer();
    builder->createLossLayer();

    net = builder->getNetwork();
    net->showAllLayers();
    delete net;

    delete builder;
    return;
}


int main(){
    Director* director= new Director();
    train_api(*director);
    delete director;

    return 0;
}
