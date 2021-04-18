#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Pair {
    string w1;
    string w2;
    string str;
    int num;
};

int main() {

    fstream text;
    int n = 0, max_value = 0;
    string str, w, check = " .,!?;";
    vector <string> s, s_temp;
    vector <Pair> result;

    text.open("hud-text.txt");

    for (int i = 0; !text.eof(); i++) {
        text >> str;

        if (check.find(str[str.size() - 1]) != string::npos) {////npos - статическая переменная которую возвращает функция find() если не находит елемент в строке
            str.pop_back();
        }
        s.push_back(str);
    }
    s.pop_back();
    str.clear();

    text.close();
    
    for (int r = 0; !s.empty(); r++) {
    
        string word = s[0];
        s.erase(s.begin(), s.begin() + 1);
        s_temp = s;

        for (int h = 0; !s_temp.empty(); h++) {
            w = s_temp[0];

            for (int y = 1;y<= min(w.size(), word.size()); y++) {
                int first = word.size() - y;
                int second = w.size() - y;

                if (word[first] == w[second]) {
                    n++;
                    str += w[second];
                }
                else {
                    break;
                }
            }
            max_value = (max_value > n) ? max_value : n;

            Pair p;
            p.w1 = word;
            p.w2 = w;
            reverse(str.begin(), str.end());
            p.str = str;
            p.num = n;
            result.push_back(p);

            str.clear();
            n = 0;
            s_temp.erase(s_temp.begin(), s_temp.begin() + 1);
        }
    }
    
    text.open("result.txt",ios_base::out | ios_base::trunc);

    for (int m = 0; m < result.size(); m++) {

        if (result[m].num == max_value) {    

            text << result[m].w1 << ", " << result[m].w2 << ", " << result[m].str << ", " << (result[m].num - 2) << '\n';
            cout << result[m].w1 << ", " << result[m].w2 << ", " << result[m].str << ", " << (result[m].num - 2) << '\n';
        }
    }

    text.close();

    return 0;
}