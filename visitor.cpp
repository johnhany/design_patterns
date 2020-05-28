#include <iostream>
#include <string>
#include <vector>


using namespace std;


class ConvLayer;
class LinearLayer;

class Visitor {
public:
    virtual void visitConvLayer(const ConvLayer* layer) const = 0;
    virtual void visitLinearLayer(const LinearLayer* layer) const = 0;
};


class Layer {
public:
    virtual ~Layer() {}
    virtual void accept(Visitor* visitor) const = 0;
};


class ConvLayer : public Layer {
public:
    void accept(Visitor* visitor) const override {
        visitor->visitConvLayer(this);
    }

    string getParam() const {
        return "[x,y,z,w]";
    }
};

class LinearLayer : public Layer {
public:
    void accept(Visitor* visitor) const override {
        visitor->visitLinearLayer(this);
    }

    string getParam() const {
        return "[x,y]";
    }
};


class calcFlopsVisitor : public Visitor {
public:
    void visitConvLayer(const ConvLayer* layer) const override {
        cout << "Calculating the FLOPS of convolution layer: " << layer->getParam() << endl;
    }
    void visitLinearLayer(const LinearLayer* layer) const override {
        cout << "Calculating the FLOPS of linear layer: " << layer->getParam() << endl;
    }
};

class visParamVisitor : public Visitor {
public:
    void visitConvLayer(const ConvLayer* layer) const override {
        cout << "Visualizing the kernels of convolution layer: " << layer->getParam() << endl;
    }
    void visitLinearLayer(const LinearLayer* layer) const override {
        cout << "Visualizing the weight of linear layer: " << layer->getParam() << endl;
    }
};


class Network {
private:
    vector<Layer*> layers;
public:
    virtual ~Network() {
        for (Layer* p : this->layers)
            delete p;
    }
    void addLayer(Layer* layer) {
        this->layers.push_back(layer);
    }

    void visitorHelper(Visitor* visitor) {
        for (Layer* p : this->layers)
            p->accept(visitor);
    }
};


int main() {
    Network* network = new Network();
    network->addLayer(new ConvLayer());
    network->addLayer(new ConvLayer());
    network->addLayer(new LinearLayer());
    network->addLayer(new LinearLayer());

    calcFlopsVisitor* visitor1 = new calcFlopsVisitor();
    network->visitorHelper(visitor1);

    visParamVisitor* visitor2 = new visParamVisitor();
    network->visitorHelper(visitor2);

    delete visitor1;
    delete visitor2;
    delete network;
    return 0;
}