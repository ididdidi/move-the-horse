//------------------------- ����������� ���������� -------------------------
# include <conio.h>
# include <iostream.h>
# include <dos.h>
# include <stdlib.h>
# include <stdio.h>
# include <iomanip.h>
# include <string.h>

//---------------------- ��������� ���������� � ������ ----------------------
# define S 	    8	       			   // ������ �嬠⭮�� ����.

//--------------------- ����᫥��� ���ᮢ �⮫�殢 -----------------------
enum abc{ a, b, c, d, e, f, g, h, er=111} j=a, i=a;    	 // ���न���� �窨.
int vertical=0, skyline=0;   			     // ��砫�� ���न����.
int sign=1, bk=0;                            // �����⥫� ���ࠢ����� ��室�;
int brk=0;                                   			   // ��ମ�;
int reg=0;                        // ��४���⥫� ०��� ��筮�(0)/���(1);
int cho=0;           			      // ������⢮ ᤥ����� 室��;
int regSTR=0;
int VIZ=0;
//------------------------- ������ �������� ������ ------------------------
struct core                        	 // ������� �᭮���� �祩�� ������;
 {
  unsigned i:3;    		          // ���न��� �।��饣� �����.
  unsigned j:3;         		  // ���न��� �।��饣� �����.
  unsigned z:1;         	     	        // ����饥 ���祭�� �����.
  unsigned f:4;                         	 // ��⪠ � ����稨 ࠧ�����;
  unsigned n:6;                              		       // ����� 室�;
 };
//---------------------------- ��������� ������� --------------------------
class cell                               // �祩�� � ����묨
 {
		  core status;            	   // ��६����� ⨯� core;
	public:
		  cell();                           // ������ ���������;
		  operator=(int z);             // ��ॣ�㧪� ��ᢠ������;
		  int cors();        // ������ ���祭�� ⥪�饣� �����;
		  core *adrs();        // ������ ����� ⥪�饣� �����;
		  void change(int i, int j, int z);    // ��������� ������;
		  friend  ostream &operator << (ostream &stream, cell obg);
 };
//============================ ��������� ������� ===========================

// - - - - - - - - - - - - - - -  HorseCTR.cpp   - - - - - - - - - - - - - -
void Start(abc q);                 //       ���⮢� ����ன�� � ᮮ�饭��.
void Help();
void semiavto(cell CB[S][S]);      // 		   ���㠢⮬���᪨� ०��.
void avto(cell CB[S][S]);          //                  ��⮬���᪨� ०��.
 int klaw(char &ss);               //                      ���� ����������.
void Stohas(int n, int dd=9);      // ��㪮��� ᮯ஢������� �뢮�� ������.
void Pisk(int n);                  //                        ��㪮��� ��⪠.
void Exit();                       //           �����襭�� ࠡ��� �ணࠬ��.

// - - - - - - - - - - - - - - -  HorseRND.cpp   - - - - - - - - - - - - - -

void metodMAN(cell CB[S][S]);          // ���冷� �㭪権 �� ��筮� ��室�.
void method(cell CB[S][S], int step, int cho);// ���冷� �㭪権 �� ��室�.
void zeroing(cell CB[S][S], int &step, int &cho);    // ���㫥��� �� �室�;
void parsing(cell CB[S][S]);          	   // �஢�ઠ ������ ��筮�� �����;
int assay(cell CB[S][S]);		      // �஢�ઠ �믮������ �����.
int choice(cell CB[S][S]);   		         // �롮� ᫥���饩 ����樨.
void storage(cell CB[S][S],int &min, int &key, int &im, int &jm, int id, int jd);
					   // �࠭���� �ਮ��⭮� ����樨.
int scan(cell CB[S][S], int i, int j, int &min);      // ���� �������쭮��.
int back(cell CB[S][S], int &cho);         // ������ �� ������襩 ࠧ�����.
void Stop(int N);                                      // �����襭�� ��室�.

// - - - - - - - - - - - - - - -  HorseOUT.cpp   - - - - - - - - - - - - - -

void PrintS(int x, int y, int n, int cl=0, int p=0); // ������. �뢮� ��ப;
void Menu();              	   //                   �뢮� ���� �� �࠭.
void Horscreen();                                	// ����ன�� �࠭�.
void Look(cell CB[S][S]);      		       	  // �뢮� ������ �� �࠭.
void outputONS(int i, int j);    	       // �뢮� ��砫��� ���न���;
void PrintD(int im, int jm, int id, int jd);       // �뢮� ������ �� �࠭.
char IvC(abc j); 				 // �������� � ᨬ����.
void coordinates();   				     // �롮� �窨 �����.
abc inptj();                                     // ���� ���न���� �⮫��.
abc inpti();                                      // ���� ���न���� ��ப�.
void No_matr();               // ����饭�� � ⮬, �� ����� ��� �� ������.
void PrintT(cell CB[S][S]);            		       // ����� �ࠥ�⮮�;
void horse();                      //                        ���㭮� ��蠤�.
void Progress(int x, int y, int max, int step); 		// �ண���;

// - - - - - - - - - - - - - - -  HorseVIZ.cpp   - - - - - - - - - - - - - -
void Viz(cell CB[S][S]);                               // ���㠫����� ����;
void coordViz();		                     // �롮� �窨 �����;
void Pr_Zw(int,int,int,int,int,int,int nk=0);  // ����訢���� 䮭� ��אַ�.
 // �� �࠭� � ⥪�⮢�� ०��� � ������� � �� 梥� ᨬ����� � 0-� ����.
int get_press(int butt, int& x_pos, int& y_pos);
 //         ��ࠡ�⪠ �����
		  //  㪠������  �   butt  (0 - �ࠢ��, 1 - �����)   ������
		  //  � �����⮬ 1 � ������ ������.       ��⥬, �᫨ ����
		  //  �� ��ঠ��, � �����頥��� 0.   � ������ ������ 㪠-
		  //  ������ ������ �  &x_pos, &y_pos  ��������� ���न����
		  //  �ᯮ������� ��� �� �࠭�.
void outupText(char *name);			// �뢮� ⥪�� �� �࠭;
// - - - - - - - - - - - - - - -  HorseWRT.cpp   - - - - - - - - - - - - - -
void Write(cell CB[S][S]);     				   // ������ � 䠩�.

// - - - - - - - - - - - - - - -
int choSTP(cell CB[S][S]);
int scanalon(cell CB[S][S], int &im, int &jm);
void metodGPR(cell CB[S][S]);
int prover(int id, int jd);
void storSTP(cell CB[S][S],int &im, int &jm,  int &key, int id, int jd);
int scanSTP(cell CB[S][S], int id, int jd);
int backSTP(cell CB[S][S]);