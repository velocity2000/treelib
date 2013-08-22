#pragma once

template <typename T>
class avl_node
{
public:
	inline avl_node(T val)
	{
		data = val;
		height = 0;
		parent = NULL;
		left_child = NULL;
		right_child = NULL;
	}

	inline ~avl_node()
	{
	}

	inline T get_data()
	{
		return data;
	}

	inline int get_height()
	{
		return height;
	}

	inline int update_height()
	{
		if(left_child != NULL && right_child != NULL)
		{
			if(left_child->get_height() > right_child->get_height())
				height = left_child->get_height() + 1;
			else
				height = right_child->get_height() + 1;
		}
		else if(left_child != NULL)
			height = left_child->get_height() + 1;
	    else if(right_child != NULL)
			height = right_child->get_height() + 1;
		else
			height = 0;
		return height;
	}

	inline int get_balance()
	{
		avl_node<T> * n = this;
		if(n->get_left_child() != NULL && n->get_right_child() != NULL)
			return n->get_left_child()->get_height() - n->get_right_child()->get_height();
		else if(n->get_left_child() != NULL)
			return n->get_left_child()->get_height() + 1;
		else if(n->get_right_child() != NULL)
			return (-1) * (n->get_right_child()->get_height() + 1);
		else
			return 0;
	}

	inline avl_node<T> * get_parent()
	{
		return parent;
	}

	inline avl_node<T> * get_left_child()
	{
		return left_child;
	}

	inline avl_node<T> * get_right_child()
	{
		return right_child;
	}

	inline void remove_parent()
	{
		parent = NULL;
	}

	inline avl_node<T> * set_left_child(avl_node * new_left)
	{
		if(new_left != NULL)
			new_left->parent = this;
		left_child = new_left;
		update_height();
		return left_child;
	}

	inline avl_node<T> * set_right_child(avl_node * new_right)
	{
		if(new_right != NULL)
			new_right->parent = this;
		right_child = new_right;
		update_height();
		return right_child;
	}

private:
	T data;
	int height;
	avl_node<T> * parent;
	avl_node<T> * left_child;
	avl_node<T> * right_child;
};

