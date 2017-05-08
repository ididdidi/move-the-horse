/*
void metodMAN(cell CB[S][S]);          // Порядок функций при ручном обходе.
void method(cell CB[S][S], int step, int cho);// Порядок функций при обходе.
void zeroing(cell CB[S][S], int &step, int &cho);    // Обнуление при входе;
void parsing(cell CB[S][S]);          	   // Проверка данных ручного ввода;
int assay(cell CB[S][S]);		      // Проверка выполнения задачи.
int choice(cell CB[S][S]);   		         // Выбор следующей позиции.
void storage(cell CB[S][S],int &min, int &key, int &im, int &jm, int id, int jd);
					   // Хранение приоритетной позиции.
int scan(cell CB[S][S], int i, int j, int &min);      // Поиск минимального.
int back(cell CB[S][S], int &cho);         // Возврат до ближайшей развилки.
void Stop(int N);                                      // Завершение обхода.
*/
//---------------------------- МЕТОДЫ  КЛАССОВ -----------------------------
cell::cell()                   			     // Базовый конструктор;
 {
  status.i=0;                                  	   // Зануляем все значения;
  status.j=0;
  status.z=0;
  status.f=0;
  status.n=0;
  PrintS(22,20,2,1);                     // Вывод сообщения о работе метода;
 }
cell::operator = (int z)            	// Конструктор присваивания;
 {
  int x, y; x=wherex(); y=wherey();         // Запоминаем положение курсора;
  status.z=z;                                // Присваиваем текущее начение;
  PrintS(22,20,3,1,1);                   // Вывод сообщения о работе метода;
  gotoxy(x,y);                           // Возврат курсора обратно где был;
  return 0;                           		// Чтобы не ругался;
 }
int cell::cors()                               // Возврат текущего значения;
 {
  int x, y; x=wherex(); y=wherey();         // Запоминаем положение курсора;
  PrintS(22,20,4,1,1);                   // Вывод сообщения о работе метода;
  gotoxy(x,y);                           // Возврат курсора обратно где был;
  return(status.z);
 }
core *cell::adrs()                      // Возврат адреса текущего элемента;
 {
  int x, y; x=wherex(); y=wherey();         // Запоминаем положение курсора;
  PrintS(22,20,5,1,1);                   // Вывод сообщения о работе метода;
  gotoxy(x,y);                           // Возврат курсора обратно где был;
  return(&status);
 }
void cell::change(int i, int j, int z)//Изменение основных значений элемента;
 {
  int x, y; x=wherex(); y=wherey();         // Запоминаем положение курсора;
  status.i=i;                               // Изменение горизонтали предка;
  status.j=j;                                 // Изменение вертикали предка;
  status.z=z;                                // Изменение текущего значения;
  PrintS(22,20,3,1,1);                   // Вывод сообщения о работе метода;
  gotoxy(x,y);                           // Возврат курсора обратно где был;
 }
ostream &operator<<(ostream &stream, cell obg)
 {
       //     setw(3) ----------------- манипулятор, задающий ширину поля.
    stream << setw(3) << obg.status.j << "-" << setw(3) << obg.status.i;
  //    ****** stream, а не cout, т.к. тогда возможно подключение к любому
  //         ! ! ! ! ! ! ! ! ! ! ! ! !       потоку, а не только на экран.

  return stream;
 }

//========================== ОПРЕДЕЛЕНИЯ ФУНКЦИЙ ===========================
//--------------------- Порядок при ручном обходе ------------------------
void metodMAN(cell CB[S][S])
 {
  int step = 0;        			         // Шаг в алгоритме обхода;
  cho=0;           			      // Количество сделаных ходов;
  brk=1;            			   // Установка задержки в единицу;
  regSTR=reg=0;                                      // Режим ручного выбора хода;
  VIZ=1;
   Viz(CB);
   zeroing(CB,step,cho);       			   // Тотальноое обнуление;
   Viz(CB);
   coordViz();
  for(;;) {
	 switch (step){
	     case  0:  CB[i][j]=1; 		     // Установка в единицу;
		       sign=-sign;  		// Смена направления обхода;
		       cho++;                   // Инкремент счетчика ходов;
		       core *Way;
		       Way=CB[i][j].adrs(); // Взятие адреса тек. элемента;
		       Way->n=cho-1;
					step=1; continue;//Переход к case:1;
	     case  1:  Viz(CB);                            // Вывод матрицы;
		       Progress(11,50,64,cho);  // Вывод прогресса операции;
					step=2; continue;
	     case  2:  step = assay(CB);  	continue;//Проверка выполнения;
	     case  3:  step = choice(CB); 	continue;//Выбор следующего;
	     case  4:  step = back(CB,cho);     continue; //Откат из тупика;
	     case 10:  Stop(0);			return;//Окончание операции;

	      default:                 step=10; continue; // Окончание по
		   }                                             // дефолту;
	}
  }
