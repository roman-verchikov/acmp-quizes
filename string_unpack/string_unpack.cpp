#include <fstream>

#define IS_DIGIT(n) ( (n - '0') >= 0 && (n - '0') <= 9 )
#define IS_LETTER(c) ( (c - 'A') >= 0 && (c - 'A') <= 9 )

int main()
{
   char buf[3];
   char c;
   int i = 0;

   std::ifstream in("INPUT.TXT");

   while (in.good()) {
      in.read(&c, 1);

      if (IS_DIGIT(c)) {
         buf[i] = c;
         ++i;
         i %= 3;
      } else if (IS_LETTER(c)) {
         
      }
   }

   return 0;
}
