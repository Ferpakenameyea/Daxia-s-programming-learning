#include <iostream>
#include <limits>
#include <iomanip>

const long long INF = std::numeric_limits<long long>::max();
int array[302];
int matrixCount;
long long dp[302][302];

void MCM_DP_GetMin() {
    int border = matrixCount;
    for(int singleMatrix = 1; singleMatrix <= border; singleMatrix++) {
        dp[singleMatrix][singleMatrix] = 0;
    }
    for(int matrixLength = 2; matrixLength <= border; matrixLength++) {
        for(int matrixStart = 1; matrixStart <= border - matrixLength + 1; matrixStart++) {
            const int matrixStartMax = matrixStart + matrixLength - 1;
            dp[matrixStart][matrixStartMax] = INF;
            for(int brackletPos = matrixStart; brackletPos <= matrixStartMax - 1; brackletPos++) {
                long long q = dp[matrixStart][brackletPos] + dp[brackletPos + 1][matrixStartMax] + array[matrixStart] * array[brackletPos + 1] * array[matrixStartMax + 1];
                if(q < dp[matrixStart][matrixStartMax]) {
                    dp[matrixStart][matrixStartMax] = q;
                }
                // IN THIS CASE, the array[i] means the rows count of the matrix, the array[i + 1] means the columns count of the matrix
            }
        }
    }
    return;
}