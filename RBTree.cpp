#ifndef _RBTree_cpp_
#define _RBTree_cpp_

#include "RBTree.hpp"

char toString(Color & color) {
	if (color == BLACK) {
		return 'B';
	}
	return 'R';
}

template<typename datatype>
typename RBTree<datatype>::RBTNode * RBTree<datatype>::min(RBTree<datatype>::RBTNode *root) const{
	RBTNode *temp = root;
	if (temp != nullptr) {
		while (temp->left != nullptr) {
			temp = temp->left;
		}
	}
	return temp;
}

template<typename datatype>
typename RBTree<datatype>::RBTNode * RBTree<datatype>::max(RBTree<datatype>::RBTNode *root) const{
	RBTNode *temp = root;
	if (temp != nullptr) {
		while (temp->right != nullptr) {
			temp = temp->right;
		}
	}
	return temp;
}

template<typename datatype>
typename RBTree<datatype>::RBTNode * RBTree<datatype>::successor(RBTree<datatype>::RBTNode *root) const {
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

template<typename datatype>
typename RBTree<datatype>::RBTNode * RBTree<datatype>::predecessor(RBTree<datatype>::RBTNode *root) const {
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

template<typename datatype>
void RBTree<datatype>::rotateLeft(RBTNode *node) {
	RBTNode **aux = &root;
	if (node->parent != nullptr && node->parent->right == node) {
		aux = &(node->parent->right);
	}
	else if (node->parent != nullptr && node->parent->left == node) {
		aux = &(node->parent->left);
	}
	*aux = node->right;
	(*aux)->parent = node->parent;
	node->parent = *aux;
	node->right = (*aux)->left;
	(*aux)->left = node;
	if (node->right != nullptr) {
		node->right->parent = node;
	}
}

template<typename datatype>
void RBTree<datatype>::rotateRight(RBTNode *node) {
	RBTNode **aux = &root;
	if (node->parent != nullptr && node->parent->right == node) {
		aux = &(node->parent->right);
	}
	else if (node->parent != nullptr && node->parent->left == node) {
		aux = &(node->parent->left);
	}
	*aux = node->left;
	(*aux)->parent = node->parent;
	node->parent = *aux;
	node->left = (*aux)->right;
	(*aux)->right = node;
	if (node->left != nullptr) {
		node->left->parent = node;
	}
}

template<typename datatype>
void RBTree<datatype>::fixViolation(RBTNode *root, RBTNode *node) {
	RBTNode *parent = nullptr, *grandparent = nullptr;
	while ((node != root) && (node->color != Color::BLACK) && (node->parent->color == Color::RED)) {
		parent = node->parent;
		grandparent = node->parent->parent;
		if (parent == grandparent->left) {
			RBTNode *uncle = grandparent->right;
			if (uncle != nullptr && uncle->color == Color::RED) {
				grandparent->color = Color::RED;
				parent->color = Color::BLACK;
				uncle->color = Color::BLACK;
				node = grandparent;
			}
			else {
				if (node == parent->right) {
					rotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				rotateRight(grandparent);
				Color temp = parent->color;
				parent->color = grandparent->color;
				grandparent->color = temp;
				node = parent;
			}
		}
		else {
			RBTNode *uncle = grandparent->left;
			if ((uncle != nullptr) && (uncle->color == Color::RED)) {
				grandparent->color = Color::RED;
				parent->color = Color::BLACK;
				uncle->color = Color::BLACK;
				node = grandparent;
			}
			else {
				if (node == parent->left) {
					rotateRight(parent);
					node = parent;
					parent =node->parent;
				}
				rotateLeft(grandparent);
				Color temp = parent->color;
				parent->color = grandparent->color;
				grandparent->color = temp;
				node = parent;
			}
		}
	}
	root->color =  Color::BLACK;
}

/*template<typename datatype>
typename RBTree<datatype>::RBTNode * RBTree<datatype>::sibling(RBTree<datatype>::RBTNode *node) {
	if (node->parent != nullptr) {
		if (node == node->parent->left) {
			return node->parent->right;
		}
		return node->parent->left;
	}
	return nullptr;
}

template<typename datatype>
bool RBTree<datatype>::isBlack(RBTree<datatype>::RBTNode *node) {
	if (node == nullptr) {
		return true;
	}
	else {
		return node->color == Color::BLACK;
	}
}

template<typename datatype>
void RBTree<datatype>::remove_case1(RBTree<datatype>::RBTNode *node) {
	if (node->parent != nullptr) {
		remove_case2(node);
	}
}

template<typename datatype>
void RBTree<datatype>::remove_case2(RBTree<datatype>::RBTNode *node) {
	RBTNode *sbl = sibling(node);
	if (!isBlack(sbl)) {
		node->parent->color = Color::RED;
		sbl->color = Color::BLACK;
		if (node == node->parent->left) {
			rotateLeft(node->parent);
		}
		else {
			rotateRight(node->parent);
		}
	}
	remove_case3(node);
}

template<typename datatype>
void RBTree<datatype>::remove_case3(RBTree<datatype>::RBTNode *node) {
	RBTNode *sbl = sibling(node);
	if (isBlack(node->parent) && isBlack(sbl) && isBlack(sbl->left) && isBlack(sbl->right)) {
		sbl->color = Color::RED;
		remove_case1(node->parent);
	}
	else {
		remove_case4(node);
	}
}

template<typename datatype>
void RBTree<datatype>::remove_case4(RBTree<datatype>::RBTNode *node) {
	RBTNode *sbl = sibling(node);
	if (!isBlack(node->parent) && isBlack(sbl) && isBlack(sbl->left) && isBlack(sbl->right)) {
		sbl->color = Color::RED;
		node->parent->color = Color::BLACK;
	}
	else {
		remove_case5(node);
	}
}

template<typename datatype>
void RBTree<datatype>::remove_case5(RBTree<datatype>::RBTNode *node) {
	RBTNode *sbl = sibling(node);
	if (node == node->parent->left && isBlack(sbl) && !isBlack(sbl->left) && isBlack(sbl->right)) {
		sbl->color = Color::RED;
		if (!isBlack(sbl->left)) {
			sbl->left->color = Color::BLACK;
		}
		rotateRight(sbl);
	}
	else if (node == node->parent->right && isBlack(sbl) && !isBlack(sbl->left) && isBlack(sbl->right)) {
		sbl->color = Color::RED;
		if (!isBlack(sbl->right)) {
			sbl->right->color = Color::BLACK;
		}
		rotateLeft(sbl);
	}
	remove_case6(node);
}

template<typename datatype>
void RBTree<datatype>::remove_case6(RBTree<datatype>::RBTNode *node) {
	RBTNode *sbl = sibling(node);
	sbl->color = node->parent->color;
	node->parent->color = Color::BLACK;
	if (node == node->parent->left) {
		sbl->right->color = Color::BLACK;
		rotateLeft(node->parent);
	}
	else {
		sbl->left->color = Color::BLACK;
		rotateRight(node->parent);
	}
}

template<typename datatype>
void RBTree<datatype>::remove_child(RBTree<datatype>::RBTNode *node) {
	RBTNode *child = (node->right == nullptr) ? node->left : node->right;
	child->parent = node->parent;
	if (node->parent->left == node) {
		node->parent->left = child;
	}
	else {
		node->parent->right = child;
	}
	if (node->color == Color::BLACK) {
		if (child->color == Color::RED) {
			child->color = Color::BLACK;
		}
		else {
			remove_case1(child);
		}
	}
	delete node;
}

template<typename datatype>
void RBTree<datatype>::BSTremove(RBTree<datatype>::RBTNode *temp) {
	RBTNode *other = temp;
	datatype key = temp->key;
	if (temp != nullptr) {
		if (temp->left == nullptr && temp->right == nullptr) {
			temp = temp->parent;
			if (temp != nullptr) {
				if (temp->left == other) {
					temp->left = nullptr;
				}
				else if (temp->right == other) {
					temp->right = nullptr;
				}
			}
			else {
				this->root = nullptr;
			}
			delete other;
		}
		else if (temp->left == nullptr && temp->right != nullptr) {
			temp = temp->parent;
			if (temp != nullptr) {
				if (key < temp->key) {
					temp->left = other->right;
				}
				else if (key > temp->key) {
					temp->right = other->right;
				}
			}
			else {
				this->root = other->right;
				this->root->parent = nullptr;
			}
			delete other;
		}
		else if (temp->left != nullptr && temp->right == nullptr) {
			temp = temp->parent;
			if (temp != nullptr) {
				if (key < temp->key) {
					temp->left = other->left;
				}
				else if (key > temp->key) {
					temp->right = other->left;
				}
			}
			else {
				this->root = other->left;
				this->root->parent = nullptr;
			}
			delete other;
		}
		else {
			RBTNode *other2 = predecessor(other);
			other->key = other2->key;
			remove(other2);
		}
	}
}

template<typename datatype>
void RBTree<datatype>::remove(RBTree<datatype>::RBTNode *node) {
	if (node != nullptr) {
		if (node->left != nullptr && node->right != nullptr) {
			RBTNode *temp = predecessor(node);
			node->key = temp->key;
			remove(temp);
		}
		else if ((node->left == nullptr && node->right != nullptr) || (node->left != nullptr && node->right == nullptr)) {
			if (node->color == Color::BLACK) {
				remove_child(node);
			}
			else {
				BSTremove(node);
			}
		}
		else {
			if (node->color == Color::RED) {
				BSTremove(node);
			}
			else {
				remove_child(node);
			}
		}
	}
}*/

template<typename datatype>
typename RBTree<datatype>::RBTNode * RBTree<datatype>::copy(RBTree<datatype>::RBTNode * root, RBTree<datatype>::RBTNode *parent) {
	RBTNode *out = nullptr;
	if (root != nullptr) {
		out = new RBTNode;
		out->parent = parent;
		out->key = root->key;
		out->left = copy(root->left, out);
		out->right = copy(root->right, out);
		out->color = root->color;
	}
	return out;
}

template<typename datatype>
void RBTree<datatype>::clear(RBTree<datatype>::RBTNode *root) {
	if (root != nullptr) {
		RBTNode *left = root->left, *right = root->right;
		delete root;
		clear(left);
		clear(right);
	}
}

template<typename datatype>
void RBTree<datatype>::display(RBTNode *root, std::ostream & out, RBTNode *max) const {
	datatype mx = max->key;
	if (root != nullptr) {
		if (root->key != mx) {
			display(root->left, out, max);
			out << toString(root->color) << "_" << root->key << ", ";
			display(root->right, out, max);
		}
		else {
			out << toString(root->color) << "_" << root->key;
		}
	}
}

template<typename datatype>
typename RBTree<datatype>::RBTNode * RBTree<datatype>::insert(RBTree<datatype>::RBTNode * &root, datatype key, RBTree<datatype>::RBTNode *parent) {
	if (root == nullptr) {
		root = new RBTNode;
		root->key = key;
		root->parent = parent;
		root->left = nullptr;
		root->right = nullptr;
		root->color = Color::RED;
		return root;
	}
	else {
		if (key < root->key) {
			return insert(root->left, key, root);
		}
		else if (key > root->key) {
			return insert(root->right, key, root);
		}
		return nullptr;
	}
}

template<typename datatype>
typename RBTree<datatype>::RBTNode * RBTree<datatype>::Find(RBTree<datatype>::RBTNode *root, datatype key) const{
	if (root == nullptr) {
		return nullptr;
	}
	else {
		if (key == root->key) {
			return root;
		}
		else if (key < root->key) {
			return Find(root->left, key);
		}
		else {
			return Find(root->right, key);
		}
	}
}

template<typename datatype>
RBTree<datatype>::RBTree() {
	root = nullptr;
	count = 0;
}

template<typename datatype>
RBTree<datatype>::RBTree(const RBTree & rhs) {
	this->root = copy(rhs.root, nullptr);
	count = rhs.count;
}

template<typename datatype>
RBTree<datatype>::~RBTree() {
	clear();
}

template<typename datatype>
void RBTree<datatype>::remove(datatype key) {
	if (find(key)) {
		remove(Find(root, key));
	}
}

template<typename datatype>
bool RBTree<datatype>::empty(void) const {
	return count == 0;
}

template<typename datatype>
void RBTree<datatype>::clear(void) {
	clear(root);
	root = nullptr;
	count = 0;
}

template<typename datatype>
size_t RBTree<datatype>::size(void) const {
	return count;
}
template<typename datatype>
bool RBTree<datatype>::find(datatype key) const {
	if (Find(root, key) == nullptr) {
		return false;
	}
	return true;
}

template<typename datatype>
void RBTree<datatype>::insert(datatype key) {
	if (!find(key)) {
		fixViolation(root, insert(root, key, nullptr));
		count++;
	}
}

template<typename datatype>
void RBTree<datatype>::display(std::ostream &out) const {
	out << "[";
	display(root, out, max(root));
	out << "]\n";
}

#endif //_RBTree_cpp_