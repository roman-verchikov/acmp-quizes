#include <fstream>
#include <vector>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

struct coords_t {
    coords_t(int _x=0, int _y=0) : x(_x), y(_y) {}
    int x;
    int y;
};

bool is_inside(const std::vector<coords_t> &ar)
{
    bool ret = false;

    return ret;
}

int main(int argc, char **argv)
{
    const int NUM_COORDS = 5;
    int num_good_landing = 0;

    std::ifstream in(INPUT);
    std::vector<coords_t> all_coords(NUM_COORDS);

    if(in.is_open()) {
        int N = 0;

        in >> N;

        for(int n = 0; n < N; n++) {
            for(int i = 0; i < NUM_COORDS; i++) {
                in >> all_coords[i].x >> all_coords[i].y;            
            }

            if(is_inside(all_coords)) {
                num_good_landing++;
            }
        }

        in.close();

        std::ofstream out(OUTPUT);

        if(out.is_open()) {
            out << num_good_landing;
            out.close();
        }
    }
}
