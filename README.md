# rc4-poc

Proof of concept for local OpenSSL RC4 buffer overrun bug

Compiling
---------

gcc / clang -O rc4_poc.c -o rc4_poc check.c -I/path/to/openssl-1.0.2f/include \
  -L/path/to/openssl-1.0.2f -lssl -lcrypto -pthread
