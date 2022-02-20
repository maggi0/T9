#include "t9.h"
#include "ui_t9.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <array>
#include <list>
#include <sstream>

using namespace std;

QString StartText = "Insert a word";
QString NotFound = "Word not found";
int i = 0;
Trie *obj = new Trie();
vector <string> words {};

int Convert::convertToInt(char c)
{
    int val = (int)c;
    switch(val)
    {
    case 97 ... 99:
        return 2;
    case 100 ... 102:
        return 3;
    case 103 ... 105:
        return 4;
    case 106 ... 108:
        return 5;
    case 109 ... 111:
        return 6;
    case 112 ... 115:
        return 7;
    case 116 ... 118:
        return 8;
    case 119 ... 122:
        return 9;
    default:
    {
        cout << "Wrong symbol";
        exit(-1);
    }
    }
}

char Convert::convertToChar(char c)
{
    int val = (int)c;
    switch (val)
    {
    case 50:
        return 'a';
    case 51:
        return 'd';
    case 52:
        return 'g';
    case 53:
        return 'j';
    case 54:
        return 'm';
    case 55:
        return 'p';
    case 56:
        return 't';
    case 57:
        return 'w';
    default:
    {
        cout << "Wrong symbol" << endl;
        exit(-1);
    }
    }
}

vector<char> Convert::convertToT9(string toT9)
{
    vector<char> v{};

    for (char c : toT9)
        v.push_back(convertToChar(c));

    return v;
}

Trie::Trie()
{
    for (int i = 0; i < 8; ++i)
        children[i] = nullptr;
}

void Trie::insert(string word)
{
    Trie *curr = this;
    for (char c : word)
    {
        int i = Convert::convertToInt(c);
        if (!(curr->children[i-2]))
            curr->children[i-2] = new Trie;
        curr = curr->children[i-2];
    }
    curr->v.push_back(word);
}

vector<string> Trie::search(string word)
{
    Trie *curr = this;
    for (char c : word)
    {
        int i = Convert::convertToInt(c);
        curr = curr->children[i-2];
        if(!curr)
        {
            vector<string> emptyv {};
            return emptyv;
        }
    }
    return curr->v;
}

Trie::~Trie()
{
    Trie *curr = this;
    for(auto &node : curr->children)
        if(node != nullptr)
            delete node;
}

bool isNumber(string s)
{
    for (char c : s) {
        if (isdigit(c) == 0)
            return false;
    }
    return true;
}

T9::T9(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::T9)
{
    ui->setupUi(this);

    LoadDictionary(obj);

    ui->display->setText(StartText);

    QPushButton *buttons[9];
    for(int i = 1; i <= 9; i++)
    {
        QString button = "Button" + QString::number(i);
        buttons[i] = T9::findChild<QPushButton *>(button);
        connect(buttons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    QPushButton *FindWordButton = T9::findChild<QPushButton *>("FindWordButton");
    connect(FindWordButton, SIGNAL(released()), this, SLOT(FindWordIterator()));

    QPushButton *ResetButton = T9::findChild<QPushButton *>("ResetButton");
    connect(ResetButton, SIGNAL(released()), this, SLOT(ResetPressed()));

    QPushButton *Button0 = T9::findChild<QPushButton *>("Button0");
    connect(Button0, SIGNAL(released()), this, SLOT(SpacePressed()));

    QPushButton *SaveButton = T9::findChild<QPushButton *>("SaveButton");
    connect(SaveButton, SIGNAL(released()), this, SLOT(SavePressed()));
}

T9::~T9()
{
    delete obj;
    delete ui;
}

void T9::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->display->text();
    if((displayVal==NotFound)||(displayVal==StartText))
    {
        ui->display->setText(butVal);
    }
    else
    {
        QString newVal = displayVal + butVal;
        ui->display->setText(newVal);
    }
}

vector<string> T9::FindWord(Trie *obj)
{
    QString displayVal = ui->display->text();
    stringstream ss(displayVal.toStdString());
    string word;
    vector <string> wordsVector {};
    while(ss >> word)
        wordsVector.push_back(word);

    vector<char> v{};
    v = Convert::convertToT9(wordsVector.back());
    string s = "";
    for (int i = 0; i < (int)v.size(); i++)
    {
        s.push_back(v.at(i));
    }

    vector<string> vect {};
    vect = obj->search(s);

    return vect;

}

void T9::FindWordIterator()
{
    QString displayVal = ui->display->text();
    stringstream ss(displayVal.toStdString());
    string word;
    vector <string> wordsVector {};
    while(ss >> word)
        wordsVector.push_back(word);

    string text = "";
    for (int i = 0; i < (int)wordsVector.size() - 1; i++)
        text = text + " " + wordsVector.at(i);

    if(isNumber(wordsVector.back()))
        words = FindWord(obj);

    if(words.empty() == true)
        ui->display->setText(NotFound);

    else
    {
        string lastWord = words.at(i%words.size());
        string toDisplay = text + " " + lastWord;
        QString qToDisplay = QString::fromStdString(toDisplay);
        ui->display->setText(qToDisplay);
        i++;
    }
}

void T9::LoadDictionary(Trie *obj)
{
    QString path = qApp->applicationDirPath() + "/dictionary.txt";
    fstream file{path.toStdString()};
    if (not file)
    {
        cout << "blad otwarcia strumienia wejsciowego" << endl;
        exit(-1);
    }

    if (file.is_open())
    { //checking whether the file is open
        string word;
        cout << "Loading dictionary... " << endl;
        while (getline(file, word))
        {
            obj->insert(word);
        }
        cout << "Dictionary loaded! " << endl;
        file.close(); //close the file object.
    }
}

void T9::ResetPressed()
{
    ui->display->setText(StartText);
}

void T9::SpacePressed()
{
    QString displayVal = ui->display->text();
    ui->display->setText(displayVal + " ");
}

void T9::SavePressed()
{
    QString path = qApp->applicationDirPath() + "/text.txt";
    ofstream file{path.toStdString()};
    if (not file)
    {
        cout << "blad otwarcia strumienia wyjsciowego" << endl;
        exit(-1);
    }

    if (file.is_open())
    {
        QString displayVal = ui->display->text();
        file << displayVal.toStdString();
        cout << "Zapisano tekst! " << endl;
        file.close();
    }
}











