#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

using namespace std;

namespace geneInfo {

    const /*expr*/ string_view geneBegin = "AA";
    const /*expr*/ string_view geneEnd = "BB";

} // namespace geneInfo

enum class Resistance { NONE, RESISTANT, STRONGLY_RESISTANT };

ostream& operator<<(ostream& stream, Resistance resistance) {
    switch(resistance) {
    case Resistance::NONE:
        return stream << "none";

    case Resistance::RESISTANT:
        return stream << "resistant";

    case Resistance::STRONGLY_RESISTANT:
        return stream << "strongly_resistant";

    default:
        stream.setstate(ios_base::failbit);
        return stream;
    }
}

template<typename ForwardIt, typename OutputIt>
void MakeGenes(ForwardIt first, ForwardIt last, OutputIt output) {
    while(first != last) {
        const auto geneBegin = search(first, last, geneInfo::geneBegin.begin(), geneInfo::geneBegin.end());

        auto geneEnd = search(geneBegin, last, geneInfo::geneEnd.begin(), geneInfo::geneEnd.end());

        if(geneEnd != last) {
            advance(geneEnd, geneInfo::geneEnd.size());

            *output = string{geneBegin, geneEnd};
            ++output;
        }

        first = geneEnd;
    }
}

class Genotype {
public:
    Genotype() = default;

    explicit Genotype(string_view code)
        : code(code) {
        MakeGenes(this->code.begin(), this->code.end(), back_inserter(genes));
        resistance = CalculateResistance();
    }

    size_t Length() const {
        return code.size();
    }

    bool HasMutation() const {
        return find_if(genes.begin(), genes.end(), [](const string& gene) {
                   return gene.find("BCDDC") != string::npos;
               }) != genes.end();
    }

    size_t GeneCount() const {
        return genes.size();
    }

    size_t LongestGene() const {
        return max_element(genes.begin(), genes.end(),
                           [](const string& left, const string& right) {
                               return left.size() < right.size();
                           })
            ->size();
    }

    bool IsResistant() const {
        return resistance == Resistance::RESISTANT || IsStronglyResistant();
    }

    bool IsStronglyResistant() const {
        return resistance == Resistance::STRONGLY_RESISTANT;
    }

private:
    Resistance CalculateResistance() const {
        if(equal(code.begin(), code.begin() + (code.size() / 2), code.rbegin())) {
            return Resistance::STRONGLY_RESISTANT;
        }

        vector<string> reverseGenes;
        MakeGenes(code.rbegin(), code.rend(), back_inserter(reverseGenes));

        if(genes == reverseGenes) {
            return Resistance::RESISTANT;
        }

        return Resistance::NONE;
    }

    string code;
    vector<string> genes;
    Resistance resistance;

    friend istream& operator>>(istream& stream, Genotype& gene) {
        if(string code; stream >> code) {
            gene = Genotype(code);
        }

        return stream;
    }
};

class Program {
public:
    Program() {
        ifstream file("dane_geny.txt");

        for(Genotype gene; file >> gene;) {
            genotypes.push_back(move(gene));
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
        map<size_t, size_t> typeCounter;

        for(auto&& genotype : genotypes) {
            ++typeCounter[genotype.Length()];
        }

        cout << "1)\n" << typeCounter.size() << '\n';

        cout << max_element(typeCounter.begin(), typeCounter.end(), [](const auto& left, const auto& right) {
                    return left.second < right.second;
                })->second;

        cout << '\n';
    }

    void Task2() {
        cout << "2) " << count_if(genotypes.begin(), genotypes.end(), mem_fn(&Genotype::HasMutation)) << '\n';
    }

    void Task3() {
        cout << "3)\n";

        cout << "max gene count: ";
        cout << max_element(genotypes.begin(), genotypes.end(), [](const Genotype& left, const Genotype& right) {
                    return left.GeneCount() < right.GeneCount();
                })->GeneCount();
        cout << '\n';

        cout << "longest gene: ";
        cout << max_element(genotypes.begin(), genotypes.end(), [](const Genotype& left, const Genotype& right) {
                    return left.LongestGene() < right.LongestGene();
                })->LongestGene();
        cout << '\n';
    }

    void Task4() {
        cout << "4)\n";

        cout << Resistance::RESISTANT << ": ";
        cout << count_if(genotypes.begin(), genotypes.end(), mem_fn(&Genotype::IsResistant)) << '\n';

        cout << Resistance::STRONGLY_RESISTANT << ": ";
        cout << count_if(genotypes.begin(), genotypes.end(), mem_fn(&Genotype::IsStronglyResistant)) << '\n';
    }

    vector<Genotype> genotypes;
};

int main() {
    Program program;
    program.Run();
}