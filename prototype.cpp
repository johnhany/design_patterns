#include <iostream>
#include <string>
#include <unordered_map>


using namespace std;


enum Device {
    DEVICE_CPU = 0,
    DEVICE_GPU
};


class Model {
protected:
    string model_name;
    string device_id;
public:
    Model() {}
    Model(string name) : model_name(name) {}
    virtual ~Model() { cout << "Model destroyed" << endl; }

    virtual Model* clone() const = 0;
    virtual void runOnDevice(string id) {
        this->device_id = id;
        cout << "Run " + model_name + " on device " + device_id << endl;
    }
    virtual string getTech() const = 0;
};

class CPUModel : public Model {
private:
    string cpuOptimizationTech;
public:
    CPUModel(string name, string tech) : Model(name), cpuOptimizationTech(tech) {}
    ~CPUModel() { cout << "CPU model destroyed" << endl; }
    Model* clone() const override {
        return new CPUModel(*this);
    }
    string getTech() const override {
        return cpuOptimizationTech;
    }
};

class GPUModel : public Model {
private:
    string gpuOptimizationTech;
public:
    GPUModel(string name, string tech) : Model(name), gpuOptimizationTech(tech) {}
    ~GPUModel() { cout << "GPU model destroyed" << endl; }
    Model* clone() const override {
        return new GPUModel(*this);
    }
    string getTech() const override {
        return gpuOptimizationTech;
    }
};


class PrototypeFactory {
private:
    std::unordered_map<Device, Model*, std::hash<int>> prototypes;

public:
    PrototypeFactory() {
        prototypes[Device::DEVICE_CPU] = new CPUModel("CPU Model", "AVX2");
        prototypes[Device::DEVICE_GPU] = new GPUModel("GPU Model", "CUDA");
    }
    ~PrototypeFactory() {
        delete prototypes[Device::DEVICE_CPU];
        delete prototypes[Device::DEVICE_GPU];
    }

    Model *createPrototype(Device device) {
        return prototypes[device]->clone();
    }
};


void train_api(PrototypeFactory &prototype_factory) {
    cout << "I want to create a CPU model" << endl;
    Model* model = prototype_factory.createPrototype(Device::DEVICE_CPU);
    model->runOnDevice("cpu:0");
    cout << "Optimization technology: " + model->getTech() << endl;
    delete model;

    cout << "I want to create a GPU model" << endl;
    model = prototype_factory.createPrototype(Device::DEVICE_GPU);
    model->runOnDevice("gpu:1");
    cout << "Optimization technology: " + model->getTech() << endl;
    delete model;
}


int main() {
    PrototypeFactory *prototype_factory = new PrototypeFactory();
    train_api(*prototype_factory);
    delete prototype_factory;

    return 0;
}