#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>

using namespace std;

template <typename TN> class SafeParameters
{
	public:
		static const TN		ABSMIN	= numeric_limits<TN>::min();
		static const TN		ABSMAX 	= numeric_limits<TN>::max();
		TN 					min; 		//Minimum Safe Value
		TN 					max; 		//Maximum Safe Value
		TN 					overage; 	//Value to store overage in
		
		SafeParameters( TN thismin = ABSMIN, TN thismax = ABSMAX )
		{
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
};


//static uint8_t zero = 0;

template <typename TN> TN safeAdd_base( TN addend_left, TN addend_right, SafeParameters<TN> &params )
{
	/*
		Safely adds two unsigned integer types
		This is the full, four parameter base version called by all other functions here
		Inputs:
			addend_left, addend_right - integers to be added
			maxval (optional) - the maximum value which the sum cannot exceed
								if maxval is not provided, uses UINT#_MAX based on precision
		
		Outputs (by reference):
			overage - if a variable is provided, passes the value over maxval to that variable
		
		Output:
			sum - sum of addend_left and addend_right, limited by maxval
	*/
	
	TN sum;
	TN margin;
	
	margin = params.max - addend_right;
	
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
	SafeParameters<TN> params;
	
	// calls main safeAdd with default max and overage pointing to null
	return safeAdd_base<TN>( addend_left, addend_right, params );
}

template <typename TN> TN safeAdd_max( TN addend_left, TN addend_right, TN maxval )
{
	SafeParameters<TN> 	params( SafeParameters<TN>::ABSMIN, maxval );
	
	// calls main safeAdd with passed max and overage point to null
	return safeAdd_base<TN>( addend_left, addend_right, params );
}

template <typename TN> TN safeAdd_min( TN addend_left, TN addend_right, TN minval )
{
	// Calls base safeadd using SafeParameters 
	// Any overage will be passed to (unused) member "outage"
	SafeParameters<TN> 	params( minval );
	TN sum = safeAdd_base<TN>( addend_left, addend_right, params );
	
	if ( sum.overage > 0 )
	{
		cout << "Warning: Overage Detected and not passed to result" << endl;
	}
	
	return sum;
}

template <typename TN> TN safeAdd( TN addend_left, TN addend_right, TN &overage, TN minval, TN maxval )
{
	
	SafeParameters<TN>	params( minval, maxval );
	TN sum;
	
	//Set overage pointer to same address
	&params.overage = &overage;
	
	sum = safeAdd_base( addend_left, addend_right, params );
	
	return sum;
}