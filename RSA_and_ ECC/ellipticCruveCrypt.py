def point_addition(P, Q, a, p):
    
    if P == (None, None):
        return Q
    if Q == (None, None):
        return P

    (x1, y1) = P
    (x2, y2) = Q

    
    if x1 == x2 and (y1 + y2) % p == 0:
        return (None, None)

    if P == Q:
        # Point doubling case
        s = (3 * x1 * x1 + a) * pow(2 * y1, p - 2, p) % p  # fermat thereom
    else:
        # Point addition case
        s = (y2 - y1) * pow(x2 - x1, p - 2, p) % p  # fermat theroem

    x3 = (s * s - x1 - x2) % p
    y3 = (s * (x1 - x3) - y1) % p

    return (x3, y3)

def scalar_multiplication(k, P, a, p):
    Q = (None, None) 
    N = P

    while k > 0:
        if k % 2 == 1:
            Q = point_addition(Q, N, a, p)
        N = point_addition(N, N, a, p)
        k //= 2

    return Q


def main():
    # Step 1: Parse the input data
    
    point = tuple(map(int, input().strip("()").split(", ")))

    
    a, b, p = map(int, input().split())

    
    m, n = map(int, input().split())

    # Step 2: Compute public keys
    # A's public key: m * P
    """ #A_public_key = scalar_multiplication(m, point, a, p)
    #print(f"A's public key: {A_public_key}") """

    # B's public key: n * P
    B_public_key = scalar_multiplication(n, point, a, p)
    #print(f"B's public key: {B_public_key}")

    # Step 3: Compute shared secrets
    """   Shared secret computed by A: m * (n * P) """
    shared_secret_A = scalar_multiplication(m, B_public_key, a, p)

    """ Shared secret computed by B: n * (m * P)
    #shared_secret_B = scalar_multiplication(n, A_public_key, a, p)

    Both shared secrets should be equal
    #assert shared_secret_A == shared_secret_B, "Shared secrets do not match!" """

    # Output the shared secret
    print(f"{shared_secret_A}")


if __name__ == "__main__":
    main()