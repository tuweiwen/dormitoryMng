#ifndef _STU_H_
#define _STU_H_
#include "stu.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// ���ֲ���ѧ����Ϣ(���������±꣬δ�ҵ��򷵻�-1)
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

// ��������
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

// ѡ������
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

// ѧ����Ϣ��������
void sortArray(stu* stuArray, int len) {
    time_t t;
    srand((unsigned) time(&t));
    // ʹ�������������������������ѡ��һ������ʽ
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

// ����ѧ����Ϣ
void create(stu* stuArray, int* len) {
    // �ж�ϵͳ�ڴ洢�����Ƿ�����
    if((*len) >= arrayMaxLen) {
        printf("ϵͳ��������ɾ������ѧ�����ݺ��ٽ�����Ӳ��� !\n");
        return;
    }

    int id;
    char name[40], dorm[10];
    printf("������ѧ�� : ");
    scanf("%d", &id);

    // �ж�ϵͳ���Ƿ��Ѿ�����
    if(binSearch(stuArray, 0, (*len) - 1, id) != -1) {
        printf("ϵͳ���Ѵ��ڸ�ѧ����Ϣ�������ظ���� ! \n");
        system("pause");
        return;
    }

    printf("���������� : ");
    scanf("%s", &name);
    printf("����������� : ");
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
    printf("��ӳɹ� ! \n");
    system("pause");
    return;
}

// ��ѯѧ����Ϣ
void retrieve(stu stuArray[], int len) {
    int id;
    printf("��������Ҫ���ҵ�ѧ�� : ");
    scanf("%d", &id);

    int i = binSearch(stuArray, 0, len - 1, id);
    if(i != -1) {
        printf("��ϵͳ�в�ѯ����ؽ�� : \n");
        printf("ѧ�� : %d\n", stuArray[i].id);
        printf("���� : %s\n", stuArray[i].name);
        printf("����� : %s\n", stuArray[i].dorm);
        system("pause");
        return;
    }

    // ��ѯʧ��
    printf("δ��ѯ����ؽ���������Ƿ�������ȷ !\n");

    system("pause");
    return;
}

// ����ѧ����Ϣ
void update(stu* stuArray, int len) {
    int id, index;
    printf("��������Ҫ������Ϣ��ѧ��ѧ�� : ");
    scanf("%d", &id);

    // �Ȳ�ѯ�ٸ���
    index = binSearch(stuArray, 0, len - 1, id);
    if(index == -1) {
        printf("δ��ѯ����ؽ��������޷����и��²�����\n�����Ƿ�������ȷ !\n\n");
        system("pause");
        
        return;
    }

    char buff[10];
    printf("������ѧ�� : %s\n", stuArray[index].name);
    printf("�������µ������ : ");
    scanf("%s", &buff);

    strcpy(stuArray[index].dorm, buff);
    printf("�޸ĳɹ�! \n");

    system("pause");
    return; 
}

// ɾ��ѧ����Ϣ
void deleteStu(stu* stuArray, int* len) {
    // �ж�ϵͳ�Ƿ�Ϊ��
    if((*len) <= 0) {
        printf("ϵͳ����Ϊ�գ�����ɾ������ ! \n");
        system("pause");
        return;
    }

    int id;
    printf("��������Ҫɾ����ѧ��ѧ�� : ");
    scanf("%d", &id);

    // ������Ϣ��ɾ��
    int index = binSearch(stuArray, 0, *len - 1, id);
    if(index == -1) {
        printf("δ��ѯ����ؽ��������޷�����ɾ��������\n�����Ƿ�������ȷ !\n");
        system("pause");
        
        return;
    }

    for(int i = index + 1; i < *len; i++)
        stuArray[i - 1] = stuArray[i];
    // ��ɾ����ѧ����Ϣ��գ��ص�ע��ָ�벿����Ҫ���¸�ֵ
    stuArray[(*len) - 1].name = (char*)malloc(sizeof(char));
    stuArray[(*len) - 1].dorm = (char*)malloc(sizeof(char));
    (*len) = (*len) - 1;
    printf("ɾ���ɹ� ! \n");
    system("pause");
    return;
}
