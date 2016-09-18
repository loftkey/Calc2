#include "Calc2.h"


// constructor
Calc2::Calc2()
{
	radians = true;
}
// overloaded constructor for radian or degree
Calc2::Calc2(bool b)
{
	radians = b;
}
//this function displays the menu for Calc2
void Calc2::CalcMenu()
{
	system("color 3");

	string parse, temp = radians ? "\nUsing: Radians\n" : "\nUsing: Degrees\n";
	bool Exit = false;
	int tempi;
	printf("%s", menu.c_str());
	printf("%s", temp.c_str());
	printf("%s", "\n[Calc]: ");
	while (!Exit)
	{
		std::getline(std::cin, parse);
		if (parse == "R" || parse == "r")
		{
			radians = !radians;
			temp = radians ? "\nUsing: Radians\n" : "\nUsing: Degrees\n";
			printf("%s", temp.c_str());
		}
		else if (parse == "E" || parse == "e")
		{
			system("CLS"); // replace with util clearScreen
			Exit = true;
		}
		else if (toupper(parse[0]) == 'F')
		{
			if (parse.size() > 2)
			{
				if (isdigit(parse[1]) && isdigit(parse[2]))
				{
					tempi = stoi(parse.substr(1, 2));
					switch (tempi)
					{
					case 00:
						F00quadratic();
						break;
					case 01:
						F01pythagorean();
						break;
					case 02:
						F02distance();
						break;
					case 03:
						F03slope();
						break;
					default:
						tempi = -1;
					}
				}
				else
					printf("%s\n", "Error: 000 INVALID INPUT");
			}
			else
				printf("%s", formulaList.c_str());
		}
		else if (parse == "L" || parse == "l")
		{
			system("CLS"); // replace with util clearScreen
			printf("%s", menu.c_str());
			printf("%s", temp.c_str());
		}
		else if (parse == "I" || parse == "i")
		{
			printf("%s", info.c_str());
		}
		else
		{
			if (!parse.empty())
				solve(parse);
		}
		parse.clear();
		
		printf("%s", "\n[Calc]: ");
	}
	system("color A");
}
// this function checks if input is valid but not a function/operator
bool Calc2::valid(char c)
{
	return (isdigit(c) || c == '(' || c == ')' || c == ' ' || c == '.');
}
// this determines order of operations precedence
bool Calc2::isPrecedence(char a, char b)
{
	if ((a == '*' || a == '/') > (b == '*' || b == '/' || b == 's' || b == 'c' || b == 't' || b == '^' || b == '(' || b == ')'))
	{
		return true;
	}
	if ((a == 's' || a == 'c' || a == 't') > (b == 's' || b == 'c' || b == 't' || b == '^' || b == '(' || b == ')'))
	{
		return true;
	}
	if ((a == '^') > (b == '^' || b == '(' || b == ')'))
	{
		return true;
	}
	return((a == '(' || a == ')') > (b == '(' || b == ')'));
}
//this function returns true if is an operator/ function
string Calc2::isFunc(string s)
{
	if (s[0] == '+')
		return "+";
	if (s[0] == '-')
		return "-";
	if (s[0] == '*')
		return "*";
	if (s[0] == '/')
		return "/";
	if (s[0] == '^')
		return "^";
	if (s.length() > 2)
	{
		if (tolower(s[0]) == 's' && tolower(s[1]) == 'i' && tolower(s[2]) == 'n')
			return "sin";
		if (tolower(s[0]) == 'c' && tolower(s[1]) == 'o' && tolower(s[2]) == 's')
			return "cos";
		if (tolower(s[0]) == 't' && tolower(s[1]) == 'a' && tolower(s[2]) == 'n')
			return "tan";
	}
	return "";
}
// Shunting Yard Algorithm
// this function convers infix to rpn and solves rpn using solveRPN()
void Calc2::solve(string input)
{
	string temp = "";
	bool noDec = true, neg = false;;
	int paren = 0;
	queue<string> outQueue;					//output queue
	std::stack<string> opStack;						//opperator stack
	while (!input.empty() || !opStack.empty())		//eats input till it is empty
	{
		if (!input.empty())
		{
			if (valid(tolower(input[0])) || !isFunc(input).empty())
			{
				while (isdigit(input[0]) || (input[0] == '.' && noDec))
				{
					noDec = (input[0] == '.') ? false : noDec;
					temp += input[0];
					input.erase(input.begin()); // eat
				}
				if (input[0] == '.')
				{
					printf("%s\n", "Error: 000 INVALID INPUT");
					break;
				}
				noDec = true;
				if (!temp.empty() && !isdigit(input[0]))
				{
					outQueue.push(temp); // push num on Queue
					temp.clear();
				}
				while (input[0] == ' ')
				{
					input.erase(input.begin()); // eat
				}
				if (!isFunc(input).empty())
				{
					temp = isFunc(input);
					if (!opStack.empty() && opStack.top()[0] != '(')
					{
						if (opStack.top()[0] == '^') // checks ^ because it is right to left instead of left to right
						{
							if (isPrecedence(opStack.top()[0] , temp[0]))
							{
								outQueue.push(opStack.top()); // push opperator on Queue
								opStack.pop(); // pop stack
							}
						}
						else if ((!isPrecedence(temp[0], opStack.top()[0])))
						{
							outQueue.push(opStack.top()); // push opperator on Queue
							opStack.pop(); // pop stack
						}
					}
					opStack.push(temp); // push Stack
					input.erase(0, temp.length()); // eat
					temp.clear();
				}
				if (input[0] == '(')
				{
					opStack.push("("); // push Stack
					paren++;
					input.erase(input.begin()); // eat
					while (input[0] == ' ')
					{
						input.erase(input.begin()); // eat
					}
					if (input[0] == '-')
					{
						neg = true;
						input.erase(input.begin()); // eat
					}
				}
				if (input[0] == ')')
				{
					while (opStack.top()[0] != '(')
					{
						outQueue.push(opStack.top()); // push opperator on Queue
						opStack.pop(); // pop stack
						if (opStack.empty())
							break;
					}
					if (opStack.top()[0] == '(')
					{
						opStack.pop(); // pop stack
						if (neg && paren == 1)
						{
							outQueue.push("-1");
							outQueue.push("*");
							neg = false;
						}
						paren--;
						input.erase(input.begin()); // eat
					}
					else
					{
						printf("%s\n", "Error: 001 MISSIMATCHED PERENTHESES");
						break;
					}
				}
			}
			else
			{
				printf("%s\n", "Error: 000 INVALID INPUT");
				break;
			}
		}
		else
		{
			while (!opStack.empty())
			{
				if (opStack.top()[0] == '(' || opStack.top()[0] == ')')
				{
					printf("%s\n", "Error: 001 MISSIMATCHED PERENTHESES");
					break;
				}
				else
				{
					outQueue.push(opStack.top()); // push opperator on Queue
					opStack.pop(); // pop stack
				}
			}
		}
	}	
	if (input.empty() && opStack.empty())
	{
		printf("\n%s\n", solveRPN(outQueue).c_str());
	}
}
// this function solves RPN
string Calc2::solveRPN(queue<string> outQueue)
{
	double dub;
	string temp;
	int size = outQueue.size();
	std::stack<double> nums;
	for (int i = 0; i < size; i++)
	{
		temp = outQueue.front();
		if ((valid(temp[0]) || !isFunc(temp).empty()) && temp[0] != '(' && temp[0] != '(')
		{
			if (isdigit(temp[0]) || temp[0] == '.' || temp == "-1")
			{
				nums.push(stod(temp));
				outQueue.pop();
			}
			else
			{
				if (isalpha(temp[0]) && nums.size() > 0) // means its sohcahtoa
				{
					switch (temp[0])	
					{
						case 's':
							if (radians)
								nums.top() = sin(nums.top());
							else
								nums.top() = sin(nums.top() * PI / 180);
							break;
						case 'c':
							if (radians)
								nums.top() = cos(nums.top());
							else
								nums.top() = cos(nums.top() * PI / 180);
							break;
						case 't':
							if (radians)
								nums.top() = tan(nums.top());
							else
								nums.top() = tan(nums.top() * PI / 180);
							break;
					}
					outQueue.pop();
				}
				else if (nums.size() > 1)
				{
					dub = nums.top();
					nums.pop();
					switch (temp[0])
					{
					case '+':
						nums.top() = nums.top() + dub;
						break;
					case '-':
						nums.top() = nums.top() - dub;
						break;
					case '*':
						nums.top() = nums.top() * dub;
						break;
					case '/':
						nums.top() = nums.top() / dub;
						break;
					case '^':
						nums.top() = pow( nums.top() , dub);
						break;
					}
					outQueue.pop();
				}
			}
		}
	}
	if (nums.size() == 1 && outQueue.empty())
	{
		std::ostringstream strs;
		strs << nums.top();
		temp = strs.str();
		if (nums.top() < .0000000000009 && nums.top() > 0)
			temp += " ?= 0";
		return temp;
	}
	else
	{
		if (nums.size() != 1)
			return ("Error: 002 nums size != 1");
		else
			return ("Error: 003 outQueue size != 0");
	}
}
//Formulas
//F00 Quadratic Formula - Public
void Calc2::F00quadratic()
{
	double a, b, c;
	string temp;
	printf("%s\n", "\n[---> Quadratic Formula:");
	printf("%s\n", "[---> given: (a, b, c): ax^2 + bx + c = 0");
	printf("%s\n", "[---> solve: (-b  +- sqrt((b^2) - 4 * a * c)) / (2 * a)");
	printf("%s\n", "[---> Please Enter ");
	printf("%s", "value of a: ");
	std::getline(std::cin,temp);
	a = stod(temp);
	printf("%s", "value of b: ");
	std::getline(std::cin, temp);
	b = stod(temp);
	printf("%s", "value of c: ");
	std::getline(std::cin, temp);
	c = stod(temp);
	F00quadratic(a, b, c);
}
//F00 Quadratic Formula - Private
void Calc2::F00quadratic(double a, double b, double c)
{
	if ((pow(b, 2) - 4 * a *  c) < 0)
	{
		printf("%s", "Error: 004 Imaginary number");
		std::cout << "Solution: ( " << -b << " +- " << sqrt(-(pow(b, 2) - 4 * a *  c)) << "i )  / " << (2 * a) << std::endl;
	}
	else
		std::cout << "Solution: ( " << -b << " +- " << sqrt(pow(b, 2) - 4 * a *  c) << " )  / " << (2 * a) << " : (" << (-b + sqrt(pow(b, 2) - 4 * a *  c)) / (2 * a) << ", " << (-b - sqrt(pow(b, 2) - 4 * a *  c)) / (2 * a) << ")" <<  std::endl;
}
//F01 Pythagorean Theorem - Public
void Calc2::F01pythagorean()
{
	double x, y;
	char missing;
	string temp;
	printf("%s\n", "\n[---> Pythagorean Theorem:");
	printf("%s\n", "[---> given: two of three values: a, b, c where c is the hypotenuse of a right triangle");
	printf("%s\n", "[---> solve: a^2 + b^2 = c^2");
	printf("%s", "[---> Please Enter the missing variable letter 'a', 'b', or 'c': ");
	std::cin >> missing;
	switch (tolower(missing))
	{
		case 'a' :
			printf("%s", "Enter b: ");
			std::cin >> x;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("%s", "Enter c: ");
			std::cin >> y;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		case 'b' :
			printf("%s", "Enter a: ");
			std::cin >> x;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("%s", "Enter c: ");
			std::cin >> y;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		case 'c' :
			printf("%s", "Enter a: ");
			std::cin >> x;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("%s", "Enter b: ");
			std::cin >> y;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		default:
			missing = 'E';
			printf("%s\n", "Error: 000 INVALID INPUT");
			break;
	}
	if (missing != 'E')
		F01pythagorean(x, y, missing);
}
//F01 Pythagorean Theorem - Private
void Calc2::F01pythagorean(double x, double y, char missing)
{
	double solution;
	if (missing != 'c')
	{
		solution = pow(y, 2) - pow(x, 2);
	}
	else
		solution = pow(y, 2) + pow(x, 2);
	
	if (solution < 0)
	{
		printf("%s", "Error: 004 Imaginary number");
		std::cout << "Solution: " << sqrt(-solution) << "i" << std::endl;
	}
	else
		std::cout <<"Solution: " <<  sqrt(solution) << std::endl;
}
//F02 Distance Formula - Public
void Calc2::F02distance()
{
	double x1, x2, y1, y2;
	printf("%s\n", "\n[---> Distance Formula");
	printf("%s\n", "[---> given: two points (x1, y1) and (x2, y2)");
	printf("%s\n", "[---> solve: The distance between the two points: sqrt((x2 - x1)^2 + (y2 - y1)^2)");
	printf("%s\n", "[---> Please Enter:");
	std::cout << "x1: ";
	std::cin >> x1;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "y1: ";
	std::cin >> y1;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "x2: ";
	std::cin >> x2;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "y2: ";
	std::cin >> y2;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	F02distance(x1, y1, x2, y2);
}
//F02 Distance Formula - Private
void Calc2::F02distance(double x1, double y1, double x2, double y2)
{
	std::cout << "Solution: " << sqrt(pow(x2-x1,2) + pow(y2-y1,2)) << std::endl;
}
//F03 Slope Formula - Public
void Calc2::F03slope()
{
	double x1, x2, y1, y2;
	printf("%s\n", "\n[---> Slope Formula");
	printf("%s\n", "[---> given: two points (x1, y1) and (x2, y2)");
	printf("%s\n", "[---> solve: The slope = Rise/Run (y2 - y1)/(x2 - x1)");
	printf("%s\n", "[---> Please Enter:");
	std::cout << "x1: ";
	std::cin >> x1;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "y1: ";
	std::cin >> y1;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "x2: ";
	std::cin >> x2;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "y2: ";
	std::cin >> y2;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	F03slope(x1, y1, x2, y2);
}
//F03 Slope Formula - Private
void Calc2::F03slope(double x1, double y1, double x2, double y2)
{
	std::cout << "Solution: " << (y2-y1) << "/" << (x2-x1) << std::endl;
}