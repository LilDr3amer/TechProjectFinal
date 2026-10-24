#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <windows.h>
#pragma execution_character_set("utf-8")
using namespace std;

int findMin(int numbers[], int size) { //поиск минимального
    int min = numbers[0];
    for (int i = 1; i < size; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }
    return min;
}

int findMax(int numbers[], int size) { //поиск максимального
    int max = numbers[0];
    for (int i = 1; i < size; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    return max;
}

double findAverage(int arr[], int size) { //среднее арифметическое
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(65001);
    int size;
    cout << "Введите размер массива от 1 до 10: \n";
    while (!(cin >> size) || size <= 0 || size > 10) {             //проверка на правильность числа
        cout << "Введите положительное число 1 до 10: \n";
        cin.clear();                                               //убирает ошибку
        cin.ignore(10000, '\n');                                   //выбрасывает мусор из буфера
    }

    int* numbers = new int[size];
    cout << "Введите " << size << " целых положительных чисел:\n\n";

    for (int i = 0; i < size; ++i) {                                //заполнение массива с последующими проверками
        int value;
        bool valid = false;
        while (!valid) {
            cout << "Элемент " << i + 1 << ": ";

            if (!(cin >> value)) {
                cout << "Ошибка! Введите целое число: \n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            if (cin.peek() == '.' || cin.peek() == ',') {
                cout << "Дробные не принимаются! Введите целое: \n";
                cin.ignore(10000, '\n');
                continue;
            }

            if (value <= 0) {
                cout << "Число должно быть положительным! Введите: \n";
                continue;
            }
            valid = true;
        }
        numbers[i] = value;
    }

    cout << "Минимальное\t" << findMin(numbers, size) << '\n';
    cout << "Максимальное\t" << findMax(numbers, size) << '\n';
    cout << fixed << setprecision(2);
    cout << "Ср. Ар.\t" << findAverage(numbers, size) << '\n';

    ofstream file("index.html");

    file << "<!DOCTYPE html>\n";
    file << "<html>\n";
    file << "<head>\n";
    file << "<meta charset='UTF-8'>\n";
    file << "<title>Мой отчет</title>\n";

    // --- СТИЛИ ---
    file << "<style>\n";
    file << "  body { font-family: Arial, sans-serif; background-color: #eef2f5; padding: 40px; }\n";
    file << "  .container { max-width: 800px; margin: 0 auto; background: white; padding: 30px; border-radius: 12px; box-shadow: 0 5px 15px rgba(0,0,0,0.1); }\n";
    file << "  h1, h2 { color: #333; text-align: center; }\n";
    file << "  .my-table { width: 100%; border-collapse: collapse; margin-bottom: 30px; text-align: center; }\n";
    file << "  .my-table th { background-color: #007bff; color: white; padding: 12px; font-weight: normal; }\n";
    file << "  .my-table td { padding: 10px; border-bottom: 1px solid #ddd; }\n";
    file << "  .my-table tr:nth-child(even) { background-color: #f8f9fa; }\n";
    file << "  .my-table tr:hover { background-color: #f1f1f1; }\n";
    file << "</style>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "<div class='container'>\n";

    file << "<h1>Результаты обработки</h1>\n";

    // 1. Таблица с массивом
    file << "<h2>Исходный массив</h2>\n";
    file << "<table class='my-table'>\n";
    file << "<tr><th>Номер</th><th>Значение</th></tr>\n";
    for (int i = 0; i < size; i++) {
        file << "<tr><td>" << i + 1 << "</td><td>" << numbers[i] << "</td></tr>\n";
    }
    file << "</table>\n";

    // 2. Таблица с результатами
    file << "<h2>Результаты вычислений</h2>\n";
    file << "<table class='my-table'>\n";
    file << "<tr><th>Минимальное</th><th>Максимальное</th><th>Среднее</th></tr>\n";
    file << "<tr><td>" << findMin(numbers, size) << "</td><td>" << findMax(numbers, size) << "</td><td>" << fixed << setprecision(2) << findAverage(numbers, size) << "</td></tr>\n";
    file << "</table>\n";

    // 3. Диаграмма
    file << "<h2>Столбчатая диаграмма</h2>\n";
    file << "<div style='display: flex; align-items: flex-end; justify-content: center; height: 350px; gap: 15px; border-bottom: 2px solid #ccc; padding-bottom: 5px; margin-bottom: 30px;'>\n";

    int maxVal = findMax(numbers, size);
    int minVal = findMin(numbers, size);
    double avg = findAverage(numbers, size);

    for (int i = 0; i < size; i++) {
        string color = "#95a5a6"; // Серый по умолчанию
        if (numbers[i] == minVal) color = "#3498db"; // Синий
        if (numbers[i] == maxVal) color = "#e74c3c"; // Красный

        int height = (numbers[i] * 300) / maxVal;

        file << "<div style='width: 40px; height: " << height << "px; background-color: " << color << "; display: flex; justify-content: center; align-items: flex-start; color: white; font-weight: bold; border-radius: 6px 6px 0 0; box-shadow: 2px 0 5px rgba(0,0,0,0.1);'>";
        file << numbers[i];
        file << "</div>\n";
    }

    // Столбец для среднего значения
    int avgHeight = (avg * 300) / maxVal;
    file << "<div style='width: 40px; height: " << avgHeight << "px; background-color: #f1c40f; display: flex; justify-content: center; align-items: flex-start; color: #333; font-weight: bold; border-radius: 6px 6px 0 0; box-shadow: 2px 0 5px rgba(0,0,0,0.1);'>";
    file << fixed << setprecision(1) << avg;
    file << "</div>\n";

    file << "</div>\n"; // конец диаграммы

    file << "<p style='text-align: center; color: #666;'><b>Легенда:</b> <span style='color:#3498db'>■ Мин</span> | <span style='color:#e74c3c'>■ Макс</span> | <span style='color:#f1c40f'>■ Среднее</span></p>\n";

    file << "</div>\n";
    file << "</body></html>";
    file.close();
    system("start index.html");


    delete[] numbers;

    system("pause");
    return 0;
}
