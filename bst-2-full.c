#include <stdio.h>
#include <stdlib.h>

typedef struct node { //트리 구조체 선언 데이터와 왼쪽과 오른쪽자식이 있음
	int key; //데이터
	struct node *left; //왼쪽 노드 
	struct node *right;  //오른쪽 노드
} Node;

/* for stack */
#define MAX_STACK_SIZE	20 // 스텍 맥스 사이즈 20
Node* stack[MAX_STACK_SIZE]; //Node형 포인터 배열 stack선언 20만큼
int top = -1;

Node* pop(); //Node포인터형 함수 선언 기능 pop
void push(Node* aNode); //기능 push

/* for queue */
#define MAX_QUEUE_SIZE	20 // 큐 사이즈 20
Node* queue[MAX_QUEUE_SIZE]; //Node형 포인터 배열 queue선언 20만큼
int front = -1;
int rear = -1;

Node* deQueue(); //큐에 element를 빼내는 함수 
void enQueue(Node* aNode); //큐에 element을 추가 하는 함수

int initializeBST(Node** h);  //초기화 함수

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;  // 문자형 변수 선언
	int key; // / int형 변수 선언 트리 노드에 넣을 키를 받음
	Node* head = NULL; // 해드 노드 선언
	printf("[----- [kim dongmin] [2017038093] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //기능 선택

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); //초기화
			break;
		case 'q': case 'Q':
			freeBST(head); //트리에 할당된 모든 메모리를 해제
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); //키값 입력받음
			insert(head, key); //트리에 노드 삽입
			break;
		case 'd': case 'D': 
			printf("Your Key = ");
			scanf("%d", &key); //키값 입력받음
			deleteNode(head, key); //키에 맞는 노드 삭제
			break;

		case 'r': case 'R':
			recursiveInorder(head->left); //중위 순회하여 트리 출력
			break;
		case 't': case 'T':
			iterativeInorder(head->left); // 반복적인 중위 순회 하여 출력
			break;

		case 'l': case 'L':
			levelOrder(head->left); //레벨 순서 순회 히여 출력
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //잘못입력에 대한 오류 처리
			break;
		}

	}while(command != 'q' && command != 'Q'); //'q' && 'Q' 이면 반복문 종료

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //해드가 가리키는 곳이 널이 아니면 
		freeBST(*h); //트리에 할당된 모든 메모리를 해제

	/* create a head node */ //해드를 만들어줌 초기상태
	*h = (Node*)malloc(sizeof(Node)); //동적할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; //자기자신 
	(*h)->key = -9999;  // 데이터

	top = -1; //top -1

	front = rear = -1;

	return 1; //리턴 1
}



