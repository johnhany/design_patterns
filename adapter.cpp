#include <iostream>
#include <string>
#include <algorithm>


using namespace std;


class PyTorch {
public:
    virtual ~PyTorch() = default;

    virtual string getParameters() const {
        return "NCHW";
    }
};


class ModelLoader {
public:
    virtual ~ModelLoader() = default;

    void loadTrainedModel(const string& param) const {
        if (param == "NCHW")
            cout << "I can run this model correctly." << endl;
        else
            cout << "I cannot recognize this model." << endl;
    }
};


class TensorFlow {
public:
    virtual ~TensorFlow() = default;

    virtual string getTFParameters() const {
        return "NHWC";
    }
};


class Adapter : public PyTorch {
private:
    TensorFlow* tensorflow;
public:
    Adapter(TensorFlow* tf) : tensorflow(tf) {}

    string getParameters() const override {
        string param = this->tensorflow->getTFParameters();
        std::swap(param[2], param[3]);
        std::swap(param[1], param[2]);
        return param;
    }
};


void load_model(const PyTorch* model) {
    string param = model->getParameters();
    ModelLoader* loader = new ModelLoader();
    loader->loadTrainedModel(param);
}


int main() {
    cout << "Loading a PyTorch model..." << endl;
    PyTorch* pytorch = new PyTorch;
    load_model(pytorch);

    cout << "Loading a TensorFlow model..." << endl;
    TensorFlow* tensorflow = new TensorFlow();
    //load_model(TensorFlow);   // won't compile

    cout << "Loading a TensorFlow model using Adapter..." << endl;
    Adapter* adapter = new Adapter(tensorflow);
    load_model(adapter);

    delete pytorch;
    delete tensorflow;
    delete adapter;

    return 0;
}