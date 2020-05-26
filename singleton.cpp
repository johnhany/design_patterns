#include <iostream>
#include <string>
#include <thread>


using namespace std;


class Model {
private:
    Model() {}
    ~Model() {}
protected:
    Model(const string id) : model_id(id) {}
    static Model* model;
    string model_id;
public:
    Model(const Model&) = delete;
    Model(Model&&) = delete;
    void operator=(const Model&) = delete;
    void operator=(Model&&) = delete;

    void train() {
        cout << "Training done with " + model_id + "\n";
    }

    static Model* getInstance(const string& id);
    static Model& getInstanceSafe(const string& id);
};

Model* Model::model = nullptr;

Model* Model::getInstance(const string& id) {
    if (model == nullptr)
        model = new Model(id);
    return model;
}

Model& Model::getInstanceSafe(const string& id) {
    static Model model_safe;
    model_safe.model_id = id;
    return model_safe;
}


void trainer1() {
    // Emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //Model* model = Model::getInstance("model_1");
    //model->train();

    Model::getInstanceSafe("model_1").train();
}

void trainer2() {
    // Emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // Model* model = Model::getInstance("model_2");
    // model->train();

    Model::getInstanceSafe("model_2").train();
}


int main()
{
    std::cout <<"If you see the same value, then singleton was reused\n" <<
                "If you see different values, then 2 singletons were created in different threads\n\n" <<
                "RESULT:\n";
    std::thread t1(trainer1);
    std::thread t2(trainer2);
    t1.join();
    t2.join();

    return 0;
}