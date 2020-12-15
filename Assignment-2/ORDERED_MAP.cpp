#include<bits/stdc++.h>
using namespace std;

bool max(int a, int b){
	if(a>b)
		return a;
	return b;
}

template <class T, class U> 
class Ordered_map{
private:
	struct Avl{
		T key;
		U value;
		Avl* right;
		Avl* left;
		int height;
	};
public:
	int sizeOfMap;
	Avl* root;
	Ordered_map()
	{
		root = NULL;
		sizeOfMap = 0;
	}
	Avl* newNode(T key, U value){
		Avl* node = new Avl();	
		node->key = key;
		node->value = value;
		node->left = NULL;
		node->right = NULL;
		node->height = 1;
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
	
	Avl* insert_avl(Avl* node,  T key, U value){
		if (node == NULL){
			sizeOfMap++;
			return (newNode(key,value));
		}
		else if(key > node->key){
			node->right = insert_avl(node->right, key, value);
		}
		else if(key < node->key)
			node->left = insert_avl(node->left, key, value);
		else if(key == node->key){
			node->value = value;
			return node;
		}

		node->height = 1+ max(heightOfNode(node->left), heightOfNode(node->right));

		int bf = balanceFactor(node);
		if(bf > 1){
			if(key < node->left->key){
				return right_rotation(node);
			}else if (key > node->left->key){
				node->left = left_rotation(node->left);
				return right_rotation(node);
			}
		}
		if(bf < -1){
			if(key > node->right->key){
				return left_rotation(node);
			}else if (key < node->right->key){
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
			cout << "("<< node->key << "," << node->value << ")" << " ; ";
			inorder(node->right);
		}
	}

	bool search_avl(Avl* node,T key){
		if(node==NULL){
			return false;
		}
		if(node->key == key){

			return true;
		}
		if(node->key < key)
			return search_avl(node->right, key);

		return search_avl(node->left, key);
	}

	Avl* delete_avl(Avl* node, T key){
		if(node==NULL)
			return node;
		else if(key < node->key)
			node->left = delete_avl(node->left, key);
		else if(key > node->key)
			node->right = delete_avl(node->right, key);
		else{
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
				sizeOfMap--;
			}
			else{
				Avl* temp = inorderSuccessor(node->right);
				node->key = temp->key;
				node->value = temp->value;
				node->right = delete_avl(node->right, temp->key);
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

	Avl* search_avl_element(Avl* node, T key){
		if(node==NULL){
			return node;
		}
		if(node->key == key){
			return node;
		}
		if(node->key < key)
			return search_avl_element(node->right, key);

		return search_avl_element(node->left, key); 
	}

	Avl* inorderSuccessor(Avl* node){
		Avl* curr_node = node;
		while(curr_node->left!=NULL){
			curr_node = curr_node->left;
		}
		return curr_node;
	}

	void deleteAvlTree(Avl* node)  
	{  
		if (node == NULL) return;  
		deleteAvlTree(node->left);  
		deleteAvlTree(node->right);  
		delete node; 
	}

	int size(){
		return sizeOfMap;
	}

	void insert(T key, U value){
		root = insert_avl(root, key, value);
	}

	bool find(T key){
		return search_avl(root, key);
	}

	void erase(T key){
		root = delete_avl(root, key);
	}

	void clear(){
		deleteAvlTree(root);
	}

	void printMap(){
		inorder(root);
	}

	U& operator[](T key){
		U x;
		Avl* temp = search_avl_element(root, key);
		if(temp == NULL){
			// cout << "key not found\n";
			root = insert_avl(root, key, x);
			temp = search_avl_element(root, key);
		}
		return temp->value;
	}
};


int main(){

	Ordered_map<string, string> om;
	string key, value;

	om.insert("ritvik", "eeeee");
	om.insert("garg", "wwwwww");
	om.insert("gaga", "qqqqqqq");
	om.insert("ritvik", "aaaa");
	om.insert("fafa", "zzzzzz");
	cout << endl;

	cout << "size of tree : " << om.size()<<endl;

	cout << om.find("ritvik") << endl;
	cout << om.find("garg") << endl;
	cout << om.find("ritafgsvik") << endl;
	cout << endl;

	cout << "inorder traversal of the constructed AVL tree is \n";  
	om.printMap();
	cout << endl;

	om.erase("ritvik");
	om.erase("garg");
	om.erase("gaga");
	om.erase("gagasda");
	cout << endl;

	cout << "size of tree : " << om.size()<<endl;

	cout << "inorder traversal of the constructed AVL tree after deletion: \n";  
	om.printMap();
	cout << endl;

	om.erase("ritvik");
	om.erase("garg");
	om.erase("gaga");
	om.erase("gagasda");
	cout << endl;

	om["ritvik"] = "ppppppp";
	cout << "ritvik : " << om["ritvik"] << endl;
	om["ritvik"] = "llllllllllp";
	om["fafa"] = "ssssss";
	cout << "fafa : " << om["fafa"] << endl;
	cout << "ritvik : " << om["ritvik"] << endl;

	cout << "size of tree : " << om.size()<<endl;

	om.clear();
	cout << "ritvik : " << om["ritvik"] << endl;
	return 0; 
}