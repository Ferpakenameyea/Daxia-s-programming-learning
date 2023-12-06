#include <iostream>
#include <string>
#include <vector>

class Manacher {
public:
    /**
     * @brief 对字符串进行Manacher处理以寻找回文子串
     * @param target 处理对象
     * @param resultBuffer 答案的写入目标
    */
    static void DoManacher(const std::string& target, std::vector<int>& resultBuffer) {
        if(resultBuffer.size() < target.length() * 2 + 2) {
            resultBuffer.resize(target.length() * 2 + 2, 0);
        }
        std::string newString;
        newString.reserve(target.length() * 2 + 2);
        newString += ("$#");
        for(int i = 0; i < target.length(); i++) {
            newString += target[i];
            newString += '#';
        }
        int maxX = 0, center = 0;
        for(int i = 0; i < newString.length(); i++) {
            resultBuffer[i] = maxX > i ? std::min(resultBuffer[2 * center - i], maxX - i) : 1;
            while(newString[i + resultBuffer[i]] == newString[i - resultBuffer[i]]) {
                resultBuffer[i]++;
            }
            if(i + resultBuffer[i] > maxX) {
                maxX = i + resultBuffer[i];
                center = i;
            }
        }
    }
};