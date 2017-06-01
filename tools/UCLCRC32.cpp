//
// Created by Fly on 2017/1/15.
//

#include "UCLCRC32.h"

void UCLCRC32::make_table()
{
    int i, j ;
    have_table = true ;
    for (i = 0 ; i < 256 ; i++)
        for (j = 0, table[i] = i ; j < 8 ; j++)
            table[i] = (table[i]>>1)^((table[i]&1)?POLYNOMIAL:0) ;
}

string crc32(const string &buff)
{
    uint32_t crc = 0;
    UCLCRC32 uclcrc32 = UCLCRC32();
    if (!uclcrc32.have_table) uclcrc32.make_table() ;
    crc = ~crc;
    for (int i = 0; i < buff.length(); i++)
        crc = (crc >> 8) ^ uclcrc32.table[(crc ^ buff[i]) & 0xff];
    char crc32[8];
    sprintf(crc32,"%08x",~crc);
    return crc32;
}