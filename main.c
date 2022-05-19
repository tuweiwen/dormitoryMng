#include "crud.h"
#include "fileIO.h"

int mainMenu(void);

int main(void) {

    //软件初始化 读取文件 / 加载数据
    FILE* source = NULL;
    stu stuArray[arrayMaxLen];  // 系统最大存储500条数据
    int arrLen = loadFile(source, stuArray);

    //主菜单 选择功能
    while(1) {
        system("cls");
        switch (mainMenu()) {
            // 增
            case 1:
                system("cls");
                create(stuArray, &arrLen);
                break;
            // 删
            case 2:
                system("cls");
                deleteStu(stuArray, &arrLen);
                break;
            // 改
            case 3:
                system("cls");
                update(stuArray, arrLen);
                break;
            // 查
            case 4:
                system("cls");
                retrieve(stuArray,arrLen);
                break;
            // 退出
            case 5:
                system("cls");
                printf("感谢使用! 系统即将关闭\n");
                system("pause");
                
                //软件关闭前 对数组进行排序 & 重新存储文件
                saveFile(source, stuArray, arrLen);
                exit(0);
                break;
            // 错误输入
            default:
                printf("非法输入，请重试! \n");
                system("pause");
                system("cls");
                break;
        }
    }
    
    return 0;
}

int mainMenu(void) {
    int choose;

    printf("--------学生宿舍管理系统--------\n");
    printf("|---- 请输入功能序号并回车 ----|\n");
    printf("|--------- 1 增加学生 ---------|\n");
    printf("|--------- 2 删除学生 ---------|\n");
    printf("|--------- 3 修改信息 ---------|\n");
    printf("|--------- 4 查找学生 ---------|\n");
    printf("|--------- 5 退出系统 ---------|\n");
    printf("--------------------------------\n");

    printf("功能序号: ");
    scanf("%d", &choose);

    return choose;
}
