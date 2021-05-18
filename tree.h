#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

#ifndef TREE_H
#define TREE_H

/* 
	
	The type T must support 
	< 
	> 
	== 
	!= 
	copy assignment operator
	copy constructor  

*/


namespace tree {

template <typename T>
class node
{
public:
	T key;
	int leftOffset;
	int rightOffset;

	// Constructor
	explicit node(T obj = T())
		: key(obj), leftOffset(-1), rightOffset(-1)
	{
	}
	node<T> &operator=(const node<T> &rhs)
	{
		if (this != &rhs)
		{
			this->key = rhs.key;
			this->leftOffset = rhs.leftOffset;
			this->rightOffset = rhs.rightOffset;
		}
		return *this;
	}

	template <typename U>
	friend std::ostream &operator<<(std::ostream &os, const node<U> &obj);

	template <typename U>
	friend bool operator<(const node<U> &lhs, const node<U> &rhs);

	template <typename U>
	friend bool operator>(const node<U> &lhs, const node<U> &rhs);

	template <typename U>
	friend bool operator==(const node<U> &lhs, const node<U> &rhs);

	template <typename U>
	friend bool operator!=(const node<U> &lhs, const node<U> &rhs);
};

template <typename U>
bool operator<(const node<U> &lhs, const node<U> &rhs)
{
	return lhs.key < rhs.key;
}

template <typename U>
bool operator>(const node<U> &lhs, const node<U> &rhs)
{
	return lhs.key > rhs.key;
}

template <typename U>
bool operator==(const node<U> &lhs, const node<U> &rhs)
{
	return lhs.key == rhs.key;
}

template <typename U>
bool operator!=(const node<U> &lhs, const node<U> &rhs)
{
	return lhs.key != rhs.key;
}

template <typename U>
std::ostream &operator<<(std::ostream &os, const node<U> &obj)
{
	os << obj.key;
	return os;
}

template <typename T>
class Tree
{
private:
	int root;
	int free_node;
	Tree *my_tree;
	FILE *fp;
public:
	const char *filename;
	

	explicit Tree()
	{
	}
	Tree(const char *file)
		: filename(file), root(-1), free_node(-1), my_tree(new Tree)
	{
		fp = fopen(file, "r+");
		if (fp == NULL)
		{
			//cout << "The file was not present i\'ll make one now !\n";
			fp = fopen(file, "w+");
			fwrite(this, sizeof(Tree), 1, fp);
			fclose(fp);
			fp = fopen(file, "r+");
			// if (fp != NULL)
			// {
			// 	cout << "The file is ready to be read\n";
			// }
		}
		//cout << ftell(fp) << "before reading tree\n";
		fread(my_tree, sizeof(Tree), 1, fp);
		//cout << ftell(fp) << "after reading tree\n";
	}

