#include <iostream>
#include <map>

class OBST_Solution {
private:
    static const int maxArraySize = 400;
    long long (*GetP)(int index);
    long long (*GetQ)(int index);

    long long e[maxArraySize][maxArraySize];
    long long w[maxArraySize][maxArraySize];
    int root[maxArraySize][maxArraySize];

    int elemCount = -1;
    long long result = -1;
public:

    OBST_Solution(int elemCount, long long (*GetP)(int index), long long (*GetQ)(int index)) : 
        elemCount(elemCount),
        GetP(GetP),
        GetQ(GetQ)
        {}

    long long Run() {
        for(int i = 1; i <= elemCount; i++) {
            e[i][i - 1] = GetQ(i - 1);
            w[i][i - 1] = GetQ(i - 1);
        }

        for(int l = 1; l <= elemCount; l++) {
            for(int i = 1; i <= elemCount - l + 1; i++) {
                int j = i + l - 1;
                e[i][j] = 0x7fffffffffffffff;
                w[i][j] = w[i][j - 1] + GetP(j) + GetQ(j);
                for(int r = i; r <= j; r++) {
                    long long t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                    if(t < e[i][j]) {
                        e[i][j] = t;
                        root[i][j] = r;
                    }
                }
            }
        }
        return e[1][elemCount];
    }

    inline long long GetResult(int from, int to) {
        return this->e[from][to];
    }

    inline int GetRoot(int from, int to) {
        return this->root[from][to];
    }
};