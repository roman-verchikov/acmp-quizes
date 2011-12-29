MAX_VAL = 1000000000

def is_divisible(n):
   for i in range(1, 21):
      if (n % i) != 0:
         return False

   return True

def main():
   ret = 1
   i = 20

   while i < MAX_VAL:
      if is_divisible(i):
         ret = i
         break

      i += 10

   print ret 

main()
