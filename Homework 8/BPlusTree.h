/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <algorithm>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
// DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode {
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	} else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
// Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T> class BPlusTree {
public:
    BPlusTree(int num);
    BPlusTree(const BPlusTree<T>& old) { root = this->copy_tree(old.root); }
	~BPlusTree() { this->destroy_tree(root);  root=NULL; }
	void insert(const T& key);
	BPlusTreeNode<T>* find(T key) { return find1(key, root); }
	void print_BFS(std::ostream& ostr) { printBFS(ostr, root); }
	void print_sideways(std::ostream& ostr) { printsideways(ostr, root, 0); }

private:
	// Private Member Variables
    int max_children;
    BPlusTreeNode<T>* root;

	// Private Functions
	BPlusTreeNode<T>* find1(T key, BPlusTreeNode<T>* root);
    int insertion_point(const T& key, std::size_t low, std::size_t high, BPlusTreeNode<T>* p); // helper function that finds which number node to insert
	BPlusTreeNode<T>* find_node(BPlusTreeNode<T>* p, const T & key); // helper function that finds which node to insert to
	void split_node(BPlusTreeNode<T>* p); // helper function that splits when necessary
	void printBFS(std::ostream& ostr, BPlusTreeNode<T>* p);
	void printsideways(std::ostream& ostr, BPlusTreeNode<T>* p, int depth);
	BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old) {
		if (!old) {
			return NULL;
		}
		BPlusTreeNode<T>* nroot = new BPlusTreeNode<T>();
		for (int i=0; i<old->keys.size(); i++) {
			nroot->keys.push_back(old->keys[i]);
		}
		for (int j=0; j<old->children.size(); j++) {
			if (old->children[j]!=NULL) {
				nroot->children[j]=copy_tree(old->children[j]); // recursive call to opy the other branches
			}
		}
		return nroot;
	}

	void destroy_tree(BPlusTreeNode<T>* root) {
		if (!root) {
			return;
		}
		for (int i=0; i<root->children.size(); i++) {
			return destroy_tree(root->children[i]);
		}
		delete root;
	}
};

template <class T> BPlusTreeNode<T>* BPlusTree<T>::find1(T key, BPlusTreeNode<T>* root) {
	if (root==NULL) {
		return NULL;
	} else {
		if (root->is_leaf()) {
			return root;
		} else {
			for (int i=0; i<root->keys.size(); i++) {
				if (root->keys[i] > key) {
					return find1(key, root->children[i]);
				} else {
					return find1(key, root->children[i+1]);
				}
			}
		}
	}
	return NULL;
}

template <class T> int BPlusTree<T>::insertion_point(const T& key, std::size_t low, std::size_t high, BPlusTreeNode<T>* p) {
	// this function will return the number of the child to insert
    if (low>high) {
		return low;
	}
	if (low==high) { 
		return low;
	}
	std::size_t mid = (low+high)/2;
	if (key<=root->keys[mid]) {
		return insertion_point(key,0,mid,p);
	} else {
		return insertion_point(key,mid+1,high,p);
	}
}

template <class T> BPlusTreeNode<T>* BPlusTree<T>::find_node(BPlusTreeNode<T>* p, const T & key) {
	// this function returns apointer to the node we want to insert to
    if (p->is_leaf()) { // checking to make sure we only insert in leafs
        return p;
    } else {
        return find_node(p->children[insertion_point(key,0,p->keys.size(),p)], key);
    }
}

