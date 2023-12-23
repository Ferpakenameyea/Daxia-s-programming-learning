#include <iostream>
#include <vector>

/**
 * @class Hungarian
 * @brief 匈牙利算法类
*/
class Hungarian {
private:
    int leftSize, rightSize;
    std::vector<std::vector<int>> map;
    std::vector<bool> visited;
    std::vector<int> matcher;
    bool Match(int i) {
        for(int j = 0; j < rightSize; j++) {
            if(map[i][j] && !visited[j]) {
                visited[j] = true;
                if(matcher[j] == -1 || Match(matcher[j])) {
                    matcher[j] = i;
                    return true;
                }
            }
        }
        return false;
    }

public:
    Hungarian(int leftSize, int rightSize) : 
            leftSize(leftSize), 
            rightSize(rightSize), 
            map(leftSize, std::vector<int>(rightSize, 0)),
            visited(rightSize, false),
            matcher(rightSize, -1) {}

    int Calculate() {
        int count = 0;
        for(int i = 0; i < this->leftSize; i++) {
            std::fill(visited.begin(), visited.end(), false);
            if(this->Match(i)) {
                count++;
            }
        }
        return count;
    }

    void AddEdge(int A, int B) {
        this->map[A][B] = true;
    }
};