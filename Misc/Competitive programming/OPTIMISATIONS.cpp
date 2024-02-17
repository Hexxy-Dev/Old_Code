#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

template<typename T>
class AddElements
{
public:
    AddElements(const T& element)
        : m_value(std::move(element))
    {}

    const T add(const T& element)
    {
        return std::move(m_value + element);
    }
private:
    T m_value;
};

template<>
class AddElements<string>
{
public:
    AddElements(const string& element)
        : m_value(std::move(element))
    {}

    const string concatenate(const string& element)
    {
        return std::move(m_value += element);//
    }
private:
    string m_value;
};
//
int start_up() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}

int static r = start_up();

#define endl '\n';
//
int main() {
    int n, i;
    cin >> n;
    for (i = 0; i < n; i++) {
        string type;
        cin >> type;
        if (type == "float") {
            double element1, element2;
            cin >> element1 >> element2;
            AddElements<double> myfloat(element1);
            cout << myfloat.add(element2) << endl;
        }
        else if (type == "int") {
            int element1, element2;
            cin >> element1 >> element2;
            AddElements<int> myint(element1);
            cout << myint.add(element2) << endl;
        }
        else if (type == "string") {
            string element1, element2;
            cin >> element1 >> element2;
            AddElements<string> mystring(element1);
            cout << mystring.concatenate(element2) << endl;
        }
    }
    return 0;
}
