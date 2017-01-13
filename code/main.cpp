#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <iomanip>

using namespace std;

#define HEIGHT 30
#define LENGTH 50

struct _score{
            int score;
            char name[15];
        }TopScoreOne[11], TopScoreTwo[11], _aux;

bool gameOver;
int x,y, fruitX, fruitY, puncteBonus;
enum eDirecton {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
int tailX[100], tailY[100];
int nTail;
int speedyX, speedyY, lessX, lessY, pointsX, pointsY, slowlyX, slowlyY;
char mat[HEIGHT][LENGTH];

void ShowConsoleCursor(bool showFlag);
void setup();
void tableInit(char mat[HEIGHT][LENGTH]);
void tableSet(char mat[HEIGHT][LENGTH]);
void displayTable(char mat[HEIGHT][LENGTH], int score);
void mainMenu(char mat[HEIGHT][LENGTH]);
void displayMenu();
void displayGameOver(_score TopScore[], int score, int number);
void displayScoreTable(_score TopScoreOne[], int score, int number);
void checkScore(_score TopScore[11], int number);
void updateScore(_score TopScore[11], int number);
void clearscreen();
void throwFood(int & x, int & y);
void input();
void logic(int &score);
void start(char mat[HEIGHT][LENGTH], int &score, int number);
void pause();
void powerups(int puncteBonus);
void hitsBonus(int &score);
void displayPause();
void resetBonus(int &x, int & y);
void resetScore(_score TopScore[], int number);
void displayOptions();
void displayScore();
void coutScore(_score TopScore[11]);
void displayControls();

int main()
{
    ShowConsoleCursor(false);
	mainMenu(mat);
    return 0;
}

void mainMenu(char mat[HEIGHT][LENGTH])
{

	setup();
	displayMenu();
	char index;
	int score = 0;
	tableInit(mat);

_start:
	cin >> index;
	if (index == '1')
		start(mat, score, 1); //0-score , 1-modul de joc(single player)
    else
        if(index== '3')
            displayOptions();
    else
        if(index == '4')
            goto _exit;
	else
		goto _start;

    _exit:
        return;
}
void start(char mat[HEIGHT][LENGTH], int &score, int number)
{

    nTail=0;
    system("cls");
    gameOver=false;
    while(gameOver==0)
    {
        tableSet(mat);
        displayTable(mat,score);
        input();
        logic(score);

    }
    if(number==1)
        displayGameOver(TopScoreOne, score, number);
        else
        displayGameOver(TopScoreTwo, score,number );



}

void displayScore()
{

        system("cls");
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
    cout<<"                                                 "<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout<<""<<endl<<endl;
    cout<<"                     Score    "<<endl<<endl;
    cout<<"                  1. Single player score  "<<endl<<endl;
    cout<<"                  2. Player vs. CPU score    "<<endl<<endl;
    cout<<"                  3. Reset single player score   "<<endl<<endl;
    cout<<"                  4. Reset Vs. mode score     "<<endl<<endl;
    cout<<"                  5. Go back     "<<endl<<endl;
     cout<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
    cout<<"                                                 "<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    up:
    char c;
    cin>>c;

    if(c=='1')
        {
            system("cls");
            checkScore(TopScoreOne,1);
            coutScore(TopScoreOne);
            cout<<endl<<"\t Press any key to go back ... ";
            if(_getch())
                displayScore();

        }
    else
        if(c=='2')
        {
            system("cls");
            checkScore(TopScoreTwo,2);
            coutScore(TopScoreTwo);
             cout<<endl<<"\t Press any key to go back ... ";
            if(_getch())
                displayScore();
        }
     else
        if(c=='3')
            {
                 resetScore(TopScoreOne,1);

                system("cls");
                cout<<endl<<"\t Done!"<<endl;
                 cout<<endl<<"\t Press any key to go back ... ";
                 if(_getch())
                    displayScore();

            }
     else
        if(c=='4')
        {
            resetScore(TopScoreTwo,2);
             system("cls");
              cout<<endl<<"\t Done!"<<endl;
               cout<<endl<<"\t Press any key to go back ... ";
                 if(_getch())
                    displayScore();
        }
    else
        if(c=='5')
            displayOptions();
    else
        goto up;
}

void displayControls()
{
    char sel;
    system("cls");
    while(true)
    {
    cout<<" ----------------------------------------------"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                     w - up                   |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|            a - left        s - right         |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                    d - down                  |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<"|                    p - Pause                 |"<<endl;
    cout<<"|                                              |"<<endl;
    cout<<" ---------------------------------------------- "<<endl<<endl<<endl;
    cout<<"1. Go back  ";
    cin>>sel;
    if(sel=='1')
        displayOptions();
    else system("cls");
    }
}

void displayOptions()
{
        system("cls");
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
    cout<<"                                                 "<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout<<""<<endl<<endl;
    cout<<"                     Options    "<<endl<<endl;
    cout<<"                  1. Score  "<<endl<<endl;
    cout<<"                  2. Controls    "<<endl<<endl;
    cout<<"                  3. Legend   "<<endl<<endl;
    cout<<"                  4. Go back     "<<endl<<endl;
     cout<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
    cout<<"                                                 "<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    up:
    char c;
    cin>>c;
    if(c=='1')
        displayScore();
    else
        if(c=='4')
            mainMenu(mat);
    else
        if(c=='2')
            displayControls();
    else
        goto up;

}

void throwFood(int &x, int &y)
{
        start:
            x=rand()%(LENGTH-1)+1;
            y=rand()%(HEIGHT-2)+1;

         for(int i = 0; i < nTail; i++)
                    if(tailX[i] == x && tailY[i] == y)
                        goto start;

}

void resetBonus(int & x, int & y)
{
    x=NULL;
    y=NULL;
}

void setup()
{
    gameOver= false;
    dir=STOP;
    resetBonus(speedyX,speedyY);
    resetBonus(slowlyX,slowlyY);
    resetBonus(pointsX,pointsY);
    resetBonus(lessX,lessY);
    x=LENGTH/2;
    y=HEIGHT/2;
    throwFood(fruitX,fruitY);
    puncteBonus=0;
}

void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}
void tableInit(char mat[HEIGHT][LENGTH])
{
    for(int i=0;i<HEIGHT;i++)

        for(int j=0;j<LENGTH;j++)
            if (i == 0 || j == 0 || i == HEIGHT - 1 || j == LENGTH  )
                mat[i][j]='*';
            else
                mat[i][j]=' ';
}
void tableSet(char mat[HEIGHT][LENGTH])
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<LENGTH;j++)

           {
            if(i==y && j==x)
                mat[i][j]='0';
            else
            if (i== fruitY && j==fruitX)
                mat[i][j]='F';
            else
            if(i==speedyY && j==speedyX)
                mat[i][j]='S';
            else
            if(i==lessY && j==lessX)
                mat[i][j]='L';
            else
            if(i==pointsY && j==pointsX)
                mat[i][j]='P';
            else
            {
                bool print=false;
                for(int k=0; k<nTail; k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        mat[i][j]='o';
                        print=true;
                    }
                }
            if(print!=true)
                mat[i][j]=' ';
            }
           }

    }


}


