#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

namespace maze_generator 
{

    enum direction_t {
        EAST,
        NORTH,
        WEST,
        SOUTH
    };

    class size {
        public:
            size(const size_t &w = 0, const size_t &h = 0) : w_(w), h_(h) {}

            size_t width() const {
                return w_;
            }

            size_t height() const {
                return h_;
            }

            void width(const size_t &w) {
                w_ = w;
            }

            void height(const size_t &h) {
                h_ = h;
            }

        private:
            size_t w_;
            size_t h_;
    };

    template<class T, size_t N>
    class array {
        public:
            typedef T* iterator;
            typedef const T *const const_iterator;

            iterator begin() {
                return els_;
            }

            iterator end() {
                return els_+N;
            }

            T& operator [] (size_t i) {
                return els_[i];
            }

            const T& operator [] (size_t i) const {
                return els_[i];
            }

            T& at(size_t i) throw (std::out_of_range) {
                if (i >= N) {
                    throw std::out_of_range();
                }

                return (*this)[i];
            }

            const T& at(size_t i) const throw (std::out_of_range) {
                if (i >= N) {
                    throw std::out_of_range();
                }

                return (*this)[i];
            }

        private:
            T els_[N];
    };

    class room {
        public:
            room() {
                std::fill(is_wall_.begin(), is_wall_.end(), false);
            }

            void add_entrance(direction_t d) {
                is_wall_[d] = true;
            }

        private:
            array<bool, 4> is_wall_; 
    };

    class maze {
        public:
            enum {
                DEFAULT_WIDTH = 10,
                DEFAULT_HEIGHT = 10
            };

            maze(size_t width = maze::DEFAULT_WIDTH, size_t height = maze::DEFAULT_HEIGHT) 
                : size_(width, height),  
                  is_solved_(false)
            {

            }

            void generate() {
            
            }

            void solve() {
                
            }

            bool solved() {
                return is_solved_;
            }

            void draw() {
                
            }

        private:

            std::vector<room> maze_;
            size size_;
            bool is_solved_;

    };

}

int main()
{
    maze_generator::maze m;

    return 0;
}
