#ifndef _RBTree_cpp_
#define _RBTree_cpp_

#include "RBTree.hpp"

char toChar(Color & color) {
	if (color == BLACK) {
		return 'B';
	}
	return 'R';
}

template<typename keyType, typename dataType>
typename RBTree<keyType, dataType>::RBTNode * RBTree<keyType, dataType>::min(RBTree<keyType, dataType>::RBTNode *root) const{
	RBTNode *temp = root;
	if (temp != nullptr) {
		while (temp->left != nullptr) {
			temp = temp->left;
		}
	}
	return temp;
}

template<typename keyType, typename dataType>
typename RBTree<keyType, dataType>::RBTNode * RBTree<keyType, dataType>::max(RBTree<keyType, dataType>::RBTNode *root) const{
	RBTNode *temp = root;
	if (temp != nullptr) {
		while (temp->right != nullptr) {
			temp = temp->right;
		}
	}
	return temp;
}

template<typename keyType, typename dataType>
typename RBTree<keyType, dataType>::RBTNode * RBTree<keyType, dataType>::successor(RBTree<keyType, dataType>::RBTNode *root) const {
	RBTNode *temp = root;
	if (temp == nullptr) {
		return temp;
	}
	else {
		temp = temp->right;
		if (temp == nullptr) {
			return temp;
		}
		while (temp->left != nullptr) {
			temp = temp->left;
		}
		return temp;
	}
}

template<typename keyType, typename dataType>
typename RBTree<keyType, dataType>::RBTNode * RBTree<keyType, dataType>::predecessor(RBTree<keyType, dataType>::RBTNode *root) const {
	RBTNode *temp = root;
	if (temp == nullptr) {
		return temp;
	}
	else {
		temp = temp->left;
		if (temp == nullptr) {
			return temp;
		}
		while (temp->right != nullptr) {
			temp = temp->right;
		}
		return temp;
	}
}

template<typename keyType, typename dataType>
void RBTree<keyType, dataType>::rotateLeft(RBTNode *node) {
	
	RBTNode *nParent = node->right;
	if (node == root) {
		root = nParent;
	}
	moveDown(node, nParent);
	node->right = nParent->left;
	if (nParent->left != nullptr) {
		nParent->left->parent = node;
	}
	nParent->left = node;
}

template<typename keyType, typename dataType>
void RBTree<keyType, dataType>::rotateRight(RBTNode *node) {
	RBTNode *nParent = node->left;
	if (node == root) {
		root = nParent;
	}
	moveDown(node, nParent);
	node->left = nParent->right;
	if (nParent->right != nullptr) {
		nParent->right->parent = node;
	}
	nParent->right = node;
}

template<typename keyType, typename dataType>
void RBTree<keyType, dataType>::fixRedRed(RBTNode *node) {
	if (node == root) {
		node->color = Color::BLACK;
		return;
	}
	RBTNode *parent = node->parent, *grandparent = parent->parent, *uncle = Uncle(node);
	if (parent->color != Color::BLACK) {
		if (uncle != nullptr && uncle->color ==Color::RED) {
			parent->color = Color::BLACK;
			uncle->color = Color::BLACK;
			grandparent->color = Color::RED;
			fixRedRed(grandparent);
		}
		else {
			if (parent == parent->parent->left) {
				if (node == node->parent->left) {
					Color tmp = parent->color;
					parent->color = grandparent->color;
					grandparent->color = tmp;
				}
				else {
					rotateLeft(parent);
					Color tmp = node->color;
					node->color = grandparent->color;
					grandparent->color = tmp;
				}
				rotateRight(grandparent);
			}
			else {
				if (node == node->parent->left) {
					rotateRight(parent);
					Color tmp = node->color;
					node->color = grandparent->color;
					grandparent->color = tmp;
				}
				else {
					Color tmp = parent->color;
					parent->color = grandparent->color;
					grandparent->color = tmp;
				}
				rotateLeft(grandparent);
			}
		}
	}
}

template<typename keyType, typename dataType>
void RBTree<keyType, dataType>::moveDown(RBTree<keyType, dataType>::RBTNode *node, RBTree<keyType, dataType>::RBTNode *nParent) {
	if (node->parent != nullptr) {
		if (node->parent->left == node) {
			node->parent->left = nParent;
		}
		else {
			node->parent->right = nParent;
		}
	}
	nParent->parent = node->parent;
	node->parent = nParent;
}

template<typename keyType, typename dataType>
typename RBTree<keyType, dataType>::RBTNode * RBTree<keyType, dataType>::Uncle(RBTree<keyType, dataType>::RBTNode *node) {
	if (node->parent == nullptr || node->parent->parent == nullptr) {
		return nullptr;
	}
	if (node->parent->parent->left == node->parent) {
		return node->parent->parent->right;
	}
	else {
		return node->parent->parent->left;
	}
}

