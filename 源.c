#define _CRT_SECURE_NO_WARNINGS
//二叉搜索树
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct BstNode{
	int data;
	struct BstNode* left;
	struct BstNode* right;
}BstNode;
BstNode* GetNewNode(int x) {
	BstNode* newnode = (BstNode*)malloc(sizeof(BstNode));
	newnode->data = x;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}
void Insert(BstNode** root, int k) {
	if (*root == NULL) {
		*root = GetNewNode(k);
	}
	else if(k >(*root)->data){
		Insert(&((*root)->right),k);
	}
	else {
		Insert(&((*root)->left), k);
	}
}
bool Search(BstNode* root, int n) {
	if (root == NULL) {
		return false;
	}
	else if (root->data == n) {
		return true;
	}
	else if (n<=root->data) {
		return Search(root->left, n);
	}
	else {
		return Search(root->right, n);
	}
}
int FindMin(BstNode* root) {
	if (root == NULL) {
		printf("Error:Tree is empty!\n");
		return NULL;
	}
	else if (root->left == NULL) {
		return root->data;
	}
	else {
		return FindMin(root->left);
	}
}
int FindMax(BstNode* root) {
	if (root == NULL) {
		printf("Error:Tree is empty!\n");
		return NULL;
	}
	else if (root->right == NULL) {
		return root->data;
	}
	else {
		return FindMin(root->right);
	}
}
int FindHeight(BstNode* root) {
	if (root == NULL) {
		return -1;
	}
	return max(FindHeight(root->left), FindHeight(root->right)) + 1;
}
BstNode* findMin(BstNode* root)//用于Delete函数
{
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}
void Delete(struct BstNode** root, int data) {
	if (*root == NULL) {
		return;
	}
	else if (data < (*root)->data) {
		Delete(&(*root)->left, data);
	}
	else if (data > (*root)->data) {
		Delete(&(*root)->right,data);
	}
	else {
		// Case 1:  No child
		if ((*root)->left == NULL &&(*root)->right == NULL) {
			free(*root);
			*root = NULL;
		}
		//Case 2: One child 
		else if ((*root)->left == NULL) {
			struct BstNode* temp = *root;
			*root = (*root)->right;
			free(temp);
		}
		else if ((*root)->right == NULL) {
			struct BstNode* temp = *root;
			*root = (*root)->left;
			free(temp);
		}
		// case 3: 2 children
		else {
			struct BstNode* temp = findMin((*root)->right);
			(*root)->data = temp->data;
			 Delete(&(*root)->right, temp->data);
		}
	}
}
int main() {
	BstNode* root = NULL;
	Insert(&root, 15);
	Insert(&root, 10);
	Insert(&root, 16);
	Insert(&root, 8);
	Insert(&root, 11);
	int num;
	printf("Enter number be searched\n");
	scanf("%d", &num);
	if (Search(root, num) == true) {
		printf("Found\n");
	}
	else {
		printf("Not Found\n");
	}
	printf("The minimum value is %d\n", FindMin(root));
	printf("The max value is %d\n", FindMax(root));
	printf("The height of tree is %d\n", FindHeight(root));
	Delete(&root, 11);
	if (Search(root, 11) == false) {
		printf("deleted 11\n");
	}
}


//树的遍历
/*
#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int data;
	struct node* left;
	struct node* right;
}node;
//队列
typedef struct queue {
	node* root;
	struct queue* next;
}queue;
queue* front = NULL;
queue* rear = NULL;
void EnQueue(node* root) {
	queue* temp = (queue*)malloc(sizeof(queue));
	temp->root = root;
	temp->next = NULL;
	if (front == NULL && rear == NULL) {
		front = temp;
		rear = temp;
		return;
	}
	rear->next = temp;
	rear = temp;
}
void DeQueue(){
	queue* temp = front;
	if (front == NULL && rear == NULL) {
		printf("queue is empty\n");
		return;
	}
	else if (front == rear) {
		front = NULL;
		rear = NULL;
	}
	else {
		front = (front->next);
	}
	free(temp);
}
//树的层次遍历
void LevelOrder(node* root) {
	if (root == NULL) {
		return;
	}
	EnQueue(root);
	while (front != NULL && rear != NULL) {
		node* current = front->root;
		printf("%d ", current->data);
		DeQueue();
		EnQueue(current->left);
		EnQueue(current->right);
	}
}
node* GetNewNode(int x) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->data = x;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}
void Insert(node** root, int k) {
	if (*root == NULL) {
		*root = GetNewNode(k);
	}
	else if (k > (*root)->data) {
		Insert(&((*root)->right), k);
	}
	else {
		Insert(&((*root)->left), k);
	}
}
int main() {
	node* root = NULL;
    Insert(&root, 10); 
    Insert(&root, 8); 
    Insert(&root, 12); 
	Insert(&root, 6);
	LevelOrder(root);
}
*/
/*
//三大遍历
#include<stdio.h>
#include<stdlib.h>
typedef struct Node {
	char data;
	struct Node* left;
	struct Node* right;
}Node;
Node* GetNewNode(int x) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = x;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}
void Insert(Node** root, int k) {
	if (*root == NULL) {
		*root = GetNewNode(k);
	}
	else if (k > (*root)->data) {
		Insert(&((*root)->right), k);
	}
	else {
		Insert(&((*root)->left), k);
	}
}
//前序遍历
void Preorder(Node* root) {
	if (root == NULL) {
		return;
	}
	printf("%c", root->data);
	Preorder(root->left);
	Preorder(root->right);
}
//中序遍历
void Inorder(Node* root) {
	if (root == NULL) {
		return;
	}
	Inorder(root->left);
	printf("%c", root->data);
	Inorder(root->right);
}
//后序遍历
void Postorder(Node* root) {
	if (root == NULL) {
		return;
	}
	Postorder(root->left);
	Postorder(root->right);
	printf("%c", root->data);
}
int main() {
	/*Code To Test the logic
	  Creating an example tree
			    M
			   / \
			  B   Q
			 / \   \
			A   C   Z
	Node* root = NULL;
	Insert(&root, 'M');
	Insert(&root, 'B'); 
	Insert(&root, 'Q');
	Insert(&root, 'A');
	Insert(&root, 'C');
	Insert(&root, 'Z');
	printf("preorder:");
	Preorder(root);
	printf("\n");
	printf("inorder:");
	Inorder(root);
	printf("\n");
	printf("postorder:");
	Postorder(root);
	printf("\n");
}
*/


