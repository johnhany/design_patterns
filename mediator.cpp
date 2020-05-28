#include <iostream>
#include <string>


using namespace std;


class Generator;
class Mediator {
public:
    virtual void execute(string img, Generator* gen = nullptr) const = 0;
};


class Generator {
protected:
    Mediator* mediator;
public:
    Generator(Mediator* mediator = nullptr) : mediator(mediator) {}

    void setMediator(Mediator* mediator) {
        this->mediator = mediator;
    }
};

class ForegroundGenerator : public Generator {
public:
    void generatePerson() {
        cout << "Generated a person in image" << endl;
        this->mediator->execute("", this);
    }
    void generateVehicle() {
        cout << "Generated a vehicle in image" << endl;
        this->mediator->execute("", this);
    }
};

class BackgroundGenerator : public Generator {
public:
    void generateBeach() {
        cout << "Generated beach background in image" << endl;
        this->mediator->execute("person", this);
    }

    void generateStreet() {
        cout << "Generated street background in image" << endl;
        this->mediator->execute("person + vehicle", this);
    }
};


class GenerationMediator : public Mediator {
private:
    ForegroundGenerator* fg_gen;
    BackgroundGenerator* bg_gen;
public:
    GenerationMediator(ForegroundGenerator* fg, BackgroundGenerator* bg) : fg_gen(fg), bg_gen(bg) {
        this->fg_gen->setMediator(this);
        this->bg_gen->setMediator(this);
    }

    void execute(string request, Generator* gen = nullptr) const override {
        if (request.find("beach") != string::npos) {
            this->bg_gen->generateBeach();
        }
        if (request.find("street") != string::npos) {
            this->bg_gen->generateStreet();
        }
        if (request.find("person") != string::npos) {
            this->fg_gen->generatePerson();
        }
        if (request.find("vehicle") != string::npos) {
            this->fg_gen->generateVehicle();
        }
    }
};


int main() {
    string request1 = "I need an image of beach";
    ForegroundGenerator* fg = new ForegroundGenerator();
    BackgroundGenerator* bg = new BackgroundGenerator();
    GenerationMediator* mediator = new GenerationMediator(fg, bg);
    cout << "Generating image based on request: " << request1 << endl;
    mediator->execute(request1);

    string request2 = "I need an image of vehicle";
    cout << "Generating image based on request: " << request2 << endl;
    mediator->execute(request2);

    cout << "You can call Generator to trigger the Mediator:" << endl;
    bg->generateStreet();

    delete fg;
    delete bg;
    delete mediator;

    return 0;
}