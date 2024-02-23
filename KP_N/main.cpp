#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <cctype>
#include <Windows.h>
#include <io.h>
#include <iomanip>

using namespace std;

// -- ���������

#define maxRecordsPerPage 15 /* ������������ ���������� ������� �� ����� �������� ��� ������ */
#define FILE_WAY "Employees"

// -- ��������� ����� --
struct employee
{
	char fio[21];/* ��� */
	int department;/* ��������� */
	int post;/* ��������� */
	int age;/* ������� */
	int exp;/* ���� ������ */
	int spendDays;/* ������������ ��� */
	double salary;/* �������� */
	bool recd;/* �������� */
};

// -- ��������������� ������� --
/* ����������� ������� �� ��������� ���������� */
void gotoxy(int x, int y)
{
COORD coord;
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* ��������� ������� ������� ������� */
COORD getxy()
{
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
	COORD ret;
	ret.X=bi.dwCursorPosition.X;
	ret.Y=bi.dwCursorPosition.Y;
	return ret;
}

/* �������� "�������" */
void hide_cur()
{
  HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);  
  CONSOLE_CURSOR_INFO cursor = {1, false}; 
  SetConsoleCursorInfo(hCons, &cursor);
}

/* �������� "�������" */
void show_cur()
{
  HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);  
  CONSOLE_CURSOR_INFO cursor = {20, true}; 
  SetConsoleCursorInfo(hCons, &cursor);
}

/* ��������� ������� ���� */
void windowSize(int width,int height)
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD crd = {width, height};
    SMALL_RECT src = {0, 0, crd.X-1, crd.Y-1};
    SetConsoleWindowInfo (out_handle, true, &src);
    SetConsoleScreenBufferSize (out_handle, crd);    
}

/* ��������� ����� ���������� ������ � ���� */
void SetColor(int text, int background)
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
/* ��������� ���������� � ���������� ���������� � ���������� ���������*/
int getAmPosts(int department)
{
	switch(department)
	{
	case 1:
		return 4;
	case 2:
		return 4;
	case 3:
		return 4;
	case 4:
		return 2;
	case 5:
		return 3;
	case 6:
		return 3;
	default:
		return 0;
	}
}

/* ����� �� ����� ���� ���������� ������� ��������� */
void prntPosts(int department)
{
	switch(department)
	{
	case 1:
		{
			std::cout<<"  �������;"<<endl;
			std::cout<<"  ������� ������;"<<endl;
			std::cout<<"  ������ ���;"<<endl;
			std::cout<<"  ������;"<<endl;
			break;
		}
	case 2:
		{
			std::cout<<"  ���������;"<<endl;
			std::cout<<"  ��������;"<<endl;
			std::cout<<"  ��������������;"<<endl;
			std::cout<<"  ���������;"<<endl;
			break;
		}
	case 3:
		{
			std::cout<<"  ������� ������;"<<endl;
			std::cout<<"  ������;"<<endl;
			std::cout<<"  �������;"<<endl;
			std::cout<<"  �������;"<<endl;
			break;
		}
	case 4:
		{
			std::cout<<"  ������� ���������;"<<endl;
			std::cout<<"  ���������;"<<endl;
			break;
		}
	case 5:
		{
			std::cout<<"  ��������� ���. ����;"<<endl;
			std::cout<<"  ������� ��������;"<<endl;
			std::cout<<"  ��������;"<<endl;
			break;
		}
	case 6:
		{
			std::cout<<"  �������;"<<endl;
			std::cout<<"  ����������;"<<endl;
			std::cout<<"  �������������;"<<endl;
			break;
		}
	}
}

/* ��������� ���������� � ��������, ������� �������� �������� ������ ��������� �� ������ ��������� */
double getSalary(int department,int post)
{
	switch(department)
	{
	case 1:
		switch(post)
		{
		case 1:return 100.;
		case 2:return 95.;
		case 3:return 92.;
		case 4:return 60.;
		default:return 0;
		}
	case 2:
		switch(post)
		{
		case 1:return 98.;
		case 2:return 90.;
		case 3:return 89.;
		case 4:return 80.;
		default:return 0;
		}
	case 3:
		switch(post)
		{
		case 1:return 88.;
		case 2:return 85.;
		case 3:return 25.;
		case 4:return 82.;
		default:return 0;
		}
	case 4:
		switch(post)
		{
		case 1:return 40.;
		case 2:return 30.;
		default:return 0;
		}
	case 5:
		switch(post)
		{
		case 1:return 110.;
		case 2:return 90.;
		case 3:return 86.;
		default:return 0;
		}
	case 6:
		switch(post)
		{
		case 1:return 70.;
		case 2:return 60.;
		case 3:return 50.;
		default:return 0;
		}
	default:
		return 0;
	}
}

/* ����� ��������� */
void prntDepartment(int department)
{
	switch(department)
	{
	case 1:std::cout<<" ������������������� ";break;
	case 2:std::cout<<"���������������������";break;
	case 3:std::cout<<"   �����. �������    ";break;
	case 4:std::cout<<"        �����        ";break;
	case 5:std::cout<<"��������� ���������� ";break;
	case 6:std::cout<<"      ��������       ";break;
	}
}

/* ����� ��������� */
void prntPost(int department,int post)
{
	switch(department)
	{
	case 1:
		{
			switch(post)
			{
			case 1: std::cout<<"      �������       ";break;
			case 2: std::cout<<"   ������� ������   ";break;
			case 3: std::cout<<"     ������ ���     ";break;
			case 4: std::cout<<"       ������       ";break;			
			}
			break;
		}
	case 2:
		{
			switch(post)
			{
			case 1: std::cout<<"     ���������      ";break;
			case 2: std::cout<<"      ��������      ";break;
			case 3: std::cout<<"   ��������������   ";break;
			case 4: std::cout<<"     ���������      ";break;
			}
			break;
		}
	case 3:
		{
			switch(post)
			{
			case 1: std::cout<<"   ������� ������   ";break;
			case 2: std::cout<<"       ������       ";break;
			case 3: std::cout<<"      �������       ";break;
			case 4: std::cout<<"      �������       ";break;
			}
			break;
		}
	case 4:
			switch(post)
			{
			case 1: std::cout<<"  ������� ��������� ";break;
			case 2: std::cout<<"     ���������      ";break;
			}
			break;
	case 5:
		{
			switch(post)
			{
			case 1: std::cout<<"��������� ���. ���� ";break;
			case 2: std::cout<<"  ������� ��������  ";break;
			case 3: std::cout<<"      ��������      ";break;
			}
			break;
		}
	case 6:
		{
			switch(post)
			{
			case 1: std::cout<<"      �������       ";break;
			case 2: std::cout<<"     ����������     ";break;
			case 3: std::cout<<"   �������������    ";break;
			}
			break;
		}
	}
}

/* ������� �������� ���� �������� �������� � ���������� ��������� */
char toNormalRus(char ichar)
{
	if((int(ichar)<=-97)&&((int(ichar)>=-128)))
		return int(ichar)+64;
	if((int(ichar)<=-17)&&((int(ichar)>=-32)))
		return int(ichar)+16;
	if((int(ichar)<=-81)&&((int(ichar)>=-96)))
		return int(ichar)+64;
	return ichar;
}

/* ������� ���� ������� �������� ���������� ������ � ���������� ��������� */
void makeNormal(char *st)
{
	int i=0;
	while(st[i]!='\0')
	{
		st[i]=toNormalRus(st[i]);
		i++;
	}
}

