#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1.0)
typedef long long ll; 

const int N = 2e5+5;

template<class X>
class Node{
	X value;
	Node *left;
	Node *right;
	int height;
public:
	Node(X item){
		value = item;
		left = NULL;
		right = NULL;
		height = 1;
	}
	X getValue(){
		return value;
	}
	Node* getleft(){
		return left;
	}
	Node* getright(){
		return right;
	}
	int getHeight(){
		return height;
	}
	void setValue(X val){
		value = val;
	}
	void setleft(Node<X> *node){
		left = node;
	}
	void setright(Node<X> *node){
		right = node;
	}
	void setHeight(int h){
		height = h;
	}
};

template<class X>
class AVL{
	Node<X> *root;
public:
	AVL(){
		root = NULL;
	}
	~AVL(){
		clear(root);
	}
	Node<X> *getRoot(){
		return root;
	}
    void setRoot(Node<X> *x)
    {
        root = x;
    }
	Node<X> *get_node(X item){
		Node<X> *temp = root;
		X val;
		while(temp != NULL){
			val = temp->getValue();
			if(val == item){
				return temp;
			}
			else if(val<item){
				temp = temp->getright();
			}
			else if(val>item){
				temp = temp->getleft();
			}
		}
		return NULL;
	}
	bool Find(X item){
		Node<X> *temp = get_node(item);
		if(temp == NULL){
			return false;
		}
		else{
			return true;
		}
	}
	
	int Height(Node<X> *node){
		if(node == NULL) return 0;
		else{
            // if(node == NULL) cout<<"ee"<<endl;
            // else cout<<"nn\n";
			return node->getHeight();
		}
	}
	
