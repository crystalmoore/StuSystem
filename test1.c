#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ѧ����Ϣ�ṹ��
typedef struct _STU
{
	char arrStuNum[10];
	char arrStuName[10];
	int iStuScore;
    struct _STU* pNext;
}STUNODE;
//����ͷ��㣬β�ڵ�
STUNODE* g_pHead = NULL;
STUNODE* g_pEnd = NULL;
//��ʾѧ������ϵͳ����
void showOrder();

//���һ��ѧ����Ϣ
void AddStuMSG(char *arrStuNum,char *arrStuName,int iStuScore);
//��ʾѧ����Ϣ
void ShowStuMSG();
//����ָ��ѧ������Ϣ
STUNODE* FindStuNum(char* arrStuNum);
//ɾ��ָ��ѧ����Ϣ
void DeleteStuMSG(STUNODE* pTemp);
//��ѧ����Ϣ���浽�ļ�
void SaveStuTOFile();
//���ļ���ȡѧ����Ϣ
void ReadStuFROMFile();
//�ͷ��������������
void ReleaseNode();
//��ѧ������
void SortStuNum();
int main()
{
	char arrStuNum[10]={'\0'};
	char arrStuName[10]={'\0'};
	int iStuScore= -1;
	int order = -1;
	int flag = 1;
	STUNODE* pTemp=NULL;
	printf("ѧ������ϵͳ:\n");
	showOrder();
	ReadStuFROMFile();
	while(flag)
	{
		printf("��ѡ����:");
		scanf("%d",&order);
		switch(order)
		{
			case 1:
				printf("1.���һ��ѧ����Ϣ\n");
				printf("����ѧ��ѧ��:\n");
				scanf("%s",arrStuNum);
				//printf("%s\n",arrStuNum);
				printf("����ѧ������:\n");
				scanf("%s",arrStuName);
				//printf("%s\n",arrStuName);
				printf("����ѧ���ɼ�:\n");
				scanf("%d",&iStuScore);
				AddStuMSG(arrStuNum,arrStuName,iStuScore);
				break;
			case 2:
				printf("2.��ʾѧ����Ϣ\n");
				ShowStuMSG();
				break;
			case 3:
				printf("3.����ָ��ѧ����Ϣ\n");
				printf("������Ҫ���ҵ�ѧ����ѧ��:\n");
				scanf("%s",arrStuNum);
				pTemp=FindStuNum(arrStuNum);
				if(NULL !=pTemp)
				{
					printf("ѧ��:%s,����%s,�ɼ�%d\n",pTemp->arrStuNum,pTemp->arrStuName,pTemp->iStuScore);
				}
				break;
			case 4:
				printf("4.�޸�ָ��ѧ����Ϣ\n");
				printf("������Ҫ�޸ĵ�ѧ����ѧ��:\n");
				scanf("%s",arrStuNum);
				pTemp=FindStuNum(arrStuNum);
				if(NULL !=pTemp)
				{
					printf("����ѧ��ѧ��:\n");
					scanf("%s",arrStuNum);
					strcpy(pTemp->arrStuNum,arrStuNum);
					printf("����ѧ������:\n");
					scanf("%s",arrStuName);
					strcpy(pTemp->arrStuName,arrStuName);
					printf("����ѧ���ɼ�:\n");
					scanf("%d",&iStuScore);
					pTemp->iStuScore=iStuScore;
				}
				break;
			case 5:
				printf("5.ɾ��ָ��ѧ����Ϣ\n");
				printf("������Ҫɾ����ѧ����ѧ��:\n");
				scanf("%s",arrStuNum);
				pTemp=FindStuNum(arrStuNum);
				if(NULL !=pTemp)
				{
					DeleteStuMSG(pTemp);
				}
				break;
			case 6:
				printf("6.��ѧ����Ϣ���浽�ļ�\n");
				SaveStuTOFile();
				break;
			case 7:
				printf("7.���ļ���ȡѧ����Ϣ\n");
				ReadStuFROMFile();
				break;
			case 8:
				showOrder();
				break;
			case 9:
				printf("��ѧ����Ϣ���򣨰�ѧ������");
				SortStuNum();
				break;
			case 0:
				flag = 0;
				printf("�˳�ϵͳ\n");
				break;
			default:
				break;
		}
	}
	SaveStuTOFile();
	//�ͷ�����
	ReleaseNode();
	system("pause");
	return 0;
}

