void stupid(cell CB[S][S])
 {
  int uu;                     // Преременная для управления выходом по ESC;
  do{
  metodGPR(CB);
		textattr(0x1A);  	clrscr();
     gotoxy(30,15); cout<<"Для выхода нажмите Esc..."; // Вывод сообщения на экран;
     uu = getch();
    }while(uu!=27);                              		   // Выход по Esc;

 }
//-------------------------------------------------------------------------
void metodGPR(cell CB[S][S])
{
  int step = 0;        			         // Шаг в алгоритме обхода;
  cho=0;           			      // Количество сделаных ходов;
  brk=1;            			   // Установка задержки в единицу;
  regSTR=reg=0;                               // Режим ручного выбора хода;
  VIZ=1;
   Viz(CB);
   zeroing(CB,step,cho);       			   // Тотальноое обнуление;
   Viz(CB);                                // Визуализация шахматного поля;
   coordViz();                                 	    // Выбор точки отсчета;
  for(;;) {
	 switch (step){
	     case  0:  CB[i][j]=1; 		     // Установка в единицу;
		       sign=-sign;  		// Смена направления обхода;
		       core *Way;
		       Way=CB[i][j].adrs(); // Взятие адреса тек. элемента;
		       Way->n=cho;    // Запоминане порядкового номера хода;
					step=1; continue;//Переход к case:1;
	     case  1:  Viz(CB);                            // Вывод матрицы;
		       Progress(11,50,64,cho);  // Вывод прогресса операции;
					step=2; continue;
	     case  2:  step = assay(CB);  	continue;//Проверка выполнения;
	     case  3:  step = choSTP(CB); 	continue;//Выбор следующего;
	     case  4:  backSTP(CB);
		       step = backSTP(CB);  continue; //Откат из тупика;
	     case 10:  Stop(0);			return;//Окончание операции;

	      default:                 step=10; continue; // Окончание по
		   }                                             // дефолту;
	}
}
//------------------------ Выбор следующей позиции --------------------------

int choSTP(cell CB[S][S])
 {

  core *Way;	Way=CB[i][j].adrs();   	  // Адрес ячейки текущего положения;

  int im=i, jm=j;            		       // Адрес допустимого перехода.
  if(!(scanalon(CB,im,jm)))
   {
    Way->f++;
    int cs=Way->f;
    switch(cs){
	      case 1:
    if((i>1)&&(j<7)&&(!CB[i-2][j+1].cors()))
       {
	im=i-2; jm=j+1;		break;
       }
					   // Хранение приоритетной позиции;
	      case 2:
    if((i>0)&&(j<6)&&(!CB[i-1][j+2].cors()))
       {
	im=i-1; jm=j+2;		break;
       }
					   // Хранение приоритетной позиции;
	      case 3:
    if((i<7)&&(j<6)&&(!CB[i+1][j+2].cors()))
       {
	im=i+1; jm=j+2;		break;
       }
					   // Хранение приоритетной позиции;
	      case 4:
    if((i<6)&&(j<7)&&(!CB[i+2][j+1].cors()))
       {
	im=i+2; jm=j+1;		break;
       }
					   // Хранение приоритетной позиции;
	      case 5:
    if((i<6)&&(j>0)&&(!CB[i+2][j-1].cors()))
       {
	im=i+2; jm=j-1;		break;
       }
					   // Хранение приоритетной позиции;
	      case 6:
    if((i<7)&&(j>1)&&(!CB[i+1][j-2].cors()))
       {
	im=i+1; jm=j-2;		break;
       }
					   // Хранение приоритетной позиции;
	      case 7:
    if((i>0)&&(j>1)&&(!CB[i-1][j-2].cors()))
       {
	im=i-1; jm=j-2;		break;
       }
					   // Хранение приоритетной позиции;
	      case 8:
    if((i>1)&&(j>0)&&(!CB[i-2][j-1].cors()))
       {
	im=i-2; jm=j-1;		break;
       }
					   // Хранение приоритетной позиции;
	      default: 		 //	clrscr();     // Если попал в тупик!
//    gotoxy(30,10); printf("%s", "Кажись заблудились...");cout<<Way->f;	delay(1000);
    Viz(CB);
    Way->f=0;
    return 4;				    // Выход на следдующий шаг;
    }
   }
  if(regSTR)              // Автоматический режим перехода на приоритетный ход;
  {
   CB[im][jm].change(i,j,0);                    // Сохранение адреса предка;
   i=(abc)im;  				    // Переназначение точки отсчета.
   j=(abc)jm;
   gotoxy(59+2*j,13-i);					delay(10);
  }
  else   parsing(CB);    		  // Ручной режим выбора переменной;
		       cho++;                   // Инкремент счетчика ходов;
  return 0;                                      // Выход на следдующий шаг;

}
//------------------------ Поиск единично перехода --------------------------
int scanalon(cell CB[S][S], int &im, int &jm)
{
   int key=0;                  	  // Флаг записи адреса допустимого перехода.

 if((i>1)&&(j<7)&&(!CB[i-2][j+1].cors())) { storSTP(CB,im,jm,key,i-2,j+1); }
 if((i>0)&&(j<6)&&(!CB[i-1][j+2].cors())) { storSTP(CB,im,jm,key,i-1,j+2); }
 if((i<7)&&(j<6)&&(!CB[i+1][j+2].cors())) { storSTP(CB,im,jm,key,i+1,j+2); }
 if((i<6)&&(j<7)&&(!CB[i+2][j+1].cors())) { storSTP(CB,im,jm,key,i+2,j+1); }
 if((i<6)&&(j>0)&&(!CB[i+2][j-1].cors())) { storSTP(CB,im,jm,key,i+2,j-1); }
 if((i<7)&&(j>1)&&(!CB[i+1][j-2].cors())) { storSTP(CB,im,jm,key,i+1,j-2); }
 if((i>0)&&(j>1)&&(!CB[i-1][j-2].cors())) { storSTP(CB,im,jm,key,i-1,j-2); }
 if((i>1)&&(j>0)&&(!CB[i-2][j-1].cors())) { storSTP(CB,im,jm,key,i-2,j-1); }

 if(key)
  {
   if(!regSTR)
    {	gotoxy(jm*7+15,(7-im)*5+7); cout << "ЖМИ";
	gotoxy(jm*7+14,(7-im)*5+9); cout << "СЮДА!";
    }
   return 1;
  }
 else		return 0;
}
//--------------------- Хранение приоритетной позиции -----------------------

