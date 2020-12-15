#include<bits/stdc++.h>
using namespace std;

template<class T, class U>
bool max(T a, U b){
	if(a>b)
		return a;
	return b;
}

template<class T, class U>
bool min(T a, U b){
	if(a<b)
		return a;
	return b;
}

template<class T>
struct Greater{
	bool operator()(const T &a, const T &b){
		return a>b;
	}
};

template <typename T, class Comparator = Greater<T>> 
class AvlTree{
private:
	Comparator cmp;
	struct Avl{
		T data;
		Avl* right;
		Avl* left;
		int height;
		int count;
		int right_count;
	};
public:
	Avl* root;
	// cmp(Comparator());
	AvlTree()
	{
		root = NULL;
	}
	Avl* newNode(T key){
		Avl* node = new Avl();	
		node->data = key;
		node->left = NULL;
		node->right = NULL;
		node->height = 1;
		node->count=1;
		node->right_count = 0;
		return node;
	}

	int heightOfNode(Avl* node){
		if(node==NULL){
			return 0;
		}

		return node->height;

		int left_height = heightOfNode(node->left);
		int right_height = heightOfNode(node->right);

		return 1+max(left_height, right_height);
	}
	
	int balanceFactor(Avl* node){
		if (node == NULL)
			return 0;
		return heightOfNode(node->left) - heightOfNode(node->right);
	}
	
	Avl* insert(Avl* node,  T key){
		if (node == NULL)
			return (newNode(key));
		// else if(key > node->data){
		else if(cmp(key,node->data)){
			node->right = insert(node->right, key);
			node->right_count++;
		}
		// else if(key < node->data)
		else if(cmp(node->data,key))
			node->left = insert(node->left, key);
		// else if(key == node->data){
		else if(!cmp(key,node->data) && !cmp(node->data,key)){
			node->count += 1;
			return node;
		}

		node->height = 1+ max(heightOfNode(node->left), heightOfNode(node->right));

		int bf = balanceFactor(node);
		if(bf > 1){
			// if(key < node->left->data){
			if(cmp(node->left->data,key)){
				return right_rotation(node);
			}else if (cmp(key, node->left->data)){
				node->left = left_rotation(node->left);
				return right_rotation(node);
			}
		}
		if(bf < -1){
			if(cmp(key, node->right->data)){
				return left_rotation(node);
			}else if (cmp(node->right->data, key)){
				node->right = right_rotation(node->right);
				return left_rotation(node);
			}
		}
		return node;
	}

	Avl* left_rotation(Avl* node){
		Avl* temp1 = node->right;
		Avl* temp2 = temp1->left;

		temp1->left = node;
		node->right = temp2;

		node->height = 1+ max(heightOfNode(node->left), heightOfNode(node->right));
		temp1->height = 1+ max(heightOfNode(temp1->left), heightOfNode(temp1->right));

		return temp1;
	}

	Avl* right_rotation(Avl* node){
		Avl* temp1 = node->left;
		Avl* temp2 = temp1->right;

		temp1->right = node;
		node->left = temp2;

		node->height = 1+ max(heightOfNode(node->left), heightOfNode(node->right));
		temp1->height = 1+ max(heightOfNode(temp1->left), heightOfNode(temp1->right));

		return temp1;
	}

	void inorder(Avl* node){
		if(node!= NULL){
			inorder(node->left);
			cout << node->data << " ";
			inorder(node->right);
		}
	}

	bool search(Avl* node,T key){
		if(node==NULL){
			return false;
		}
		// if(node->data == key){
		if(!cmp(key,node->data) && !cmp(node->data, key)){
			return true;
		}
		// if(node->data < key)
		if(cmp(key,node->data))
			return search(node->right, key);

		return search(node->left, key);
	}

