#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义会员结构体
struct Member {
    int id;
    char name[50];
    int age;
    struct Member* next;
};

// 函数声明
struct Member* createMember(int id, const char* name, int age);
void addMember(struct Member** head, struct Member* newMember);
void printMembers(const struct Member* head);
void freeMembers(struct Member* head);

int main() {
    struct Member* members = NULL;

    // 添加会员
    addMember(&members, createMember(1, "John Doe", 25));
    addMember(&members, createMember(2, "Jane Smith", 30));
    addMember(&members, createMember(3, "Bob Johnson", 22));

    // 打印会员信息
    printf("Members:\n");
    printMembers(members);

    // 释放内存
    freeMembers(members);

    return 0;
}

// 创建新会员
struct Member* createMember(int id, const char* name, int age) {
    struct Member* newMember = (struct Member*)malloc(sizeof(struct Member));
    if (newMember == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    newMember->id = id;
    strncpy(newMember->name, name, sizeof(newMember->name) - 1);
    newMember->age = age;
    newMember->next = NULL;

    return newMember;
}

// 添加新会员到链表
void addMember(struct Member** head, struct Member* newMember) {
    if (*head == NULL) {
        *head = newMember;
    } else {
        struct Member* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newMember;
    }
}

// 打印会员信息
void printMembers(const struct Member* head) {
    const struct Member* current = head;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Age: %d\n", current->id, current->name, current->age);
        current = current->next;
    }
}

// 释放链表内存
void freeMembers(struct Member* head) {
    struct Member* current = head;
    while (current != NULL) {
        struct Member* next = current->next;
        free(current);
        current = next;
    }
}
