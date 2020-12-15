#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define prime_num 17
#define hash_size 100


template <class T, class U>
class Unordered_map{
	// ll prime_num = 97;
public:
	class ll_node{
	public:
		T key;
		U value;
		ll_node* next;
	}*hash_table[hash_size];

	Unordered_map(){
		for(ll i=0;i<hash_size;i++)
			hash_table[i] = NULL;
	}

	ll calculateHashIndex(T key){
		ostringstream os;
		os << key;
		string str = os.str();
		ll index=0;
		ll prime = prime_num;
		for(int i=0; i<str.length();i++){
			index = (index + (prime*str[i])%hash_size)%hash_size;
			prime = (prime*prime_num)%hash_size;
		}
		return index;
	}

	ll_node* newNode(T key, U value){
		ll_node* temp = new ll_node();
		temp->key = key;
		temp->value = value;
		temp->next = NULL;
		return temp;
	}

	void insert(T key, U value){
		ll index = calculateHashIndex(key);

		ll_node* head = hash_table[index];
		if(head==NULL){
			ll_node* node = newNode(key, value);
			hash_table[index]=node;
		}
		else{
			ll_node* curr = hash_table[index];

			bool found=false;

			while(curr->next != NULL){
				if(curr->key ==  key){
					found=true;
					break;
				}
				curr = curr->next;
			}


			if(!found && curr->key != key){
				curr->next = newNode(key, value);
				cout << "Inserted\n";
			}
			else {
				cout << "key already exist\n";
			}
		}
	}


	pair<bool, U> find(T key){
		pair<bool, U> result;
		ll index = calculateHashIndex(key);
		if(hash_table[index]==NULL){
			result.first =false;
			return result; 
		}
		else{
			ll_node* curr = hash_table[index];

			while(curr != NULL && curr->key!=key)
				curr = curr->next;


			if(curr!=NULL){
				result.first = true;
				result.second = curr->value;
			}
			else
				result.first = false;

			return result;
		}
	}

	void erase(T key){
		ll index = calculateHashIndex(key);
		ll_node *head = hash_table[index], *prev=NULL;

		if(head==NULL){
			cout << "key not there\n";
			return;
		}
		else{
			if(head->key == key){
				prev=head;
				head = head->next;
				hash_table[index]=head;
				delete prev;
				return;
			}

			while(head->next!=NULL && head->key != key){
				prev = head;
				head = head->next;
			}

			if(head->next==NULL && head->key != key)
				cout << "key not found\n";
			else{
				prev->next = head->next;
				delete prev;
			}
		}
		return;
	}

	void printMap(){
		for(ll i=0; i<hash_size; i++){
			cout << i << " : ";
			ll_node* curr = hash_table[i];
			while(curr!=NULL){
				cout << "=>[" << curr->key << "=" << curr->value << "]";
				curr=curr->next;
			}
			cout <<endl;
		}
	}

	U operator[](T key){
		pair<bool, U> result = find(key);
		U x;
		if(result.first==true){
			cout << "val is : "<< result.second<<endl;
			x = result.second;

		}
		else{
			cout << "key  not found \n";
		}
		return x;
	}
};


int main(){
	Unordered_map<string, string> um;
	string key, value;
	pair<bool, string> ans ;
	um.insert("ritvik", "eeeee");
	um.insert("garg", "wwwwww");
	um.insert("gaga", "qqqqqqq");
	um.insert("ritvik", "aaaa");
	um.insert("fafa", "zzzzzz");
	cout << endl;
	ans = um.find("ritvik");
	if (ans.first == false)
		cout << "No key Found!!!" << endl;
	else
		cout << "Value : " << ans.second << endl;
	ans = um.find("garg");
	if (ans.first == false)
		cout << "No key Found!!!" << endl;
	else
		cout << "Value : " << ans.second << endl;
	ans = um.find("ritafgsvik");
	if (ans.first == false)
		cout << "No key Found!!!" << endl;
	else
		cout << "Value : " << ans.second << endl;
	cout << endl;
	um.printMap();
	um.erase("ritvik");
	um.erase("garg");
	um.erase("gaga");
	um.erase("gagasda");
	cout << endl;
	um.printMap();
	ans = um.find("ritvik");
	if (ans.first == false)
		cout << "No key Found!!!" << endl;
	else
		cout << "Value : " << ans.second << endl;
	ans = um.find("garg");
	if (ans.first == false)
		cout << "No key Found!!!" << endl;
	else
		cout << "Value : " << ans.second << endl;
	ans = um.find("ritafgsvik");
	if (ans.first == false)
		cout << "No key Found!!!" << endl;
	else
		cout << "Value : " << ans.second << endl;
	// cout << "operator overloading : "<< um["fafa"] << endl;
	um["fafa"];
	return 0;
}