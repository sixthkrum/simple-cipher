simple-cipher is a simple text file encryption program for the terminal

It takes three arguments:

First argument: e/d e: encryption , d: decryption

Second argument: file name

Third argument: password

It encrypts the text by:

1. Devides the file into blocks of characters the size of the password

2. Adding the characters of the block and the password (character by character, taking modulus 256 of the result if the sum exceeds 256)

3. XOR-ing the added characters and the password

The resulting block is outputted to the encrypted file.

The file is decrypted by reversing these steps.

If the size of the last block in the file was less than the password size then trailing '0's appear in the decryption 

to build: g++ simple-cipher.cpp
