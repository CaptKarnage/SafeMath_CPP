#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>

using namespace std;

template <typename TN> class SafeParameters
{
	public:
		//ABSMIN and ABSMAX are static values, always the same for a given TypeName, TN
		//Using standard libary numeric_limits for the type
		static const TN		ABSMIN	= numeric_limits<TN>::min();
		static const TN		ABSMAX 	= numeric_limits<TN>::max();
		
		//Defaults set here are so even new SafeParameters statment has values assigned
		TN 					min		= ABSMIN; 		//Minimum Safe Value
		TN 					max		= ABSMAX; 		//Maximum Safe Value
		
		//This is a placeholder intended to be overwritten with the overage result of the operation
		//Initialized to 0 - assume no overage unless one is calculated
		TN 					overage = 0;
		
		SafeParameters( TN thismin = ABSMIN, TN thismax = ABSMAX )
		{
			//Contructor: if parameters not passed, default min is ABSMIN, default max is ABSMAX
			//Initial check insures that max > min
			if ( thismax >= thismin )
			{
				min = thismin;
				max = thismax;
			}
			else
			{
				min = thismax;
				max = thismin;
			}
			
			//Set an initial value
			
			overage = 0;
		}
		
		bool isValid()
		{
			//Checks all applicable conditions to make sure the parameters are valid
			bool valid = ( max >= min );
			
			return valid;
		}
		
		bool checkValue( TN value )
		{
			//Checks if passed value is valid given the parameters
			bool valid = ( isValid && ( value >= min ) && ( value <= max ) );
			
			return valid;
		}
		
};


//static uint8_t zero = 0;

template <typename TN> TN safeAdd_base( TN addend_left, TN addend_right, SafeParameters<TN> &params )
{
	/*
		Safely adds two unsigned integer types
		This is the full, four parameter base version called by all other functions here
		Inputs:
			addend_left, addend_right - integers to be added
			parms - SafeParameters set decribing min / max of variables and provides member overage to store any overages in
		
		Output:
			sum - sum of addend_left and addend_right, limited by maxval
	*/
	
	TN sum;
	TN margin = ( params.max - addend_right );
	
	if ( margin > addend_left )
	{
		//Will not exceed maximum, no overage, add as normal
		sum = addend_left + addend_right;
		params.overage = 0;
		
	}
	else
	{
		//Exceeds maximum, sum is maximum, calculate overage
		sum = params.max;
		params.overage = addend_left - margin;
		
	}
	
	return 	sum;
	
}

template <typename TN> TN safeAdd_quick( TN addend_left, TN addend_right )
{
	//Adds two numbers using built-in min & max based on TN
	// Calls base safeadd using SafeParameters 
	// Any overage will be passed to (unused) member "overage"
	SafeParameters<TN> params;
	TN sum = safeAdd_base<TN>( addend_left, addend_right, params );
	
	if ( params.overage != 0 )
	{
		cout << "Warning: Overage Detected and not passed to result" << endl;
	}
	
	return sum;
}

template <typename TN> TN safeAdd_max( TN addend_left, TN addend_right, TN maxval )
{
	//Adds two numbers using built-in min based on TN and user provided maxval
	// Calls base safeadd using SafeParameters 
	// Any overage will be passed to (unused) member "overage"
	SafeParameters<TN> 	params( SafeParameters<TN>::ABSMIN, maxval );
	TN sum = safeAdd_base<TN>( addend_left, addend_right, params );
	
	if ( params.overage != 0 )
	{
		cout << "Warning: Overage Detected and not passed to result" << endl;
	}
	
	return sum;
}

template <typename TN> TN safeAdd_min( TN addend_left, TN addend_right, TN minval )
{
	//Adds two numbers using built-in max based on TN and user provided minval
	// Calls base safeadd using SafeParameters 
	// Any overage will be passed to (unused) member "overage"
	SafeParameters<TN> 	params( minval );
	TN sum = safeAdd_base<TN>( addend_left, addend_right, params );
	
	if ( params.overage != 0 )
	{
		cout << "Warning: Overage Detected and not passed to result" << endl;
	}
	
	return sum;
}

template <typename TN> TN safeAdd_over( TN addend_left, TN addend_right, TN &overage )
{
	//Adds two numbers using built-in min & max based on TN
	// Calls base safeadd using SafeParameters 
	// Any overage will be passed to member "overage" which will be passed to ref overage
	SafeParameters<TN> 	params;
	TN sum = safeAdd_base<TN>( addend_left, addend_right, params );
	
	//pass overage back to calling function
	overage = params.overage;
	
	return sum;
}

template <typename TN> TN safeAdd( TN addend_left, TN addend_right, TN &overage, TN minval, TN maxval )
{
	
	SafeParameters<TN>	params( minval, maxval );
	
	//Set overage pointer to same address - better efficiency?
	//&params.overage = &overage;
	
	TN sum = safeAdd_base( addend_left, addend_right, params );
	
	//pass overage back to calling function
	overage = params.overage;
	
	return sum;
}