//��ʾѧ������ϵͳ����
void showOrder()
{
	printf("1.���һ��ѧ����Ϣ\n");//��
    printf("2.��ʾѧ����Ϣ\n");
	printf("3.����ָ��ѧ����Ϣ\n");//��
	printf("4.�޸�ָ��ѧ����Ϣ\n");//��
	printf("5.ɾ��ָ��ѧ����Ϣ\n");//ɾ
	printf("6.��ѧ����Ϣ���浽�ļ�\n");//д�ļ�
	printf("7.���ļ���ȡѧ����Ϣ\n");//���ļ�
	printf("8.��ʾѧ������ϵͳ����\n");
	printf("9.��ѧ����Ϣ���򣨰�ѧ������");
	printf("0.�˳�ϵͳ\n");
}
//���һ��ѧ����Ϣ
void AddStuMSG(char *arrStuNum,char *arrStuName,int iStuScore)
{
	//����һ���ڵ�
	STUNODE* pTemp = (STUNODE*)malloc(sizeof(STUNODE));
	//���ڵ���Ϣ
	if(NULL == arrStuNum || NULL == arrStuName || iStuScore <0)
	{
		printf("ѧ����Ϣ�������\n");
		return;
	}
	//�ڵ��Ա��ֵ
	strcpy(pTemp->arrStuNum,arrStuNum);
	strcpy(pTemp->arrStuName,arrStuName);
	pTemp->iStuScore=iStuScore;
	pTemp->pNext=NULL;
	//����������
	if(NULL == g_pHead || NULL == g_pEnd)//����Ϊ��
	{
		g_pHead=pTemp;
	}
	else
	{
		g_pEnd->pNext=pTemp;//����
	}
	g_pEnd = pTemp;
}

//��ʾѧ����Ϣ
void ShowStuMSG()
{
	STUNODE* pTemp=g_pHead;
	while(pTemp !=NULL)
	{
		printf("ѧ��:%s,����%s,�ɼ�%d\n",pTemp->arrStuNum,pTemp->arrStuName,pTemp->iStuScore);
		pTemp=pTemp->pNext;
	}
}
//����ָ��ѧ������Ϣ
STUNODE* FindStuNum(char* arrStuNum)
{
	STUNODE* pTemp = g_pHead;
	//�������ĺϷ���
	if(NULL==arrStuNum)
	{
		printf("ѧ���������\n");
		return NULL;
	}
	//�ж������Ƿ�Ϊ��
	if(NULL== g_pHead || NULL==g_pEnd)
	{
		printf("����Ϊ��\n");
		return NULL;
	}
	//��������
	while(pTemp)
	{
		if(0 ==strcmp(pTemp->arrStuNum,arrStuNum))
		{
			return pTemp;
		}
		pTemp=pTemp->pNext;
	}
	printf("û�и�ѧ������Ϣ\n");
	return NULL;
}

//ɾ��ָ��ѧ����Ϣ
void DeleteStuMSG(STUNODE* pNode)
{
	//�������һ���ڵ�
	if(g_pHead == g_pEnd)
	{
		free(g_pHead);
		g_pHead=NULL;
		g_pEnd=NULL;
	}
	//�����������ڵ㣬Ҫɾ���Ľڵ���ͷ������β�ڵ�
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
			//һ��Ҫ��g_pHead->pNext=NULL;�����Ұָ�����
			g_pHead->pNext=NULL;
		}
	}
	

	//�����������ڵ�����ϵ����
	else
	{
		STUNODE* pTemp =g_pHead;
		//�ж�ͷ
		if(g_pHead == pNode)
		{
			//��סͷ
			pTemp=g_pHead;
			g_pHead=g_pHead->pNext;
			free(pTemp);
			pTemp=NULL;//һ��Ҫ��pTemp=NULL;�����Ұָ�����
			return;//����
		}
		//��������,��ͷ��㿪ʼ������Ҫɾ����ǡ����ͷ��㣬���ϣ�
		while(pTemp)
		{
			if(pTemp->pNext == pNode)
			{
				//���������
				//��һ��Ҫɾ�����Ǹ���β�ڵ�
				if(pNode == g_pEnd)
				{
					free(pNode);
					pNode=NULL;
					//β��ǰ�ƶ�һ��
					g_pEnd=pTemp;
					//��g_pEnd->pNext=NULL�ÿգ�����Ұָ�����
					g_pEnd->pNext=NULL;
					return;
				}

				//�ڶ���Ҫɾ�����Ǹ�����ͨ�ڵ�
				else
				{
					//��סҪɾ���Ľڵ�
					STUNODE* p =pTemp->pNext;
					//����
					pTemp->pNext=pTemp->pNext->pNext;
					//�ͷŽڵ�
					free(p);
					p=NULL;//�ÿ�
					return;
				}

			}
			pTemp=pTemp->pNext;
		}
	}
}

