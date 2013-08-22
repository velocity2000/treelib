#include <iostream>
#include "avl_tree.h"

using namespace std;

void main()
{
	avl_tree<int> * t = new avl_tree<int>();
	t->insert(20);
	t->insert(30);
	t->insert(40);
	t->insert(35);
	t->insert(10);
	t->insert(15);

	cout<< t->find_node(20)->get_height() << '\t';
	cout<< t->find_node(30)->get_height() << '\t';
	cout<< t->find_node(40)->get_height() << '\t';
	cout<< t->find_node(35)->get_height() << '\t';
	cout<< t->find_node(10)->get_height() << '\t';
	cout<< t->find_node(15)->get_height() << '\t';
	cout<< endl;

	t->remove(15);
	cout<< t->find_node(20)->get_height() << '\t';
	cout<< t->find_node(30)->get_height() << '\t';
	cout<< t->find_node(40)->get_height() << '\t';
	cout<< t->find_node(35)->get_height() << '\t';
	cout<< t->find_node(10)->get_height() << '\t';
	cout<< endl;

	avl_node<int> * l = t->find_node(40)->get_left_child();
	avl_node<int> * r = t->find_node(40)->get_right_child();
	if (l != NULL && r != NULL)
	{
		cout<< "40-s left child is: " << l->get_data() << endl;
		cout<< "40-s right child is: " << r->get_data() << endl;
	}
	else if (l != NULL)
	{
		cout<< "40-s left child is: " << l->get_data() << endl;
		cout<< "40-s right child is: " << "NULL" << endl;
	}
	else
	{
		cout<< "40-s left child is: " << "NULL" << endl;
		cout<< "40-s right child is: " << r->get_data() << endl;
	}

	if(t->find_sub_tree(20)->get_root() != NULL)
	{
		cout<< "the root of subtree is: " << t->find_sub_tree(20)->get_root()->get_data() << endl;
	}

	cout<< endl;

}