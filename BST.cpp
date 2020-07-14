// 6week 12171788 박지은

#include <stdio.h>
#include <stdlib.h>

typedef struct NodeStruct
{
	int value;
	struct NodeStruct* leftChild;
	struct NodeStruct* rightChild;
}Node;

Node* root = NULL;

Node* BST_insert(Node* root, int value)
{
	if (root == NULL)
	{
		root = (Node*)malloc(sizeof(Node));
		root->leftChild = root->rightChild = NULL;
		root->value = value;
		return root;
	}
	else
	{
		if (root->value > value)
			root->leftChild = BST_insert(root->leftChild, value);
		else
			root->rightChild = BST_insert(root->rightChild, value);
	}
	return root;
}

Node* findMinNode(Node* root)
{
	Node* tmp = root;
	while (tmp->leftChild != NULL)
		tmp = tmp->leftChild;
	return tmp;
}

Node* BST_delete(Node* root, int value)
{
	Node* tNode = NULL;
	if (root == NULL)
		return NULL;

	if (root->value > value)
		root->leftChild = BST_delete(root->leftChild, value);
	else if (root->value < value)
		root->rightChild = BST_delete(root->rightChild, value);
	else
	{
		if (root->rightChild != NULL && root->leftChild != NULL)
		{
			tNode = findMinNode(root->rightChild);
			root->value = tNode->value;
			root->rightChild = BST_delete(root->rightChild, tNode->value);
		}
		else
		{
			tNode = (root->leftChild == NULL) ? root->rightChild : root->leftChild;
			free(root);
			return tNode;
		}
	}

	return root;
}

bool getIndex(Node* root, int value)
{
	NodeStruct *Cur = root;
	while (1) {
		if (Cur->value == value) {
			return true;
		}
		if (Cur->value < value) {
			if (Cur->rightChild == NULL) return false;
			Cur = Cur->rightChild;
		}
		else {
			if (Cur->leftChild == NULL) return false;
			Cur = Cur->leftChild;
		}
	}
}

void BST_print(Node* root)
{
	if (root == NULL) return;

	printf("%d\n", root->value);
	BST_print(root->leftChild);
	BST_print(root->rightChild);
}

int main()
{
	int input;
	int input2;
	int num = 0;

	while (1) {
		scanf("%d", &input);

		if (input > 0) {
			num++; // input 8개 제한
			if(num <= 8) root = BST_insert(root, input);
		}
		else if (input < 0) {
			num = 0;
			input2 = abs(input);

			if (getIndex(root,input2) == true) {
				printf("%d\n", input2);
				root = BST_delete(root, input2);
			}
			else if (getIndex(root, input2) == false) {
				printf("0\n");
			}
		}
		else if (input == 0) {
			BST_print(root);
			break;
		}
	}

	return 0;
}
