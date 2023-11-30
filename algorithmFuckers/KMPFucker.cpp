#include <iostream>
#include <vector>
#include <string.h>
class KMPSolver {
private:
    KMPSolver() {}
public:
    static std::vector<int> BuildNextArray(const char* subString, int subStringLength) {
        std::vector<int> next;
        next.reserve(subStringLength);
        next.push_back(0);
        int prefixLength = 0;
        int i = 1;
        while(i < subStringLength) {
            if(subString[prefixLength] == subString[i]) {
                prefixLength++;
                next.push_back(prefixLength);
                i++;
            } else {
                if(prefixLength == 0) {
                    next.push_back(0);
                    i++;
                } else {
                    prefixLength = next[prefixLength - 1];
                }
            }
        }
        return next;
    }

    static int KMPSearch(const char* string, const char* subString, int findRange, int subStringLength, std::vector<int>& nextArray) {
        int i = 0, j = 0;
        while(i < findRange) {
            if(string[i] == subString[j]) {
                i++;
                j++;
            } else if(j > 0) {
                j = nextArray[j - 1];
            } else {
                i++;
            }

            if(j == subStringLength) {
                return i - j;
            }
        }
        return -1;
    }

    static int KMPSearch(const char* string, const char* subString, int findRange, int subStringLength) {
        std::vector<int> nextArray = BuildNextArray(subString, subStringLength);
        return KMPSearch(string, subString, findRange, subStringLength, nextArray);
    }

    static int KMPSearch(const char* string, const char* subString) {
        return KMPSearch(string, subString, strlen(string), strlen(subString));
    }

    static int KMPSearch(const char* string, const char* subString, int findRange, int subStringLength, int fromIndex) {
        return KMPSearch(string + fromIndex, subString, findRange, subStringLength);
    }

    static int KMPSearch(const char* string, const char* subString, int fromIndex) {
        return KMPSearch(string + fromIndex, subString, strlen(string), strlen(subString));
    }

    static std::vector<int> KMPSearchFindAll(const char* string, const char* subString, int findRange, int subStringLength, bool skipFullString = true) {
        std::vector<int> result;
        std::vector<int> next = BuildNextArray(subString, subStringLength);
        int currentFrom = 0;
        while(true) {
            int foundIndex = KMPSearch(string, subString, findRange, subStringLength, next);
            if(foundIndex == -1){
                break;
            }
            result.push_back(currentFrom + foundIndex);
            int skipper = (skipFullString ? subStringLength : 1);
            string += skipper + foundIndex;
            currentFrom += skipper + foundIndex;
            findRange -= skipper + foundIndex;
        }
        return result;
    }

    static std::vector<int> KMPSearchFindAll(const char* string, const char* subString, bool skipFullString = true) {
        return KMPSearchFindAll(string, subString, strlen(string), strlen(subString), skipFullString);
    }
};

int main() {
    char* stringA = "abcabcabcabc";
    char* stringB = "abcabc";
    auto res = KMPSolver::KMPSearchFindAll(stringA, stringB, false);
    for(auto r : res) {
        std::cout << r << " ";
    }   
}