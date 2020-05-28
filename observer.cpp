#include <iostream>
#include <string>
#include <list>


using namespace std;


class DeviceNode {
public:
    virtual ~DeviceNode() {};
    virtual void pullGrad(int grad) = 0;
};


class MasterNode {
public:
    virtual ~MasterNode() {};
    virtual void attach(DeviceNode* device) = 0;
    virtual void detach(DeviceNode* device) = 0;
    virtual void publishGrad() = 0;
};


class RealMasterNode : public MasterNode {
private:
    int grad = 1;
    list<DeviceNode*> devices;
public:
    void attach(DeviceNode* device) override {
        cout << "[Master] Add a new device node" << endl;
        this->devices.push_back(device);
    }

    void detach(DeviceNode* device) override {
        cout << "[Master] Remove a device node" << endl;
        this->devices.remove(device);
    }

    void publishGrad() override {
        cout << "[Master] Publishing new grads to device nodes" << endl;
        for (auto& p : this->devices)
            p->pullGrad(this->grad);
    }
};


class RealDeviceNode : public DeviceNode {
private:
    int grad = 0;
    RealMasterNode& master;
public:
    RealDeviceNode(RealMasterNode& master) : master(master) {
        this->imReadyForNewGrad();
    }
    virtual ~RealDeviceNode() {}

    void pullGrad(int grad) override {
        this->grad += grad;
    }

    void imReadyForNewGrad() {
        this->master.attach(this);
    }

    void imNotReadyForNewGrad() {
        this->master.detach(this);
    }

    string getGrad() {
        return to_string(this->grad);
    }
};


int main() {
    RealMasterNode* master = new RealMasterNode();
    RealDeviceNode* device1 = new RealDeviceNode(*master);
    RealDeviceNode* device2 = new RealDeviceNode(*master);
    RealDeviceNode* device3 = new RealDeviceNode(*master);

    master->publishGrad();

    cout << "Device1 is slow. Not receiving new grads for now" << endl;
    device1->imNotReadyForNewGrad();
    cout << "Device2 is slow. Not receiving new grads for now" << endl;
    device2->imNotReadyForNewGrad();

    master->publishGrad();

    RealDeviceNode* device4 = new RealDeviceNode(*master);
    cout << "Device4 is slow. Not receiving new grads for now" << endl;
    device4->imNotReadyForNewGrad();
    cout << "Device1 is ready to receive new grads" << endl;
    device1->imReadyForNewGrad();

    master->publishGrad();

    cout << "Device1: " << device1->getGrad() << endl;
    cout << "Device2: " << device2->getGrad() << endl;
    cout << "Device3: " << device3->getGrad() << endl;
    cout << "Device4: " << device4->getGrad() << endl;

    delete master;
    delete device1;
    delete device2;
    delete device3;
    delete device4;
    return 0;
}