//---------------------- Порядок функций при обходе ------------------------
void method(cell CB[S][S], int step, int cho)
{
 for(;;) {
	 switch (step){
	     case  0:  CB[i][j]=1; 		     // Установка в единицу;
		       sign=-sign;  		// Смена направления обхода;
		       cho++;                   // Инкремент счетчика ходов;
		       gotoxy(47,16); printf("%4d",cho); // Вывод тек. хода;
		       Progress(15,24,64,cho);  // Вывод прогресса операции;
					step=1; continue;//Переход к case:1;
	     case  1:  Look(CB);	step=2; continue;  // Вывод матрицы;
	     case  2:  step = assay(CB);  	continue;//Проверка выполнения;
	     case  3:  step = choice(CB); 	continue;//Выбор следующего;
	     case  4:  step = back(CB,cho);     continue; //Откат из тупика;
	     case 10:  Stop(0);			return;//Окончание операции;

	      default:                 step=10; continue; // Окончание по
		   }                                             // дефолту;
	}
}
//-------------------------- Обнуление при входе ---------------------------
void zeroing(cell CB[S][S], int &step, int &cho)
 {
   step = 0; cho=0;        			     // Обнуление при входе!
   Horscreen();      		      // Настройка интерфейса экрана обхода;
   Look(CB);                          		  // Вывод матрицы на экран;
   for(int l=0;l<8;l++)
     for(int m=0;m<8;m++)
       {
	core *Way; 	Way=CB[l][m].adrs(); // Взятие адреса тек. элемента;
	Way->i=0;
	Way->j=0;           		  // Обнуление всех значений ячейки;
	Way->z=0;
	Way->f=0;
	if(reg){
	gotoxy(59+2*m,l+6); cout<<"."; gotoxy(59+2*m,13-l);}  // Экранизация;
       }
 }

//-------------------------- Проверка ручного ввода ------------------------
void parsing(cell CB[S][S])
 {
  int key=0;// Ключ успешного выхода из цикла ручного ввода следующего хода;
  int oldi, oldj;                        // Хранилище предыдущего положения;
  oldi=(int)i; oldj=(int)j;              	  // Инициализация Хранилищ;
  do{
      coordViz();
     if(!CB[skyline][vertical].cors())
      {
       if((skyline==(oldi-2))&&((oldj+1)==vertical)) key=1;

       if((skyline==(oldi-1))&&((oldj+2)==vertical)) key=1;

       if((skyline==(oldi+1))&&((oldj+2)==vertical)) key=1;

       if((skyline==(oldi+2))&&((oldj+1)==vertical)) key=1;

       if((skyline==(oldi+2))&&((oldj-1)==vertical)) key=1;

       if((skyline==(oldi+1))&&((oldj-2)==vertical)) key=1;

       if((skyline==(oldi-1))&&((oldj-2)==vertical)) key=1;

       if((skyline==(oldi-2))&&((oldj-1)==vertical)) key=1;
      }
   }while(!key);
   CB[skyline][vertical].change(oldi,oldj,0); 	// Сохранеие адреса предка;
 }

//---------------------- Проверка выполнения задания ------------------------

int assay(cell CB[S][S])
 {
  PrintS(22,22,8,1,1);                            // Сообщение о работе ф-ии;

  int Z=1;                           // Переменая для обозначения результата.
  for(int i=0; i<S; i++)                   	      // Внешний цикл вывода.
    for(int j=0; j<S; j++)                 	   // Внутренний цикл вывода.
       if(!(CB[i][j].cors())) Z=0;	    	// Возврат нулевого значения.
  if(Z) { return 10;}
  else return 3;
 }