/* ������� �������� �� ����� � ���������� ������� �������� (������ �����������) */
bool isalpha(char s)
{
	if(((s>='a')&&(s<='z'))||((s>='A')&&(s<='Z'))||((s>=-32)&&(s<=-1))||((s>=-64)&&(s<=-33)))
	/* ���� ������ �������� ������ - ���������� true, ����� - false */
		return true;
	return false;
}

/* ������� ���� �������� � ������ ������� � ������ � ��������� ������ */
void lowerAll(char *input,char *output)
{
	int i=0;
	while(input[i]!='\0')
	{
		output[i]=tolower(input[i]);
		i++;
	}
	output[i]='\0';
}

/* �������� ���� (y - ������ ����, k - ���������� ������� ����) */
int menu(int y,int k)
{
	hide_cur();/* �������� "�������" */
	int pm=1;/* ���������� ��� �������� ���������� ������ ���� */
	gotoxy(1,y);/* ��������� � ������� ������� ������ */
	std::cout<<">";/* ������� ������ */
	char ch='\0';/* ���������� ��� �������� ������� ������� */
	while(ch!=13)/* ���� �� ����� Enter */
	{
		ch=_getch();/* ������� ������� ������� */
		gotoxy(1,y+pm-1);
		std::cout<<" ";/* ������� ������ */
		switch(ch)
		{
		case 'H':/* ���� ������ ������� ����� */
			{
				pm--;/* ��������� ����� ������ ���� */
				if(pm<1)/* ���� ���������� ����� ���� ������ ������� */
					pm=k;/* ������ ��������� ������� ��������� ����� */
				break;
			}
		case 'P':/* ���� ������ ������� ���� */
			{
				pm++;/* ����������� ����� ������ ���� */
				if(pm>k)/* ���� ���������� ����� ���� ������, ��� ���������� ������� � ���� */
					pm=1;/* �������� ������ ����� */
				break;
			}
		}
		gotoxy(1,y+pm-1);
		std::cout<<">";/* ������� ������ �� �������, ��������� � pm */
	}
	show_cur();/* ���������� "�������" */
	return pm;/* ���������� ��������� ����� ���� */
}

/* ������� ������ */
bool e_ansv(char mess[256])
{
	int y=getxy().Y;/* ��������� ������� ��������� "�������" �� ��� Y */
	gotoxy(0,y);/* ��������� � ������ ������� ������ */
	cout<<" "<<mess<<endl;/* ������� ���������� ��������� � �������� ������ */
	cout<<"  ��"<<endl;
	cout<<"  ���"<<endl;
	int pm=menu(y+1,2)-1;/* �������������� ����� ������ ���� ����� ����������� ������� */
	gotoxy(0,y+3);
	if(!pm)
		return true;
	return false;
}

/* �������� ���������� ������� � ����� */
int getFileSize(FILE *file)
{
	int i=0;/* ���������� ������� */
	employee a;/* ���������� ���� ��������� (��� ������ �� �����) */
	rewind(file);/* ��������� � ������ ����� */
	while(fread(&a,sizeof(employee),1,file))/* �� ��� ���, ���� ���������� ������ �� ����� */
		i++;/* ����������� ���������� ������� �� ������� */
	rewind(file);/* ��������� �� ������ ����� */
	return i;/* ���������� ���������� ������� */
}

/* ����� ����� ������� */
void prntHeader()
{
	/* ������ ������ */
	for(int i=0;i<119;i++)
		std::cout<<"_";
	std::cout<<endl;
	/* ������ ������ */
	std::cout<<"| � |        ���         |      ���������      |     ���������      | ������� | ���� | ���������� | �������� | ������ |"<<endl;
	/* ������ ������ */
	for(int i=0;i<119;i++)
		std::cout<<"_";
	std::cout<<endl;
}

/* ����� �� ����� ���������� ������ */
void prntRecord(int n,employee worker)
{
	if(n%2!=0)
		SetColor(0,7);
	printf("|%3i|%20s|",n,worker.fio);/* ������� ���������� ������ */
	prntDepartment(worker.department);
	std::cout<<"|";
	prntPost(worker.department,worker.post);
	printf("| %3i ��� |%2i ���| %5i ���� | %8.2f |",worker.age,worker.exp,worker.spendDays,worker.salary);
	if(worker.recd)
		std::cout<<"   ��   ";
	else
		std::cout<<"   ���  ";
	std::cout<<"|"<<endl;
	SetColor(0,15);
}

/* ����� ������� ���������� ���� employee */
void prntMas(employee *wMas,int kSearched)
{
	int pages=kSearched/(maxRecordsPerPage+1);/* ���������� ������� ������� (0 - ���� ��������) */
	if(pages)/* ���� ������� ������, ��� ���� */
	{
		char ch='\0';/* ������ ������� ������� */
		int cPage=0;/* ����� ������� �������� */
		while(ch!=13)
		{
			system("cls");
			prntHeader();/* ������� ����� ������� */
			int i=1;
			while(i<=maxRecordsPerPage)	/* ���� �� ����� �������� ����. ���������� ��� ����� �������� */
			{
				prntRecord(i+cPage*maxRecordsPerPage,wMas[i-1+cPage*maxRecordsPerPage]);
				i++;
			}
			for(int j=0;j<119;j++)/* ������������ ������� */
				std::cout<<"_";
			std::cout<<endl<<endl;
			std::cout<<" ��� ���������� ��������� ������� Enter; ��� ������������ �� ��������� ����������� ������� ����� ��� ����";
			bool f=false;/* ������� ��� ����������� ����� */
			do/* �������� ������� ����� �� ���������� ������ (��� ���������� �� ��������� ������) */
			{
				ch=_getch();/* �������� ������� ������� */
				switch(ch)
				{
				case 'H':/* ���� ������ ������� ����� */
					{
						if(cPage>0)/* ���� �� ��������� �� ��������, ����� ������� ������ ���� */
						{
							cPage--;/* ��������� ����� �������� */
							f=true;/* ������� �� ����� do...while */
						}
						break;
					}
				case 'P':/* ���� ������ ������� ������ */
					{
						if(cPage<pages)/* ���� �� ��������� �� ��������, ����� ������� ������, ��� ����� ���������� ������� */
						{
							cPage++;/* ����������� ����� �������� */
							f=true;/* ������� �� ����� do...while */
						}
						break;
					}
				case 13:
					{
						f=true;/* ������� �� ����� do...while */
						break;
					}
				}
			}while(!f);
		}
		return;
	}
	/* ���� �������� ����� ���� */
	system("cls");
	prntHeader();/* ������� ����� ������� */
	for(int i=0;i<kSearched;i++)/* ������� ��������� ������ */
		prntRecord(i+1,wMas[i]);
	for(int j=0;j<119;j++)/* ������������ ������� */
		std::cout<<"_";
	std::cout<<endl<<endl;
	system("pause");
}

/* �������� ������ �� ����� �� ������ (����� �������� ������� � �������!) */
void removeRecord(int n,FILE *fp)
{
	fseek(fp,sizeof(employee)*(n),SEEK_SET);/* ��������� � ������, ��������� ����� ��������� */
	employee wr;/* ���������� ��� �������� ������ */
	int i=0;/* ����� ������������ ������ */
	while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
	{
		fseek(fp,sizeof(employee)*(n+i-1),SEEK_SET);/* ��������� �� 1 ������ ����� */
		fwrite(&wr,sizeof(employee),1,fp);/* ������������ �� ����� ������� ������ ��������� */
		i++;/* ����������� ����� ������������ ������ */
		fseek(fp,sizeof(employee)*(n+i),SEEK_SET);/* ��������� � ��������� ������������ ������ */
	}
	_chsize(_fileno(fp), sizeof(employee)*(getFileSize(fp)-1));/* ��������� ��������� ������ (�.�. � ��� ��������� ������ ��������� �������������) */
	fseek(fp,sizeof(employee)*(n-1),SEEK_SET);
}

