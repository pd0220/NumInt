// used headers and libraries
#include <iostream>
#include <math.h>

// constants in keV
double const m_ec2 = 511.;
double const m_nuc2 = 0.12;
double const E_0 = 18.6;

// numeric integration according to Newton-Cotes formula: Composite Trapezoidal Rule
// numerator
auto f1 = [](double const &E) {
    double t1 = (E + m_ec2);
    double t2 = (E_0 - E + m_nuc2);
    double t3 = std::sqrt(t1 * t1 - m_ec2 * m_ec2);
    double t4 = std::sqrt(t2 * t2 - m_nuc2 * m_nuc2);
    return E * t1 * t2 * t3 * t4;
};

// denominator
auto f2 = [](double const &E) {
    double t1 = (E + m_ec2);
    double t2 = (E_0 - E + m_nuc2);
    double t3 = std::sqrt(t1 * t1 - m_ec2 * m_ec2);
    double t4 = std::sqrt(t2 * t2 - m_nuc2 * m_nuc2);
    return t1 * t2 * t3 * t4;
};

// approximation for testing
// numerator
auto f3 = [](double const &E) {
    return E * std::sqrt(E) * (E_0 - E) * (E_0 - E);
};

// denominator
auto f4 = [](double const &E) {
    return std::sqrt(E) * (E_0 - E) * (E_0 - E);
};

// integration function
auto integrate = [](int const &n, double const &x0, double const &x1, auto const &func) {
    // h parameter
    double h = (x1 - x0) / n;
    // result of the summation
    double sum = 0;
    // summation
    for (int i = 1; i <= n - 1; i++)
    {
        double x = x0 + i * h;
        sum += func(x);
    }
    // the result will be stored in this variable
    return h / 2 * (func(x0) + 2 * sum + func(x1));
};

// main function
int main(int, char **)
{
    // set precision
    std::cout.precision(16);

    // parameters
    double const x0 = 0.;
    double const x1 = E_0;
    int const n = (int)1e8;

    // integration results
    // test for multiple
    /*
    for (int i = 4; i <= 8; i++)
    {
        int n = (int)std::pow(10, i);
        double result1 = integrate(n, x0, x1, f1);
        double result2 = integrate(n, x0, x1, f2);
        std::cout << result1 << std::endl;
        std::cout << result2 << std::endl;
        std::cout << result1 / result2 << std::endl;
        std::cout << "------" << std::endl;
    }
    */
    // result
    std::cout << integrate(n, x0, x1, f1) / integrate(n, x0, x1, f2) << std::endl;
    // approximation
    std::cout << integrate(n, x0, x1, f3) / integrate(n, x0, x1, f4) << std::endl;
}
