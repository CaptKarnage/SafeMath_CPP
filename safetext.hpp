template <typename TN> size_t numDigits(TN number)
{
    size_t digits = 0;
    if (number < 0) 
	{
		digits = 1; // remove this line if '-' counts as a digit
	}
	
    while ( number > 0 ) {
        number /= 10;
        digits++;
    }
	
    return digits;
}

class Text
{
	
	private:
		const size_t	numchars;
		char			text[];
	
	public:
		Text( char const text_array[], size_t n ): 
			numchars(n)	//Member Initializer List
			
		{
			
			
		}
}