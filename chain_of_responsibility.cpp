#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Handler {
public:
    virtual Handler* setNext(Handler* handler) = 0;
    virtual string process(string img) = 0;
};

class AbstractHandler : public Handler {
private:
    Handler* next;
public:
    AbstractHandler() : next(nullptr) {}

    Handler* setNext(Handler* handler) override {
        this->next = handler;
        return handler;
    }
    string process(string img) override {
        if (this->next)
            return this->next->process(img);
        else
            return {};
    }
};

class FaceDetection : public AbstractHandler {
public:
    string process(string img) override {
        string rst = "";
        if (img.find("face") != string::npos)
            rst += "Detected face. ";
        rst += AbstractHandler::process(img);
        return rst;
    }
};

class BodyDetection : public AbstractHandler {
public:
    string process(string img) override {
        string rst = "";
        if (img.find("body") != string::npos)
            rst += "Detected body. ";
        rst += AbstractHandler::process(img);
        return rst;
    }
};

class TextDetection : public AbstractHandler {
public:
    string process(string img) override {
        string rst = "";
        if (img.find("text") != string::npos)
            rst += "Detected text. ";
        rst += AbstractHandler::process(img);
        return rst;
    }
};


void detect_api(Handler& handler, string& image) {
    cout << "Processing image: " << image << endl;
    string rst = handler.process(image);
    if (rst.empty())
        rst = "Detected nothing.";
    cout << rst << endl;
}


int main() {
    FaceDetection* face = new FaceDetection();
    BodyDetection* body = new BodyDetection();
    TextDetection* text = new TextDetection();

    face->setNext(body)->setNext(text);

    string img1 = "An image of a person with face and body, and some text";
    detect_api(*face, img1);

    string img2 = "An image of a person with face, and some text";
    detect_api(*body, img2);

    delete face;
    delete body;
    delete text;

    return 0;
}