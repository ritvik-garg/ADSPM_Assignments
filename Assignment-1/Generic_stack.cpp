#include<iostream>
#include <iomanip>
#include <fstream>
using namespace std;


template<typename T>
struct stackNode {
	T data;
	struct stackNode* next;
};

template<typename T>
class Stack{
private:
	stackNode<T>* top;
public:
	Stack(){
		top=NULL;
	}
	void push(T value);
	void pop();
	T topElement();
	void display();
	bool isEmpty();
	int size();
};

template<typename T>
void Stack<T>::push(T value){

	stackNode<T>* newstackNode =  new stackNode<T>();

	newstackNode->data = value; 
	
	if(top ==  NULL)
		newstackNode->next = NULL;
	else{
		newstackNode->next=top;
	}
	top = newstackNode;
}

template<typename T>
void Stack<T>::pop(){
	if(top == NULL)
		cout<<"\nStack is already empty : nothing to pop\n";
	else{
		stackNode<T>* temp = top;
		top = top->next;
		temp->next = NULL;
		free(temp);
	}
}

template<typename T>
T Stack<T>::topElement(){
	if(top == NULL){
		cout<<"\nStack is already empty : nothing on top\n";
		exit(0);
	}
	else{
		return top->data;
	}
}

template<typename T>
void Stack<T>::display(){
	stackNode<T>* temp = top;
	if(temp == NULL){
		cout << "\nStack is already empty : nothing on display\n";
	}
	while(temp){
		cout<<temp->data << " ";
		temp = temp->next;
	}
	cout<<endl;
}

template<typename T>
bool Stack<T>::isEmpty(){
	if(top == NULL)
		return true;
	return false;
}

template<typename T>
int Stack<T>::size(){
	int size=0;
	stackNode<T> *temp = top;
	while(temp != NULL){
		temp = temp->next;
		size++;
	}
	return size;
}

int priority(char op){
	if(op=='/' || op == '*' || op == '%')
		return 2;
	else if(op == '+' || op == '-')
		return 1;
	return 0;
}

double evaluate(double val1, double val2, char op){
	double result;

	switch (op){
		case '+' : result = val1 + val2;
		break;
		case '*' : result = val1 * val2;
		break;
		case '-' : result = val1 - val2;
		break;
		case '/' : result = val1 / val2;
		break;
		case '%' : result = int(val1) % int(val2);
		// case '%' : result = fmod(val1,val2);
	}
	return result;
}

double solveExpression(string expr){
	
	Stack<double> value;
	Stack<char> _operator;

	string num="";
	int expr_length = expr.length();
	double result, val1, val2;
	char op;

	for(int i=0; i<expr_length; i++){
		if(expr[i]=='('){
			_operator.push(expr[i]);
		}

		else if(expr[i] >='0' && expr[i]<='9'){
			while(i<expr_length && ((expr[i] >='0' && expr[i]<='9') || expr[i]=='.')){				
				num += expr[i];
				i++;
			}
			double numerical_val = stod(num);
			num = "";
			value.push(numerical_val);
			i--;
		}

		else if(expr[i]==')'){
			while(_operator.topElement() != '('){
				val1 = value.topElement();
				value.pop();
				val2 = value.topElement();
				value.pop();
				op = _operator.topElement();
				_operator.pop();
				result = evaluate(val2, val1, op);
				value.push(result);
			}
			_operator.pop(); // pop '('
		}

		else if(expr[i]=='+' || expr[i]=='-' || expr[i]=='/' || expr[i]=='*' || expr[i]=='%'){
			if(!_operator.isEmpty()){
				if(priority(expr[i]) > priority(_operator.topElement())){
					_operator.push(expr[i]);	
				}
				else{
					while(!_operator.isEmpty() && priority(expr[i]) <= priority(_operator.topElement())){
						val1 = value.topElement();
						value.pop();
						val2 = value.topElement();
						value.pop();
						op = _operator.topElement();
						_operator.pop();
						result = evaluate(val2, val1, op);
						value.push(result);
					}
					_operator.push(expr[i]);
				}
			}
			else
				_operator.push(expr[i]);
		}
	}
	
	while(value.size()!=1){
		val1 = value.topElement();
		value.pop();
		val2 = value.topElement();
		value.pop();
		op = _operator.topElement();
		_operator.pop();
		result = evaluate(val2, val1, op);
		value.push(result);
	}
	return result;
}

int main(){

	string expr;
	cin >> expr;
	double ans = solveExpression(expr);
	cout << fixed << setprecision(5) << ans << endl;
	return 0;
	
}