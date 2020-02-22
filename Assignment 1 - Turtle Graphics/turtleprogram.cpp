/**
 * turtleprogram.h file documentation
 *
 * @author Nathan Ngo
 * @date 01/17/2020
 */

#include "turtleprogram.h"
#include <cassert>

//--------------------------------------------------------------------------
//Default constructor
TurtleProgram::TurtleProgram() 
{
	Instructions = nullptr;
	InstrLength = 0;
}

//--------------------------------------------------------------------------
//Constructor with one parameter
TurtleProgram::TurtleProgram(const string &Command) 
{
	InstrLength = 1;
	Instructions = new string[InstrLength];
	Instructions[0] = Command;
	
}

//--------------------------------------------------------------------------
//Constructor with two parameters
TurtleProgram::TurtleProgram(const string &Command, const string &Times) 
{
	InstrLength = 2;
	Instructions = new string[InstrLength];
	Instructions[0] = Command;
	Instructions[1] = Times;
	
}

//--------------------------------------------------------------------------
//Copy constructor
TurtleProgram::TurtleProgram(const TurtleProgram &Tp)
{
	//initializes a new set of instructions which is the same as Tp
	InstrLength = Tp.getLength();
	if (InstrLength > 0)
	{
		Instructions = new string[Tp.getLength()];
	}
	else
	{
		Instructions = nullptr;
	}
	//assign data to the new instruction;
	for (int I = 0; I < InstrLength; I++)
	{
		Instructions[I] = Tp.getIndex(I);
	}
}

//--------------------------------------------------------------------------
//getLength()
//Get the length of the object
int TurtleProgram::getLength() const
{
	return InstrLength;
}

//--------------------------------------------------------------------------
//getIndex()
//Get the string of an array given its index
string TurtleProgram::getIndex(const int &I) const
{
	if (I >= 0 && I < this->InstrLength)
	{
		return Instructions[I];
	}
	return nullptr;
}

//--------------------------------------------------------------------------
//setIndex()
//Change the string of an array given its index and the string
void TurtleProgram::setIndex(const int &I, const string &Str)
{
	if (I >= 0 && I <	InstrLength)
	{
		Instructions[I] = Str;
	}
	return;
}

//--------------------------------------------------------------------------
//Operator != overloading
//Overloaded != operator for comparing two class Array
bool TurtleProgram::operator!=(const TurtleProgram &Rhs) const 
{
	//checks if the length of two string is not equal
	if (this->getLength() != Rhs.getLength())
	{
		return true;
	}
	//goes through the array and compares each element
	for (int I = 0; I < Rhs.getLength(); I++)
	{
		if (this->getIndex(I) != Rhs.getIndex(I))
		{
			return true;
		}
	}
	return false;

}

//--------------------------------------------------------------------------
//Operator == overloading
//Overloaded == operator for comparing two class Array
bool TurtleProgram::operator==(const TurtleProgram &Rhs) const
{
	//checks if the length of two string is equal
	if (this->getLength() != Rhs.getLength())
	{
		return false;
	}
	//goes through the array and compares each element
	for (int I = 0; I < this->getLength(); I++)
	{			
		if (this->Instructions[I].compare(Rhs.Instructions[I]) != 0)
		//if (this->getIndex(I) != Rhs.getIndex(I))
		{
			return false;
		}
	}
	return true;
	
}

//--------------------------------------------------------------------------
//Operator+ overloading
//Overloaded + operator for any class Array
TurtleProgram TurtleProgram::operator+(const TurtleProgram &Tp) const 
{	
	//checks if the right hand side object is empty
	if (Tp.getLength() == 0)
	{
		return *this;
	}
	//creates a new string array.
	TurtleProgram Bigger;
	int TotalLength = this->getLength() + Tp.getLength();	
	Bigger.Instructions = new string[TotalLength];
	//sets the length of the new array.
	Bigger.InstrLength = TotalLength;
	//assigns data from the left hand side array to the new array.
	for (int I = 0; I < getLength(); I++)
	{
		Bigger.setIndex(I, this->getIndex(I));
	}
	//assigns data from the right hand side array to the new array.
	for (int I = 0; I < Tp.getLength(); I++)
	{
		Bigger.setIndex(this->getLength() + I, Tp.getIndex(I));
	}
	return Bigger;
}

