#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

const char DataFile[] = "BookDB.db";
int DefaultColor;
enum Color{
	Black = 0,
	Blue = 1,
	Green = 160,
	Red = 208,
	Yellow = 6,
	Grey =112,
	WhiteGrey = 112,
	White = 240,
	Aqua = 176
};
typedef struct bookdata{
	char Name[256]; //å �̸� 
	char Author[256]; //å ���� 
	char Company[256]; //���ǻ� 
	char Date[256]; //������ 
	int Price; //����
	int isOK; //���⿩��, 1 �̸� ���Ⱑ�� 0�̸� �Ұ��� 
	struct bookdata *Next; 
}BOOKDT;

void BookAdd(BOOKDT *HD);
void LinkAdd(BOOKDT *HD,BOOKDT *ND);
void LinkDelete(BOOKDT *HD,BOOKDT *SD);
void BookAllPrint(BOOKDT *HD);
void DataSave(BOOKDT *HD);
void DataLoad(BOOKDT *HD);
void BookSearch(BOOKDT *HD);
void BookDelete(BOOKDT *HD);
void BookBorrow(BOOKDT *HD);
void ChangeColor(int CL);
int GetColor();

int main(void){
	
	BOOKDT *head = (BOOKDT *)calloc(1,sizeof(struct bookdata)); //���Ḯ��Ʈ�� ���
	head->Price = -1;
	head->Next = NULL;
	DataLoad(head); //������ �ε� 
	DefaultColor = GetColor(); //�ܼ� �⺻ ���ڻ� ������ 
	//system("mode con:cols=120 lines=30"); //�ܼ�â ũ�� ���� _ ���� 
	SetConsoleTitle("�������� ������Ʈ");
	int menu=1;
	
	while(menu != 0){
		ChangeColor(WhiteGrey);
		printf("2017000000 ??? �⸻����  \n"); 
		printf("���������������\n");
		printf("   1. ����   ���           \n");
		printf("   2. ����   ����           \n"); 
		printf("   3. ����   �˻�           \n"); 
		printf("   4. ����   ����/�ݳ�      \n");
		printf("   5. ��ü   ���� ���      \n");
		printf("   6. ����� ���� ����      \n");
		printf("   0. ����                  \n");
		printf("���������������\n");
		ChangeColor(DefaultColor);
		printf("> ");
		fflush(stdin);
		scanf("%d",&menu);
		
		switch(menu){
			case 1:
				BookAdd(head);
				printf("> �߰� �Ǿ����ϴ�.\n\n\n");
				break;
			case 2:
				BookDelete(head);
				break;
			case 3:
				BookSearch(head);
				break;
			case 4:
				BookBorrow(head);
				break;
			case 5:
				BookAllPrint(head);
				break;
			case 6:
				DataSave(head);
				printf("> ���� �Ǿ����ϴ�.\n");
				break;
		}
	}	
	return 0;
}

void BookAdd(BOOKDT *HD){
	char Name[256]; //å �̸� 
	char Author[256]; //å ���� 
	char Company[256]; //���ǻ� 
	char Date[256]; //������ 
	int Price; //����
	BOOKDT *Node = (BOOKDT *)malloc(sizeof(BOOKDT));
	
	ChangeColor(Red);
	printf("\n[�ȳ�] $ , | ���ڴ� ����Ͻ� �� �����ϴ�.\n\n");
	ChangeColor(DefaultColor);
	
	printf("�� å �̸�   �Է� : ");
	fflush(stdin);
	gets(Name);
	printf("�� å ����   �Է� : ");
	fflush(stdin);
	gets(Author);
	printf("�� å ���ǻ� �Է� : ");
	fflush(stdin);
	gets(Company);
	printf("�� å ������ �Է� : ");
	fflush(stdin);
	gets(Date);
	printf("�� å ����   �Է� : ");
	fflush(stdin);
	scanf("%d",&Price);
	
	strcpy(Node->Name,Name);
	strcpy(Node->Author,Author);
	strcpy(Node->Company,Company);
	strcpy(Node->Date,Date);
	Node->Price = Price;
	Node->isOK = 1; 
	Node->Next = NULL;
	
	LinkAdd(HD,Node);
}