// -- ������� ����� ������ --

/* ������� ��� ����� ��� (str - ������������ ������) */
void enterFIO(char *str)
{
	bool f=true;/* ������ ��� ������ ����� */
	while(f)/* ���� ������ ������� � ���� ������ � ����� */
	{
		f=false;
		//std::cout<<" ������� ������� � �������� ��������� (���������):";
		char buff[80];
		cin.clear();/* ������� ������� (��� ���������� ������ gets_s()) */
		cin.sync();
		gets_s(buff,80);
		buff[79]='\0';/* ������ �� ��������� ������� ������ ������� ����� ������ */
		makeNormal(buff);
		int i(0),iS(0);/* ���������� ��� �������� �� ��������� ������ � ������������ ������ */
		
		/* ������� */
		while((!isalpha(buff[i]))&&(buff[i]!='\0'))/* ���������� ��� �������, �� ���������� ������� */
			i++;
		if(buff[i]=='\0')/* ���� ������ ����������� */
		{
			std::cout<<" - �� ������ �� �����! ��������� ����!"<<endl;
			f=true;
			continue;
		}
		str[iS]=toupper(buff[i]);/* ���� �� ���������, �� ��������� ������ ����� � ������� ������� � 
								    ������� ������ ������ � ������������ ������*/
		iS++; i++;
		while((isalpha(buff[i]))&&(iS<15))/* ���������� ��������� ����� ������� */
		{
			str[iS]=tolower(buff[i]);/* ��������� ������ � ������ ������� � ������� ��� � ������������ ������ */
			iS++; i++;
		}
		str[iS]=' ';/* ������ ������ ����� ������� */
		iS++;

		/* ������ ������� */

		while((!isalpha(buff[i]))&&(buff[i]!='\0'))/* ���������� ��� �������, �� ���������� ������� */
			i++;
		if(buff[i]=='\0')/* ���� ������ ����������� */
		{
			std::cout<<" - �� �� ����� ���������! ��������� ����!"<<endl;
			f=true;
			continue;
		}
		str[iS]=toupper(buff[i]);/* ���� �� ���������, �� ��������� ��������� ������� � ������� ������� � 
								    ������� ��� � ������������ ������*/
		iS++; i++;

		/* ������ ������� */

		str[iS]='.';/* ������ ����� ����� ������� �������� */
		iS++;
		while((!isalpha(buff[i]))&&(buff[i]!='\0'))/* ���������� ��� �������, �� ���������� ������� */
			i++;
		if(buff[i]=='\0')/* ���� ������ ����������� */
		{
			std::cout<<" - �� �� ����� ������ �������! ��������� ����!"<<endl;
			f=true;
			continue;
		}
		str[iS]=toupper(buff[i]);/* ���� �� ���������, �� ��������� ��������� ������� � ������� ������� � 
								    ������� ��� � ������������ ������*/
		iS++; i++;
		str[iS]='.';/* ������ ����� ����� ������� �������� */
		iS++;
		str[iS]='\0';/* ������ ����� ������ */
	}
}

/* ������� ����� ����� ����� (�� 0) */
int enterInt()
{
	bool f=true;/* ������ ��� ������ ����� */
	char buff[80];/* ������ ��� ����� */
	while(f)/* ���� ������ ������� � ���� ������ � ����� */
	{
		f=false;
		cin.clear();/* ������� ������� (��� ���������� ������ gets_s()) */
		cin.sync();
		gets_s(buff,80);
		buff[79]='\0';/* ������ �� ��������� ������� ������ ������� ����� ������ */
		makeNormal(buff);/* ��������� ������� ������� � ���������� ��� (��� ����� isdigit ����� �������� ��������� ������) */
		int i(0);/* ���������� ��� ������� �� ������ */
		while(buff[i]!='\0')/* ���� ������ �� ����������� */
		{
			if(((buff[i]>=-32)&&(buff[i]<=-1))||((buff[i]>=-64)&&(buff[i]<=-33))||(!isdigit(buff[i])))/* ���� ������ ������ - �� ����� */
			{
				f=true;
				break;
			}
			i++;
		}
		if(f)/* ���� �������� ������ ��� ����� */
		{
			std::cout<<" - ������� ������������ �����!"<<endl<<"   ��������� ����:";
			continue;
		}
	}
	return atoi(buff);/* ��������� ��������� ������ � ����� � ���������� */
}

/* ������� ��� ����� ��������� */
int enterOffice()
{
	int nY=getxy().Y,fl(1);/* ������������� ������ ������ � ������ ���������� ������ */
	gotoxy(0,nY);/* ��������� �� ������ ������, � ������� �� ��������� */
	std::cout<<" === �������� ��������� ==="<<endl;/* ������� ��������� ��� ���� */
	std::cout<<"  �������������������;"<<endl;
	std::cout<<"  ���������������������;"<<endl;
	std::cout<<"  ������������ �������;"<<endl;
	std::cout<<"  �����;"<<endl;
	std::cout<<"  ��������� ����������;"<<endl;
	std::cout<<"  ��������;"<<endl;
	fl=menu(nY+1,6);/* ����������� ���� � ������� ����������� ������� */
	gotoxy(0,nY+7);/* ��������� �� ����� ���� */
	return fl;
}

/* ������� ��� ����� ��������� */
int enterPost(int department)
{
	int nY=getxy().Y,fl(1);/* ������������� ������ ������ � ������ ���������� ������ */
	gotoxy(0,nY);/* ��������� �� ������ ������, � ������� �� ��������� */
	std::cout<<" === �������� ��������� ==="<<endl;/* ������� ��������� ��� ���� */
	prntPosts(department);/* ������� ��� ��������� ������� ��������� */
	fl=menu(nY+1,getAmPosts(department));/* ����������� ���� � ������� ����������� ������� */
	gotoxy(0,nY+getAmPosts(department)+1);/* ��������� �� ����� ���� */
	return fl;
}

/* ������� ��� ����� �������� */
int enterAge()
{
	int age(0);/* �������������� ���������� �������� */
	while((age<18)||(age>80))/* ���� ��������� ������� ������ 18 ��� ������ 80 */
	{
		age=enterInt();/* ������ ������� � ������� ����������� ������� */
		if((age<18)||(age>80))
			std::cout<<" - ������� ��������� ������ ���� �� 18 �� 80 ������������!"<<endl<<" ��������� ����:";
	}
	return age;
}

/* ������� ��� ����� ����� */
int enterExp(int age)
{
	int exp(age+18);/* �������������� ���������� ����� */
	while(exp>age-18)/* ���� ��������� ���� ������, ��� ����������� ��������� ���� ��� ����� �������� 
					    (��� �������, ��� ����������� ������� ��� ����� �� ������ - 18 ��� */
	{
		exp=enterInt();/* ������ ���� � ������� ����������� ������� */
		if(exp>age-18)
			std::cout<<" - ���� ������� ��������� �� ����� ���� ������ "<<age-18<<" ���!"<<endl<<" ��������� ����:";
	}
	return exp;
}

