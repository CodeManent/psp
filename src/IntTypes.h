#ifndef INTTYPES_H_
#define INTTYPES_H_


#if defined linux
	#include <stdint.h>
	typedef uint64_t uint64;
	typedef int64_t int64;
	typedef uint32_t uint32;
	typedef int32_t int32;
	typedef uint16_t uint16;
	typedef int16_t int16;
	typedef uint8_t uint8;
	typedef int8_t int8;
#elif defined WIN32
	typedef unsigned __int64 uint64;
	typedef __int64 int64;
	typedef unsigned __int32 uint32;
	typedef __int32 int32;
	typedef unsigned __int16 uint16;
	typedef __int16 int16;
	typedef unsigned __int8 uint8;
	typedef __int8 int8;
#endif

#include <stdint.h>
typedef uint64_t uint64;
typedef int64_t int64;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint8_t uint8;
typedef int8_t int8;

typedef struct replacementOf128bitInt{
	uint32 LOLO;
	uint32 LOHI;
	uint32 HILO;
	uint32 HIHI;
} uint128;

typedef unsigned int uint;

#endif
