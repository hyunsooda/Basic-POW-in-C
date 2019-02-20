# Basic-POW-in-C

## Todo

Migrate work of finding hash to GPGPU(CUDA) rather than multiple-thread(POSIX standard) or Go-routine(not parallel)

Big int library for CUDA:https://github.com/dmatlack/cuda-rsa/blob/master/src/mpz/digit.h

## Run
You should install gmp library(for big integer) before run the source code.
```
g++ proofofwork.cpp sha256.cpp -lgmp  && ./a.out
````
