#include "crud.h"
#include "fileIO.h"

int mainMenu(void);

int main(void) {

    //�����ʼ�� ��ȡ�ļ� / ��������
    FILE* source = NULL;
    stu stuArray[arrayMaxLen];  // ϵͳ���洢500������
    int arrLen = loadFile(source, stuArray);

    //���˵� ѡ����
    while(1) {
        system("cls");
        switch (mainMenu()) {
            // ��
            case 1:
                system("cls");
                create(stuArray, &arrLen);
                break;
            // ɾ
            case 2:
                system("cls");
                deleteStu(stuArray, &arrLen);
                break;
            // ��
            case 3:
                system("cls");
                update(stuArray, arrLen);
                break;
            // ��
            case 4:
                system("cls");
                retrieve(stuArray,arrLen);
                break;
            // �˳�
            case 5:
                system("cls");
                printf("��лʹ��! ϵͳ�����ر�\n");
                system("pause");
                
                //����ر�ǰ ������������� & ���´洢�ļ�
                saveFile(source, stuArray, arrLen);
                exit(0);
                break;
            // ��������
            default:
                printf("�Ƿ����룬������! \n");
                system("pause");
                system("cls");
                break;
        }
    }
    
    return 0;
}

int mainMenu(void) {
    int choose;

    printf("--------ѧ���������ϵͳ--------\n");
    printf("|---- �����빦����Ų��س� ----|\n");
    printf("|--------- 1 ����ѧ�� ---------|\n");
    printf("|--------- 2 ɾ��ѧ�� ---------|\n");
    printf("|--------- 3 �޸���Ϣ ---------|\n");
    printf("|--------- 4 ����ѧ�� ---------|\n");
    printf("|--------- 5 �˳�ϵͳ ---------|\n");
    printf("--------------------------------\n");

    printf("�������: ");
    scanf("%d", &choose);

    return choose;
}
