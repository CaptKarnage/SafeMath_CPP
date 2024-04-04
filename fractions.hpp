//#include <stdint.h>
//#include <stdio.h>
//#include <string.h> //string.h reqiures dynamic memory allocation - MISRA nono
#include <cstring>
#include "safemath.hpp"  //since stdint and stdio are in safemath, they don't need to be included again?
//#include "safetext.hpp"

using namespace std; //only needed for string.h, can remove?

const size_t	mixedmultiplier 	= 3; //Pattern repeats 3 times for mixed fractions
const size_t	impropermultiplier 	= 2; //Pattern repeats 2 times for improper fractions
const size_t	mixedadder 			= 2; //Add 1 for space, 1 for "/"
const size_t	improperadder		= 1; //Add 1 for "/"
const size_t	size_format[4]		= {3, 2, 3, 4};
//const size_t	size_format16		= 2;
//const size_t	size_format32		= 3;
//const size_t	size_format64		= 4;


template <typename TN> class Fraction
{
	private:
		TN 				numerator;
		TN 				denominator;
		bool 			negative;
		const size_t	uSize = sizeof(TN);				//Number of bytes in format
		const size_t	uFormatSize = size_format[uSize];
		const size_t	precision = CHAR_BIT * uSize;
	
	public:
		
		Fraction( TN num, TN denom, bool neg = false ) 
		{
			
			numerator 	= num;
			denominator = denom;
			negative 	= neg;
			
		}
		
		char* asString(bool mixed = false)
		{
			const char		sDiv[1] 	= {'/'};
			char			sNeg[1] 	= {' '};
			
			//Get static sizes for numerator & denominator "Strings"
			size_t 			uNum_len	= log10(numerator);
			size_t  		uDenom_len	= log10(denominator);
			
			size_t			uTotal_len	= 0;
			size_t			uFormat_len	= 0;
					
			if ( negative )
			{
				sNeg[1] = '-';
			}
			
			char sFormu[uFormatSize];

			/*
			#if precision == 8
				
			#elif precision == 16
			
			#elif precision == 32
			
			#elif precision == 64
			
			#else
				
			#endif
			*/
			
			switch (precision)
			{
				case 8:
					strncpy( sFormu, "%hu", uSize );
					break;
					
				case 16:
					strncpy( sFormu, "%u", uSize );
					break;
					
				case 32:
					strncpy( sFormu, "%lu", uSize );
					break;
					
				case 64:
					strncpy( sFormu, "%llu", uSize );
					break;
			}
			
			//Note that snprintf handles "Strings" (upper S) which are actually character arrays
			//actual "strings" (lower s) will create strange characters
			
			uTotal_len 	= uNum_len + uDenom_len + size(sDiv) + size(sNeg) + 1; //1 for final null character
			char sOut [uTotal_len];
			
			
			if (mixed && ( numerator > denominator ) )
			{
				//Format as mixed fraction
				uFormat_len = ( ( mixedmultiplier * uFormatSize ) + mixedadder );
				char sFormat [uFormat_len];
				snprintf( sFormat, uFormat_len, "%s %s%s%s", sFormu, sFormu, sDiv, sFormu );
				cout << sFormat << endl;
				snprintf( sOut, uTotal_len, sFormat, whole(), remainder(), denominator );
			}
			else
			{
				//Default format / format as improper fraction
				uFormat_len = ( ( impropermultiplier * uFormatSize ) + improperadder );
				char sFormat [uFormat_len];
				snprintf( sFormat, uFormat_len, "%s%s%s", sFormu, sDiv, sFormu );
				cout << sFormat << endl;
				snprintf( sOut, uTotal_len, sFormat, numerator, denominator );
			}
			
			return sOut;
			
		}
		
		TN whole()
		{
			return ( numerator / denominator );
		}
		
		TN remainder()
		{
			return ( numerator % denominator );
		}
		
		double asDouble()
		{
			double	dOut;
			dOut = ( static_cast<double>(numerator) / static_cast<double>(denominator) );
			return dOut;
		}
		
};