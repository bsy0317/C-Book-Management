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
	char Name[256]; //책 이름 
	char Author[256]; //책 저자 
	char Company[256]; //출판사 
	char Date[256]; //출판일 
	int Price; //가격
	int isOK; //대출여부, 1 이면 대출가능 0이면 불가능 
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
	
	BOOKDT *head = (BOOKDT *)calloc(1,sizeof(struct bookdata)); //연결리스트의 헤더
	head->Price = -1;
	head->Next = NULL;
	DataLoad(head); //데이터 로드 
	DefaultColor = GetColor(); //콘솔 기본 글자색 가져옴 
	//system("mode con:cols=120 lines=30"); //콘솔창 크기 설정 _ 오류 
	SetConsoleTitle("도서관리 프로젝트");
	int menu=1;
	
	while(menu != 0){
		ChangeColor(WhiteGrey);
		printf("2017000000 ??? 기말과제  \n"); 
		printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
		printf("   1. 도서   등록           \n");
		printf("   2. 도서   삭제           \n"); 
		printf("   3. 도서   검색           \n"); 
		printf("   4. 도서   대출/반납      \n");
		printf("   5. 전체   도서 출력      \n");
		printf("   6. 변경된 사항 저장      \n");
		printf("   0. 종료                  \n");
		printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
		ChangeColor(DefaultColor);
		printf("> ");
		fflush(stdin);
		scanf("%d",&menu);
		
		switch(menu){
			case 1:
				BookAdd(head);
				printf("> 추가 되었습니다.\n\n\n");
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
				printf("> 저장 되었습니다.\n");
				break;
		}
	}	
	return 0;
}

void BookAdd(BOOKDT *HD){
	char Name[256]; //책 이름 
	char Author[256]; //책 저자 
	char Company[256]; //출판사 
	char Date[256]; //출판일 
	int Price; //가격
	BOOKDT *Node = (BOOKDT *)malloc(sizeof(BOOKDT));
	
	ChangeColor(Red);
	printf("\n[안내] $ , | 문자는 사용하실 수 없습니다.\n\n");
	ChangeColor(DefaultColor);
	
	printf("▶ 책 이름   입력 : ");
	fflush(stdin);
	gets(Name);
	printf("▶ 책 저자   입력 : ");
	fflush(stdin);
	gets(Author);
	printf("▶ 책 출판사 입력 : ");
	fflush(stdin);
	gets(Company);
	printf("▶ 책 출판일 입력 : ");
	fflush(stdin);
	gets(Date);
	printf("▶ 책 가격   입력 : ");
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
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT)); //순환링크
	FT->Next = HD;
	while(FT->Next != NULL){
		FT = FT->Next;
	}
	FT->Next = ND;
}
void LinkDelete(BOOKDT *HD,BOOKDT *SD){
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT)); //순환링크
	BOOKDT *TMP = (BOOKDT *)malloc(sizeof(BOOKDT)); //순환링크 임시저장 
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
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	ChangeColor(Aqua);
	printf("                                       보유 도서 목록                                                         \n");
	ChangeColor(DefaultColor);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	ChangeColor(White);
	printf("%-3s %-29s %-30s %-20s %-10s %-5s %-3s\n","번호","이름","저자","출판사","출판일","가격","대출  "); 
	ChangeColor(DefaultColor);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT));
	FT->Next=HD;
	
	while(FT->Next != NULL){
		FT = FT->Next;
		if(FT->Price >= 0)
		{
			printf("%-3d %-30s %-30s %-20s %-11s %-5d ",cnt++,FT->Name,FT->Author,FT->Company,FT->Date,FT->Price);
			if(FT->isOK == 1){
				ChangeColor(Green);
				printf("%-3s\n","가능  ");
				ChangeColor(DefaultColor);
			}
			else{
				ChangeColor(Red);
				printf("%-3s\n","불가능");	
				ChangeColor(DefaultColor);
			}
		}
	}
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n\n\n");
}
void BookSearch(BOOKDT *HD){
	
	char data[512];
	int cnt=0;
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT)); //순환링크
	printf("검색할 단어를 입력하세요 > ");
	fflush(stdin);
	gets(data);
	
	//UI출력 
	system("CLS");
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	ChangeColor(Aqua);
	printf("                                                도서 목록                                                     \n");
	ChangeColor(DefaultColor);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	ChangeColor(White);
	printf("%-3s %-29s %-30s %-20s %-10s %-5s %-3s\n","번호","이름","저자","출판사","출판일","가격","대출  "); 
	ChangeColor(DefaultColor);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	//UI출력 완료 
	
	
	FT->Next = HD;
	while(FT->Next != NULL){
		FT = FT->Next;
		if(FT->Price >= 0)
		{
		if(strstr(FT->Name,data) != NULL || strstr(FT->Author,data) != NULL || strstr(FT->Company,data) != NULL || strstr(FT->Date,data) != NULL || strstr(FT->isOK?"가능":"불가능",data) != NULL){
			printf("%-3d %-30s %-30s %-20s %-11s %-5d ",cnt++,FT->Name,FT->Author,FT->Company,FT->Date,FT->Price);
			if(FT->isOK == 1){
				ChangeColor(Green);
				printf("%-3s\n","가능  ");
				ChangeColor(DefaultColor);
			}
			else{
				ChangeColor(Red);
				printf("%-3s\n","불가능");	
				ChangeColor(DefaultColor);
			}
		}
		}
	}
	if(cnt == 0)
	printf("              \n검색된 자료가 없습니다.\n");
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n\n\n");
	
}

