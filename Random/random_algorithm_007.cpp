#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>

struct elev {
    int cod;
    std::vector<std::string> optiuni;
    std::vector<float> note;
};

void Print(elev e) {
    printf("%7d ",e.cod);
    std::string o = "";
    for(std::string& opt : e.optiuni)
        o += opt + ' ';
    while (o.length() != 34) o += ' ';
    printf("%s",o.c_str());
    for(auto n : e.note)
        printf("%.2f%s   ", n, (n >= 9.999f ? "":" "));
    putchar('\n');
}

int main() {
    std::ifstream fin("asteptare.txt");
    std::vector<elev> elevi;
    std::string tmp;
    while(fin >> tmp) {
        elev e;
        fin.get();fin.get();fin.get();fin.get();fin.get();fin.get();
        fin >> tmp;
        e.cod = std::stoi(tmp);
        uint8_t ok = 5;
        while(ok && fin >> tmp) {
            if(isdigit(tmp[0])) {
                e.note.push_back(std::stof(tmp));
                ok--;
            } else
                e.optiuni.push_back(tmp);
        }
        elevi.push_back(e);
    }
    fin.close();
    int c = 0;
    for(int i = 0; i < elevi.size(); ++i) {
        elev& e = elevi[i];
        if(((std::find(e.optiuni.begin(), e.optiuni.end(), "$IA") != e.optiuni.end())
        || (std::find(e.optiuni.begin(), e.optiuni.end(), "$INFO") != e.optiuni.end())
        )&& (e.note[4] >= 8.89f)) {
            c++;
            printf("%d %s", c, (c>=100?"":(c>=10?" ":"  ")));
            Print(e);
        }
    }
}