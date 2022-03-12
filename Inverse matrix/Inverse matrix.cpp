﻿#include <iostream>
#include <iomanip>
using namespace std;
void swap(double** p, int* tx, int* ty, int* m, int* n) {
    double tmp;
    int tmpx = *tx, tmpy = *ty;
sw:
    for (int i = tmpy; i < *m; i++) {
        if (p[i][tmpx] != 0) {
            for (int s = tmpx; s < *n; s++) {
                tmp = p[i][s];
                p[i][s] = p[*ty][s];
                p[*ty][s] = tmp;
            }
            return;
        }
    }
    tmpx++;
    *tx = *tx + 1;
    if (tmpx != *n && tmpy != *m) {
        goto sw;
    }
}
void up(double** p, int* tx, int* ty, int* m, int* n) {
    int tmpx = *tx, tmpy = *ty;
    double num;
    for (int i = tmpy - 1; i >= 0; i--) {
        num = p[i][tmpx];
        if (num != 0) {
            for (int j = tmpx; j < *n; j++) {
                p[i][j] = p[i][j] + (p[tmpy][j] * -1 * num);
            }
        }
    }
}
void down(double** p, int* tx, int* ty, int* m, int* n) {
    int tmpx = *tx, tmpy = *ty;
    double num;
    for (int i = tmpy + 1; i < *m; i++) {
        num = p[i][tmpx];
        if (num != 0) {
            for (int j = tmpx; j < *n; j++) {
                p[i][j] = p[i][j] + (p[tmpy][j] * -1 * num);
            }
        }
    }
}
void print(double** p, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(2) << p[i][j] << " ";
        }
        cout << endl;
    }
}
void operation(double** p, int* tx, int* ty, int* m, int* n) {
    int tmpy = *ty;
    double leader = p[tmpy][*tx];
    if (leader != 0) {
        for (int i = *tx; i < *n; i++) { //取得前導1
            if (leader != 1) {
                p[tmpy][i] = p[tmpy][i] / leader;
            }
            else {
                break;
            }
        }
        up(p, tx, ty, m, n); down(p, tx, ty, m, n);
        cout << endl;
        print(p, *m, *n);
    }
    *ty = *ty + 1; *tx = *tx + 1;
}
int main()
{
    int m, n, x = 0, y = 0,p = 0;
    double** matrix;
    cout << "Please enter the matrix size(m*n):\nm=";
    cin >> m;
    cout << "n=";
    cin >> n;
    n = n * 2;
    matrix = (double**)malloc(m * sizeof(double*));
    cout << "Please enter a matrix:" << endl;
    for (int i = 0; i < m; i++)
    {
        matrix[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n / 2; j++)
        {
            cin >> matrix[i][j];
        }
        for (int j = n / 2; j < n; j++) {
            if ((n / 2 + i) == j) {
                matrix[i][j] = 1;
            }
            else {
                matrix[i][j] = 0;
            }
        }

    }
    print(*&matrix, m, n);
    while (true)
    {
        if (matrix[y][x] == 0 && x < n && y < m) { //找出非零整數
            swap(*&matrix, &x, &y, &m, &n);
        }
        operation(*&matrix, &x, &y, &m, &n);
        if (x + 1 > n || y + 1 > m) {
            break;
        }
    }
    cout << "\n\nAns:\n";
    print(*&matrix, m, n);
}