void recursiveInorder(Node* ptr) //중위 순회 함수
{
	if(ptr) {
		recursiveInorder(ptr->left); //왼쪽으로 이동하고 다시 중위 순회
		printf(" [%d] ", ptr->key);  // 노드 키값 출력
		recursiveInorder(ptr->right); //오른쪽으로 이동하고 다시 중위 순회
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) // 반복적인 중위 순회 하여 출력
{
	for(;;)
	{
		for(; node; node = node->left) 
			push(node); //스텍에 삽입
		node = pop(); //스택에서 삭제

		if(!node) break; // 공백 스택
		printf(" [%d] ", node->key); // 출력

		node = node->right; // 노드에  다음 노드 대입
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //레벨 순서 순회 히여 출력
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */
 
	enQueue(ptr); //enQueue 함수에 매개변수 ptr

	for(;;) //반복
	{
		ptr = deQueue(); 
		if(ptr) {
			printf(" [%d] ", ptr->key); //출력

			if(ptr->left)
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
			break;

	}

}


int insert(Node* head, int key) //트리에 노드 삽입하는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // 동적할당
	newNode->key = key; //노드에 받은 키값 대입
	newNode->left = NULL; //왼쪽 노드 NULL
	newNode->right = NULL; // 오른쪽 NULL

	if (head->left == NULL) { // 해드 왼쪽 하위 노드가 없는 경우
		head->left = newNode; //해드 왼쪽 하위 노드에 새로운 노드 삽입
		return 1; //리턴 1
	}

	/* head->left is the root */
	Node* ptr = head->left; // Node형 포인터 구조체 ptr선언 해드 노드의 왼쪽 하위 노드 주소 대입

	Node* parentNode = NULL; //Node형 포인터 구조체 parentNode선언
	while(ptr != NULL) { // 반복문 ptr이 널이 될때까지

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //키와 같은 노드가 있으면 리턴1

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //parentNode에 ptr대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)  //ptr 키값이 입력 받은 키값 보다 작은 경우
			ptr = ptr->right;  //오른쪽 하위 트리로 이동
		else
			ptr = ptr->left; //외쪽 하위 트리로 이동
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) // 노드의 키가 입력받은 키값보다 큰 경우
		parentNode->left = newNode;  //하위 왼쪽 트리에 새노드
	else
		parentNode->right = newNode; // 오른 쪽 트리에 새노드
	return 1; // 리턴1
}


int deleteNode(Node* head, int key) //데이터에 맞는 노드 삭제 하는 함수
{
	if (head == NULL) { //해드가 널인 경우
		printf("\n Nothing to delete!!\n"); // 오류 출력
		return -1;  //리턴 -1
	}

	if (head->left == NULL) { // 해드 왼쪽 하위 노드가 없는 경우
		printf("\n Nothing to delete!!\n"); //오류 출력
		return -1; //리턴 -1
	}

	/* head->left is the root */
	Node* root = head->left; // Node형 포인터 구조체 root선언 해드 노드의 왼쪽 하위 노드 주소 대입



	Node* parent = NULL; // Node형 포인터 구조체 parent선언
	Node* ptr = root; // Node형 포인터 구조체 ptr선언 하고 root 대입

	while((ptr != NULL)&&(ptr->key != key)) { //반복문 ptr != NULL 이고 ptr->key != key일 때
		if(ptr->key != key) {  //조건문 ptr키 값이 입력 받은 키값과 다른 경우 

			parent = ptr;	/* save the parent */

			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	/* there is no node for the key */
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;

		}

		free(ptr);
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
		if (ptr->left != NULL)
			child = ptr->left;
		else
			child = ptr->right;

		if(parent != NULL)
		{
			if(parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr);
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;

	free(candidate); //동적할당해제
	return 1;
}


void freeNode(Node* ptr)// 트리에 할당된 모든 메모리를 해제 하는 함수
{
	if(ptr) { // 트리에 할당된 모든 메모리를 해제
		freeNode(ptr->left); //왼쪽 하위 노드로 이동하고 다시freeNode
		freeNode(ptr->right); //오른쪽 하위 노드로 이동하고 다시 freeNode
		free(ptr);  //동적할당 해제
	}
}

int freeBST(Node* head) //트리에 할당된 모든 메모리를 해제 하는 함수 해드도
{

	if(head->left == head) // 자기 자신일때
	{
		free(head); //해드 동적할당 해제
		return 1; //리턴1
	}

	Node* p = head->left; // Node형 포인터 구조체 p선언 해드 노드의 왼쪽 하위 주소 대입

	freeNode(p);// 트리에 할당된 모든 메모리를 해제

	free(head);// 해드 해제
	return 1; //리턴 1
}



Node* pop() //스택에 추가하는 함수
{
	if (top < 0) return NULL; //스택이 비었을 경우
	return stack[top--];
}

void push(Node* aNode)
{
	stack[++top] = aNode; //노드에 추가
}


void printStack() 
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue() //큐에 element를 빼내는 함수 
{
	if (front == rear) {  //비어있는 지 확인
		// printf("\n....Now Queue is empty!!\n" );
		return NULL; //리턴 NULL
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];

}

void enQueue(Node* aNode) //큐에 element을 추가 하는 함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear+ 1에 저장
	if (front == rear) { //큐가 Full인지 확인
		// printf("\n....Now Queue is full!!\n");
		return; //리턴
	}

	queue[rear] = aNode;
}