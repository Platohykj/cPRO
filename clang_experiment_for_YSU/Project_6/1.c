#include <stdio.h>

void removeDuplicates(int arr[], int *size) {
    if (*size <= 1) {
        // 如果数组长度小于等于1，无需删除重复元素
        return;
    }

    int index = 1; // 从第二个元素开始比较
    for (int i = 1; i < *size; i++) {
        int j;
        for (j = 0; j < index; j++) {
            if (arr[i] == arr[j]) {
                break; // 找到重复元素，跳出内层循环
            }
        }

        if (j == index) {
            // 如果内层循环完成，说明当前元素不重复
            arr[index] = arr[i];
            index++;
        }
    }

    *size = index; // 更新数组大小
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 3, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    // 打印原始数组
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 调用函数删除重复元素
    removeDuplicates(arr, &size);

    // 打印删除重复元素后的数组
    printf("Array after removing duplicates: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