void countSalary(employee &worker)
{
	double slr=worker.spendDays*getSalary(worker.department,worker.post);/* ����������� �������� ��� �������� */
	double premium(0);/* �������������� ���������� �������� */
	if((worker.exp>=10)&&(worker.exp<=20))/* ���� ���� ��������� �� 10 �� 20 ��� */
		premium=slr/10;
	if((worker.exp>=20)&&(worker.exp<=30))/* ���� ���� ��������� �� 20 �� 30 ��� */
		premium=slr/4;
	if(worker.exp>30)/* ���� ���� ��������� ����� 30 ��� */
		premium=slr*4/10;
	worker.salary=slr+premium;/* ������� �������� � ������ */
}

/* ���� ������� ��� ������ (� ������� ����������) */
void enterFIOForSearch(char *st)
{
	int nY=getxy().Y,fl(1);/* ������������� ������ ������ � ������ ���������� ������ */
	gotoxy(0,nY);/* ��������� �� ������ ������, � ������� �� ��������� */
	std::cout<<" === �� ����� ����� ������� ��������� ����� ==="<<endl;/* ������� ��������� ��� ���� */
	std::cout<<"  �� ���� �������;"<<endl;
	std::cout<<"  �� ����� �������;"<<endl;
	std::cout<<"  �� ������ 3-� ������;"<<endl;
	fl=menu(nY+1,3);/* ����������� ���� � ������� ����������� ������� */
	gotoxy(0,nY+7);/* ��������� �� ����� ���� */
	system("cls");
	switch(fl)
	{
	case 1:
		{
			std::cout<<" === ������� ������� � �������� ��������� ==="<<endl;
			std::cout<<endl<<" >";
			enterFIO(st);
			break;
		}
	case 2:
		{
			std::cout<<" === ������� ����� ��� ��������� ==="<<endl<<" >";
			char FIO[21];
			gets_s(FIO);/* ������ ������� ��� */
			makeNormal(FIO);
			strcpy(st,FIO);
			break;
		}
	case 3:
		{
			std::cout<<" === ������� ������ 3 ����� ������� ��������� ==="<<endl<<" >";
			char FIO[21];
			do
			{
				gets_s(FIO);/* ������ ������� ��� */
				if(strlen(FIO)!=3)
					cout<<" - �� ������ ������ 3 �����!"<<endl<<" >";
			}while(strlen(FIO)!=3);
			FIO[3]='\0';/* ������� �� 3-� �������� */
			makeNormal(FIO);
			st[0]='3';/* ���������� � ������ ������������ ������ ������, ����� ��������� ����� ������ �� ���� ������ ������ */
			strcpy(st+1,FIO);
			break;
		}
	}
	return;
}

/* ��������� ������ ���� �������� */
bool checkFirstThreeLetters(char *st,char *st1)
{
	for(int i=0;i<3;i++)
		if(st[i]!=st1[i])/* ���� ������� ������������ */
			return false;
	return true;
}

// -- �������� ������� --

/* ����� ���� ������� �� ����� */
void showRecords()
{
	FILE *fp=fopen(FILE_WAY,"rb");
	if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
	{
		std::cout<<" !!! ���������� ������� ���� !!!"<<endl<<" �������� ���� �� ������. ������� ��� �����, ������� ������ � ����."<<endl;
		system("pause");
		return;
	}
	employee wr;/* ���������� ���� ��������� */
	int fSize=0;/* ���������� ������� � ����� */
	while(fread(&wr,sizeof(employee),1,fp))	/* ������� ���������� ������� � ����� */
		fSize++;
	rewind(fp);
	int pages=fSize/(maxRecordsPerPage+1);/* ���������� ������� ������� (0 - ���� ��������) */
	if(pages)/* ���� ������� ������, ��� ���� */
	{
		char ch='\0';/* ������ ������� ������� */
		int cPage=0;/* ����� ������� �������� */
		while(ch!=13)
		{
			system("cls");
			prntHeader();/* ������� ����� ������� */
			int i=1;
			fseek(fp,sizeof(employee)*cPage*maxRecordsPerPage,SEEK_SET);
			while((fread(&wr,sizeof(employee),1,fp))&&(i<=maxRecordsPerPage))	/* ����� �������, ���� ��� �� ���������� ��� 
																				   ���� �� ����� �������� ����. ���������� ��� ����� �������� */
			{
				prntRecord(i+cPage*maxRecordsPerPage,wr);
				i++;
			}
			for(int i=0;i<119;i++)/* ������������ ������� */
				std::cout<<"_";
			std::cout<<endl<<endl;
			std::cout<<" ��� ���������� ��������� ������� Enter; ��� ������������ �� ��������� ����������� ������� ����� ��� ����";
			bool f=false;/* ������� ��� ����������� ����� */
			do/* �������� ������� ����� �� ���������� ������ (��� ���������� �� ��������� ������) */
			{
				ch=_getch();/* �������� ������� ������� */
				switch(ch)
				{
				case 'H':/* ���� ������ ������� ����� */
					{
						if(cPage>0)/* ���� �� ��������� �� ��������, ����� ������� ������ ���� */
						{
							cPage--;/* ��������� ����� �������� */
							f=true;/* ������� �� ����� do...while */
						}
						break;
					}
				case 'P':/* ���� ������ ������� ������ */
					{
						if(cPage<pages)/* ���� �� ��������� �� ��������, ����� ������� ������, ��� ����� ���������� ������� */
						{
							cPage++;/* ����������� ����� �������� */
							f=true;/* ������� �� ����� do...while */
						}
						break;
					}
				case 13:
					{
						f=true;/* ������� �� ����� do...while */
						break;
					}
				}
			}while(!f);
		}
		fclose(fp);/* ��������� ���� */
		return;
	}
	/* ���� �������� ����� ���� */
	prntHeader();/* ������� ����� ������� */
	int i=1;
	while(fread(&wr,sizeof(employee),1,fp))	/* ����� �������, ���� ��� �� ����������  */
	{
		prntRecord(i,wr);
		i++;
	}
	for(int i=0;i<119;i++)/* ������������ ������� */
		std::cout<<"_";
	std::cout<<endl<<endl;
	system("pause");
	fclose(fp);/* ��������� ���� */
}

/* ���������� ������� � ���� */
void addRecords()
{
	FILE *fp=fopen(FILE_WAY,"a+b");
	if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
	{
		std::cout<<" !!! ���������� �������/������� ���� !!!"<<endl;
		system("pause");
		return;
	}
	employee aw;/* ���������� ���� ��������� */
	bool f(1);/* ���������� ��� ����� */
	while(f)
	{
		/* ��� */
		system("cls");
		std::cout<<" --- ������� ������� � �������� ��������� ---"<<endl;
		std::cout<<endl<<" >";
		enterFIO(aw.fio);
		/* ��������� */
		system("cls");
		aw.department=enterOffice();
		/* ��������� */
		system("cls");
		aw.post=enterPost(aw.department);
		/* ������� */
		system("cls");
		std::cout<<" --- ������� ������� ��������� ---"<<endl;
		std::cout<<endl<<" >";
		aw.age=enterAge();
		/* ���� */
		system("cls");
		std::cout<<" --- ������� ���� ��������� ---"<<endl;
		std::cout<<endl<<" >";
		aw.exp=enterExp(aw.age);
		/* ������������ ��� */
		system("cls");
		std::cout<<" --- ������� ���������� ������������ ���� ---"<<endl;
		do
		{
			std::cout<<endl<<" >";
			aw.spendDays=enterInt();
			if(aw.spendDays>31)
				std::cout<<" - ������ ����� ����� �� 0 �� 31! ��������� ����!";
		}while(aw.spendDays>31);
		/* �������� */
		countSalary(aw);
		/* ������ */
		system("cls");
		aw.recd=e_ansv(" --- ������ �� ��������? ---");
		/* ������������ */
		system("cls");
		prntHeader();
		printf("| 1 |%20s|",aw.fio);
		prntDepartment(aw.department);
		std::cout<<"|";
		prntPost(aw.department,aw.post);
		printf("|   %3i   |  %2i  |  %8i  | %8.2f |",aw.age,aw.exp,aw.spendDays,aw.salary);
		if(aw.recd)
			std::cout<<"   ��   ";
		else
			std::cout<<"   ���  ";
		std::cout<<"|"<<endl;
		for(int i=0;i<119;i++)
			std::cout<<"_";
		std::cout<<endl<<endl;
		bool ansv=e_ansv("�������� ��� ������? (� ���������� � ����� ����� ���������������)");
		if(ansv)
			fwrite(&aw,1,sizeof(aw),fp);
		std::cout<<endl<<endl;
		f=e_ansv("�������� ��� ���� ������?");
	}
	fclose(fp);/* ��������� ���� */
}

