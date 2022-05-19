#ifndef _STU_H_
#define _STU_H_
#include "stu.h"
#endif

#include <stdio.h>
#include <windows.h>

// 读取文件数据信息，返回读取信息条数(int)
int loadFile(FILE* source, stu* stuArray) {
    // 打开文件
    source = fopen("source.csv", "r");
    // 无法打开时创建新文件
    if(source == NULL) {
        printf("无法打开文件，已创建新文件 ! \n");
        source = fopen("source.csv", "w+");
    }
    
    char buff[40];
    char separator[2] = ",";
    int count = 0;
    // 读取，停止条件为EOF或信息条数大于arrayMaxLen条
    while(fgets(buff, 60, source) != NULL && count <= arrayMaxLen) {
        // 以逗号进行分割
        char* temp = strtok(buff, separator);
        char* l = malloc(strlen(temp) * sizeof(char));  // 重新分配指针空间保存被分割的字符
        strcpy(l, temp);
        stuArray[count].id = atoi(l);

        temp = strtok(NULL, separator);
        l = malloc(strlen(temp) * sizeof(char));
        strcpy(l, temp);
        stuArray[count].name = l;

        temp = strtok(NULL, separator);
        l = malloc(strlen(temp) * sizeof(char));
        strcpy(l, temp);
        stuArray[count].dorm = l;
        
        int len = strlen(stuArray[count].dorm);
        if(stuArray[count].dorm[len - 1] == '\n') {
            stuArray[count].dorm[len - 1] = '\0';   // 去除宿舍数据末尾的"\n"(换行符)
        }

        count++;
    }

    return count;
}

// 保存数据信息至文件
void saveFile(FILE* source, stu stuArray[], int len) {
    // 关闭原文档
    fclose(source);
    // remove("source.csv");
    // system("del source.csv");
    source = fopen("source.csv", "w+"); // 直接复写原文件
    for(int i = 0; i < len - 1; i++) {
        fprintf(source, "%d,%s,%s\n", stuArray[i].id, stuArray[i].name, stuArray[i].dorm);
    }
    // 最后一行不写入换行符，避免系统读取数据时发生错误
    fprintf(source, "%d,%s,%s", stuArray[len - 1].id, stuArray[len - 1].name, stuArray[len - 1].dorm);
    fclose(source); // 关闭新文档
    return;
}
