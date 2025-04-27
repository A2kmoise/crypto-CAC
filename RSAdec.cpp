#include <stdio.h>

// Function to compute GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular inverse of e mod f(n)
int mod_inverse(int e, int phi) {
    int t = 0, new_t = 1;
    int r = phi, new_r = e;

    while (new_r != 0) {
        int quotient = r / new_r;

        int temp = new_t;
        new_t = t - quotient * new_t;
        t = temp;

        temp = new_r;
        new_r = r - quotient * new_r;
        r = temp;
    }

    if (r > 1) return -1; // No inverse
    if (t < 0) t += phi;

    return t;
}

// Modular exponentiation (base^exp % mod)
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

int main() {
    // Step 1: Key generation
    int p = 61;
    int q = 53;
    int n = p * q;             // n = 3233
    int phi = (p - 1) * (q - 1); // f(n) = 3120

    int e = 17;  // Public exponent (common choice)
    if (gcd(e, phi) != 1) {
        printf("e and phi(n) are not coprime.\n");
        return 1;
    }

    int d = mod_inverse(e, phi); // Private exponent
    if (d == -1) {
        printf("Modular inverse of e does not exist.\n");
        return 1;
    }

    printf("Public Key:  (e=%d, n=%d)\n", e, n);
    printf("Private Key: (d=%d, n=%d)\n\n", d, n);

    // Step 2: User enters message
    int message;
    printf("Enter a message to decrypt (as number 0-127): ");
    scanf("%d", &message);

    if (message < 0 || message > 127) {
        printf("Message out of range.\n");
        return 1;
    }

    // Step 3: Encrypt the message
    long long encrypted = mod_exp(message, e, n);
    printf("Encrypted message: %lld\n", encrypted);

    // Step 4: Decrypt the message
    long long decrypted = mod_exp(encrypted, d, n);
    printf("Decrypted message (numeric): %lld\n", decrypted);
    printf("Decrypted character: %c\n", (char)decrypted);

    return 0;
}