//------------------------ Выбор следующей позиции --------------------------
int choice(cell CB[S][S])
 {
  PrintS(22,22,9,1,1);                            // Сообщение о работе ф-ии;

  int min=8;		      // Минимальное количество допустимых переходов.
  int im=i, jm=j;            		       // Адрес допустимого перехода.
  int key=0;                  	  // Флаг записи адреса допустимого перехода.
  int start, end;                  	 // Обозначение Начала и Конца цикла;
  if(sign>0) { start=0; end=9;}      			 // Обход по часовой;
  else {start=9; end=0;}                             // Обход против часовой;
  for( ; start!=end; start+=sign)
   {
    switch(start){
	      case 0: PrintS(58,17,10,0,1); continue;// Сообщение о направлении;
	      case 1:
    if(i>1)
     if(j<7)
      if(!CB[i-2][j+1].cors()) { storage(CB,min,key,im,jm,i-2,j+1); }
    continue;                              // Хранение приоритетной позиции;
	      case 2:
    if(i>0)
     if(j<6)
      if(!CB[i-1][j+2].cors()) {storage(CB,min,key,im,jm,i-1,j+2);}
    continue;                              // Хранение приоритетной позиции;
	      case 3:
    if(i<7)
     if(j<6)
      if(!CB[i+1][j+2].cors()) {storage(CB,min,key,im,jm,i+1,j+2);}
    continue;                              // Хранение приоритетной позиции;
	      case 4:
    if(i<6)
     if(j<7)
      if(!CB[i+2][j+1].cors()) {storage(CB,min,key,im,jm,i+2,j+1);}
    continue;                              // Хранение приоритетной позиции;
	      case 5:
    if(i<6)
     if(j>0)
      if(!CB[i+2][j-1].cors()) {storage(CB,min,key,im,jm,i+2,j-1);}
    continue;                              // Хранение приоритетной позиции;
	      case 6:
    if(i<7)
     if(j>1)
      if(!CB[i+1][j-2].cors()) {storage(CB,min,key,im,jm,i+1,j-2);}
    continue;                              // Хранение приоритетной позиции;
	      case 7:
    if(i>0)
     if(j>1)
      if(!CB[i-1][j-2].cors()) {storage(CB,min,key,im,jm,i-1,j-2);}
    continue;                              // Хранение приоритетной позиции;
	      case 8:
    if(i>1)
     if(j>0)
      if(!CB[i-2][j-1].cors()) {storage(CB,min,key,im,jm,i-2,j-1);}
    continue;                              // Хранение приоритетной позиции;
	      case 9: PrintS(58,17,11,0,1); continue;// Сообщение о направлении;
	      default: Start(b); gotoxy(25,15); cout<<"Такого не может быть";
    }
   }
  if(!key)              			      // Если попал в тупик!
   {

			clrscr();
    gotoxy(30,10); printf("%s", "Кажись заблудились...");	delay(1000);
    if(reg&&!VIZ)
    {
     Horscreen();  		       // Настройка итерфейса экрана обхода;
     Look(CB);                           	  // Вывод матрици на экран;
     outputONS(skyline, vertical);             	     // Вывод точки отсчета;
    }
    else     Viz(CB);
    return 4;                                    // Выход на следдующий шаг;
   }
  if(reg)              // Автоматический режим перехода на приоритетный ход;
  {
   CB[im][jm].change(i,j,0);                    // Сохранение адреса предка;
   i=(abc)im;  				    // Переназначение точки отсчета.
   j=(abc)jm;
   gotoxy(59+2*j,13-i);					delay(10);
  }
  else
  {
  gotoxy(jm*7+15,(7-im)*5+7); cout << "ЖМИ";
  gotoxy(jm*7+14,(7-im)*5+9); cout << "СЮДА!";
  parsing(CB);
  }   			  // Ручной режим выбора переменной;
  return 0;                                      // Выход на следдующий шаг;
}
//--------------------- Хранение приоритетной позиции -----------------------
void storage(cell CB[S][S],int &min, int &key, int &im, int &jm, int id, int jd)
 {
  PrintS(22,22,13,1,1);                           // Сообщение о работе ф-ии;

  if(scan(CB, id, jd, min))          	      // Подсчет доступных переходов;
   {im=id; jm=jd; key=1;}   // Хранение адреса позиции и фиксация результата;
  else if(!key)      // В случае отсутствия приоритета и фиксации результата;
	{im=id; jm=jd; key=1;}//Хранение адреса первого допустимого перехода
						   //  и фиксация результата;
  PrintD(im,jm,id,jd);         	      // Вывод данных о координатах на экран;
  if(reg)gotoxy(59+2*j,13-i);				  //	delay(100);
 }
