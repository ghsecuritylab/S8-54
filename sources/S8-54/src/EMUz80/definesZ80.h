#pragma once


typedef short unsigned int uint16;
typedef unsigned char uint8;
typedef unsigned int uint;
typedef signed short int16;
typedef signed char int8;


typedef uint8 bool;



#define false 0
#define true (!false)

#define _bitset(bits)                               \
  ((uint8)(                                         \
  (((uint8)((uint)bits / 01)        % 010) << 0) |  \
  (((uint8)((uint)bits / 010)       % 010) << 1) |  \
  (((uint8)((uint)bits / 0100)      % 010) << 2) |  \
  (((uint8)((uint)bits / 01000)     % 010) << 3) |  \
  (((uint8)((uint)bits / 010000)    % 010) << 4) |  \
  (((uint8)((uint)bits / 0100000)   % 010) << 5) |  \
  (((uint8)((uint)bits / 01000000)  % 010) << 6) |  \
  (((uint8)((uint)bits / 010000000) % 010) << 7)))

#define BINARY_U8( bits ) _bitset(0##bits)

typedef int(*pFuncIV)(void);
typedef uint8*(*pFuncpU8V)(void);
typedef uint16*(*pFuncpU16V)(void);
typedef void(*pFuncVU16)(uint16);
typedef bool(*pFuncBV)(void);

#define GET_nBIT(value, bit) (((value) & (1 << bit)) >> bit)
#define SET_nBIT(value, bit) ((value) | (1 << bit))
#define RES_nBIT(value, bit) ((value) & (~(1 << bit)))
#define LOAD_nBIT(value, bit, vBit) if(vBit) ((value) |= (1 << bit)); else ((value) &= (~(1 << bit)))

#define LISTING
