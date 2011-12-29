#-------------------------------------------------------------------------------
# The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
# 
# Find the sum of all the primes below two million.
#-------------------------------------------------------------------------------

MAX_VAL = 2000000

primes = [2, 3, 5, 7, 11]

def is_prime(n):
   for i in primes:
      if( n % i == 0 ) and (i*i <= n):
         return False

   return True

def main():
   sum = 0
   cur_prime = primes[-1]

   while cur_prime < MAX_VAL:
      while not is_prime(cur_prime):
         cur_prime += 2
      else:
         primes.append(cur_prime)

      cur_prime+=2

   for n in primes:
      if(n > MAX_VAL):
         break
      sum += n

   print sum

main()   

