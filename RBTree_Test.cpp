#include <iostream>
#include "RBTree.hpp"

using namespace std;

int main() {
	RBTree<int> mytree;
	mytree.insert(1);
	mytree.insert(11);
	mytree.insert(17);
	mytree.insert(13);
	mytree.insert(25);
	mytree.insert(27);
	mytree.insert(6);
	mytree.insert(8);
	mytree.insert(15);
	mytree.insert(22);
	mytree.display();
	return 0;
}