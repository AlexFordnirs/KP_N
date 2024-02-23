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

// -- КОНСТАНТЫ

#define maxRecordsPerPage 15 /* Максимальное количество записей на одной странице при выводе */
#define FILE_WAY "Employees"

// -- СТРУКТУРА ФАЙЛА --
struct employee
{
	char fio[21];/* ФИО */
	int department;/* Отделение */
	int post;/* Должность */
	int age;/* Возраст */
	int exp;/* Стаж работы */
	int spendDays;/* Отработанные дни */
	double salary;/* Зарплата */
	bool recd;/* Оплачено */
};

// -- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ --
/* Перемещение курсора на указанные координаты */
void gotoxy(int x, int y)
{
COORD coord;
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* Получение текущей позиции курсора */
COORD getxy()
{
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
	COORD ret;
	ret.X=bi.dwCursorPosition.X;
	ret.Y=bi.dwCursorPosition.Y;
	return ret;
}

/* Спрятать "каретку" */
void hide_cur()
{
  HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);  
  CONSOLE_CURSOR_INFO cursor = {1, false}; 
  SetConsoleCursorInfo(hCons, &cursor);
}

/* Показать "каретку" */
void show_cur()
{
  HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);  
  CONSOLE_CURSOR_INFO cursor = {20, true}; 
  SetConsoleCursorInfo(hCons, &cursor);
}

/* Изменение размера окна */
void windowSize(int width,int height)
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD crd = {width, height};
    SMALL_RECT src = {0, 0, crd.X-1, crd.Y-1};
    SetConsoleWindowInfo (out_handle, true, &src);
    SetConsoleScreenBufferSize (out_handle, crd);    
}

/* Изменение цвета выводимого текста и фона */
void SetColor(int text, int background)
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
/* Получение информации о количестве должностей в переданном отделении*/
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

/* Вывод на экран всех должностей данного отделения */
void prntPosts(int department)
{
	switch(department)
	{
	case 1:
		{
			std::cout<<"  Механик;"<<endl;
			std::cout<<"  Старший мастер;"<<endl;
			std::cout<<"  Мастер ГПМ;"<<endl;
			std::cout<<"  Токарь;"<<endl;
			break;
		}
	case 2:
		{
			std::cout<<"  Энергетик;"<<endl;
			std::cout<<"  Электрик;"<<endl;
			std::cout<<"  Электромеханик;"<<endl;
			std::cout<<"  Сантехник;"<<endl;
			break;
		}
	case 3:
		{
			std::cout<<"  Главный мастер;"<<endl;
			std::cout<<"  Мастер;"<<endl;
			std::cout<<"  Уборщик;"<<endl;
			std::cout<<"  Плотник;"<<endl;
			break;
		}
	case 4:
		{
			std::cout<<"  Старщий кладовщик;"<<endl;
			std::cout<<"  Кладовщик;"<<endl;
			break;
		}
	case 5:
		{
			std::cout<<"  Начальник тех. бюро;"<<endl;
			std::cout<<"  Старший технолог;"<<endl;
			std::cout<<"  Технолог;"<<endl;
			break;
		}
	case 6:
		{
			std::cout<<"  Сварщик;"<<endl;
			std::cout<<"  Тракторист;"<<endl;
			std::cout<<"  Комплектовщик;"<<endl;
			break;
		}
	}
}

/* Получение информации о зарплате, которую получает работник данной должности на данном отделении */
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

/* Вывод отделения */
void prntDepartment(int department)
{
	switch(department)
	{
	case 1:std::cout<<" Электромеханическое ";break;
	case 2:std::cout<<"Электроэнергетическое";break;
	case 3:std::cout<<"   Строй. участок    ";break;
	case 4:std::cout<<"        Склад        ";break;
	case 5:std::cout<<"Отделение технологов ";break;
	case 6:std::cout<<"      Поставка       ";break;
	}
}

/* Вывод должности */
void prntPost(int department,int post)
{
	switch(department)
	{
	case 1:
		{
			switch(post)
			{
			case 1: std::cout<<"      Механик       ";break;
			case 2: std::cout<<"   Старший мастер   ";break;
			case 3: std::cout<<"     Мастер ГПМ     ";break;
			case 4: std::cout<<"       Токарь       ";break;			
			}
			break;
		}
	case 2:
		{
			switch(post)
			{
			case 1: std::cout<<"     Энергетик      ";break;
			case 2: std::cout<<"      Электрик      ";break;
			case 3: std::cout<<"   Электромеханик   ";break;
			case 4: std::cout<<"     Сантехник      ";break;
			}
			break;
		}
	case 3:
		{
			switch(post)
			{
			case 1: std::cout<<"   Главный мастер   ";break;
			case 2: std::cout<<"       Мастер       ";break;
			case 3: std::cout<<"      Уборщик       ";break;
			case 4: std::cout<<"      Плотник       ";break;
			}
			break;
		}
	case 4:
			switch(post)
			{
			case 1: std::cout<<"  Старщий кладовщик ";break;
			case 2: std::cout<<"     Кладовщик      ";break;
			}
			break;
	case 5:
		{
			switch(post)
			{
			case 1: std::cout<<"Начальник тех. бюро ";break;
			case 2: std::cout<<"  Старший технолог  ";break;
			case 3: std::cout<<"      Технолог      ";break;
			}
			break;
		}
	case 6:
		{
			switch(post)
			{
			case 1: std::cout<<"      Сварщик       ";break;
			case 2: std::cout<<"     Тракторист     ";break;
			case 3: std::cout<<"   Комплектовщик    ";break;
			}
			break;
		}
	}
}

/* Перевод вводимых букв русского алфавита в корректную кириллицу */
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

/* Перевод всех русских символов переданной строки в корректную кириллицу */
void makeNormal(char *st)
{
	int i=0;
	while(st[i]!='\0')
	{
		st[i]=toNormalRus(st[i]);
		i++;
	}
}

/* Функция проверки на буквы с поддержкой русских символов (взамен стандартной) */
bool isalpha(char s)
{
	if(((s>='a')&&(s<='z'))||((s>='A')&&(s<='Z'))||((s>=-32)&&(s<=-1))||((s>=-64)&&(s<=-33)))
	/* Если символ является буквой - возвращаем true, иначе - false */
		return true;
	return false;
}

/* Перевод всех символов в нижний регистр и запись в исходящую строку */
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

