#include <fstream>
#include <vector>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

using std::vector;

class saw_sequence {
public:
    saw_sequence() {}
    ~saw_sequence() {}

    void get_input(const char *in_file = INPUT) 
    {
       std::ifstream in(in_file);

        if(in.is_open()) {
            in >> N;

            _values.assign(N, 0);

            for(int i = 0; i < N; ++i) {
                in >> _values[i];
            }

            in.close();
        }
    }

    void solve(void)
    {
        // Worst case should be O(M*N)
        for(int i = 0; i < N;) {
            int cur_seq_len = get_sequence_len(i);
   
            if(longest_sequence < cur_seq_len) {
                longest_sequence = cur_seq_len;
            }

            i += cur_seq_len;
        }
    }

    void write_output(const char *out_file = OUTPUT) 
    {
        std::ofstream out(out_file);

        if(out.is_open()) {
            out << longest_sequence;

            out.flush();
            out.close();
        }
    }

private:

    int N;
    int longest_sequence; //return value
    vector<int> _values;

    enum operations_e {
        LESS_THAN,
        GREATER_THAN,
        INVALID_OPERATION
    };

    int get_sequence_len(int start_from)
    {
        int len = 1;
        operations_e prev_operation = LESS_THAN;

        for(int i = start_from; i < (N-1); ++i) {
            if(current_operation(_values[i], _values[i+1], prev_operation)) {
                ++len;
            } else {
                break;
            }
        }

        prev_operation = GREATER_THAN;

        for(int i = start_from; i < (N-1); ++i) {
            if(current_operation(_values[i], _values[i+1], prev_operation)) {
                ++len;
            } else {
                break;
            }
        }

        return len;
    }


    bool current_operation(int lhs, int rhs, operations_e &prev_operation)
    {
        bool ret = false;

        switch(prev_operation) {
            case LESS_THAN:
                ret = lhs > rhs;
                prev_operation = GREATER_THAN;
                break;
            case GREATER_THAN:
                ret = lhs < rhs;
                prev_operation = LESS_THAN;
                break;
        }

        return ret;
    }
};

#ifdef CPP_OLD_IMPL

int main(int argc, char **argv)
{
    saw_sequence s;

    s.get_input();
    s.solve();
    s.write_output();

    return 0;
}

#endif