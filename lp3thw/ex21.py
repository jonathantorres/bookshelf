def add(a, b):
    return a + b

def substract(a, b):
    return a - b

def multiply(a, b):
    return a * b

def divide(a, b):
    return a / b

print("Let's do some math with just functions")

age = add(30, 5)
height = substract(78, 4)
weight = multiply(90, 2)
iq = divide(100, 2)

print(f"Age: {age}, Height: {height}, Weight {weight}, IQ: {iq}")

what = add(age, substract(height, multiply(weight, divide(iq, 2))))
formula = age + (height - (weight * (iq / 2)))

print("That becomes: ", what, "Can you do it by hand?")
print("Formula should be the same madness:", formula)
