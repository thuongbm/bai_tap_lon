#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T>
class node{
private:
	T data;
	node *left;
	node *right;
public:
	node() : left(NULL), right(NULL) {}
	node *make_node (T x){
		node *n = new node();
		n->data = x;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
	node *insert (node *root, T x){
		if ( root == NULL ){
			return make_node(x);
		}
		if (x < root->data){
			root->left = insert(root->left, x);
		}
		else if (x > root->data){
			root->right = insert(root->right, x);
		}
		return root;
	}
	void display(node *root){
		if (root != NULL){
			display(root->left);
			cout << root->data << ' ';
			display(root->right);
		}
	}
	node *min_node (node *root){
		node *temp = root;
		while (temp != NULL && temp->left != NULL){
			temp = temp->left;
		}
		return temp;
	}
	node *delete_node (node *root, T x){
		if (root == NULL) return;
		if (x < root->data){
			root->left = delete_node(root->left, x);
		}
		else if (x > root->data){
			root->right = delete_node(root->right, x);
		}
		else {
			if (root->left == NULL){
				node *temp = root->right;
				delete root;
				return temp;
			}
			if (root->right == NULL){
				node *temp = root->left;
				delete root;
				return temp;
			}
			else {
				node *temp = min_node (root->right);
				root->data = temp->data;
				root->right = delete_node(root, temp->data);
			}	
		}
		return root;
	}
	node* find (node *root, T x){
		if (root == NULL) return;
		node *tmp = root;
		while (tmp != NULL){
			if (tmp->data == x) return tmp;
			if (tmp->data > x){
				tmp = tmp->left;
			}
			if (tmp->data < x){
				tmp = tmp->right;
			}
		}
		return nullptr;
	}
	bool emty(node *root){
		return root == NULL;
	}
	T& get_data(){
		return data;
	}
};



