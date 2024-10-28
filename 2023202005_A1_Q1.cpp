#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;

template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &value) : data(value), next(nullptr) {}
    };

    Node *topNode;

public:
    Stack() : topNode(nullptr) {}

    void push(const T &value)
    {
        Node *newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    T pop()
    {
        if (isEmpty())
        {
            cerr << "Stack is empty." << endl;
            exit(1);
        }

        T value = topNode->data;
        Node *temp = topNode;
        topNode = topNode->next;
        delete temp;
        return value;
    }

    T top() const
    {
        if (isEmpty())
        {
            cerr << "Stack is empty." << endl;
            exit(1);
        }
        return topNode->data;
    }

    bool isEmpty() const
    {
        return topNode == nullptr;
    }

    ~Stack()
    {
        while (!isEmpty())
        {
            Node *temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
};
//calculate addition

string add(const string &a, const string &b)
{
    string result;
    int carry = 0;

    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0)
    {
        int sum = carry;
        if (i >= 0)
            sum += a[i] - '0';
        if (j >= 0)
            sum += b[j] - '0';

        carry = sum / 10;
        sum %= 10;

        result = char(sum + '0') + result;

        if (i >= 0)
            i--;
        if (j >= 0)
            j--;
    }

    return result;
}
//calculate subtract
string subtract(const string &a, const string &b) {
    string result;

    int i = a.size() - 1;
    int j = b.size() - 1;
    int borrow = 0;

    while (i >= 0 || j >= 0) {
        int num1 = (i >= 0) ? a[i] - '0' : 0;
        int num2 = (j >= 0) ? b[j] - '0' : 0;

        int diff = num1 - num2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result = char(diff + '0') + result;

        if (i >= 0) i--;
        if (j >= 0) j--;
    }

    // Remove leading zeros
    result.erase(0, min(result.find_first_not_of('0'), result.size()));

    return result.empty() ? "0" : result;
}

//Calculate multiply
string multiply(const string &a, const string &b) {
    int size_a = a.size();
    int size_b = b.size();
    int size_result = size_a + size_b;
    int *result = new int[size_result]();

    for (int i = size_a - 1; i >= 0; i--) {
        for (int j = size_b - 1; j >= 0; j--) {
            int product = (a[i] - '0') * (b[j] - '0');
            int sum = product + result[i + j + 1];

            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    string result_str;
    int start = 0;
    while (start < size_result && result[start] == 0) {
        ++start;
    }
    for (int i = start; i < size_result; ++i) {
        result_str += to_string(result[i]);
    }

    delete[] result;

    return result_str.empty() ? "0" : result_str;
}


bool isSmallerOrEqual(const string &a, const string &b)
{
    if (a.length() < b.length())
    {
        return true;
    }
    if (a.length() > b.length())
    {
        return false;
    }

    for (size_t i = 0; i < a.length(); ++i)
    {
        if (a[i] < b[i])
        {
            return true;
        }
        if (a[i] > b[i])
        {
            return false;
        }
    }

    return true; // They are equal
}
//Calculate divide
string divide(const string &a, const string &b)
{
    if (b == "0")
    {
        return "Undefined"; // Division by zero
    }

    string quotient;
    string remainder = "";

    for (char c : a)
    {
        remainder += c;

        int i = 0;
        while (isSmallerOrEqual(b, remainder))
        {
            remainder = subtract(remainder, b);
            i += 1;
        }

        quotient += to_string(i);
    }

    // Remove leading zeros from the quotient
    size_t firstNonZero = 0;
    while (firstNonZero < quotient.size() && quotient[firstNonZero] == '0')
    {
        firstNonZero++;
    }
    quotient = quotient.substr(firstNonZero);

    if (quotient.empty())
    {
        return "0";
    }

    return quotient;
}
//calculate exponentiation
string exponentiate(const string &base, int exponent)
{
    if (exponent == 0)
    {
        return "1";
    }
    else if (exponent % 2 == 0)
    {
        string temp = exponentiate(base, exponent / 2);
        return multiply(temp, temp);
    }
    else
    {
        string temp = exponentiate(base, (exponent - 1) / 2);
        return multiply(multiply(temp, temp), base);
    }
}
//Calculate gcd
string gcd(string a, string b)
{
    if (a == "0" || b == "0")
    {
        return "GCD(0, x) or GCD(x, 0) is not defined!";
    }

    while (b != "0")
    {
        string remainder = subtract(a, multiply(divide(a, b), b));
        a = b;
        b = remainder;
    }

    return a;
}
//Calculate factorial
string factorial(string n)
{
    if (n == "0" || n == "1")
    {
        return "1";
    }

    string result = "1";
    string one = "1";

    while (n != "1")
    {
        result = multiply(result, n);
        n = subtract(n, one);

        // Remove leading zeros from n
        n.erase(0, min(n.find_first_not_of('0'), n.size() - 1));
    }

    return result;
}

int precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '/' || c == 'x')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}
//convert infix to postfix
string infixToPostfix(const string &expression)
{
    string postfix;
    Stack<char> operatorStack;

    for (char c : expression)
    {
        if (isdigit(c))
        {
            postfix += c;
        }
        else if (c == '+' || c == '-' || c == 'x' || c == '/')
        {
            if (!postfix.empty())
            {
                postfix += ' '; // Add space as delimiter before the operator
            }

            while (!operatorStack.isEmpty() && precedence(c) <= precedence(operatorStack.top()))
            {
                postfix += operatorStack.pop();
                postfix += ' '; // Add space as delimiter
            }
            operatorStack.push(c);
        }
    }

    while (!operatorStack.isEmpty())
    {
        postfix += ' '; // Add delimiter
        postfix += operatorStack.pop();
    }

    return postfix;
}

string performOperation(const string &op1, const string &op2, char op)
{
    switch (op)
    {
    case '+':
        return add(op1, op2);
    case '-':
        return subtract(op1, op2);
    case 'x':
        return multiply(op1, op2);
    case '/':
        return divide(op1, op2);
    }
    return "Error: Invalid operator";
}
//evaluate postfix
string evaluatePostfix(string exp)
{
    Stack<string> operandStack;

    stringstream ss(exp);
    string token;

    while (ss >> token)
    {
        if (isdigit(token[0]))
        {
            operandStack.push(token);
        }
        else if (token == "+" || token == "-" || token == "x" || token == "/")
        {
            string op2 = operandStack.pop();
            string op1 = operandStack.pop();
            string result = performOperation(op1, op2, token[0]);
            operandStack.push(result);
        }
        else
        {
            cerr << "Invalid token: " << token << endl;
            exit(1);
        }
    }

    string finalResult = operandStack.pop();
    return finalResult;
}



int main()
{
    int operationType;
    cin >> operationType;

    if (operationType == 1)
    {
        cin.ignore(); // Consume newline character

        string expression;
        getline(cin, expression);

   

        // Convert infix to postfix using user-defined stack
        string postfixExpression=infixToPostfix(expression);
       // cout << "Postfix Expression: " <<postfixExpression << endl;

        // Evaluate postfix expression using user-defined stack
        string result = evaluatePostfix(postfixExpression);
        cout << result << endl;
        cout.flush();
    }
    else if (operationType == 2)
    {
        string base, exponent;
        cin >> base >> exponent;
        // Perform exponentiation
        string result = exponentiate(base, stoi(exponent));
        cout << result << endl;
    }
    else if (operationType == 3)
    {
        string num1, num2;
        cin >> num1 >> num2;
        // Perform GCD calculation
        string result = gcd(num1, num2);
        cout << result << endl;
    }
    else if (operationType == 4)
    {
        string num;
        cin >> num;
        // Perform factorial calculation
        string result = factorial(num);
        cout << result << endl;
    }

    return 0;
}