void storSTP(cell CB[S][S],int &im, int &jm,  int &key, int id, int jd)
 {
  int temp=8;     			     // Подсчет допустимых переходов;
  if((id>1)&&(jd<7)) temp-=CB[id-2][jd+1].cors();	else temp--;
  if((id>0)&&(jd<6)) temp-=CB[id-1][jd+2].cors();	else temp--;
  if((id<7)&&(jd<6)) temp-=CB[id+1][jd+2].cors();	else temp--;
  if((id<6)&&(jd<7)) temp-=CB[id+2][jd+1].cors();	else temp--;
  if((id<6)&&(jd>0)) temp-=CB[id+2][jd-1].cors();	else temp--;
  if((id<7)&&(jd>1)) temp-=CB[id+1][jd-2].cors();	else temp--;
  if((id>0)&&(jd>1)) temp-=CB[id-1][jd-2].cors();	else temp--;
  if((id>1)&&(jd>0)) temp-=CB[id-2][jd-1].cors();	else temp--;
 Pr_Zw(jd*7+12,(7-id)*5+5,7,5,0xf,0xC,0);
/* if(temp<2)            // Обнаружение меньшего кол-ва допустимых переходов;
   {im=id; jm=jd; key=1;}   // Хранение адреса позиции и фиксация результата;
*/ if((id==0&&jd==0)||(id==0&&jd==7)||(id==7&&jd==0)||(id==7&&jd==7))
  {im=id; jm=jd; key=1;}   // Хранение адреса позиции и фиксация результата;
 }

//------------------------- Возврат к развилке ------------------------------
int backSTP(cell CB[S][S])
 {
  core *Way; Way=CB[i][j].adrs();       // Взятие адреса текуущего положения;
  cho--;                                 // Откат количества пройденых шагов;
  Way->z=0; 				      // Обнуление текущего значения;
  Viz(CB); gotoxy(32,2); cout<< "Откат изменений...";
  Progress(11,50,64,cho);         //                      	 delay(1000);
  i=(abc)Way->i;                          // Переход к предыдущей позиции;
  j=(abc)Way->j;
  return 0;
 }

//----------------------- Проверка на вылет из поля -------------------------
int prover(int id, int jd)
 {
  if(id<0 || id>7 || jd<0 || jd>7) return 0;
  else return 1;
 }


//***************************************************************************
