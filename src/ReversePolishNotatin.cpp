// Reverse Polish notation
// Allows ints and floats.
//
#include <iostream>
using namespace std;
using std::cout;
using std::endl;
//
//Stack code
#define MAX_STACK 100
float _stack[MAX_STACK];
int tos = 0;

bool Full(){
	return tos >= MAX_STACK - 1;
}

bool Empty(){
	return tos == 0;
}

void Push(float value){
	if (Full()){
		return;
	}
	tos++;
	_stack[tos] = value;
}

float Pop(){
	float t = _stack[tos];
	tos--;
	return t;
}
//Enf of stack code

bool IsOp(char c){
	//Check for operators.
	switch (c){
		case '+':
		case '-':
		case '*':
		case '/':
			return true;
		default:
			return false;
	}
}

double RPN(string expression){
	int i = 0;
	float v1, v2, ret;
	v1 = ret = v2 = 0.0;

	string tok = "";

	while (i < expression.length()){
		//Skip white space
		while (isspace(expression[i])){
			i++;
		}
		//Check for digits and .
		if (isdigit(expression[i]) | expression[i] == '.'){
			while (isdigit(expression[i]) | expression[i] == '.'){
				tok += expression[i];
				i++;
			}
			//Push on stack number.
			Push(atof(tok.c_str()));
			tok = "";
		}
		//Check for operator
		else if (IsOp(expression[i])){
			if (expression[i] == '+'){
				v1 = Pop();
				v2 = Pop();
				ret = (v1 + v2);
			}
			if (expression[i] == '-'){
				v1 = Pop();
				v2 = Pop();
				ret = v2 - v1;
			}
			if (expression[i] == '*'){
				v1 = Pop();
				v2 = Pop();
				ret = (v1 * v2);
			}
			if (expression[i] == '/'){
				v1 = Pop();
				v2 = Pop();
				ret = (v2 / v1);
			}
			//INC Counter
			i++;
			//Push result onto stack
			Push(ret);
		}
		else{
			cout << "Invaild Expression." << endl;
			break;
		}
	}
	//Return answer
	return Pop();
}

int main(int argc, char *argv[]){
	system("title RPN Calulator Demo");
	//Infix == (4 * (12 + 3) / 2 * (5 + 5) - (100 * 2))/2 Answer 50
	string expr = "4 12 3 + * 2 / 5 5 + * 100 2 * - 2 /";

	cout << "Expression  : " << expr.c_str() << endl;
	cout << "Answer      : " << RPN(expr) << endl << endl;
	cout << "Expression  : " << "22 7 /" << endl;
	cout << "PI          : " << RPN("22 7 /") << endl;

	system("pause");
	return 0;
}