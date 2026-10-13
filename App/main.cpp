#include <iostream>
#include <string>
#include <stdexcept>
#include "matrix.h"
#include "trianglematrix.h"

// Вспомогательная функция для безопасного ввода размеров
size_t input_size(const std::string& prompt) {
    int size;
    while (true) {
        std::cout << prompt;
        if (std::cin >> size && size > 0) {
            return static_cast<size_t>(size);
        }
        std::cout << "Ошибка! Введите положительное целое число.\n";
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }
}

// Вспомогательная функция для безопасного ввода вещественного числа
double input_scalar(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            return val;
        }
        std::cout << "Ошибка! Некорректное число.\n";
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }
}

// Функция для ручного ввода обычной квадратной матрицы
Matrix<double> input_ordinary_matrix(size_t N) {
    std::cout << "Введите элементы матрицы " << N << "x" << N << " построчно:\n";
    Matrix<double> mat(N, N);
    for (size_t i = 1; i <= N; ++i) {
        for (size_t j = 1; j <= N; ++j) {
            std::cout << "Элемент [" << i << "][" << j << "]: ";
            std::cin >> mat[i][j];
        }
    }
    return mat;
}

// Функция для ручного ввода треугольной матрицы (только элементы на и выше диагонали)
TriangleMatrix<double> input_triangle_matrix(size_t N) {
    std::cout << "Введите элементы верхнетреугольной матрицы " << N << "x" << N << " (элементы ниже диагонали автоматически станут 0):\n";
    TriangleMatrix<double> mat(N);
    for (size_t i = 1; i <= N; ++i) {
        for (size_t j = i; j <= N; ++j) {
            std::cout << "Элемент [" << i << "][" << j << "]: ";
            std::cin >> mat[i][j];
        }
    }
    return mat;
}

