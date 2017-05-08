/*      Файл, содержащий функции записи в файл и чтения из файла.
void Write(char M[K_Strok][K_Stolb], int  st, int  el); //   Запись в файл.
*/
void Write(cell CB[S][S])      // Запись в файл.
{
  int sh=0;
  char name[40];
  abc im=i, jm=j;
  core *Way;
  core BC[65];
		 textattr(0x1A); clrscr();
  gotoxy(20, 2); cout << "Режим вывода траектори в файл";
  gotoxy(25,12); cout << "Инициализация массива...";
  for(int i=64; i>0; i--)
   {
     sh++;
     Way=CB[im][jm].adrs();  		      // Взятие адреса тек. элемента;
     BC[i].i=im; im=(abc)Way->i;
     BC[i].j=jm; jm=(abc)Way->j;
     Progress(15,24,64,sh); 					delay(10);
   }
  gotoxy(20,20); clreol();
  gotoxy(20,12); clreol(); cout << "Имя файла:   ";  cin >> name;

 FILE *fff;

 if((fff=fopen(name, "w+t"))==NULL)
 {
    gotoxy(25,15);   cout << "НЕ МОГУ создать файл "<< name;
    getch();     return;
 }

		       fputs("/* Координаты пройденого пути :   \n\n", fff);
  for(int k=1;k<65;k++)
   {
    fprintf(fff, "  %c\-%d",IvC((abc)BC[k].j), (unsigned int)BC[k].i+1);
    if(k&&!(k%8))
    fputs("\n\n", fff);
   }
		 fputs("\n\n * * * * * * * * * * * * * * * * * * /", fff);
  fclose(fff);

  textattr(0x31); clrscr();
  gotoxy(25,15); cout << "З А П И С Ь   ЗАВЕРШЕНА !!!"; Stohas(5,333);
}