/* �������������� ������� */
void editRecords()
{
	int num=1;
	while(num!=0)
	{
		system("cls");
		showRecords();
		FILE *fp=fopen(FILE_WAY,"r+b");
		if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
		{
			std::cout<<" !!! ���������� ������� ���� !!!"<<endl;
			system("pause");
			return;
		}
		std::cout<<endl<<" === ������� ����� ������, ������� �� ������ ��������������� (��� ������� 0, ����� �����) ==="<<endl<<"  >";
		num=enterInt();/*  ���� ������ ������, ������� ����� ������������� (���� �� ����,����� �����) */
		if(num==0)/* ���� ������ ���� */
			break;
		if(num>getFileSize(fp))/* ���� ��������� ����� ������, ��� ���������� ������� � ����� */
		{
			cout<<" ��� ������ � ����� �������! ����������� ��������� �� ������ � ��������� ����!"<<endl;
			system("pause");
		}
		else/* ���� ������ �� ���� � �� �����, �������, ��� ���������� ������� � ����� */
		{
			fseek(fp,sizeof(employee)*(num-1),SEEK_SET);/* ��������� � ������ ��� ������ � ����� */
			employee wr;/* ���������� ���� ��������� ��� �������� ������������� ������ */
			fread(&wr,sizeof(employee),1,fp);/* ������ ������ ������ �� ����� � ���������� */
			int pm=1;/* ��������� ����� ���� */
			while(pm!=9)/* ���� �� ������ ����� ������ */
			{
				system("cls");/* ������� ����� */
				prntHeader();/* ������� ����� ������� */
				prntRecord(num,wr);/* ������� ������������� ������ */
				for(int i=0;i<119;i++)/* ������������� ������� */
					std::cout<<"_";
				std::cout<<endl<<endl;/* ��������� ���� ������ �� ������� � ������� ���� */
				std::cout<<" === ��� ����� ���������������? ==="<<endl;
				int mY=getxy().Y;/* ������ ���� */
				std::cout<<"  ��� ���������;"<<endl;/* 1 */
				std::cout<<"  ���������;"<<endl;/* 2 */
				std::cout<<"  ���������;"<<endl;/* 3 */
				std::cout<<"  �������;"<<endl;/* 4 */
				std::cout<<"  ����;"<<endl;/* 5 */
				std::cout<<"  ������������ ���;"<<endl;/* 6 */
				std::cout<<"  ������ ��������� ��������;"<<endl;/* 7 */
				std::cout<<"  ������ �������;"<<endl;/* 8 */
				std::cout<<"  ����� � ���������� ����."<<endl;/* 9 */
				pm=menu(mY,9);/* �������������� ���� */
				switch(pm)/* ��������� ��������� � ���� �������� */
				{
				case 1:
					{
						system("cls");
						std::cout<<" === ������� ������� � �������� ��������� (���������) ==="<<endl<<" >";
						enterFIO(wr.fio);
						break;
					}
				case 2:
					{
						system("cls");
						wr.department=enterOffice();
						/* break ���������� ��������, ����� ����� ����� ��������� ����� ��� ��������� ���� ��������� */
					}
				case 3:
					{
						system("cls");
						wr.post=enterPost(wr.department);
						countSalary(wr);
						break;
					}
				case 4:
					{
						system("cls");
						std::cout<<" --- ������� ������� ��������� ---"<<endl;
						std::cout<<endl<<" >";
						wr.age=enterAge();
						/* break ���������� ��������, ����� ����� ����� �������� ��� ��������� ���� ����� */
					}
				case 5:
					{
						system("cls");
						std::cout<<" --- ������� ���� ��������� ---"<<endl;
						std::cout<<endl<<" >";
						wr.exp=enterExp(wr.age);
						countSalary(wr);
						break;
					}
				case 6:
					{
						system("cls");
						std::cout<<" --- ������� ���������� ������������ ���� ---"<<endl;
						do
						{
							std::cout<<endl<<" >";
							wr.spendDays=enterInt();
							if(wr.spendDays>31)
								std::cout<<" - ������ ����� ����� �� 0 �� 31! ��������� ����!";
						}while(wr.spendDays>31);
						countSalary(wr);
						break;
					}
				case 7:
					{
						system("cls");
						wr.recd=e_ansv(" --- ������ �� ��������? ---");
						break;
					}
				case 8:
					{
						/* ��� */
						system("cls");
						std::cout<<" --- ������� ������� � �������� ��������� (���������) ---"<<endl;
						std::cout<<endl<<" >";
						enterFIO(wr.fio);
						/* ��������� */
						system("cls");
						wr.department=enterOffice();
						/* ��������� */
						system("cls");
						wr.post=enterPost(wr.department);
						/* ������� */
						system("cls");
						std::cout<<" --- ������� ������� ��������� ---"<<endl;
						std::cout<<endl<<" >";
						wr.age=enterAge();
						/* ���� */
						system("cls");
						std::cout<<" --- ������� ���� ��������� ---"<<endl;
						std::cout<<endl<<" >";
						wr.exp=enterExp(wr.age);
						/* ������������ ��� */
						system("cls");
						std::cout<<" --- ������� ���������� ������������ ���� ---"<<endl;
						do
						{
							std::cout<<endl<<" >";
							wr.spendDays=enterInt();
							if(wr.spendDays>31)
								std::cout<<" - ������ ����� ����� �� 0 �� 31! ��������� ����!";
						}while(wr.spendDays>31);
						/* �������� */
						countSalary(wr);
						/* ������ */
						system("cls");
						wr.recd=e_ansv(" --- ������ �� ��������? ---");
						break;
					}
				}
			}
			fseek(fp,sizeof(employee)*(num-1),SEEK_SET);/* ������� ����� � �����, ���� ������ ���� �������� ������ */
			fwrite(&wr,sizeof(employee),1,fp);/* ���������� ������ � ���� */
		}
		fclose(fp);/* ��������� ���� */
	}
}

