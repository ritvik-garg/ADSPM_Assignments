#include <bits/stdc++.h> 
using namespace std; 
#define LONG_LONG_SIZE 41
#define ll long long

struct Trie { 
	Trie* child[2]; 
	ll key; 
}; 

Trie* getNode() 
{ 
	Trie* newNode = new Trie; 
	newNode->key = 0; 
	newNode->child[0] = NULL;
	newNode->child[1] = NULL; 
	return newNode; 
} 

void insert(Trie* root, ll val) 
{ 
	Trie* temp = root; 

	for (ll i=LONG_LONG_SIZE-1; i>=0; i--) { 
		ll x = 1L << i;
		bool curr = (val & x); 

		// if null-> add new 
		if (temp->child[curr] == NULL){
			// cout << "nulll found\n";
			temp->child[curr] = getNode(); 
		}

		temp = temp->child[curr]; 
	} 
	temp->key = val; 
} 
 
ll get_max_XOR(Trie* root, ll val) 
{ 
	Trie* temp = root;; 
	ll res = 0;
	for (ll i = LONG_LONG_SIZE - 1; i >= 0; i--) { 
		ll x = 1L << i;
		// cout << "x : "<< x << endl;
		bool curr = (val & x); 
		// cout << "curr : " << curr << endl;
		bool opp = curr == 0 ? 1 : 0;
		// cout << "opp bit : " << opp << endl;
		if (temp->child[opp] != NULL){
			res += pow(2,i);
			temp = temp->child[opp]; 
		}
		else if (temp->child[curr] != NULL) 
			temp = temp->child[curr]; 
	} 
	// cout << "res : " << res<< endl;
	return res; 
} 


int main() 
{ 
	ll n, q, val;
	cin >> n >> q;

	ll arr[n];
	Trie* root = getNode(); 

	for(ll i=0;i<n;i++){
		cin >> arr[i];
		insert(root, arr[i]); 
	}

	for(ll i=0;i<q;i++){
		cin >> val;
		cout << get_max_XOR(root, val) << endl;
	}

	return 0; 
} 
