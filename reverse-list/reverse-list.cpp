#include <iostream>

using namespace std;

struct node {
   node *next;
   int value;
};

node *reverse (node *first)
{
   node *next = first.next;
   node *prev = 0;
   node *cur  = first;

   while (next) {
      prev = cur;
      cur  = next;
      next = next.next;
   }

   return n;
}

void print(node *first)
{
   node *next = 0;

   do {
      cout << first->value << endl;
      next = first->next;
   } while (next);
}

int main()
{
   node *n4 = {NULL, 4};
   node *n3 = {n4, 3};
   node *n2 = {n3, 2};
   node *n1 = {n2, 1};

   node *list[] = {n1, n2, n3, n4};

   return 0;
}
