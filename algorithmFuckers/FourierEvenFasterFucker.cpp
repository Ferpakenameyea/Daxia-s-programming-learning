#include <iostream>
#include <vector>
#include <complex>
class IterativeFFT {
private:
    IterativeFFT() {}
    static inline unsigned int BitReverse(unsigned int source, int rangeLength) {
        unsigned int reader = 0x00000001;
        unsigned int writer = 0x00000001 << rangeLength - 1;
        unsigned int result = 0x00000000;
        while(writer != 0) {
            if(source & reader) {
                result |= writer;
            }
            reader <<= 1;
            writer >>= 1;    
        }
        return result;
    }

    static inline void BitReverseCopy(const std::vector<std::complex<double>>& source, std::vector<std::complex<double>>& target) {
        int lgsize = Lg2_POWER2_ONLY(source.size());
        for(int i = 0; i < source.size(); i++) {
            target[BitReverse(i, lgsize)] = source[i];
        }
    }

    static inline int Lg2_POWER2_ONLY(int target) {
        unsigned int reader = 0x00000001;
        int result = 0;
        while((reader & target) == 0) {
            reader <<= 1;
            result++;
        }
        return result;
    }
public:
    static void DoFFT(const std::vector<std::complex<double>>& source, std::vector<std::complex<double>>& target) {
        BitReverseCopy(source, target);
        int n = source.size();
        int m = 1;
        int lgN = Lg2_POWER2_ONLY(n);
        for(int s = 1; s <= lgN; s++) {
            m <<= 1;
            std::complex<double> omegaM = std::polar(1.0, (2.0 * M_PI) / m);
            for(int k = 0; k <= (n - 1); k += m) {
                std::complex<double> omega = 1.0;
                for(int j = 0; j < (m / 2); j++) {
                    std::complex<double> t = omega * target[k + j + m / 2];
                    std::complex<double> u = target[k + j];
                    target[k + j] = u + t;
                    target[k + j + m / 2] = u - t;
                    omega *= omegaM;
                }
            }
        }
        return;
    }

    static void DoIFFT(const std::vector<std::complex<double>>& source, std::vector<std::complex<double>>& target) {
        BitReverseCopy(source, target);
        int n = source.size();
        int m = 1;
        int lgN = Lg2_POWER2_ONLY(n);
        for(int s = 1; s <= lgN; s++) {
            m <<= 1;
            std::complex<double> omegaM = std::polar(1.0, (-2.0 * M_PI) / m);
            for(int k = 0; k <= (n - 1); k += m) {
                std::complex<double> omega = 1.0;
                for(int j = 0; j < (m / 2); j++) {
                    std::complex<double> t = omega * target[k + j + m / 2];
                    std::complex<double> u = target[k + j];
                    target[k + j] = u + t;
                    target[k + j + m / 2] = u - t;
                    omega *= omegaM;
                }
            }
        }
        for(std::complex<double>& iterator : target) {
            iterator /= n;
            iterator = iterator.real();
        }
        return;
    }
};

int main() {
    std::vector<std::complex<double>> array = {1, 2, 2, 3};
    std::vector<std::complex<double>> target(array.size(), 0.0);
    IterativeFFT::DoFFT(array, target);
    for(auto c : target) {
        std::cout << c << " ";
    }
    std::cout << '\n';
    IterativeFFT::DoIFFT(target, array);
    for(auto c : array) {
        std::cout << c << " ";
    }
}