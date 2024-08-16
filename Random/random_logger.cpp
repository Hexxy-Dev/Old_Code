#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template<typename T>
void log(const T& val) {
    std::cout << val;
}

template<typename T>
void log(const std::vector<T>& v) {
    std::cout << "{ ";
    std::for_each(v.begin(), v.end(), [](const auto& x){log(x);log(' ');});
    std::cout << " }";
}

template<typename T, typename... ARGS>
void log(const T& val, const ARGS&... args) {
    log(val);
    log(args...);
}

class Singleton {
public:
    static Singleton* get_instance() {
        static Singleton s;
        return &s;
    }
    Singleton(Singleton&) = delete;
    Singleton& operator=(Singleton&) = delete;
private:
    Singleton() {}
};






int main()
{
    log(1,1590,'g',"sagjqio",'\n','a');

    std::vector<int> v = {1,46,679,325,458,325,786789,1};
    log('v',": ",v,'\n');
}