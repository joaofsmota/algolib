#ifndef TREE_H
#define TREE_H

#include "../utils.h"
#include "../debug.h"
#include "node.h"

/*

	(sorted) binary tree.
	
	In context :
	{

	} // tree is out of scope => tree.~sb_tree_t() => every node is destroyed
*/

using namespace container::node;

namespace container {

	namespace sb_tree {

		template<typename T>
		struct sb_tree_t;

		template<typename T>
		struct sbstCmd;

#define RefSBST(T) sb_tree_t<T>& 

		template<typename T>
		struct sb_tree_t
		{
			sb_tree_t(void) : root_(NULL) {
				static_assert(std::is_class<T>::value == false, "T must be a basic type");
			}
			~sb_tree_t(void) { 
				sbstCmd<T>::destroy(root_);
			}
			DiNodePtr(T) root_;
		};

		template<typename T>
		struct sbstCmd {
			static void insert(RefSBST(T), T);
			static void remove(RefSBST(T), T);
			static DiNodePtr(T) search(RefSBST(T), T);
			static bool empty(RefSBST(T));
			static u64 height(RefSBST(T));
			static void inorder(RefSBST(T));
			static void destroy(DiNodePtr(T));
		private:
			static void insert(T, DiNodePtr(T));
			static T successor(DiNodePtr(T));
			static T predecessor(DiNodePtr(T));
			static DiNodePtr(T) remove(T, DiNodePtr(T));
			static DiNodePtr(T) search(T, DiNodePtr(T));
			static u64 height(DiNodePtr(T));
			static void inorder(DiNodePtr(T));
		};

		template<typename T>
		inline void sbstCmd<T>::destroy(DiNodePtr(T) root) {
			if (root != NULL)
			{
				destroy(root->prev_);
				destroy(root->next_);
				delete root;
				root = NULL;
			}
		}

		template<typename T>
		inline void sbstCmd<T>::insert(T data, DiNodePtr(T) node) {
			if (data < node->data_)
			{
				if (node->prev_ != NULL) insert(data, node->prev_);
				else {
					node->prev_ = AllocDiNode(T, data);
					AssertRaw(node->prev_ != NULL)
				}
			}
			else if (data > node->data_)
			{
				if (node->next_ != NULL) insert(data, node->next_);
				else {
					node->next_ = AllocDiNode(T, data);
					AssertRaw(node->next_ != NULL)
				}
			}
			else
			{
				node->data_ = data;
				return;
			}
		}

		template<typename T>
		inline T sbstCmd<T>::successor(DiNodePtr(T) node) {
			node = node->next_;
			while (node->prev_ != NULL)
				node = node->prev_;
			return(node->data_);
		}

		template<typename T>
		inline T sbstCmd<T>::predecessor(DiNodePtr(T) node) {
			node = node->prev_;
			while (node->next_ != NULL)
				node = node->next_;
			return(node->data_);
		}

		template<typename T>
		inline DiNodePtr(T) sbstCmd<T>::remove(T data, DiNodePtr(T) node) {
			if (node == NULL) return(NULL);
			else
			{
				if (data > node->data_)
				{
					node->next_ = remove(data, node->next_);
				}
				else if (data < node->data_)
				{
					node->prev_ = remove(data, node->prev_);
				}
				else
				{
					if (node->prev_ == NULL && node->next_ == NULL) // it's a leaf
					{
						delete node;
						node = NULL;
					}
					else if (node->next_ != NULL)
					{
						node->data_ = successor(node);
						node->next_ = remove(node->data_, node->next_);
					}
					else
					{
						node->data_ = predecessor(node);
						node->prev_ = remove(node->data_, node->prev_);
					}
				}
			}
			return(node);
		}

		template<typename T>
		inline DiNodePtr(T) sbstCmd<T>::search(T data, DiNodePtr(T) node) {
			if (node != NULL)
			{
				if (data == node->data_) return(node);
				else
				{
					if (data < node->data_) return(search(data, node->prev_));
					else return(search(data, node->next_));
				}
			}
			else return(NULL);
		}

		template<typename T>
		inline u64 sbstCmd<T>::height(DiNodePtr(T) node){
			if (node == NULL) return(0);
			else {
				u64 leftHeight = height(node->prev_);
				u64 rightHeight = height(node->next_);
				return(Max(leftHeight, rightHeight) + 1);
			}
		}

		template<typename T>
		inline void sbstCmd<T>::inorder(DiNodePtr(T) node) {
			if (node != NULL)
			{
				inorder(node->prev_);
				PartialPrint(node->data_);
				inorder(node->next_);
			}
		}

		template<typename T>
		inline void sbstCmd<T>::insert(RefSBST(T) tree, T data){
			if (tree.root_ == NULL) {
				tree.root_ = AllocDiNode(T, data);
				AssertRaw(tree.root_ != NULL);
			}
			else 
				insert(data, tree.root_);
		}

		template<typename T>
		inline void sbstCmd<T>::remove(RefSBST(T) tree, T data) {
			remove(data, tree.root_);
		}

		template<typename T>
		inline DiNodePtr(T) sbstCmd<T>::search(RefSBST(T) tree, T data) {
			return(search(data, tree.root_));
		}

		template<typename T>
		inline bool sbstCmd<T>::empty(RefSBST(T) tree) {
			return(tree.root_ == NULL ? true : false);
		}

		template<typename T>
		inline u64 sbstCmd<T>::height(RefSBST(T) tree) {
			return(height(tree.root_));
		}

		template<typename T>
		inline void sbstCmd<T>::inorder(RefSBST(T) tree) {
			inorder(tree.root_);
		}

	}

}

#endif // !TREE_H
