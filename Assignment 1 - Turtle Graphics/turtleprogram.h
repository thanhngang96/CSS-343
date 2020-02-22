/**
 * turtleprogram.h file documentation
 *
 * @author Nathan Ngo
 * @date 01/17/2020
 */

#ifndef TURTLEPROGRAM_H
#define TURTLEPROGRAM_H
#include <iostream>
#include <string>

using namespace std;

class TurtleProgram {
	//Operator << overloading
	friend ostream &operator<<(ostream &Out, const TurtleProgram &Tp);

public:	
	//Default constructors
	TurtleProgram();
	//Constructor with one parameter
	explicit TurtleProgram(const string &Command);
	//Constructor with two parameters
	TurtleProgram(const string &Command, const string &Times);
	//Copy constructor
	TurtleProgram(const TurtleProgram &Tp); 
	//Destructor
	virtual ~TurtleProgram(); 
	//Getters & setters
	int getLength() const;  
	string getIndex(const int &I) const;  
	void setIndex(const int &I, const string &Str);
	//Operator overloading
	bool operator==(const TurtleProgram &Rhs) const;
	bool operator!=(const TurtleProgram &Rhs) const;	
	TurtleProgram &operator=(const TurtleProgram &Rhs);
	TurtleProgram operator+(const TurtleProgram &Tp) const;
	TurtleProgram &operator+=(const TurtleProgram &Tp);
	TurtleProgram operator*(const int &Times) const;
	TurtleProgram &operator*=(const int &Times);
private:
	string* Instructions;
	int InstrLength;
};

#endif // TURTLEPROGRAM_H
