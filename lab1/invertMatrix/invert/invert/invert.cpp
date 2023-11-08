#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int N = 3;

void ReadMatrix(double matrix[][N], const string& fileName) 
{
    ifstream file(fileName);
    if (!file.is_open()) 
    {
        cout << "Error: Could not open file " << fileName << endl;
        exit(1);
    }
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            if (!(file >> matrix[i][j])) 
            {
                cout << "Error: Could not read matrix element (" << i << "," << j << ")" << endl;
                exit(1);
            }
        }
    }
    file.close();
}

void PrintMatrix(double matrix[][N]) 
{
    cout << fixed << setprecision(3);
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

double GetDeterminant(double matrix[][N]) 
{
    double determinant = 0;
    determinant = matrix[0][0] * matrix[1][1] * matrix[2][2];
    determinant += matrix[2][0] * matrix[0][1] * matrix[1][2];
    determinant += matrix[1][0] * matrix[2][1] * matrix[0][2];
    determinant -= matrix[2][0] * matrix[1][1] * matrix[0][2];
    determinant -= matrix[0][0] * matrix[2][1] * matrix[1][2];
    determinant -= matrix[1][0] * matrix[0][1] * matrix[2][2];
    return determinant;
}

void TransposeMatrix(double matrix[][N], double adj[][N]) 
{
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            adj[j][i] = matrix[i][j];
        }
    }
    double plugMatrix[N][N];
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            plugMatrix[i][j] = adj[i][j];
        }
    }
    // Находим алгебраические дополнения
    int sign = 1;
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            // Вычисляем знак
            if ((i + j) % 2 == 0) 
            {
                sign = 1;
            }
            else 
            {
                sign = -1;
            }

            // Вычисляем минор
            double minor[2][2];
            int r = 0, c = 0;
            for (int k = 0; k < 3; k++) 
            {
                if (k != i) 
                {
                    c = 0;
                    for (int l = 0; l < 3; l++) 
                    {
                        if (l != j) 
                        {
                            minor[r][c] = plugMatrix[k][l];
                            c++;
                        }
                    }
                    r++;
                }
            }

            // Вычисляем определитель минора
            double det = minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0];

            // Вычисляем алгебраическое дополнение
            adj[i][j] = sign * det;
        }
    }
}

void MultiMatrixOnNumber(double det, double transpose[][N], double inv[][N]) 
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            inv[i][j] = (1 / det) * transpose[i][j];
        }
    }
}

void InvertMatrix(double matrix[][N], double inv[][N]) 
{
    double det = GetDeterminant(matrix);
    if (det == 0) {
        cout << "Error: Matrix is singular" << endl;
        exit(1);
    }
    double transpose[N][N];
    TransposeMatrix(matrix, transpose);
    MultiMatrixOnNumber(det, transpose, inv);
}

int main(int argc, char* argv[]) 
{
    double matrix[N][N];
    double inv[N][N];
    ReadMatrix(matrix, argv[1]);
    InvertMatrix(matrix, inv);
    PrintMatrix(inv);
    return 0;
}
