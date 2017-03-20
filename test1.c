#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//学生信息结构体
typedef struct _STU
{
	char arrStuNum[10];
	char arrStuName[10];
	int iStuScore;
    struct _STU* pNext;
}STUNODE;
//链表头结点，尾节点
STUNODE* g_pHead = NULL;
STUNODE* g_pEnd = NULL;
//显示学生管理系统功能
void showOrder();

//添加一个学生信息
void AddStuMSG(char *arrStuNum,char *arrStuName,int iStuScore);
//显示学生信息
void ShowStuMSG();
//查找指定学生的信息
STUNODE* FindStuNum(char* arrStuNum);
//删除指定学生信息
void DeleteStuMSG(STUNODE* pTemp);
//将学生信息保存到文件
void SaveStuTOFile();
//从文件读取学生信息
void ReadStuFROMFile();
//释放链表，即清空链表
void ReleaseNode();
//按学号排序
void SortStuNum();
int main()
{
	char arrStuNum[10]={'\0'};
	char arrStuName[10]={'\0'};
	int iStuScore= -1;
	int order = -1;
	int flag = 1;
	STUNODE* pTemp=NULL;
	printf("学生管理系统:\n");
	showOrder();
	ReadStuFROMFile();
	while(flag)
	{
		printf("请选择功能:");
		scanf("%d",&order);
		switch(order)
		{
			case 1:
				printf("1.添加一个学生信息\n");
				printf("输入学生学号:\n");
				scanf("%s",arrStuNum);
				//printf("%s\n",arrStuNum);
				printf("输入学生姓名:\n");
				scanf("%s",arrStuName);
				//printf("%s\n",arrStuName);
				printf("输入学生成绩:\n");
				scanf("%d",&iStuScore);
				AddStuMSG(arrStuNum,arrStuName,iStuScore);
				break;
			case 2:
				printf("2.显示学生信息\n");
				ShowStuMSG();
				break;
			case 3:
				printf("3.查找指定学生信息\n");
				printf("请输入要查找的学生的学号:\n");
				scanf("%s",arrStuNum);
				pTemp=FindStuNum(arrStuNum);
				if(NULL !=pTemp)
				{
					printf("学号:%s,姓名%s,成绩%d\n",pTemp->arrStuNum,pTemp->arrStuName,pTemp->iStuScore);
				}
				break;
			case 4:
				printf("4.修改指定学生信息\n");
				printf("请输入要修改的学生的学号:\n");
				scanf("%s",arrStuNum);
				pTemp=FindStuNum(arrStuNum);
				if(NULL !=pTemp)
				{
					printf("输入学生学号:\n");
					scanf("%s",arrStuNum);
					strcpy(pTemp->arrStuNum,arrStuNum);
					printf("输入学生姓名:\n");
					scanf("%s",arrStuName);
					strcpy(pTemp->arrStuName,arrStuName);
					printf("输入学生成绩:\n");
					scanf("%d",&iStuScore);
					pTemp->iStuScore=iStuScore;
				}
				break;
			case 5:
				printf("5.删除指定学生信息\n");
				printf("请输入要删除的学生的学号:\n");
				scanf("%s",arrStuNum);
				pTemp=FindStuNum(arrStuNum);
				if(NULL !=pTemp)
				{
					DeleteStuMSG(pTemp);
				}
				break;
			case 6:
				printf("6.将学生信息保存到文件\n");
				SaveStuTOFile();
				break;
			case 7:
				printf("7.从文件读取学生信息\n");
				ReadStuFROMFile();
				break;
			case 8:
				showOrder();
				break;
			case 9:
				printf("将学生信息排序（按学号升序）");
				SortStuNum();
				break;
			case 0:
				flag = 0;
				printf("退出系统\n");
				break;
			default:
				break;
		}
	}
	SaveStuTOFile();
	//释放链表
	ReleaseNode();
	system("pause");
	return 0;
}

//显示学生管理系统功能
void showOrder()
{
	printf("1.添加一个学生信息\n");//增
    printf("2.显示学生信息\n");
	printf("3.查找指定学生信息\n");//查
	printf("4.修改指定学生信息\n");//改
	printf("5.删除指定学生信息\n");//删
	printf("6.将学生信息保存到文件\n");//写文件
	printf("7.从文件读取学生信息\n");//读文件
	printf("8.显示学生管理系统功能\n");
	printf("9.将学生信息排序（按学号升序）");
	printf("0.退出系统\n");
}
//添加一个学生信息
void AddStuMSG(char *arrStuNum,char *arrStuName,int iStuScore)
{
	//创建一个节点
	STUNODE* pTemp = (STUNODE*)malloc(sizeof(STUNODE));
	//检查节点信息
	if(NULL == arrStuNum || NULL == arrStuName || iStuScore <0)
	{
		printf("学生信息输入出错\n");
		return;
	}
	//节点成员赋值
	strcpy(pTemp->arrStuNum,arrStuNum);
	strcpy(pTemp->arrStuName,arrStuName);
	pTemp->iStuScore=iStuScore;
	pTemp->pNext=NULL;
	//接在链表上
	if(NULL == g_pHead || NULL == g_pEnd)//链表为空
	{
		g_pHead=pTemp;
	}
	else
	{
		g_pEnd->pNext=pTemp;//连接
	}
	g_pEnd = pTemp;
}

