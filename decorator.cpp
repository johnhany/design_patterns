#include <iostream>
#include <string>
#include <vector>


using namespace std;


class Network {
protected:
    vector<bool> layers;
public:
    Network() {}
    Network(int depth) {
        while (depth--)
            layers.push_back(true);
    }
    virtual ~Network() { cout << "Network destroyed" << endl; }
    virtual string train() const = 0;
};

class TrainableNetwork : public Network {
public:
    TrainableNetwork(int depth) : Network(depth) {}

    string train() const final {
        string rst = "";
        for (bool i : layers)
            rst += to_string(i);
        return rst;
    }
};

// Cannot override TrainableNetwork::train()
/*
class FineTunedNetwork : public TrainableNetwork {
public:
    string train() const {}
};
*/

class Decorator : public Network {
protected:
    Network* network;
public:
    Decorator(Network* net) : network(net) {}

    string train() const override {
        return this->network->train();
    }
};

class FineTuned : public Decorator {
public:
    FineTuned(Network* net): Decorator(net) {}

    string train() const override {
        string base = this->network->train();
        int depth = base.size();
        for (int i = 0; i < depth-1; i++)
            base[i] = '0';
        base[depth-1] = '1';
        return base;
    }
};

class ObjectDetection : public FineTuned {
public:
    ObjectDetection(Network* net): FineTuned(net) {}

    string train() const override {
        string base = this->network->train();
        base.push_back('1');
        base.push_back('1');
        return base;
    }
};


void train_api(Network* network) {
    cout << "Layers that will be trained: " << network->train() << endl;
}


int main() {
    cout << "Train a base model" << endl;
    Network* base_model = new TrainableNetwork(3);
    train_api(base_model);

    cout << "Fine-tune the base model" << endl;
    Network* fine_tuned = new FineTuned(base_model);
    train_api(fine_tuned);

    cout << "Train an object detection model based on fine-tuned" << endl;
    Network* obj_det = new ObjectDetection(fine_tuned);
    train_api(obj_det);

    delete base_model;
    delete fine_tuned;
    delete obj_det;

    return 0;
}