	Avl* delete_element(Avl* node, T key){
		if(node==NULL)
			return node;
		else if(cmp(node->data, key))
			node->left = delete_element(node->left, key);
		else if(cmp(key,node->data))
			node->right = delete_element(node->right, key);
		else{
			if(node->count > 1){
				node->count--;
			// cout << "decreasing count :" << node->count << " dta: " << node->data <<endl; 
				return node;
			}
			if(node->left == NULL || node->right == NULL){
				Avl* temp;
				if(node->left ==NULL)
					temp = node->right;
				else
					temp = node->left;

				if(temp==NULL){
					temp = node;
					node = NULL;
				}else
				*node = *temp;			
				delete temp;
			}
			else{
				Avl* temp = inorderSuccessor(node->right);
				node->data = temp->data;
				node->count = temp->count;
				temp->count = 1;
				node->right = delete_element(node->right, temp->data);
			}	
		} 

		if(node==NULL)
			return node;

		node->height = 1+ max(heightOfNode(node->left), heightOfNode(node->right));

		int bf = balanceFactor(node);

		if(bf>1){
			if(balanceFactor(node->left) >= 0)
				return right_rotation(node);
			else{
				node->left = left_rotation(node->left);
				return right_rotation(node);
			}
		}

		if(bf<-1){
			if(balanceFactor(node->right) <= 0)
				return left_rotation(node);
			else{
				node->right = right_rotation(node->right);
				return left_rotation(node);
			}
		}
		return node;
	}

	Avl* search_element(Avl* node, T key){
		if(node==NULL){
			return node;
		}
		if(!cmp(key,node->data) && !cmp(node->data, key)){
			return node;
		}
		if(cmp(key,node->data))
			return search_element(node->right, key);

		return search_element(node->left, key); 
	}

	int count_occurrences(Avl* node, T key){
		Avl* temp = search_element(node, key);
		if(temp!=NULL)
			return temp->count;
		else
			return 0;
	}

	Avl* inorderSuccessor(Avl* node){
		Avl* curr_node = node;
		while(curr_node->left!=NULL){
			curr_node = curr_node->left;
		}
		return curr_node;
	}

	T lower_bound(Avl* node, T key){
		if(node->left == NULL && node->right == NULL && cmp(key,node->data))
			return -1;

		if((cmp(node->data, key) || (!cmp(key, node->data)  && !cmp(node->data, key))) && (node->left==NULL || cmp(key, node->left->data)))
			return node->data;

		if(cmp(node->data, key))
			return lower_bound(node->left, key);

		else
			return lower_bound(node->right, key);
	}

	T upper_bound(Avl* node, T key){
		if(node->left == NULL && node->right == NULL && (cmp(key, node->data) || (!cmp(key, node->data)  && !cmp(node->data, key))))			
			return -1;

		if(cmp(node->data, key) && (node->left==NULL || (cmp(key,node->left->data) || (!cmp(key,node->left->data) && !cmp(node->left->data, key)))))
			return node->data;

		if(cmp(node->data, key))
			return upper_bound(node->left, key);

		else
			return upper_bound(node->right, key);
	}

	T kth_largest(Avl* node, int key){
		if (node == NULL) 
			return 0; 

		int ans = root->right_count + 1; 
		if (ans == key) 
			return node->data; 

		if (ans > key) 
			return kth_largest(node->right, key); 

		return kth_largest(root->left, key-ans);
	}

	T k_Largest(Avl* node, int key){
		int count=0, ans=INT_MAX,flag=0;
		k_l_helper(node, key, count,ans,flag);
		return ans;
	}

	void k_l_helper(Avl* node, int key, int &count, int &ans, int &flag){
		if(node==NULL || count>=key)
			return ;
		k_l_helper(node->right, key, count,ans, flag);
		count += node->count;
		if(count>=key && flag==0){
			flag=1;
			ans =  node->data;
			return;
		}

		k_l_helper(node->left, key, count, ans, flag);
	}

	T closestElement(Avl* node, T key){
		int ans = INT_MAX;
		int minDistance = INT_MAX;
		Avl* root = node;
		while(root != NULL){
			int distance = abs(root->data - key);
			if(distance < minDistance){
				minDistance = distance;
				ans = root->data;
			}
			else if(distance == minDistance){
				ans = min(ans, root->data);
			}

			if(distance == 0)
				break;

			if(cmp(root->data, key))
				root = root->left;
			else if(cmp(key,root->data))
				root = root->right;
		}
		return ans;
	}

	int rangeQuery(Avl* node, T start, T end){
		if(node==NULL)
			return 0;
		// if(node->data ==start && node->data ==end)
		if(!cmp(node->data, end) && !cmp(end, node->data) && !cmp(node->data, start) && !cmp(start, node->data))
			return 1;
		// if(node->data >=start && node->data <=end)
		if(((!cmp(node->data, start) && !cmp(start, node->data)) || cmp(node->data, start)) && ((!cmp(node->data, end) && !cmp(end, node->data))||cmp(end, node->data)))
			return node->count+rangeQuery(node->left, start, end) + rangeQuery(node->right, start, end);
		else if(cmp(node->data, end))
			return rangeQuery(node->left, start, end);
		else
			return rangeQuery(node->right, start, end);
	}
};


