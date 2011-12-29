
LATEST_PRIME = 10001

primes = [2, 3, 5]

def is_prime(n):
   for i in primes:
      if ((n % i) == 0) and (i*i <= n):
         return False

   return True

def generate_primes(max_val):
   start = len(primes)
   i = primes[-1]

   for last_prime in range(start, max_val+1):
      while not is_prime(i):
         i += 2
      else:
         primes.append(i)

      i += 2

def main():
   generate_primes(LATEST_PRIME)
   print primes[-1]

main()   
