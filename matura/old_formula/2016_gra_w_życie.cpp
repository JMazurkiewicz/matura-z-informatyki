#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>

using namespace std;

constexpr size_t ROWS = 12;
constexpr size_t COLUMNS = 20;

enum class Cell : char { DEAD = '.', ALIVE = 'X' };

istream& operator>>(istream& stream, Cell& cell) {
    char symbol;
    stream >> symbol;
    cell = static_cast<Cell>(symbol);

    return stream;
}

class GameOfLife {
private:
    using Board = array<array<Cell, COLUMNS>, ROWS>;

public:
    constexpr GameOfLife NextGeneration() const {
        GameOfLife nextGeneration{};

        for(size_t rowIndex = 0; rowIndex < ROWS; ++rowIndex) {
            for(size_t columnIndex = 0; columnIndex < COLUMNS; ++columnIndex) {
                nextGeneration.board[rowIndex][columnIndex] = GetNextCellAt(rowIndex, columnIndex);
            }
        }

        return nextGeneration;
    }

    constexpr Cell At(size_t row, size_t column) const {
        return board[row][column];
    }

    constexpr bool IsAliveAt(size_t row, size_t column) const {
        return At(row, column) == Cell::ALIVE;
    }

    constexpr size_t CountAliveNeighboursForCellAt(size_t row, size_t column) const {
        const size_t upperNeighbourRow = (row == 0) ? (ROWS - 1) : (row - 1);
        const size_t rightNeighbourColumn = (column == COLUMNS - 1) ? (0) : (column + 1);
        const size_t leftNeighbourColumn = (column == 0) ? (COLUMNS - 1) : (column - 1);
        const size_t bottomNeighbourRow = (row == ROWS - 1) ? (0) : (row + 1);

        const bool isUpperLeftAlive = IsAliveAt(upperNeighbourRow, leftNeighbourColumn);
        const bool isUpperAlive = IsAliveAt(upperNeighbourRow, column);
        const bool isUpperRightAlive = IsAliveAt(upperNeighbourRow, rightNeighbourColumn);
        const bool isLeftAlive = IsAliveAt(row, leftNeighbourColumn);
        const bool isRightAlive = IsAliveAt(row, rightNeighbourColumn);
        const bool isBottomLeftAlive = IsAliveAt(bottomNeighbourRow, leftNeighbourColumn);
        const bool isBottomAlive = IsAliveAt(bottomNeighbourRow, column);
        const bool isBottomRightAlive = IsAliveAt(bottomNeighbourRow, rightNeighbourColumn);

        return isUpperLeftAlive + isUpperAlive + isUpperRightAlive + isLeftAlive + isRightAlive + isBottomLeftAlive +
               isBottomAlive + isBottomRightAlive;
    }

    constexpr Cell GetNextCellAt(size_t row, size_t column) const {
        const size_t aliveNeighbours = CountAliveNeighboursForCellAt(row, column);

        if(At(row, column) == Cell::ALIVE) {
            return (aliveNeighbours == 2 || aliveNeighbours == 3) ? Cell::ALIVE : Cell::DEAD;
        } else {
            return (aliveNeighbours == 3) ? Cell::ALIVE : Cell::DEAD;
        }
    }

    size_t CountAliveCells() const {
        return accumulate(board.begin(), board.end(), size_t{}, [](size_t sum, const Board::value_type& row) {
            return sum + count(row.begin(), row.end(), Cell::ALIVE);
        });
    }

    bool operator==(const GameOfLife& other) const {
        return board == other.board;
    }

private:
    Board board;

    friend istream& operator>>(istream& stream, GameOfLife& game) {
        for(auto&& row : game.board) {
            copy_n(istream_iterator<Cell>{stream}, row.size(), row.begin());
        }

        return stream;
    }
};

class Program {
public:
    Program() {
        ifstream{"gra.txt"} >> game;
    }

    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() const {
        GameOfLife generation = game;

        for(size_t i = 1; i < 37; ++i) {
            generation = generation.NextGeneration();
        }

        cout << "1) " << generation.CountAliveNeighboursForCellAt(1, 18) << '\n';
    }

    void Task2() const {
        cout << "2) " << game.NextGeneration().CountAliveCells() << '\n';
    }

    void Task3() const {
        GameOfLife generation = game;

        size_t generationCounter = 1;
        while(true) {
            GameOfLife nextGeneration = generation.NextGeneration();
            ++generationCounter;

            if(nextGeneration == generation) {
                break;
            }

            generation = nextGeneration;
        }

        cout << "3)\n";
        cout << "generation: " << generationCounter << '\n';
        cout << "alive cells: " << generation.CountAliveCells() << '\n';
    }

    GameOfLife game;
};

int main() {
    Program program;
    program.Run();
}