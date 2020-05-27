#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>


using namespace std;


struct BackboneNetwork {
    vector<string> layers;

    BackboneNetwork(std::initializer_list<string> names) {
        for (const string& s : names)
            layers.push_back(s);
    }

    string train() const {
        int n = layers.size();
        string output = "";
        for (int i = 0; i < n; i++) {
            output += layers[i];
            if (i != n-1)
                output += "+";
        }
        return output;
    }
};


struct FineTunePart {
    string linear_layer;

    FineTunePart(string name) : linear_layer(name) {}
};


class ObjectDetection {
private:
    BackboneNetwork* backbone;
public:
    ObjectDetection(const BackboneNetwork* network) : backbone(new BackboneNetwork(*network)) {}
    ObjectDetection(const ObjectDetection& other) : backbone(new BackboneNetwork(*other.backbone)) {}
    ~ObjectDetection() {
        delete backbone;
    }
    BackboneNetwork* getBackbone() const {
        return backbone;
    }
    string train(const FineTunePart& fine_tune) const {
        return this->backbone->train() + "+" + fine_tune.linear_layer;
    }
};


class FlyweightFactory {
private:
    unordered_map<string, ObjectDetection> flyweights;
    string getKey(const BackboneNetwork& backbone) const {
        return backbone.train();
    }
public:
    FlyweightFactory(std::initializer_list<BackboneNetwork> backbones) {
        for (const BackboneNetwork& bb : backbones)
            this->flyweights.insert(make_pair(this->getKey(bb), ObjectDetection(&bb)));
    }

    ObjectDetection getFlyweight(const BackboneNetwork& backbone) {
        string key = this->getKey(backbone);
        if (this->flyweights.find(key) == this->flyweights.end()) {
            this->flyweights.insert(make_pair(key, ObjectDetection(&backbone)));
        }
        return this->flyweights.at(key);
    }

    void printAllFlyweights() const {
        cout << "All Flyweights:" << endl;
        for (auto& itm : this->flyweights)
            cout << itm.first << endl;
    }
};


void train_api(FlyweightFactory& factory, std::initializer_list<string> base_layers, string final_layer) {
    const ObjectDetection& obj_det = factory.getFlyweight(base_layers);
    string rst = obj_det.train({final_layer});
    cout << "Fine-tuning a network:" << endl;
    cout << rst << endl;
}


int main()
{
    FlyweightFactory *factory = new FlyweightFactory({{"A1", "A2", "A3"}, {"B1", "B2", "B3"}});
    factory->printAllFlyweights();

    train_api(*factory, {"A1", "A2", "A3"}, "X1");
    train_api(*factory, {"A1", "A2", "A3"}, "Y1");
    train_api(*factory, {"B1", "B2", "B3"}, "X1");
    train_api(*factory, {"C1", "C2", "C3"}, "X1");

    factory->printAllFlyweights();

    delete factory;

    return 0;
}