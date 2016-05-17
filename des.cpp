#include "des.h"
const int Des::T_Initial_Permutation[64] = {
    58, 50, 42, 34, 26 ,18 ,10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7 };

const int Des::T_Final_Permutation[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25 };

const int Des::T_Expansion_P_Box[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1 };

const int Des::T_Straight_P_Box[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25 };

const int Des::T_S_Box[8][4][16] = {
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},

    {{15 ,1 ,8 ,14 ,6 ,11 ,3 ,4 ,9 ,7 ,2 ,13 ,12 ,0 ,5 ,10},
     {3 ,13 ,4 ,7 ,15 ,2 ,8 ,14 ,12 ,0 ,1 ,10 ,6 ,9 ,11 ,5},
     {0 ,14 ,7 ,11 ,10 ,4 ,13 ,1 ,5 ,8 ,12 ,6 ,9 ,3 ,2 ,15},
     {13 ,8 ,10 ,1 ,3 ,15 ,4 ,2 ,11 ,6 ,7 ,12 ,0 ,5 ,14 ,9}},

    {{10 ,0 ,9 ,14 ,6 ,3 ,15 ,5 ,1 ,13 ,12 ,7 ,11 ,4 ,2 ,8},
     {13 ,7 ,0 ,9 ,3 ,4 ,6 ,10 ,2 ,8 ,5 ,14 ,12 ,11 ,15 ,1},
     {13 ,6 ,4 ,9 ,8 ,15 ,3 ,0 ,11 ,1 ,2 ,12 ,5 ,10 ,14 ,7},
     {1 ,10 ,13 ,0 ,6 ,9 ,8 ,7 ,4 ,15 ,14 ,3 ,11 ,5 ,2 ,12}},

    {{7 ,13 ,14 ,3 ,0 ,6 ,9 ,10 ,1 ,2 ,8 ,5 ,11 ,12 ,4 ,15},
     {13 ,8 ,11 ,5 ,6 ,15 ,0 ,3 ,4 ,7 ,2 ,12 ,1 ,10 ,14 ,9},
     {10 ,6 ,9 ,0 ,12 ,11 ,7 ,13 ,15 ,1 ,3 ,14 ,5 ,2 ,8 ,4},
     {3 ,15 ,0 ,6 ,10 ,1 ,13 ,8 ,9 ,4 ,5 ,11 ,12 ,7 ,2 ,14}},

    {{2 ,12 ,4 ,1 ,7 ,10 ,11 ,6 ,8 ,5 ,3 ,15 ,13 ,0 ,14 ,9},
     {14 ,11 ,2 ,12 ,4 ,7 ,13 ,1 ,5 ,0 ,15 ,10 ,3 ,9 ,8 ,6},
     {4 ,2 ,1 ,11 ,10 ,13 ,7 ,8 ,15 ,9 ,12 ,5 ,6 ,3 ,0 ,14},
     {11 ,8 ,12 ,7 ,1 ,14 ,2 ,13 ,6 ,15 ,0 ,9 ,10 ,4 ,5 ,3}},

    {{12 ,1 ,10 ,15 ,9 ,2 ,6 ,8 ,0 ,13 ,3 ,4 ,14 ,7 ,5 ,11},
     {10 ,15 ,4 ,2 ,7 ,12 ,9 ,5 ,6 ,1 ,13 ,14 ,0 ,11 ,3 ,8},
     {9 ,14 ,15 ,5 ,2 ,8 ,12 ,3 ,7 ,0 ,4 ,10 ,1 ,13 ,11 ,6},
     {4 ,3 ,2 ,12 ,9 ,5 ,15 ,10 ,11 ,14 ,1 ,7 ,6 ,0 ,8 ,13}},

    {{4 ,11 ,2 ,14 ,15 ,0 ,8 ,13 ,3 ,12 ,9 ,7 ,5 ,10 ,6 ,1},
     {13 ,0 ,11 ,7 ,4 ,9 ,1 ,10 ,14 ,3 ,5 ,12 ,2 ,15 ,8 ,6},
     {1 ,4 ,11 ,13 ,12 ,3 ,7 ,14 ,10 ,15 ,6 ,8 ,0 ,5 ,9 ,2},
     {6 ,11 ,13 ,8 ,1 ,4 ,10 ,7 ,9 ,5 ,0 ,15 ,14 ,2 ,3 ,12}},

    {{13 ,2 ,8 ,4 ,6 ,15 ,11 ,1 ,10 ,9 ,3 ,14 ,5 ,0 ,12 ,7},
     {1 ,15 ,13 ,8 ,10 ,3 ,7 ,4 ,12 ,5 ,6 ,11 ,0 ,14 ,9 ,2},
     {7 ,11 ,4 ,1 ,9 ,12 ,14 ,2 ,0 ,6 ,10 ,13 ,15 ,3 ,5 ,8},
     {2 ,1 ,14 ,7 ,4 ,10 ,8 ,13 ,15 ,12 ,9 ,0 ,3 ,5 ,6 ,11}}
};

