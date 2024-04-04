//#include <stdint.h>
//#include <stdio.h>
//#include <string.h>
#include <iostream> //This is for testing / debug only needs to be removed in final
//#include "safemath.hpp"
#include "fractions.hpp"

using namespace std;

int main() {
	
	//Set up all the test variables
	uint8_t		n8 	= 201;
	uint8_t		d8 	= 100;
	uint16_t	n16	= 60001;
	uint16_t	d16 = 6000;
	uint32_t	n32 = 4000000001;
	uint32_t	d32 = 400000000;
	uint64_t	n64 = 18000000000000000001;
	uint64_t	d64 = 500000000000000000;
	
	//Test fraction constructors
	Fraction	f8( n8, d8 );
	Fraction	f16( n16, d16 );
	Fraction	f32( n32, d32 );
	Fraction	f64( n64, d64 );

	//Test safeAdd function
	uint8_t		s8 	= safeAdd_quick<uint8_t>( n8, d8 );
	uint16_t	s16 = safeAdd_quick<uint16_t>( n16, d16 );
	uint32_t	s32 = safeAdd_quick<uint32_t>( n32, d32 );
	uint64_t	s64 = safeAdd_quick<uint64_t>( n64, d64 );

	cout << s8  << endl; //Outputs as char... because uint8_t doesn't really exist as an unsigned integer type
	cout << s16 << endl;
	cout << s32 << endl;
	cout << s64 << endl;
	cout << endl;
	
	//Test asDouble method
	cout << f8.asDouble() << endl;
	cout << f16.asDouble() << endl;
	cout << f32.asDouble() << endl;
	cout << f64.asDouble() << endl;
	
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