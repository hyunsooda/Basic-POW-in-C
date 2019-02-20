#include <iostream>
#include <gmp.h>
#include <string.h>
#include <unistd.h>
#include "sha256.h"

using namespace std;

const int targetBit = 20;

void genRandomTransactionHash(char *dest, size_t length) {
    srand(time(NULL));

    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

string prepareData(unsigned long timestamp, string transactionHash, unsigned long long nonce) {
    char output[200];
    sprintf(output, "%lu%s%llu", timestamp, transactionHash, nonce);
    string temp(output);
    string outputHash = sha256(temp);
    return outputHash;
}

void mine() {
    unsigned long long nonce = 0;
    unsigned long timestamp = (unsigned long)time(NULL);
    char transaction[50];
    string hash;
    mpz_t byteHash;
    mpz_t target, tempBit;
    unsigned char isSuccess;

    genRandomTransactionHash(transaction, sizeof(transaction));
    string temp(transaction);
    string transactionHash = sha256(temp);

    mpz_init(byteHash);
    mpz_init(target);
    mpz_init(tempBit);
    mpz_set_ui(byteHash,0);
    mpz_set_ui(target,0);
    mpz_set_ui(tempBit,0);
    mpz_set_str(tempBit, "1", 2);
    mpz_mul_2exp(target, tempBit, 256 - targetBit);

    while(1) {
        hash = prepareData(timestamp, transactionHash, nonce);
        const char* charHash = hash.c_str();
        printf("\r%s", charHash);
        mpz_set_str(byteHash, charHash , 16);
        isSuccess = mpz_cmp(target, byteHash);
        if(isSuccess == 1) {
            printf("\n");
            mpz_out_str(stdout, 2, target);
            printf("\n\n");
            mpz_out_str(stdout, 2, byteHash);
            printf("\nsuccess\n");
            break;
        }
        nonce++;
    }   
}


int main(int argc, char *argv[])
{
    mine();
    return 0;
}