
//#include <bits/stdc++.h>
#include <iostream>
#include <climits>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// structure of AVL tree node
class TreeNode
{
	public:
	int key;
	TreeNode *left_child;
	TreeNode *right_child;
	int height;
};

// function to find the
// height of input node in tree
int height(TreeNode *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// returns maximum value
// among two integers
int max(int a1, int b1)
{
	return (a1 > b1)? a1 : b1;
}


TreeNode* initialize()
{
	TreeNode* root = NULL;
	return root;
}
TreeNode* addNode(int key)
{
	TreeNode* tempNode = new TreeNode();
	tempNode->key = key;
	tempNode->left_child = NULL;
	tempNode->right_child = NULL;
	tempNode->height = 1;

	return(tempNode);
}
//  function to do right
// rotation at yNode

TreeNode *right_Rotation(TreeNode *yNode)
{
	TreeNode *xNode = yNode->left_child;
	TreeNode *tNode2 = xNode->right_child;

	// do rotation
	xNode->right_child = yNode;
	yNode->left_child = tNode2;

	// Update heights
	yNode->height = max(height(yNode->left_child),
					height(yNode->right_child)) + 1;
	xNode->height = max(height(xNode->left_child),
					height(xNode->right_child)) + 1;


	return xNode;
}


TreeNode *left_Rotation(TreeNode *xNode)
{
	TreeNode *yNode = xNode->right_child;
	TreeNode *tNode2 = yNode->left_child;

	// do rotation
	yNode->left_child = xNode;
	xNode->right_child = tNode2;

	// Update heights
	xNode->height = max(height(xNode->left_child),
					height(xNode->right_child)) + 1;
	yNode->height = max(height(yNode->left_child),
					height(yNode->right_child)) + 1;

	// Return new root
	return yNode;
}

// Get Balance factor of node nNode
int find_balance (TreeNode *nNode)
{
	if (nNode == NULL)
		return 0;
	return height(nNode->left_child) - height(nNode->right_child);
}


TreeNode* insert(TreeNode* rootNode, int key)
{

	if (rootNode == NULL)
		return(addNode(key));


	if (key < rootNode->key)
		rootNode->left_child = insert(rootNode->left_child, key);
	else if (key > rootNode->key)
		rootNode->right_child = insert(rootNode->right_child, key);
	else
		return rootNode;


	rootNode->height = 1 + max(height(rootNode->left_child),
						height(rootNode->right_child));


	int valueOfBalance = find_balance (rootNode);



	// Left Left Case
	if (valueOfBalance > 1 && key < rootNode->left_child->key)
		return right_Rotation(rootNode);

	// Right Right Case
	if (valueOfBalance < -1 && key > rootNode->right_child->key)
		return left_Rotation(rootNode);

	// Left Right Case
	if (valueOfBalance > 1 && key > rootNode->left_child->key)
	{
		rootNode->left_child = left_Rotation(rootNode->left_child);
		return right_Rotation(rootNode);
	}

	// Right Left Case
	if (valueOfBalance < -1 && key < rootNode->right_child->key)
	{
		rootNode->right_child = right_Rotation(rootNode->right_child);
		return left_Rotation(rootNode);
	}


	return rootNode;
}


TreeNode * minimumNode(TreeNode* tempNode)
{
    TreeNode* current = tempNode;

    /* loop down to find the leftmost leaf */
    while (current->left_child != NULL)
        current = current->left_child;

    return current;
}

TreeNode* search(TreeNode* rootNode, int key){

	TreeNode* current = rootNode;
	while(current != NULL){

		if(current->key == key){
			return current;
		}
		else if(current->key > key){
			current = current->left_child;
		}
		else{
			current = current->right_child;
		}
	}
	return NULL;

}
TreeNode* deleteNode(TreeNode* rootNode, int key)
{


    if (rootNode == NULL)
        return rootNode;


    if ( key < rootNode->key )
        rootNode->left_child = deleteNode(rootNode->left_child, key);


    else if( key > rootNode->key )
        rootNode->right_child = deleteNode(rootNode->right_child, key);

    else
    {

        if( (rootNode->left_child == NULL) ||
            (rootNode->right_child == NULL) )
        {
            TreeNode *temp = rootNode->left_child ?
                         rootNode->left_child :
                         rootNode->right_child;


            if (temp == NULL)
            {
                temp = rootNode;
                rootNode = NULL;
            }
            else
            *rootNode = *temp;

            free(temp);
        }
        else
        {

            TreeNode* temp = minimumNode(rootNode->right_child);
            rootNode->key = temp->key;

            rootNode->right_child = deleteNode(rootNode->right_child,
                                     temp->key);
        }
    }

    if (rootNode == NULL)
    return rootNode;

    rootNode->height = 1 + max(height(rootNode->left_child),
                           height(rootNode->right_child));

    int valueOfBalance = find_balance (rootNode);

    if (valueOfBalance > 1 &&
        find_balance (rootNode->left_child) >= 0)
        return right_Rotation(rootNode);

    // Left Right Case
    if (valueOfBalance > 1 &&
        find_balance (rootNode->left_child) < 0)
    {
        rootNode->left_child = left_Rotation(rootNode->left_child);
        return right_Rotation(rootNode);
    }

    // Right Right Case
    if (valueOfBalance < -1 &&
        find_balance (rootNode->right_child) <= 0)
        return left_Rotation(rootNode);

    // Right Left Case
    if (valueOfBalance < -1 &&
        find_balance (rootNode->right_child) > 0)
    {
        rootNode->right_child = right_Rotation(rootNode->right_child);
        return left_Rotation(rootNode);
    }

    return rootNode;
}
vector<int> res;
void searchKeys(TreeNode* rootNode, int key1,int key2){
    if(!rootNode){
        return;
    }
		if(rootNode->key < key1){
        searchKeys(rootNode->right_child,key1,key2);
    }
    else if(rootNode->key >=key1 && rootNode->key <= key2){
        searchKeys(rootNode->left_child,key1,key2);
				res.push_back(rootNode->key);
        searchKeys(rootNode->right_child,key1,key2);
    }
    else if(rootNode->key > key2){
        searchKeys(rootNode->left_child,key1,key2);
    }
}
// Driver Code

int main()
{
    //initialize tree
	TreeNode *root = NULL;
	bool flag = false;
	std::ifstream myfile;
	std::ofstream output("output_file.txt");

	myfile.open("input_file.txt");
	string mystring;
	if ( myfile.is_open() ) {
		while ( myfile.good() ) {
			myfile >> mystring;
			int ind = mystring.find('(');
			int pos = mystring.find(')');
			string temp = mystring.substr(0,ind);
			int value,v1,v2,x;
			if(temp != "Initialize" && temp != "Search"){
				 value = stoi(mystring.substr(ind+1,pos-ind-1));
			}
			else if(temp == "Search"){
				 x = mystring.find(',');
				if(x==-1){
					 value = stoi(mystring.substr(ind+1,pos-ind-1));
				}
				else{
					 v1 = stoi(mystring.substr(ind+1,x-ind-1));
					 v2 = stoi(mystring.substr(x+1,pos-x-1));
				}
			}
			if(temp != "Initialize" && flag == false){
				output << "we cannot perform any operation without initializing tree"<<endl;
				return 0;
			}
			if(temp == "Initialize"){
				root = initialize();
				flag = true;
			}
			else if(temp == "Insert"){
				root = insert(root,value);
			}
			else if(temp == "Delete"){
				deleteNode(root, value);
			}
			else if(temp == "Search" && x==-1){
					TreeNode* node1 = search(root,value);
					if(node1){
						output << node1->key<<endl;
					}
					else{
						output <<"NULL"<<endl;
					}

			}
			else if(temp == "Search" && x!=-1){
				searchKeys(root,v1,v2);
				if(res.empty()){
					output <<"NULL"<<endl;
				}
				else{
					for(int i=0;i<res.size()-1;i++){
					    	output<<res[i]<<",";
					}
					output<<res[res.size()-1]<<endl;
				}
			}
		}
	}

output.close();
	return 0;
}