//--------------------------------------------------------------------------
//Operator+= overloading
//Overloaded += operator for any class Array
TurtleProgram &TurtleProgram::operator+=(const TurtleProgram &Tp) 
{
	//check if the right hand side object is empty
	if (Tp.getLength() == 0)
	{
		assert(Tp.getLength() >= 0 && "Tp length must be >= 0");
		return *this;
	}
	int TotalLength = this->getLength() + Tp.getLength();
	auto TempInstructions = new string[TotalLength];
	int TempLength = this->getLength();
	//assigns data from the left hand side array to the new array.
	for (int I = 0; I < this->getLength(); I++)
	{
		TempInstructions[I] = this->Instructions[I];
	}
	//assigns data from the right hand side array to the new array.
	for (int I = 0; I < Tp.getLength(); I++)
	{
		TempInstructions[TempLength] = Tp.Instructions[I];
		TempLength++;
	}		this->InstrLength += Tp.getLength();
	//deletes the old array
	delete[] Instructions;
	//assigns to the new array
	this->Instructions = TempInstructions;
	return *this;
}

//--------------------------------------------------------------------------
//Operator* overloading
//Overloaded * operator for any class Array
TurtleProgram TurtleProgram::operator*(const int &Times) const
{
	assert(Times > 0 && "Times a positive number");
	//creates a new string array.
	TurtleProgram Bigger;
	Bigger.InstrLength = this->getLength()*Times;
	Bigger.Instructions = new string[Bigger.InstrLength];

	//goes through the array and assigns data to each element.
	for (int I = 0; I < Bigger.InstrLength; I++)
	{
		//sets the new data by assigning the array  
		//alternately between original indexes
		Bigger.Instructions[I] = this->Instructions[I % this->getLength()];
	}
	return Bigger;
}
//--------------------------------------------------------------------------
//Operator*= overloading
//Overloaded *= operator for any class Array
TurtleProgram &TurtleProgram::operator*=(const int &Times)
{
	//checks if Times is a valid number
	if (Times <= 0)
	{
		assert(Times >= 0 && "Times a positive number");
		return *this;
	}
	//creates a new string array.
	int TempLength = this->getLength()* Times;
	auto TempInstructions = new string[TempLength];

	//goes through the array and assigns data to each element.
	for (int I = 0; I < TempLength; I++)
	{
		//sets the new data by assigning the array  
		//alternately between original indexes
		TempInstructions[I] = this->Instructions[I % this->getLength()];
	}
	this->InstrLength = TempLength;
	//deletes the old array
	delete[] Instructions;
	//assigns to the new array
	this->Instructions = TempInstructions;
	return *this;
}
//--------------------------------------------------------------------------
//Assignment operator overloading
//Overloaded operator= to make deep copy
TurtleProgram &TurtleProgram::operator=(const TurtleProgram &Rhs) 
{ 
	if (*this != Rhs)
	{
		//deletes the array
		delete[] Instructions;
		//assigns new length
		this->InstrLength = Rhs.getLength();
		//creates a new array with the new length
		this->Instructions = new string[this->InstrLength];
		//goes through the array and assigns new element
		for (int I = 0; I < this->InstrLength; I++)
		{
			this->Instructions[I] = Rhs.Instructions[I];
		}
		return *this;
	}
	return *this;
}
//--------------------------------------------------------------------------
//Destructor
//Release the memory before the class instance is destroyed
TurtleProgram::~TurtleProgram() 
{
	delete[] Instructions;
}

// --------------------------------------------------------------------------
// Operator<<
// Overloaded output operator for class Array
ostream &operator<<(ostream &Out, const TurtleProgram &Tp) 
{
	Out << "[";
	for (int I = 0; I < Tp.getLength(); I++)
	{
		Out << Tp.Instructions[I];
		//check for the last Instruction.
		if (I + 1 < Tp.getLength())
		{
			Out << " ";
		}
	}
	Out << "]";
	return Out;              
}
