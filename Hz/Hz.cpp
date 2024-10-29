#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
// Абстрактный класс Test
class Test {
public:
    virtual int get_total_score() const = 0;
    virtual int get_solved_problems_count() const = 0;
    virtual int get_max_score() const = 0;
};

// Класс HeirTest (потомок класса Test)
class HeirTest : public Test {
private:
    string country;
    string team;
    vector<int> solvedProblems;

public:
    HeirTest() {
        country = "";
        team = "";
        vector<int> tmp;
        solvedProblems = tmp;
    }
    HeirTest(const string& country, const string& team, const vector<int>& solvedProblems)
        : country(country), team(team), solvedProblems(solvedProblems) {
    }

    virtual int get_total_score() const override {
        int totalScore = 0;
        for (int i = 0; i < solvedProblems.size(); i++) {
            totalScore += solvedProblems[i];
        }
        return totalScore;
    }

    virtual int get_solved_problems_count() const override {
        return solvedProblems.size();
    }

    virtual int get_max_score() const override {
        int maxScore = 0;
        for (int i = 0; i < solvedProblems.size(); i++) {
            maxScore = max(maxScore, solvedProblems[i]);
        }
        return maxScore;
    }

    const string& get_country() const {
        return country;
    }

    const string& get_team() const {
        return team;
    }

    const vector<int>& get_solved_problems() const {
        return solvedProblems;
    }
};

// Класс Prises (наследник класса HeirTest)
class Prises : public HeirTest {
private:
    int diplomaNumber;
    string prizeName;

public:
    Prises(const string& country, const string& team, const vector<int>& solvedProblems,
        int diplomaNumber, const string& prizeName)
        : HeirTest(country, team, solvedProblems), diplomaNumber(diplomaNumber), prizeName(prizeName) {
    }

    int get_diploma_number() const {
        return diplomaNumber;
    }

    const string& get_prize_name() const {
        return prizeName;
    }
    Prises() {
        diplomaNumber = 0;
        prizeName = "";
    }
};

// Функция сравнения результатов по общему баллу (для сортировки)
bool compareByTotalScore(const Prises& result1, const Prises& result2) {
    return result1.get_total_score() > result2.get_total_score();
}

// Функция записи результатов в файл
void writeToFile(const vector<Prises>& results, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const Prises& result : results) {
            file << "Country: " << result.get_country() << endl;
            file << "Team: " << result.get_team() << endl;
            file << "Total Score: " << result.get_total_score() << endl;
            file << "Diploma Number: " << result.get_diploma_number() << endl;
            file << "Prize Name: " << result.get_prize_name() << endl;
            file << endl;
        }
        file.close();
        cout << "Results written to file: " << filename << endl;
    }
    else {
        cerr << "Unable to write to file: " << filename << endl;
    }
}

// Функция чтения данных из файла Olimp.txt и создания объектов Prises
vector<Prises> readOlimpFile(const string& filename) {
    vector<Prises> results;

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t countryEndPos = line.find(' ');
            string country = line.substr(0, countryEndPos);
            line = line.substr(countryEndPos + 1);

            size_t teamEndPos = line.find(':');
            string team = line.substr(0, teamEndPos);
            line = line.substr(teamEndPos + 1);
            vector<int> solved_problems;
            size_t spacePos = line.find(' ');
            bool flag = 0;
            while (spacePos != string::npos) {
                if (flag) {
                    string scoreStr = line.substr(0, spacePos);
                    int score = stoi(scoreStr);
                    solved_problems.push_back(score);
                }
                else
                {
                    flag = 1;
                }
                line = line.substr(spacePos + 1);
                spacePos = line.find(' ');
            }
            if (!line.empty()) {
                int score = stoi(line);
                solved_problems.push_back(score);
            }

            Prises result(country, team, solved_problems, 0, "");
            results.push_back(result);
        }

        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }

    return results;
}


// Функция чтения данных из файла Prizy.txt и заполнения дипломов и призов
void fillDiplomasAndPrizes(vector<Prises>& results, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        int diplomaNumber = 1;
        while (getline(file, line)) {
            istringstream iss(line);
            string prizeName;

            iss >> prizeName;

            if (diplomaNumber <= results.size()) {
                results[diplomaNumber - 1] = Prises(results[diplomaNumber - 1].get_country(),
                    results[diplomaNumber - 1].get_team(),
                    results[diplomaNumber - 1].get_solved_problems(),
                    diplomaNumber,
                    prizeName);
            }

            diplomaNumber++;
        }

        file.close();
        cout << "Diplomas and prizes filled from file: " << filename << endl;
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

int main() {
    // Чтение данных из файла Olimp.txt
    vector<Prises> results = readOlimpFile("Olimp.txt");

    // Заполнение дипломов и призов из файла Prizy.txt
    fillDiplomasAndPrizes(results, "Prizy.txt");

    // Сортировка результатов по общему баллу
    sort(results.begin(), results.end(), compareByTotalScore);

    // Запись результатов в текстовый файл Result.txt
    writeToFile(results, "Result.txt");

    // Запись результатов в бинарный файл Result.bin
    ofstream binaryFile("Result.bin", ios::binary);
    if (binaryFile.is_open()) {
        for (const Prises& result : results) {
            binaryFile.write(reinterpret_cast<const char*>(&result), sizeof(Prises));
        }
        binaryFile.close();
        cout << "Results written to binary file: Result.bin" << endl;
    }
    else {
        cerr << "Unable to write to binary file: Result.bin" << endl;
    }
}