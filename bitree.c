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
	int arr[9] = {1,3,4,7,8,9,2,6,5};
	for (int i = 0 ; i < sizeof(arr) / sizeof(*arr) ; i ++)
	{
		tmp.id = arr[i];
		snprintf(tmp.name,MAX,"stu%d",i + 1);
		insert(&tree,&tmp);
	}
	//Travse the tree in preOrder
	PreOrder(tree);
	//the object value

	draw(tree,0);
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
	return 0;

}

#endif
