bool CompareByFractionDescending(const double& num1, const double& num2) {
    double fraction1 = num1 - static_cast<int>(num1);
    double fraction2 = num2 - static_cast<int>(num2);

    return fraction1 > fraction2;
}


void SwapNumbers(double& num1, double& num2) {
    double temp = num1;
    num1 = num2;
    num2 = temp;
}

void SortNumbers(double* numbers, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (CompareByFractionDescending(numbers[j], numbers[j + 1])) {
                SwapNumbers(numbers[j], numbers[j + 1]);
            }
        }
    }
}