	void insert(T key)
	{
		node<T> newNode(key);
		//cout << "New node : " << newNode << endl;
		node<T> temp;
		int offset;
		//cout << "Size of this : " << sizeof(Tree) << endl;

		if (this->my_tree->free_node == -1)
		{
			//cout << ftell(this->fp) << endl;
			//cout << fp << endl;
			fseek(this->fp, 0, SEEK_END);
			//cout << fp << endl;
			offset = ftell(this->fp);
			//cout << offset << endl;
		}
		else
		{
			offset = this->my_tree->free_node;
			fseek(this->fp, offset, SEEK_SET);
			fread(&temp, sizeof(node<T>), 1, fp);
			this->my_tree->free_node = temp.rightOffset;
		}
		if (this->my_tree->root == -1)
		{
			this->my_tree->root = offset;
		}
		else
		{
			node<T> curr_node;
			node<T> prev_node;
			int curr = this->my_tree->root;
			int prev = -1;

			while (curr != -1)
			{
				fseek(fp, curr, SEEK_SET);

				if (curr != -1)
				{
					fread(&curr_node, sizeof(node<T>), 1, fp);
				}
				prev = curr;
				prev_node = curr_node;
				if (key < curr_node.key)
				{
					curr = curr_node.leftOffset;
				}
				else if (key > curr_node.key)
				{
					curr = curr_node.rightOffset;
				}
				else if (key == curr_node.key)
				{
					// cout << "Present\n";
					return;
				}
			}

			if (key < prev_node.key)
			{
				prev_node.leftOffset = offset;
			}
			else if (key > prev_node.key)
			{
				prev_node.rightOffset = offset;
			}
			fseek(this->fp, prev, SEEK_SET);
			fwrite(&prev_node, sizeof(node<T>), 1, fp);
		}
		fseek(this->fp, 0, SEEK_SET);
		fwrite(this->my_tree, sizeof(Tree), 1, fp);
		fseek(this->fp, offset, SEEK_SET);
		fwrite(&newNode, sizeof(node<T>), 1, fp);
	}
private:
	int findMax(int curr, int *inner_prev) // inorder predecessor
	{
		node<T> temp;
		int prev = -1;
		while (curr != -1)
		{
			fseek(fp, curr, SEEK_SET);
			fread(&temp, sizeof(node<T>), 1, fp);
			*inner_prev = prev;
			prev = curr;
			curr = temp.rightOffset;
		}
		return prev;
	}
private:
	void insert_free_nodes(int offset) // function to insert the free nodes into this.
	{
		node<T> temp;

		// reading the mytree pointer
		fseek(fp, 0, SEEK_SET);
		fread(this->my_tree, sizeof(Tree<T>), 1, fp);

		if (this->my_tree->free_node == -1)
		{
			this->my_tree->free_node = offset;
			fseek(fp, 0, SEEK_SET);
			fwrite(this->my_tree, sizeof(Tree<T>), 1, fp);
		}
		else
		{
			fseek(fp, offset, SEEK_SET); // join the free node
			fread(&temp, sizeof(node<T>), 1, fp);
			temp.rightOffset = this->my_tree->free_node;
			this->my_tree->free_node = offset;
			fseek(fp, 0, SEEK_SET);
			fwrite(this->my_tree, sizeof(Tree<T>), 1, fp);
		}
	}
public:
	void delete_key(T key)
	{
		node<T> temp;

		// reading the mytree pointer
		fseek(fp, 0, SEEK_SET);
		fread(this->my_tree, sizeof(Tree<T>), 1, fp);

		int prev = -1;
		int curr = this->my_tree->root;

		// 1. step find the leafnode;
		if (curr == -1) // the root is null.
			return;

		while (curr != -1)
		{
			fseek(fp, curr, SEEK_SET);
			fread(&temp, sizeof(node<T>), 1, fp);
			if (key < temp.key)
			{
				prev = curr;
				curr = temp.leftOffset;
			}
			else if (key > temp.key)
			{
				prev = curr;
				curr = temp.rightOffset;
			}
			else if (key == temp.key)
			{
				break;
			}
		}
		if (curr == -1) // element not found .
		{
			return;
		}
		if (curr != -1) // element found here
		{
			node<T> prev_temp;
			fseek(fp, curr, SEEK_SET);
			fread(&temp, sizeof(node<T>), 1, fp);
			if (temp.leftOffset == -1 && temp.rightOffset == -1) // leaf node case       1.)***********************************
			{
				//printf("leaf node\n");
				if (prev == -1) // only the root node present
				{
					fseek(fp, 0, SEEK_SET);
					fread(this->my_tree, sizeof(Tree<T>), 1, fp);
					this->my_tree->free_node = -1;
					this->my_tree->root = -1;
					fseek(fp, 0, SEEK_SET);
					fwrite(this->my_tree, sizeof(Tree<T>), 1, fp);

					insert_free_nodes(curr);
				}
				else
				{

					fseek(fp, prev, SEEK_SET);
					fread(&prev_temp, sizeof(node<T>), 1, fp);
					if (prev_temp.leftOffset == curr) // determining the prev_temps right or left child .
					{
						//printf("I bcam left\n");
						prev_temp.leftOffset = -1;
					}
					else if (prev_temp.rightOffset == curr) // making the prev_temp as null (-1)
					{
						//printf("I became right\n");

						prev_temp.rightOffset = -1;
					}
					fseek(fp, prev, SEEK_SET);
					fwrite(&prev_temp, sizeof(node<T>), 1, fp);

					insert_free_nodes(curr);
				}
				// we  have to free the curr and attach it in the free list .
			}

			// If the node is has one child                                                 2.)***********************************
			if (temp.rightOffset == -1 && temp.leftOffset != -1)
			{
				//printf("One child\n");
				if (prev == -1) // only one root and a child
				{
					fseek(fp, 0, SEEK_SET);
					fread(this->my_tree, sizeof(Tree<T>), 1, fp);
					this->my_tree->root = temp.leftOffset;
					fseek(fp, 0, SEEK_SET);
					fwrite(this->my_tree, sizeof(Tree<T>), 1, fp);
					temp.leftOffset = -1;
					fseek(fp, curr, SEEK_SET);
					fwrite(&temp, sizeof(node<T>), 1, fp);
					insert_free_nodes(curr);
				}
				else
				{
					fseek(fp, prev, SEEK_SET);
					fread(&prev_temp, sizeof(node<T>), 1, fp);
					if (curr == prev_temp.rightOffset)
					{
						prev_temp.rightOffset = temp.leftOffset;
					}
					if (curr == prev_temp.leftOffset)
					{
						prev_temp.leftOffset = temp.leftOffset;
					}
					fseek(fp, prev, SEEK_SET);
					fwrite(&prev_temp, sizeof(node<T>), 1, fp);

					temp.leftOffset = -1;
					fseek(fp, curr, SEEK_SET);
					fwrite(&temp, sizeof(node<T>), 1, fp);
					insert_free_nodes(curr);
				}
			}
			else if (temp.rightOffset != -1 && temp.leftOffset == -1) // Both are null in nature. has two children.
			{
				//printf("Two children\n");
				if (prev == -1)
				{
					fseek(fp, 0, SEEK_SET);
					fread(this->my_tree, sizeof(Tree<T>), 1, fp);
					this->my_tree->root = temp.rightOffset;
					fseek(fp, 0, SEEK_SET);
					fwrite(this->my_tree, sizeof(Tree<T>), 1, fp);
					temp.rightOffset = -1;
					fseek(fp, curr, SEEK_SET);
					fwrite(&temp, sizeof(node<T>), 1, fp);
					insert_free_nodes(curr);
				}
				else
				{
					fseek(fp, prev, SEEK_SET);
					fread(&prev_temp, sizeof(node<T>), 1, fp);
					if (curr == prev_temp.rightOffset)
					{
						prev_temp.rightOffset = temp.rightOffset;
					}
					if (curr == prev_temp.leftOffset)
					{
						prev_temp.leftOffset = temp.rightOffset;
					}
					fseek(fp, prev, SEEK_SET);
					fwrite(&prev_temp, sizeof(node<T>), 1, fp);
					temp.rightOffset = -1;
					fseek(fp, curr, SEEK_SET);
					fwrite(&temp, sizeof(node<T>), 1, fp);
					insert_free_nodes(curr);
				}
			}
			if (temp.rightOffset != -1 && temp.leftOffset != -1)
			{
				node<T> joker;
				int inner_prev;
				int *t = &inner_prev;
				int inner_curr = findMax(temp.leftOffset, t);

				fseek(fp, inner_curr, SEEK_SET);
				fread(&joker, sizeof(node<T>), 1, fp);
				temp.key = joker.key; // copy the largest value in leftsubtree.

				fseek(fp, curr, SEEK_SET);
				fwrite(&temp, sizeof(node<T>), 1, fp);

				int parent_left_subtree = curr; // offset of the parent of the left sub tree    PARENT POINTER OFFSET

				if (inner_curr == temp.leftOffset && inner_prev == -1)
				{
					fseek(fp, inner_curr, SEEK_SET);
					fread(&joker, sizeof(node<T>), 1, fp);

					temp.leftOffset = joker.leftOffset;

					fseek(fp, curr, SEEK_SET);
					fwrite(&temp, sizeof(node<T>), 1, fp);

					joker.leftOffset = -1;
					fseek(fp, inner_curr, SEEK_SET);
					fwrite(&joker, sizeof(node<T>), 1, fp);
					insert_free_nodes(inner_curr);
				}
				else if (inner_curr != temp.leftOffset && inner_prev != -1)
				{
					node<T> last;
					fseek(fp, inner_curr, SEEK_SET);
					fread(&last, sizeof(node<T>), 1, fp); // read the inner_curr in last

					fseek(fp, inner_prev, SEEK_SET);
					fread(&joker, sizeof(node<T>), 1, fp);
					joker.rightOffset = last.leftOffset;
					last.leftOffset = -1;
					fseek(fp, inner_curr, SEEK_SET);
					fwrite(&last, sizeof(node<T>), 1, fp);

					fseek(fp, inner_prev, SEEK_SET);
					fwrite(&joker, sizeof(node<T>), 1, fp);
					insert_free_nodes(inner_curr);
				}
			}
		}
	}

private:
	void inorder(int root)
	{
		if (root == -1)
			return;
		else
		{
			node<T> temp;
			fseek(fp, root, SEEK_SET);
			fread(&temp, sizeof(node<T>), 1, fp);
			inorder(temp.leftOffset);
			cout << temp.key <<" ";
			inorder(temp.rightOffset);
		}
	}

public:
	void display_inorder()
	{
		if (this->my_tree->root == -1)
			return;
		fseek(this->fp, 0, SEEK_SET);
		fread(this->my_tree, sizeof(Tree<T>), 1, fp);
		inorder(this->my_tree->root);
		cout << "\n";
	}

private:
	void preorder(int root)
	{
		if (root == -1)
			return;
		else
		{
			node<T> temp;
			fseek(fp, root, SEEK_SET);
			fread(&temp, sizeof(node<T>), 1, fp);
			cout << temp.key <<" ";
			preorder(temp.leftOffset);
			preorder(temp.rightOffset);
		}
	}

public:
	void display_preorder()
	{
		if (this->my_tree->root == -1)
			return;
		fseek(this->fp, 0, SEEK_SET);
		fread(this->my_tree, sizeof(Tree<T>), 1, fp);
		preorder(this->my_tree->root);
		cout << "\n";
	}

private:
	void postorder(int root)
	{
		if (root == -1)
			return;
		else
		{
			node<T> temp;
			fseek(fp, root, SEEK_SET);
			fread(&temp, sizeof(node<T>), 1, fp);
			postorder(temp.leftOffset);
			postorder(temp.rightOffset);
			cout << temp.key <<" ";
		}
	}

public:
	void display_postorder()
	{
		if (this->my_tree->root == -1)
			return;
		fseek(this->fp, 0, SEEK_SET);
		fread(this->my_tree, sizeof(Tree<T>), 1, fp);
		postorder(this->my_tree->root);
		cout << "\n";
	}
private:
	void inorder_vector(int root, vector<T> & vec) 
	{	
		if (root == -1)
			return;
		else
		{
			node<T> temp;
			fseek(fp, root, SEEK_SET);
			fread(&temp, sizeof(node<T>), 1, fp);
			inorder_vector(temp.leftOffset,vec);
			vec.push_back(temp.key);
			inorder_vector(temp.rightOffset,vec);
		}
		
	}
	void preorder_vector(int root, vector<T> & vec) 
	{	
		if (root == -1)
			return;
		else
		{
			node<T> temp;
			fseek(fp, root, SEEK_SET);
			fread(&temp, sizeof(node<T>), 1, fp);
			vec.push_back(temp.key);
			preorder_vector(temp.leftOffset,vec);
			preorder_vector(temp.rightOffset,vec);
		}
		
	}
	void postorder_vector(int root, vector<T> & vec) 
	{	
		if (root == -1)
			return;
		else
		{
			node<T> temp;
			fseek(fp, root, SEEK_SET);
			fread(&temp, sizeof(node<T>), 1, fp);
			postorder_vector(temp.leftOffset,vec);
			postorder_vector(temp.rightOffset,vec);
			vec.push_back(temp.key);
		}
		
	}

public: 
	vector<T> get_inorder()
	{
		vector<T> res;
		if (this->my_tree->root == -1)
			return res;
		fseek(this->fp, 0, SEEK_SET);
		fread(this->my_tree, sizeof(Tree<T>), 1, fp);
		inorder_vector(this->my_tree->root,res);
		return res;
	}

	vector<T> get_preorder()
	{
		vector<T> res;
		if (this->my_tree->root == -1)
			return res;
		fseek(this->fp, 0, SEEK_SET);
		fread(this->my_tree, sizeof(Tree<T>), 1, fp);
		preorder_vector(this->my_tree->root,res);
		return res;
	}

	vector<T> get_postorder()
	{
		vector<T> res;
		if (this->my_tree->root == -1)
			return res;
		fseek(this->fp, 0, SEEK_SET);
		fread(this->my_tree, sizeof(Tree<T>), 1, fp);
		postorder_vector(this->my_tree->root,res);
		return res;
	}

}; 

}
#endif
