#include <array>
#include <iostream>
#include <limits>

using Real = double;

constexpr Real Abs(Real arg) {
    return (arg < 0) ? (-arg) : arg;
}

class Function {
private:
    using Coefficients = std::array<Real, 4>;

    static constexpr Real precision = 0.00001;

    static constexpr std::array<Coefficients, 5> coefficients = {

        Coefficients{  -1.00000,    1.80861,   0.00000,  0.19139},
        Coefficients{   1.14833,   -4.63636,   6.44498, -1.95694},
        Coefficients{ -51.59809,   74.48325, -33.11483,  4.63636},
        Coefficients{ 224.47368, -201.58852,  58.90909, -5.58852},
        Coefficients{-307.12440,  197.11005, -40.76555,  2.71770}
    };

    static constexpr Real CalculatePart(Real arg, const Coefficients& coeff) {
        return coeff[0] + arg * (coeff[1] + arg * (coeff[2] + arg * coeff[3]));
    }

public:
    static constexpr Real Calculate(Real arg) {
        for(size_t index = 1; index <= 5; ++index) {
            if(arg < index) {
                return CalculatePart(arg, coefficients[index - 1]);
            }
        }

        return std::numeric_limits<Real>::quiet_NaN();
    }

    static constexpr Real FindMax(Real first, Real last) {
        while(first <= last && Calculate(first) < Calculate(first + precision)) {
            first += precision;
        }

        return Calculate(first);
    }

    static constexpr Real FindRoot(Real first, Real last) {
        while(first <= last && Abs(Calculate(first)) > Abs(Calculate(first + precision))) {
            first += precision;
        }

        return first;
    }
};

class Program {
public:
    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() {
        std::cout << "1) " << Function::Calculate(1.5) << '\n';
    }

    void Task2() {
        std::cout << "2) " << Function::FindMax(4.00, 4.25) << '\n';
    }

    void Task3() {
        std::cout << "3)\n";

        std::cout << Function::FindRoot(0.50, 1.00) << '\n';
        std::cout << Function::FindRoot(2.50, 3.00) << '\n';
        std::cout << Function::FindRoot(3.25, 3.50) << '\n';
        std::cout << Function::FindRoot(4.75, 5.00) << '\n';
    }
};

int main() {
    Program program;
    program.Run();
}