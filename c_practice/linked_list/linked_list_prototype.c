#include <stdio.h>
#include <stdlib.h>


// struct NODE{
//     struct NODE *next;
//     int data;
// };
/*
struct NODE *head = malloc(sizeof(struct NODE));
이런 식으로 선언해주어야 한다.
*/

// typedef를 사용하면 
// node *head = (node*)malloc(sizeof(node));
// 이렇게 쉽게 선언해서 쓸 수 있다
typedef struct NODE{
    struct NODE *next;
    int data;
}node;

// 기준 노드 뒤에 노드를 추가하는 함수
void appendFirst(node *target, int data)
{
    if (target == NULL)     // 기준 노드가 NULL이면 함수 종료
        return;

    node *newNode = malloc(sizeof(node));   // 새 노드 생성
    if (newNode == NULL)    // 메모리 할당에 실패하면 함수 종료
        return;
    newNode->next = target->next;           // 새 노드의 다음 노드에 기준 노드의 다음 노드를 지정
    newNode->data = data;                   // 데이터 저장

    target->next = newNode;                 // 기준 노드의 다음 노드에 새 노드를 지정
}

void removeFirst(node *target)
{
    if (target == NULL)     // 기준 노드가 NULL이면 함수를 끝냄
        return;

    node *removeNode = target->next;        // 기준 노드의 다음 노드 주소를 저장
    if (removeNode == NULL) //삭제할 노드가 NULL이면 함수 종료
        return;
    target->next = removeNode->next;        // 기준 노드의 다음 노드에 삭제할 노드의 다음 노드를 지정

    free(removeNode);
}


int main()
{
    // 헤드 노드 생성. 헤드 노드는 데이터를 저장하지 않음
    struct NODE *head = malloc(sizeof(struct NODE));

    appendFirst(head, 10);
    appendFirst(head, 20);
    appendFirst(head, 30);

    removeFirst(head);

    node *curr = head->next;
    while (curr != NULL)
    {
        printf("%d\n", curr->data);
        curr = curr->next;
    }

    curr = head->next;
    while (curr != NULL)
    {
        node *next = curr->next;    // 지울 노드의 다음 노드 주소를 저장해놓고
        free(curr);                 // 노드 지운 다음
        curr = next;                // 현재 주소에 아까 저장해놓은 다음 노드 주소를 저장(다음에 갈 주소)
    }

    free(head);

    return 0;
}