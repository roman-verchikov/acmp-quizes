#-------------------------------------------------------------------------------
# A palindromic number reads the same both ways. The largest palindrome
# made from the product of two 2-digit numbers is 9009 = 91  99.
# 
# Find the largest palindrome made from the product of two 3-digit
# numbers.
#-------------------------------------------------------------------------------

BASE = 10

def num_digits(number):
   n = 0
   
   while number:
      number /= BASE
      n += 1
   
   return n

def get_digit(number, digit_pos, total_digits):
   tmp = number
   
   for i in range(0, total_digits-digit_pos):
      tmp /= BASE

   return ( tmp % BASE )

def is_palindrome(n):
   ret = True
   total_digits = num_digits(n)

   begin = 1
   end   = total_digits

   while end >= begin:
      x1 = get_digit(n, begin, total_digits)
      x2 = get_digit(n, end, total_digits)

      if(x1 != x2): 
         ret = False
         break

      begin += 1
      end   -= 1

   return ret

def test2():
   tested_nums = [
         987789,
         12345,
         1001,
         999554,
         12321,
         123456654321
   ]

   for i in tested_nums:
      print i, is_palindrome(i)

def test():
   tested_number = 63846

   for i in range(1, num_digits(tested_number)+1):
      x = get_digit(tested_number, i, num_digits(tested_number))

      print i, " digit of ", tested_number, "is", x

   
def main():
   mul1 = 1
   mul2 = 1
   max = 0

   for i in range(100, 1000):
      for j in range(i, 1000):

         mul = i*j

         if is_palindrome(mul) and mul > max:
            ret = mul
            max = mul
            mul1 = i
            mul2 = j

   print ret, " = ", mul1, "*", mul2


main()
#test()
#test2()
