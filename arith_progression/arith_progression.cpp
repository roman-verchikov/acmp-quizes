#include <fstream>

int main()
{
   int A1, A2, N;

   {
   std::ifstream in("INPUT.TXT");
   in >> A1 >> A2 >> N;
   }

   {
   std::ofstream out("OUTPUT.TXT");
   out << A1 + (N-1)*(A2-A1);
   }

   return 0;
}
