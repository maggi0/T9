#ifndef T9_H
#define T9_H

#include <QMainWindow>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class T9; }
QT_END_NAMESPACE

class Convert
{
public:
    /** takes a letter and returns its corresponding number according to T9 dictionary */
    static int convertToInt(char c);
    /** takes a number and returns its corresponding letter according to T9 dictionary */
    static char convertToChar(char c);
    /** takes a word and returns a vector of characters stored in the word */
    static std::vector<char> convertToT9(std::string toT9);
};

class Trie
{
    Trie *children[8];
    std::vector<std::string> v {};
public:
    /** Initialize the trie. */
    Trie();
    /** Inserts a word into the trie. */
    void insert(std::string word);
    /** Returns the vector of words stored in a node */
    std::vector<std::string> search(std::string word);
    /** Destructor */
    ~Trie();
};

class T9 : public QMainWindow
{
    Q_OBJECT

public:
    T9(QWidget *parent = nullptr);
    ~T9();

private:
    Ui::T9 *ui;

private slots:
    /** Action executed when a numeric key is pressed */
    void NumPressed();
    /** returns the vector of words stored in the passed nose */
    std::vector<std::string> FindWord(Trie *obj);
    /** Action executed when the "Find Word" button is pressed */
    void FindWordIterator();
    /** Loads the dictionary into the Trie */
    void LoadDictionary(Trie *obj);
    /** Action executed when the "Reset" Button is pressed */
    void ResetPressed();
    /** Action executed when the "Space" Button is pressed */
    void SpacePressed();
    /** Action executed when the "Save Text" Button is pressed */
    void SavePressed();
};
#endif // T9_H
