#include <iostream>


using namespace std;


class AbstractModel {
protected:
    virtual void initDataset() const = 0;
    void initDataLoader() const {
        cout << "[AbstractModel] Created a DataLoader with batch size of 64 from Dataset" << endl;
    }
    void initBaseNetwork() const {
        cout << "[AbstractModel] Initialized the base network with pretrained weights" << endl;
    }
    virtual void initFinalLayer() const = 0;
    virtual void initLossFunction() const = 0;
public:
    void init() const {
        this->initDataset();
        this->initDataLoader();
        this->initBaseNetwork();
        this->initFinalLayer();
        this->initLossFunction();
    }
};

class ClassificationModel : public AbstractModel {
protected:
    void initDataset() const override {
        cout << "[Classification] Loaded ImageNet dataset" << endl;
    }
    void initFinalLayer() const override {
        cout << "[Classification] Let's use a linear layer" << endl;
    }
    void initLossFunction() const override {
        cout << "[Classification] Let's use cross-entropy" << endl;
    }
};

class DetectionModel : public AbstractModel {
protected:
    void initDataset() const override {
        cout << "[Detection] Loaded COCO dataset" << endl;
    }
    void initFinalLayer() const override {
        cout << "[Detection] Let's add several layers and train them" << endl;
    }
    void initLossFunction() const override {
        cout << "[Detection] Let's use RetinaLoss" << endl;
    }
};


void init_api(AbstractModel* model) {
    model->init();
}


int main() {
    cout << "I want to initialize a classification model" << endl;
    ClassificationModel* model1 = new ClassificationModel();
    init_api(model1);

    cout << "\nI want to initialize a detection model" << endl;
    DetectionModel* model2 = new DetectionModel();
    init_api(model2);

    delete model1;
    delete model2;
    return 0;
}