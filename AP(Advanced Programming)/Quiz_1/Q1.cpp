#include <iostream>
using namespace std;

template <class T>
void CreateMatris(T ***matris1, int n1, int m1)
{
    (*matris1) = (T **)malloc(sizeof(T *) * n1);
    int i = 0;
    while (i < n1)
    {
        *(*matris1 + i) = (T *)malloc(sizeof(T) * m1);
        i++;
    }
}

template <class T>
void FillMatris(T ***matris1, int n1, int m1)
{
    int i = 0;
    while (i < n1)
    {
        for (int j = 0; j < m1; j++)
            cin >> (*matris1)[i][j];
        i++;
    }
}

template <class T>
void PrintMatris(T ***matris, int n, int m)
{
    int i = 0;
    while (i < n)
    {
        int j = 0;
        while (j < m)
        {
            cout << *(*(*matris + i) + j) << " ";
            if (j == m - 1)
                cout << endl;
            j++;
        }
        i++;
    }
}

int main()
{
    int n1;
    int tedad;
    int n2;
    int m1;
    int m2;
    int m3;
    int xx;
    cin >> n1;
    cin >> m1;
    cin >> m2;
    cin >> tedad;
    n2 = m1;
    m3 = m1;
    if ((tedad == 0) || (tedad == 1) || (tedad == -1))
    {
        double **matris1;
        double **matris2;
        double **The_final_matris;
        CreateMatris(&matris1, n1, m1);
        FillMatris(&matris1, n1, m1);
        CreateMatris(&matris2, n2, m2);
        FillMatris(&matris2, n2, m2);
        CreateMatris(&The_final_matris, n1, m2);
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                double total = 0;
                xx = 0;
                while (xx < m3)
                {
                    total += *((*(matris1 + i)) + xx) * *((*(matris2 + xx)) + j);
                    xx++;
                }
                *((*(The_final_matris + i)) + j) = total;
            }
        }
        PrintMatris(&The_final_matris, n1, m2);
        int ii = 0;
        while (ii < n1)
        {
            free(*(matris1 + ii));
            ii++;
        }
        int iii = 0;
        while (iii < n2)
        {
            free(*(matris2 + iii));
            iii++;
        }

        free(The_final_matris);
        free(matris2);
        free(matris1);
    }
    if (tedad == 2)
    {
        string matris1[n1][m1];
        string matris2[n2][m2];
        string The_final_matris[n1][m2];
        int i = 0;
        while (i < n1)
        {
            for (int j = 0; j < m1; j++)
                cin >> matris1[i][j];
            i++;
        }
        i = 0;
        while (i < n2)
        {
            for (int j = 0; j < m2; j++)
                cin >> matris2[i][j];
            i++;
        }
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                *((*(The_final_matris + i)) + j) = matris1[i][j] + "_" + matris2[i][j];
            }
        }
        i = 0;
        while (i < n1)
        {
            int j = 0;
            while (j < m2)
            {
                cout << The_final_matris[i][j] << " ";
                if (j == m2 - 1)
                    cout << endl;
                j++;
            }
            i++;
        }
    }
}
//  2 2 2
//  2 2
//  2 2
//  2 2
//  2 2