void LinkAdd(BOOKDT *HD,BOOKDT *ND){
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT)); //��ȯ��ũ
	FT->Next = HD;
	while(FT->Next != NULL){
		FT = FT->Next;
	}
	FT->Next = ND;
}
void LinkDelete(BOOKDT *HD,BOOKDT *SD){
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT)); //��ȯ��ũ
	BOOKDT *TMP = (BOOKDT *)malloc(sizeof(BOOKDT)); //��ȯ��ũ �ӽ����� 
	FT->Next = HD;
	while(FT->Next != NULL){
		TMP = FT;
		FT = FT->Next;
		if(SD == FT){
			TMP->Next = FT->Next;
			free(FT);
		}
	}
} 
void BookAllPrint(BOOKDT *HD){
	int cnt=0;
	system("CLS");
	printf("��������������������������������������������������������\n");
	ChangeColor(Aqua);
	printf("                                       ���� ���� ���                                                         \n");
	ChangeColor(DefaultColor);
	printf("��������������������������������������������������������\n");
	ChangeColor(White);
	printf("%-3s %-29s %-30s %-20s %-10s %-5s %-3s\n","��ȣ","�̸�","����","���ǻ�","������","����","����  "); 
	ChangeColor(DefaultColor);
	printf("��������������������������������������������������������\n");
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT));
	FT->Next=HD;
	
	while(FT->Next != NULL){
		FT = FT->Next;
		if(FT->Price >= 0)
		{
			printf("%-3d %-30s %-30s %-20s %-11s %-5d ",cnt++,FT->Name,FT->Author,FT->Company,FT->Date,FT->Price);
			if(FT->isOK == 1){
				ChangeColor(Green);
				printf("%-3s\n","����  ");
				ChangeColor(DefaultColor);
			}
			else{
				ChangeColor(Red);
				printf("%-3s\n","�Ұ���");	
				ChangeColor(DefaultColor);
			}
		}
	}
	printf("��������������������������������������������������������\n\n\n\n");
}
void BookSearch(BOOKDT *HD){
	
	char data[512];
	int cnt=0;
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT)); //��ȯ��ũ
	printf("�˻��� �ܾ �Է��ϼ��� > ");
	fflush(stdin);
	gets(data);
	
	//UI��� 
	system("CLS");
	printf("��������������������������������������������������������\n");
	ChangeColor(Aqua);
	printf("                                                ���� ���                                                     \n");
	ChangeColor(DefaultColor);
	printf("��������������������������������������������������������\n");
	ChangeColor(White);
	printf("%-3s %-29s %-30s %-20s %-10s %-5s %-3s\n","��ȣ","�̸�","����","���ǻ�","������","����","����  "); 
	ChangeColor(DefaultColor);
	printf("��������������������������������������������������������\n");
	//UI��� �Ϸ� 
	
	
	FT->Next = HD;
	while(FT->Next != NULL){
		FT = FT->Next;
		if(FT->Price >= 0)
		{
		if(strstr(FT->Name,data) != NULL || strstr(FT->Author,data) != NULL || strstr(FT->Company,data) != NULL || strstr(FT->Date,data) != NULL || strstr(FT->isOK?"����":"�Ұ���",data) != NULL){
			printf("%-3d %-30s %-30s %-20s %-11s %-5d ",cnt++,FT->Name,FT->Author,FT->Company,FT->Date,FT->Price);
			if(FT->isOK == 1){
				ChangeColor(Green);
				printf("%-3s\n","����  ");
				ChangeColor(DefaultColor);
			}
			else{
				ChangeColor(Red);
				printf("%-3s\n","�Ұ���");	
				ChangeColor(DefaultColor);
			}
		}
		}
	}
	if(cnt == 0)
	printf("              \n�˻��� �ڷᰡ �����ϴ�.\n");
	printf("��������������������������������������������������������\n\n\n\n");
	
}

