#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <optional>
#include <utility>
#include <vector>

using namespace std;

constexpr size_t ARRAY_SIZE = 20;

enum class Pixel { WHITE = 0, BLACK = 1 };

istream& operator>>(istream& stream, Pixel& pixel) {
    char temp;
    stream >> temp;
    pixel = static_cast<Pixel>(temp - '0');

    return stream;
}

ostream& operator<<(ostream& stream, Pixel pixel) {
    return stream << static_cast<int>(pixel);
}

enum class PictureState { CORRECT, REPAIRABLE, UNREPAIRABLE };

ostream& operator<<(ostream& stream, PictureState state) {
    switch(state) {
    case PictureState::CORRECT:
        return stream << "correct";

    case PictureState::REPAIRABLE:
        return stream << "repairable";

    case PictureState::UNREPAIRABLE:
        return stream << "unrepairable";

    default:
        stream.setstate(ios_base::failbit);
        return stream;
    }
}

class Picture {
public:
    Picture() = default;

    Picture(const Picture&) = delete;
    Picture(Picture&&) = default;

    void operator=(const Picture&) = delete;
    Picture& operator=(Picture&&) = default;

    size_t CountBlackPixels() const {
        return accumulate(pixels.begin(), pixels.end(), size_t{}, [](size_t blackCount, const auto& row) {
            return blackCount + count(row.begin(), row.end(), Pixel::BLACK);
        });
    }

    bool IsReverse() const {
        return CountBlackPixels() > 200;
    }

    bool IsRecursive() const {
        for(size_t p = 0; p < 10; ++p) {
            for(size_t q = 0; q < 10; ++q) {
                const bool areSame = pixels[p][q] == pixels[p + 10][q] && pixels[p + 10][q] == pixels[p][q + 10] &&
                                     pixels[p][q + 10] == pixels[p + 10][q + 10];

                if(!areSame) {
                    return false;
                }
            }
        }

        return true;
    }

    Pixel GetPairBitInRow(size_t rowIndex) const {
        const size_t blackCount = count(pixels[rowIndex].begin(), pixels[rowIndex].end(), Pixel::BLACK);
        return static_cast<Pixel>(blackCount % 2 != 0);
    }

    Pixel GetPairBitInColumn(size_t columnIndex) const {
        const size_t blackCount = count_if(pixels.begin(), pixels.end(),
                                           [columnIndex](const auto& row) { return row[columnIndex] == Pixel::BLACK; });

        return static_cast<Pixel>(blackCount % 2 != 0);
    }

    bool IsPairBitInvalidInRow(size_t rowIndex) const {
        return GetPairBitInRow(rowIndex) != rowPairBit[rowIndex];
    }

    bool IsPairBitInvalidInColumn(size_t columnIndex) const {
        return GetPairBitInColumn(columnIndex) != columnPairBit[columnIndex];
    }

    pair<size_t, size_t> GetInvalidRowAndColumnPairBits() const {
        size_t invalidPairBitInRowCounter = 0;
        size_t invalidPairBitInColumnCounter = 0;

        for(size_t index = 0; index < ARRAY_SIZE; ++index) {
            if(IsPairBitInvalidInRow(index)) {
                ++invalidPairBitInRowCounter;
            }

            if(IsPairBitInvalidInColumn(index)) {
                ++invalidPairBitInColumnCounter;
            }
        }

        return {invalidPairBitInRowCounter, invalidPairBitInColumnCounter};
    }

    PictureState GetState() const {
        auto [invalidPairBitInRowCounter, invalidPairBitInColumnCounter] = GetInvalidRowAndColumnPairBits();

        if(invalidPairBitInColumnCounter > 1 || invalidPairBitInRowCounter > 1) {
            return PictureState::UNREPAIRABLE;
        } else if(invalidPairBitInColumnCounter == 1 || invalidPairBitInRowCounter == 1) {
            return PictureState::REPAIRABLE;
        }

        return PictureState::CORRECT;
    }