/* Создание меню (y - высота меню, k - количество пунктов меню) */
int menu(int y,int k)
{
	hide_cur();/* Скрываем "каретку" */
	int pm=1;/* Переменная для хранения выбранного пункта меню */
	gotoxy(1,y);/* Переходим в позицию первого пункта */
	std::cout<<">";/* Выводим курсор */
	char ch='\0';/* Переменная для хранения нажатой клавиши */
	while(ch!=13)/* Пока не нажат Enter */
	{
		ch=_getch();/* Ожидаем нажатия клавиши */
		gotoxy(1,y+pm-1);
		std::cout<<" ";/* Стираем курсор */
		switch(ch)
		{
		case 'H':/* Если нажата стрелка вверх */
			{
				pm--;/* Уменьшаем номер пункта меню */
				if(pm<1)/* Если измененный пункт меню меньше единицы */
					pm=k;/* Делаем выбранным пунктом последний пункт */
				break;
			}
		case 'P':/* Если нажата стрелка вниз */
			{
				pm++;/* Увеличиваем номер пункта меню */
				if(pm>k)/* Если измененный пункт меню больше, чем количество пунктов в меню */
					pm=1;/* Выбираем первый пункт */
				break;
			}
		}
		gotoxy(1,y+pm-1);
		std::cout<<">";/* Выводим курсор на позицию, указанную в pm */
	}
	show_cur();/* Возвращаем "каретку" */
	return pm;/* Возвращаем выбранный пункт меню */
}

/* Простой запрос */
bool e_ansv(char mess[256])
{
	int y=getxy().Y;/* Сохраняем текущее положение "каретки" по оси Y */
	gotoxy(0,y);/* Переходим в начало текущей строки */
	cout<<" "<<mess<<endl;/* Выводим переданное сообщение и варианты ответа */
	cout<<"  Да"<<endl;
	cout<<"  Нет"<<endl;
	int pm=menu(y+1,2)-1;/* Организовываем выбор пункта меню через специальную функцию */
	gotoxy(0,y+3);
	if(!pm)
		return true;
	return false;
}

/* Получить количество записей в файле */
int getFileSize(FILE *file)
{
	int i=0;/* Количество записей */
	employee a;/* Переменная типа структуры (для чтения из файла) */
	rewind(file);/* Переходим в начало файла */
	while(fread(&a,sizeof(employee),1,file))/* До тех пор, пока происходит чтение из файла */
		i++;/* Увеличиваем количество записей на единицу */
	rewind(file);/* Переходим на начало файла */
	return i;/* Возвращаем количество записей */
}

/* Вывод шапки таблицы */
void prntHeader()
{
	/* Первая строка */
	for(int i=0;i<119;i++)
		std::cout<<"_";
	std::cout<<endl;
	/* Вторая строка */
	std::cout<<"| № |        ФИО         |      Отделение      |     Должность      | Возраст | Стаж | Отработано | Зарплата | Выдано |"<<endl;
	/* Третья строка */
	for(int i=0;i<119;i++)
		std::cout<<"_";
	std::cout<<endl;
}

/* Вывод на экран переданной записи */
void prntRecord(int n,employee worker)
{
	if(n%2!=0)
		SetColor(0,7);
	printf("|%3i|%20s|",n,worker.fio);/* Выводим полученную запись */
	prntDepartment(worker.department);
	std::cout<<"|";
	prntPost(worker.department,worker.post);
	printf("| %3i лет |%2i лет| %5i дней | %8.2f |",worker.age,worker.exp,worker.spendDays,worker.salary);
	if(worker.recd)
		std::cout<<"   Да   ";
	else
		std::cout<<"   Нет  ";
	std::cout<<"|"<<endl;
	SetColor(0,15);
}

/* Вывод массива переменных типа employee */
void prntMas(employee *wMas,int kSearched)
{
	int pages=kSearched/(maxRecordsPerPage+1);/* Количество страниц записей (0 - одна страница) */
	if(pages)/* Если страниц больше, чем одна */
	{
		char ch='\0';/* Символ нажатой клавиши */
		int cPage=0;/* Номер текущей страницы */
		while(ch!=13)
		{
			system("cls");
			prntHeader();/* Выводим шапку таблицы */
			int i=1;
			while(i<=maxRecordsPerPage)	/* пока не будет выведено макс. количество для одной страницы */
			{
				prntRecord(i+cPage*maxRecordsPerPage,wMas[i-1+cPage*maxRecordsPerPage]);
				i++;
			}
			for(int j=0;j<119;j++)/* Подчеркиваем таблицу */
				std::cout<<"_";
			std::cout<<endl<<endl;
			std::cout<<" Для завершения просмотра нажмите Enter; Для передвижению по страницам используйте стрелки вверх или вниз";
			bool f=false;/* Функция для продолжения цикла */
			do/* Ожидание нажатие одной из подходящих клавиш (для избавления от мелькания экрана) */
			{
				ch=_getch();/* Ожидание нажатия клавиши */
				switch(ch)
				{
				case 'H':/* Если нажата стрелка влево */
					{
						if(cPage>0)/* Если мы находимся на странице, номер которой больше нуля */
						{
							cPage--;/* Уменьшаем номер страницы */
							f=true;/* Выходим из цикла do...while */
						}
						break;
					}
				case 'P':/* Если нажата стрелка вправо */
					{
						if(cPage<pages)/* Если мы находимся на странице, номер которой меньше, чем общее количество страниц */
						{
							cPage++;/* Увеличиваем номер страницы */
							f=true;/* Выходим из цикла do...while */
						}
						break;
					}
				case 13:
					{
						f=true;/* Выходим из цикла do...while */
						break;
					}
				}
			}while(!f);
		}
		return;
	}
	/* Если страница всего одна */
	system("cls");
	prntHeader();/* Выводим шапку таблицы */
	for(int i=0;i<kSearched;i++)/* Выводим найденные записи */
		prntRecord(i+1,wMas[i]);
	for(int j=0;j<119;j++)/* Подчеркиваем таблицу */
		std::cout<<"_";
	std::cout<<endl<<endl;
	system("pause");
}

/* Удаление записи из файла по номеру (номер вводится начиная с единицы!) */
void removeRecord(int n,FILE *fp)
{
	fseek(fp,sizeof(employee)*(n),SEEK_SET);/* Переходим к записи, следующей после удаляемой */
	employee wr;/* Переменная для хранения записи */
	int i=0;/* Номер перемещаемой записи */
	while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
	{
		fseek(fp,sizeof(employee)*(n+i-1),SEEK_SET);/* Переходим на 1 запись ранее */
		fwrite(&wr,sizeof(employee),1,fp);/* Переписываем на место текущей записи следующую */
		i++;/* Увеличиваем номер перемещаемой записи */
		fseek(fp,sizeof(employee)*(n+i),SEEK_SET);/* Переходим к следующей перемещаемой записи */
	}
	_chsize(_fileno(fp), sizeof(employee)*(getFileSize(fp)-1));/* Отслекаем последнюю запись (т.к. у нас последняя запись идентична предпоследней) */
	fseek(fp,sizeof(employee)*(n-1),SEEK_SET);
}

// -- ФУНКЦИИ ВВОДА ДАННЫХ --

