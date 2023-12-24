#include <iostream>

template<typename T>
/**
 * @brief 执行对某个数的模意义下的运算
 * @param T 运算的类型
 * @class ModdedCalculator
*/
struct ModdedCalculator {
private:
    const T modder;
    T current = 0;

public:
    T ModdedQuickPow(const T base, const int power) {
        if(power == 0) return 1;
        if(power == 1) return base % modder;
        const T temp = ModdedQuickPow(base, power / 2) % modder;
        if(power & 1) {
            return ((base % modder) * (temp % modder)) % modder * (temp % modder) % modder;
        }
        return ((temp % modder) * (temp % modder)) % modder;
    }

    inline T GetInv(const T target) {
        return ModdedQuickPow(target, modder - 2) % modder;
    }

    ModdedCalculator(const T modder) : modder(modder), current(0) {}

    void SetCurrent(const T& value) {
        this->current = value % modder;
    }

    T GetCurrent() {
        return current;
    }

    void Reset() {
        this->current = 0;
    }

    void SetModder(const T modder) {
        this->modder = modder;
    }

    T GetModder() const {
        return modder;
    }

    void operator+=(const T other){
        this->current = (this->current + other % modder) % modder;
    }

    void operator-=(const T other){
        this->current = (this->current - other % modder + modder) % modder;
    }

    void operator*=(const T other){
        this->current = (this->current * ((other % modder + modder) % modder)) % modder;
    }

    void operator/=(const T other){
        this->current = (this->current * (GetInv(other) % modder)) % modder;
    }
};

int main() {
    ModdedCalculator<long long> cal(500);
    cal.SetCurrent(30);
    cal -= 50;
    std::cout << cal.GetCurrent();
}