const int Des::T_Parity_Drop[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4 };

const int Des::T_Compression_P_Box[48] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32 };

array<uint8_t,8> Des::getKey() const
{
    return key;
}

/*
 * Set a Des Key
 */
void Des::setKey(const array<uint8_t,8> &value)
{
    key = value;
    key_64.reset();
    for (int i = 0; i < 8 ; ++i)
    {
        uint8_t c = key[7 - i];
        for (int j = 0; j < 8 && c; ++j) {
            if (c & 0x1) {
                key_64.set(8 * i + j);
            }
            c >>= 1;
        }
    }

//    key = value;
//    key_64.reset();
//    int kl = key.length();
//    if(kl>4) kl = 4;
//    for (int i = 0; i < kl ; ++i)
//    {
//        wchar_t c = key[kl- 1 - i];
//        for (int j = 0; j < 16 && c; ++j) {
//            if (c & 0x1) {
//                key_64.set(16 * i + j);
//            }
//            c >>= 1;
//        }
//    }
    _R_Key_Generate();
}

/*
 * Round Key generation
 */
void Des::_R_Key_Generate()
{
    bitset<56> temp = _Parity_Drop(key_64);
    const int shift_count[] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
    sender.send_str("DES Round Keys :");
//    cout<<"DES Round Keys : "<<endl;
    for (int i = 0; i < 16; ++i)
    {
        temp = _Shift_Left(temp, shift_count[i]);
        round_key[i] = _Compression_P_Box(temp);
        sender.send_str("R Key["+to_string(i+1)+"]"+round_key[i].to_string());
//        cout<<"R_Key["<<i<<"] : "<<round_key[i].to_string()<<endl;
    }
    sender.send_str("");
//    cout<<endl;
}

/*
 * Drop parity bit
 */
bitset<56> Des::_Parity_Drop(bitset<64> source)
{
    bitset<56> res_buffer;
    for (int i = 0; i < 56; ++i) res_buffer[55 - i] = source[64 - T_Parity_Drop[i]];
    return res_buffer;
}

/*
 * Compress P box
 */
bitset<48> Des::_Compression_P_Box(bitset<56> source)
{
    bitset<48> res_buffer;
    for (int i = 0; i < 48; ++i) res_buffer[47 - i] = source[56 - T_Compression_P_Box[i]];
    return res_buffer;
}
/*
 * Shift Left with shiftcount
 */
bitset<56> Des::_Shift_Left(bitset<56> source, int shift_count)
{
    bitset<56> res_buffer = source << shift_count;
    if (shift_count == 1)
    {
        res_buffer[0] = source[27];
        res_buffer[28] = source[55];
    }
    if (shift_count == 2)
    {
        res_buffer[0] = source[26];
        res_buffer[1] = source[27];
        res_buffer[28] = source[54];
        res_buffer[29] = source[55];
    }
    return res_buffer;
}

/*
 * Permutation with input table
 */
bitset<64> Des::_Permutation(bitset<64> source, const int *table)
{
    bitset<64> res_buffer;
    for (int i = 0; i < 64; ++i) res_buffer[63 - i] = source[64 - table[i]];
    return res_buffer;
}

/*
 * Initial Permutation
 */
bitset<64> Des::_Initial_Permutation(bitset<64> source)
{
    return _Permutation(source, T_Initial_Permutation);
}

/*
 * Mixer
 */
bitset<64> Des::_Mixer(bitset<64> source, int kn)
{
    bitset<64> res_buffer;
    bitset<32> buf_L, buf_R;
    for (int i = 0; i < 32; ++i)
    {
        buf_R[i] = source[i];
        buf_L[i] = source[32 + i];
    }
    buf_L ^= _Function(buf_R, round_key[kn]);
    for (int i = 0; i < 32; ++i)
    {
        res_buffer[i] = buf_R[i];
        res_buffer[i + 32] = buf_L[i];
    }
    return res_buffer;
}

/*
 * Swapper
 */
bitset<64> Des::_Swapper(bitset<64> source)
{
    bitset<64> res_buffer;
    for (int i = 0; i < 32; ++i)
    {
        res_buffer[i] = source[i + 32];
        res_buffer[i + 32] = source[i];
    }
    return res_buffer;
}

/*
 * Final Permutation
 */
bitset<64> Des::_Final_Permutation(bitset<64> source)
{
    return _Permutation(source, T_Final_Permutation);
}

/*
 * Function for Mixer
 */
bitset<32> Des::_Function(bitset<32> R, bitset<48> ky)
{
    bitset<48> temp_buffer = _Expansion_P_Box(R) ^ ky;
    bitset<6> buf_6;
    bitset<4> buf_4;
    bitset<32> res_buffer;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 6; ++j) buf_6[j] = temp_buffer[i * 6 + j];
        buf_4 = _S_Box(buf_6, 7 - i);
        for (int j = 0; j < 4; ++j) res_buffer[i * 4 + j] = buf_4[j];
    }
    return _Straight_P_Box(res_buffer);
}

