//------------------------- СТАНДАРТНЫЕ БИБЛИОТЕКИ -------------------------
# include <conio.h>
# include <iostream.h>
# include <dos.h>
# include <stdlib.h>
# include <stdio.h>
# include <iomanip.h>
# include <string.h>

//---------------------- КОНСТАНТЫ ПЕРЕМЕННЫЕ И КЛАССЫ ----------------------
# define S 	    8	       			   // Размер шахматного поля.

//--------------------- Перечисление адресов столбцов -----------------------
enum abc{ a, b, c, d, e, f, g, h, er=111} j=a, i=a;    	 // Координаты точки.
int vertical=0, skyline=0;   			     // Начальные координаты.
int sign=1, bk=0;                            // Указатель направления обхода;
int brk=0;                                   			   // Тормоз;
int reg=0;                        // Пререключатель режима Ручной(0)/Авто(1);
int cho=0;           			      // Количество сделаных ходов;
int regSTR=0;
int VIZ=0;
//------------------------- Базовые структуры данных ------------------------
struct core                        	 // Структура основной ячейки данных;
 {
  unsigned i:3;    		          // Координата предыдущего элемента.
  unsigned j:3;         		  // Координата предыдущего элемента.
  unsigned z:1;         	     	        // Текущее значение элемента.
  unsigned f:4;                         	 // Метка о наличии развилки;
  unsigned n:6;                              		       // Номер хода;
 };
//---------------------------- ПРОТОТИПЫ КЛАССОВ --------------------------
class cell                               // Ячейка с данными
 {
		  core status;            	   // Переменная типа core;
	public:
		  cell();                           // Базовый конструктор;
		  operator=(int z);             // Перегрузка присваивания;
		  int cors();        // Возврат значения текущего элемента;
		  core *adrs();        // Возврат адоеса текущего элемента;
		  void change(int i, int j, int z);    // изменение данных;
		  friend  ostream &operator << (ostream &stream, cell obg);
 };
//============================ ПРОТОТИПЫ ФУНКЦИЙ ===========================

// - - - - - - - - - - - - - - -  HorseCTR.cpp   - - - - - - - - - - - - - -
void Start(abc q);                 //       Стартовые настройки и сообщения.
void Help();
void semiavto(cell CB[S][S]);      // 		   Полуавтоматический режим.
void avto(cell CB[S][S]);          //                  Автоматический режим.
 int klaw(char &ss);               //                      Опрос клавиатуры.
void Stohas(int n, int dd=9);      // Звуковое сопровождение вывода матрицы.
void Pisk(int n);                  //                        Звуковая метка.
void Exit();                       //           Завершение работы программы.

// - - - - - - - - - - - - - - -  HorseRND.cpp   - - - - - - - - - - - - - -

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

// - - - - - - - - - - - - - - -  HorseOUT.cpp   - - - - - - - - - - - - - -

void PrintS(int x, int y, int n, int cl=0, int p=0); // Универ. вывод строк;
void Menu();              	   //                   Вывод меню на экран.
void Horscreen();                                	// Настройки экрана.
void Look(cell CB[S][S]);      		       	  // Вывод матрицы на экран.
void outputONS(int i, int j);    	       // Вывод начальных координат;
void PrintD(int im, int jm, int id, int jd);       // Вывод данных на экран.
char IvC(abc j); 				 // Интерпритатор в символы.
void coordinates();   				     // Выбор точки отсчета.
abc inptj();                                     // Ввод координаты столбца.
abc inpti();                                      // Ввод координаты строки.
void No_matr();               // Сообщение о том, что матрица ещё не задана.
void PrintT(cell CB[S][S]);            		       // Печать траектоори;
void horse();                      //                        Рисунок лошади.
void Progress(int x, int y, int max, int step); 		// Прогресс;

// - - - - - - - - - - - - - - -  HorseVIZ.cpp   - - - - - - - - - - - - - -
void Viz(cell CB[S][S]);                               // Визуализация поля;
void coordViz();		                     // Выбор точки отсчета;
void Pr_Zw(int,int,int,int,int,int,int nk=0);  // Закрашивание фона прямоуг.
 // на экране в текстовом режиме и задание в нём цвета символов в 0-м кадре.
int get_press(int butt, int& x_pos, int& y_pos);
 //         Обработка клика
		  //  указанной  в   butt  (0 - правой, 1 - левой)   клавиши
		  //  с возвратом 1 в момент нажатия.       Затем, если даже
		  //  же держать, то возвращается 0.   В момент нажатия ука-
		  //  занной клавиши в  &x_pos, &y_pos  заносятся координаты
		  //  расположения мыши на экране.
void outupText(char *name);			// Вывод текста на экран;
// - - - - - - - - - - - - - - -  HorseWRT.cpp   - - - - - - - - - - - - - -
void Write(cell CB[S][S]);     				   // Запись в файл.

// - - - - - - - - - - - - - - -
int choSTP(cell CB[S][S]);
int scanalon(cell CB[S][S], int &im, int &jm);
void metodGPR(cell CB[S][S]);
int prover(int id, int jd);
void storSTP(cell CB[S][S],int &im, int &jm,  int &key, int id, int jd);
int scanSTP(cell CB[S][S], int id, int jd);
int backSTP(cell CB[S][S]);