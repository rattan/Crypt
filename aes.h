#ifndef AES_H
#define AES_H

/*
 * Des.h
 * Written by Rattan
 * Version control : https://github.com/rattan/Ctypt
 * copyright (c) 2016 Kang Jin Gu. All rights reserved
 * Follow General Public License(GPL)
 * Create File : 2016/04/15
 * Last Modify : 2016/05/14
 * This class "Aes" can Encrypt and Decrypt 16Byte(128bit) Data with Advanced Encrypt Standard(DES).
 * Key and input data format is std::wstring(unicode/16bit).
 * Key and input data is 128,192,256bit or more or less.
 * If more than 256 bit, key cut over 256bits ~ and data split 128bit and calculate each data.
 * If less than 6128bit, fill 0 over effective value.
 */

#include<string>
#include<array>
using namespace std;

template<typename T, std::size_t N, std::size_t P>
using array2d = std::array<std::array<T,P>,N>;

struct shift_row{
    inline int operator()(int op1,int op2){return op1-op2+4;}
};
struct shift_row_inv{
    inline int operator()(int op1,int op2){return op1+op2;}
};

struct add_round{
    inline uint8_t operator()(uint8_t op1,uint8_t op2){return op1;}
};
struct add_round_Inv{
    inline uint8_t operator()(uint8_t op1,uint8_t op2){return op1^op2;}
};


class Aes
{
    wstring key;

    array<uint8_t,32> key_256;

    array<uint8_t,240> expand_key;

    array2d<uint8_t,4,4> state_src;
    array2d<uint8_t,4,4> state_dst;

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



    void _pre_round_transformation();
    void _round();
    array2d<uint8_t,4,4> _sub_bytes(array2d<uint8_t,4,4> src_state, const uint8_t table[][16]);
    template<typename T> array2d<uint8_t,4,4> _shift_rows(array2d<uint8_t,4,4> src_state,T sel);
    array2d<uint8_t,4,4> _mix_columns(array2d<uint8_t,4,4> src_state, const uint8_t table[][4]);
    template<typename T> array2d<uint8_t,4,4> _add_round_key(array2d<uint8_t,4,4> src_state, const int ex_key_index,T sel);

    void _Encrypt();
    void _Decrypt();

    void clear_state();

public:
    Aes();

    enum {keylen_128 = 128,keylen_192 = 192,keylen_256 = 256};

    wstring getKey() const;
    void setKey(const wstring &value,int c_key_len);
    wstring Encrypt(wstring source);
    wstring Decrypt(wstring source);
};

#endif // AES_H
