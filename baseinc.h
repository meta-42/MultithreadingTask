#pragma once
#include <windows.h>

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <list>
#include <assert.h>

#include <thread>
#include <mutex> 
#include <condition_variable> 

#define SAFE_DELETE( p ) { if( p ) { delete p; p = 0; }  }
#define SAFE_DELETE_ARRAY( p ) { if( p ) { delete[] p; p = 0; }  }
#define SAFE_RELEASE( p ) { if( p ) { ( p )->Release(); p = 0; }  }

struct GenericPlatformTypes
{
	// Unsigned base types.
	typedef unsigned char 		uint8;		// 8-bit  unsigned.
	typedef unsigned short int	uint16;		// 16-bit unsigned.
	typedef unsigned int		uint32;		// 32-bit unsigned.
	typedef unsigned long long	uint64;		// 64-bit unsigned.

											// Signed base types.
	typedef	signed char			int8;		// 8-bit  signed.
	typedef signed short int	int16;		// 16-bit signed.
	typedef signed int	 		int32;		// 32-bit signed.
	typedef signed long long	int64;		// 64-bit signed.

	typedef unsigned char		byte;		///< byte
};

typedef GenericPlatformTypes PlatformTypes;

typedef PlatformTypes::uint8		uint8;		///< An 8-bit unsigned integer.
typedef PlatformTypes::uint16		uint16;		///< A 16-bit unsigned integer.
typedef PlatformTypes::uint32		uint32;		///< A 32-bit unsigned integer.
typedef PlatformTypes::uint64		uint64;		///< A 64-bit unsigned integer.

												// Signed base types.
typedef	PlatformTypes::int8			int8;		///< An 8-bit signed integer.
typedef PlatformTypes::int16		int16;		///< A 16-bit signed integer.
typedef PlatformTypes::int32		int32;		///< A 32-bit signed integer.
typedef PlatformTypes::int64		int64;		///< A 64-bit signed integer.

typedef PlatformTypes::byte			byte;
