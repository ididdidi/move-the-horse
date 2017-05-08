//----------------------------- Просмотр  поля -----------------------------
void Viz(cell CB[S][S])
{
		textmode(C4350); textattr(0x70); clrscr();

 int Rx=7, Ry=5;
 //          *(E + Строка * 160 + Позиция    ) = Символ
//          *(E + Строка * 160 + Позиция + 1) = Цвет,Фон
//   Имя  │Левый верх.угол│Длина сторон пр│Коды цветов в прям:│ Номер
// функции│  по X │  по Y │  по X │  по Y │ Символов│  Фона   │ кадра

//void Pr_Zw(int Wlx,int Wly,int Dlx,int Dly,int ZwSim,int ZwFon,int nk)
 Pr_Zw(9,3,62,44,0xf,0);
 for( int i=0; i<8; i++)
  {
   gotoxy(11,i*Ry+10); cout<<8-i;
   gotoxy(i*Rx+19,5); printf("%c",'a'+i);
   for(int j=0; j<8; j++)
   {
    if(CB[i][j].cors())
    {
     core *Way;        Way=CB[i][j].adrs();
     Pr_Zw(j*Rx+12,(7-i)*Ry+5,Rx,Ry,0xf,(j+i)%2? 3 : 0xb ,0);
     gotoxy(j*7+16,(7-i)*5+7); cout << Way->n+1;
     gotoxy(j*7+15,(7-i)*5+9); cout << IvC((abc)Way->j)<<"-"<<(Way->i)+1;
    }
    else Pr_Zw(j*Rx+12,(7-i)*Ry+5,Rx,Ry,0xf,(i+j)%2? 1 : 0xE ,0);



   }
  gotoxy(74,4); cout<<"Режим:";
  Pr_Zw(73,5,5,3,0xA,0xC);
  if(reg||regSTR){ gotoxy(75,7); cout<<"АВТ";}
  else{ gotoxy(75,7); cout<<"РУЧ";}
  }
}
//----------------------------
void coordViz()
 {
  do{

     int XP, YP, ex;
     do{
	ex = get_press(0,XP,YP);
       }while(!ex);

	XP/=8;  YP/=8;

     if(!XP && !YP) break;
     if(XP>72&&XP<78&&YP>4&&YP<8)
      {
       reg=1;
       regSTR=1;
       gotoxy(75,7); cout<<"AВТ";
       break;
      }
     vertical=(XP-12)/7;
     skyline=7-((YP-5)/5);
     j=(abc)vertical;
     i=(abc)skyline;
  }while((skyline>S-1)||(vertical>S-1));
 }

//---------------------------- Вывод  квадратов ----------------------------
//          *(E + Строка * 160 + Позиция    ) = Символ
//          *(E + Строка * 160 + Позиция + 1) = Цвет,Фон
//   Имя  │Левый верх.угол│Длина сторон пр│Коды цветов в прям:│ Номер
// функции│  по X │  по Y │  по X │  по Y │ Символов│  Фона   │ кадра

void Pr_Zw(int Wlx,int Wly,int Dlx,int Dly,int ZwSim,int ZwFon,int nk)

// ВНИМАНИЕ !!! Осторожно с номером кадра !!! Более 1 - нельзя !!!.

{
char huge *E = (char *) 0xb8000000;                //      Адрес видеокадра.
 int j,i;
				  E += nk * 8000;  // Пересчёт на nk-й кадр.

   for(j=0;   j<  Dly;   j++ )
   for(i=0;   i<2*Dlx;   i+=2)

   *((E + 160*(Wly+j) + 2*Wlx) + i+1)= ZwSim + 16*ZwFon;
}
//---------------------------- Обработкка клика ----------------------------
int get_press(int butt, int& x_pos, int& y_pos) //  Обработка события клика,
					// Передача параметров через ССЫЛКИ.
{
			    int x=100, y=100, pr;
	 asm {                                  //     Ассемблерная вставка.
		mov ax,5;
		mov bx,butt;
		int 0x33;
		mov x,cx;
		mov y,dx;
		mov pr,bx;
	     }
			    x_pos = x;
			    y_pos = y;
return(pr ? 1:0);
}
//--------------------------------------------------------------------------
void outupText(char *name)			// Вывод текста на экран;
{
 char buff[80];					// буфер для хранения строки;
 int len=0;					// индекс строки;
 FILE *fff;
						clrscr();
 if((fff=fopen(name, "r+t"))==NULL)
 {
    gotoxy(20,16);   cout << "НЕ МОГУ открыть файл "<< name;
    getch();     return;
 }

 cout << "\n\t      ";
 while(fgetc(fff) != EOF)		// Цикл считывания из файла
  {					// и вывода на экран;
	fscanf(fff, "%s", buff); 	//  Считываем слово

	 len += (strlen(buff)+1);	// посчитаем длину строки;

	if(len<52 && buff[1]!=')')      // Если длина строки не певышает заданную ширину
	  cout << ' ' << buff;	// печатаем
	else                	// иначе
	 {
	  cout << "\n\t       " << buff;     // перенесем на новую строку;
	  len=strlen(buff)+1;
	 }
  }
}
