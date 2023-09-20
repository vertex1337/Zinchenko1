void CountNumbers(const double* numbers, int size, int& goodCount, int& badCount, int& zeroCount) {
    goodCount = 0;
    badCount = 0;
    zeroCount = 0;

    for (int i = 0; i < size; i++) {
        double num = numbers[i];
        if (num == 0) {
            zeroCount++;
        }
        else if (static_cast<int>(num) % 2 == 0) {
            badCount++;
        }
        else {
            goodCount++;
        }
    }
}