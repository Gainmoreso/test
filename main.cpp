#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

typedef struct HTNode
{
    int weight;
    char ch;
    HTNode *parrent, *lchild, *rchild;
} HTNode, *HuffmanTree;

vector<HuffmanTree> nodes;
map<char, string>CharCode;

bool comp(HuffmanTree &a, HuffmanTree &b)
{
    return a->weight <= b->weight;
}

void InitNodes()
{
    cout << "输入编码个数: ";
    int n;
    cin >> n;
    cin.ignore();
    for(int i = 0;i < n;i++)
    {

        HuffmanTree newNode = new HTNode;
        cin.get(newNode->ch);
        cin >> newNode->weight;
        newNode->parrent = newNode->lchild = newNode->rchild = NULL;
        nodes.push_back(newNode);
        cin.ignore();
    }
}

void CreateHuffmanTree(HuffmanTree &Tree)
{
    while(nodes.size() != 1)
    {
        HuffmanTree parrentPtr = new HTNode;
        sort(nodes.begin(), nodes.end(), comp);
        parrentPtr->ch = '@';
        parrentPtr->weight = nodes.at(0)->weight + nodes.at(1)->weight;
        parrentPtr->parrent = NULL;
        parrentPtr->lchild = nodes.at(0);
        parrentPtr->rchild = nodes.at(1);
        nodes.at(0)->parrent = nodes.at(1)->parrent = parrentPtr;

        nodes.erase(nodes.begin());
        nodes.erase(nodes.begin());
        nodes.insert(nodes.begin(), parrentPtr);
    }
    Tree = nodes.at(0);
}

void PrintHuffmanTree(HuffmanTree T)
{
    if(T != NULL)
    {
        PrintHuffmanTree(T->lchild);
        cout << T->weight << " ";
        PrintHuffmanTree(T->rchild);
    }
}

void GetHuffmanTreeCode(HuffmanTree &root,string code)
{
    if(root)
    {
        if(root->lchild == NULL && root->rchild == NULL)
        {
            CharCode.insert(pair<char, string>(root->ch, code));
        }
        GetHuffmanTreeCode(root->lchild, code + "0");
        GetHuffmanTreeCode(root->rchild, code + "1");
    }
}

void PrintCharCode(map<char, string>charcode)
{
    map<char, string>::iterator itbegin = CharCode.begin();
    map<char, string>::iterator itend = CharCode.end();
    while(itbegin != itend)
    {
        cout << itbegin->first << ": " << itbegin->second << endl;
        itbegin++;
    }
}

void CharToCode(map<char, string>charcode, string s)
{
    for(int i = 0; i < s.length(); i++)
        cout << charcode.at(s[i]);
    cout << endl;
}

void CodeToChar(map<char, string>charcode, string s)
{
    int i = 0;
    for(int j = i+1; j <= s.length(); j++)
    {
        string str = s.substr(i, j-i);
        for(map<char, string>::iterator it = charcode.begin(); it != charcode.end(); it++)
        {
            if(it->second == str)
            {
                cout << it->first;
                i = j;
            }
        }
    }
}

int main()
{
    InitNodes();
    HuffmanTree Tree;
    CreateHuffmanTree(Tree);
    PrintHuffmanTree(Tree);
    cout << endl;
    GetHuffmanTreeCode(Tree, "");
    PrintCharCode(CharCode);

    string s1, s2;
    getline(cin, s1);
    CharToCode(CharCode, s1);
    cin >> s2;
    CodeToChar(CharCode, s2);
    return 0;
}
