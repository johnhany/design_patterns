#include <iostream>
#include <string>
#include <vector>


using namespace std;


class Command {
protected:
    string image;
public:
    virtual ~Command() {}
    void setCurrentImage(string& img) {
        this->image = img;
    }
    virtual void execute() const = 0;
};


class Receiver {
public:
    void applyEffectsOnForeground(const string& img) {
        cout << "  Add some special effects on the foreground of " << img << endl;
    }
    void applyEffectsOnBackground(const string& img) {
        cout << "  Add some special effects on the background of " << img << endl;
    }
};


class EditPortrait : public Command {
private:
    Receiver* receiver;
public:
    explicit EditPortrait(Receiver* rec) : receiver(rec) {}
    void execute() const override {
        cout << "Edit portrait..." << endl;
        this->receiver->applyEffectsOnBackground(this->image);
    }
};

class EditFullImage : public Command {
private:
    Receiver* receiver;
public:
    explicit EditFullImage(Receiver* rec) : receiver(rec) {}
    void execute() const override {
        cout << "Edit full image..." << endl;
        this->receiver->applyEffectsOnForeground(this->image);
        this->receiver->applyEffectsOnBackground(this->image);
    }
};


class Invoker {
private:
    vector<Command*> cmd_queue;
public:
    virtual ~Invoker() {
        for (auto& p : this->cmd_queue)
            delete p;
        cout << "Invoker destroyed" << endl;
    }

    void addCommand(Command* cmd) {
        this->cmd_queue.push_back(cmd);
    }

    void revokeLastCommand() {
        if (!this->cmd_queue.empty())
            this->cmd_queue.pop_back();
    }

    void executeAllCommands(string img) {
        for (auto& p : this->cmd_queue) {
            p->setCurrentImage(img);
            p->execute();
        }
    }
};


int main() {
    string image = "IMAGE";
    Receiver* receiver = new Receiver();
    Invoker* invoker = new Invoker();
    Command* cmd1 = new EditPortrait(receiver);
    Command* cmd2 = new EditFullImage(receiver);
    Command* cmd3 = new EditPortrait(receiver);
    invoker->addCommand(cmd1);
    invoker->addCommand(cmd2);
    invoker->addCommand(cmd3);

    invoker->revokeLastCommand();

    invoker->executeAllCommands(image);

    delete receiver;
    delete invoker;
    delete cmd1;
    delete cmd2;
    delete cmd3;
    return 0;
}