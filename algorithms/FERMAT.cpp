x^(p - 1) = 1 (mod p)
x^(p - 1) = x * x^(p - 2) = 1(mod p)
Conclusion:
a / b (mod p) = a * fastpow(b, p - 2, p) % p