/* Функция для ввода ФИО (str - возвращаемая строка) */
void enterFIO(char *str)
{
	bool f=true;/* Флажек для работы цикла */
	while(f)/* Пока флажек активен и есть ошибки в вводе */
	{
		f=false;
		//std::cout<<" Введите фамилию и инициалы работника (латиницей):";
		char buff[80];
		cin.clear();/* Очистка буффера (для корректной работы gets_s()) */
		cin.sync();
		gets_s(buff,80);
		buff[79]='\0';/* Ставим на последнюю позицию строки признак конца строки */
		makeNormal(buff);
		int i(0),iS(0);/* Переменные для перехода по введенной строке и возвращаемой строке */
		
		/* ФАМИЛИЯ */
		while((!isalpha(buff[i]))&&(buff[i]!='\0'))/* Пропускаем все символы, не являющиеся буквами */
			i++;
		if(buff[i]=='\0')/* Если строка закончилась */
		{
			std::cout<<" - Вы ничего не ввели! Повторите ввод!"<<endl;
			f=true;
			continue;
		}
		str[iS]=toupper(buff[i]);/* Если всё нормально, то переводим первую букву в верхний регистр и 
								    заносим первый символ в возвращаемую строку*/
		iS++; i++;
		while((isalpha(buff[i]))&&(iS<15))/* Записываем остальные части фамилии */
		{
			str[iS]=tolower(buff[i]);/* Переводим символ в нижний регистр и заносим его в возвращаемую строку */
			iS++; i++;
		}
		str[iS]=' ';/* Ставим пробел после фамилии */
		iS++;

		/* ПЕРВЫЙ ИНИЦИАЛ */

		while((!isalpha(buff[i]))&&(buff[i]!='\0'))/* Пропускаем все символы, не являющиеся буквами */
			i++;
		if(buff[i]=='\0')/* Если строка закончилась */
		{
			std::cout<<" - Вы не ввели инициалов! Повторите ввод!"<<endl;
			f=true;
			continue;
		}
		str[iS]=toupper(buff[i]);/* Если всё нормально, то переводим найденный инициал в верхний регистр и 
								    заносим его в возвращаемую строку*/
		iS++; i++;

		/* ВТОРОЙ ИНИЦИАЛ */

		str[iS]='.';/* Ставим точку после первого инициала */
		iS++;
		while((!isalpha(buff[i]))&&(buff[i]!='\0'))/* Пропускаем все символы, не являющиеся буквами */
			i++;
		if(buff[i]=='\0')/* Если строка закончилась */
		{
			std::cout<<" - Вы не ввели второй инициал! Повторите ввод!"<<endl;
			f=true;
			continue;
		}
		str[iS]=toupper(buff[i]);/* Если всё нормально, то переводим найденный инициал в верхний регистр и 
								    заносим его в возвращаемую строку*/
		iS++; i++;
		str[iS]='.';/* Ставим точку после второго инициала */
		iS++;
		str[iS]='\0';/* Ставим конец строки */
	}
}

/* Функция ввода целых чисел (от 0) */
int enterInt()
{
	bool f=true;/* Флажек для работы цикла */
	char buff[80];/* Строка для ввода */
	while(f)/* Пока флажек активен и есть ошибки в вводе */
	{
		f=false;
		cin.clear();/* Очистка буффера (для корректной работы gets_s()) */
		cin.sync();
		gets_s(buff,80);
		buff[79]='\0';/* Ставим на последнюю позицию строки признак конца строки */
		makeNormal(buff);/* Переводим русские символы в нормальный вид (без этого isdigit будет выдавать системную ошибку) */
		int i(0);/* Переменная для прохода по строке */
		while(buff[i]!='\0')/* Пока строка не закончилась */
		{
			if(((buff[i]>=-32)&&(buff[i]<=-1))||((buff[i]>=-64)&&(buff[i]<=-33))||(!isdigit(buff[i])))/* Если символ строки - не цифра */
			{
				f=true;
				break;
			}
			i++;
		}
		if(f)/* Если допущены ошибки при вводе */
		{
			std::cout<<" - Введено некорректное число!"<<endl<<"   Повторите ввод:";
			continue;
		}
	}
	return atoi(buff);/* Переводим введенную строку в число и возвращаем */
}

/* Функция для ввода отделения */
int enterOffice()
{
	int nY=getxy().Y,fl(1);/* Инициализация высоты текста и флажка выбранного пункта */
	gotoxy(0,nY);/* Переходим на начало строки, в которой мы находимся */
	std::cout<<" === Выберите отделение ==="<<endl;/* Выводим начальный вид меню */
	std::cout<<"  Электромеханическое;"<<endl;
	std::cout<<"  Электроэнергетическое;"<<endl;
	std::cout<<"  Строительный участок;"<<endl;
	std::cout<<"  Склад;"<<endl;
	std::cout<<"  Отделение технологов;"<<endl;
	std::cout<<"  Поставка;"<<endl;
	fl=menu(nY+1,6);/* Организация меню с помощью специальной функции */
	gotoxy(0,nY+7);/* Переходим на конец меню */
	return fl;
}

/* Функция для ввода должности */
int enterPost(int department)
{
	int nY=getxy().Y,fl(1);/* Инициализация высоты текста и флажка выбранного пункта */
	gotoxy(0,nY);/* Переходим на начало строки, в которой мы находимся */
	std::cout<<" === Выберите должность ==="<<endl;/* Выводим начальный вид меню */
	prntPosts(department);/* Выводим все должности данного отделения */
	fl=menu(nY+1,getAmPosts(department));/* Организация меню с помощью специальной функции */
	gotoxy(0,nY+getAmPosts(department)+1);/* Переходим на конец меню */
	return fl;
}

/* Функция для ввода возраста */
int enterAge()
{
	int age(0);/* Инициализируем переменную возраста */
	while((age<18)||(age>80))/* Если введенный возраст меньше 18 или больше 80 */
	{
		age=enterInt();/* Вводим возраст с помощбю специальной функции */
		if((age<18)||(age>80))
			std::cout<<" - Возраст работника должен быть от 18 до 80 включительно!"<<endl<<" Повторите ввод:";
	}
	return age;
}

/* Функция для ввода стажа */
int enterExp(int age)
{
	int exp(age+18);/* Инициализируем переменную стажа */
	while(exp>age-18)/* Если введенный стаж больше, чем максимально возможный стаж для этого возраста 
					    (при условии, что минимальный возраст для приёма на работу - 18 лет */
	{
		exp=enterInt();/* Вводим стаж с помощбю специальной функции */
		if(exp>age-18)
			std::cout<<" - Стаж данного работника не может быть больше "<<age-18<<" лет!"<<endl<<" Повторите ввод:";
	}
	return exp;
}

void countSalary(employee &worker)
{
	double slr=worker.spendDays*getSalary(worker.department,worker.post);/* Высчитываем зарплату без надбавки */
	double premium(0);/* Инициализируем переменную надбавки */
	if((worker.exp>=10)&&(worker.exp<=20))/* Если стаж работника от 10 до 20 лет */
		premium=slr/10;
	if((worker.exp>=20)&&(worker.exp<=30))/* Если стаж работника от 20 до 30 лет */
		premium=slr/4;
	if(worker.exp>30)/* Если стаж работника более 30 лет */
		premium=slr*4/10;
	worker.salary=slr+premium;/* Заносим зарплату в запись */
}

