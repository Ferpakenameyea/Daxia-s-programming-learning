#include <iostream>

class AccodingSolution{
private:
    AccodingSolution() {}
public:
    static void DoSomethingNTimes(void (*Function)(void)){
        int dataCount;
        std::cin >> dataCount;
        for(int i = 0; i < dataCount; i++){
            Function();
        }
    }
};