template<typename keyType, typename dataType>
typename RBTree<keyType, dataType>::RBTNode * RBTree<keyType, dataType>::sibling(RBTree<keyType, dataType>::RBTNode *node) {
	if (node->parent == nullptr) {
		return nullptr;
	}
	if (node->parent->left == node) {
		return node->parent->right;
	}
	return node->parent->left;
}

template<typename keyType, typename dataType>
bool RBTree<keyType, dataType>::hasRedChild(RBTree<keyType, dataType>::RBTNode *node) {
	return (node->left != nullptr && node->left->color == Color::RED) || (node->right != nullptr && node->right->color == Color::RED);
}

template<typename keyType, typename dataType>
typename RBTree<keyType, dataType>::RBTNode * RBTree<keyType, dataType>::BSTreplace(RBTree<keyType, dataType>::RBTNode *node) {
	if (node->left != nullptr && node->right != nullptr) {
		return successor(node);
	}
	if (node->left == nullptr && node->right == nullptr) {
		return nullptr;
	}
	if (node->left != nullptr) {
		return node->left;
	}
	else {
		return node->right;
	}
}

template<typename keyType, typename dataType>
void RBTree<keyType, dataType>::remove(RBTree<keyType, dataType>::RBTNode *v) {
	RBTNode *u = BSTreplace(v);
	bool uvBlack = ((u == nullptr || u->color == Color::BLACK) && (v->color == Color::BLACK));
	RBTNode *parent = v->parent;
	if (u == nullptr) {
		if (v == root) {
			root = nullptr;
		}
		else {
			if (uvBlack) {
				fixDoubleBlack(v);
			}
			else {
				if (sibling(v) != nullptr) {
					sibling(v)->color = Color::RED;
				}
			}
			if (v->parent->left == v) {
				parent->left = nullptr;
			}
			else {
				parent->right = nullptr;
			}
		}
		delete v;
		return;
	}
	if (v->left == nullptr || v->right == nullptr) {
		if (v == root) {
			v->pr = u->pr;
			v->left = v->right = nullptr;
			delete u;
		}
		else {
			if (v->parent->left == v) {
				parent->left = u;
			}
			else {
				parent->right = u;
			}
			delete v;
			u->parent = parent;
			if (uvBlack) {
				fixDoubleBlack(u);
			}
			else {
				u->color = Color::BLACK;
			}
		}
		return;
	}
	auto tmp = u->pr;
	u->pr = v->pr;
	v->pr = tmp;
	remove(u);
}

template<typename keyType, typename dataType>
void RBTree<keyType, dataType>::fixDoubleBlack(RBTree<keyType, dataType>::RBTNode *node) {
	if (node == root) {
		return;
	}
	RBTNode *sbl = sibling(node), *parent = node->parent;
	if (sbl == nullptr) {
		fixDoubleBlack(parent);
	}
	else {
		if (sbl->color == Color::RED) {
			parent->color = Color::RED;
			sbl->color = Color::BLACK;
			if (sbl->parent->left == sbl) {
				rotateRight(parent);
			}
			else {
				rotateLeft(parent);
			}
			fixDoubleBlack(node);
		}
		else {
			if (hasRedChild(sbl)) {
				if (sbl->left != nullptr && sbl->left->color == Color::RED) {
					if (sbl->parent->left == sbl) {
						sbl->left->color = sbl->color;
						sbl->color = parent->color;
						rotateRight(parent);
					}
					else {
						sbl->left->color = parent->color;
						rotateRight(sbl);
						rotateLeft(parent);
					}
				}
				else {
					if (sbl->parent->left == sbl) {
						sbl->right->color = parent->color;
						rotateLeft(sbl);
						rotateRight(parent);
					}
					else {
						sbl->right->color = sbl->color;
						sbl->color = parent->color;
						rotateLeft(parent);
					}
				}
				parent->color = Color::BLACK;
			}
			else {
				sbl->color = Color::RED;
				if (parent->color == Color::BLACK) {
					fixDoubleBlack(parent);
				}
				else {
					parent->color = Color::BLACK;
				}
			}
		}
	}
}

template<typename keyType, typename dataType>
typename RBTree<keyType, dataType>::RBTNode * RBTree<keyType, dataType>::copy(RBTree<keyType, dataType>::RBTNode *root, RBTree<keyType, dataType>::RBTNode *parent) {
	RBTNode *out = nullptr;
	if (root != nullptr) {
		out = new RBTNode;
		out->parent = parent;
		out->pr = root->pr;
		out->color = root->color;
		out->left = copy(root->left, out);
		out->right = copy(root->right, out);
	}
	return out;
}

