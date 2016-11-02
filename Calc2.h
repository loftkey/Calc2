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


		[*]	09/14/2016 | 0.1.3:
				ADDITIONS:
					-Added info to class and menu
					-Added distance formula
				CHANGES:
					-Changed menu from switch statment to if else statement
				TO-DO:
					-Add left/right arrow shift through answers
					-Fix cin << and getline adding on functions
					-Add slope, slope curve, quotient, power rule, trig identities,complete the square (Idk if that's a formula), u sub, integration by parts, factoring, commutative law and all those other basic onesSAS, ASS, ASA. Finding angle/side of triangles, basic derivativeand integration formulas.

		[*]	09/15/2016 | 0.1.4:
				ADDITIONS:
					-Added slope formula
					-Added ErrorList to info
				CHANGES:
					-Fixed cin << and getline adding on functions
				TO-DO:
					-Add Error handling for incorrect input on functions!! maybe add infix ->rpn->num fuunctionality
					-Add left/right arrow shift through answers
					-Add slope curve, quotient, power rule, trig identities,complete the square (Idk if that's a formula), u sub, integration by parts, factoring, commutative law and all those other basic onesSAS, ASS, ASA. Finding angle/side of triangles, basic derivativeand integration formulas.
					-Add decimal point acception
					-Add negative number acception
					-Add pi and other constants

		[*]	09/17/2016 | 0.1.5:
				ADDITIONS:
					-Added support for decimal numbers
					-Added support for negative numbers
				CHANGES:
					
				TO-DO:
					-Add Error handling for incorrect input on functions!! maybe add infix ->rpn->num fuunctionality
					-Add left/right arrow shift through answers
					-Add slope curve, quotient, power rule, trig identities,complete the square (Idk if that's a formula), u sub, integration by parts, factoring, commutative law and all those other basic onesSAS, ASS, ASA. Finding angle/side of triangles, basic derivativeand integration formulas.
					-Add support for pi and other constants
					-Add % support

		[*]	11/01/2016 | 0.1.6:
				ADDITIONS:
					-Added distance formula for 3D
					-Added SI Prefix list
					-Added constant list still needs more
				CHANGES:
					- Fixed missmatch parenthesis infinite loop
				TO-DO:
					-Add Error handling for incorrect input on functions!! maybe add infix ->rpn->num fuunctionality
					-Add left/right arrow shift through answers
					-Add slope curve, quotient, trig identities,complete the square (Idk if that's a formula), factoring, commutative law and all those other basic onesSAS, ASS, ASA. Finding angle/side of triangles, basic derivativeand integration formulas.
					-Add support for pi and other constants
					-Add % support
					-Fix constant list formating
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
	const string	menu = "[-----------------------------------------------------]\n[------------------- Calc v0.1 Key -------------------]\n[-----------------------------------------------------]\n[---> R - Toggle Radians/Degrees \n[---> F - Formula List\n[---> Const - Constants List\n[---> P - SI Prefix Table \n[---> L - Clear \n[---> I - Info (please read if you have an Error)\n[---> E - Exit \n[-----------------------------------------------------]\n[----- To use Type out problem in infix notation -----]\n[------- or in Riggy type '-calc ' followed by -------] \n[--------- an above command or infix problem ---------]\n[-----------------------------------------------------]";
	const string	formulaList = "\n[---> F00 - Quadratic Formula\n[---> F01 - Pythagorean Theorem\n[---> F02 - Distance Formula 2D\n[---> F03 - Distance Formula 3D\n[---> F04 - Slope Formula";
	const string	info = "\nCreated By: Ody\nFor support: beta.beam.lab@gmail.com\ninput not case-sensitive\nFormulas Do not support Fractions\nDecimals supported\nTo input negative number surround it with parenthesis example: 2 * (-12) or (-(60 + 2 - sin(30)))\nBuild 0.1.5b\n\nError List\nError: 000 INVALID INPUT\nError: 001 MISSIMATCHED PERENTHESES\nError: 002 nums size != 1 ------------ (this means there where left over numbers on stack or no numbers at all ie not enough opperators)\nError: 003 outQueue size != 0 -------- (This means not all items on queue made it to the stack ie too many opperators\nError: 004 Imaginary number ---------- (This means that the answer was imaginary ie square root of a negative number)";
	const string	prefixes = "\nFactor 		Name 		Symbol		Value\n10^24		yotta		Y		1 000 000 000 000 000 000 000 000\n10^21		zetta		Z		1 000 000 000 000 000 000 000\n10^18		exa		E		1 000 000 000 000 000 000\n10^15		peta		P		1 000 000 000 000 000\n10^12		tera		T		1 000 000 000 000\n10^9		giga		G		1 000 000 000\n10^6		mega		M		1 000 000\n10^3		kilo		k		1 000\n10^2		hecto		h		1 00\n10^1		deka		da 		10\n10^-1		deci		d		0.1\n10^-2		centi		c 		0.01\n10^-3		milli		m		0.001\n10^-6		micro		µ		0.000 001\n10^-9		nano		n 		0.000 000 001\n10^-12		pico		p		0.000 000 000 001\n10^-15		femto		f		0.000 000 000 000 001\n10^-18		atto		a		0.000 000 000 000 000 001\n10^-21		zepto		z		0.000 000 000 000 000 000 001\n10^-24		yocto		y		0.000 000 000 000 000 000 000 001\n";
	const string constants = "\nMe = 5.98 * 10^24 	[Kilogram] Mass of Earth\nRe = 6.37 * 10 ^ 6[meters] Radius of Earth\ng = 9.80[meters / second] gravity on earth surface\nG = 6.67 * 10 ^ -11[(Newton * Meters ^ 2) / (Kilograms ^ 2)] Gravitational constant\nkb = 1.38 * 10 ^ -23[Joules / Kelvin] Boltzmann's constant\nR = 8.31[Joules / (mol * Kelvin)] Gas constant\nNa = 6.02 * 10 ^ 23[particles / mol] Avogardo's number\nT0 = -273[degrees Celcius] Absolute zero\nsigma = 5.67 * 10 ^ -8[Watts / (meters ^ 2 * Kelvin ^ 4)] Stefan - Boltzmann constant\nPatm = 101300[Pascal] standard atmosphere\nVsound = 343[meters / second] speed of sound in air 20 degrees Celsius\nMp = 1.67 * 10 ^ -27[Kilogram] Mass of the proton(and neutron)\nMe = 9.11 * 10 ^ -31[Kilogram] Mass of the electron\nK = 8.99 * 10 ^ 9[Newton*meters ^ 2 / Celcius ^ 2] Coulomb's law constant (1/4pi*e)\n";
	bool			radians;
	bool			valid(char c);
	bool			isPrecedence(char, char);
	string			isFunc(string);
	string			solveRPN(queue<string> outQueue);

//----------------------- Formulas ----------------------------------------
	void			F00quadratic(double a, double b, double c);
	void			F01pythagorean(double x, double y, char missing);
	void			F02distance2D(double x1, double y1, double x2, double y2);
	void			F03distance3D(double x1, double y1, double z1, double x2, double y2, double z);
	void			F04slope(double x1, double y1, double x2, double y2);
//-------------------------------------------------------------------------

public:
	const double	C_PI = 3.1415926535897932384626433832795;

	Calc2::Calc2();
	Calc2::Calc2(bool);
	void			CalcMenu();
	void			solve(string);
	
//----------------------- Formulas ----------------------------------------
	void			F00quadratic();
	void			F01pythagorean();
	void			F02distance2D();
	void			F03distance3D();
	void			F04slope();
//-------------------------------------------------------------------------
};

#endif CALC2