void displayTable(char mat[HEIGHT][LENGTH], int score)
{
	clearscreen();


	cout << endl;
	cout << "\t Score: " << score << endl;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j <= LENGTH; j++)
			if (i == 0 || j == 0 || i == HEIGHT - 1 || j == LENGTH)
			{
				if (j == 0)
					cout << "       ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 115);
				cout << ' ';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
				if (mat[i][j] == 'o' || mat[i][j] == '0')
				{

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					if (mat[i][j] == '0')
						cout << char(178);
					else
						cout << char(176);
					//cout << ' ';
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
				else
					if (mat[i][j] == 'F')
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
						cout << char(254);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
                else
					if (mat[i][j] == 'S' || mat[i][j]== 'P' || mat[i][j]=='L')
					{
					    int num=rand()%5+10;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
						cout << '?';
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}

					else
						cout << mat[i][j];
		cout << endl;
	}

}

void displayMenu()
{
    system("cls");
    cout<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
    cout<<"                                                 "<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout<<endl;
    cout<<"     ******   *     *      *     *  *  *****     "<<endl;
    cout<<"    *         * *   *     * *    * *   *         "<<endl;
    cout<<"     ******   *  *  *    *   *   **    ****      "<<endl;
    cout<<"           *  *   * *   *******  * *   *         "<<endl;
    cout<<"     ******   *     *  *       * *  *  *****     "<<endl<<endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout<<""<<endl<<endl;
    cout<<"                     M E N U    "<<endl<<endl;
    cout<<"                  1. Singel player  "<<endl<<endl;
    cout<<"                  2. Player vs. CPU    "<<endl<<endl;
    cout<<"                  3. Options    "<<endl<<endl;
    cout<<"                  4. Exit     "<<endl<<endl;
     cout<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
    cout<<"                                                 "<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}


