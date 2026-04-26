import random

N = 7
print("=== Generate a dataset of size x * N ===")
print("N =", N)
x = int(input("Enter x: "))
total_n = x * N

value_min = 1
value_max = 20
values = [random.randint(value_min, value_max) for _ in range(total_n)] # random values from 1 to 20

weight_min = 1
weight_max = 10
weights = [random.randint(weight_min, weight_max) for _ in range(total_n)] # random weights from 1 to 10

W = total_n * 2  # half of N

with open(f"{x}x.txt", 'w') as f:
    f.write(f"n {total_n}\n")
    f.write(f"W {W}\n")
    for v in values:
        f.write(f"{v}\n")
    for w in weights:
        f.write(f"{w}\n")
        
print(f"{x}x.txt generated successfully!")
        