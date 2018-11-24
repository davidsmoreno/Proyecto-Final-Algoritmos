#include <iostream>
#include "RBTree.hpp"

using namespace std;

int main() {
	RBTree<int, char> mytree, three;
	for (int i = -5; i < 6; ++i) {
		mytree.insert(i, 'p'+i);
		cout << i << " was inserted" << endl;
		mytree.display();
	}
	RBTree<int, char> two = mytree;
	three = mytree;
	for (int i = 5; i > -6; --i) {
		mytree.remove(i);
		cout << i << " was deleted" << endl;
		mytree.display();
	}
	cout << "-----------------------" << endl;
	two.display();
	two.clear();
	two.display();
	cout << "-----------------------" << endl;
	three.display();
	cout << three[-4] << endl;
	three.swap(three.at(-5), three.at(5));
	three.display();
	return 0;
}