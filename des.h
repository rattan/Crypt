#ifndef DES_H
#define DES_H

/*
 * Des.h
 * Written by Rattan
 * Version control : https://github.com/rattan/Ctypt
 * copyright (c) 2016 Kang Jin Gu. All rights reserved
 * Follow General Public License(GPL)
 * Create File : 2016/04/15
 * Last Modify : 2016/05/14
 * This class "Des" can Encrypt and Decrypt 8Byte(64bit) Data with Data Encrypt Standard(DES).
 * Key and input data format is std::wstring(unicode/16bit).
 * Key and input data is 64bit or more or less.
 * If more than 64 bit, key cut over 64bits ~ and data split 64bit and calculate each data.
 * If less than 64bit, fill 0 over effective value.
 *
 * show standard output when key generating and processing rounds.
 */

#include<string>
#include<bitset>
#include<iostream>

#include"sender.h"

using namespace std;

class Des
{
    // Encrypt, Decrypt value
    bitset<64> data_src;
    bitset<64> data_dst;

    // Des Cipher Key
    wstring key;
    bitset<64> key_64;

    //Des Round Key
    bitset<48> round_key[16];

    // Des Tables
    static const int T_Initial_Permutation[64];
    static const int T_Final_Permutation[64];
    static const int T_Expansion_P_Box[48];
    static const int T_Straight_P_Box[32];
    static const int T_S_Box[8][4][16];
    static const int T_Parity_Drop[56];
    static const int T_Compression_P_Box[48];

    // Key Generator
    void _R_Key_Generate();
    bitset<56> _Parity_Drop(bitset<64> source);
    bitset<56> _Shift_Left(bitset<56> source,int shift_count);
    bitset<48> _Compression_P_Box(bitset<56> source);

    // Encrypt, Decrypt Bolcks
    bitset<64> _Permutation(bitset<64> cource,const int*table);
    bitset<64> _Initial_Permutation(bitset<64> source);
    bitset<64> _Mixer(bitset<64> source,int kn);
    bitset<64> _Swapper(bitset<64> source);
    bitset<64> _Final_Permutation(bitset<64> source);

    // Function Box in Mixer
    bitset<32> _Function(bitset<32> R,const bitset<48> ky);
    bitset<48> _Expansion_P_Box(bitset<32> source);
    bitset<4> _S_Box(bitset<6> buffer,int sn);
    bitset<32> _Straight_P_Box(bitset<32> source);

    // Encrypt, Decrypt Encapsulation
    void _Encrypt();
    void _Decrypt();

public:
    Des();
    Des(wstring ky);
    enum {Enc = 0,Dec = 1};

    // Do Encrypt, Decrypt
    wstring Encrypt(wstring PlainText);
    wstring Decrypt(wstring CipherText);

    // Des Key
    wstring getKey() const;
    void setKey(const wstring &value);

    Sender sender;
};

#endif // DES_Hs
