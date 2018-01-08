#include <stdio.h>
#include <stdlib.h>
#include "crypto.h"
#include <string.h>

int tests_run = 0;

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

static char* test_encrypt1() {
    KEY k = {1, "TPERULES"};
    const char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* output = (char*) malloc(strlen(input) + 1);
    encrypt(k, input, output);
    mu_assert("test_encrypt1 > failed",strcmp(output,"URFVPJB[]ZN^XBJCEBVF@ZRKMJ") == 0);
    return 0;
}

static char* test_encrypt2() {
    KEY k = {1, "MYKEY"};
    const char* input = "HALLO";
    char* output = (char*) malloc(strlen(input) + 1);
    encrypt(k, input, output);
    mu_assert("test_encrypt2 > failed", strcmp(output, "EXGIV") == 0);
    return 0;
}

static char* test_keylength() {
    KEY k = {1, ""};
    const char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* output = (char*) malloc(strlen(input) + 1);
    int error = encrypt(k, input, output);
    mu_assert("test_keylength > failed", error == E_KEY_TOO_SHORT);
    return 0;
}

static char* test_key_contains_illegal_char1() {
    KEY k = {1, "l33_t"};
    const char* input = "GEHEIM";
    char* output = (char*) malloc(strlen(input) + 1);
    int error = encrypt(k, input, output);
    mu_assert("test_key_contains_illegal_char1 > failed", error == E_KEY_ILLEGAL_CHAR);
    return 0;
}

static char* test_key_contains_illegal_char2() {
    KEY k = {1, "l33_t"};
    const char* input = "GEHEIM";
    char* output = (char*) malloc(strlen(input) + 1);
    int error = decrypt(k, input, output);
    mu_assert("test_key_contains_illegal_char2 > failed", error == E_KEY_ILLEGAL_CHAR);
    return 0;
}


static char* test_message_contains_illegal_char() {
    KEY k = {1, "TPERULES"};
    const char* input = "_";
    char* output = (char*) malloc(strlen(input) + 1);
    int error = encrypt(k, input, output);
    mu_assert("test_message_contains_illegal_char > failed", error == E_MESSAGE_ILLEGAL_CHAR);
    return 0;
}

static char* test_cypherText_contains_illegal_char() {
    KEY k = {1, "TPERULES"};
    const char* input = "*";
    char* output = (char*) malloc(strlen(input) + 1);
    int error = decrypt(k, input, output);
    mu_assert("test_cypherText_contains_illegal_char > failed", error == E_CYPHER_ILLEGAL_CHAR);
    return 0;
}

static char* test_encrypt_decrypt() {
    KEY k = {1, "TPERULES"};
    const char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* output = (char*) malloc(strlen(input) + 1);
    char* output2 = (char*) malloc(strlen(input) + 1);
    encrypt(k, input, output);
    decrypt(k, output, output2);
    mu_assert("test_encrypt_decrypt > failed", strcmp(output2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 0);
    return 0;
}

static char* test_decrypt1() {
    KEY k = {1, "TPERULES"};
    const char* cypherText = "URFVPJB[]ZN^XBJCEBVF@ZRKMJ";
    char* output = (char*) malloc(strlen(cypherText) + 1);
    decrypt(k, cypherText, output);
    mu_assert("test_decrypt1 > failed",strcmp(output,"ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 0);
    return 0;
}


static char* allTests() {
    mu_run_test(test_encrypt1);
    mu_run_test(test_keylength);
    mu_run_test(test_encrypt2);
    mu_run_test(test_key_contains_illegal_char1);
    mu_run_test(test_key_contains_illegal_char2);
    mu_run_test(test_message_contains_illegal_char);
    mu_run_test(test_cypherText_contains_illegal_char);
    mu_run_test(test_encrypt_decrypt);
    mu_run_test(test_decrypt1);
    return 0;
}

int main() {
    char *result = allTests();

    if (result != 0) printf("%s\n", result);
    else             printf("ALL TESTS PASSED\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
