#include <iostream>
#include <vector>
#include <complex>
#include <valarray>
class FFT {
private:
    FFT() {}
public:
    static void DoFFT(std::valarray<std::complex<double>>& args) {
        const size_t n = args.size();
        if (n <= 1) {
            return;
        }
        std::complex<double> omegaN = std::polar(1.0, (2 * M_PI) / n);
        std::complex<double> omega(1.0);

        std::valarray<std::complex<double>> even = args[std::slice(0, n / 2, 2)];
        std::valarray<std::complex<double>> odd = args[std::slice(1, n / 2, 2)];
        DoFFT(even);
        DoFFT(odd);
        for (int i = 0; i < n / 2; i++) {
            args[i] = even[i] + omega * odd[i];
            args[i + n / 2] = even[i] - omega * odd[i];
            omega *= omegaN;
        }
        return;
    }

    static void DoIFFT(std::valarray<std::complex<double>>& args) {
        const size_t n = args.size();
        if (n <= 1) {
            return;
        }
        std::complex<double> omegaN = std::polar(1.0, (-2 * M_PI) / n);
        std::complex<double> omega(1.0);

        std::valarray<std::complex<double>> even = args[std::slice(0, n / 2, 2)];
        std::valarray<std::complex<double>> odd = args[std::slice(1, n / 2, 2)];
        DoIFFT(even);
        DoIFFT(odd);
        for (int i = 0; i < n / 2; i++) {
            args[i] = (even[i] + omega * odd[i]) / 2.0;
            args[i + n / 2] = (even[i] - omega * odd[i]) / 2.0;
            omega *= omegaN;
        }
        return;
    }
};

int main() {
    std::valarray<std::complex<double>> array = {1, 2, 2, 3};
    FFT::DoFFT(array);
    for(auto i : array) {
        std::cout << i << " ";
    }
}
