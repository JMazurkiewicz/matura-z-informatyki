#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

constexpr size_t LINE_COUNT = 1095;

string ToString(int value, int base) {
    const bool isNegative = value < 0;

    if(isNegative) {
        value = -value;
    }

    string result;

    while(value != 0) {
        result += "01234567"[value % base];
        value /= base;
    }

    if(isNegative) {
        result += '-';
    }

    reverse(result.begin(), result.end());
    return result;
}

class Station {
public:
    explicit Station(int base)
        : base(base) { }

    Station(const Station&) = delete;

    int GetLowestTemperature() const {
        const auto minElement = min_element(data.begin(), data.end(), [](const Data& left, const Data& right) {
            return left.temperature < right.temperature;
        });

        return minElement->temperature;
    }

    bool IsIncorrectAt(int index) const {
        return data[index].time != 12 + 24 * index;
    }

    double TemperatureJumpAt(int p, int q) const {
        const double sqrtR = data[p].temperature - data[q].temperature;
        return ceil((sqrtR * sqrtR) / abs(p - q));
    }

private:
    int base;

    struct Data {
        Data()
            : Data(0, 0) { }

        Data(int time, int temperature)
            : time(time)
            , temperature(temperature) { }

        int time;
        int temperature;
    };

    vector<Data> data;

public:
    friend istream& operator>>(istream& stream, Station& station) {
        for(string timeString, temperatureString; stream >> timeString >> temperatureString;) {
            const int time = stoi(timeString, nullptr, station.base);
            const int temperature = stoi(temperatureString, nullptr, station.base);

            station.data.emplace_back(time, temperature);
        }

        return stream;
    }

    friend size_t CountRecordDays(const Station& s1, const Station& s2, const Station& s3) {
        int record1 = numeric_limits<int>::min();
        int record2 = numeric_limits<int>::min();
        int record3 = numeric_limits<int>::min();

        int counter = 0;

        for(size_t index = 0; index < LINE_COUNT; ++index) {
            const int oldRecord1 = record1;
            const int oldRecord2 = record2;
            const int oldRecord3 = record3;

            record1 = max(record1, s1.data[index].temperature);
            record2 = max(record2, s2.data[index].temperature);
            record3 = max(record3, s3.data[index].temperature);

            if(record1 != oldRecord1 || record2 != oldRecord2 || record3 != oldRecord3) {
                ++counter;
            }
        }

        return counter;
    }
};

class Program {
public:
    Program()
        : station2(2)
        , station4(4)
        , station8(8) {
        ios_base::sync_with_stdio(false);

        ifstream("dane_systemy1.txt") >> station2;
        ifstream("dane_systemy2.txt") >> station4;
        ifstream("dane_systemy3.txt") >> station8;
    }

    void Run() {
        Task1();
        Task2();
        Task3();
        Task4();
    }

private:
    void Task1() {
        cout << "1)\n";
        cout << "S1: " << ToString(station2.GetLowestTemperature(), 2) << '\n';
        cout << "S2: " << ToString(station4.GetLowestTemperature(), 2) << '\n';
        cout << "S3: " << ToString(station8.GetLowestTemperature(), 2) << '\n';
        cout << '\n';
    }

    void Task2() {
        int counter = 0;

        for(size_t index = 0; index < LINE_COUNT; ++index) {
            if(station2.IsIncorrectAt(static_cast<int>(index)) && station4.IsIncorrectAt(static_cast<int>(index)) &&
               station8.IsIncorrectAt(static_cast<int>(index))) {
                ++counter;
            }
        }

        cout << "2) " << counter << "\n\n";
    }

    void Task3() {
        cout << "3) " << CountRecordDays(station2, station4, station8) << "\n\n";
    }

    void Task4() {
        double highestTemperatureJump = numeric_limits<double>::min();

        for(size_t p = 0; p < LINE_COUNT; ++p) {
            for(size_t q = p + 1; q < LINE_COUNT; ++q) {
                highestTemperatureJump =
                    max(highestTemperatureJump, station2.TemperatureJumpAt(static_cast<int>(p), static_cast<int>(q)));
            }
        }

        cout << "4) " << highestTemperatureJump << '\n';
    }

    Station station2;
    Station station4;
    Station station8;
};

int main() {
    Program program;
    program.Run();
}