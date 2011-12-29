import math

#-------------------------------------------------------------------------------
# The prime factors of 13195 are 5, 7, 13 and 29.
# 
# What is the largest prime factor of the number 600851475143 ?
#-------------------------------------------------------------------------------

NUMBER = 600851475143  

primes = [2, 3]
print primes

def my_sqrt(x):
   return math.trunc(math.ceil(math.sqrt(x)))


def is_prime(n):
   for i in primes:
      if ( (n % i) == 0):
         return False
      if i > my_sqrt(n):
         return True

   return True

def generate_primes(max_val):
   i = 3

   while (i*i) < max_val:
      if is_prime(i):
         primes.append(i)
      i += 1

def problem_solver():
   res = 0

   generate_primes(NUMBER)

   for i in primes:
      if (NUMBER % i == 0):
         res = i

   print res


def main():
   problem_solver()


main()