//显示学生信息
void ShowStuMSG()
{
	STUNODE* pTemp=g_pHead;
	while(pTemp !=NULL)
	{
		printf("学号:%s,姓名%s,成绩%d\n",pTemp->arrStuNum,pTemp->arrStuName,pTemp->iStuScore);
		pTemp=pTemp->pNext;
	}
}
//查找指定学生的信息
STUNODE* FindStuNum(char* arrStuNum)
{
	STUNODE* pTemp = g_pHead;
	//检测参数的合法性
	if(NULL==arrStuNum)
	{
		printf("学号输入错误\n");
		return NULL;
	}
	//判断链表是否为空
	if(NULL== g_pHead || NULL==g_pEnd)
	{
		printf("链表为空\n");
		return NULL;
	}
	//遍历链表
	while(pTemp)
	{
		if(0 ==strcmp(pTemp->arrStuNum,arrStuNum))
		{
			return pTemp;
		}
		pTemp=pTemp->pNext;
	}
	printf("没有该学生的信息\n");
	return NULL;
}

//删除指定学生信息
void DeleteStuMSG(STUNODE* pNode)
{
	//链表仅有一个节点
	if(g_pHead == g_pEnd)
	{
		free(g_pHead);
		g_pHead=NULL;
		g_pEnd=NULL;
	}
	//链表有两个节点，要删除的节点是头结点或者尾节点
	else if(g_pHead->pNext == g_pEnd)
	{
		if(g_pHead == pNode)
		{
			free(g_pHead);
			g_pHead=g_pEnd;
		}
		else
		{
			free(g_pEnd);
			g_pEnd=g_pHead;
			//一定要把g_pHead->pNext=NULL;否则会野指针错误
			g_pHead->pNext=NULL;
		}
	}
	

	//链表有三个节点或以上的情况
	else
	{
		STUNODE* pTemp =g_pHead;
		//判断头
		if(g_pHead == pNode)
		{
			//记住头
			pTemp=g_pHead;
			g_pHead=g_pHead->pNext;
			free(pTemp);
			pTemp=NULL;//一定要把pTemp=NULL;否则会野指针错误
			return;//结束
		}
		//遍历链表,从头结点开始遍历：要删除的恰好是头结点，以上；
		while(pTemp)
		{
			if(pTemp->pNext == pNode)
			{
				//分两种情况
				//第一，要删除的那个是尾节点
				if(pNode == g_pEnd)
				{
					free(pNode);
					pNode=NULL;
					//尾向前移动一个
					g_pEnd=pTemp;
					//将g_pEnd->pNext=NULL置空；否则野指针错误
					g_pEnd->pNext=NULL;
					return;
				}

				//第二，要删除的那个是普通节点
				else
				{
					//记住要删除的节点
					STUNODE* p =pTemp->pNext;
					//链接
					pTemp->pNext=pTemp->pNext->pNext;
					//释放节点
					free(p);
					p=NULL;//置空
					return;
				}

			}
			pTemp=pTemp->pNext;
		}
	}
}

//将学生信息保存到文件
void SaveStuTOFile()
{
	FILE* pFile= NULL;
	//打开文件之前先判断链表是否为空，如果为空，直接return
	STUNODE* pTemp=g_pHead;
	char strBuf[30]={'\0'};//用来放字符串
	char strScore[10]={'\0'};//用来放由整形转换为字符串的成绩
	if(NULL== g_pHead)
	{
		printf("没有学生\n");
		return;
	}
	//打开文件
	
	pFile=fopen("test.txt","wb+");
	if(NULL == pFile)
	{
		printf("打开文件失败\n");
		return;
	}

	//将学生信息写入
	while(pTemp)
	{
		//学号
		strcpy(strBuf,pTemp->arrStuNum);
		strcat(strBuf,"#");
		//姓名
		strcat(strBuf,pTemp->arrStuName);
		strcat(strBuf,"#");
		//成绩
		itoa(pTemp->iStuScore,strScore,10);//将整形转换为字符串，
		strcat(strBuf,strScore);
		//
		fwrite(strBuf,1,strlen(strBuf),pFile);
		fwrite("\r\n",1,strlen("\r\n"),pFile);//分行
		pTemp=pTemp->pNext;
	}
	//关闭文件
	fclose(pFile);
}

//从文件读取学生信息
void ReadStuFROMFile()
{
	//打开文件
	FILE* pFile=fopen("test.txt","rb+");
	//将在文件中读取到的东西放进数组里
	char strBuf[30]={0};
	char strStuNum[10]={0};
	char strStuName[10]={0};
	char strStuScore[10]={0};
	int nCount=0;
	int j=0;
	int k=0;
	if(NULL==pFile)
	{
		printf("文件打开失败\n");
		return;
	}
	//操作文件，读取
	while(NULL !=fgets(strBuf,30,pFile))
	{//当行非空时候
		int i=0;
		nCount=0;
		j=0;//分别用j和k是为了看着直观
		k=0;
		for(i=0;strBuf[i]!='\r';i++)//一行一行的读
		{
			//每行的元素由#隔开，nCount=0,1,2
			if(0==nCount){//存放学号
				strStuNum[i]=strBuf[i];
				if('#'==strBuf[i])
				{
					strStuNum[i]='\0';
					nCount++;
				}
			}
			else if(1==nCount)
			{//存放姓名
				strStuName[j]=strBuf[i];
				if('#'==strBuf[i])
				{
					strStuName[j]='\0';
					nCount++;
				}
				j++;

			}
			else
			{//存放成绩
				strStuScore[k]=strBuf[i];

				k++;
			}
		}
		//逐行插入链表
		AddStuMSG(strStuNum,strStuName,atoi(strStuScore));

	}

	//关闭文件
	fclose(pFile);
}
//释放链表，即清空链表
void ReleaseNode()
{
	STUNODE* pTemp=g_pHead;
	while(NULL != g_pHead)
	{
		//从头开始删除
		//记住节点
		pTemp=g_pHead;
		//头结点往后移了一位
		g_pHead=g_pHead->pNext;
		//free
		free(pTemp);
	}
}

//按学号排序
void SortStuNum(){
	;
}