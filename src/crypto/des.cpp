#include "des.h"
#include "des_key.h"
#include "des_data.h"

DES::DES(byte8 key)
{
    keygen(key);
}

byte8 DES::encrypt(byte8 block)
{
    return des(block, false);
}

byte8 DES::decrypt(byte8 block)
{
    return des(block, true);
}

byte8 DES::encrypt(byte8 block, byte8 key)
{
    DES des(key);
    return des.des(block, false);
}

byte8 DES::decrypt(byte8 block, byte8 key)
{
    DES des(key);
    return des.des(block, true);
}

void DES::keygen(byte8 key)
{
    // initial key schedule calculation
    byte8 permuted_choice_1 = 0; // 56 bits
    for (byte i = 0; i < 56; i++)
    {
        permuted_choice_1 <<= 1;
        permuted_choice_1 |= (key >> (64-PC1[i])) & LB64_MASK;
    }

    // 28 bits
    byte4 C = (byte4) ((permuted_choice_1 >> 28) & 0x000000000fffffff);
    byte4 D = (byte4)  (permuted_choice_1 & 0x000000000fffffff);

    // Calculation of the 16 keys
    for (byte i = 0; i < 16; i++)
    {
        // key schedule, shifting Ci and Di
        for (byte j = 0; j < ITERATION_SHIFT[i]; j++)
        {
            C = (0x0fffffff & (C << 1)) | (0x00000001 & (C >> 27));
            D = (0x0fffffff & (D << 1)) | (0x00000001 & (D >> 27));
        }

        byte8 permuted_choice_2 = (((byte8) C) << 28) | (byte8) D;

        sub_key[i] = 0; // 48 bits (2*24)
        for (byte j = 0; j < 48; j++)
        {
            sub_key[i] <<= 1;
            sub_key[i] |= (permuted_choice_2 >> (56-PC2[j])) & LB64_MASK;
        }
    }
}

byte8 DES::des(byte8 block, bool mode)
{
    // applying initial permutation
    block = ip(block);

    // dividing T' into two 32-bit parts
    byte4 L = (byte4) (block >> 32) & L64_MASK;
    byte4 R = (byte4) (block & L64_MASK);

    // 16 rounds
    for (byte i = 0; i < 16; i++)
    {
        byte4 F = mode ? f(R, sub_key[15-i]) : f(R, sub_key[i]);
        feistel(L, R, F);
    }

    // swapping the two parts
    block = (((byte8) R) << 32) | (byte8) L;
    // applying final permutation
    return fp(block);
}

byte8 DES::ip(byte8 block)
{
    // initial permutation
    byte8 result = 0;
    for (byte i = 0; i < 64; i++)
    {
        result <<= 1;
        result |= (block >> (64-IP[i])) & LB64_MASK;
    }
    return result;
}

byte8 DES::fp(byte8 block)
{
    // inverse initial permutation
    byte8 result = 0;
    for (byte i = 0; i < 64; i++)
    {
        result <<= 1;
        result |= (block >> (64-FP[i])) & LB64_MASK;
    }
    return result;
}

void DES::feistel(byte4 &L, byte4 &R, byte4 F)
{
    byte4 temp = R;
    R = L ^ F;
    L = temp;
}

byte4 DES::f(byte4 R, byte8 k) // f(R,k) function
{
    // applying expansion permutation and returning 48-bit data
    byte8 s_input = 0;
    for (byte i = 0; i < 48; i++)
    {
        s_input <<= 1;
        s_input |= (byte8) ((R >> (32-EXPANSION[i])) & LB32_MASK);
    }

    // XORing expanded Ri with Ki, the round key
    s_input = s_input ^ k;

    // applying S-Boxes function and returning 32-bit data
    byte4 s_output = 0;
    for (byte i = 0; i < 8; i++)
    {
        // Outer bits
        char row = (char) ((s_input & (0x0000840000000000 >> 6*i)) >> (42-6*i));
        row = (row >> 4) | (row & 0x01);

        // Middle 4 bits of input
        char column = (char) ((s_input & (0x0000780000000000 >> 6*i)) >> (43-6*i));

        s_output <<= 4;
        s_output |= (byte4) (SBOX[i][16*row + column] & 0x0f);
    }

    // applying the round permutation
    byte4 f_result = 0;
    for (byte i = 0; i < 32; i++)
    {
        f_result <<= 1;
        f_result |= (s_output >> (32 - PBOX[i])) & LB32_MASK;
    }

    return f_result;
}