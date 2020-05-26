#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <random>


using namespace std;


std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 1);


class Classifier {
protected:
    Classifier* parent;
public:
    virtual ~Classifier() { cout << "Classifier destroyed" << endl; }

    void setParent(Classifier* parent) {
        this->parent = parent;
    }
    Classifier* getParent() const {
        return this->parent;
    }

    virtual void add(Classifier* child) {}
    virtual void remove(Classifier* child) {}

    virtual bool isEnsemble() const {
        return false;
    }
    virtual string predict() const = 0;
};

class LeafClassifier : public Classifier {
public:
    string predict() const override {
        int dice_roll = distribution(generator);
        return to_string(dice_roll);
    }
};

class EnsembleClassifier : public Classifier {
protected:
    list<Classifier*> children;
public:
    ~EnsembleClassifier() override {
        for (auto& i : children)
            delete i;
        cout << "  Ensemble destroyed" << endl;
    }
    void add(Classifier* child) override {
        this->children.push_back(child);
        child->setParent(this);
    }
    void remove(Classifier* child) override {
        this->children.remove(child);
        child->setParent(nullptr);
    }
    bool isEnsemble() const override {
        return true;
    }
    string predict() const override {
        string rst = "[";
        for (auto& i : children) {
            rst += i->predict();
        }
        rst += "]";
        return rst;
    }
};


void predict_api(Classifier* classifier) {
    cout << "Predict result: " << classifier->predict() << endl;
}


int main() {
    cout << "Using a single classifier" << endl;
    Classifier* single = new LeafClassifier();

    predict_api(single);
    delete single;

    cout << "Using an ensemble classifier" << endl;
    Classifier* ensemble = new EnsembleClassifier();
    ensemble->add(new LeafClassifier());
    ensemble->add(new LeafClassifier());
    ensemble->add(new LeafClassifier());

    predict_api(ensemble);
    delete ensemble;

    cout << "Using a stacked-ensemble classifier" << endl;
    Classifier* root = new EnsembleClassifier();
    Classifier* sub1 = new EnsembleClassifier();
    root->add(sub1);
    sub1->add(new LeafClassifier());
    Classifier* sub2 = new EnsembleClassifier();
    root->add(sub2);
    sub2->add(new LeafClassifier());
    sub2->add(new LeafClassifier());

    predict_api(root);
    delete root;

    return 0;
}