/* �������� ������� */
void removeRecords()
{
	int pm=1;/* ��������� ����� ���� */
	while(pm!=3)/* ���� �� ������ ����� � ��. ���� */
	{
		system("cls");/* ������� ����� */
		showRecords();/* ������� ��� ������ */
		std::cout<<endl<<" === �������� �������, �� �������� ����� ����������� �������� ==="<<endl;/* ������� ���� */
		int mY=getxy().Y;/* ���������� ������� ��������� ������� �� ��� Y */
		std::cout<<"  �� ���;"<<endl;
		std::cout<<"  �� ��������;"<<endl;
		std::cout<<"  ����� � ������� ����."<<endl;
		pm=menu(mY,3);/* �������������� ���� */
		FILE *fp=fopen(FILE_WAY,"r+b");/* �������� ���� � ������ ����������� ������ */
		if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
		{
			std::cout<<" !!! ���������� ������� ���� !!!"<<endl;
			system("pause");
			return;
		}
		switch(pm)/* ��������� �������� �������� ���������� ������ ���� */
		{
		case 1:
			{
				system("cls");
				//std::cout<<" === ������� ����� ��� ���������, ������ � ������� �� ������� ������� ==="<<endl<<" >";
				char sFIO[2][21];/* ������� ��� */
				enterFIOForSearch(sFIO[0]);
				lowerAll(sFIO[0],sFIO[0]);/* ��������� ��� ������� ���������� ��� � ������ ������� */
				rewind(fp);/* ��������� � ������ ����� */
				employee wr;/* ���������� ��� �������� ������ */
				int i=1,kRemoved=0;/* ���������� ������ ������� ������ � �������� ���������� ��������� ������� */
				while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
				{
					lowerAll(wr.fio,sFIO[1]);
					if(
						((sFIO[0][0]=='3')&&(checkFirstThreeLetters(sFIO[1],&sFIO[0][1])))
						||
						((sFIO[0][0]!='3')&&(strstr(sFIO[1],sFIO[0])!=0))
						)/* ���� ������� ��� ��������� � ������ */
					{
						system("cls");/* ������� ����� */
						prntHeader();/* ������� ����� ������� */
						prntRecord(i,wr);/* ������� ������� ������ */
						for(int j=0;j<119;j++)/* ������������ ������� */
							std::cout<<"_";
						std::cout<<endl<<endl;/* ��������� ���� ������ �� ������� */
						bool fl=e_ansv("������� ��� ������?");/* ����������, ������� �� ��� ������ */
						if(fl)/* ���� fl=true */
						{
							removeRecord(i,fp);/* ������� ������� ������ */
							kRemoved++;/* ����������� ���������� ��������� ������� */
						}
					}
					i++;/* ����������� ����� ������� ������ */
				}
				system("cls");/* ������� ����� */
				if(!kRemoved)/* ���� �� �� ������� �� ����� ������ */
					std::cout<<" �� ������� �� ����� ������!"<<endl;
				else/* ����� */
					std::cout<<" ������� "<<kRemoved<<" �������!"<<endl;
				system("pause");
				break;
			}
		case 2:
			{
				system("cls");/* ������� ����� */
				std::cout<<" === ������� ������� �������� ���������, ������ � ������� �� ������� ������� ==="<<endl<<" ������ �������:";
				int sAge[2];/* ������� � ������ ������� �������� �������� */
				sAge[0]=enterInt();/* ������ ������ ������� */
				std::cout<<" ������� �������:";
				sAge[1]=enterInt();/* ������ ������� ������� */
				rewind(fp);/* ��������� � ������ ����� */
				employee wr;/* ���������� ��� �������� ������ */
				int i=1,kRemoved=0;/* ���������� ������ ������� ������ � �������� ���������� ��������� ������� */
				while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
				{
					if((wr.age>=sAge[0])&&(wr.age<=sAge[1]))/* ���� ������� � ������� ������ ������ � ������ ��� �������� */
					{
						system("cls");/* ������� ����� */
						prntHeader();/* ������� ����� ������� */
						prntRecord(i,wr);/* ������� ������� ������ */
						for(int j=0;j<119;j++)/* ������������ ������� */
							std::cout<<"_";
						std::cout<<endl<<endl;/* ��������� ���� ������ �� ������� */
						bool fl=e_ansv("������� ��� ������?");/* ����������, ������� �� ��� ������ */
						if(fl)/* ���� fl=true */
						{
							removeRecord(i,fp);/* ������� ������� ������ */
							kRemoved++;/* ����������� ���������� ��������� ������� */
						}
					}
					i++;/* ����������� ����� ������ */
				}
				system("cls");/* ������� ����� */
				if(!kRemoved)/* ���� �� �� ������� �� ����� ������ */
					std::cout<<" �� ������� �� ����� ������!"<<endl;
				else/* ����� */
					std::cout<<" ������� "<<kRemoved<<" �������!"<<endl;
				system("pause");
				break;
			}
		}
		fclose(fp);/* ��������� ���� */
	}
}

/* ���������� ������� */
void sortRecords()
{
	int pm=1;
	while(pm!=0)
	{
		system("cls");
		cout<<" === ��� ����������� ������? ==="<<endl;
		int mY=getxy().Y;
		cout<<"  �� ���;"<<endl;
		cout<<"  �� ���������;"<<endl;
		cout<<"  ����� � ������� ����."<<endl;
		pm=menu(mY,3);
		switch(pm)
		{
		case 1:
			{
				FILE *fp=fopen(FILE_WAY,"r+b");/* �������� ���� � ������ ����������� ������ */
				if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
				{
					std::cout<<" !!! ���������� ������� ���� !!!"<<endl;
					system("pause");
					return;
				}
				employee w1,w2;/* ���������� ��� �������� ������������ ������� */
				bool f=true;/* ������, ����������� �� �����������/���������� ����� ��������� ������� ������� */
				while(f)/* ���� ���� ������ ������� */
				{
					f=false;/* �� ���� ������ */
					rewind(fp);/* ��������� � ������ ����� */
					while(fread(&w1,sizeof(employee),1,fp)&&fread(&w2,sizeof(employee),1,fp))/* ��������� 2 ������ � ���������� �� */
					{
						if(strcmp(w1.fio,w2.fio)>0)/* ���� ������ ��� "������" ������� */
						{
							fseek(fp,-2*long(sizeof(employee)),SEEK_CUR);/* ��������� �� 2 ������� ����� */
							fwrite(&w2,sizeof(employee),1,fp);/* ���������� "�������" ��� */
							fwrite(&w1,sizeof(employee),1,fp);/* ���������� "�������" ��� */
							f=true;/* ��������� ������ */
							break;/* ������� �� ����� */
						}
						fseek(fp,-1*long(sizeof(employee)),SEEK_CUR);/* ��������� �� 1 ������� ����� */
					}
				}
				fclose(fp);/* ��������� ���� */
				showRecords();/* ������� ������ */
				break;
			}
		case 2:
			{
				FILE *fp=fopen(FILE_WAY,"r+b");/* �������� ���� � ������ ����������� ������ */
				if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
				{
					std::cout<<" !!! ���������� ������� ���� !!!"<<endl;
					system("pause");
					return;
				}
				employee w1,w2;/* ���������� ��� �������� ������������ ������� */
				bool f=true;/* ������, ����������� �� �����������/���������� ����� ��������� ������� ������� */
				while(f)/* ���� ���� ������ ������� */
				{
					f=false;/* �� ���� ������ */
					rewind(fp);/* ��������� � ������ ����� */
					while(fread(&w1,sizeof(employee),1,fp)&&fread(&w2,sizeof(employee),1,fp))/* ��������� 2 ������ � ���������� �� */
					{
						if(((w1.department*10)+w1.post)>((w2.department*10)+w2.post))/* ������ ���������� ������ ������ ��������� ����������� 
																					 ���������� ������ ��������� � ������ ���������, ����������� �� 10.
																					 ����� ������� ������� ����� ����� ��������� �� �����, � ������� - �� ���������.
																					 ��� ����� ������������ ������ 2 ������ ��������� � ����� ��� ���������� 
																					 ���������� �� ����� ����� ���������� �����, � ���������� 
																					 ���������� ��� �� ����������, ��� � �� ���������� */
						{
							fseek(fp,long(sizeof(employee))*(-2),SEEK_CUR);/* ��������� �� 2 ������� ����� */
							fwrite(&w2,sizeof(employee),1,fp);/* ���������� ������� ����� ��������� � ��������� */
							fwrite(&w1,sizeof(employee),1,fp);/* ���������� ������� ����� ��������� � ��������� */
							f=true;/* ��������� ������ */
							break;/* ������� �� ����� */
						}
						fseek(fp,-1*long(sizeof(employee)),SEEK_CUR);/* ��������� �� 1 ������� ����� */
					}
				}
				fclose(fp);/* ��������� ���� */
				showRecords();/* ������� ������ */
				break;
			}
		}
	}
}

