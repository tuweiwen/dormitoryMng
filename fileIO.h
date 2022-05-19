#ifndef _STU_H_
#define _STU_H_
#include "stu.h"
#endif

#include <stdio.h>
#include <windows.h>

// ��ȡ�ļ�������Ϣ�����ض�ȡ��Ϣ����(int)
int loadFile(FILE* source, stu* stuArray) {
    // ���ļ�
    source = fopen("source.csv", "r");
    // �޷���ʱ�������ļ�
    if(source == NULL) {
        printf("�޷����ļ����Ѵ������ļ� ! \n");
        source = fopen("source.csv", "w+");
    }
    
    char buff[40];
    char separator[2] = ",";
    int count = 0;
    // ��ȡ��ֹͣ����ΪEOF����Ϣ��������arrayMaxLen��
    while(fgets(buff, 60, source) != NULL && count <= arrayMaxLen) {
        // �Զ��Ž��зָ�
        char* temp = strtok(buff, separator);
        char* l = malloc(strlen(temp) * sizeof(char));  // ���·���ָ��ռ䱣�汻�ָ���ַ�
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
            stuArray[count].dorm[len - 1] = '\0';   // ȥ����������ĩβ��"\n"(���з�)
        }

        count++;
    }

    return count;
}

// ����������Ϣ���ļ�
void saveFile(FILE* source, stu stuArray[], int len) {
    // �ر�ԭ�ĵ�
    fclose(source);
    // remove("source.csv");
    // system("del source.csv");
    source = fopen("source.csv", "w+"); // ֱ�Ӹ�дԭ�ļ�
    for(int i = 0; i < len - 1; i++) {
        fprintf(source, "%d,%s,%s\n", stuArray[i].id, stuArray[i].name, stuArray[i].dorm);
    }
    // ���һ�в�д�뻻�з�������ϵͳ��ȡ����ʱ��������
    fprintf(source, "%d,%s,%s", stuArray[len - 1].id, stuArray[len - 1].name, stuArray[len - 1].dorm);
    fclose(source); // �ر����ĵ�
    return;
}