//��ѧ����Ϣ���浽�ļ�
void SaveStuTOFile()
{
	FILE* pFile= NULL;
	//���ļ�֮ǰ���ж������Ƿ�Ϊ�գ����Ϊ�գ�ֱ��return
	STUNODE* pTemp=g_pHead;
	char strBuf[30]={'\0'};//�������ַ���
	char strScore[10]={'\0'};//������������ת��Ϊ�ַ����ĳɼ�
	if(NULL== g_pHead)
	{
		printf("û��ѧ��\n");
		return;
	}
	//���ļ�
	
	pFile=fopen("test.txt","wb+");
	if(NULL == pFile)
	{
		printf("���ļ�ʧ��\n");
		return;
	}

	//��ѧ����Ϣд��
	while(pTemp)
	{
		//ѧ��
		strcpy(strBuf,pTemp->arrStuNum);
		strcat(strBuf,"#");
		//����
		strcat(strBuf,pTemp->arrStuName);
		strcat(strBuf,"#");
		//�ɼ�
		itoa(pTemp->iStuScore,strScore,10);//������ת��Ϊ�ַ�����
		strcat(strBuf,strScore);
		//
		fwrite(strBuf,1,strlen(strBuf),pFile);
		fwrite("\r\n",1,strlen("\r\n"),pFile);//����
		pTemp=pTemp->pNext;
	}
	//�ر��ļ�
	fclose(pFile);
}

//���ļ���ȡѧ����Ϣ
void ReadStuFROMFile()
{
	//���ļ�
	FILE* pFile=fopen("test.txt","rb+");
	//�����ļ��ж�ȡ���Ķ����Ž�������
	char strBuf[30]={0};
	char strStuNum[10]={0};
	char strStuName[10]={0};
	char strStuScore[10]={0};
	int nCount=0;
	int j=0;
	int k=0;
	if(NULL==pFile)
	{
		printf("�ļ���ʧ��\n");
		return;
	}
	//�����ļ�����ȡ
	while(NULL !=fgets(strBuf,30,pFile))
	{//���зǿ�ʱ��
		int i=0;
		nCount=0;
		j=0;//�ֱ���j��k��Ϊ�˿���ֱ��
		k=0;
		for(i=0;strBuf[i]!='\r';i++)//һ��һ�еĶ�
		{
			//ÿ�е�Ԫ����#������nCount=0,1,2
			if(0==nCount){//���ѧ��
				strStuNum[i]=strBuf[i];
				if('#'==strBuf[i])
				{
					strStuNum[i]='\0';
					nCount++;
				}
			}
			else if(1==nCount)
			{//�������
				strStuName[j]=strBuf[i];
				if('#'==strBuf[i])
				{
					strStuName[j]='\0';
					nCount++;
				}
				j++;

			}
			else
			{//��ųɼ�
				strStuScore[k]=strBuf[i];

				k++;
			}
		}
		//���в�������
		AddStuMSG(strStuNum,strStuName,atoi(strStuScore));

	}

	//�ر��ļ�
	fclose(pFile);
}
//�ͷ��������������
void ReleaseNode()
{
	STUNODE* pTemp=g_pHead;
	while(NULL != g_pHead)
	{
		//��ͷ��ʼɾ��
		//��ס�ڵ�
		pTemp=g_pHead;
		//ͷ�����������һλ
		g_pHead=g_pHead->pNext;
		//free
		free(pTemp);
	}
}

//��ѧ������
void SortStuNum(){
	;
}