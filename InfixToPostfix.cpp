#include <iostream>
#define SIZE 300

using namespace std;

// Class implementation of Stack
class Stack
{
public:
    int top;
    Stack()
    {
        top = -1;
    }

    char array[SIZE];

    //To check if the stack is empty
    bool empty()
    {
        return top < 0;
    }

    //To check if the stack is full
    bool full()
    {
        return top == SIZE - 1;
    }

    // To insert an element into the stack
    void push(int element)
    {
        if (!full())
        {
            array[++top] = element;
        }
    }

    //To delete & return the last value
    int pop()
    {
        int element = -1;
        if (!empty())
        {
            element = array[top];
            top--;
        }
        return element;
    }

    //To display the top of stack
    char Top()
    {
        if (!empty())
        {
            return array[top];
        }
        return 0;
    }

    //To clear the Stack
    void clear()
    {
        // keep deleting until array is empty
        while (!empty())
        {
            pop();
        }
    }
}; // end of Stack class

//Function to return precedence of operators
int prec(char c)
{
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Function to verify whether a character is numeric digit.
bool IsNumericDigit(char C)
{
    if (C >= '0' && C <= '9')
        return true;
    return false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C)
{
    if (C == '+' || C == '-' || C == '*' || C == '/')
        return true;

    return false;
}

// Function to perform an operation and return output.
int PerformOperation(char operation, int operand1, int operand2)
{
    if (operation == '+')
        return operand1 + operand2;
    else if (operation == '-')
        return operand1 - operand2;
    else if (operation == '*')
        return operand1 * operand2;
    else if (operation == '/')
        return operand1 / operand2;

    else
        cout << "Unexpected Error \n";
    return -1;
}

// Function to convert infix expression to postfix expression
string infixToPostfix(string s)
{
    Stack st; //For stack operations
    string result;

    //iterating the given string input
    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];

        //checking if character is operand
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            //incrementing operand to postfix expression
            result += c;

        //pushing to stack if '(' is encountered
        else if (c == '(')
        {
            st.push('(');
            result += ' ';
        }

        //removing operators from stack and adding to post fix expression 
        //if ')' is encountered
        else if (c == ')')
        {
            while (st.Top() != '(')
            {
                result += st.Top();
                st.pop();
            }
            st.pop();
        }

        //if an operator is encountered poping according to precedence
        //then pushing the operator into stack
        else
        {
            while (!st.empty() && prec(s[i]) <= prec(st.Top()))
            {
                result += st.Top();
                st.pop();
            }
            st.push(c);
            result += ' ';
        }
    }

    // Pop all the remaining elements from the stack
    while (!st.empty())
    {
        result += st.Top();
        st.pop();
    }

    return result;
} //End of Infix to Postfix function

// Function to evaluate postfix expression
int EvaluatePostfix(string expression)
{
    Stack S;

    //iterating postfix expression
    for (int i = 0; i < expression.length(); i++)
    {
        //continue if a delimiter is encountered
        if (expression[i] == ' ')
            continue;

        //performing operations if operator is encountered
        else if (IsOperator(expression[i]))
        {
            int operand2 = S.Top();
            S.pop();
            int operand1 = S.Top();
            S.pop();

            int result = PerformOperation(expression[i], operand1, operand2);
            //pushing back the result into stack
            S.push(result);
        }

        //calculating two digit number and pushing into stack
        else if (IsNumericDigit(expression[i]))
        {
            int operand = 0;
            while (i < expression.length() && IsNumericDigit(expression[i]))
            {
                operand = (operand * 10) + (expression[i] - '0');
                i++;
            }
            i--;
            S.push(operand);
        }
    }
    //returning the last element remaining in stack after the evaluation
    return S.Top();
}

//Driver program to test above functions
int main()
{
    cout << "\nINFIX TO POSTFIX CONVERSION" << endl;
    string exp = "25/5+10-2";
    string Postfix = infixToPostfix(exp);
    int result = EvaluatePostfix(Postfix);
    cout << exp << " = " << result << endl;
    return 0;
}