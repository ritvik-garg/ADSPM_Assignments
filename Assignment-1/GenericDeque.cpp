#include<bits/stdc++.h>
using namespace std;


template <typename T> 
class Deque{

private:
	T *arr;
	int len_deque, num_elements, left_ptr, right_ptr;

public:
	Deque();
	Deque(int size, T value);
	bool empty();
	bool full();
	void push_back(T value);
	void push_front(T value);
	void pop_front();
	void pop_back();
	T front();
	T back();
	void resize(int size, T default_value);
	void clear();
	int size();
	T& operator[](int index);
	void doubleSize();
	void display();
};

template <typename T>
Deque<T> :: Deque(){
	len_deque =  5;
	arr = new T[len_deque];
	left_ptr = -1;
	right_ptr = -1;
	num_elements = 0;
}

template <typename T>
Deque<T> :: Deque(int size, T value){
	len_deque = 2*size ;
	arr = new T[len_deque];
	fill(arr, arr+size, value);
	left_ptr = 0;
	right_ptr = size-1;
	num_elements = size;
}

template <typename T>
bool Deque<T>::empty(){
	if(left_ptr==-1)
		return true;
	return false;
}

template <typename T>
bool Deque<T>::full(){
	if((left_ptr==0 && right_ptr==len_deque-1) || (right_ptr+1==left_ptr))
		return true;
	return false;
}

template <typename T>
void Deque<T>::push_front(T value){
	if(full()){
		cout << "already filled\n";
		doubleSize();
	}
	if (left_ptr == -1 ){
		left_ptr = right_ptr = 0;
	}
	else if(left_ptr == 0){
		left_ptr = len_deque-1;
	}
	else{
		left_ptr--;
	}
	arr[left_ptr] = value;
	num_elements++;
}

template <typename T>
void Deque<T>::push_back(T value){
	if(full()){
		cout << "already filled\n";
		doubleSize();
	}
	if(left_ptr == -1 ){
		left_ptr = right_ptr = 0;
	}
	else if(right_ptr == len_deque-1){
		right_ptr = 0;
	}
	else{
		right_ptr++;
	}
	arr[right_ptr] = value;
	num_elements++;
}

template <typename T>
void Deque<T>::pop_front(){
	if(empty()){
		cout << "already empty\n";
		exit(0);
	}
	else if(left_ptr ==  right_ptr){
		left_ptr = right_ptr = -1;
	}
	else if(left_ptr==len_deque-1){
		left_ptr = 0;
	}
	else{
		left_ptr++;
	}
	num_elements--;
}

template <typename T>
void Deque<T>::pop_back(){
	if(empty()){
		cout << "already empty\n";
		exit(0);
	}
	else if(left_ptr ==  right_ptr){
		left_ptr = right_ptr = -1;
	}
	else if(right_ptr==0){
		right_ptr = len_deque-1;
	}
	else{
		right_ptr--;
	}
	num_elements--;
}

template <typename T>
T Deque<T>::front(){
	if(empty()){
		cout << "nothing ot return \n";
		exit(0);
	}

	return arr[left_ptr];
}

template <typename T>
T Deque<T>::back(){
	if(empty()){
		cout << "nothing ot return \n";
		exit(0);
	}

	return arr[right_ptr];
}

template <typename T>
int Deque<T>::size(){
	return num_elements;
}

template <typename T>
void Deque<T>::clear(){
	left_ptr = right_ptr = -1;
}

template <typename T>
void Deque<T>::resize(int new_size, T default_value){
	T* new_arr = new T[new_size];
	int left = left_ptr;
	int right = right_ptr;

	for(int i=0;i<new_size;i++){
		if(i<num_elements)
			new_arr[i]=arr[(left+i)%len_deque];
		else
			new_arr[i]=default_value;
	}

	delete[] arr;
	arr = new_arr;
	left_ptr = 0;
	len_deque = new_size;
	right_ptr = len_deque-1;
	num_elements = len_deque;
}

template<typename T>
void Deque<T>:: doubleSize(){
	T* new_arr = new T[2*len_deque];
	int left = left_ptr;
	int right = right_ptr;
	int i=0;
	
	for(int i=0;i<num_elements;i++){
		new_arr[i]=arr[(left+i)%len_deque];
	}
	delete[] arr;
	arr = new_arr;
	left_ptr = 0;
	right_ptr = len_deque-1;
	len_deque = 2*len_deque;
}

template <typename T>
T& Deque<T>::operator[](int index){
	if(empty()){
		cout << "no value found\n";
		exit(0);
	}
	return arr[index];
}

template <typename T>
void Deque<T>::display(){
	cout << "in display : \n ";
	if(empty()){
		cout << "no value found\n";
		exit(0);
	}
	for(int i=0;i<num_elements;i++){
		cout << arr[(left_ptr+i)%len_deque] << " ";
	}
	cout << endl;
}


int main(){
	// Deque<int> deque(5,3);
	Deque<int> *deque =NULL;

	int q,n,test_cases;
	int x;
	cin >>test_cases;
	while(test_cases--){
		cin >>q;
		switch (q)
		{

			case 1: cin>>x;
			deque->push_front(x);  
			deque->display();
			break;

			case 2: deque->pop_front();
			deque->display();
			break;

			case 3: cin>>x;
			deque->push_back(x);
			deque->display();
			break;

			case 4: deque->pop_back();
			deque->display();
			break;

			case 5: deque = new Deque<int>;
			break;

			case 6: cin>>n>>x;
			deque = new Deque<int>(n,x);
			deque->display();
			break;

			case 7: cout<<deque->front()<<endl;
			break;

			case 8: cout<<deque->back()<<endl;
			break;

			case 9: 
			if(deque->empty() == 0){	
				cout << "false\n";
			}
			else
				cout<< "true\n";
			break;

			case 10: cout<<deque->size()<<endl;
			break;

			case 11: cin>>n>>x;
			deque->resize(n,x);
			deque->display();
			break;

			case 12: deque->clear();
			break;

			case 13: cin>>n;
			cout<< (*deque)[n]<<endl;
			break;

			case 14: deque->display();
			break;

			default:
			break;
		}
	}
	delete deque;
	return 0;
}