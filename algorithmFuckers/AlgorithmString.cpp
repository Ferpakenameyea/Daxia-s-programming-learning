#include <iostream>
#include <string>

static const int MAX = 2001;
static int dp[MAX][MAX];
static std::pair<int, int> subStringXY;
static int subStringMax;

class AlgorithmString {
private:
    AlgorithmString() {}
public:
    static int GetLongestCommonSubSequence(const std::string &a, const std::string &b)
    {
        const int length1 = a.length();
        const int length2 = b.length();
        for (int i = 1; i <= length1; i++)
        {
            for (int j = 1; j <= length2; j++)
            {
                if (a[i - 1] == b[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[length1][length2];
    }

    static int GetLongestCommonSubString(const std::string &a, const std::string &b)
    {
        const int lena = a.length();
        const int lenb = b.length();
        int& max = subStringMax;
        int& x = subStringXY.first; 
        int& y = subStringXY.second;
        
        max = 0; x = 0; y = 0;

        for (int i = 0; i < lena; i++)
        {
            for (int j = 0; j < lenb; j++)
            {
                if (a[i] == b[j])
                {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                }
                else
                {
                    dp[i + 1][j + 1] = 0;
                }
                if (dp[i + 1][j + 1] > max)
                {
                    x = i + 1;
                    y = j + 1;
                    max = dp[i + 1][j + 1];
                }
            }
        }

        return max;
    }

    static void PrintCommonSubString(const std::string& org_a) {
        if(subStringMax != 0) {
            for(int i = subStringXY.first - subStringMax; i < subStringXY.first; i++) {
                std::cout << org_a[i];
            }
        }
    }
};

int main() {
    std::string a = "hello";
    std::string b = "weel";
    AlgorithmString::GetLongestCommonSubString(a, b);
    AlgorithmString::PrintCommonSubString(a);
}