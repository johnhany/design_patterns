#include <iostream>
#include <string>


using namespace std;


class DeviceNode {
public:
    virtual void pushGrad(int grad) = 0;
};

class RealDeviceNode : public DeviceNode {
public:
    void pushGrad(int grad) override {
        cout << "Pushing grad value " + to_string(grad) + " from a real device node" << endl;
    }
};

class ProxyDeviceNode : public DeviceNode {
private:
    RealDeviceNode* real_device;
    int accum_grad = 0;

    bool isItTimeToPush() const {
        if (accum_grad < 3) {
            cout << "  Not yet..." << endl;
            return false;
        } else {
            cout << "  Okay, it's time" << endl;
            return true;
        }
    }

    void printLog() const {
        cout << "  Printing some logs" << endl;
    }
public:
    ProxyDeviceNode(RealDeviceNode* device) : real_device(new RealDeviceNode(*device)) {}
    ~ProxyDeviceNode() {
        delete real_device;
    }

    void pushGrad(int grad) override {
        accum_grad += grad;
        if (this->isItTimeToPush()) {
            this->real_device->pushGrad(accum_grad);
            accum_grad = 0;
        }
        this->printLog();
    }
};


void train_api(DeviceNode& device) {
    for (int i = 0; i < 6; i++) {
        device.pushGrad(1);
    }
}


int main() {
    cout << "Executing grad push with a real device:" << endl;
    RealDeviceNode* real_device = new RealDeviceNode();
    train_api(*real_device);

    cout << "Executing grad push via a proxy device:" << endl;
    ProxyDeviceNode* proxy_device = new ProxyDeviceNode(real_device);
    train_api(*proxy_device);

    delete real_device;
    delete proxy_device;
    return 0;
}