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

// 添加会员
void addMember(struct Member** head, int id, const char* name, int age) {
    struct Member* newMember = (struct Member*)malloc(sizeof(struct Member));
    newMember->id = id;
    strcpy(newMember->name, name);
    newMember->age = age;
    newMember->next = *head;
    *head = newMember;
}

// 删除会员
void deleteMember(struct Member** head, int id) {
    struct Member* current = *head;
    struct Member* previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current != NULL) {
        if (previous == NULL) {
            *head = current->next;
        } else {
            previous->next = current->next;
        }
        free(current);
    }
}

// 修改会员信息
void updateMember(struct Member* head, int id, const char* newName, int newAge) {
    struct Member* current = head;

    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current != NULL) {
        strcpy(current->name, newName);
        current->age = newAge;
    }
}

// 查找会员
struct Member* findMember(struct Member* head, int id) {
    struct Member* current = head;

    while (current != NULL && current->id != id) {
        current = current->next;
    }

    return current;
}

// 显示所有会员信息
void displayMembers(struct Member* head) {
    struct Member* current = head;

    while (current != NULL) {
        printf("ID: %d, Name: %s, Age: %d\n", current->id, current->name, current->age);
        current = current->next;
    }
}

// 释放链表内存
void freeMembers(struct Member* head) {
    struct Member* current = head;
    struct Member* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    struct Member* members = NULL;

    // 添加几个示例会员
    addMember(&members, 1, "Alice", 25);
    addMember(&members, 2, "Bob", 30);
    addMember(&members, 3, "Charlie", 22);

    // 显示所有会员信息
    printf("All Members:\n");
    displayMembers(members);

    // 查找并修改会员信息
    struct Member* foundMember = findMember(members, 2);
    if (foundMember != NULL) {
        printf("\nUpdating Member with ID 2:\n");
        updateMember(members, 2, "Bob Updated", 35);
        displayMembers(members);
    }

    // 删除一个会员
    printf("\nDeleting Member with ID 1:\n");
    deleteMember(&members, 1);
    displayMembers(members);

    // 释放内存
    freeMembers(members);

    return 0;
}
