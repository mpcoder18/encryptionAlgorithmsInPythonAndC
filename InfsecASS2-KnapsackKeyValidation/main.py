import sys
import math

# handling the modulus
try:
    multiplier, modulus = map(int, input().split())
    if modulus <= 0:
        print(-1)
        sys.exit(0)

    # this sets the elements in the array
    privateKey = list(map(int, input().split()))
    publicKey = list(map(int, input().split()))

    # Ensure both arrays are of equal length
    if len(privateKey) != len(publicKey):
        print(0)
        sys.exit(0)

    privateKeySum = 0
    output = 1  # Assume valid until proven otherwise

    # checking if the private key is a superincreasing knapsack
    for j in range(len(privateKey) - 1):
        privateKeySum += privateKey[j]
        if privateKey[j + 1] <= privateKeySum:
            output = -1
            break  # No need to continue checking further

    # sum of the privateKey must be smaller than the modulus in order to work
    sumprivateKey = sum(privateKey)

    # the greatest common divisor must be 1
    gcdResult = math.gcd(multiplier, modulus)

    # if the private key conditions fail
    if modulus <= sumprivateKey or gcdResult != 1:
        output = -1

    # Only check public key if private key is valid
    if output != -1:
        for i in range(len(privateKey)):
            if ((privateKey[i] * multiplier) % modulus) != publicKey[i]:
                output = 0
                break  # No need to continue if any mismatch is found

    print(output)

except ValueError:
    # Handle unexpected input, for instance if the input cannot be converted to int
    print(-1)
    sys.exit(7)
    