int main(){

	// AvlTree<string	, Greater<string>> t;
	// t.root = t.insert(t.root, "sfaf");
	// t.root = t.insert(t.root, "sghhddf");
	// t.root = t.insert(t.root, "sfsgaf");
	// t.root = t.insert(t.root, "sfafgfgf");
	// t.root = t.insert(t.root, "sfaf");
	// t.root = t.insert(t.root, "sfagff");
	// t.root = t.insert(t.root, "sfaf");  

	// cout << "inorder traversal of the constructed AVL tree is \n";  
	// t.inorder(t.root);
	// cout << endl;


	// cout << t.search(t.root, "sfafgfgf") << endl;
	// cout << t.search(t.root, "sfgnnfdaf") << endl;

	// cout << t.count_occurrences(t.root, "sfaf")<<endl;
	// cout << t.count_occurrences(t.root, "sfagff")<<endl;
	// t.root = t.delete_element(t.root, "sfafgfgf");
	// t.root = t.delete_element(t.root, "sfaf");
	// t.root = t.delete_element(t.root, "sfaf");
	// t.root = t.delete_element(t.root, "sfaf");
	// cout << t.count_occurrences(t.root, "sfaf")<<endl;
	// t.root = t.delete_element(t.root, "sfagff");
	// cout << t.count_occurrences(t.root, "sfagff")<<endl;

	// cout << "After deleting " << endl;
	// t.inorder(t.root);
	// cout << endl;

	AvlTree<int, Greater<int>> t;
	t.root = t.insert(t.root, 34);  
	t.root = t.insert(t.root, 32); 
	t.root = t.insert(t.root, 65);  
	t.root = t.insert(t.root, 21);  
	t.root = t.insert(t.root, 36);  
	t.root = t.insert(t.root, 87);  
	t.root = t.insert(t.root, 32);
	t.root = t.insert(t.root, 65);  
	t.root = t.insert(t.root, 87);  
	t.root = t.insert(t.root, 32);
	t.root = t.insert(t.root, 65);
	t.root = t.insert(t.root, 87);  
	// t.root = t.insert(t.root, 92);
	t.root = t.insert(t.root, 65);
	t.root = t.insert(t.root, 87);  
	cout << "inorder traversal of the constructed AVL tree is \n";  
	t.inorder(t.root);
	cout << endl;
	cout << t.search(t.root, 25) << endl;
	cout << t.search(t.root, 29) << endl;
	cout << endl;
	cout << t.count_occurrences(t.root, 25)<<endl;
	cout << t.count_occurrences(t.root, 65)<<endl;
	cout << t.count_occurrences(t.root, 34)<<endl;
	cout << endl;
	t.root = t.delete_element(t.root, 34);
	t.root = t.delete_element(t.root, 21);
	t.root = t.delete_element(t.root, 36);
	t.root = t.delete_element(t.root, 30);
	cout << "After deleting " << endl;
	t.inorder(t.root);
	cout << endl;
	cout << t.lower_bound(t.root, 29)<<endl;
	cout << t.lower_bound(t.root, 50)<<endl;
	cout << t.lower_bound(t.root, 51)<<endl;
	cout << endl;
	cout << t.upper_bound(t.root, 29)<<endl;
	cout << t.upper_bound(t.root, 50)<<endl;
	cout << t.upper_bound(t.root, 36)<<endl;
	cout << endl;
	cout << t.rangeQuery(t.root, 10, 100)<<endl;
	cout << t.rangeQuery(t.root, 40, 60)<<endl;
	cout << t.rangeQuery(t.root, 32, 65)<<endl;
	cout <<endl;
	cout << t.closestElement(t.root,33)<<endl;
	cout << t.closestElement(t.root, 35)<<endl;
	cout << t.closestElement(t.root, 46)<<endl;
	cout <<endl;
	cout << t.k_Largest(t.root, 9)<<endl;
	cout << t.k_Largest(t.root, 10)<<endl;
	cout << t.k_Largest(t.root, 11)<<endl;
	cout << t.k_Largest(t.root, 12)<<endl;
	cout << t.k_Largest(t.root, 13)<<endl;
	cout << t.k_Largest(t.root, 14)<<endl;

	return 0;  
}