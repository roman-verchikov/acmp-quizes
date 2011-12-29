// http://acmp.ru/?main=task&id_task=347

#include <fstream>
#include <string>
#include <algorithm>
#include <map>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

const int N = 5;
int g_cards[N];
std::string g_result = "Nothing";

void get_input(void)
{
    std::ifstream in(INPUT);

    if(in.is_open()) {
        for(int i = 0; i < N; i++) {
            in >> g_cards[i];
        }
        in.close();
    }
}

void solve(void)
{
    std::sort(g_cards, g_cards+N);
    std::map<int, int> repeats;

    for(int i = 0; i < N; i++) {
        repeats[g_cards[i]]++;
    }
    
    if(repeats.size() == 1) {
        // impossible
        g_result = "Impossible";
    } else if(repeats.size() == 2) {
        // 4+1 or 2+3
        if((*repeats.begin()).second == 1 || (*repeats.begin()).second == 4) {
            g_result = "Four of a Kind";
        } else {
            g_result = "Full House";
        }
    } else if(repeats.size() == 3) {
        // 1+1+3 or 1+2+2
        for(std::map<int,int>::const_iterator i = repeats.begin(); i != repeats.end(); ++i) {
            if( (*i).second == 3 ) {
                g_result = "Three of a Kind";
                break;
            } else if( (*i).second == 2 ) {
                g_result = "Two Pairs";
                break;
            }
        }
    } else if(repeats.size() == 4) {
        g_result = "One Pair";
    } else if(repeats.size() == 5) {
        g_result = "Straight";

        for(int i = 1; i < N; i++) {
            if(g_cards[i-1] != g_cards[i]-1) {
                g_result = "Nothing";
                break;
            }
        }
    }
}

void save_output(void)
{
    std::ofstream out(OUTPUT);

    if(out.is_open()) {
        out << g_result;
        out.flush();
        out.close();
    }
}

int main(void)
{
    get_input();
    solve();
    save_output();

    return 0;
}