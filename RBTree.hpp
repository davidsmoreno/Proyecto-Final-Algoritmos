#ifndef _RBTree_hpp_
#define _RBTree_hpp_

enum Color {
	RED, BLACK
};

template <typename keyType, typename dataType>
class RBTree {
	private:
		struct RBTNode {
			std::pair<keyType, dataType> pr;
			RBTNode *left;
			RBTNode *right;
			RBTNode *parent;
			Color color;
		};

		size_t count;
		RBTNode *root;

		RBTNode * min(RBTNode *root) const;
		RBTNode * max(RBTNode *root) const;
		RBTNode * successor(RBTNode *root) const;
		RBTNode * predecessor(RBTNode *root) const;

		void rotateLeft(RBTNode *node);
		void rotateRight(RBTNode *node);
		void fixRedRed(RBTNode *node);
		void moveDown(RBTNode *node, RBTNode *nParent);

		RBTNode * Uncle(RBTNode *node);
		RBTNode *sibling(RBTNode *node);
		bool hasRedChild(RBTNode *node);
		RBTNode *BSTreplace(RBTNode *node);
		void remove(RBTNode *v);
		void fixDoubleBlack(RBTNode *node);

		RBTNode * copy(RBTNode * root, RBTNode *parent = nullptr);
		void clear(RBTNode *root);
		void display(RBTNode *root, std::ostream & out, keyType max) const;
		RBTNode * Find(keyType key) const;

	public:
		RBTree();
		RBTree(const RBTree & rhs);
		~RBTree();
		void remove(keyType key);
		bool empty(void) const;
		void clear(void);
		size_t size(void) const;
		bool find(keyType key) const;
		void insert(keyType key, dataType data);
		void display(std::ostream &out = std::cout) const;
		RBTree<keyType, dataType> & operator=(const RBTree<keyType, dataType> & rhs);
		dataType & operator[](keyType key);
		dataType & at(keyType key);
		void swap(dataType & dt1, dataType & dt2);
};

#include "RBTree.cpp"

#endif //_RBTree_hpp_