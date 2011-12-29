#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

pair<int, int> fast_algo(int N)
{
   int n = N / 2;
   int k = N - n;

   if (N % 2 == 0) {
      if (n % 2 == 0 && k % 2 == 0) {
         n--;
         k++;
      } else {
         n -= 2;
         k += 2;
      }
   }

   return pair<int, int>(n, k);
}

int main()
{
   ifstream in ("INPUT.TXT");
   int N = 0;

   if (in.is_open()) {
      in >> N;
      pair<int, int> fast = fast_algo(N);

      ofstream out("OUTPUT.TXT");

      if (out.is_open()) {
         out << fast.first << " " << fast.second;
      }
   }
}
