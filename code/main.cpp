#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <iomanip>

using namespace std;

#define HEIGHT 50
#define LENGTH 100

struct _score{
            int score;
            char name[15];
        }TopScoreOne[11], TopScoreTwo[11], _aux;

void tableSet(char mat[HEIGHT][LENGTH]);
void displayTable(char mat[HEIGHT][LENGTH], int score);
void mainMenu();
void displayMenu();
void displayGameOver(_score TopScore[], int score, int number);
void displayScoreTable(_score TopScoreOne[], int score, int number);
void checkScore(_score TopScore[11], int number);
void updateScore(_score TopScore[11], int number);
void clearscreen();

int main()
{
    int score;
    /*
    //Cateva comenzi care ma ajuta sa verific functiile de afisare
    char mat[HEIGHT][LENGTH];

    displayMenu();
    cin>>score;
    tableSet(mat);

    for(int i=1; i<10; i++)
    {
        mat[12][i]='*';
        displayTable(mat,score);
    }

    displayGameOver(TopScoreOne,score,1);
    */
    return 0;
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
void tableSet(char mat[HEIGHT][LENGTH])
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<LENGTH;j++)

           if (i == 0 || j == 0 || i == HEIGHT - 1 || j == LENGTH  )
                mat[i][j]='*';
            else
                mat[i][j]=' ';
    }

}

void displayTable(char mat[HEIGHT][LENGTH], int score)
{
    clearscreen();
    cout<<endl;
    for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j <= LENGTH; j++)
			if (i == 0 || j == 0 || i == HEIGHT - 1 || j == LENGTH || mat[i][j] != ' ')
			{

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 115);
				cout << ' ';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
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
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<"     *****      *     *       * ******       ****  *       * ***** ****    "<<endl;
    cout<<"    *          * *    * *   * * *           *    *  *     *  *     *   *   "<<endl;
    cout<<"    *  ****   *   *   *  * *  * *****       *    *   *   *   ****  ****    "<<endl;
    cout<<"    *  *  *  *******  *   *   * *           *    *    * *    *     * *     "<<endl;
    cout<<"     *****  *       * *       * ******       ****      *     ***** *   *   "<<endl<<endl;
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
            updateScore(TopScore,number);

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
