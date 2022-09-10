#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../utils.h"
#include "../debug.h"
#include "node.h"

using namespace container::node;

namespace container {

	namespace llist {

		template<typename T>
		struct llist_t;

		template<typename T>
		struct llCmd;

#define RefLL(T) llist_t<T>&

		template<typename T>
		struct llist_t
		{
			llist_t(void) : head_(NULL), currSize(0) {}
			~llist_t(void);
			u64 currSize;
			MonoNodePtr(T) head_;
		};

		template<typename T>
		llist_t<T>::~llist_t(void) {
			while (head_ != NULL) {
				MonoNodePtr(T) temp { head_->next_ };
				head_->next_ = NULL;
				delete head_;
				head_ = NULL; 
				head_ = temp;
			}
			currSize = 0;
		}

		template<typename T>
		struct llCmd {
			static void insert_back(RefLL(T), const T);
			static void insert_front(RefLL(T), const T);
			static bool contains(RefLL(T), const T);
			static s64 indexOf(RefLL(T), const T);
			static void remove(RefLL(T), const T);
			static void remove_front(RefLL(T));
			static void reserve(RefLL(T), const u64);
			struct iterator
			{
				iterator(void) : currentNode_(NULL) {}
				iterator(MonoNodePtr(T) node) : currentNode_(node) {}
				iterator& operator=(MonoNodePtr(T) node) {
					this->currentNode_ = node;
					return(*this);
				}
				iterator& operator++(void) {
					if (this->currentNode_ != NULL)
						this->currentNode_ = this->currentNode_->next_;
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
				MonoNodePtr(T) currentNode_; 
			};
			static iterator begin(RefLL(T));
			static iterator end(RefLL(T));
		};

		template<typename T>
		inline void llCmd<T>::insert_back(RefLL(T) L, const T data) {
			if (L.head_ == NULL)
			{
				L.head_ = AllocMonoNode(T, data);
				AssertRaw(L.head_ != NULL)
				L.currSize += 1;
				return;
			}
			else {

				MonoNodePtr(T) curr { L.head_ };

				for (; curr->next_ != NULL;)
					curr = curr->next_;

				MonoNodePtr(T) novel { AllocMonoNode(T, data) };
				AssertRaw(novel != NULL)

				curr->next_ = novel;

				L.currSize += 1;
			}
		}

		template<typename T>
		inline void llCmd<T>::insert_front(RefLL(T) L, const T data) {
			if (L.head_ == NULL)
			{
				L.head_ = AllocMonoNode(T, data);
				AssertRaw(L.head_ != NULL)
				return;
			}
			else
			{
				MonoNodePtr(T) novelHead { AllocMonoNode(T, data) };
				AssertRaw(novelHead != NULL)

				novelHead->next_ = L.head_;
				L.head_ = novelHead;
				L.currSize += 1;
			}
		}

		template<typename T>
		inline bool llCmd<T>::contains(RefLL(T) L, const T data) {
			if (L.head_ == NULL) return(false);

			for (MonoNodePtr(T) curr { L.head_ }; L.head_->next_ != NULL; L.head_ = L.head_->next_)
				if (curr->data_ == data)
					return(true);

			return(false);
		}

		template<typename T>
		inline s64 llCmd<T>::indexOf(RefLL(T) L, const T data) {
			if (L.head_ == NULL) return(-1);

			s64 index = {};
			for (MonoNodePtr(T) curr { L.head_ }; L.head_->next_ != NULL; L.head_ = L.head_->next_, index++)
				if (curr->data_ == data)
					return(index);

			return(-1);
		}

		template<typename T>
		inline void llCmd<T>::remove(RefLL(T) L, const T data) {
			if (L.head_ == NULL) return;

			if (L.head_->data_ == data)
			{
				L.head_ = L.head_->next_;
				L.currSize -= 1;
				return;
			}

			for (MonoNodePtr(T) curr{ L.head_ }; curr->next_ != NULL; curr = curr->next_)
			{
				if (curr->next_->data_ == data)
				{
					curr->next_ = curr->next_->next_;
					L.currSize -= 1;
					return;
				}
			}

			return;
		}

		template<typename T>
		inline void llCmd<T>::remove_front(RefLL(T) L) {

			if (L.head_ == NULL) return;

			if (L.head_->next_ != NULL)
			{
				L.head_ = L.head_->next_;
				L.currSize -= 1;
			}
			else
			{
				delete L.head_;
				L.head_ = NULL;
				L.currSize = 0; 
			}

		}

		template<typename T>
		inline void llCmd<T>::reserve(RefLL(T) L, const u64 size) {
			
		}

		template<typename T>
		inline llCmd<T>::iterator llCmd<T>::begin(RefLL(T) L)
		{
			llCmd<T>::iterator it(L.head_);
			return(it);
		}

		template<typename T>
		inline llCmd<T>::iterator llCmd<T>::end(RefLL(T) L)
		{
			u64 i = {};
			MonoNodePtr(T) curr { L.head_ };
			for (; curr != NULL; curr = curr->next_, i++)
				if (i == L.currSize - 1)
					break;

			llCmd<T>::iterator it(curr);
			return(it);
		}

}

}

#endif // !LINKED_LIST_H
