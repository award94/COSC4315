def f2():
   return 5

def func(a, b):
   x = a + b
   return x

y = func(1,2) + func(1,2)
x = f2() + f2()

if(f2() == f2()):
   z = 1

print(func(func(1,2),f2()) + f2())
#print(func(func(1,1) + 1, 2) + 1)