/* Ввод фамилии для поиска (с разными вариантами) */
void enterFIOForSearch(char *st)
{
	int nY=getxy().Y,fl(1);/* Инициализация высоты текста и флажка выбранного пункта */
	gotoxy(0,nY);/* Переходим на начало строки, в которой мы находимся */
	std::cout<<" === По какой части фамилии проводить поиск ==="<<endl;/* Выводим начальный вид меню */
	std::cout<<"  По всей фамилии;"<<endl;
	std::cout<<"  По части фамилии;"<<endl;
	std::cout<<"  По первым 3-м буквам;"<<endl;
	fl=menu(nY+1,3);/* Организация меню с помощью специальной функции */
	gotoxy(0,nY+7);/* Переходим на конец меню */
	system("cls");
	switch(fl)
	{
	case 1:
		{
			std::cout<<" === Введите фамилию и инициалы работника ==="<<endl;
			std::cout<<endl<<" >";
			enterFIO(st);
			break;
		}
	case 2:
		{
			std::cout<<" === Введите часть ФИО работника ==="<<endl<<" >";
			char FIO[21];
			gets_s(FIO);/* Вводим искомое ФИО */
			makeNormal(FIO);
			strcpy(st,FIO);
			break;
		}
	case 3:
		{
			std::cout<<" === Введите первые 3 буквы фамилии работника ==="<<endl<<" >";
			char FIO[21];
			do
			{
				gets_s(FIO);/* Вводим искомое ФИО */
				if(strlen(FIO)!=3)
					cout<<" - Вы должны ввести 3 буквы!"<<endl<<" >";
			}while(strlen(FIO)!=3);
			FIO[3]='\0';/* Урезаем до 3-х символов */
			makeNormal(FIO);
			st[0]='3';/* Записываем в начало возвращаемой строки тройку, чтобы поисковик искал именно по трем ПЕРВЫМ буквам */
			strcpy(st+1,FIO);
			break;
		}
	}
	return;
}

/* Сравнение первых трех символов */
bool checkFirstThreeLetters(char *st,char *st1)
{
	for(int i=0;i<3;i++)
		if(st[i]!=st1[i])/* Если найдено несовпадение */
			return false;
	return true;
}

// -- ОСНОВНЫЕ ФУНКЦИИ --

/* Вывод всех записей на экран */
void showRecords()
{
	FILE *fp=fopen(FILE_WAY,"rb");
	if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
	{
		std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl<<" Возможно файл не создан. Создать его можно, добавив записи в файл."<<endl;
		system("pause");
		return;
	}
	employee wr;/* Переменная типа структуры */
	int fSize=0;/* Количество записей в файле */
	while(fread(&wr,sizeof(employee),1,fp))	/* Подсчет количества записей в файле */
		fSize++;
	rewind(fp);
	int pages=fSize/(maxRecordsPerPage+1);/* Количество страниц записей (0 - одна страница) */
	if(pages)/* Если страниц больше, чем одна */
	{
		char ch='\0';/* Символ нажатой клавиши */
		int cPage=0;/* Номер текущей страницы */
		while(ch!=13)
		{
			system("cls");
			prntHeader();/* Выводим шапку таблицы */
			int i=1;
			fseek(fp,sizeof(employee)*cPage*maxRecordsPerPage,SEEK_SET);
			while((fread(&wr,sizeof(employee),1,fp))&&(i<=maxRecordsPerPage))	/* Вывод записей, пока они не закончатся или 
																				   пока не будет выведено макс. количество для одной страницы */
			{
				prntRecord(i+cPage*maxRecordsPerPage,wr);
				i++;
			}
			for(int i=0;i<119;i++)/* Подчеркиваем таблицу */
				std::cout<<"_";
			std::cout<<endl<<endl;
			std::cout<<" Для завершения просмотра нажмите Enter; Для передвижению по страницам используйте стрелки вверх или вниз";
			bool f=false;/* Функция для продолжения цикла */
			do/* Ожидание нажатие одной из подходящих клавиш (для избавления от мелькания экрана) */
			{
				ch=_getch();/* Ожидание нажатия клавиши */
				switch(ch)
				{
				case 'H':/* Если нажата стрелка влево */
					{
						if(cPage>0)/* Если мы находимся на странице, номер которой больше нуля */
						{
							cPage--;/* Уменьшаем номер страницы */
							f=true;/* Выходим из цикла do...while */
						}
						break;
					}
				case 'P':/* Если нажата стрелка вправо */
					{
						if(cPage<pages)/* Если мы находимся на странице, номер которой меньше, чем общее количество страниц */
						{
							cPage++;/* Увеличиваем номер страницы */
							f=true;/* Выходим из цикла do...while */
						}
						break;
					}
				case 13:
					{
						f=true;/* Выходим из цикла do...while */
						break;
					}
				}
			}while(!f);
		}
		fclose(fp);/* Закрываем файл */
		return;
	}
	/* Если страница всего одна */
	prntHeader();/* Выводим шапку таблицы */
	int i=1;
	while(fread(&wr,sizeof(employee),1,fp))	/* Вывод записей, пока они не закончатся  */
	{
		prntRecord(i,wr);
		i++;
	}
	for(int i=0;i<119;i++)/* Подчеркиваем таблицу */
		std::cout<<"_";
	std::cout<<endl<<endl;
	system("pause");
	fclose(fp);/* Закрываем файл */
}

/* Добавление записей в файл */
void addRecords()
{
	FILE *fp=fopen(FILE_WAY,"a+b");
	if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
	{
		std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ/СОЗДАТЬ ФАЙЛ !!!"<<endl;
		system("pause");
		return;
	}
	employee aw;/* Переменную типа структуры */
	bool f(1);/* Переменная для цикла */
	while(f)
	{
		/* ФИО */
		system("cls");
		std::cout<<" --- Введите фамилию и инициалы работника ---"<<endl;
		std::cout<<endl<<" >";
		enterFIO(aw.fio);
		/* ОТДЕЛЕНИЕ */
		system("cls");
		aw.department=enterOffice();
		/* ДОЛЖНОСТЬ */
		system("cls");
		aw.post=enterPost(aw.department);
		/* ВОЗРАСТ */
		system("cls");
		std::cout<<" --- Введите возраст работника ---"<<endl;
		std::cout<<endl<<" >";
		aw.age=enterAge();
		/* СТАЖ */
		system("cls");
		std::cout<<" --- Введите стаж работника ---"<<endl;
		std::cout<<endl<<" >";
		aw.exp=enterExp(aw.age);
		/* ОТРАБОТАННЫЕ ДНИ */
		system("cls");
		std::cout<<" --- Введите количество отработанных дней ---"<<endl;
		do
		{
			std::cout<<endl<<" >";
			aw.spendDays=enterInt();
			if(aw.spendDays>31)
				std::cout<<" - Ввести нужно число от 0 до 31! Повторите ввод!";
		}while(aw.spendDays>31);
		/* ЗАРПЛАТА */
		countSalary(aw);
		/* ВЫДАЧА */
		system("cls");
		aw.recd=e_ansv(" --- Выдана ли зарплата? ---");
		/* ПРЕДПРОСМОТР */
		system("cls");
		prntHeader();
		printf("| 1 |%20s|",aw.fio);
		prntDepartment(aw.department);
		std::cout<<"|";
		prntPost(aw.department,aw.post);
		printf("|   %3i   |  %2i  |  %8i  | %8.2f |",aw.age,aw.exp,aw.spendDays,aw.salary);
		if(aw.recd)
			std::cout<<"   Да   ";
		else
			std::cout<<"   Нет  ";
		std::cout<<"|"<<endl;
		for(int i=0;i<119;i++)
			std::cout<<"_";
		std::cout<<endl<<endl;
		bool ansv=e_ansv("Добавить эту запись? (в дальнейшем её можно будет отредактировать)");
		if(ansv)
			fwrite(&aw,1,sizeof(aw),fp);
		std::cout<<endl<<endl;
		f=e_ansv("Добавить ещё одну запись?");
	}
	fclose(fp);/* Закрываем файл */
}

