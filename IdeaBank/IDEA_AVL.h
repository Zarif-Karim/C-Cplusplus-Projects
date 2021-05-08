#pragma once

struct Index {
	string key;
	list<int> idList;
};

class IDEA_AVL : public AvlTree<Index, string>
{
private:
	void  _traversal(void (*process)(Index& dataProc, int& id),
		NODE<Index>* root, int& id);
	void _print(NODE<Index> * root);
public:

	// change to modify
	bool  AVL_Modify(string  key, Index** dataOut);
	void  AVL_Update_Traverse(void (*process)(Index& dataProc, int& id), int& id); //in-order
	void  Print_Dictionary();
};

void IDEA_AVL
::Print_Dictionary() {
	_print(tree);
}

void IDEA_AVL
::_print(NODE<Index> * root) {
	//	Statements 
	if (root)
	{
		_print(root->left);
		if (!root->data.idList.empty()) {
			cout << setw(20) << left << root->data.key;
			cout << "{ ";
			for (int z : root->data.idList) cout << z << ", ";
			cout << "\b\b }\n";
		}
		_print(root->right);
	} //  if 
	return;
}

bool IDEA_AVL
::AVL_Modify(string   key, Index** dataOut)
{
	//	Local Definitions
	NODE<Index>* node;

	//	Statements 
	if (!tree)
		return false;

	node = _retrieve(key, tree);
	if (node)
	{
		*dataOut = &(node->data);
		return true;
	} // if found
	else
		return false;
}	//  AVL_Retrieve 

void  IDEA_AVL
::AVL_Update_Traverse(void (*process)(Index& dataProc, int& id), int& id)
{
	//	Statements 
	_traversal(process, tree, id);
	return;
}	// end AVL_Traverse 

void  IDEA_AVL
::_traversal(void (*process)(Index& dataProc, int& id),
	NODE<Index>* root, int& id)
{
	//	Statements 
	if (root)
	{
		_traversal(process, root->left, id);
		process(root->data, id);
		_traversal(process, root->right, id);
	} //  if 
	return;
}
