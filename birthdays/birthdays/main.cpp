#include <stdio.h>

int month_len[] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

int month_to_days(int m)
{
    int ret = 0;

    for (int i = 0; i < m; ++i) {
        ret += month_len[i];
    }

    return ret;
}

int date_to_int(int d, int m, int y)
{
    --m;
    --d;
    y -= 93;

    d += month_to_days(m);

    return y * 365 + d;
}

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    int d1 = 0, m1 = 0, y1 = 0;
    int d2 = 0, m2 = 0, y2 = 0;

    scanf("%d.%d.%d", &d1, &m1, &y1); 
    scanf("%d.%d.%d", &d2, &m2, &y2);

    int _d1 = date_to_int(d1, m1, y1);
    int _d2 = date_to_int(d2, m2, y2);
    
    printf("%d", _d2-_d1);

    return 0;
}