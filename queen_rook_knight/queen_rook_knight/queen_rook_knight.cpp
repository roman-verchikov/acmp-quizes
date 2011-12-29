#include <stdio.h>
#include <string.h>
#include <ctype.h>

class field {
public:
    field() {
        init();
    }

    void mark(char c, int n) {}

    void print(void) const 
    {
        printf(" ---------------- \n");
        for(int i = LAST_Y; i >= FIRST_Y; --i) {
            printf("|");
            for(char c = FIRST_X; c <= LAST_X; ++c) {
                printf("%c|", get_val(c, i));
            }
            printf("\n");
        }
        printf(" ---------------- \n");
    }

    void mark_queen_pos(char c, int n)
    {
        // horizontal
        for(char i = FIRST_X; i <= LAST_X; ++i) {
            mark_pos(i, n, MARK);
        }

        // vertical
        for(int i = FIRST_Y; i <= LAST_Y; ++i) {
            mark_pos(c, i, MARK);
        }

        // diagonal
        int delta_start = LAST_Y - 
        for(int i = FIRST_Y; i <= LAST_Y; ++i) {
            mark_pos(
        }

        mark_pos(c,n, QUEEN);
    }

    void mark_rook_pos(char c, int n)
    {
        for(char i = FIRST_X; i <= LAST_X; ++i) {
            mark_pos(i, n, MARK);
        }

        // vertical
        for(int i = FIRST_Y; i <= LAST_Y; ++i) {
            mark_pos(c, i, MARK);
        }

        mark_pos(c,n, ROOK);
    }

    void mark_knight_pos(char c, int n)
    {
        struct pair {
            char x;
            int  y;
        } diffs[] = {
            {1, 2},
            {2, 1},
            {-1, 2},
            {-2, 1},
            {-2, -1},
            {-1, -2},
            {2, -1},
            {1, -2}
        };

        int size = sizeof(diffs)/sizeof(*diffs);

        for(int i = 0; i < size; ++i) {
            char x = c + diffs[i].x;
            char y = n + diffs[i].y;

            mark_pos(x, y, MARK);
        }

        mark_pos(c,n, KNIGHT);
    }

    int num_marked_fields(void)const
    {
        int cnt = 0;

        for(char c = FIRST_X; c <= LAST_X; ++c) {
            for(int i = FIRST_Y; i <= LAST_Y; ++i) {
                if(get_val(c, i) == MARK) {
                    ++cnt;
                }
            }
        }

        return cnt;
    }

private:

    enum {
        FIRST_X         = 'A',
        LAST_X          = 'H',
        FIRST_Y         = 1,
        LAST_Y          = 8,
        FIELD_SIZE      = 8
    };

    enum pos_value {
        EMPTY_FIELD     = '0',
        MARK            = 'x',
        QUEEN           = 'Q',
        ROOK            = 'R',
        KNIGHT          = 'K'
    };

    int get_val(char c, int n) const
    {
        int x = x_coord(c);
        int y = y_coord(n);

        return __field[x][y];
    }

    int x_coord(char c) const
    {
        return (toupper(c)-'A');
    }

    int y_coord(int n) const
    {
        return (n-1);
    }

    bool is_valid(char c, int n) const
    {
        return ((c >= FIRST_X) && (c <= LAST_X) && (n >= FIRST_Y) && (n <= LAST_Y));
    }

    void mark_pos(char c, int n, pos_value v) 
    {
        int x = x_coord(c);
        int y = y_coord(n);

        if(is_valid(c,n)) {
            if(__field[x][y] == EMPTY_FIELD || __field[x][y] == MARK) {
                __field[x][y] = v;
            }
        }
    }

    void init(void)
    {
        for(int i = 0; i < FIELD_SIZE; ++i) {
            for(int j = 0; j < FIELD_SIZE; ++j) {
                __field[i][j] = EMPTY_FIELD;
            }        
        }
    }

    int __field[FIELD_SIZE][FIELD_SIZE];
};


int main(int argc, char **argv)
{
    int n1, n2, n3;
    char c1, c2, c3;

    field f;

    freopen("INPUT.TXT", "r", stdin);
    //freopen("OUTPUT.TXT", "w", stdout);

    scanf("%c%d %c%d %c%d", &c1, &n1, &c2, &n2, &c3, &n3);


    f.mark_queen_pos(c1, n1);
    f.mark_rook_pos(c2, n2);
    f.mark_knight_pos(c3, n3);

    f.print();

    return 0;
}