void BookDelete(BOOKDT *HD){
	char data[512];
	int cnt=0;
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT)); //��ȯ��ũ
	printf("������ å ������ �Է��ϼ��� > ");
	fflush(stdin);
	gets(data);
	FT->Next = HD;
	while(FT->Next != NULL){
		FT = FT->Next;
		if(FT->Price >= 0){
			if(strcmp(FT->Name,data) == 0){
				LinkDelete(HD,FT);
				cnt++;
			} 
		}
	}
	if(cnt == 0){
		printf("������������������������\n");
		ChangeColor(Red);
		printf("              �˻��� �ڷᰡ �����ϴ�.         \n");
		ChangeColor(DefaultColor);
		printf("������������������������\n\n\n\n");
	}
	else{
		printf("������������������������\n");
		ChangeColor(Red);
		printf("              �ڷᰡ ���� �Ǿ����ϴ�.         \n");
		ChangeColor(DefaultColor);
		printf("������������������������\n\n\n\n");	
	}
}
void BookBorrow(BOOKDT *HD){
	char tmp[300];
	char Answer;
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT));
	FT->Next = HD;
	printf("�����ų� �ݳ� �� å�� �̸��� �Է��ϼ���> ");
	fflush(stdin);
	gets(tmp);
	while(FT->Next != NULL){
		FT = FT->Next;
		if(strcmp(FT->Name,tmp) == 0){
			if(FT->isOK == 1){
				printf("������������������������\n");
				ChangeColor(Green);
				printf("                �����Ͻðڽ��ϱ�? (Y/N)       \n");
				ChangeColor(DefaultColor);
				printf("������������������������\n");
				printf("> "); 
				Answer = getche();
				toupper(Answer);
				if(Answer == 'Y'){
					FT->isOK = 0;
					printf("                ���� ó�� �Ǿ����ϴ�.         \n");
					printf("������������������������\n");
				}
				else printf("\n");
				break;	
			}
			if(FT->isOK == 0){
				printf("������������������������\n");
				ChangeColor(Green);
				printf("                �ݳ��Ͻðڽ��ϱ�? (Y/N)       \n");
				ChangeColor(DefaultColor);
				printf("������������������������\n");
				printf("> "); 
				Answer = getche();
				toupper(Answer);
				if(Answer == 'Y'){
					FT->isOK = 1;
					printf("                �ݳ� ó�� �Ǿ����ϴ�.         \n");
					printf("������������������������\n");	
				}
				else printf("\n");
			}
		}
	}
	
} 
void DataSave(BOOKDT *HD){
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT)); //��ȯ��ũ
	FILE *fp = fopen(DataFile,"w+");
	FT->Next = HD;
	while(FT->Next != NULL){
		FT = FT->Next;
		if(FT->Price >= 0){
			fprintf(fp,"%s|%s|%s|%s|%d|%d$",FT->Name,FT->Author,FT->Company,FT->Date,FT->Price,FT->isOK);
			//$ �� ��带 �����ϴ� ���ڷ� ����� 
			//| �� ����� ��ü �׸��� �����ϴ� ���ڷ� ���� 
		}
	}
	fclose(fp);
}

void DataLoad(BOOKDT *HD){
	char ctmp[50000]={"0"};  //������ ��ü 
	char ctok[3000][512]; //�ټ���� �и��� ���ڿ� 
	char *cp= NULL;
	int cnt=0,x=0,y=0; 
	
	FILE *fp = fopen(DataFile,"r+");
	if(fp != NULL){
		
	fgets(ctmp,50000,fp); 
	fclose(fp);
	cp = strtok(ctmp,"$");
	while(cp != NULL){	
		strcpy(ctok[cnt],cp);
		cp = strtok(NULL,"$");
		cnt++;
	}
	}	
	ctok[cnt][0] = '\0'; //���� ���ڿ� ����
	
	cnt=0;
	while(ctok[cnt][0] != '\0'){
		y++;
		BOOKDT *tmp = (BOOKDT *)malloc(sizeof(BOOKDT));
		cp = strtok(ctok[cnt],"|");
		strcpy(tmp->Name,cp);
		
		cp = strtok(NULL,"|");
		strcpy(tmp->Author,cp);
		
		cp = strtok(NULL,"|");
		strcpy(tmp->Company,cp);
		
		cp = strtok(NULL,"|");
		strcpy(tmp->Date,cp);
		
		cp = strtok(NULL,"|");
		sscanf(cp,"%d",&x);
		tmp->Price=x;
		
		cp = strtok(NULL,"|");
		sscanf(cp,"%d",&x);
		tmp->isOK=x;
		
		tmp->Next=NULL;
		LinkAdd(HD,tmp);
		cnt++;
	}	
}
	

void ChangeColor(int CL){
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), CL);
}
int GetColor(){
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hC,&csbi);
	return csbi.wAttributes;
} 