template <class T> void BPlusTree<T>::split_node(BPlusTreeNode<T>* p) {
	// helper function for insert that deals with splitting the nodes when needed.
    if (p->keys.size()==max_children) {
        if (p==root) { // creating two new children to split
            BPlusTreeNode<T>* node1 = new BPlusTreeNode<T>();
            BPlusTreeNode<T>* node2 = new BPlusTreeNode<T>();
			int num = p->keys.size()/2;
			for (int i=0; i<p->keys.size(); i++) { 
				if (i<num) {
					node1->keys.push_back(p->keys[i]);
				} else {
					node2->keys.push_back(p->keys[i]);
				}
            }
			root->children.push_back(node1);
			root->children.push_back(node2);
			root->keys.clear();
			for (int j=1; j<root->children.size(); j++) {
				root->keys.push_back(root->children[j]->keys[0]);
			}
        } else {
			if (root->children.size()!=max_children) { // creating a new child
				BPlusTreeNode<T>* node1 = new BPlusTreeNode<T>();
				int num = p->keys.size()/2;
				for (int i=0; i<p->keys.size(); i++) { 
					if (i>num) {
						node1->keys.push_back(p->keys[i]);
					}
				}
				p->keys.erase(p->keys.begin()+(max_children-1));
				root->children.push_back(node1);
				sort(root->children.begin(), root->children.end());
				root->keys.clear();
				for (int j=1; j<root->children.size(); j++) {
					root->keys.push_back(root->children[j]->keys[0]);
				}
				sort(root->keys.begin(), root->keys.end());
			} else { // split a child into two new nodes
				BPlusTreeNode<T>* node1 = new BPlusTreeNode<T>();
            	BPlusTreeNode<T>* node2 = new BPlusTreeNode<T>();
				int num = p->keys.size()/2;
				for (int i=0; i<p->keys.size(); i++) { 
					if (i<num) {
						node1->keys.push_back(p->keys[i]);
					} else {
						node2->keys.push_back(p->keys[i]);
					}
            	}
				p->children.push_back(node1);
				p->children.push_back(node2);
				p->keys.clear();
				for (int j=1; j<p->children.size(); j++) {
					p->keys.push_back(p->children[j]->keys[0]);
				}
			}
		}
    }
}

template <class T> BPlusTree<T>::BPlusTree(int num) {
    max_children = num;
    root = NULL;
}

template <class T> void BPlusTree<T>::insert(const T& key) {
    if (root == NULL) { // creating new pointer and inserting to keys
        root = new BPlusTreeNode<T>();
        root->keys.push_back(key);
    } else {
        BPlusTreeNode<T>* node = find_node(root,key);
        int num = insertion_point(key,0,node->keys.size(),node);
        node->keys.insert(node->keys.begin()+num,key); // inserting key into desired node from previous function calls
		sort(node->keys.begin(), node->keys.end());
		if (node->keys.size()==max_children) {
			split_node(node); // split function call if the node exceeds order limit
		}
    } 
}

template <class T> void BPlusTree<T>::printsideways(std::ostream& ostr, BPlusTreeNode<T>* p, int depth) {
	if (p==NULL) {
		ostr << "Tree is empty." << std::endl; 
	} else {
		for (int i=0; i<p->children.size()/2; i++) { // looping thorugh the first half of the tree
			printsideways(ostr, p->children[i], depth+1);
		}
    	for (int i=0; i<depth; i++) {
			ostr << "    ";
		} 
    	int num = p->keys.size();
		for (int i=0; i<num; i++) { // printing root
			if (i==num-1) {
				ostr << p->keys[i] << std::endl;
			} else {
				ostr << p->keys[i] << ",";
			}
		}
		for (int i=p->children.size()/2; i<p->children.size(); i++) { // looping through second half
			printsideways(ostr, p->children[i], depth+1);
		}
	}
}

template <class T> void BPlusTree<T>::printBFS(std::ostream& ostr, BPlusTreeNode<T>* p) {
	if (p==NULL) { // handling an empty tree
		ostr << "Tree is empty." << std::endl;
	} else {
		int num = p->keys.size();
		for (int i=0; i<num; i++) { // printing the root
			if (i==num-1) {
				ostr << p->keys[i] << std::endl;
			} else {
				ostr << p->keys[i] << ",";
			}
		}
		if (p->children.size()>0) { // printing out the children keys
			for (int j=0; j<p->children.size(); j++) {
				for (int k=0; k<p->children[j]->keys.size(); k++) {
					if (k!=(p->children[j]->keys.size())-1) {
						ostr << p->children[j]->keys[k] << ",";
					} else {
						ostr << p->children[j]->keys[k];
					}
				}
				if (j<p->children.size()-1) {
					ostr << "\t";
				} else {
					ostr << std::endl;
				}
			}
		}
	}
}
#endif
