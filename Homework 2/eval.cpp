#include "Set.h"
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
#include <iostream>
using namespace std;

string toPostfix(const string& infix, string& postfix);
int precedence(const char& ch);

int evaluate(string infix, const Set& trueValues, const Set& falseValues,
	string& postfix, bool& result)
{
	if (infix == "")
		return 1;
	//STEP 1: SYNTACTICALLY VALID
	// Remove spaces
	string tempInfix;
	for (int i = 0; i < infix.size(); i++)
	{
		char ch = infix[i];
		if(ch != ' ')
			tempInfix += ch;
	}
	infix = tempInfix;
	tempInfix = "";

	for (int i = 0; i < infix.size(); i++)
	{
		char ch = infix[i];
		if (isalpha(ch) && tolower(ch) != ch) // a non-lowercase letter
			return 1;
		else if (!isalpha(ch) && ch != '!' && ch != '&' && ch != '|' && ch != ')' && ch != '(') // no operator or parenthases or space
			return 1;
	}

	for (int i = 1; i < infix.size(); i++)
	{
		char ch = infix[i];
		if (!isalpha(ch) && ch != '!' && ch != '(' && infix[i - 1] == '(')
			return 1;
	}

	for (int i = 0; i < infix.size()-1; i++)
	{
		char ch = infix[i];
		if (!isalpha(ch) && ch != ')' && infix[i + 1] == ')')
			return 1;
	}

	// Create temp without '(' or ')'
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] != '(' && infix[i] != ')')
			tempInfix += infix[i];
	}
	if (tempInfix == "")
		return 1;

	// Check that there are no instances of double operators or double operands
	for (int i = 1; i < tempInfix.size(); i++)
	{
		if ((isalpha(tempInfix[i - 1]) && isalpha(tempInfix[i])))
			return 1;
		else if ((tempInfix[i - 1] == '&' || tempInfix[i - 1] == '|') 
			&& (tempInfix[i] == '&' || tempInfix[i] == '|'))
			return 1;
	}

	// Check that the first and last characters in the string are either 
	// '(', '!' or alpha or ')' or alpha, respectively
	if ((infix[0] != '(' && infix[0] != '!' && !isalpha(infix[0])) ||
		(infix[infix.size() - 1] != ')' && !isalpha(infix[infix.size() - 1])))
		return 1;

	// Loop to check that there are no instances of invalid
	// parentheses
	int rightParentheses = 0;
	int leftParentheses = 0;

	for (int i = 0; i < infix.size(); i++)
	{
		char ch = infix[i];
		if (ch == '(')
			leftParentheses++;
		if (ch == ')')
			rightParentheses++;
		if (rightParentheses > leftParentheses)
			return 1;
		if (i == infix.size() - 1 && rightParentheses != leftParentheses)
			return 1;
	}

	//===========================================================//

	//STEP 2: CHECK OPERAND LETTERS

	for (int i = 0; i < infix.size(); i++)
	{
		if (!trueValues.contains(infix[i]) && !falseValues.contains(infix[i]) && isalpha(infix[i]))
			return 2;
		else if (trueValues.contains(infix[i]) && falseValues.contains(infix[i]))
			return 3;
	}

	// if 1, 2, or 3 has not been returned and infix is syntactically valid
	// and infix contains only letters that in either falseValues or trueValues
	postfix = toPostfix(infix, postfix);

	//===========================================================//

	//STEP 3: EVALUATE POSTFIX

	stack<bool> operands;
	bool operand1;
	bool operand2;
	for (int i = 0; i < postfix.size(); i++)
	{
		char ch = postfix[i];
		if (trueValues.contains(ch))
			operands.push(true);
		else if (falseValues.contains(ch))
			operands.push(false);
		else if (ch == '!')
		{
			operand1 = operands.top();
			operands.top() = !operands.top();
		}
		else
		{
			operand2 = operands.top();
			operands.pop();
			operand1 = operands.top();
			operands.pop();
			if (ch == '|')
				operands.push(operand1 | operand2);
			else if (ch == '&')
				operands.push(operand1 & operand2);
		}
	}
	result = operands.top();
	return 0;
}

string toPostfix(const string& infix, string& postfix)
{
	postfix = "";
	stack<char> operators;
	for (int i = 0; i < infix.size(); i++)
	{
		char ch = infix[i];
		if (ch == ' ')
			continue;
		if (isalpha(ch))
		{
			postfix += ch;
			continue;
		}
		switch (ch)
		{
		case '(':
		{
			operators.push(ch);
			break;
		}
		case ')':
		{
			while (operators.top() != '(')
			{
				postfix += operators.top();
				operators.pop();
			}
			operators.pop();
			break;
		}
		case '|':
		case '&':
		{
			while (!operators.empty() && operators.top() != '('
				&& (precedence(ch) <= precedence(operators.top())))
			{
				postfix += operators.top();
				operators.pop();
			}
			operators.push(ch);
			break;
		}
		case '!':
			while (!operators.empty() && operators.top() != '('
				&& (precedence(ch) < precedence(operators.top())))
			{
				postfix += operators.top();
				operators.pop();
			}
			operators.push(ch);
			break;
		}
	}
	while (!operators.empty())
	{
		postfix += operators.top();
		operators.pop();
	}
	return postfix;
}

int precedence(const char& ch)
{
	if (ch == '!')
		return 3;
	else if (ch == '&')
		return 2;
	else if (ch == '|')
		return 1;
	return -1;
}

int main()
{
	string trueChars = "tywz";
	string falseChars = "fnx";
	Set trues;
	Set falses;
	for (int k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (int k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	string pf;
	bool answer;
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" &&  answer);
	assert(evaluate("y|", trues, falses, pf, answer) == 1);
	assert(evaluate("n t", trues, falses, pf, answer) == 1);
	assert(evaluate("nt", trues, falses, pf, answer) == 1);
	assert(evaluate("()", trues, falses, pf, answer) == 1);
	assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
	assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
	assert(evaluate("", trues, falses, pf, answer) == 1);
	assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
		&& pf == "ff!tn&&|" && !answer); //TRACE
	assert(evaluate(" x  ", trues, falses, pf, answer) == 0 && pf == "x" && !answer);
	trues.insert('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 3);
	falses.erase('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 0 && pf == "x"  &&  answer);
	trues.erase('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 2);
	falses.insert('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && !answer);
	cout << "Passed all tests" << endl;
}