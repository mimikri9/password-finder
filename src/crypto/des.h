#pragma once
//@RKarpov: It's not my code. Sorry.
//Herb Sutter Exceptional C++ 
//excuse: 87  New Engineering Puzzles,... Task 3.1, first recomendation.
//The MIT License (MIT)

//Copyright (c) 2014 Faraz Fallahi

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include <cstdint>

using byte8 = uint64_t;
using byte4 = uint32_t;
using byte2 = uint16_t;
using byte  = uint8_t;

class DES
{
public:
    DES(byte8 key);
    byte8 des(byte8 block, bool mode);

    byte8 encrypt(byte8 block);
    byte8 decrypt(byte8 block);

    static byte8 encrypt(byte8 block, byte8 key);
    static byte8 decrypt(byte8 block, byte8 key);

protected:
    void keygen(byte8 key);

    byte8 ip(byte8 block);
    byte8 fp(byte8 block);

    void feistel(byte4 &L, byte4 &R, byte4 F);
    byte4 f(byte4 R, byte8 k);

private:
    byte8 sub_key[16]; // 48 bits each
};

