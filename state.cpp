#include <iostream>


using namespace std;


class Network;

class State {
protected:
    Network* network;
public:
    virtual ~State() {}

    void setNetwork(Network* net) {
        this->network = net;
    }

    virtual void train() = 0;
    virtual string name() = 0;
};


class Network {
private:
    State* state;
public:
    Network(State* state) {
        this->switchState(state);
    }
    ~Network() {
        delete state;
    }

    void switchState(State* state) {
        cout << "[Network] Switch to state: " << state->name() << endl;
        if (this->state != nullptr)
            delete this->state;
        this->state = state;
        this->state->setNetwork(this);
    }

    void train() {
        this->state->train();
    }
};


class FullTrainState : public State {
public:
    void train() override {
        cout << "Training all the layers in network" << endl;
    }
    string name() override {
        return "Train-From-Scratch";
    }
};


class FineTuneState : public State {
public:
    void train() override {
        cout << "Training only the last layer in network" << endl;
    }
    string name() override {
        return "Fine-Tuning";
    }
};


class HyperParamSearchState : public State {
public:
    void train() override {
        cout << "Searching the optim hyper-params in network" << endl;
        this->network->switchState(new FullTrainState());
    }
    string name() override {
        return "Hyper-Param-Search";
    }
};


int main() {
    FullTrainState* full_train = new FullTrainState();
    Network* network = new Network(full_train);
    network->train();

    HyperParamSearchState* hyper_search = new HyperParamSearchState();
    network->switchState(hyper_search);
    network->train();

    FineTuneState* fine_tune = new FineTuneState();
    network->train();
    network->switchState(fine_tune);
    network->train();

    delete full_train;
    delete hyper_search;
    delete fine_tune;
    delete network;
    return 0;
}