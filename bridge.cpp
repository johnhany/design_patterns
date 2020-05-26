#include <iostream>
#include <string>


using namespace std;


class DatasetImplementation {
public:
    virtual ~DatasetImplementation() {}

    virtual string dataPreprocess() const = 0;
};

class Cifar10 : public DatasetImplementation {
public:
    string dataPreprocess() const override {
        return "Cifar10";
    }
};

class ImageNet : public DatasetImplementation {
public:
    string dataPreprocess() const override {
        return "ImageNet";
    }
};


class ModelAbstraction {
protected:
    DatasetImplementation* dataset;
public:
    ModelAbstraction(DatasetImplementation* impl) : dataset(impl) {}
    virtual ~ModelAbstraction() {}

    virtual void train() const {
        cout << "Train base model on " + this->dataset->dataPreprocess() << endl;
    }
};

class RLSearchModel : public ModelAbstraction {
public:
    RLSearchModel(DatasetImplementation* impl) : ModelAbstraction(impl) {}

    void train() const override {
        cout << "Apply Reinforcement Learning search on " + this->dataset->dataPreprocess() << endl;
    }
};

class ESSearchModel : public ModelAbstraction {
public:
    ESSearchModel(DatasetImplementation* impl) : ModelAbstraction(impl) {}

    void train() const override {
        cout << "Apply Evolution Strategy search on " + this->dataset->dataPreprocess() << endl;
    }
};


void train_api(const ModelAbstraction& model) {
    model.train();
}


int main() {
    DatasetImplementation* dataset = new Cifar10();
    ModelAbstraction* model = new ModelAbstraction(dataset);
    train_api(*model);
    delete dataset;
    delete model;

    dataset = new ImageNet();
    model = new ModelAbstraction(dataset);
    train_api(*model);
    delete dataset;
    delete model;

    dataset = new Cifar10();
    model = new RLSearchModel(dataset);
    train_api(*model);
    delete dataset;
    delete model;

    dataset = new ImageNet();
    model = new RLSearchModel(dataset);
    train_api(*model);
    delete dataset;
    delete model;

    dataset = new Cifar10();
    model = new ESSearchModel(dataset);
    train_api(*model);
    delete dataset;
    delete model;

    dataset = new ImageNet();
    model = new ESSearchModel(dataset);
    train_api(*model);
    delete dataset;
    delete model;

    return 0;
}