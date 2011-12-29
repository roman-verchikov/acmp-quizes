#include <stdio.h>
#include <string.h>

#define F(i, s) for (int i = s; i < l; ++i)
#define C(c) (a[c] - '0')

char  a[100], A[1000]; 
int l, c;

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    scanf("%s", a);
    l = strlen(a);

    F(i, 0) 
        F(j, i+1)
            F(k, j+1) {
                int n = C(i) * 100 + C(j) * 10 + C(k);

                if ( n >= 100 && n < 1000 && !A[n] ) {
                    A[n] = 1;
                    ++c;
                }
            }
    
    printf("%d", c);

    return 0;
}