/*
 * Binary Search Tree #1
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {  //연결리스트구조를 활용한 이진탐색트리
	int key;
	struct node *left;  //왼쪽 자식노드에 대한 포인터
	struct node *right;  //오른쪽 자식노드에 대한 포인터
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
void freeNode(Node* ptr);
/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

  printf("[----- [HanSeungheon] [%d] -----]\n", 2020023057);
  
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)  
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));  //트리가 비어있다면 헤드노드에 메모리 할당
	(*h)->left = NULL;	/* root */  
	(*h)->right = *h;  //자기 자신을 가리키도록 한다
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)  //중위순회
{
	if(ptr) {
		inorderTraversal(ptr->left);   
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);  
	}
}

void preorderTraversal(Node* ptr)  //전위순회
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left); 
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)  //후위순회
{
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));  //새로운 노드 생성 및 메모리 동적할당
	newNode->key = key;  //입력받은 키값 대입
	newNode->left = NULL;  //왼쪽 자식 노드에 대한 포인터 초기화
	newNode->right = NULL;  //오른쪽 자식 노드에 대한 포인터 초기화

	if (head->left == NULL) { //루트 노드가 비었다면
	 	head->left = newNode;  //헤드에 뉴노드 주소 대입
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;  

	Node* parentNode = NULL;
	while(ptr != NULL) { //루트노드가 null이 아닐 때

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;  //부모노드에 루트노드주소 입력

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)  //루트 노드의 키값보다 클 때
			ptr = ptr->right;  //오른쪽 트리로
		else
			ptr = ptr->left;  //작다면 왼쪽트리로
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)  // 입력한 값이 부모노드의 키값보다 클 때, 
		parentNode->left = newNode;  //왼쪽트리로
	else
		parentNode->right = newNode;  //작다면 오른쪽 트리로
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {  //헤드노드가 NULL임을 확인하는 프리컨디션 조사
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;  //루트노드를 가리키는 포인터 선언


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;  //헤드노드를 가리키는 포인터 선언

	while(ptr != NULL) {  //루트노드가 NULL임을 확인하는 프리컨디션 조사

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				/* root node case */
				if(parentNode == head)
					head->left = NULL;  //루트노드가 비었을 때

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;  //오른쪽 자식 트리의 노드로
		else
			ptr = ptr->left;  //왼쪽 자식 트리의 노드로


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)  //재귀방식의 탐색
{
	if(ptr == NULL)  //헤드노드가 NULL을 확인하는 프리컨디션 조사
		return NULL;

	if(ptr->key < key)  //키값이 작으면 
		ptr = searchRecursive(ptr->right, key);  //ptr 값 변경 및 함수 재귀 호출 
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);  //ptr 값 변경 및 함수 재귀 호출

	/* if ptr->key == key */
	return ptr;  //ptr반환

}

Node* searchIterative(Node* head, int key)  //반복탐색
{
	/* root node */
	Node* ptr = head->left;  //ptr = root

	while(ptr != NULL) //root != null
	{
		if(ptr->key == key)  //키값이 바로 일치
			return ptr;  //ptr 반환

		if(ptr->key < key) ptr = ptr->right;  //왼쪽트리 버리고 오른쪽 이동
		else
			ptr = ptr->left;  //왼쪽트리만 조사하기 위한 조건
	}

	return NULL;
}

void freeNode(Node* ptr)  //메모리 할당
{
	if(ptr) {
		freeNode(ptr->left);  //재귀구조 
		freeNode(ptr->right);  //재귀구조
		free(ptr);  //ptr할당 해제
	}
}

int freeBST(Node* head)  //할당된 모든 메모리 할당 해제
{

	if(head->left == head)  //노드가 비었다면
	{
		free(head); //헤드노드해제
		return 1;
	}

	Node* p = head->left;  //루트노드 주소 대입

	freeNode(p);  //루트노드 메모리 해제

	free(head);  //헤드노드 메모리 해제
	return 1;
}