//----------------------- Поиск минимального соседа -------------------------
int scan(cell CB[S][S], int id, int jd, int &min)
{
 PrintS(22,22,14,1,1);                            // Сообщение о работе ф-ии;
 core *Way;	Way=CB[i][j].adrs();   	  // Адрес ячейки текущего положения;
 int temp=8;     			     // Подсчет допустимых переходов;
  if((id>1)&&(jd<7)) temp-=CB[id-2][jd+1].cors();	else temp--;
  if((id>0)&&(jd<6)) temp-=CB[id-1][jd+2].cors();	else temp--;
  if((id<7)&&(jd<6)) temp-=CB[id+1][jd+2].cors();	else temp--;
  if((id<6)&&(jd<7)) temp-=CB[id+2][jd+1].cors();	else temp--;
  if((id<6)&&(jd>0)) temp-=CB[id+2][jd-1].cors();	else temp--;
  if((id<7)&&(jd>1)) temp-=CB[id+1][jd-2].cors();	else temp--;
  if((id>0)&&(jd>1)) temp-=CB[id-1][jd-2].cors();	else temp--;
  if((id>1)&&(jd>0)) temp-=CB[id-2][jd-1].cors();	else temp--;
 if(reg){
  gotoxy(16,12); cout<<temp; gotoxy(59+2*jd,13-id); cout<<"*";
  gotoxy(59+2*jd,13-id);					  //	delay(300);
  }
 else Pr_Zw(jd*7+12,(7-id)*5+5,7,5,0xf,0xC,0);
 if(temp&&(temp==min))           // Сравнение количества доступных переходов;
  if(!bk){Way->f=1;}  	    		    // Уcтановка флага вариативности;
  else{Way->f=0; bk=0;}                        // Снятие флага вариативности;
 if(temp<min)            // Обнаружение меньшего кол-ва допустимых переходов;
  {
   min=temp;               // Презапись меньшего кол-ва допустимых переходов;
   Way->f=0;                    	       // Снятие флага вариативности;
   if(reg){
   gotoxy(18,14); cout<<min;}          		  // Вывод минимума на экран;
   return 1;                                     // Переход к слеующему шагу;
  }
 else return 0;
}
//------------------------- Возврат к развилке ------------------------------
int back(cell CB[S][S], int &cho)
 {
  PrintS(22,22,15,1,1);                           // Сообщение о работе ф-ии;
  core *Way; Way=CB[i][j].adrs();       // Взятие адреса текуущего положения;
  cho--;                                 // Откат количества пройденых шагов;
  if(reg&&!VIZ)
   {
    gotoxy(47,16); printf("%4d",cho);    // Вывод количества пройденых шагов;
    Progress(15,24,64,cho);                	 // Вывод прогресса операции;
    char J = IvC(j);		gotoxy(47,10); cout<<J<<"  "<<i;
			    // Вывод координаты текущего положнения на экран;
    gotoxy(59+2*j,13-i);
   }			 				    delay(1000);
  if(!(Way->f))    			   // Поиск ближайшей метки развилки;
   {
     Way->z=0; 				            // Обнуление текущего значения;
     if(reg&&!VIZ)cout<<Way->z;
     else{Viz(CB); gotoxy(32,2); cout<< "Откат изменений...";
     Progress(11,50,64,cho);}
     i=(abc)Way->i;                          // Переход к предыдущей позиции;
     j=(abc)Way->j;
     return 4;
   }
  else
   {
    sign=-sign;                            	 // Смена направления обхода;
    Way->f=0;                                   	  // Зануление флага;
    bk=1;                                       // Отметка о занулении флага;
    return 0;
   }
 }

//--------------------------- Грамматный выход ------------------------------
void Stop(int N)
 {
  PrintS(22,22,16,1,1);                           // Сообщение о работе ф-ии;
   switch (N){
	     case  0: 	   /*	clrscr();
		gotoxy(35,10); cout<<"ИииииииииХааа!!!";*/ delay(1000); return;
	     default: 		clrscr();
		gotoxy(40,10); cout<<"Упс...";           delay(1000); return;
	     }
 }
//***************************************************************************