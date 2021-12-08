// 입력받은 문자열만큼 링크드리스트를 만들고 
// 그 다음 입력받은 문자열과 같은 데이터를 가진 노드를 삭제하고 출력하는 프로그램.

// input : 첫 줄에 리스트에 추가할 데이터 개수, 그 다음줄부터 추가할 문자열, 맨 마지막 줄은 삭제할 문자열
// 3
// star
// flower
// cloud
// flower


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE{
    char *data;
    struct NODE *next;
}node;

void appendFirst(node *target, char* data)
{
    if (target == NULL)
        return;

    node *newNode = malloc(sizeof(node));
    if (newNode == NULL)
        return;
    newNode->next = target->next;
    newNode->data = data;

    target->next = newNode;
}

void removeNode(node *target)
{
    if (target == NULL)
        return;

    node *removeNode = target->next;
    if (removeNode == NULL)
        return;
    target->next = removeNode->next;

    free(removeNode);
}

int main()
{
    node *head = malloc(sizeof(node));
    head->next = NULL;

    int testcase;
    scanf("%d\n", &testcase);
    for (int i = 0; i < testcase; i++)
    {
        char *data;
        // 이렇게 식을 짜면 메모리 할당에 실패했을 때 프로그램을 종료하게 할 수 있다.
        if (!(data = (char *)malloc(sizeof(char) * 10)))
            return 0;

        scanf("%s", data);
        // printf("%p\n", data);
        
        appendFirst(head, data);
    }
    
    // 입력받은 하나의 문자열과 같은 데이터를 가진 노드 삭제
    char *rm_str = (char *)malloc(sizeof(char) * 10);
    scanf("%s", rm_str);
    node *curr = head;
    while (curr != NULL)
    {
        if (curr->next == NULL)
            break;

        if (strcmp(curr->next->data, rm_str) == 0)
        {
            removeNode(curr);
            break;
        }

        curr = curr->next;
    }

    // 링크드리스트의 요소 출력
    curr = head->next;
    while (curr != NULL)
    {
        printf("%s\n", curr->data);
        curr = curr->next;
    }

    // 링크드 리스트 메모리 해제
    curr = head->next;
    while (curr != NULL)
    {
        node *next = curr->next;    // 지울 노드의 다음 노드 주소를 저장해놓고
        free(curr);                 // 노드 지운 다음
        curr = next;                // 현재 주소에 아까 저장해놓은 다음 노드 주소를 저장
    }

    free(head);
    free(rm_str);

    return 0;
}