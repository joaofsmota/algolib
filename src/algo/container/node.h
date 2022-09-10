#ifndef NODE_H
#define NODE_H

namespace container {

	namespace node {

#define DiNodePtr(T) di_node_t<T>*
#define MonoNodePtr(T) mono_node_t<T>* 

#define AllocDiNode(T, data_) new di_node_t<T>(data_) 
#define AllocMonoNode(T, data_) new mono_node_t<T>(data_)

		template<typename T>
		struct di_node_t
		{
			di_node_t(T data) : data_(data), next_(NULL), prev_(NULL) {}
			~di_node_t(void) {}
			T data_;
			DiNodePtr(T) next_;
			DiNodePtr(T) prev_;
		};

		template<typename T>
		struct mono_node_t
		{
			mono_node_t(T data) : data_(data), next_(NULL) {}
			~mono_node_t(void) {}
			T data_;
			MonoNodePtr(T) next_;
		};

	}
}

#endif // !NODE_H
