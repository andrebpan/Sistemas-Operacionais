#include <iostream>
#define MAX 800
using namespace std;

int main()
{
    int a[MAX], b[MAX], c[MAX][MAX];
    int i, j, k;

    for(i=0; i< MAX; i++)
    {
        for(j=0; j< MAX; j++)
        {
            a[i][j] = 0;
            b[i][j] = i+j;
            c[i][j] = i+j;
        }
    }

    for(i =0; i<MAX; i++)
    {
        for(j=0; j<MAX;j++)
        {
            for(k=0; k<MAX;k++)
            {
                a[i][j] += b[i][k] + c[k][j];
            }
        }
    }
    return 0;
}