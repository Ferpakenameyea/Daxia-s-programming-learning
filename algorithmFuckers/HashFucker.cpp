#include <string>
#include <vector>
#include <iostream>

/**
 * 原作者为北京航空航天大学22级软件学院算法分析与设计助教团队，本人仅为整理重写
 * 由于使用此文件导致的所有被误认为抄袭，作弊等后果，本人概不负责
*/

// 用于计算字符串哈希的结构体
struct Hash {
private:
	int BASE, PRIME; 
    std::vector<int> hashval, powerCache;
    int length;

public:

    /**
     * @brief 推荐使用的默认模数
     * @attention 模数必须要是质数，如果您需要使用自己的模数，请您注意这一点
    */
    static const int MOD = 1000000007;

    /**
     * @brief 初始化哈希构造器
     * @param base 构建字符串哈希时所用的乘数
     * @param modder 构建字符串哈希时所用的模数（需要是质数）
     * @param target 构建字符串哈希的字符串源
    */
	void Initialize(int base, int modder, const std::string& target) {
		BASE = base, PRIME = modder;
		this->length = target.size();
        hashval.resize(target.length());
        powerCache.resize(target.length());

		hashval[0] = target[0];
		for (int i = 1; i < length; i ++) {
			hashval[i] = ((long long)hashval[i - 1] * base + target[i]) % modder;
        }
        powerCache[0] = 1;
		for (int i = 1; i <= length; i ++) {
            powerCache[i] = (long long)powerCache[i - 1] * base % modder;
        }
    }

    /**
     * @brief 获取字符串[from, to]范围子串的哈希值
     * @param from 起始位置（包括）
     * @param to 终止位置（包括）
     * @return 从下标from开始到下标to结束的子串哈希值
    */
	int GetQuery(int from, int to) {
		if(from < 0) {
            from = 0;
        }

        if(to >= this->length) {
            to = this->length - 1;
        }
        
        if (from != 0) {
            return (hashval[to] + PRIME - (long long)hashval[from - 1] * powerCache[to - from + 1] % PRIME) % PRIME;
        }
        return hashval[to];
	}

    /**
     * @brief 获取整个字符串的完整哈希值
     * @return 哈希值
    */
    int HashCode() {
        return GetQuery(0, this->length - 1);
    }
    
    /**
     * @brief 获取对象源的长度
     * @return 长度
    */
    int Length() {
        return this->length;
    }
};

int main() {
    std::string mainString = "Hello, world!";
    std::string subString = "world!";
    Hash& hash = *new Hash();
    Hash& hash2 = *new Hash();
    hash.Initialize(256, Hash::MOD, mainString);
    hash2.Initialize(256, Hash::MOD, subString);
    std::cout << hash.GetQuery(7, hash.Length() - 1) << "==?" << hash2.HashCode() << std::endl;
}