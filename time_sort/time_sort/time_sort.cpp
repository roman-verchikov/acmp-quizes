#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

class c_time {
public:
    c_time(int hours = HOURS_MIN, int mins = MINS_MIN, int secs = SECS_MIN)
    {
        _set(hours, mins, secs);
    }

    void set(int hours, int mins, int secs) 
    {
        _set(hours, mins, secs);
    }

    bool operator < (const c_time &t) const 
    {
        if(_hours < t._hours) {
            return true;
        } 
        
        if (_hours == t._hours && _mins < t._mins) {
            return true;
        } 
        
        if (_hours == t._hours && _mins == t._mins && _secs < t._secs) {
            return true;
        }

        return false;
    }

    bool operator == (const c_time &t) const
    {
        return (_hours == t._hours && 
                _mins  == t._mins  && 
                _secs  == t._secs);
    }

    operator std::string(void) const
    {
        std::ostringstream ost;        

        ost << _hours << " " << _mins << " " << _secs;

        return ost.str();
    }

private:
    enum {
        HOURS_MIN = 0,
        MINS_MIN  = 0,
        SECS_MIN  = 0,
        HOURS_MAX = 23,
        MINS_MAX  = 59,
        SECS_MAX  = 59
    };

    int _hours;
    int _mins;
    int _secs;

    bool time_ok(int hours, int mins, int secs) const
    {
        return ((HOURS_MIN <= hours && hours <= HOURS_MAX) &&
                (MINS_MIN  <= hours && hours <= MINS_MAX) &&
                (SECS_MIN  <= hours && hours <= SECS_MAX));
    }

    void _set(int hours, int mins, int secs) 
    {
        if(time_ok(hours, mins, secs)) {
            _hours = hours;
            _mins  = mins;
            _secs  = secs;
        }
    }
};



int main(void)
{    
    int N = 0;
    std::ifstream in(INPUT);

    if(in.is_open()) {
        in >> N;

        std::vector<c_time> times(N);

        for(int i = 0; i < N; i++) {
            int h = 0, m = 0, s = 0;
            in >> h >> m >> s;
            
            times[i].set(h, m, s);
        }

        std::sort(times.begin(), times.end());
        std::ofstream out (OUTPUT);

        if(out.is_open()) {
            for(int i = 0; i < N; i++) {
                out << (std::string)times[i] << std::endl;
            }
        }
    }
}