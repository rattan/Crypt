#ifndef AES_H
#define AES_H

/*
 * Des.h
 * Written by Rattan
 * Version control : https://github.com/rattan/Ctypt
 * copyright (c) 2016 Kang Jin Gu. All rights reserved
 * Follow General Public License(GPL)
 * Create File : 2016/04/15
 * Last Modify : 2016/05/17
 * This class "Aes" can Encrypt and Decrypt 16Byte(128bit) Data with Advanced Encrypt Standard(DES).
 * Key and input data format is std::wstring(unicode/16bit).
 * Key and input data is 128,192,256bit or more or less.
 * If more than 256 bit, key cut over 256bits ~ and data split 128bit and calculate each data.
 * If less than 6128bit, fill 0 over effective value.
 *
 * show standard output when key generating and processing rounds.
 */

#include<string>
#include<array>
#include<iostream>
#include"sender.h"
using namespace std;

// 2d array template
template<typename T, std::size_t N, std::size_t P>
using array2d = std::array<std::array<T,P>,N>;

// shift row policy
struct shift_row{
    inline int operator()(int op1,int op2){return op1-op2+4;}
};
struct shift_row_inv{
    inline int operator()(int op1,int op2){return op1+op2;}
};

class Aes
{

    wstring key;

    // Cipher key with byte array
    array<uint8_t,32> key_256;
    // Expanded cipher keys
    array<uint8_t,240> expand_key;

    // Enc,Dec value
    array2d<uint8_t,4,4> state_src;
    array2d<uint8_t,4,4> state_dst;

    // AES Constant tables.
    static const uint8_t T_S_Box[16][16];
    static const uint8_t T_S_Box_Inv[16][16];
    static const uint8_t T_Mix_Col_E[16][16];
    static const uint8_t T_Mix_Col_L[16][16];
    static const uint8_t T_Const_Mix[4][4];
    static const uint8_t T_Const_Mix_Inv[4][4];
    int cipher_key_length;
    int round_count;

    // key generate.
    void _key_Expansion();
    array<uint8_t,4> _make_temp_word(array<uint8_t,4> w,uint8_t RCon);


    // Round blocks
    void _pre_round_transformation();
    array2d<uint8_t,4,4> _sub_bytes(array2d<uint8_t,4,4> src_state, const uint8_t table[][16]);
    template<typename T> array2d<uint8_t,4,4> _shift_rows(array2d<uint8_t,4,4> src_state,T sel);
    array2d<uint8_t,4,4> _mix_columns(array2d<uint8_t,4,4> src_state, const uint8_t table[][4]);
    array2d<uint8_t,4,4> _add_round_key(array2d<uint8_t,4,4> src_state, const int ex_key_index);

    // Enc,Dec Encapsulation
    void _Encrypt();
    void _Decrypt();

    void clear_state();
    void cout_state(const array2d<uint8_t,4,4> src);    // this function shows state's value with standard output

public:
    Aes();

    // define aes key length
    enum {keylen_128 = 128,keylen_192 = 192,keylen_256 = 256};

    // Aes key.
    wstring getKey() const;
    void setKey(const wstring &value,int c_key_len);

    // Do Encrypt, Decrypt
    wstring Encrypt(wstring source);
    wstring Decrypt(wstring source);

    Sender sender;
};

#endif // AES_H
