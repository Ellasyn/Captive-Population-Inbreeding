#include "MathsUtils.h"
using namespace std;

#define pi 3.142
#define e 2.718

// Random integer between zero and max (inclusive)
int MathsUtils::randomInt(int max)
{

    std::random_device randomSeed; // Non-deterministic random number generator
    std::mt19937 generator(randomSeed()); // Mersenne Twister engine seed
    std::uniform_int_distribution<> distribution(0, max);
    int num = distribution(generator);
    return num;
}

// Standard factorial calculation
int MathsUtils::factorial(int k) {
    int result;
    if (k == 0) { return 1; };
    if (k < 0) {
        return 1;
    };
    if (k != 0) {
        result = k * factorial((k)-1);
        if (result == 0) { result = 1; };
        return result;
    }
    else { return 1; };
};

// Standard poisson distribution
double MathsUtils::poisson(int k, double lambda) {
    double p;
    p = (powl(e, (-lambda))) * powl(lambda, k) / factorial(k);
    return p;
}



