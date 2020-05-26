#include <iostream>
#include <string>


using namespace std;


class Dataset {
public:
    virtual ~Dataset() { cout << "Dataset destroyed" << endl; }
    virtual string getDatasetName() const = 0;
};

class ImageNet : public Dataset {
public:
    string getDatasetName() const override {
        return "ImageNet";
    }
};

class CelebA : public Dataset {
public:
    string getDatasetName() const override {
        return "CelebA";
    }
};


class Network {
public:
    virtual ~Network() { cout << "Network destroyed" << endl; }
    virtual string getNetworkType() const = 0;
    virtual string giveMeADataset(const Dataset& dataset) const = 0;
};

class CNN : public Network {
public:
    string getNetworkType() const override {
        return "CNN";
    }
    string giveMeADataset(const Dataset& dataset) const override {
        const string dataset_name = dataset.getDatasetName();
        return "I am training a CNN with " + dataset_name;
    }
};

class GAN : public Network {
public:
    string getNetworkType() const override {
        return "GAN";
    }
    string giveMeADataset(const Dataset& dataset) const override {
        const string dataset_name = dataset.getDatasetName();
        return "I am training a GAN with " + dataset_name;
    }
};


class Trainer {
public:
    virtual ~Trainer(){ cout << "Trainer destroyed" << endl; };
    virtual Network* createNetwork() const = 0;
    virtual Dataset* createDataset() const = 0;
};


class CNNTrainer : public Trainer {
public:
    Network* createNetwork() const override {
        return new CNN();
    }
    Dataset* createDataset() const override {
        return new ImageNet();
    }
};

class GANTrainer : public Trainer {
public:
    Network* createNetwork() const override {
        return new GAN();
    }
    Dataset* createDataset() const override {
        return new CelebA();
    }
};


void train_api(const Trainer& trainer) {
    const Dataset* dataset = trainer.createDataset();
    const Network* network = trainer.createNetwork();
    cout << "I want to train a " + network->getNetworkType() + " model." << endl;
    cout << network->giveMeADataset(*dataset) << endl;
    delete dataset;
    delete network;
    return;
}


int main() {
    CNNTrainer* trainer1 = new CNNTrainer();
    train_api(*trainer1);
    delete trainer1;

    GANTrainer* trainer2 = new GANTrainer();
    train_api(*trainer2);
    delete trainer2;

    return 0;
}