void BookDelete(BOOKDT *HD){
	char data[512];
	int cnt=0;
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT)); //순환링크
	printf("삭제할 책 제목을 입력하세요 > ");
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
		printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
		ChangeColor(Red);
		printf("              검색된 자료가 없습니다.         \n");
		ChangeColor(DefaultColor);
		printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n\n\n");
	}
	else{
		printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
		ChangeColor(Red);
		printf("              자료가 삭제 되었습니다.         \n");
		ChangeColor(DefaultColor);
		printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n\n\n");	
	}
}
void BookBorrow(BOOKDT *HD){
	char tmp[300];
	char Answer;
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT));
	FT->Next = HD;
	printf("빌리거나 반납 할 책의 이름을 입력하세요> ");
	fflush(stdin);
	gets(tmp);
	while(FT->Next != NULL){
		FT = FT->Next;
		if(strcmp(FT->Name,tmp) == 0){
			if(FT->isOK == 1){
				printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
				ChangeColor(Green);
				printf("                대출하시겠습니까? (Y/N)       \n");
				ChangeColor(DefaultColor);
				printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
				printf("> "); 
				Answer = getche();
				toupper(Answer);
				if(Answer == 'Y'){
					FT->isOK = 0;
					printf("                대출 처리 되었습니다.         \n");
					printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
				}
				else printf("\n");
				break;	
			}
			if(FT->isOK == 0){
				printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
				ChangeColor(Green);
				printf("                반납하시겠습니까? (Y/N)       \n");
				ChangeColor(DefaultColor);
				printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
				printf("> "); 
				Answer = getche();
				toupper(Answer);
				if(Answer == 'Y'){
					FT->isOK = 1;
					printf("                반납 처리 되었습니다.         \n");
					printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");	
				}
				else printf("\n");
			}
		}
	}
	
} 
void DataSave(BOOKDT *HD){
	BOOKDT *FT = (BOOKDT *)malloc(sizeof(BOOKDT)); //순환링크
	FILE *fp = fopen(DataFile,"w+");
	FT->Next = HD;
	while(FT->Next != NULL){
		FT = FT->Next;
		if(FT->Price >= 0){
			fprintf(fp,"%s|%s|%s|%s|%d|%d$",FT->Name,FT->Author,FT->Company,FT->Date,FT->Price,FT->isOK);
			//$ 는 노드를 구분하는 문자로 사용함 
			//| 은 노드의 객체 항목을 구분하는 문자로 사용됨 
		}
	}
	fclose(fp);
}

void DataLoad(BOOKDT *HD){
	char ctmp[50000]={"0"};  //데이터 전체 
	char ctok[3000][512]; //줄수대로 분리된 문자열 
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
	ctok[cnt][0] = '\0'; //종료 문자열 넣음
	
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