void displayGameOver(_score TopScore[], int score, int number)
{

    //system("cls");
    for (int i=0; i<HEIGHT/2+3; i++)
        cout << "\x1b[A";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout<<"  *****      *     *       * ******     ****  *       * ***** ****    "<<endl;
    cout<<" *          * *    * *   * * *         *    *  *     *  *     *   *   "<<endl;
    cout<<" *  ****   *   *   *  * *  * *****     *    *   *   *   ****  ****    "<<endl;
    cout<<" *  *  *  *******  *   *   * *         *    *    * *    *     * *     "<<endl;
    cout<<"  *****  *       * *       * ******     ****      *     ***** *   *   "<<endl<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout<<endl;
    Sleep(3000);
    system("cls");
    displayScoreTable(TopScore,score,number);

}


void displayScoreTable(_score TopScore[], int score, int number)
{
    checkScore(TopScore,number);
    int i, ok=0;
    if(score > TopScore[10].score)
    {
        TopScore[10].score=score;
        cout<<"\t Enter your name: "<<endl;
        cout<<"Your name: ";
        cin.get();
        cin.getline(TopScore[10].name,14);

        cout<<endl;

        for( i=9; i>=1 && ok==0; i--)
            if(TopScore[i+1].score > TopScore[i].score)
            {
                _aux=TopScore[i];
                TopScore[i]=TopScore[i+1];
                TopScore[i+1]=_aux;
            }
            else
                ok=i;

        ok++;
        if(ok==1)
            cout<<"Good game, this is the best score!";
        else
            if(ok==2)
                cout<<"Well played, this is the second best score!";
        else
            if(ok==3)
                cout<<"Good job, this is the third best score!";
        else
            cout<<"Nice, this is "<<ok<<"-th the best score";


    }
    else
        cout<<"You are not in top 10!";
    Sleep(1500);
        //system("cls");
        cout<<endl<<endl<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 124);
        cout<<"   Score    Name                   ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout<<endl<<endl;
        coutScore(TopScore);
            updateScore(TopScore,number);
            Sleep(1000);
            cout<<endl<<"Press any key...";
            Sleep(500);
            if(_getch())
                mainMenu(mat);

}
void coutScore(_score TopScore[10])
{
      for(int i=1; i<=10; i++)
            {
                if(i<10)
                {
                if(TopScore[i].score < 10)
                     cout<<i<<'.'<<"  "<<TopScore[i].score<<"       "<<TopScore[i].name<<endl;
                else
                    if(TopScore[i].score < 100)
                        cout<<i<<'.'<<"  "<<TopScore[i].score<<"      "<<TopScore[i].name<<endl;
                else
                    if(TopScore[i].score < 1000)
                         cout<<i<<'.'<<"  "<<TopScore[i].score<<"     "<<TopScore[i].name<<endl;
                else
                     cout<<i<<'.'<<"  "<<TopScore[i].score<<"    "<<TopScore[i].name<<endl;
                }

                    else

                {

                if(TopScore[i].score < 10)
                     cout<<i<<'.'<<" "<<TopScore[i].score<<"       "<<TopScore[i].name<<endl;
                else
                    if(TopScore[i].score < 100)
                        cout<<i<<'.'<<" "<<TopScore[i].score<<"      "<<TopScore[i].name<<endl;
                else
                    if(TopScore[i].score < 1000)
                         cout<<i<<'.'<<" "<<TopScore[i].score<<"     "<<TopScore[i].name<<endl;
                else
                     cout<<i<<'.'<<" "<<TopScore[i].score<<"    "<<TopScore[i].name<<endl;

                }
            }
}

void checkScore( _score TopScore[], int number)
{
    if(number == 1) //caz in care verificam scorurile de la Singleplayer mode
    {
        ifstream fin("TopScoreSinglePlayer");

        for(int i=1; i<11; i++)
        {
            fin>>TopScore[i].score;
            fin.get();
            fin.get(TopScore[i].name,14);
            fin.get();
        }
        fin.close();
    }
    else
    if(number == 2) // Top score la player vs CPU
    {
        ifstream fin("TopScoreVsMode");

        for(int i=1; i<11; i++)
        {
            fin>>TopScore[i].score;
            fin.get();
            fin.get(TopScore[i].name,14);
            fin.get();
        }
        fin.close();
    }

}

