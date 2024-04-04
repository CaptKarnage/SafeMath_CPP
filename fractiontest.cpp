//#include <stdint.h>
//#include <stdio.h>
//#include <string.h>
#include <iostream> //This is for testing / debug only needs to be removed in final
//#include "safemath.hpp"
#include "fractions.hpp"

using namespace std;

int main() {
	
	//Set up all the test variables
	uint8_t		n8 		= 201;
	uint8_t		d8		= 100;
	uint8_t		o8		= 0;
	uint8_t		mn8		= 10;
	uint8_t		mx8		= 100;
	
	uint16_t	n16		= 60001;
	uint16_t	d16		= 6000;
	uint16_t	o16		= 0;
	uint16_t	mn16	= 1000;
	uint16_t	mx16	= 10000;
	
	uint32_t	n32		= 4000000001;
	uint32_t	d32		= 400000000;
	uint32_t	o32		= 0;
	uint32_t	mn32	= 1000000;
	uint32_t	mx32	= 1000000000;
	
	uint64_t	n64 	= 18000000000000000001;
	uint64_t	d64 	= 500000000000000000;
	uint64_t	o64 	= 0;
	uint64_t	mn64	= 1000000000;
	uint64_t	mx64	= 5000000000000000000;
	
	//Test fraction constructors
	Fraction	f8( n8, d8 );
	Fraction	f16( n16, d16 );
	Fraction	f32( n32, d32 );
	Fraction	f64( n64, d64 );

	//Test safeAdd_quick function (default min/max, no overage tracking)
	//These should all generate warnings since overages would occur
	uint8_t		s8 	= safeAdd_quick<uint8_t>( n8, d8 );
	uint16_t	s16 = safeAdd_quick<uint16_t>( n16, d16 );
	uint32_t	s32 = safeAdd_quick<uint32_t>( n32, d32 );
	uint64_t	s64 = safeAdd_quick<uint64_t>( n64, d64 );

	cout	<< s8  	<< endl; //Outputs as char... because uint8_t doesn't really exist as an unsigned integer type
	cout 	<< s16 	<< endl;
	cout 	<< s32 	<< endl;
	cout 	<< s64 	<< endl;
	cout 	<< endl;

	//Test safeAdd_min function (custom min/default max, no overage tracking)
	s8	= safeAdd_min<uint8_t>( n8, d8, mn8 );
	s16 = safeAdd_min<uint16_t>( n16, d16, mn16 );
	s32 = safeAdd_min<uint32_t>( n32, d32, mn32 );
	s64 = safeAdd_min<uint64_t>( n64, d64, mn64 );
	
	cout	<< s8  	<< endl; //Outputs as char... because uint8_t doesn't really exist as an unsigned integer type
	cout 	<< s16 	<< endl;
	cout 	<< s32 	<< endl;
	cout 	<< s64 	<< endl;
	cout 	<< endl;

	//Test safeAdd_max function (default min/cutom max, no overage tracking)
	s8	= safeAdd_max<uint8_t>( n8, d8, mx8 );
	s16 = safeAdd_max<uint16_t>( n16, d16, mx16 );
	s32 = safeAdd_max<uint32_t>( n32, d32, mx32 );
	s64 = safeAdd_max<uint64_t>( n64, d64, mx64 );
	
	cout	<< s8  	<< endl; //Outputs as char... because uint8_t doesn't really exist as an unsigned integer type
	cout 	<< s16 	<< endl;
	cout 	<< s32 	<< endl;
	cout 	<< s64 	<< endl;
	cout 	<< endl;
	
	//Test safeAdd_over function (default min/max, returns overage)
	s8	= safeAdd_over<uint8_t>( n8, d8, o8 );
	s16 = safeAdd_over<uint16_t>( n16, d16, o16 );
	s32 = safeAdd_over<uint32_t>( n32, d32, o32 );
	s64 = safeAdd_over<uint64_t>( n64, d64, o64 );
	
	cout	<< s8	<< " with overage of: "	<< o8 	<< endl;
	cout 	<< s16 	<< " with overage of: " << o16 	<< endl;
	cout 	<< s32 	<< " with overage of: " << o32 	<< endl;
	cout 	<< s64 	<< " with overage of: " << o64 	<< endl;
	cout	<< endl;
	
	//Test safeAdd function (custom min/max, returns overage)
	s8	= safeAdd<uint8_t>( n8, d8, o8, mn8, mx8 );
	s16 = safeAdd<uint16_t>( n16, d16, o16, mn16, mx16 );
	s32 = safeAdd<uint32_t>( n32, d32, o32, mn32, mx32 );
	s64 = safeAdd<uint64_t>( n64, d64, o64, mn64, mx64 );
	
	cout	<< s8	<< " with overage of: "	<< o8 	<< endl;
	cout 	<< s16 	<< " with overage of: " << o16 	<< endl;
	cout 	<< s32 	<< " with overage of: " << o32 	<< endl;
	cout 	<< s64 	<< " with overage of: " << o64 	<< endl;
	cout	<< endl;
	
	//Test asDouble method
	cout	<< f8.asDouble()	<< endl;
	cout 	<< f16.asDouble() 	<< endl;
	cout 	<< f32.asDouble() 	<< endl;
	cout 	<< f64.asDouble() 	<< endl;
	
	//Test asString method
	/*
	cout << f8.asString()  << endl;
	cout << f16.asString() << endl;
	cout << f32.asString() << endl;
	cout << f64.asString() << endl;
	cout << endl;
	*/
	
	return 0;
	
}