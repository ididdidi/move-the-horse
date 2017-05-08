// Pogram for plotting the graph of a function!!!
// яЁюуЁрььр фы  яюёЄЁюхэш  уЁрЇшър ЇєэъЎшш
//--------------------------------------------------------------------------
# include "HorsePRT.h"     // Стандартные библиотеки и прототиппы функций;
# include "HorseCTR.cpp"    	     	    // Функции управления програмой;
# include "HorseRND.cpp"                        // Методы и базовые функции;
# include "HorseOUT.cpp"           // Диалоговые функции, внешний интерфейс;
# include "HorseVIZ.cpp"           	   // Визуализаация шахматного поля;
# include "HorseWRT.cpp"           	   	 // Запись траектори в файл;
# include "HorseGPR.cpp"
//--------------------------------------------------------------------------
int main()
{
				Start(a); // Приветствие и настройка экрана;
     int uu; char ss;                      //     Для кодов нажатой клавиши.
     cell CB[S][S];           // СОЗДАНИЕ ОБЪЕКТА

  for(;;) {
			  Menu();  //          Выдача на экран меню.
			  uu = klaw(ss);   //              Опрос клавиатуры.
	 if(uu) {
	   switch (ss) {
	     case  68:   Exit();  	    return 0; //      F10   Останов.
	     case  59:   Help();	    continue; //      F1       Help.
	     case  60:   manual(CB);	    continue; //      F2     Ручной.
   	     case  61:   semiavto(CB);	    continue; //      F3 ПолуАвтомат.
	     case  62:   avto(CB);	    continue; //      F4    Автомат.
	     case  63:   PrintT(CB);	    continue; //      F5   Просмотр.
	     case  64:   Write(CB);	    continue; //      F6     Запись.
	     case  65:   stupid(CB);        continue;
	      default:  Stohas(3,200);      continue; //  Звуковое сообщение
						      //   о нажатии неиспо-
						      //  льзуемой управ.кл.
		       }
		}
       switch (ss) {
	 case 13:                   ; continue;    //         Enter - пусто.
	      default: Stohas(4,150);   continue;  // Звук.сооб. о неисполь-
						   // льзуемой символ. клав.
		   }
	}
}