void updateScore(_score TopScore[], int number)
{
    if(number == 1)
    {
         ofstream fout("TopScoreSinglePlayer");
        for(int i=1 ; i<11; i++)
        {
            fout<<TopScore[i].score<<endl;
            fout<<TopScore[i].name<<endl;
        }
        fout.close();
    }
    else
         if(number == 2)
    {
         ofstream fout("TopScoreVsMode");
        for(int i=1 ; i<11; i++)
        {
            fout<<TopScore[i].score<<endl;
            fout<<TopScore[i].name<<endl;
        }
        fout.close();
    }
}

void resetScore(_score TopScore[], int number)
{
    if(number == 1)
    {
         ofstream fout("TopScoreSinglePlayer");
        for(int i=1 ; i<11; i++)
        {
            fout<<0<<endl;
            fout<<'-'<<endl;
        }
        fout.close();
    }
    else
         if(number == 2)
    {
         ofstream fout("TopScoreVsMode");
        for(int i=1 ; i<11; i++)
        {
            fout<<0<<endl;
            fout<<'-'<<endl;
        }
        fout.close();
    }
}


void input()
{
    if(_kbhit())// daca ceva e apasat- conio.h
    {
        switch(_getch())// se refera la tasta apasata- conio.h
        {
        case 'a':
           {
            Sleep(0);
           if(dir!=RIGHT)
            dir=LEFT;
            break;
           }
        case 'd':
            {
            Sleep(0);
            if(dir!=LEFT)
            dir=RIGHT;
            break;
            }
        case 'w':
            {
            Sleep(50);
            if(dir!=DOWN)
            dir=UP;
            break;
            }
        case 's':
            {
            Sleep(50);
            if(dir!=UP)
            dir=DOWN;
            break;
            }
        case 'p':
            {
               pause();
                break;
            }


        }
    }
}
void pause() //pauses game
{


    cout<<""<<endl<<endl;
    cout<<"Game paused. Press 'p' if you want to continue";
    displayPause();
    ooo:
            if( _getch()== 'p')
                       {
                           system("cls");
                       }
        else goto ooo;

    }



void logic(int &score)
{
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X, prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1; i<nTail; i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }


	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
	{
		Sleep(18);
		y--;
	}
	break;
	case DOWN:
	{
		y++;
		Sleep(18);
	}
	break;
	default:
		break;
	}
    if(x>LENGTH-1 || x<=0 || y>HEIGHT-2
        || y<=0)
        gameOver=true;
    for(int i=0; i<nTail; i++)
        if(tailX[i]==x && tailY[i]==y)
            gameOver=true;
    if(x==fruitX && y==fruitY)
    {
        nTail++;
        score++;
        puncteBonus++;
        throwFood(fruitX,fruitY);
        powerups(puncteBonus);
    }
    else
        hitsBonus(score);

}

void hitsBonus(int &score)
{
    if(x==pointsX && y==pointsY)
    {
        score+=2;
        pointsX=NULL;
        pointsY=NULL;

    }
    else
    if(x==speedyX && y==speedyY)
    {
        Sleep(0);
        speedyX=NULL;
        speedyY=NULL;
    }
    else
    if(x==slowlyX && y==slowlyY)
    {
        Sleep(5510);
        slowlyX=NULL;
        slowlyY=NULL;

    }
    else
    if(x==lessX && y==lessY)
    {
        tailX[nTail]=NULL;
        tailY[nTail]=NULL;
        nTail--;
        lessX=NULL;
        lessY=NULL;
    }
}
void powerups(int puncteBonus)
{
    if(puncteBonus%5==0 && puncteBonus%2!=0)
        {
            throwFood(speedyX, speedyY);
           //Sleep(0);
        }


    else
    if(puncteBonus%5==0 && puncteBonus%2==0)
        {
            throwFood(slowlyX, slowlyY);
            //Sleep(10);
        }


    else
    if(puncteBonus%6==0)
    {
        throwFood(pointsX, pointsY);
        //score+=2;
    }
    else
    if(puncteBonus%8==0)
    {
        throwFood(lessX, lessY);
        // lesstail
    }

}
void ShowConsoleCursor(bool showFlag)//face underscor-ul invizibil
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


void displayPause()
{
	for (int i = 0; i<HEIGHT / 2 + 6; i++)
		cout << "\x1b[A";
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "\t \t****     *     *    *  *****  ***** " << endl;
	cout << "\t \t*   *   * *    *    *  *      *     " << endl;
	cout << "\t \t****   *   *   *    *  *****  ****  " << endl;
	cout << "\t \t*     *******  *    *      *  *     " << endl;
	cout << "\t \t*    *       * ******  *****  ***** " << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << endl;
}
