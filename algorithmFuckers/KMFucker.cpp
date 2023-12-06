#include <vector>
#include <limits>
#include <iostream>

const long long INF = std::numeric_limits<long long>::max();

class KM {
private:
    long long SafeMinus(const long long a, const long long b) {
        if(b == INF) {
            return -INF;
        }
        if(b == -INF) {
            return INF;
        }
        return a - b;
    }
    //hide constructor
    std::vector<int> match;
    std::vector<bool> va, vb;
    std::vector<long long> la, lb, delta;
    long long (*weight)(int from, int to);
    const int size;
    bool DFS(int x) {
        va[x] = true;
        for(int y = 0; y < size; y++) {
            if(!vb[y]) {
                if(la[x] + lb[y] - weight(x, y) == 0) {
                    vb[y] = true;
                    if((match[y] == -1) || DFS(match[y])) {
                        match[y] = x;
                        return true;
                    }
                } else {
                    delta[y] = std::min<long long>(
                        delta[y],
                        SafeMinus(la[x] + lb[y], weight(x, y))
                    );
                }
            }
        }
        return false;
    }

public:
    
    KM(const int size, long long (*weight)(int from, int to)) :
        match(size, -1), 
        va(size, false),
        vb(size, false), 
        la(size, -INF), 
        lb(size, 0), 
        delta(size, INF),
        weight(weight), 
        size(size) {}

    long long Run() {
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                la[i] = std::max<long long>(
                    la[i],
                    weight(i, j)
                );
            }
        }
        for(int i = 0; i < size; i++) {
            while(true) {
                std::fill(va.begin(), va.end(), false);
                std::fill(vb.begin(), vb.end(), false);
                std::fill(delta.begin(), delta.end(), INF);
                if(DFS(i)) {
                    break;
                }
                long long delta = INF;
                for(int j = 0; j < size; j++) {
                    if(!vb[j]) {
                        delta = std::min<long long>(delta, this->delta[j]);
                    }
                }
                for(int j = 0; j < size; j++) {
                    if(va[j]) {
                        la[j] -= delta;
                    }
                    if(vb[j]) {
                        lb[j] += delta;
                    }
                }
            }
        }
        long long result = 0;
        for(int i = 0; i < size; i++) {
            result += weight(match[i], i);
        }
        return result;
    }
};

// ACCODING 可过（运行较慢，做CPP封装类的板子本质上不是复制粘贴
// 而是提供一种思路）

struct Vector2{
private:
    long long x, y;
public:
    long long Mannhadon(const Vector2& other) const {
        return
        std::abs(this->x - other.x) +
        std::abs(this->y - other.y);
    }
    Vector2(int x, int y) : x(x), y(y) {}
};
std::vector<Vector2> froms;
std::vector<Vector2> targets;
// 定义边权获取规则，由于需要的是最小，所以干脆提供负边权，这样
// 就不用修改KM算法内部。KM算出来的“最大”反一下就是最小
long long getWeight(int from, int to) {
    return -(froms[from].Mannhadon(targets[to]));
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int count;
    std::cin >> count;
    for(int i = 0; i < count; i++) {
        froms.clear();
        targets.clear();
        int size;
        std::cin >> size;
        for(int i = 0; i < size; i++) {
            int x, y;
            std::cin >> x >> y;
            froms.emplace_back(x, y);
        }
        for(int i = 0; i < size; i++) {
            int x, y;
            std::cin >> x >> y;
            targets.emplace_back(x, y);
        }
        // 构造KM算法解决方案对象
        KM km(size, getWeight);
        std::cout << std::abs(km.Run()) << '\n';
    }
}