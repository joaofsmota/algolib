#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "../debug.h"
#include "../utils.h"
#include "node.h"

using namespace container::node;

namespace container {

	namespace dllist {

		template<typename T>
		struct dllist_t;

		template<typename T>
		struct dllCmd;

#define RefDLL(T) dllist_t<T>&

		template<typename T>
		struct dllist_t
		{
			dllist_t(void) : head_(NULL), currSize(0) {}
			~dllist_t(void);
			u64 currSize;
			DiNodePtr(T) head_;
		};

		template<typename T>
		dllist_t<T>::~dllist_t(void) {
			while (head_ != NULL) {
				DiNodePtr(T) temp { head_->next_ };
				head_->next_ = NULL;
				delete head_;
				head_ = NULL;
				head_ = temp;
			}
			currSize = 0;
		}

		template<typename T>
		struct dllCmd {
			static void insert_back(RefDLL(T), const T);
			static void insert_front(RefDLL(T), const T);
			static bool contains(RefDLL(T), const T);
			static s64 indexOf(RefDLL(T), const T);
			static void remove(RefDLL(T), const T);
			static void remove_back(RefDLL(T));
			static void remove_front(RefDLL(T));
			static void reserve(RefDLL(T), const u64);
			struct iterator
			{
				iterator(void) : currentNode_(NULL) {}
				iterator(DiNodePtr(T) node) : currentNode_(node) {}
				iterator& operator=(DiNodePtr(T) node) {
					this->currentNode_ = node;
					return(*this);
				}
				iterator& operator++(void) {
					if (this->currentNode_ != NULL)
						this->currentNode_ = this->currentNode_->next_;
					return(*this);
				}
				iterator& operator--(void) {
					if (this->currentNode_ != NULL)
						this->currentNode_ = this->currentNode_->prev_;
					return(*this);
				}
				bool operator!=(const iterator& iter) {
					return(this->currentNode_ != iter.currentNode_);
				}
				T operator*(void) {
					return(this->currentNode_->data_);
				}
				~iterator(void) {}
			private:
				DiNodePtr(T) currentNode_;
			};
			static iterator begin(RefDLL(T));
			static iterator end(RefDLL(T));
		};

		template<typename T>
		inline void dllCmd<T>::insert_back(RefDLL(T) L, const T data)
		{

		}

		template<typename T>
		inline void dllCmd<T>::insert_front(RefDLL(T), const T)
		{
		}

		template<typename T>
		inline bool dllCmd<T>::contains(RefDLL(T), const T)
		{
			return false;
		}

		template<typename T>
		inline s64 dllCmd<T>::indexOf(RefDLL(T), const T)
		{
			return s64();
		}

		template<typename T>
		inline void dllCmd<T>::remove(RefDLL(T), const T)
		{
		}

		template<typename T>
		inline void dllCmd<T>::remove_back(RefDLL(T))
		{
		}

		template<typename T>
		inline void dllCmd<T>::remove_front(RefDLL(T))
		{
		}

		template<typename T>
		inline void dllCmd<T>::reserve(RefDLL(T), const u64)
		{
		}

		template<typename T>
		inline dllCmd<T>::iterator dllCmd<T>::begin(RefDLL(T))
		{
			return iterator();
		}

		template<typename T>
		inline dllCmd<T>::iterator dllCmd<T>::end(RefDLL(T))
		{
			return iterator();
		}

	}

}

#endif // !DOUBLY_LINKED_LIST_H
