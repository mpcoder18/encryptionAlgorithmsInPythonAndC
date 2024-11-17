""" the input consists of 
d||e. d stands for decryption, e stands for encryption

then comes 3 numbers
p, q and e.         P and q are prime numbers and e is something different

then comes numbers that need to be encrypted

encryption is pretty easy

algorithm for encryption is:
multiply the prime numbers p and q with eachother and set it in n
then you have the message which in this case are numbers pi
then you do pi to the power e  and do that result mod n that is the encrypted message


algorithm for decryption is iets moeilijker maar ook prima te doen  """

def encrypt(Mi, e, n):
    # Example encryption function using modular exponentiation (Mi^e % n)
    # Mi is the plaintext, e is the public exponent, and n is the modulus
    return pow(Mi, e, n)

def decrypt(Ci, d, n):
    # Example decryption function using modular exponentiation (Ci^d % n)
    # Ci is the ciphertext, d is the private key, and n is the modulus
    return pow(Ci, d, n)

# This decides whether you have to encrypt or decrypt
EorD = input("Type 'e' for encryption or 'd' for decryption: ")

# Input the values of p, q, and e
p, q, e = map(int, input("Enter p, q, and e (separated by spaces): ").split())

# Calculate n and the totient function phi(n)
n = p * q
phi_n = (p - 1) * (q - 1)

# Calculate the private key (d) by finding the modular inverse of e modulo phi_n
def mod_inverse(a, m):
    # Extended Euclidean Algorithm to find the modular inverse of a mod m
    def extended_gcd(a, b):
        if b == 0:
            return a, 1, 0
        g, x1, y1 = extended_gcd(b, a % b)
        x = y1
        y = x1 - (a // b) * y1
        return g, x, y

    g, x, _ = extended_gcd(a, m)
    if g != 1:
        raise ValueError("Inverse doesn't exist")
    return x % m

d = mod_inverse(e, phi_n)

if EorD == 'e':
    # Encryption
    Mi = int(input("Enter the message (integer) to encrypt: "))
    encrypted_message = encrypt(Mi, e, n)
    print(f"Encrypted message: {encrypted_message}")
elif EorD == 'd':
    # Decryption
    Ci = int(input("Enter the message (integer) to decrypt: "))
    decrypted_message = decrypt(Ci, d, n)
    print(f"Decrypted message: {decrypted_message}")
else:
    print("Invalid option")