#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include "count.h"
#include "sort.h"

using namespace std;

char* getExtension(char* filename) {
    int len = strlen(filename);
    char* extension;

    int index = -1;
    if (len > 3) {
        for (int i = len; i > 0; i--) {
            if (filename[i] == '.') {
                index = i;
                break;
            }
        }
        for (int i = index; i < len; i++) {
            if (filename[i] >= 'A' && filename[i] <= 'Z' || filename[i] >= 'a' && filename[i] <= 'z') {
                return filename + index;
            }
        }
    }
    if (index == -1) {
        return NULL;
    }
    return NULL;
}


double* readNumbers(const char* filename, int& numCount) {
    ifstream inputFile(filename);
    double* numbers = nullptr;
    numCount = 0;

    if (!inputFile.is_open()) {
        cerr << "Ошибка: Невозможно открыть файл " << filename << endl;
        return numbers;
    }

    double num;
    while (inputFile >> num) {
        numCount++;
        double* newNumbers = new double[numCount];
        for (int i = 0; i < numCount - 1; i++) {
            newNumbers[i] = numbers[i];
        }
        newNumbers[numCount - 1] = num;

        delete[] numbers;
        numbers = newNumbers;
    }

    inputFile.close();
    return numbers;
}

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    double* nums = nullptr;
    int numCount = 0;
    string outputFile = "";

    if (argc == 1) {
        string fileName;
        bool fileReadSuccess = false;
        do {
            cout << "Введите имя файла для чтения:  ";
            cin >> fileName;
            nums = readNumbers(fileName.c_str(), numCount);
            if (nums != nullptr) {
                fileReadSuccess = true;
            }
            else {
                cout << "Неправильное имя файла, попробуйте еще раз.\n";
            }
        } while (!fileReadSuccess);
    }
    else {
        for (int i = 1; i < argc; i++) {
            if (argc - 1 == i) {
                if (getExtension(argv[i]) != NULL) {
                    outputFile = argv[i];
                    break;
                }
            }
            numCount++;
            double* newNums = new double[numCount];
            for (int j = 0; j < numCount - 1; j++) {
                newNums[j] = nums[j];
            }
            newNums[numCount - 1] = atof(argv[i]);

            delete[] nums;
            nums = newNums;
        }
    }

    if (outputFile == "") {
        cout << "Введите имя файла для сохранения: ";
        cin >> outputFile;
    }
    ofstream outfile(outputFile);


    SortNumbers(nums, numCount);
    int goodCount = 0, badCount = 0, zeroCount = 0;
    CountNumbers(nums, numCount, goodCount, badCount, zeroCount);

    // Запись результатов в файл
    ofstream output_file(outputFile);
    if (!output_file.is_open()) {
        std::cout << "Помилка: Неможливо відкрити вихідний файл." << std::endl;
        delete[] nums;
        return 1;
    }
    cout << "Відсортовані числа:" << endl;
    output_file << "Відсортовані числа:" << endl;
    for (int i = 0; i < numCount; i++) {
        cout << nums[i] << " ";
        output_file << nums[i] << " ";
    }
    output_file << std::endl;
    cout << std::endl;

    output_file << "Кількість 'гарних(odd)' чисел: " << goodCount << std::endl;
    output_file << "Кількість 'поганих(even)' чисел: " << badCount << std::endl;
    output_file << "Кількість 'ніяких(0)' чисел: " << zeroCount << std::endl;
    cout << "Кількість 'гарних(odd)' чисел: " << goodCount << std::endl;
    cout << "Кількість 'поганих(even)' чисел: " << badCount << std::endl;
    cout << "Кількість 'ніяких(0)' чисел: " << zeroCount << std::endl;

    output_file.close();

    std::cout << "Результати успішно записані у файл '" << outputFile << "'" << std::endl;

    delete[] nums;

    return 0;
}
