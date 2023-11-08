#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std; 
const int N = 3;

void read_matrix(double matrix1[][N], double matrix2[][N], const string& filename1, const string& filename2) {
    ifstream file1(filename1), file2(filename2);
    if (!file1.is_open()) {
        cerr << "Error: Could not open file " << filename1 << endl;
        exit(1);
    }
    if (!file2.is_open()) {
        cerr << "Error: Could not open file " << filename2 << endl;
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!(file1 >> matrix1[i][j])) {
                cerr << "Error: Could not read matrix1 element (" << i << "," << j << ")" << endl;
                exit(1);
            }
            if (!(file2 >> matrix2[i][j])) {
                cerr << "Error: Could not read matrix2 element (" << i << "," << j << ")" << endl;
                exit(1);
            }
        }
    }
    file1.close();
    file2.close();
}

void multi(double matrix1[][N], double matrix2[][N], double result[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void print_matrix(double matrix[][N]) {
    cout << fixed << setprecision(3);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


int main(int argc, char* argv[]) {
    double matrix1[N][N];
    double matrix2[N][N];
    double result[N][N];
    // читаем коэффициенты матриц из входных файлов
    read_matrix(matrix1, matrix2, "matrix1.txt", "matrix2.txt");
    // перемножаем матрицы
    multi(matrix1, matrix2, result);
    // выводим результат в стандартный поток вывода
    print_matrix(result);
    return 0;
}
