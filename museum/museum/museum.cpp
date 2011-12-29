#include <fstream>
#include <cstdio>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

#define MINS_IN_HOUR 60

class c_interval {
public:
    c_interval(void){ _start = INVALID_VALUE; _end = INVALID_VALUE;}

    void set(int h1, int m1, int h2, int m2)
    {
        _start = h1*MINS_IN_HOUR+m1;
        _end = h2*MINS_IN_HOUR+m2;
    }

    bool intersects(const int m) const
    {
        return (_start <= m && _end >= m);
    }

public:
    enum {
        INVALID_VALUE = -1
    };

    int _start;
    int _end;
};

#define INTERSECTS(t, m)\
    ((t)._start <= (m) && (m) <= (t)._end)

c_interval *g_times = 0;
int N = 0;
int g_result = 0;

void generate_big_input(void)
{
    const int K = 99998;

    freopen(INPUT, "w", stdout);

    printf("%d\n", K);

    for(int i = 0; i < K; i++) {
        printf("10:20 20:30\n");
    }
}

void get_input(void)
{
    freopen(INPUT, "r", stdin);

    scanf("%d", &N);

    int K = N%4;
    g_times = new c_interval [N+K];

    for(int i = 0; i < N; ++i) {
        int h1 = 0, m1 = 0;
        int h2 = 0, m2 = 0;

        scanf("%d:%d %d:%d", &h1, &m1, &h2, &m2);

        g_times[i].set(h1, m1, h2, m2);
    }
}

void solve()
{
    const int TOTAL_MINS = 60*24;

    int max = 0;

    for(int i = 0; i < TOTAL_MINS; ++i) {
        int cnt = 0;

        for(int j = 0; j < N; j+=4) {
            if(g_times[j]._start <= i && g_times[j]._end >= i) {
                cnt++;
            }
            if(g_times[j+1]._start <= i && g_times[j+1]._end >= i) {
                cnt++;
            }
            if(g_times[j+2]._start <= i && g_times[j+2]._end >= i) {
                cnt++;
            }
            if(g_times[j+3]._start <= i && g_times[j+3]._end >= i) {
                cnt++;
            }
        }

        if(cnt > max) max = cnt;
    }

    g_result = max;

    delete [] g_times;
}

void save_output()
{
    std::ofstream out(OUTPUT);

    if(out.is_open()) {
        out << g_result;
        out.flush();
        out.close();
    }
}

int main()
{
    get_input();
    solve();
    save_output();

    return 0;
}