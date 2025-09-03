#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

// Prototipos
string inverte(string a);

int main(int argc, char const *argv[])
{
    string palavra{"ATECUB AN OS"};
    cout << inverte(palavra) << endl;
    return 0;
}

string inverte(string a)
{
    reverse(a.begin(), a.end());
    return a;
}