/* Редактирование записей */
void editRecords()
{
	int num=1;
	while(num!=0)
	{
		system("cls");
		showRecords();
		FILE *fp=fopen(FILE_WAY,"r+b");
		if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
		{
			std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl;
			system("pause");
			return;
		}
		std::cout<<endl<<" === Введите номер записи, которую вы хотите отредактировать (или введите 0, чтобы выйти) ==="<<endl<<"  >";
		num=enterInt();/*  Ввод номера записи, которую нужно редактировать (либо же нуля,чтобы выйти) */
		if(num==0)/* Если введен ноль */
			break;
		if(num>getFileSize(fp))/* Если введенное число больше, чем количество записей в файле */
		{
			cout<<" Нет записи с таким номером! Внимательно взгляните на записи и повторите ввод!"<<endl;
			system("pause");
		}
		else/* Если введен не ноль и не число, большее, чем количество записей в файле */
		{
			fseek(fp,sizeof(employee)*(num-1),SEEK_SET);/* Переходим к нужной нам записи в файле */
			employee wr;/* Переменная типа структуры для хранения редактируемой записи */
			fread(&wr,sizeof(employee),1,fp);/* Читаем нужную запись из файла в переменную */
			int pm=1;/* Выбранный пункт меню */
			while(pm!=9)/* Пока не выбран пункт выхода */
			{
				system("cls");/* Очищаем экран */
				prntHeader();/* Выводим шапку таблицы */
				prntRecord(num,wr);/* Выводим редактируемую запись */
				for(int i=0;i<119;i++)/* Подчемркиваем таблицу */
					std::cout<<"_";
				std::cout<<endl<<endl;/* Отступаем одну строку от таблицы и выводим меню */
				std::cout<<" === Что нужно отредактировать? ==="<<endl;
				int mY=getxy().Y;/* Высота меню */
				std::cout<<"  ФИО работника;"<<endl;/* 1 */
				std::cout<<"  Отделение;"<<endl;/* 2 */
				std::cout<<"  Должность;"<<endl;/* 3 */
				std::cout<<"  Возраст;"<<endl;/* 4 */
				std::cout<<"  Стаж;"<<endl;/* 5 */
				std::cout<<"  Отработанные дни;"<<endl;/* 6 */
				std::cout<<"  Статус получения зарплаты;"<<endl;/* 7 */
				std::cout<<"  Запись целиком;"<<endl;/* 8 */
				std::cout<<"  Выход в предыдущее меню."<<endl;/* 9 */
				pm=menu(mY,9);/* Организовываем меню */
				switch(pm)/* Выполняем выбранные в меню действия */
				{
				case 1:
					{
						system("cls");
						std::cout<<" === Введите фамилию и инициалы работника (латиницей) ==="<<endl<<" >";
						enterFIO(wr.fio);
						break;
					}
				case 2:
					{
						system("cls");
						wr.department=enterOffice();
						/* break специально пропущен, чтобы после ввода отделения сразу был предложен ввод должности */
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
						std::cout<<" --- Введите возраст работника ---"<<endl;
						std::cout<<endl<<" >";
						wr.age=enterAge();
						/* break специально пропущен, чтобы после ввода возраста был предложен ввод стажа */
					}
				case 5:
					{
						system("cls");
						std::cout<<" --- Введите стаж работника ---"<<endl;
						std::cout<<endl<<" >";
						wr.exp=enterExp(wr.age);
						countSalary(wr);
						break;
					}
				case 6:
					{
						system("cls");
						std::cout<<" --- Введите количество отработанных дней ---"<<endl;
						do
						{
							std::cout<<endl<<" >";
							wr.spendDays=enterInt();
							if(wr.spendDays>31)
								std::cout<<" - Ввести нужно число от 0 до 31! Повторите ввод!";
						}while(wr.spendDays>31);
						countSalary(wr);
						break;
					}
				case 7:
					{
						system("cls");
						wr.recd=e_ansv(" --- Выдана ли зарплата? ---");
						break;
					}
				case 8:
					{
						/* ФИО */
						system("cls");
						std::cout<<" --- Введите фамилию и инициалы работника (латиницей) ---"<<endl;
						std::cout<<endl<<" >";
						enterFIO(wr.fio);
						/* ОТДЕЛЕНИЕ */
						system("cls");
						wr.department=enterOffice();
						/* ДОЛЖНОСТЬ */
						system("cls");
						wr.post=enterPost(wr.department);
						/* ВОЗРАСТ */
						system("cls");
						std::cout<<" --- Введите возраст работника ---"<<endl;
						std::cout<<endl<<" >";
						wr.age=enterAge();
						/* СТАЖ */
						system("cls");
						std::cout<<" --- Введите стаж работника ---"<<endl;
						std::cout<<endl<<" >";
						wr.exp=enterExp(wr.age);
						/* ОТРАБОТАННЫЕ ДНИ */
						system("cls");
						std::cout<<" --- Введите количество отработанных дней ---"<<endl;
						do
						{
							std::cout<<endl<<" >";
							wr.spendDays=enterInt();
							if(wr.spendDays>31)
								std::cout<<" - Ввести нужно число от 0 до 31! Повторите ввод!";
						}while(wr.spendDays>31);
						/* ЗАРПЛАТА */
						countSalary(wr);
						/* ВЫДАЧА */
						system("cls");
						wr.recd=e_ansv(" --- Выдана ли зарплата? ---");
						break;
					}
				}
			}
			fseek(fp,sizeof(employee)*(num-1),SEEK_SET);/* Находим место в файле, куда должна быть записана запись */
			fwrite(&wr,sizeof(employee),1,fp);/* Записываем запись в файл */
		}
		fclose(fp);/* Закрываем файл */
	}
}

