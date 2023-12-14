#include <stdio.h>
#include <stdlib.h>
//定义链表结构
struct node {
    int data;
    struct node *next;
};
typedef struct node node;
//创建一个空链表
node *list_create(){
    node* list = (node*)malloc(sizeof(node));
    if(list == NULL) {
        printf("Error creating a new list.\n");
        exit(0);
    }
    list->data = 0;
    list->next = NULL;
    return list;
}
//添加
//插入一个元素
void list_insert(node *list, int data) {
    node *temp = list;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    temp->next = new_node;
}
//删除一个元素
void list_delete(node *list, int data) {
    node *temp = list;
    while(temp->next != NULL) {
        if(temp->next->data == data) {
            node *delete_node = temp->next;
            temp->next = temp->next->next;
            free(delete_node);
            return;
        }
        temp = temp->next;
    }
}
//查找一个元素
node *list_find(node *list, int data) {
    node *temp = list->next;
    while(temp != NULL) {
        if(temp->data == data) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
//修改一个元素
void list_modify(node *list, int old_data, int new_data) {
    node *temp = list->next;
    while(temp != NULL) {
        if(temp->data == old_data) {
            temp->data = new_data;
            return;
        }
        temp = temp->next;
    }
}
//链表长度
int list_length(node *list) {
    int len = 0;
    node *temp = list->next;
    while(temp != NULL) {
        len++;
        temp = temp->next;
    }
    return len;
}
//链表是否为空
int list_is_empty(node *list) {
    return list->next == NULL;
}
//清空链表
void list_clear(node *list) {
    node *temp = list->next;
    while(temp != NULL) {
        node *delete_node = temp;
        temp = temp->next;
        free(delete_node);
    }
    list->next = NULL;
}
//销毁链表
void list_destroy(node *list) {
    list_clear(list);
    free(list);
}
//获取第index个元素
int list_get_(node *list, int index) {
    if(index < 0 || index >= list_length(list)) {
        printf("Error: index out of range.\n");
        exit(0);
    }
    node *temp = list->next;
    for(int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->data;
}
//设置第index个元素
void list_set(node *list, int index, int data) {
    if(index < 0 || index >= list_length(list)) {
        printf("Error: index out of range.\n");
        exit(0);
    }
    node *temp = list->next;
    for(int i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->data = data;
}
//打印链表
void list_print(node *list) {
    node *temp = list->next;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

}
//测试

int main() {
    int array[] = {1, 2, 3, 4, 5};
    node *list = list_create_with_array(array, 5);
    list_print(list);
    return 0;
}