/*
 * Expansion P Box for Function
 */
bitset<48> Des::_Expansion_P_Box(bitset<32> source)
{
    bitset<48> res_buffer;
    for (int i = 0; i < 48; ++i) res_buffer[47 - i] = source[32 - T_Expansion_P_Box[i]];
    return res_buffer;
}

/*
 * S Box for Function
 */
bitset<4> Des::_S_Box(bitset<6> buffer, int sn)
{
    bitset<4> buf_4;
    bitset<2> buf_2;
    for (int i = 0; i < 4; ++i) buf_4[i] = buffer[i + 1];
    buf_2[0] = buffer[0]; buf_2[1] = buffer[5];
    return bitset<4>(T_S_Box[sn][buf_2.to_ulong()][buf_4.to_ulong()]);
}

/*
 * Straight P Box for Function
 */
bitset<32> Des::_Straight_P_Box(bitset<32> source)
{
    bitset<32> res_buffer;
    for (int i = 0; i < 32; ++i) res_buffer[31 - i] = source[32 - T_Straight_P_Box[i]];
    return res_buffer;
}

/*
 * Encrypt member value : data_src
 */
void Des::_Encrypt()
{
    bitset<64> buffer = _Initial_Permutation(data_src);
    sender.send_str("DES Encrypt Round States :\nAfter Initial Permutation : "+buffer.to_string());
//    cout<<"DES Encrypt Round States :\nAfter Initial Permutation : "<<buffer.to_string()<<endl;
    for (int i = 0; i < 15; ++i)
    {
        buffer = _Swapper(_Mixer(buffer, i));
        sender.send_str("After Round["+to_string(i+1)+"] : "+buffer.to_string());
//        cout<<"After Round["<<i+1<<"] : "<<buffer.to_string()<<endl;
    }
    buffer = _Mixer(buffer, 15);
    sender.send_str("After Round[16] : "+buffer.to_string());
//    cout<<"After Round[16] : "<<buffer.to_string()<<endl;
    data_dst = _Final_Permutation(buffer);
    sender.send_str("After Final Round[Result] : "+data_dst.to_string()+"\n");
//    cout<<"After Final Round[Result] : "<<data_dst.to_string()<<endl<<endl;
}

/*
 * Decryption member value : data_dst
 */
void Des::_Decrypt()
{
    bitset<64> buffer = _Initial_Permutation(data_dst);
    sender.send_str("DES Decrypt Round States :\nAfter Initial Permutation : "+buffer.to_string());
//    cout<<"DES Decrypt Round States :"<<endl<<"After Initial Permutation : "<<buffer.to_string()<<endl;
    for(int i=15;i>0;--i)
    {
        buffer = _Swapper(_Mixer(buffer, i));
        sender.send_str("After Round["+to_string(i+1)+"] : "+buffer.to_string());
//        cout<<"After Round["<<16-i<<"] : "<<buffer.to_string()<<endl;
    }
    buffer = _Mixer(buffer,0);
    sender.send_str("After Round[16] : "+buffer.to_string());
//    cout<<"After Round[16] : "<<buffer.to_string()<<endl;
    data_src = _Final_Permutation(buffer);
    sender.send_str("After Final Round[Result] : "+data_src.to_string()+"\n");
//    cout<<"After Final Round[Result] : "<<data_src.to_string()<<endl<<endl;
}

Des::Des()
{
}

/*
 * Encrypt parameter PlainText.
 * PlainText must be 8Byte.
 */
array<uint8_t,8> Des::Encrypt(array<uint8_t,8> PlainText)
{
    data_src.reset();
    data_dst.reset();
    for (int i = 0; i < 8; ++i)
    {
        uint16_t c = PlainText[i];
        for (int j = 0; j < 8 && c; ++j) {
            if (c & 0x1) {
                data_src.set(8 * (7-i) + j);
            }
            c >>= 1;
        }
    }
    _Encrypt();
    array<uint8_t,8> result;
    for(int i=7;i>=0;--i)
    {
        uint16_t c = 0;
        for(int j=0;j<8;++j)
        {
            data_dst[i*8+j] ? c|=0x01<<j : c;
        }
        result[7-i] = c;
    }
    return result;
}

/*
 * Decrypt parameter CipherText.
 * CipherText must be 8Byte.
 */
array<uint8_t,8> Des::Decrypt(array<uint8_t,8> CipherText)
{
    data_src.reset();
    data_dst.reset();
    for (int i = 0; i < 8; ++i)
    {
        uint16_t c = CipherText[7 - i];
        for (int j = 0; j < 8 && c; ++j) {
            if (c & 0x1) {
                data_dst.set(8 * i + j);
            }
            c >>= 1;
        }
    }
    _Decrypt();
    array<uint8_t,8> result;
    for(int i=7;i>=0;--i)
    {
        uint16_t c = 0;
        for(int j=0;j<8;++j)
        {
            data_src[i*8+j] ? c|=0x01<<j : c;
        }
        result[7-i] = c;
    }

    return result;

}
