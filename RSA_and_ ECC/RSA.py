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

# Helper function to calculate modular inverse of e modulo phi
def modinv(e, phi):
    # Extended Euclidean Algorithm to find modular inverse
    def egcd(a, b):
        if a == 0:
            return b, 0, 1
        g, x, y = egcd(b % a, a)
        return g, y - (b // a) * x, x
    
    g, x, y = egcd(e, phi)
    return x % phi  # Return the modular inverse without raising an exception

# Function to perform RSA encryption or decryption
def rsaEncryptDecrypt(mode, p, q, e, numbers):
    # Calculate n and φ(n)
    n = p * q
    phi = (p - 1) * (q - 1)
    
    if mode == 'd':  # Decrypting
        # Compute private key d using modular inverse of e modulo φ(n)
        d = modinv(e, phi)
    else:  # Encrypting
        d = e  # For encryption, we use the public key e as is

    # Encryption or decryption
    result = []
    for num in numbers:
        if mode == 'e':  # Encrypt
            encrypted = pow(num, e, n)  # Perform modular exponentiation
            result.append(encrypted)
        elif mode == 'd':  # Decrypt
            decrypted = pow(num, d, n)  # Perform modular exponentiation with private key
            result.append(decrypted)
    
    return result

# Input reading and processing
def main():
    # Read the input (assuming the inputs are in the correct format as per the image)
    mode = input()  # 'e' for encrypt or 'd' for decrypt
    p, q, e = map(int, input().split())  # Read p, q, e
    numbers = []
    
    # Read the numbers to be encrypted or decrypted
    try:
        while True:
            number = int(input().strip())
            numbers.append(number)
    except EOFError:
        pass

    # Perform encryption or decryption
    result = rsaEncryptDecrypt(mode, p, q, e, numbers)

    # Print the result
    for r in result:
        print(r)

# Run the program
if __name__ == "__main__":
    main()