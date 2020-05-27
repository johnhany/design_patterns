#include <iostream>
#include <string>


using namespace std;


class Dataset {
public:
    void init() const {
        cout << "Dataset initialized" << endl;
    }

    string getBatch() const {
        return "Here's your data mini-batch";
    }
};

class Network {
public:
    void init() const {
        cout << "Network initialized" << endl;
    }

    string optimize() const {
        return "Network optimized for 1 step";
    }

    string predict() const {
        return "Network predicts some results";
    }
};


class TrainerFacade {
protected:
    Dataset* dataset;
    Network* network;
public:
    TrainerFacade(Dataset* data = nullptr, Network* net = nullptr) {
        this->dataset = data ?: new Dataset();
        this->network = net ?: new Network();
    }
    ~TrainerFacade() {
        delete dataset;
        delete network;
    }

    void train() {
        dataset->init();
        network->init();

        for (int i = 0; i < 3; i++) {
            cout << "Iteration " << i << endl;
            string batch = dataset->getBatch();
            cout << batch << endl;
            string logs = network->optimize();
            cout << logs << endl;
        }

        string predict = network->predict();
        cout << predict << endl;
    }
};


void train_api(TrainerFacade* trainer) {
    trainer->train();
}


int main() {
    Dataset* dataset = new Dataset();
    Network* network = new Network();

    TrainerFacade* trainer = new TrainerFacade(dataset, network);
    train_api(trainer);

    delete trainer;
    return 0;
}