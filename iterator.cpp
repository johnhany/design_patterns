#include <iostream>
#include <string>
#include <vector>


using namespace std;


template <typename T, typename U>
class Iterator {
public:
    typedef typename vector<T>::iterator iter_type;
    Iterator(U *data) : container(data) {
        iter = container->data.begin();
    }

    void first() {
        iter = container->data.begin();
    }

    void next() {
        iter++;
    }

    vector<T> getBatch(int batch_size) {
        vector<T> rst;
        while (!this->reachEnd() && batch_size--)
            rst.push_back(this->getSample());
        return rst;
    }

    T getSample() {
        T rst = *iter;
        this->next();
        return rst;
    }

    bool reachEnd() {
        return (iter == container->data.end());
    }
private:
    U *container;
    iter_type iter;
};


template <class T>
class Container {
    friend class Iterator<T, Container>;

public:
    Container(std::initializer_list<T> data) {
        for (auto& a : data)
            this->add(a);
    }

    void add(T a) {
        data.push_back(a);
    }

    Iterator<T, Container> *createIterator() {
        return new Iterator<T, Container>(this);
    }
private:
    std::vector<T> data;
};


class Sample {
public:
    Sample(string img) : data(img) {}

    string getData() {
        return data;
    }
private:
    string data;
};


int main() {
    cout << "Dataset of int" << endl;
    Container<int> dataset1{1,2,3,4,5,6};
    auto itr1 = dataset1.createIterator();

    cout << "Current sample: " << itr1->getSample() << endl;

    cout << "Next sample: " << itr1->getSample() << endl;

    auto batch1 = itr1->getBatch(3);
    cout << "Next sample batch:" << endl;
    for (auto& a : batch1)
        cout << a << ", ";
    cout << endl;

    batch1 = itr1->getBatch(3);
    cout << "Get another batch:" << endl;
    for (auto& a : batch1)
        cout << a << ", ";
    cout << endl;

    cout << "Dataset of Sample" << endl;
    Container<Sample> dataset2{};
    for (int i = 10; i < 15; i++)
        dataset2.add(Sample(to_string(i)));
    auto itr2 = dataset2.createIterator();

    cout << "Next sample: " << itr2->getSample().getData() << endl;

    auto batch2 = itr2->getBatch(3);
    cout << "Next sample batch:" << endl;
    for (auto& a : batch2)
        cout << a.getData() << ", ";
    cout << endl;

    return 0;
}