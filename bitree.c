#include <stdio.h>
#include <stdlib.h>

#define MAX 20


struct score_st{
	int id;
	char name[MAX];
};

typedef struct node_st{
	struct score_st data;
	struct node_st * LeftPtr;
	struct node_st * RightPtr;
}Bitree,*PBitree;

/*This function is used for Finding the Min value in Binary Search Tree
with the reversed method
*/
struct node_st * FindMin(struct node_st * root)
{
	if (root == NULL)
		return NULL;
	if (root->LeftPtr == NULL)
		return root;
	else
		return FindMin(root->LeftPtr);
}
/*
	The function is used for remove one node from the 
	Binary Search Tree
*/
struct node_st * Delete(struct node_st * root,int value)
{
	struct node_st * node;

	if (root == NULL)
		return NULL;
	//go to the leftSide
	else if(root->data.id > value)
		root->LeftPtr = Delete(root->LeftPtr,value);
	//go to the rightSide
	else if(root->data.id < value)
		root->RightPtr = Delete(root->RightPtr,value);
	//the node has both left and right child 
	else if(root->LeftPtr != NULL && root->RightPtr != NULL)
	{
		node = FindMin(root->RightPtr);
		root->data.id = node->data.id;
		root->RightPtr = Delete(root->RightPtr,root->data.id);
	}
	//has one or zero child
	else
	{
		node = root;
		if(root->LeftPtr == NULL)
			root = root->RightPtr;
		else if(root->RightPtr == NULL)
			root = root->LeftPtr;
		free(node);
	}
	//return the pointer to the parent-call function
	return root;

}

/*This function is used for Finding the MAX value in Binary Search Tree
with a non-reverse method
*/ 
struct node_st * FindMax(struct node_st * root)
{
	if (root == NULL)
		return NULL;
	while(root->RightPtr)
	{
		root = root->RightPtr;
	}
	return root;
}
struct node_st * search(struct node_st * root,int id)
{
	struct node_st * t;
	t = root;
	while(t)
	{
		if (t->data.id == id)
			return t;
		if (t->data.id > id)
			t = t->LeftPtr;
		else
			t = t->RightPtr;
	}
	return NULL;
}
void draw(struct node_st * root,int level)
	{
		if (root == NULL)
			return ;
		draw(root->RightPtr,level + 1);

		for (int i = 0 ; i < level ; i ++)
			printf("    ");
		printf("%d\n",root->data.id);

		draw(root->LeftPtr,level + 1);
	}
struct node_st * find(struct node_st * root,int id)
{
	if (root == NULL)
		return NULL;
	if(root->data.id == id)
		return root;
	if(root->data.id >= id)
		return find(root->LeftPtr,id);
	return find(root->RightPtr,id);
}
void PreOrder(PBitree  root)
{
	if (root != NULL)
	{
		printf("%d-%s\n",root->data.id,root->data.name);
		PreOrder(root->LeftPtr);
		PreOrder(root->RightPtr);
	}
}

int insert(struct node_st ** root,struct score_st * data)
{	
	struct node_st * node;
	if (*root == NULL)
	{
		node = (node_st*)malloc(sizeof(*node));
		if (node == NULL)
			return -1;
		node->data = *data;
		node->LeftPtr = NULL;
		node->RightPtr = NULL;

		*root = node;
		return 0;
	}
	if (data->id <= (*root)->data.id)
		return insert(&(*root)->LeftPtr,data);
	return insert(&(*root)->RightPtr,data);
}

int main()
{
	//Define a root node of the Bitree
	struct node_st * tree = NULL;
	//Define a temperary-test Node data
	struct score_st tmp;
	//Define the test data
	//1,3,4,7,8,9,2,6,5
	//6,2,8,1,5,3,4
	//11,23,4,75,38,99,256,6,54
	int arr[] = {11,23,4,75,38,99,256,6,54};
	for (int i = 0 ; i < sizeof(arr) / sizeof(*arr) ; i ++)
	{
		tmp.id = arr[i];
		snprintf(tmp.name,MAX,"stu%d",i + 1);
		insert(&tree,&tmp);
	}
	#if 1
	//This module is to travse the tree in PreOrder
	PreOrder(tree);
	#endif
	#if 1
	//this module is used for finding the minimum value
	struct node_st * res;
	res = FindMin(tree);
	printf("%d",res->data.id);
	#endif
	#if 1
	//this module is used for drawing the tree
	draw(tree,0);
	#endif
	#if 0
	int value;
	printf("Please input the value you want to find:\n");
	//To get the return result
	scanf("%d",&value);
	struct node_st *ret;
	ret = find(tree,value);

	if (ret == NULL)
		printf("Cannot find the value!\n");
	else
		printf("find the %d info",ret->data.id);
	#endif
	#if 0
	int value;
	printf("Please input the value you want to find:\n");
	//To get the return result
	scanf("%d",&value);
	struct node_st *ret;
	ret = search(tree,value);

	if (ret == NULL)
		printf("Cannot find the value!\n");
	else
		printf("find the %d info",ret->data.id);
	#endif
	#if 1
	//this module is used for deleting...
	int value;
	printf("Please input the value you want to remove:\n");
	//To get the return result
	scanf("%d",&value);
	struct node_st *ret;
	ret = Delete(tree,value);

	if (ret == NULL)
		printf("Cannot find the value!\n");
	else
		draw(ret,0);
	#endif
	return 0;

}
