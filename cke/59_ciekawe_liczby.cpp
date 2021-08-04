#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>

using namespace std;

constexpr bool Has3DifferentFactors(int value) {
    if(value % 2 == 0) {
        return false;
    }

    int factorsCounter = 0;

    for(int factor = 3; value > 1; factor += 2) {
        if(value % factor == 0) {
            ++factorsCounter;

            do {
                value /= factor;
            } while(value % factor == 0);
        }

        if(factorsCounter > 3) {
            return false;
        }
    }

    return factorsCounter == 3;
}

constexpr int ReverseNumber(int value) {
    int reversedNumber = 0;

    while(value != 0) {
        reversedNumber *= 10;
        reversedNumber += value % 10;
        value /= 10;
    }

    return reversedNumber;
}

bool IsPalindrome(int value) {
    const string str = to_string(value);
    return equal(str.begin(), str.begin() + (str.size() / 2), str.rbegin());
}

constexpr int DigitProduct(int value) {
    int product = 1;
    while(value != 0) {
        product *= value % 10;
        value /= 10;
    }

    return product;
}

constexpr bool HasOnlyOneDigit(int value) {
    return (value / 10) == 0;
}

constexpr int PowerOfNumber(int value) {
    int power = 0;
    while(!HasOnlyOneDigit(value)) {
        value = DigitProduct(value);
        ++power;
    }
    return power;
}

inline namespace Test {

    static_assert(Has3DifferentFactors(32) == false);
    static_assert(Has3DifferentFactors(210) == false);
    static_assert(Has3DifferentFactors(1331) == false);
    static_assert(Has3DifferentFactors(1157625) == true);
    static_assert(Has3DifferentFactors(105) == true);

    static_assert(ReverseNumber(123) == 321);
    static_assert(ReverseNumber(1113111) == 1113111);
    static_assert(ReverseNumber(4334) == 4334);
    static_assert(ReverseNumber(789) == 987);
    static_assert(ReverseNumber(2223) == 3222);

    static_assert(DigitProduct(234) == 24);
    static_assert(DigitProduct(531) == 15);
    static_assert(DigitProduct(8761) == 336);
    static_assert(DigitProduct(11) == 1);
    static_assert(DigitProduct(10) == 0);

    static_assert(HasOnlyOneDigit(31) == false);
    static_assert(HasOnlyOneDigit(15) == false);
    static_assert(HasOnlyOneDigit(5) == true);
    static_assert(HasOnlyOneDigit(0) == true);
    static_assert(HasOnlyOneDigit(1) == true);

    static_assert(PowerOfNumber(678) == 4);
    static_assert(PowerOfNumber(1991) == 2);

} // namespace Test

int main() {
    ifstream file("liczby.txt");

    int has3DifferentFactorsCounter = 0;
    int isReversedSumPalindromeCounter = 0;

    map<int, size_t> powerCounter;
    for(int i = 1; i <= 8; ++i) {
        powerCounter[i] = 0;
    }

    int maxNumberWithPower1 = 0;
    int minNumberWithPower1 = numeric_limits<int>::max();

    for(int value; file >> value;) {
        if(Has3DifferentFactors(value)) {
            ++has3DifferentFactorsCounter;
        }

        const int reversedSum = value + ReverseNumber(value);
        if(IsPalindrome(reversedSum)) {
            ++isReversedSumPalindromeCounter;
        }

        const int powerOfNumber = PowerOfNumber(value);
        ++powerCounter[powerOfNumber];

        if(powerOfNumber == 1) {
            maxNumberWithPower1 = max(maxNumberWithPower1, value);
            minNumberWithPower1 = min(minNumberWithPower1, value);
        }
    }

    cout << "1) " << has3DifferentFactorsCounter << '\n';
    cout << "2) " << isReversedSumPalindromeCounter << '\n';

    cout << "3) moc: ilosc\n";
    for(auto [power, count] : powerCounter) {
        cout << power << ": " << count << '\n';
    }

    cout << '\n';
    cout << "max: " << maxNumberWithPower1 << '\n';
    cout << "min: " << minNumberWithPower1 << '\n';
}