import random


N = 1000
print("=== Generate a dataset of size x * N ===")
print("N =", N)
x = int(input("Enter x: "))

value_min = 1
value_max = 500
values = [random.randint(value_min, value_max) for _ in range(x*N)] # random values from 1 to 500

weight_min = 1
weight_max = 50
weights = [random.randint(weight_min, weight_max) for _ in range(x*N)] # random weights from 1 to 50

W = N // 2  # half of N

with open(f"{x}x.txt", 'w') as f:
    f.write(f"n {N}\n")
    f.write(f"W {W}\n")
    for v in values:
        f.write(f"{v}\n")
    for w in weights:
        f.write(f"{w}\n")
        
print(f"{x}x.txt generated successfully!")
        