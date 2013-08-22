#pragma once
#include "avl_node.h"

template<typename T>
class avl_tree
{
public:
	inline avl_tree()
	{
		root = NULL;
	}

	inline avl_tree(T val)
	{
		root = new avl_node<T>(val);
	}

	inline ~avl_tree()
	{
		delete root;
		root = NULL;
	}

	inline avl_tree<T> * find_sub_tree(T val)
	{
		avl_node<T> * target = find_node(val);

		if (target != NULL)
		{
			avl_tree<T> * subtree = new avl_tree<T>();
			subtree->root = target;
			return subtree;
		}
		else
			return NULL;
	}

	inline avl_node<T> * find_node(T val)
	{
		avl_node<T> * tmp = root;
		while (tmp != NULL)
		{
			if(tmp->get_data() == val)
				return tmp;
			else if(tmp->get_data() > val)
				tmp = tmp->get_left_child();
			else
				tmp = tmp->get_right_child();
		}
		return NULL;
	}

	inline bool insert(T val)
	{
		avl_node<T> * added_node;
		if (root == NULL)
		{
			root = new avl_node<T>(val);
		}
		else
		{
			avl_node<T> * tmp = root;
			while (true)
			{
				if (val < tmp->get_data())
				{
					if (tmp->get_left_child() == NULL)
					{
						added_node = tmp->set_left_child(new avl_node<T>(val));
						break;
					}
					else
						tmp = tmp->get_left_child();
				}
				else if (val > tmp->get_data())
				{
					if (tmp->get_right_child() == NULL)
					{
						added_node = tmp->set_right_child(new avl_node<T>(val));
						break;
					}
					else
						tmp = tmp->get_right_child();
				}
				else
					return false;
			}
			tmp = added_node;
			while (tmp != NULL)
			{
				tmp->update_height();
				balance_at_node(tmp);
				tmp = tmp->get_parent();
			}
		}
		return true;
	}

	inline bool remove(T val)
	{
		if (root == NULL)
			return false;

		avl_node<T> * replacement, * replacement_parent, * tmp_node;
		avl_node<T> * to_be_removed = find_node(val);
		if (to_be_removed == NULL)
			return false;

		avl_node<T> * p = to_be_removed->get_parent();
		enum {left, right} side;
		if (p != NULL)
		{
			if (p->get_left_child() == to_be_removed)
				side = left;
			else
				side = right;
		}

		int bal = to_be_removed->get_balance();
		if (to_be_removed->get_left_child() == NULL && to_be_removed->get_right_child() == NULL)
		{
			if (p != NULL)
			{
				if (side == left)
					p->set_left_child(NULL);
				else
					p->set_right_child(NULL);

				delete to_be_removed;
				p->update_height();
				balance_at_node(p);
			}
			else
			{
				set_root(NULL);
				delete to_be_removed;
			}
		}
		else if (to_be_removed->get_right_child() == NULL)
		{
			if (p != NULL)
			{
				if (side == left)
					p->set_left_child(to_be_removed->get_left_child());
				else
					p->set_right_child(to_be_removed->get_left_child());

				delete to_be_removed;
				p->update_height();
				balance_at_node(p);
			}
			else
			{
				set_root(to_be_removed->get_left_child());
				delete to_be_removed;
			}
		}
		else if (to_be_removed->get_left_child() == NULL)
		{
			if (p != NULL)
			{
				if (side == left)
					p->set_left_child(to_be_removed->get_right_child());
				else
					p->set_right_child(to_be_removed->get_right_child());

				delete to_be_removed;
				p->update_height();
				balance_at_node(p);
			}
			else
			{
				set_root(to_be_removed->get_right_child());
				delete to_be_removed;
			}
		}
		else // when both children exists
		{
			if (bal > 0)
			{
				if (to_be_removed->get_left_child()->get_right_child() == NULL)
				{
					replacement = to_be_removed->get_left_child();
					replacement->set_right_child(to_be_removed->get_right_child());

					tmp_node = replacement;
				}
				else
				{
					replacement = to_be_removed->get_left_child()->get_right_child();
					while (replacement->get_right_child() != NULL)
					{
						replacement = replacement->get_right_child();
					}
					replacement_parent = replacement->get_parent();
					replacement_parent->set_right_child(replacement->get_left_child());

					tmp_node = replacement_parent;

					replacement->set_left_child(to_be_removed->get_left_child());
					replacement->set_right_child(to_be_removed->get_right_child());
				}
			}
			else
			{
				if (to_be_removed->get_right_child()->get_left_child() == NULL)
				{
					replacement = to_be_removed->get_right_child();
					replacement->set_left_child(to_be_removed->get_left_child());

					tmp_node = replacement;
				}
				else
				{
					replacement = to_be_removed->get_right_child()->get_left_child();
					while (replacement->get_left_child() != NULL)
					{
						replacement = replacement->get_left_child();
					}
					replacement_parent = replacement->get_parent();
					replacement_parent->set_left_child(replacement->get_right_child());

					tmp_node = replacement_parent;
				
					replacement->set_left_child(to_be_removed->get_left_child());
					replacement->set_right_child(to_be_removed->get_right_child());
				}
			}
			if (p != NULL)
			{
				if (side == left)
					p->set_left_child(replacement);
				else 
					p->set_right_child(replacement);

				delete to_be_removed;
			}
			else
			{
				set_root(replacement);
	
				delete to_be_removed;
			}

			balance_at_node(tmp_node);
		}
		return true;
	}

	inline avl_node<T> * get_root()
	{
		return root;
	}

	inline int get_height()
	{
		return root->get_height();
	}

private:
	avl_node<T> * root;

	inline void set_root(avl_node<T> * n)
	{
		root = n;
		if(root != NULL)
			root->remove_parent();
	}

	inline void rotate_left(avl_node<T> * n)
	{
		avl_node<T> * p = n->get_parent();

		enum {left, right} side;
		if(p != NULL)
		{
			if(p->get_left_child() == n)
				side = left;
			else
				side = right;
		}
	
		avl_node<T> * tmp = n->get_right_child();
		n->set_right_child(tmp->get_left_child());
		tmp->set_left_child(n);

		// attaching the subtree to the parrent (or setting root)
		if (p != NULL)
		{
			if (side == left)
				p->set_left_child(tmp);
			if (side == right)
				p->set_right_child(tmp);
		}
		else
		{
			set_root(tmp);
		}
	}

	inline void rotate_right(avl_node<T> * n)
	{
		avl_node<T> * p = n->get_parent();

		enum {left, right} side;
		if(p != NULL)
		{
			if(p->get_left_child() == n)
				side = left;
			else
				side = right;
		}

		avl_node<T> * tmp = n->get_left_child();
		n->set_left_child(tmp->get_right_child());
		tmp->set_right_child(n);

		if (p != NULL)
		{
			if (side == left)
				p->set_left_child(tmp);
			if (side == right)
				p->set_right_child(tmp);
		}
		else
		{
			set_root(tmp);
		}
	}

	inline void balance_at_node(avl_node<T> * n)
	{
		int bal = n->get_balance();

		if (bal > 1)
		{
			if (n->get_left_child()->get_balance() < 0)
				rotate_left(n->get_left_child());
			rotate_right(n);
		}
		else if (bal < -1)
		{
			if(n->get_right_child()->get_balance() > 0)
				rotate_right(n->get_right_child());
			rotate_left(n);
		}
	}
};