/* Удаление записей */
void removeRecords()
{
	int pm=1;/* Выбранный пункт меню */
	while(pm!=3)/* Пока не выбран выход в гл. меню */
	{
		system("cls");/* Очищаем экран */
		showRecords();/* Выводим все записи */
		std::cout<<endl<<" === Выберите признак, по которому будет происходить удаление ==="<<endl;/* Выводим меню */
		int mY=getxy().Y;/* Записываем текущее положение курсора по оси Y */
		std::cout<<"  По ФИО;"<<endl;
		std::cout<<"  По возрасту;"<<endl;
		std::cout<<"  Выход в главное меню."<<endl;
		pm=menu(mY,3);/* Организовываем меню */
		FILE *fp=fopen(FILE_WAY,"r+b");/* Открывем файл в режиме расширеного чтения */
		if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
		{
			std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl;
			system("pause");
			return;
		}
		switch(pm)/* Выполняем действия согласно выбранному пункту меню */
		{
		case 1:
			{
				system("cls");
				//std::cout<<" === Введите часть ФИО работника, записи о котором вы желаете удалить ==="<<endl<<" >";
				char sFIO[2][21];/* Искомое ФИО */
				enterFIOForSearch(sFIO[0]);
				lowerAll(sFIO[0],sFIO[0]);/* Переводим все символы введенного ФИО в нижний регистр */
				rewind(fp);/* Переходим в начало файла */
				employee wr;/* Переменная для хранения записи */
				int i=1,kRemoved=0;/* Переменные номера текущей записи и подсчета количества удаленных записей */
				while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
				{
					lowerAll(wr.fio,sFIO[1]);
					if(
						((sFIO[0][0]=='3')&&(checkFirstThreeLetters(sFIO[1],&sFIO[0][1])))
						||
						((sFIO[0][0]!='3')&&(strstr(sFIO[1],sFIO[0])!=0))
						)/* Если искомое ФИО совпадает с данным */
					{
						system("cls");/* Очищаем экран */
						prntHeader();/* Выводим шапку таблицы */
						prntRecord(i,wr);/* Выводим текущую запись */
						for(int j=0;j<119;j++)/* Подчеркиваем таблицу */
							std::cout<<"_";
						std::cout<<endl<<endl;/* Отступаем одну строку от таблицы */
						bool fl=e_ansv("Удалить эту запись?");/* Спрашиваем, удалять ли эту запись */
						if(fl)/* Если fl=true */
						{
							removeRecord(i,fp);/* Удаляем текущую запись */
							kRemoved++;/* Увеличиваем количество удаленных записей */
						}
					}
					i++;/* Увеличиваем номер текущей записи */
				}
				system("cls");/* Очищаем экран */
				if(!kRemoved)/* Если бы не удалили ни одной записи */
					std::cout<<" Не удалено ни одной записи!"<<endl;
				else/* Иначе */
					std::cout<<" Удалено "<<kRemoved<<" записей!"<<endl;
				system("pause");
				break;
			}
		case 2:
			{
				system("cls");/* Очищаем экран */
				std::cout<<" === Введите границы возраста работника, записи о котором вы желаете удалить ==="<<endl<<" Нижняя граница:";
				int sAge[2];/* Верхняя и нижняя граница искомого возраста */
				sAge[0]=enterInt();/* Вводим нижнюю границу */
				std::cout<<" Верхняя граница:";
				sAge[1]=enterInt();/* Вводим верхнюю границу */
				rewind(fp);/* Переходим в начало файла */
				employee wr;/* Переменная для хранения записи */
				int i=1,kRemoved=0;/* Переменные номера текущей записи и подсчета количества удаленных записей */
				while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
				{
					if((wr.age>=sAge[0])&&(wr.age<=sAge[1]))/* Если возраст в текущей записи входит в нужный нам интервал */
					{
						system("cls");/* Очищаем экран */
						prntHeader();/* Выводим шапку таблицы */
						prntRecord(i,wr);/* Выводим текущую запись */
						for(int j=0;j<119;j++)/* Подчеркиваем таблицу */
							std::cout<<"_";
						std::cout<<endl<<endl;/* Отступаем одну строку от таблицы */
						bool fl=e_ansv("Удалить эту запись?");/* Спрашиваем, удалять ли эту запись */
						if(fl)/* Если fl=true */
						{
							removeRecord(i,fp);/* Удаляем текущую запись */
							kRemoved++;/* Увеличиваем количество удаленных записей */
						}
					}
					i++;/* Увеличиваем номер записи */
				}
				system("cls");/* Очищаем экран */
				if(!kRemoved)/* Если бы не удалили ни одной записи */
					std::cout<<" Не удалено ни одной записи!"<<endl;
				else/* Иначе */
					std::cout<<" Удалено "<<kRemoved<<" записей!"<<endl;
				system("pause");
				break;
			}
		}
		fclose(fp);/* Закрываем файл */
	}
}

/* Сортировка записей */
void sortRecords()
{
	int pm=1;
	while(pm!=0)
	{
		system("cls");
		cout<<" === Как сортировать записи? ==="<<endl;
		int mY=getxy().Y;
		cout<<"  По ФИО;"<<endl;
		cout<<"  По должности;"<<endl;
		cout<<"  Выйти в главное меню."<<endl;
		pm=menu(mY,3);
		switch(pm)
		{
		case 1:
			{
				FILE *fp=fopen(FILE_WAY,"r+b");/* Открывем файл в режиме расширеного чтения */
				if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
				{
					std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl;
					system("pause");
					return;
				}
				employee w1,w2;/* Переменные для хранения сравниваемых записей */
				bool f=true;/* Флажек, указывающий на присутствие/отсутствие факта изменения порядка записей */
				while(f)/* Пока были замены записей */
				{
					f=false;/* Не было замены */
					rewind(fp);/* Переходим в начало файла */
					while(fread(&w1,sizeof(employee),1,fp)&&fread(&w2,sizeof(employee),1,fp))/* Считываем 2 записи и сравниваем их */
					{
						if(strcmp(w1.fio,w2.fio)>0)/* Если первое ФИО "больше" второго */
						{
							fseek(fp,-2*long(sizeof(employee)),SEEK_CUR);/* Переходим на 2 позиции назад */
							fwrite(&w2,sizeof(employee),1,fp);/* Записываем "меньшее" ФИО */
							fwrite(&w1,sizeof(employee),1,fp);/* Записываем "большее" ФИО */
							f=true;/* Произошла замена */
							break;/* Выходим из цикла */
						}
						fseek(fp,-1*long(sizeof(employee)),SEEK_CUR);/* Переходим на 1 позицию назад */
					}
				}
				fclose(fp);/* Закрываем файл */
				showRecords();/* Выводим записи */
				break;
			}
		case 2:
			{
				FILE *fp=fopen(FILE_WAY,"r+b");/* Открывем файл в режиме расширеного чтения */
				if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
				{
					std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl;
					system("pause");
					return;
				}
				employee w1,w2;/* Переменные для хранения сравниваемых записей */
				bool f=true;/* Флажек, указывающий на присутствие/отсутствие факта изменения порядка записей */
				while(f)/* Пока были замены записей */
				{
					f=false;/* Не было замены */
					rewind(fp);/* Переходим в начало файла */
					while(fread(&w1,sizeof(employee),1,fp)&&fread(&w2,sizeof(employee),1,fp))/* Считываем 2 записи и сравниваем их */
					{
						if(((w1.department*10)+w1.post)>((w2.department*10)+w2.post))/* Создаём уникальные номера каждой должности посредством 
																					 добавления номера должности к номеру отделения, умноженного на 10.
																					 Таким образом десятки этого числа указывают на отдел, а единицы - на должность.
																					 При таком формировании номера 2 разные должности в одном или нескольких 
																					 отделениях не могут иметь одинаковый номер, и сортировка 
																					 происходит как по должностям, так и по отделениям */
						{
							fseek(fp,long(sizeof(employee))*(-2),SEEK_CUR);/* Переходим на 2 позиции назад */
							fwrite(&w2,sizeof(employee),1,fp);/* Записываем меньший номер отделения и должности */
							fwrite(&w1,sizeof(employee),1,fp);/* Записываем больший номер отделения и должности */
							f=true;/* Произошла замена */
							break;/* Выходим из цикла */
						}
						fseek(fp,-1*long(sizeof(employee)),SEEK_CUR);/* Переходим на 1 позицию назад */
					}
				}
				fclose(fp);/* Закрываем файл */
				showRecords();/* Выводим записи */
				break;
			}
		}
	}
}

