/*
													Trie DataStructure
	->Trie is an efficient information reTrieval data structure.
	->This program is implementation of Trie DataStructure using map which memory
		 efficient.
*/
#include <iostream>
#include <unordered_map>
using namespace std;

//define a trie Node
struct Trie
{
	bool Is_Leaf; // check if leaf Node
	unordered_map<char, Trie*> map; // child Nodes of the current Nodes
};

//create trie Node and return
Trie* Create_Node()
{
	Trie* Node = new Trie;
	Node->Is_Leaf = false;  //by default false
	return Node;
}

//Insert a string in Trie.
void Insert(Trie*& Head, char* str)
{
	if(Head == nullptr)
		Head = Create_Node();

	// start from root and find best position
	Trie* current = Head;
	while (*str)
	{
		// create a new Node if path doesn't exists
		if (current->map.find(*str) == current->map.end())
			current->map[*str] = Create_Node();

		// go to next Node
		current = current->map[*str];
		// move to next character
		str++;
	}
	// mark current Node as leaf
	current->Is_Leaf = true;
}

// returns true if given Node has any children
bool checkChildren(Trie const* curr)
{
	for (auto it : curr->map)
		if (it.second != nullptr)
			return true;
	return false;
}


// function to delete a string in Trie.
bool deletion(Trie*& current, char* str)
{
	// return if Trie is empty
	if (current == nullptr)
		return false;

	//if we are not at the end of the string
	if (*str)
	{
		if (current != nullptr &&  current->map.find(*str) != current->map.end() && deletion(current->map[*str], str + 1) && current->Is_Leaf == false)
		{
			//if it doesn't have children then delete current node
			if (!checkChildren(current))
			{
				delete current;;
				current = nullptr;
				return true;
			}
			else {
				return false;
			}
		}
	}

	// if we are at the end of the string
	//if it is leaf node  and do not have children then delete it
	// it have children then make Is_Leaf to false;
	if (*str == '\0' && current->Is_Leaf)
	{
		if (!checkChildren(current))
		{
			delete current;
			current = nullptr;
			return true;
		}
		else
		{
			current->Is_Leaf = false;
			return false;
		}
	}
	return false;
}

//function for searching string in Trie
bool search(Trie* Head, char* str)
{
	// return false if Trie is empty
	if (Head == nullptr)
		return false;

	Trie* current = Head;

	while (*str)
	{
		// go to next Node
		current = current->map[*str];
		// if reached at end of the trie and we didn't find the string then retru
		if (current == nullptr)
			return false;
		str++;
	}
	// if current node is leaf then we reached at the end of the string then return true else false;
	return current->Is_Leaf;
}

int main()
{
	//here is an example
	Trie* Head = nullptr;
	char x[] = "Git";
	char y[] = "Github";
	Insert(Head, x); //Insert "Git" to trie
	cout << search(Head, x) << endl; // will print 1
	Insert(Head, y); // Insert "Github" to trie
	cout << search(Head, y) <<endl; // print 1

	deletion(Head, x); // delete "Git" from trie
	cout << search(Head, y) <<endl; //prints 1
	cout << search(Head, x) << endl; // prints 0 because "Git" is deleted
	return 0;
}




//reference : https://www.techiedelight.com/memory-efficient-trie-implementation-using-map-insert-search-delete/
