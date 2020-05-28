#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


class Optimizer {
public:
    virtual ~Optimizer() {}
    virtual void step(vector<float>& params) const = 0;
};


class Model {
private:
    Optimizer* optim;
    vector<float> params;
public:
    Model(Optimizer* optimizer) : optim(optimizer) {}
    ~Model() {
        delete this->optim;
    }

    void initParameters(std::initializer_list<float> data) {
        for (float a : data)
            this->params.push_back(a);
    }

    void printParameters() {
        cout << "All parameters in the model:" << endl;
        for (float a : params)
            cout << a << ", ";
        cout << endl;
    }

    void setOptimizationMethod(Optimizer* optimizer) {
        delete this->optim;
        this->optim = optimizer;
    }

    void train() {
        this->optim->step(this->params);
    }
};


class GradienDescend : public Optimizer {
private:
    float lr;
public:
    GradienDescend(float lr = 0.l) : Optimizer(), lr(lr) {}
    void step(vector<float>& params) const override {
        cout << "Train the model with gradient descend method" << endl;
        for (float& a : params)
            a -= this->lr;
    }
};

class GradienAscend : public Optimizer {
private:
    float lr;
public:
    GradienAscend(float lr = 0.l) : Optimizer(), lr(lr) {}
    void step(vector<float>& params) const override {
        cout << "Train the model with gradient ascend method" << endl;
        for (float& a : params)
            a += this->lr;
    }
};


int main()
{
    GradienDescend* optim1 = new GradienDescend(0.1);
    Model* model = new Model(optim1);
    model->initParameters({1, 2, 3, 4, 5});
    model->printParameters();

    model->train();
    model->printParameters();

    GradienAscend* optim2 = new GradienAscend(0.5);
    model->setOptimizationMethod(optim2);
    model->train();
    model->printParameters();

    return 0;
}