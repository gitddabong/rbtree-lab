// 이진 탐색 트리

#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    int data;
    struct NODE *left;
    struct NODE *right;
}Node;

Node* root = NULL;

Node* BST_insert(Node* root, int data)
{
    // 노드에 아무것도 없는 경우
    if (root == NULL)
    {
        root = (Node*)malloc(sizeof(Node)); // 동적으로 메모리를 할당해서 그 주소를 root에 저장
        root->left = root->right = NULL;    // 아직 양쪽 노드가 없으니 null
        root->data = data;                  // 노드에 입력받은 데이터 추가
        return root;                        // 아까 할당받은 메모리 주소를 root에 리턴
    }

    // 노드가 비어있지 않을 때
    else
    {
        if (root->data > data)  // 루트의 데이터 값이 더 크면 data는 왼쪽에 삽입
            root->left = BST_insert(root->left, data);
        else    // 루트의 데이터 값이 작은 경우 data는 오른쪽에 삽입
            root->right = BST_insert(root->right, data);
    }
    return root;
}

// 이진 탐색 트리에서 최솟값을 찾으려면 맨 왼쪽으로만 타고 가면 나옴
// 루트 기준 최솟값을 가지는 노드의 주소값을 리턴
Node* findMinNode(Node* root)
{
    Node* tmp = root;
    while (tmp->left != NULL)
        tmp = tmp->left;
    return tmp;
}

// 입력받은 data와 같은 값을 가지는 노드 삭제
Node* BST_delete(Node* root, int data)
{
    Node* tNode = NULL;
    if (root == NULL)
        return NULL;

    // 입력받은 data가 작은 경우 왼쪽 서브트리로 이동
    if (root->data > data)
        root->left = BST_delete(root->left, data);
    // 입력받은 data가 큰 경우 오른쪽 서브트리로 이동
    else if (root->data < data)
        root->right = BST_delete(root->right, data);
    // 찾았다
    // 그냥 삭제하면 안되고 자식들은 다 연결해주고 자신만 나와야 함
    else
    {
        // 삭제할 노드가 자식이 둘 다 있는 경우
        if (root->right != NULL && root->left != NULL)
        {
            tNode = findMinNode(root->right);   // tNode에 루트의 오른쪽 서브트리에서 최솟값을 가진 노드 주소 삽입
            root->data = tNode->data;           // 최솟값 데이터를 삭제하려는 노드의 값으로 변경
            root->right = BST_delete(root->right, tNode->data);     // 원본 노드 삭제하고 넘어온 리턴 값을 오른쪽 자식으로 갱신
        }
        // 어느 한 쪽이라도 없는 경우
        else
        {
            // 왼쪽 자식이 없다면 tNode에 오른쪽 자식을, 아니면 왼쪽 자식을 넣기
            // 둘 다 없으면 return NULL; 이 되겠네
            tNode = (root->left == NULL) ? root->right : root->left;
            free(root);
            return tNode;   // 바꿔치기한 자식의 주소를 리턴
        }
    }
    return root;
}

// 입력받은 데이터가 있는지 확인
Node* BST_search(Node* root, int data)
{
    if (root == NULL)
        return NULL;

    if (root->data == data)
        return root;
    else if (root->data > data)
        return BST_search(root->left, data);
    else
        return BST_search(root->right, data);
}

// 전위 순회
void BST_print(Node* root)
{
    if (root == NULL)
        return;
    
    printf("%d ", root->data);
    BST_print(root->left);
    BST_print(root->right);
}

// 메모리 해제
void BST_free(Node* root)
{
    if (root == NULL)
        return;
    
    BST_free(root->left);
    BST_free(root->right);
    free(root);
}

int main()
{
    // int testcase;
    // scanf("%d\n", &testcase);
    // for (int i = 0; i < testcase; i++)
    // {
    //     int data;
    //     scanf("%d\n", &data);
    //     root = BST_insert(root, data);
    // }


    root = BST_insert(root, 5);
    root = BST_insert(root, 3);
    root = BST_insert(root, 7);
    root = BST_insert(root, 1);
    root = BST_insert(root, 9);
    root = BST_insert(root, 6);
    BST_print(root);
    printf("\n");
    root = BST_delete(root, 7);

    BST_print(root);
    BST_free(root);
    return 0;
}