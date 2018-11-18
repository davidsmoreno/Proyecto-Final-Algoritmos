#ifndef _RBTree_hpp_
#define _RBTree_hpp_

enum Color {
	RED, BLACK
};

template <typename datatype>
class RBTree {
	private:
		struct RBTNode {
			datatype key;
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
		void fixViolation(RBTNode *root, RBTNode *node);

		/*RBTNode * sibling(RBTNode *node);
		bool isBlack(RBTNode *node);
		void remove_case1(RBTNode *node);
		void remove_case2(RBTNode *node);
		void remove_case3(RBTNode *node);
		void remove_case4(RBTNode *node);
		void remove_case5(RBTNode *node);
		void remove_case6(RBTNode *node);
		void remove_child(RBTNode *node);
		void BSTremove(RBTNode *temp);
		void remove(RBTNode *node);*/

		RBTNode * copy(RBTNode * root, RBTNode *parent = nullptr);
		void clear(RBTNode *root);
		void display(RBTNode *root, std::ostream & out, RBTNode *max) const;
		RBTNode * insert(RBTNode * &root, datatype key, RBTNode *parent = nullptr);
		RBTNode * Find(RBTNode *root, datatype key) const;

	public:
		RBTree();
		RBTree(const RBTree & rhs);
		~RBTree();
		void remove(datatype key);
		bool empty(void) const;
		void clear(void);
		size_t size(void) const;
		bool find(datatype key) const;
		void insert(datatype key);
		void display(std::ostream &out = std::cout) const;
};

#include "RBTree.cpp"

#endif //_RBTree_hpp_