/* ����� ������� */
void searchRecords()
{
	int pm=1;
	while(pm!=3)
	{
		system("cls");
		std::cout<<" === �� ������ �������� ���������� �����? ==="<<endl;
		std::cout<<"  �� ���;"<<endl;
		std::cout<<"  �� ���������;"<<endl;
		std::cout<<"  ����� � ������� ����."<<endl;
		pm=menu(1,3);
		switch(pm)
		{
		case 1:
			{
				FILE *fp=fopen(FILE_WAY,"rb");/* �������� ���� � ������ ������ */
				if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
				{
					std::cout<<" !!! ���������� ������� ���� !!!"<<endl;
					system("pause");
					return;
				}
				system("cls");
				//std::cout<<" === ������� ����� ��� ���������, ������ � ������� �� ������� ������� ==="<<endl<<" >";
				char sFIO[2][21];/* ������� ��� */
				enterFIOForSearch(sFIO[0]);
				lowerAll(sFIO[0],sFIO[0]);/* ��������� ��� ������� ���������� ��� � ������ ������� */
				system("cls");/* ������� ����� */
				rewind(fp);/* ��������� � ������ ����� */
				employee wr;/* ���������� ��� �������� ������ */
				employee *wMas=new employee[getFileSize(fp)];/* ������ ��� �������� ���������� ������� */
				int i=1,kSearched=0;/* ���������� ������ ������� ������ � �������� ���������� ��������� ������� */
				while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
				{
					lowerAll(wr.fio,sFIO[1]);/* ��������� ��� ������� ����������� ��� � ������ ������� � ������� � ������ sFIO[1] */
					if(
						((sFIO[0][0]=='3')&&(checkFirstThreeLetters(sFIO[1],&sFIO[0][1])))
						||
						((sFIO[0][0]!='3')&&(strstr(sFIO[1],sFIO[0])!=0))
						)/* ���� ������� ��� ��������� � ������ */
					{
						wMas[kSearched]=wr;
						kSearched++;/* ����������� ���������� ��������� ������� */
					}
					i++;/* ����������� ����� ������� ������ */
				}
				fclose(fp);/* ��������� ���� */
				if(!kSearched)/* ���� �� �� ����� �� ����� ������ */
				{
					std::cout<<" �� ������� �� ����� ������!"<<endl;
					system("pause");
					break;
				}
				prntMas(wMas,kSearched);/* ������� ��������� ������ �� ����� */	
				delete wMas;
				break;
			}
		case 2:
			{
				FILE *fp=fopen(FILE_WAY,"rb");/* �������� ���� � ������ ������ */
				if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
				{
					std::cout<<" !!! ���������� ������� ���� !!!"<<endl;
					system("pause");
					return;
				}
				system("cls");
				int sD=enterOffice();/* ������� ����� */
				int sP=enterPost(sD);/* ������� ��������� */
				system("cls");/* ������� ����� */
				rewind(fp);/* ��������� � ������ ����� */
				employee wr;/* ���������� ��� �������� ������ */
				employee *wMas=new employee[getFileSize(fp)];/* ������ ��� �������� ���������� ������� */
				int i=1,kSearched=0;/* ���������� ������ ������� ������ � �������� ���������� ��������� ������� */
				while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
				{
					if((wr.department==sD)&&(wr.post==sP))/* ���� ������� ����� � ��������� ��������� � ������� */
					{
						wMas[kSearched]=wr;
						kSearched++;/* ����������� ���������� ��������� ������� */
					}
					i++;/* ����������� ����� ������� ������ */
				}
				fclose(fp);/* ��������� ���� */
				if(!kSearched)/* ���� �� �� ����� �� ����� ������ */
				{
					std::cout<<" �� ������� �� ����� ������!"<<endl;
					system("pause");
					break;
				}
				prntMas(wMas,kSearched);/* ������� ��������� ������ �� ����� */
				delete wMas;
				break;
			}
		}
	}
}

/* ������� */

void request_1()
{
	FILE *fp=fopen(FILE_WAY,"rb");/* �������� ���� � ������ ������ */
	if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
	{
		std::cout<<" !!! ���������� ������� ���� !!!"<<endl;
		system("pause");
		return;
	}
	employee wr;/* ���������� ��� �������� ������ */
	fread(&wr,sizeof(employee),1,fp);/* ��������� �� ����� ������ ������ */
	double maxSalary=wr.salary;/* ������������ �������� */
	while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
		if(wr.salary>maxSalary)/* ���� �������� ������� ��������� ������ ������������ */
			maxSalary=wr.salary;/* ������ ������ �������� ������������ */
	rewind(fp);/* ��������� � ������ ����� */
	employee *mas=new employee[getFileSize(fp)];/* ������ ������� */
	int k=0;/* ���������� ������� � ������� */
	while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
		if(wr.salary==maxSalary)/* ���� �������� ������� ��������� ����� ������������ */
		{
			mas[k]=wr;/* ������� ������ � ������ */
			k++;
		}
	fclose(fp);/* ��������� ���� */
	prntMas(mas,k);/* ������� ������ */
	delete mas;
	showRecords();
}


void request_2()
{
	system("cls");
	int cDep=enterOffice();/* ������ ��������� */
	FILE *fp=fopen(FILE_WAY,"rb");/* �������� ���� � ������ ������ */
	if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
	{
		std::cout<<" !!! ���������� ������� ���� !!!"<<endl;
		system("pause");
		return;
	}
	employee wr;/* ���������� ��� �������� ������ */
	double debt=0;/* ���� */
	while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
		if((wr.department==cDep)&&(!wr.recd))/* ���� ��������� ��������� � ��������� � �������� �� �������� */
			debt+=wr.salary;/* ���������� ������ �������� � ����� ������ ��������� */
	system("cls");
	std::cout<<endl<<" ����� ����� ������ �� ���������� ��������� (";/* ������� ���� */
	prntDepartment(cDep);
	std::cout<<") ���������� "<<debt<<" ���."<<endl;
	system("pause");
	rewind(fp);
	employee *wMas=new employee[getFileSize(fp)];/* ������ ��� �������� ���������� ������� */
	int kSearched=0;/* ���������� ��� �������� ���������� ��������� ������� */
	while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
	{
		if(wr.department==cDep)/* ���� ������� ����� ��������� � ������ */
		{
			wMas[kSearched]=wr;
			kSearched++;/* ����������� ���������� ��������� ������� */
		}
	}
	fclose(fp);/* ��������� ���� */
	if(!kSearched)/* ���� �� �� ����� �� ����� ������ */
	{
		std::cout<<" �� ������� �� ����� ������!"<<endl;
		system("pause");
		return;
	}
	prntMas(wMas,kSearched);/* ������� ��������� ������ �� ����� */	
	delete wMas;
}

