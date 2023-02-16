#include <iostream>
#include <random>        // biblioteka umożliwiająca generowanie liczb losowych
#include <chrono>        // biblioteka do pomiaru czasu
#include <algorithm>     // biblioteka zawierająca funkcję std::sort()
#include <omp.h>         // biblioteka umożliwiająca programowanie równoległe
#include <cstring>       // biblioteka zawierająca funkcję std::memset()

using namespace std;

int main() {
    int size;                                    // zmienna przechowująca wymiar macierzy
    cout << "Enter matrix size: ";
    cin >> size;

    int** matrix = new int*[size];                // utworzenie macierzy jako tablicy wskaźników na tablice jednowymiarowe
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];               // utworzenie tablic jednowymiarowych reprezentujących kolejne wiersze
    }

    std::random_device rd;
    std::mt19937 engine(rd());    // generator liczb losowych
    uniform_int_distribution<int> dist(-1000, 1000);  // rozkład jednostajny liczb całkowitych z przedziału [-1000, 1000]
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = dist(engine);         // losowe wypełnienie macierzy liczbami
        }
    }

    int rangeIndex = 0;                          // indeks zakresów wprowadzonych przez użytkownika
    int from, to;
    char cont;
    vector<pair<int, int>> ranges;              // wektor przechowujący zakresy wprowadzone przez użytkownika
    do {
        cout << "Enter range to search for (e.g. -500 500): ";
        cin >> from >> to;
        ranges.emplace_back(from, to);   // dodanie nowego zakresu do wektora
        rangeIndex++;
        cout << "Enter another range? (y/n) ";
        cin >> cont;
    } while (cont == 'y');

    int counts[rangeIndex][11];                  // tablica przechowująca liczbę wystąpień liczb z zakresu w macierzy, w zależności od liczby wątków
    memset(counts, 0, sizeof(counts));           // wypełnienie tablicy zerami
    cout << omp_get_max_threads() << endl;       // wypisanie maksymalnej liczby dostępnych wątków
    for (int t = 0; t <= 10; t++) {              // pętla iterująca po liczbie wątków
        omp_set_num_threads(t);                  // ustawienie liczby wątków dla sekcji równoległej
        auto start = chrono::high_resolution_clock::now();    // pomiar czasu rozpoczęcia sekcji równoległej

#pragma omp parallel for default(none) collapse(2) shared(matrix, ranges, counts, size, rangeIndex) private(t) schedule(dynamic)           // dyrektywa OpenMP

        for (int i = 0; i < size; i++) {        // iteruj przez macierz w celu zliczenia liczby wystąpień dla każdego z określonych przedziałów
            for (int j = 0; j < size; j++) {
                int num = matrix[i][j];
                for (int k = 0; k < rangeIndex; k++) {
                    if (num >= ranges[k].first && num <= ranges[k].second) {
#pragma omp atomic
                        counts[k][t]++;
                    }
                }
            }
        }

        auto end = chrono::high_resolution_clock::now();    // zakończ pomiar czasu i oblicz jego trwanie
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time taken with " << t << " threads: " << duration.count() << " microseconds" << endl;    // wyświetl czas wykonania i liczbę wątków
    }

    cout << "Range\tCount\tThreads" << endl;
    for (int k = 0; k < rangeIndex; k++) {
        for (int t = 0; t <= 10; t++) {
            cout << ranges[k].first << "-" << ranges[k].second << "\t" << counts[k][t] << "\t" << t << endl;
        }
    }

    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
