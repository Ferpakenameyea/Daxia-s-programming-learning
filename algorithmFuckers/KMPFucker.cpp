#include <iostream>
#include <vector>
#include <string.h>
class KMPSolver {
private:
    KMPSolver() {}
public:
    static void BuildNextArray(const char* subString, int subStringLength, std::vector<int>& result) {
        result.reserve(subStringLength);
        result.clear();
        result.push_back(0);
        int prefixLength = 0;
        int i = 1;
        while(i < subStringLength) {
            if(subString[prefixLength] == subString[i]) {
                prefixLength++;
                result.push_back(prefixLength);
                i++;
            } else {
                if(prefixLength == 0) {
                    result.push_back(0);
                    i++;
                } else {
                    prefixLength = result[prefixLength - 1];
                }
            }
        }
        return;
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
        std::vector<int> nextArray;
        BuildNextArray(subString, subStringLength, nextArray);
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

    static void KMPSearchFindAll(const char* string, const char* subString, int findRange, int subStringLength, std::vector<int>& nextArray, std::vector<int>& resultBuffer) {
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
                resultBuffer.push_back(i - j);
                j = nextArray[j - 1];
            }
        }
        return;
    }

    static void KMPSearchFindAll(const char* string, const char* subString, int findRange, int subStringLength, std::vector<int>& resultBuffer) {
        std::vector<int> next;
        BuildNextArray(subString, subStringLength, next);
        KMPSearchFindAll(string, subString, findRange, subStringLength, next, resultBuffer);
    }
};

int main() {
    
}