void request_3()
{
	FILE *fp=fopen(FILE_WAY,"rb");/* �������� ���� � ������ ������ */
	if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
	{
		std::cout<<" !!! ���������� ������� ���� !!!"<<endl;
		system("pause");
		return;
	}
	employee wr;
	int allWr=0;/* ����� ���������� ���������� */
	int wrPerDep[6]={0,0,0,0,0,0};/* ���������� ���������� �� ������ ��������� */
	while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
	{
		allWr++;/* ����������� ����� ���������� ���������� */
		wrPerDep[wr.department-1]++;/* ����������� ���������� ���������� ������� ��������� */
	}
	system("cls");
	std::cout<<" === ���������� ����������� ���������� �� ���������� ==="<<endl<<endl;
	for(int i=0;i<33;i++)/* ������� ������� ������� ������� */
		std::cout<<"_";
	std::cout<<endl;
	for(int i=0;i<6;i++)/* ������� ������� */
	{
		if(i%2!=0)
			SetColor(0,7);
		std::cout<<"|";
		prntDepartment(i+1);
		printf("| %6.2f",float(wrPerDep[i])*100/allWr);/* ������������ � ������� ���������� ���������� ������� ��������� � ��������� */
		std::cout<<"% |"<<endl;
		SetColor(0,15);
	}
	for(int i=0;i<33;i++)/* ������������ ������� */
		std::cout<<"_";
	std::cout<<endl<<endl;
	fclose(fp);/* ��������� ���� */
	system("pause");
}

void request_4()
{
	FILE *fp=fopen(FILE_WAY,"rb");/* �������� ���� � ������ ������ */
	if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
	{
		std::cout<<" !!! ���������� ������� ���� !!!"<<endl;
		system("pause");
		return;
	}
	employee wr;
	int allWr=0;/* ����� ���������� ���������� */
	int wrPerExp[4]={0,0,0,0};/* ���������� ���������� �� ������ ��������� */
	while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
	{
		allWr++;/* ����������� ����� ���������� ���������� */
		/* ����������� ���������� ���������� ���������� ��������� */
		if(wr.exp<10)
			wrPerExp[0]++;
		if((wr.exp>=10)&&(wr.exp<20))
			wrPerExp[1]++;
		if((wr.exp>=20)&&(wr.exp<30))
			wrPerExp[2]++;
		if(wr.exp>=30)
			wrPerExp[3]++;
	}
	system("cls");
	std::cout<<" === ���������� ����������� ���������� �� ���������� ����� ==="<<endl<<endl;
	for(int i=0;i<25;i++)/* ������� ������� ������� ������� */
		std::cout<<"_";
	std::cout<<endl;
	/* ������������ � ������� ���������� ���������� �� ������ ��������� � ��������� */
	printf("| �� 0 �� 10  | %6.2f%1c |\n",float(wrPerExp[0])*100/allWr,'%');
	SetColor(0,7);
	printf("| �� 10 �� 20 | %6.2f%1c |\n",float(wrPerExp[1])*100/allWr,'%');
	SetColor(0,15);
	printf("| �� 20 �� 30 | %6.2f%1c |\n",float(wrPerExp[2])*100/allWr,'%');
	SetColor(0,7);
	printf("| 30 � �����  | %6.2f%1c |\n",float(wrPerExp[3])*100/allWr,'%');
	SetColor(0,15);
	for(int i=0;i<25;i++)/* ������������ ������� */
		std::cout<<"_";
	std::cout<<endl<<endl;
	fclose(fp);/* ��������� ���� */
	system("pause");
}


void request_5()
{
	system("cls");
	int cDep=enterOffice();/* ������ ��������� */
	FILE *fp=fopen(FILE_WAY,"rb");/* �������� ���� � ������ ������ */
	if(fp==NULL)/* �������� ����� � ������������ �� ������������� ��� �������� */
	{
		std::cout<<" !!! ���������� ������� ���� !!!"<<endl;
		system("pause");
		return;
	}
	employee wr;/* ���������� ��� �������� ������ */
	double sum=0;/* ����� ����� ������� */
	int allWr=0;/* ���������� ���������� ������� ������ */
	while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
		if(wr.department==cDep)/* ���� ��������� ��������� � ��������� */
		{
			sum+=wr.salary;/* ���������� ������ �������� � ����� ������� ��������� */
			allWr++;/* ����������� ���������� ���������� ��������� */
		}
	system("cls");
	std::cout<<endl<<" ������� �������� �� ���������� ��������� (";/* ������� ������� �������� */
	prntDepartment(cDep);
	std::cout<<") ���������� "<<sum/allWr<<" ���."<<endl;
	system("pause");
	rewind(fp);
	employee *wMas=new employee[getFileSize(fp)];/* ������ ��� �������� ���������� ������� */
	int kSearched=0;/* ���������� ��� �������� ���������� ��������� ������� */
	while(fread(&wr,sizeof(employee),1,fp))/* ���� ���������� ������ �� ����� */
	{
		if(wr.department==cDep)/* ���� ������� ����� ��������� � ������ */
		{
			wMas[kSearched]=wr;
			kSearched++;/* ����������� ���������� ��������� ������� */
		}
	}
	fclose(fp);/* ��������� ���� */
	if(!kSearched)/* ���� �� �� ����� �� ����� ������ */
	{
		std::cout<<" �� ������� �� ����� ������!"<<endl;
		system("pause");
		return;
	}
	prntMas(wMas,kSearched);/* ������� ��������� ������ �� ����� */	
	delete wMas;
}
void main()
{
	windowSize(120,30);
	setlocale(LC_ALL,"Russian");
	system("color f0");
	int pm=1;
	while(pm!=8)
	{
		system("cls");
		std::cout<<" ===== ������� ���� ====="<<endl<<endl;
		std::cout<<"  �������� �����;"<<endl;/* 1 */
		std::cout<<"  ���������� ������� � ����;"<<endl;/* 2 */
		std::cout<<"  �������������� �������;"<<endl;/* 3 */
		std::cout<<"  �������� �������;"<<endl;/* 4 */
		std::cout<<"  ���������� �������;"<<endl;/* 5 */
		std::cout<<"  ����� �� �������;"<<endl;/* 6 */
		std::cout<<"  �������;"<<endl;/* 7 */
		std::cout<<"  ����� �� ���������;"<<endl;/* 8 */
		pm=menu(2,8);
		switch(pm)
		{
		case 1:
			{
				system("cls");
				showRecords();
				break;
			}
		case 2:
			{
				system("cls");
				addRecords();
				break;
			}
		case 3:
			{
				system("cls");
				editRecords();
				break;
			}
		case 4:
			{
				system("cls");
				removeRecords();
				break;
			}
		case 5:
			{
				system("cls");
				sortRecords();
				break;
			}
		case 6:
			{
				system("cls");
				searchRecords();
				break;
			}
		case 7:
			{
				int rn=1;
				while(rn!=6)
				{
					system("cls");
					std::cout<<" === �������� ������ ==="<<endl;
					std::cout<<"  1. ����� ����������� � ������������ ���������;"<<endl;
					std::cout<<"  2. ������ ����� ����� ������ �� ���������� ���������;"<<endl;
					std::cout<<"  3. ����� ����������� ����������� ���������� �� ����������;"<<endl;
					std::cout<<"  4. ����� ����������� ����������� ���������� �� �����;"<<endl;
					std::cout<<"  5. ����� ������� �������� ���������� ���������� ���������;"<<endl;
					std::cout<<"  ����� � ������� ����."<<endl;
					rn=menu(1,6);
					switch(rn)
					{
					case 1:system("cls");request_1();break;
					case 2:system("cls");request_2();break;
					case 3:system("cls");request_3();break;
					case 4:system("cls");request_4();break;
					case 5:system("cls");request_5();break;
					}
				}
				break;
			}
		}
	}
}