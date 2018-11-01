def f2():
   return 5

def func(a, b):
   x = a + b
   return x

print(func(func(1,2),2) + f2())
#print(func(func(1,1) + 1, 2) + 1)