/* Поиск записей */
void searchRecords()
{
	int pm=1;
	while(pm!=3)
	{
		system("cls");
		std::cout<<" === По какому признаку произвести поиск? ==="<<endl;
		std::cout<<"  По ФИО;"<<endl;
		std::cout<<"  По должности;"<<endl;
		std::cout<<"  Выход в главное меню."<<endl;
		pm=menu(1,3);
		switch(pm)
		{
		case 1:
			{
				FILE *fp=fopen(FILE_WAY,"rb");/* Открывем файл в режиме чтения */
				if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
				{
					std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl;
					system("pause");
					return;
				}
				system("cls");
				//std::cout<<" === Введите часть ФИО работника, записи о котором вы желаете увидеть ==="<<endl<<" >";
				char sFIO[2][21];/* Искомое ФИО */
				enterFIOForSearch(sFIO[0]);
				lowerAll(sFIO[0],sFIO[0]);/* Переводим все символы введенного ФИО в нижний регистр */
				system("cls");/* Очищаем экран */
				rewind(fp);/* Переходим в начало файла */
				employee wr;/* Переменная для хранения записи */
				employee *wMas=new employee[getFileSize(fp)];/* Массив для хранения подходящих записей */
				int i=1,kSearched=0;/* Переменные номера текущей записи и подсчета количества удаленных записей */
				while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
				{
					lowerAll(wr.fio,sFIO[1]);/* Переводим все символы полученного ФИО в нижний регистр и передаём в строку sFIO[1] */
					if(
						((sFIO[0][0]=='3')&&(checkFirstThreeLetters(sFIO[1],&sFIO[0][1])))
						||
						((sFIO[0][0]!='3')&&(strstr(sFIO[1],sFIO[0])!=0))
						)/* Если искомое ФИО совпадает с данным */
					{
						wMas[kSearched]=wr;
						kSearched++;/* Увеличиваем количество удаленных записей */
					}
					i++;/* Увеличиваем номер текущей записи */
				}
				fclose(fp);/* Закрываем файл */
				if(!kSearched)/* Если мы не нашли ни одной записи */
				{
					std::cout<<" Не найдено ни одной записи!"<<endl;
					system("pause");
					break;
				}
				prntMas(wMas,kSearched);/* Выводим найденные записи на экран */	
				delete wMas;
				break;
			}
		case 2:
			{
				FILE *fp=fopen(FILE_WAY,"rb");/* Открывем файл в режиме чтения */
				if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
				{
					std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl;
					system("pause");
					return;
				}
				system("cls");
				int sD=enterOffice();/* Искомый отдел */
				int sP=enterPost(sD);/* Искомая должность */
				system("cls");/* Очищаем экран */
				rewind(fp);/* Переходим в начало файла */
				employee wr;/* Переменная для хранения записи */
				employee *wMas=new employee[getFileSize(fp)];/* Массив для хранения подходящих записей */
				int i=1,kSearched=0;/* Переменные номера текущей записи и подсчета количества удаленных записей */
				while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
				{
					if((wr.department==sD)&&(wr.post==sP))/* Если искомый отдел и должность совпадают с данными */
					{
						wMas[kSearched]=wr;
						kSearched++;/* Увеличиваем количество удаленных записей */
					}
					i++;/* Увеличиваем номер текущей записи */
				}
				fclose(fp);/* Закрываем файл */
				if(!kSearched)/* Если мы не нашли ни одной записи */
				{
					std::cout<<" Не найдено ни одной записи!"<<endl;
					system("pause");
					break;
				}
				prntMas(wMas,kSearched);/* Выводим найденные записи на экран */
				delete wMas;
				break;
			}
		}
	}
}

/* ЗАПРОСЫ */

void request_1()
{
	FILE *fp=fopen(FILE_WAY,"rb");/* Открывем файл в режиме чтения */
	if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
	{
		std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl;
		system("pause");
		return;
	}
	employee wr;/* Переменная для хранения записи */
	fread(&wr,sizeof(employee),1,fp);/* Считываем из файла первую запись */
	double maxSalary=wr.salary;/* Максимальная зарплата */
	while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
		if(wr.salary>maxSalary)/* Если зарплата данного работника больше максимальной */
			maxSalary=wr.salary;/* Делаем данную зарплату максимальной */
	rewind(fp);/* Переходим в начало файла */
	employee *mas=new employee[getFileSize(fp)];/* Массив записей */
	int k=0;/* Количество записей в массиве */
	while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
		if(wr.salary==maxSalary)/* Если зарплата данного работника равна максимальной */
		{
			mas[k]=wr;/* Заносим запись в массив */
			k++;
		}
	fclose(fp);/* Закрываем файл */
	prntMas(mas,k);/* Выводим массив */
	delete mas;
	showRecords();
}


