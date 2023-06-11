// main.cpp : Defines the entry point for the application.
//

#define IDEBUG

#include "algo/container/sbst.h"
#include "algo/container/llist.h"

using namespace container;

int main(int argc, char** argv)
{

	clock_t begin = clock();
	{
		// work here


		llist::llist_t<int> targetList = {};

		for (s32 i = 0; i != 3; i++)
			llist::llCmd<s32>::insert_front(targetList, i);

		llist::llCmd<s32>::iterator it = llist::llCmd<s32>::begin(targetList);
		for (size_t i = 0; i < 3; ++i)
		{
			s32 val = *it;
			Print(val);
			++it; 
		}

		llist::llCmd<s32>::iterator end = llist::llCmd<s32>::end(targetList);
	

		sb_tree::sb_tree_t<r32> treef32 = {}; 

		sb_tree::sbstCmd<r32>::insert(treef32, 2.313f); 
		sb_tree::sbstCmd<r32>::insert(treef32, 1.313f);
		sb_tree::sbstCmd<r32>::insert(treef32, 0.313f);
		sb_tree::sbstCmd<r32>::insert(treef32, 2.300f);

		sb_tree::sbstCmd<r32>::remove(treef32, 2.313f);

		
		
	}
	clock_t end = clock();


	Endl();
	Print((double)(end - begin) / CLOCKS_PER_SEC);

	return(0);
}
