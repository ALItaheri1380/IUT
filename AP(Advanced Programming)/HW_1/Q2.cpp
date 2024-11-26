#include<iostream>
using namespace std;
///***signaturs are***///
void CreateMatris(int*** matris1, int n1, int m1);
void FillMatris(int*** matris1, int n1, int m1);
void PrintMatris(int*** matris, int n, int m);
///***END OF SIGNATURSE***///

void CreateMatris(int*** matris1, int n1, int m1)
{
    (*matris1) = (int**)malloc(sizeof(int*) * n1);
    int i=0;
    while (i<n1)
    {
        *(*matris1 + i) = (int*)malloc(sizeof(int) * m1);
        i++;
    }      
}
/////////////////////
/////////////////////
void FillMatris(int*** matris1, int n1, int m1)
{
    int i=0;
      while (i<n1)
      {
        for (int j = 0; j < m1; j++)
            scanf("%d", (*(*matris1 + i) + j));
            i++;
      }
      
}
///////////////////////
//////////////////////
void PrintMatris(int*** matris, int n, int m)
{
        int i=0;
        while (i<n)
        {
            int j=0;
            while (j<m)
            {
            cout <<*(*(*matris + i) + j)<<" ";
            if(j==m-1)
                  cout<<endl;
            j++;      
        }
            i++;
    }
}
//////////////////////
/////////////////////
int main()
{
    int  n1;
    int  n2;
    int  m1;
    int  m2;
    int  m3;
    int  xx;
    cin>>n1;
    cin>>m1;
    cin>>m2;
    n2 = m1;
    m3 = m1;
    int**   matris1;
    int**   matris2;
    int**   The_final_matris;
    CreateMatris(&matris1, n1, m1);
    FillMatris(&matris1, n1, m1);
    CreateMatris(&matris2, n2, m2);
    FillMatris(&matris2, n2, m2);
    CreateMatris(&The_final_matris, n1, m2);
     for (int i = 0; i < n1; i++){
        for (int j = 0; j < m2; j++)
        {
            int total = 0;
            xx=0;
            while(xx<m3)
            {
                total += *((*(matris1 + i)) + xx) * *((*(matris2 + xx)) + j);
                xx++;
            }
            *((*(The_final_matris + i)) + j) = total;

        }
    }
    PrintMatris(&The_final_matris, n1, m2);
    int ii=0;
    while (ii<n1)
    {
        free(*(matris1 + ii));
        ii++;
    }
    int iii=0;
    while (iii<n2 )
    {
        free(*(matris2 + iii));
        iii++;
    }
    
    free(The_final_matris);
    free(matris2);
    free(matris1);
} 
//  2 2 2
//  2 2
//  2 2
//  2 2
//  2 2