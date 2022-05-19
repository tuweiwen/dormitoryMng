#ifndef _STU_H_
#define _STU_H_
#include "stu.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// 二分查找学生信息(返回数组下标，未找到则返回-1)
int binSearch(stu stuArray[], int l, int r, int idFind) {
    if(l > r)
        return -1;
    int mid = (l + r) / 2;
    if(stuArray[mid].id == idFind)
        return mid;
    if(stuArray[mid].id < idFind)
        binSearch(stuArray, mid + 1, r, idFind);
    else
        binSearch(stuArray, l, mid - 1, idFind);
}

// 快速排序
void quickSort(stu* stuArray, int l, int r) {
    if (l < r) {
        int i = l, j = r;
        stu x = stuArray[l];
        while (i < j) {
            while (i < j && stuArray[j].id > x.id) j--;
            if (i < j) {
                stuArray[i] = stuArray[j];
                i++;
            }
            while (i < j && stuArray[i].id < x.id) i++;
            if (i < j) {
                stuArray[j] = stuArray[i];
                j--;
            }
        }
        stuArray[i] = x;
        quickSort(stuArray, l, i - 1);
        quickSort(stuArray, i + 1, r);
    }
}

// 选择排序
void chooseSort(stu* stuArray, int len) {
    for(int i = 0; i < len - 1; i++) {
        int minIndex = i;
        for(int j = i + 1; j < len; j++) {
            if(stuArray[minIndex].id > stuArray[j].id) {
                minIndex = j;
            }
        }
        stu swapTemp = stuArray[minIndex];
        stuArray[minIndex] = stuArray[i];
        stuArray[i] = swapTemp;
    }
}

// 学生信息数组排序
void sortArray(stu* stuArray, int len) {
    time_t t;
    srand((unsigned) time(&t));
    // 使用随机数种子生成随机数，随机选择一种排序方式
    switch (rand() % 2) {
        case 0:
            quickSort(stuArray, 0, len - 1);
            break;
        case 1:
            chooseSort(stuArray, len);
            break;
    }
    return;
}

// 创建学生信息
void create(stu* stuArray, int* len) {
    // 判断系统内存储数据是否已满
    if((*len) >= arrayMaxLen) {
        printf("系统已满，请删除部分学生数据后再进行添加操作 !\n");
        return;
    }

    int id;
    char name[40], dorm[10];
    printf("请输入学号 : ");
    scanf("%d", &id);

    // 判断系统中是否已经存在
    if(binSearch(stuArray, 0, (*len) - 1, id) != -1) {
        printf("系统中已存在该学生信息，请勿重复添加 ! \n");
        system("pause");
        return;
    }

    printf("请输入姓名 : ");
    scanf("%s", &name);
    printf("请输入宿舍号 : ");
    scanf("%s", &dorm);

    stuArray[*len].id = id;

    // strcpy(stuArray[*len].name, name);
    // strcpy(stuArray[*len].dorm, dorm);

    stuArray[*len].name = (char*)malloc(sizeof(char) * strlen(name));
    strcpy(stuArray[*len].name, name);

    stuArray[*len].dorm = (char*)malloc(sizeof(char) * strlen(dorm));
    strcpy(stuArray[*len].dorm, dorm);

    sortArray(stuArray, (*len) + 1);
    (*len) = (*len) + 1;
    printf("添加成功 ! \n");
    system("pause");
    return;
}

// 查询学生信息
void retrieve(stu stuArray[], int len) {
    int id;
    printf("请输入需要查找的学号 : ");
    scanf("%d", &id);

    int i = binSearch(stuArray, 0, len - 1, id);
    if(i != -1) {
        printf("在系统中查询到相关结果 : \n");
        printf("学号 : %d\n", stuArray[i].id);
        printf("姓名 : %s\n", stuArray[i].name);
        printf("宿舍号 : %s\n", stuArray[i].dorm);
        system("pause");
        return;
    }

    // 查询失败
    printf("未查询到相关结果，请检查是否输入正确 !\n");

    system("pause");
    return;
}

// 更新学生信息
void update(stu* stuArray, int len) {
    int id, index;
    printf("请输入需要更新信息的学生学号 : ");
    scanf("%d", &id);

    // 先查询再更新
    index = binSearch(stuArray, 0, len - 1, id);
    if(index == -1) {
        printf("未查询到相关结果，因此无法进行更新操作。\n请检查是否输入正确 !\n\n");
        system("pause");
        
        return;
    }

    char buff[10];
    printf("搜索到学生 : %s\n", stuArray[index].name);
    printf("请输入新的宿舍号 : ");
    scanf("%s", &buff);

    strcpy(stuArray[index].dorm, buff);
    printf("修改成功! \n");

    system("pause");
    return; 
}

// 删除学生信息
void deleteStu(stu* stuArray, int* len) {
    // 判断系统是否为空
    if((*len) <= 0) {
        printf("系统数据为空，无需删除数据 ! \n");
        system("pause");
        return;
    }

    int id;
    printf("请输入需要删除的学生学号 : ");
    scanf("%d", &id);

    // 查找信息再删除
    int index = binSearch(stuArray, 0, *len - 1, id);
    if(index == -1) {
        printf("未查询到相关结果，因此无法进行删除操作。\n请检查是否输入正确 !\n");
        system("pause");
        
        return;
    }

    for(int i = index + 1; i < *len; i++)
        stuArray[i - 1] = stuArray[i];
    // 把删除的学生信息清空，重点注意指针部分需要重新赋值
    stuArray[(*len) - 1].name = (char*)malloc(sizeof(char));
    stuArray[(*len) - 1].dorm = (char*)malloc(sizeof(char));
    (*len) = (*len) - 1;
    printf("删除成功 ! \n");
    system("pause");
    return;
}