	Node<X> *left_rotate(Node<X> *current){
		Node<X> *temp,*par;
		par = current->getright();
		temp = par->getleft();
		par->setleft(current);
		current->setright(temp);
		
		par->setHeight(max(Height(par->getright()),Height(par->getleft()))+1);
		current->setHeight(max(Height(current->getright()),Height(current->getleft()))+1);

		if(root == current) root = par;
		
		return par;
	}
	Node<X> *right_rotate(Node<X> *current){
		Node<X> *temp,*par;
		par = current->getleft();
		temp = par->getright();
		par->setright(current);
		current->setleft(temp);
		
		par->setHeight(max(Height(par->getright()),Height(par->getleft()))+1);
		current->setHeight(max(Height(current->getright()),Height(current->getleft()))+1);
		
		if(root == current) root = par;
		
		return par;
	}
	void in_order(Node<X> *current){
		if(current == NULL) return;
		
		in_order(current->getleft());
		cout << current->getValue() << " ";
		in_order(current->getright());
		
	}
	void pre_order(Node<X> *current){
		if(current == NULL) return;
		
		cout << current->getValue() << " ";
		pre_order(current->getleft());
		pre_order(current->getright());
	}
	void post_order(Node<X> *current){
		if(current == NULL) return;
		
		post_order(current->getleft());
		post_order(current->getright());
		cout << current->getValue() << " ";
	}
	bool isLeaf(Node<X> *p){
		return ((p->getleft() == NULL) && (p->getright() == NULL));
	}
	void print_state(Node<X> *current){
		if(current == NULL) return;
		
		cout << current->getValue() << " ";
		if(isLeaf(current)) return;
		cout << "(";
		print_state(current->getleft());
		cout << "," ; 
		print_state(current->getright());
		cout << ")";
	}
	Node<X> *Insert(Node<X> *curr,X item){
		if(root == NULL){
			root = new Node<X>(item);
			return NULL;
		}
		if(curr == NULL){
			Node<X> *node = new Node<X>(item);
			return node;
		}
		
		if(curr->getValue() < item){
			Node<X> *temp = Insert(curr->getright(),item); 
			curr->setright(temp);
		}
		else{
			Node<X> *temp = Insert(curr->getleft(),item);
			curr->setleft(temp);
		}
		
		int hl = Height(curr->getleft());
		int hr = Height(curr->getright());
		curr->setHeight(max(hl,hr)+1);
		int bf = hl - hr;
		if(bf > 1 && item < curr->getleft()->getValue()){
			return right_rotate(curr);
		}
		else if(bf > 1 && item > curr->getleft()->getValue()){
			curr->setleft(left_rotate(curr->getleft()));
			return right_rotate(curr);
		}
		else if(bf < -1 && item > curr->getright()->getValue()){
			return left_rotate(curr);
		}
		else if(bf < -1 && item < curr->getright()->getValue()){
			curr->setright(right_rotate(curr->getright()));
			return left_rotate(curr);
		}
		return curr;
	}
	Node<X> *successor(Node<X> *curr){
		while(curr->getleft() != NULL){
			curr = curr->getleft();
		}
		return curr;
	}
	int getBalanceFactor(Node<X> *curr){
		int hl = Height(curr->getleft());
		int hr = Height(curr->getright());
		return (hl-hr);
	}
	Node<X> *Delete(Node<X> *curr,X item){
		if(curr == NULL) return NULL;
		
		int val = curr->getValue();
        // cout<<"curr "<<val<<endl;
		if(val < item){
			curr->setright(Delete(curr->getright(),item));
		}
		else if(val > item){
			curr->setleft(Delete(curr->getleft(),item));
		}
		else{
			Node<X> *temp;
			if(isLeaf(curr)){
				delete curr;
                curr = nullptr;
			}
			else if(curr->getright() == NULL){
				temp = curr;
                curr = curr->getleft();
				delete temp;
			}
			else if(curr->getleft() == NULL){
				temp = curr;
                curr=curr->getright();
				delete temp;
			}
			else{
				temp = successor(curr->getright());
				curr->setValue(temp->getValue());
				curr->setright(Delete(curr->getright(),temp->getValue()));
			}
		}
		if(curr == NULL) return NULL;
		
		curr->setHeight(1+max(Height(curr->getright()),Height(curr->getleft())));
		int bf = getBalanceFactor(curr);
		
		if(bf > 1 && getBalanceFactor(curr->getleft()) >= 0){
			return right_rotate(curr);
		}
		else if(bf > 1 && getBalanceFactor(curr->getleft()) < 0){
			curr->setleft(left_rotate(curr->getleft()));
			return right_rotate(curr);
		}
		else if(bf < -1 && getBalanceFactor(curr->getright()) <= 0){
			return left_rotate(curr);
		}
		else if(bf < -1 && getBalanceFactor(curr->getright()) > 0){
			curr->setright(right_rotate(curr->getright()));
			return left_rotate(curr);
		}
        // cout<<"curr "<<val<<endl;
		
		return curr;
	}
	void clear(Node<X> *current){
		if(current == NULL) return;
		
		clear(current->getleft());
		clear(current->getright());
		free(current);
	}
};

int main(){
	freopen("in.txt","r",stdin);
	freopen("out_avl.txt","w",stdout);
	AVL<int> a;
	char s[2];
	int val;
	while(!feof(stdin)){
		scanf("%s %d",s,&val);
		if(s[0] == 'I'){
			if(!a.Find(val)){
				a.Insert(a.getRoot(),val);
				a.print_state(a.getRoot());
				cout << "\n";
			}
			else{
				cout << val << " is already in AVL." << "\n";
			}
		}
		else if(s[0] == 'D'){
			if(a.Find(val)){
				a.setRoot(a.Delete(a.getRoot(),val));
				a.print_state(a.getRoot());
				cout << "\n";
			}
			else{
				cout << val << " is not in AVL." << "\n";
			}
		}
		else if(s[0] == 'F'){
			if(a.Find(val)){
				cout << "Found\n"; 
			}
			else{
				cout << "Not Found\n";
			}
		}
		else if(s[0] == 'T'){
			a.in_order(a.getRoot());
		}
	}
}