void show_menu() {
    std::cout << "\n================= МАТРИЧНЫЙ КАЛЬКУЛЯТОР =================\n"
        << "1. Матричные операции с Matrix (+, -, *, +=, -=, *=)\n"
        << "2. Матричные операции с TriangleMatrix (+, -, *, +=, -=, *=)\n"
        << "3. Скалярные операции с Matrix (*, /, *=, /=)\n"
        << "4. Скалярные операции с TriangleMatrix (*, /, *=, /=)\n"
        << "5. Вычислить определитель треугольной матрицы\n"
        << "0. Выход\n"
        << "=========================================================\n"
        << "Выберите пункт меню: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice = -1;

    while (choice != 0) {
        show_menu();
        if (!(std::cin >> choice)) {
            std::cout << "Некорректный ввод! Выберите число из меню.\n";
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            size_t N = input_size("Введите размер квадратных матриц: ");
            std::cout << "\n--- Ввод матрицы A ---\n";
            Matrix<double> A = input_ordinary_matrix(N);
            std::cout << "\n--- Ввод матрицы B ---\n";
            Matrix<double> B = input_ordinary_matrix(N);

            std::cout << "\nВыберите операцию (+, -, *, +=, -=, *=): ";
            std::string op;
            std::cin >> op;

            try {
                if (op == "+") {
                    std::cout << "Результат A + B:\n" << (A + B);
                }
                else if (op == "-") {
                    std::cout << "Результат A - B:\n" << (A - B);
                }
                else if (op == "*") {
                    std::cout << "Результат A * B:\n" << (A * B);
                }
                else if (op == "+=") {
                    A += B;
                    std::cout << "Матрица A после (A += B):\n" << A;
                }
                else if (op == "-=") {
                    A -= B;
                    std::cout << "Матрица A после (A -= B):\n" << A;
                }
                else if (op == "*=") {
                    A *= B;
                    std::cout << "Матрица A после (A *= B):\n" << A;
                }
                else {
                    std::cout << "Ошибка: Неизвестная операция!\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
            break;
        }
        case 2: {
            size_t N = input_size("Введите размер треугольных матриц: ");
            std::cout << "\n--- Ввод треугольной матрицы A ---\n";
            TriangleMatrix<double> A = input_triangle_matrix(N);
            std::cout << "\n--- Ввод треугольной матрицы B ---\n";
            TriangleMatrix<double> B = input_triangle_matrix(N);

            std::cout << "\nВыберите операцию (+, -, *, +=, -=, *=): ";
            std::string op;
            std::cin >> op;

            try {
                if (op == "+") {
                    std::cout << "Результат A + B:\n" << (A + B);
                }
                else if (op == "-") {
                    std::cout << "Результат A - B:\n" << (A - B);
                }
                else if (op == "*") {
                    std::cout << "Результат A * B:\n" << (A * B);
                }
                else if (op == "+=") {
                    A += B;
                    std::cout << "Матрица A после (A += B):\n" << A;
                }
                else if (op == "-=") {
                    A -= B;
                    std::cout << "Матрица A после (A -= B):\n" << A;
                }
                else if (op == "*=") {
                    A *= B;
                    std::cout << "Матрица A после (A *= B):\n" << A;
                }
                else {
                    std::cout << "Ошибка: Неизвестная операция!\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
            break;
        }
        case 3: {
            size_t N = input_size("Введите размер матрицы: ");
            Matrix<double> A = input_ordinary_matrix(N);

            std::cout << "\nВыберите скалярную операцию (*, /, *=, /=): ";
            std::string op;
            std::cin >> op;

            double scalar = input_scalar("Введите число (скаляр): ");

            try {
                if (op == "*") {
                    std::cout << "Результат левого умножения (скаляр * Matrix):\n" << (scalar * A);
                    std::cout << "Результат правого умножения (Matrix * скаляр):\n" << (A * scalar);
                }
                else if (op == "/") {
                    std::cout << "Результат деления (Matrix / скаляр):\n" << (A / scalar);
                }
                else if (op == "*=") {
                    A *= scalar;
                    std::cout << "Матрица A после (A *= скаляр):\n" << A;
                }
                else if (op == "/=") {
                    A /= scalar;
                    std::cout << "Матрица A после (A /= скаляр):\n" << A;
                }
                else {
                    std::cout << "Ошибка: Неизвестная операция!\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
            break;
        }
        case 4: {
            size_t N = input_size("Введите размер треугольной матрицы: ");
            TriangleMatrix<double> A = input_triangle_matrix(N);

            std::cout << "\nВыберите скалярную операцию (*, /, *=, /=): ";
            std::string op;
            std::cin >> op;

            double scalar = input_scalar("Введите число (скаляр): ");

            try {
                if (op == "*") {
                    std::cout << "Результат левого умножения (скаляр * TriangleMatrix):\n" << (scalar * A);
                    std::cout << "Результат правого умножения (TriangleMatrix * скаляр):\n" << (A * scalar);
                }
                else if (op == "/") {
                    std::cout << "Результат деления (TriangleMatrix / скаляр):\n" << (A / scalar);
                }
                else if (op == "*=") {
                    A *= scalar;
                    std::cout << "Матрица A после (A *= скаляр):\n" << A;
                }
                else if (op == "/=") {
                    A /= scalar;
                    std::cout << "Матрица A после (A /= скаляр):\n" << A;
                }
                else {
                    std::cout << "Ошибка: Неизвестная операция!\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
            break;
        }
        case 5: {
            size_t N = input_size("Введите размер треугольной матрицы: ");
            TriangleMatrix<double> A = input_triangle_matrix(N);
            std::cout << "\nВведенная матрица:\n" << A;

            auto& non_const_A = const_cast<TriangleMatrix<double>&>(A);
            std::cout << "Определитель треугольной матрицы равен: " << non_const_A.getDeterminant() << "\n";
            break;
        }
        case 0:
            std::cout << "Выход из программы Матричный калькулятор. До свидания!\n";
            break;
        default:
            std::cout << "Неверный пункт меню! Выберите число от 0 до 5.\n";
            break;
        }
    }
    return 0;
}
