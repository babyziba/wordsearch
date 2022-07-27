#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

string puzzleMaker(string s1, int len);
void createNew();
void openOld(string file);
class No;
void insert(No *&he, string val);



string puzzleMaker(string s1, int len)
{
    int t = len * 2;
    char word[t];
    int g = s1.length();
    int c = 0,i;
    for (i = 0; i <t; i++)
    {
        if (c < g and i % 2 != 0)
        {
            word[i] = s1[c];
            c++;
        }
        else
        {
            word[i] = 'a' + rand() % 26;
        }
    }
    return word;
}
void createNew()
{
    int n = 0, h = 0,i,t;
    cout << "enter the amount of words you'd like to type:";
    cin >> n;
    string w[n];
    string p[n];
    for (i = 0; i < n; i++)
    {
        cout << "please enter word [" << i + 1 << "]:";
        cin >> w[i];
        t = w[i].length();
        if (t >= h)
        {
            h = t;
        }
    }
    for (i = 0; i < n; i++)
    {
        string t = puzzleMaker(w[i], h);
        p[i] = t;
    }
    cout << "save?(Y/N):";
    char a;
    cin >> a;
    if (a == 'y' || a == 'Y')
    {
        string file;
        cout << "enter the file-name:";
        cin >> file;
        //this saves the data
        fstream puzzleData;
        puzzleData.open(file + ".txt", ios::out); //writes to file
        if (puzzleData.is_open())
        {
            puzzleData << "Puzzles\n";
            for (i = 0; i < n; i++)
            {
                puzzleData << p[i] << "\n";
            }
            puzzleData << "Solutions\n";
            for (i = 0; i < n; i++)
            {
                puzzleData << w[i] << "\n";
            }
        }
    }
}

void openOld(string file)
{
    fstream puzzleData;
    puzzleData.open(file + ".txt", ios::in); //reads from file
    if (puzzleData.is_open())
    {
        string tD;
        while (getline(puzzleData, tD))
        {
            cout << tD << "\n";
        }
    }
}
// keeping track of # of words? im confused where my error is :( 
class No
{
public:
    string da;
    No *nxt;
    No(string val)
    {
        da = val;
        nxt = NULL;
    }
};

void insert(No *&he, string val)
{
    No *n = new No(val);
    if (he == NULL)
    {
        he = n;
        return;
    }
    No *te = he;
    while (te->nxt != NULL)
    {
        te = te->nxt;
    }
    te->nxt = n;
}

void solvePuzzle(string file)
{
    No *puzzles = NULL;
    No *solutions = NULL;
    fstream puzzleData;
    puzzleData.open(file + ".txt", ios::in); //reading from file
    if (puzzleData.is_open())
    {
        string tD;
        int v = 0;
        //gathering data
        while (getline(puzzleData, tD))
            if (v == 2)
            {
                insert(puzzles, tD);
            }
            if (v == 1)
            {
                insert(solutions, tD);
            }
            if (tD == "Puzzles")
            {
                v = 2;
            }
            if (tD == "Solutions")
            {
                v = 1;
            }
        }
        No *t1 = solutions;
        No *t2 = puzzles;
        while (t1 != NULL)
        {
            while (t2 != NULL)
            {
                if (t1 == NULL)
                {
                    t2 = NULL;
                    continue;
                }
                string sS = t1->da;
                string sP = t2->da;
                int lP = strlen(sP.c_str());
                int lS = strlen(sS.c_str());
                for (int i = 0; i < lS; i++)
                {
                    for (int j = 0; j < lP; j++)
                    {
                        if (sS[i] == sP[j])
                        {
                            cout << sS[i];
                            i = i + 1;
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                }
                cout << "\n";
                t2 = t2->nxt;
                t1 = t1->nxt;
            }
        }
    }


int main()
{
    bool s = true;
    while (s)
    {
        cout << "hello user!" << endl;
        cout << "Choose an option:" << endl;
        cout << "(1) Create a new puzzle" << endl;
        cout << "(2) Open an existing puzzle" << endl;
        cout << "(3) Solve an existing puzzle" << endl;
        cout << "(4) Exit" << endl;
        int userInput = 0;
        cin >> userInput;
        string file1, file2;
        switch (userInput)
        {
        case 1:
            createNew();
            break;
        case 2:
            cout << "Enter file name to read old puzzle:";
            cin >> file1;
            openOld(file1);
            break;
        case 3:
            cout << "Enter file name to read old puzzle:";
            cin >> file2;
            solvePuzzle(file2);
            break;
        case 4:
            s = false;
            break;
        default:
            cout << "Please enter a valid choice 1-4!" << endl;
            break;
        }
    }
}