#include <iostream>
#include <string>
#include <vector>
#include <ctime>


using namespace std;


class Memento {
public:
    virtual string getState() const = 0;
};

class ConcreteMemento : public Memento {
private:
    string state;
public:
    ConcreteMemento(string state) : state(state) {}

    string getState() const override {
        return this->state;
    }
};


class Editor {
private:
    string image;
public:
    Editor(string img) : image(img) {
        cout << "[Editor] Initial image: " << this->image << endl;
    }

    void resizeToHalf() {
        int length = this->image.size();
        string rst = "";
        for (int i = 0; i < length; i++) {
            if (i % 2 == 0)
                rst.push_back(this->image[i]);
        }
        this->image = rst;
        cout << "[Editor] Image: " << this->image << endl;
    }

    void resizeTo2X() {
        int length = this->image.size();
        string rst = "";
        for (int i = 0; i < length; i++) {
            rst.push_back(this->image[i]);
            rst.push_back(this->image[i]);
        }
        this->image = rst;
        cout << "[Editor] Image: " << this->image << endl;
    }

    void brighten(int var) {
        int length = this->image.size();
        string rst = "";
        for (int i = 0; i < length; i++) {
            if (this->image[i] + var <= '9')
                rst.push_back(this->image[i] + var);
            else
                rst.push_back('9');
        }
        this->image = rst;
        cout << "[Editor] Image: " << this->image << endl;
    }

    Memento* save() {
        return new ConcreteMemento(this->image);
    }

    void restore(Memento* memento) {
        this->image = memento->getState();
        cout << "[Editor] Image is restored to: " << this->image << endl;
    }
};


class App {
private:
    vector<Memento*> hist;
    Editor* editor;
public:
    App(Editor* editor) : editor(editor) {}

    void backup() {
        cout << "[App] Saving current image..." << endl;
        this->hist.push_back(this->editor->save());
    }

    void undo() {
        if (this->hist.empty()) return;
        cout << "[App] Undoing last process..." << endl;
        Memento* mem = this->hist.back();
        this->hist.pop_back();
        this->editor->restore(mem);
    }
};


int main() {
    string image = "12323454";
    Editor* editor = new Editor(image);
    App* app = new App(editor);

    app->backup();
    editor->resizeToHalf();

    app->backup();
    editor->resizeTo2X();

    app->backup();
    editor->brighten(6);

    app->undo();
    app->undo();
    app->undo();

    return 0;
}