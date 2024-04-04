#include <iostream>

//Need to add:
//Pointer to Class to non-pointer member
//Pointer to Class to pointer member
//Non-Pointer Class to pointer member

using namespace std;

int main ()
{
	//This program is simply to demonstrate pointers and attempt to make them less confusing
	//* - this is the unary dereference operator - it will take a pointer and return the value stored
	//& - this is the unary address operator - it will take a variable and return the address it is stored in
	
	//Defining and assigning basic test variable, var
	//<modifiers><typename>variablename = value;
	//When the program is executed, the variable will be assigned an address
	//The value will be stored in the address in a format based on the typename and modifiers
	//In a deterministic system (properly coded RTOS or on rails), the variables will always be assigned the same address
	unsigned int var = 1000;

	//Defining variable to hold address, avar
	//<modifiers><typename>* variablename = address
	//Using assignment operator to set the address to the same as var
	//Note that everything after <typename> is considered that type
	//So *avar is of <unsigned int> type in this example
	//avar without a unary operator is the pointer and will return the address
	//Dereferencing avar with * returns the value at the address
	//You should also get the address the avar variable / pointer / address is stored in with &avar
	unsigned int* avar = &var;

	//var returns the actual value of 1000
	cout << var << endl;
	
	//&var returns the address that var is stored at
	cout << &var << endl;
	
	//*avar returns the value at the address pointed to by avar
	//thus also returns the actual value of 1000
	cout << *avar << endl;
	
	//avar returns the address that var is stored at
	cout << avar << endl;
	
	//&avar woudl then return the address that avar itself is at
	cout << &avar << endl;

	return 0;

}