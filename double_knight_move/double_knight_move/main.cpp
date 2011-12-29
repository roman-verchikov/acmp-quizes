#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct point_t {
    char c;
    int n;
} point_t;

typedef struct diffs_t {
    int dx;
    int dy;
} diffs_t;

diffs_t possible_diffs[] = {
    {1, 2},
    {2, 1},
    {2, -1},
    {1, -2},
    {-1, -2},
    {-2, -1},
    {-2, 1},
    {-1, 2}
};

int NUM_POSSIBLE_DIFFS = sizeof(possible_diffs) / sizeof(diffs_t);

int are_equal(const point_t *lhs, const point_t *rhs)
{
    return (lhs->c == rhs->c) && (lhs->n == rhs->n);
}

point_t next_pos(point_t cur_pos, diffs_t diff)
{
    point_t p = cur_pos;

    p.c += diff.dx;
    p.n += diff.dy;

    return p;
}

int good_pos(point_t p)
{
    return (p.c >= 'a' && p.c <= 'h' && p.n >= 1 && p.n <= 8);
}

int is_possible_move(const point_t start, const point_t end, int level)
{
    int retval = level;
    int i = 0;

    if (!good_pos(start) || !good_pos(end) || level > 2) {
        return 3;
    }

    if (are_equal(&start, &end) && level != 0) {
        return level;
    }

    ++level;

    for (i = 0; i < NUM_POSSIBLE_DIFFS; ++i) {
        point_t cur_pos = next_pos(start, possible_diffs[i]);
        retval = is_possible_move(cur_pos, end, level);

        if (retval <= 2) break;
    }

    return retval;
}

int main()
{
    point_t start, end;
    int ret = 0;
    char buf[16];

    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    scanf("%c%d, %c%d", &start.c, &start.n, &end.c, &end.n);

    ret = is_possible_move(start, end, 0);

    printf("%s", ret > 2 ? "NO" : itoa(ret, buf, 10));

    return 0;
}