template<typename keyType, typename dataType>
void RBTree<keyType, dataType>::clear(RBTree<keyType, dataType>::RBTNode *root) {
	if (root != nullptr) {
		RBTNode *left = root->left, *right = root->right;
		delete root;
		clear(left);
		clear(right);
	}
	count = 0;
}

template<typename keyType, typename dataType>
void RBTree<keyType, dataType>::display(RBTNode *root, std::ostream & out, keyType max) const{
	if (root != nullptr) {
		if (root->pr.first < max) {
			display(root->left, out, max);
			out << toChar(root->color) << "{" << root->pr.first << ", " << root->pr.second << "}, ";
			display(root->right, out, max);
		}
		else {
			display(root->left, out, max);
			out << toChar(root->color) << "{" << root->pr.first << ", " << root->pr.second << "}";
		}
	}
}

template<typename keyType, typename dataType>
typename RBTree<keyType, dataType>::RBTNode * RBTree<keyType, dataType>::Find(keyType key) const{
	RBTNode *temp = root;
	while (temp != nullptr) {
		if (key < temp->pr.first) {
			if (temp->left == nullptr) {
				break;
			}
			else {
				temp = temp->left;
			}
		}
		else if (key == temp->pr.first) {
			break;
		}
		else {
			if (temp->right == nullptr) {
				break;
			}
			else {
				temp =  temp->right;
			}
		}
	}
	return temp;
}

template<typename keyType, typename dataType>
RBTree<keyType, dataType>::RBTree() {
	root = nullptr;
	count = 0;
}

template<typename keyType, typename dataType>
RBTree<keyType, dataType>::RBTree(const RBTree & rhs) {
	this->root = copy(rhs.root, nullptr);
	count = rhs.count;
}

template<typename keyType, typename dataType>
RBTree<keyType, dataType>::~RBTree() {
	clear();
}

template<typename keyType, typename dataType>
bool RBTree<keyType, dataType>::remove(keyType key) {
	if (root == nullptr) {
		return false;
	}
	RBTNode *v = Find(key);
	if (v->pr.first != key) {
		return false;
	}
	remove(v);
	count--;
	return true;
}

template<typename keyType, typename dataType>
bool RBTree<keyType, dataType>::empty(void) const {
	return count == 0;
}

template<typename keyType, typename dataType>
void RBTree<keyType, dataType>::clear(void) {
	clear(root);
	root = nullptr;
	count = 0;
}

template<typename keyType, typename dataType>
size_t RBTree<keyType, dataType>::size(void) const {
	return count;
}
template<typename keyType, typename dataType>
bool RBTree<keyType, dataType>::find(keyType key) const {
	RBTNode *tmp = Find(key);
	if (tmp != nullptr && tmp->pr.first == key) {
		return true;
	}
	return false;
}

template<typename keyType, typename dataType>
bool RBTree<keyType, dataType>::insert(keyType key, dataType data) {
	RBTNode *newNode = new RBTNode;
	newNode->pr = {key, data};
	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->parent = nullptr;
	newNode->color = Color::RED;
	if (root == nullptr) {
		newNode->color = Color::BLACK;
		root  = newNode;
	}
	else {
		RBTNode *temp = Find(key);
		if (temp->pr.first == key) {
			return false;
		}
		newNode->parent = temp;
		if (key < temp->pr.first) {
			temp->left = newNode;
		}
		else {
			temp->right = newNode;
		}
		fixRedRed(newNode);
	}
	count++;
	return true;
}

template<typename keyType, typename dataType>
void RBTree<keyType, dataType>::display(std::ostream &out) const {
	RBTNode *mx = max(root);
	out << '[';
	if (mx != nullptr) {
		display(root, out, mx->pr.first);
	}
	out << "] size: " << count << "\n";
}

template<typename keyType, typename dataType>
RBTree<keyType, dataType> & RBTree<keyType, dataType>::operator=(const RBTree<keyType, dataType> & rhs) {
	this->clear();
	this->root = copy(rhs.root, nullptr);
	this->count = rhs.count;
	return *this;
}

template<typename keyType, typename dataType>
dataType & RBTree<keyType, dataType>::operator[](keyType key) {
	return at(key);
}

template<typename keyType, typename dataType>
dataType & RBTree<keyType, dataType>::at(keyType key) {
	RBTNode *temp = Find(key);
	if (temp != nullptr && temp->pr.first == key) {
		return temp->pr.second;
	}
	throw std::underflow_error("Function at(key) invoked when key wasnt in the tree");
}

template<typename keyType, typename dataType>
void RBTree<keyType, dataType>::swap(dataType & dt1, dataType & dt2) {
	dataType tmp = dt1;
	dt1 = dt2;
	dt2 = tmp;
}

#endif //_RBTree_cpp_