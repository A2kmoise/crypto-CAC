#include <stdio.h>
#include <string.h>

void decrypt(char encMes[]) {
    printf("Enter the key: ");
    int key;
    scanf("%d", &key);
    
    int length = strlen(encMes);
    char decrypted[length + 1]; // To hold the decrypted message

    for (int i = 0; i < length; i++) {
        char ch = encMes[i];

        // Decrypt uppercase letters
        if (ch >= 'A' && ch <= 'Z') {
            decrypted[i] = (ch - key < 'A') ? (ch - key + 26) : (ch - key);
        }
        // Decrypt lowercase letters
        else if (ch >= 'a' && ch <= 'z') {
            decrypted[i] = (ch - key < 'a') ? (ch - key + 26) : (ch - key);
        } else {
            // Non-alphabetic characters remain unchanged
            decrypted[i] = ch;
        }
    }
    decrypted[length] = '\0'; // Null-terminate the decrypted string

    printf("Decrypted message: %s\n", decrypted);
}

int main() {
    char encMes[100]; // Adjust the size as needed
    printf("Enter your encrypted message: ");
    scanf("%s", encMes);

    decrypt(encMes);

    return 0;
}
