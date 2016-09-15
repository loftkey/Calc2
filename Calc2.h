/*
/////////////////////////////////////////////////////////////////////////////////////////////////

START DATE: 09/11/2016
DESCRIPTION: Calc2 is a calculator with functions for equations

/////////////////////////////////////////////////////////////////////////////////////////////////
	CHANGE LOG:

		[*]	09/11/2016 | 0.1.0:
				ADDITIONS:
					-Added CalcMenu UI
					-Added infix to rpn parsing function solve(string)
					-Added input validity function and isFunction function
				CHANGES: N/A
				TO-DO: 
					-Add RPN function

		[*]	09/12/2016 | 0.1.1:
				ADDITIONS:
					-Added RPN solver
					-Added Precedence Function
					-Added F001 Quadratic Formula functions
					-Added constructor and overloaded construuctor
					-Added infix to rpn function solve(string)
					-Added menu string, formula list string, and radian bool
					-Added PI constant
				CHANGES:
					-Fixed Precedence function
					-Fixed parentheses pushing on to stack
				TO-DO:
					-Add more formulas

		[*]	09/13/2016 | 0.1.2:
				ADDITIONS:
					-Added F002 Pathagorean formula
					-Added Error messages
				CHANGES:
					-Fixed cin << and getline skipping
				TO-DO:
					-Add distance, slope, slope curve, quotient, power rule, trig identities,complete the square (Idk if that's a formula), u sub, integration by parts, factoring, commutative law and all those other basic onesSAS, ASS, ASA. Finding angle/side of triangles, basic derivativeand integration formulas.
					-Add pi, e and other constants to calculator functionality
					-Add info option in menu
					-Change menu from switch statment to if else statement
					-Figure out how to implement pointers for effeciency


		[*]	09/13/2016 | 0.1.3:
				ADDITIONS:
					-Added info to class and menu
					-Added distance formula
				CHANGES:
					-Changed menu from switch statment to if else statement
				TO-DO:
					-Add left/right arrow shift through answers
					-Fix cin << and getline adding on functions
					-Add slope, slope curve, quotient, power rule, trig identities,complete the square (Idk if that's a formula), u sub, integration by parts, factoring, commutative law and all those other basic onesSAS, ASS, ASA. Finding angle/side of triangles, basic derivativeand integration formulas.


*/

#ifndef CALC2
#define CALC2

#include <string>
#include <math.h>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <sstream>
using std::string;
using std::vector;
using std::queue;

class Calc2
{
private:
	const string	menu = "[-----------------------------------------------------]\n[------------------- Calc v0.1 Key -------------------]\n[-----------------------------------------------------]\n[---> R - Toggle Radians/Degrees \n[---> F - Formula List\n[---> L - Clear \n[---> I - Info\n[---> E - Exit \n[-----------------------------------------------------]\n[----- To use Type out problem in infix notation -----]\n[------- or in Riggy type '-calc ' followed by -------] \n[--------- an above command or infix problem ---------]\n[-----------------------------------------------------]";
	const string	formulaList = "\n[---> F00 - Quadratic Formula\n[---> F01 - Pythagorean Theorem\n[---> F02 - Distance Formula";
	const string	info = "\nCreated By: Ody\nFor support: beta.beam.lab@gmail.com\ninput not case-sensitive\nBuild 0.1.3b\n";
	bool			radians;
	bool			valid(char c);
	bool			isPrecedence(char, char);
	string			isFunc(string);
	string			solveRPN(queue<string> outQueue);

//----------------------- Formulas ----------------------------------------
	void			F00quadratic(double a, double b, double c);
	void			F01pythagorean(double x, double y, char missing);
	void			F02distance(double x1, double y1, double x2, double y2);
//-------------------------------------------------------------------------

public:
	const double	PI = 3.1415926535897932384626433832795;
	Calc2::Calc2();
	Calc2::Calc2(bool);
	void			CalcMenu();
	void			solve(string);
	
//----------------------- Formulas ----------------------------------------
	void			F00quadratic();
	void			F01pythagorean();
	void			F02distance();
//-------------------------------------------------------------------------
};

#endif CALC2