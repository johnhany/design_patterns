#include <iostream>
#include <string>


using namespace std;


class Network {
public:
    virtual ~Network() { cout << "Network destroyed" << endl; }
    virtual string getNetworkType() const = 0;
};


class CNN : public Network {
public:
    string getNetworkType() const override {
        return "CNN";
    }
};

class GAN : public Network {
public:
    string getNetworkType() const override {
        return "GAN";
    }
};


class Trainer {
public:
    virtual ~Trainer(){ cout << "Trainer destroyed" << endl; };
    virtual Network* createNetwork() const = 0;

    void whatModelAmITraining() const {
        Network* network = this->createNetwork();
        cout << "I am training a " + network->getNetworkType() + " model." << endl;
        delete network;
        return;
    }
};


class CNNTrainer : public Trainer {
public:
    Network* createNetwork() const override {
        return new CNN();
    }
};

class GANTrainer : public Trainer {
public:
    Network* createNetwork() const override {
        return new GAN();
    }
};


void train_api(const Trainer& trainer) {
    trainer.whatModelAmITraining();
}


int main() {
    cout << "I'm going to train a CNN model." << endl;
    Trainer* trainer1 = new CNNTrainer();
    train_api(*trainer1);

    cout << "I'm going to train a GAN model." << endl;
    Trainer* trainer2 = new GANTrainer();
    train_api(*trainer2);

    delete trainer1;
    delete trainer2;

    return 0;
}