    size_t GetInvalidBitsCount() const {
        const pair<size_t, size_t> invalidBits = GetInvalidRowAndColumnPairBits();
        return invalidBits.first + invalidBits.second;
    }

    optional<pair<size_t, size_t>> GetPixelToRepair() const {
        if(PictureState state = GetState(); state == PictureState::CORRECT || state == PictureState::UNREPAIRABLE) {
            return nullopt;
        }

        size_t row;
        for(row = 0; row < ARRAY_SIZE; ++row) {
            if(IsPairBitInvalidInRow(row)) {
                break;
            }
        }

        size_t column = 0;
        for(column = 0; column < ARRAY_SIZE; ++column) {
            if(IsPairBitInvalidInColumn(column)) {
                break;
            }
        }

        return make_pair(row + 1, column + 1);
    }

private:
    array<array<Pixel, ARRAY_SIZE>, ARRAY_SIZE> pixels;
    array<Pixel, ARRAY_SIZE> rowPairBit;
    array<Pixel, ARRAY_SIZE> columnPairBit;

    friend istream& operator>>(istream& stream, Picture& picture) {
        if(!(stream >> ws)) {
            return stream;
        }

        for(size_t index = 0; index < ARRAY_SIZE; ++index) {
            copy_n(istream_iterator<Pixel>{stream}, ARRAY_SIZE, picture.pixels[index].begin());
            stream >> picture.rowPairBit[index];
        }

        copy_n(istream_iterator<Pixel>(stream), ARRAY_SIZE, picture.columnPairBit.begin());
        return stream;
    }

    friend ostream& operator<<(ostream& stream, const Picture& picture) {
        for(auto&& row : picture.pixels) {
            copy(row.begin(), row.end(), ostream_iterator<Pixel>(stream));
            stream << '\n';
        }

        return stream;
    }
};

class Program {
public:
    Program() {
        ifstream file("dane_obrazki.txt");

        for(Picture temp; file >> temp;) {
            pictures.push_back(move(temp));
        }
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
        cout << "reverse count: " << count_if(pictures.begin(), pictures.end(), mem_fn(&Picture::IsReverse)) << '\n';

        cout << "max black count: "
             << max_element(pictures.begin(), pictures.end(),
                            [](const Picture& left, const Picture& right) {
                                return left.CountBlackPixels() < right.CountBlackPixels();
                            })
                    ->CountBlackPixels()
             << '\n';
    }

    void Task2() {
        auto isRecursive = mem_fn(&Picture::IsRecursive);

        cout << "2)\n";
        cout << "recursive count: " << count_if(pictures.begin(), pictures.end(), isRecursive) << '\n';
        cout << "first recursive:\n";
        cout << *find_if(pictures.begin(), pictures.end(), isRecursive);
    }

    void Task3() {
        map<PictureState, size_t> stateCounter;

        for(auto&& picture : pictures) {
            ++stateCounter[picture.GetState()];
        }

        cout << "3)\n";
        for(auto [state, count] : stateCounter) {
            cout << state << " count: " << count << '\n';
        }

        cout << "max invalid pair bits: ";

        cout << max_element(pictures.begin(), pictures.end(), [](const Picture& left, const Picture& right) {
                    return left.GetInvalidBitsCount() < right.GetInvalidBitsCount();
                })->GetInvalidBitsCount();

        cout << '\n';
    }

    void Task4() {
        cout << "3)\n";

        for(size_t index = 0; index < pictures.size(); ++index) {
            if(const auto pixelToRepair = pictures[index].GetPixelToRepair(); pixelToRepair.has_value()) {
                cout << '(' << (index + 1) << ", " << pixelToRepair->first << ", ";
                cout << pixelToRepair->second << ")\n";
            }
        }
    }

    vector<Picture> pictures;
};

int main() {
    Program program;
    program.Run();
}