void request_2()
{
	system("cls");
	int cDep=enterOffice();/* Вводим отделение */
	FILE *fp=fopen(FILE_WAY,"rb");/* Открывем файл в режиме чтения */
	if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
	{
		std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl;
		system("pause");
		return;
	}
	employee wr;/* Переменная для хранения записи */
	double debt=0;/* Долг */
	while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
		if((wr.department==cDep)&&(!wr.recd))/* Если отделение совпадает с выбранным и зарплата не оплачена */
			debt+=wr.salary;/* Прибавляем данную зарплату к сумме долгов отделения */
	system("cls");
	std::cout<<endl<<" Общая сумма долгов по выбранному отделению (";/* Выводим долг */
	prntDepartment(cDep);
	std::cout<<") составляет "<<debt<<" грн."<<endl;
	system("pause");
	rewind(fp);
	employee *wMas=new employee[getFileSize(fp)];/* Массив для хранения подходящих записей */
	int kSearched=0;/* Переменная для подсчета количества удаленных записей */
	while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
	{
		if(wr.department==cDep)/* Если искомый отдел совпадает с данным */
		{
			wMas[kSearched]=wr;
			kSearched++;/* Увеличиваем количество удаленных записей */
		}
	}
	fclose(fp);/* Закрываем файл */
	if(!kSearched)/* Если мы не нашли ни одной записи */
	{
		std::cout<<" Не найдено ни одной записи!"<<endl;
		system("pause");
		return;
	}
	prntMas(wMas,kSearched);/* Выводим найденные записи на экран */	
	delete wMas;
}

void request_3()
{
	FILE *fp=fopen(FILE_WAY,"rb");/* Открывем файл в режиме чтения */
	if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
	{
		std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl;
		system("pause");
		return;
	}
	employee wr;
	int allWr=0;/* Общее количество работников */
	int wrPerDep[6]={0,0,0,0,0,0};/* Количество работников на каждое отделение */
	while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
	{
		allWr++;/* Увеличиваем общее количество работников */
		wrPerDep[wr.department-1]++;/* Увеличиваем количество работников данного отделения */
	}
	system("cls");
	std::cout<<" === Процентное соотношение работников по отделениям ==="<<endl<<endl;
	for(int i=0;i<33;i++)/* Выводим верхнюю границу таблицы */
		std::cout<<"_";
	std::cout<<endl;
	for(int i=0;i<6;i++)/* Выводим таблицу */
	{
		if(i%2!=0)
			SetColor(0,7);
		std::cout<<"|";
		prntDepartment(i+1);
		printf("| %6.2f",float(wrPerDep[i])*100/allWr);/* Подсчитываем и выводим количество работников данного отделения в процентах */
		std::cout<<"% |"<<endl;
		SetColor(0,15);
	}
	for(int i=0;i<33;i++)/* Подчеркиваем таблицу */
		std::cout<<"_";
	std::cout<<endl<<endl;
	fclose(fp);/* Закрываем файл */
	system("pause");
}

void request_4()
{
	FILE *fp=fopen(FILE_WAY,"rb");/* Открывем файл в режиме чтения */
	if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
	{
		std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl;
		system("pause");
		return;
	}
	employee wr;
	int allWr=0;/* Общее количество работников */
	int wrPerExp[4]={0,0,0,0};/* Количество работников на каждую категорию */
	while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
	{
		allWr++;/* Увеличиваем общее количество работников */
		/* Увеличиваем количество работников подходящей категории */
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
	std::cout<<" === Процентное соотношение работников по категориям стажа ==="<<endl<<endl;
	for(int i=0;i<25;i++)/* Выводим верхнюю границу таблицы */
		std::cout<<"_";
	std::cout<<endl;
	/* Подсчитываем и выводим количество работников на каждую категорию в процентах */
	printf("| от 0 до 10  | %6.2f%1c |\n",float(wrPerExp[0])*100/allWr,'%');
	SetColor(0,7);
	printf("| от 10 до 20 | %6.2f%1c |\n",float(wrPerExp[1])*100/allWr,'%');
	SetColor(0,15);
	printf("| от 20 до 30 | %6.2f%1c |\n",float(wrPerExp[2])*100/allWr,'%');
	SetColor(0,7);
	printf("| 30 и более  | %6.2f%1c |\n",float(wrPerExp[3])*100/allWr,'%');
	SetColor(0,15);
	for(int i=0;i<25;i++)/* Подчеркиваем таблицу */
		std::cout<<"_";
	std::cout<<endl<<endl;
	fclose(fp);/* Закрываем файл */
	system("pause");
}


void request_5()
{
	system("cls");
	int cDep=enterOffice();/* Вводим отделение */
	FILE *fp=fopen(FILE_WAY,"rb");/* Открывем файл в режиме чтения */
	if(fp==NULL)/* Открытие файла и реагирование на невозможность его открытия */
	{
		std::cout<<" !!! НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ !!!"<<endl;
		system("pause");
		return;
	}
	employee wr;/* Переменная для хранения записи */
	double sum=0;/* Общая сумма зарплат */
	int allWr=0;/* Количество работников данного отдела */
	while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
		if(wr.department==cDep)/* Если отделение совпадает с выбранным */
		{
			sum+=wr.salary;/* Прибавляем данную зарплату к сумме зарплат отделения */
			allWr++;/* Увеличиваем количество работников отделения */
		}
	system("cls");
	std::cout<<endl<<" Средняя зарплата по выбранному отделению (";/* Выводим среднюю зарплату */
	prntDepartment(cDep);
	std::cout<<") составляет "<<sum/allWr<<" грн."<<endl;
	system("pause");
	rewind(fp);
	employee *wMas=new employee[getFileSize(fp)];/* Массив для хранения подходящих записей */
	int kSearched=0;/* Переменная для подсчета количества удаленных записей */
	while(fread(&wr,sizeof(employee),1,fp))/* Пока происходит чтение из файла */
	{
		if(wr.department==cDep)/* Если искомый отдел совпадает с данным */
		{
			wMas[kSearched]=wr;
			kSearched++;/* Увеличиваем количество удаленных записей */
		}
	}
	fclose(fp);/* Закрываем файл */
	if(!kSearched)/* Если мы не нашли ни одной записи */
	{
		std::cout<<" Не найдено ни одной записи!"<<endl;
		system("pause");
		return;
	}
	prntMas(wMas,kSearched);/* Выводим найденные записи на экран */	
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
		std::cout<<" ===== Главное меню ====="<<endl<<endl;
		std::cout<<"  Просмотр файла;"<<endl;/* 1 */
		std::cout<<"  Добавление записей в файл;"<<endl;/* 2 */
		std::cout<<"  Редактирование записей;"<<endl;/* 3 */
		std::cout<<"  Удаление записей;"<<endl;/* 4 */
		std::cout<<"  Сортировка записей;"<<endl;/* 5 */
		std::cout<<"  Поиск по записям;"<<endl;/* 6 */
		std::cout<<"  Запросы;"<<endl;/* 7 */
		std::cout<<"  Выход из программы;"<<endl;/* 8 */
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
					std::cout<<" === Выберите запрос ==="<<endl;
					std::cout<<"  1. Вывод сотрудников с максимальной зарплатой;"<<endl;
					std::cout<<"  2. Расчет общей суммы долгов по выбранному отделению;"<<endl;
					std::cout<<"  3. Вывод процентного соотношения работников по отделениям;"<<endl;
					std::cout<<"  4. Вывод процентного соотношения работников по стажу;"<<endl;
					std::cout<<"  5. Вывод средней зарплаты работников выбранного отделения;"<<endl;
					std::cout<<"  Выход в главное меню."<<endl;
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