// https://www.hackerrank.com/challenges/attribute-parser/problem
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define Noom

#include <string>
#include <sstream>
#include <unordered_map>

struct Tag
{
    Tag()
        : name(""), closed(false)
    {}

    string name;
    unordered_map<string, string> args;
    bool closed;

    vector<Tag> children;
};

vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream. 
    string token;
    
    while (getline(ss, token, delimiter)) {
        internal.push_back(token);
    }
    
    return internal;
}

Tag* FindLastChild(vector<Tag>& tags, Tag* parent = nullptr)
{
    for (int i = 0; i < tags.size(); i++)
    {
        if (tags[i].closed == false)
        {
            parent = &tags[i];
#ifdef Noom
            cout << "|";
#endif // Noom
            parent = FindLastChild(tags[i].children, parent);
            break;
        }
    }

    return parent;
}

void CloseTag(vector<Tag>& tags, const string& name)
{
    for (int i = 0; i < tags.size(); i++)
    {
        if (tags[i].name == name)
        {
            tags[i].closed = true;
            return;
        }
    }

    for (int i = 0; i < tags.size(); i++)
    {
        CloseTag(tags[i].children, name);
    }
}

void printTag(Tag* tag, int depth = 0)
{
    cout << tag->name << " ";
    for (auto arg : tag->args)
        cout << arg.first << "=" << arg.second << " ";
    cout << tag->closed << "\n";
    depth++;
    for (Tag child : tag->children)
    {
        for(int j = 0; j < depth; j++)
            cout << "   ";
        printTag(&child, depth);
    }
}

void Find(const vector<Tag>& tagsList, const vector<string>& tags, const string& value, int progress = 0)
{
    for (int i = 0; i < tagsList.size(); i++)
    {
#ifdef Noom
        cout << progress << " " << tagsList.size() << " " << tags.size() << " \n";
#endif // Noom
        if (progress < tags.size() - 1)
        {
            if (tagsList[i].name == tags[progress])
            {
                progress++;
                Find(tagsList[i].children, tags, value, progress);
                return;
            }
        }
        else
        {
#ifdef Noom
            cout << "Found: " << tagsList[i].name << " !\n";
#endif // Noom
            if (tagsList[i].name == tags[progress])
            {
                if (tagsList[i].args.find(value) != tagsList[i].args.end())
                {
                    auto output = *tagsList[i].args.find(value);
                    cout << output.second << "\n";
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
#ifdef Noom
            cout << "DONE\n\n";
#endif // Noom
            return;
        }
    }
    cout << "Not Found!\n";
#ifdef Noom
    cout << "DONE\n\n";
#endif // Noom
}

int main() {
    vector<Tag> tagsList;
    int n, q;
    cin >> n >> q;
    cin.get();

    while (n--)
    {
        string line;
        getline(cin, line);

        line = line.substr(1, line.size() - 2);

        vector<string> tokens = split(line, ' ');

        if (tokens[0][0] != '/')
        {
            Tag newTag;
            newTag.name = tokens[0];

            int tokensnr = tokens.size() - 1;

            for(int i = 1; tokensnr % 3 == 0 && tokensnr != 0; i +=3, tokensnr -= 3)
                newTag.args.insert(make_pair(tokens[i], tokens[i + 2].substr(1, tokens[i + 2].size() - 2)));

            Tag* parent = FindLastChild(tagsList);

            if (parent)
                parent->children.push_back(newTag);
            else
                tagsList.push_back(newTag);
        }
        else
        {
            tokens[0] = tokens[0].substr(1, tokens[0].size() - 1);

            CloseTag(tagsList, tokens[0]);
        }

#ifdef Noom2
        cout << "\n\n";
        for (Tag tag : tagsList)
        {
            printTag(&tag);
        }
        cout << "\n\n";
#endif // Noom
    }

#ifdef Noom
    cout << "\n\n";
    for (Tag tag : tagsList)
    {
        printTag(&tag);
    }
    cout << "\n\n";
#endif // Noom

    while (q--)
    {
        string line;
        getline(cin, line);

        vector<string> queries = split(line, '.');
        string value = queries[queries.size() - 1];
        {
            vector<string> last = split(value, '~');
            queries[queries.size() - 1] = last[0];
            value = last[1];
        }
        Find(tagsList, queries, value);
    }
    
    return 0;
}


/*
#include <iostream>
#include <map>
using namespace std;

map <string, string> tagMap;

void createMap(int &n, string pretag) {
    if(!n) return;

    string line, tag, attr, value;
    getline(cin, line);

    int i=1;
    if(line[i]=='/') {           // found closing tag
        while(line[i]!='>') i++;
        if(pretag.size()>(i-2))		// update tag
            tag = pretag.substr(0,pretag.size()-i+1);
        else
            tag = "";
    }
    else {                       // found opening tag
        while(line[i]!=' ' && line[i]!='>') i++;
        tag = line.substr(1,i-1);	// update tag
        if(pretag!="") tag = pretag + "." + tag;

        int j;
        while(line[i]!='>') { // go through attributes
            j = ++i;
            while(line[i]!=' ') i++;
            attr = line.substr(j,i-j);	// attribute name

            while(line[i]!='\"') i++;
            j = ++i;
            while(line[i]!='\"') i++;
            value = line.substr(j,i-j);	// attribute value
            i+= 1;

            tagMap[tag + "~" + attr] = value;
        }
    }
    createMap(--n, tag);
}

int main() {
    int n, q;
    cin >> n >> q;
    cin.ignore();
    createMap(n,"");

    string attr, value;
    while(q--) {
        getline(cin,attr);
        value = tagMap[attr];
        if(value=="") value = "Not Found!";
        cout << value << endl;
    }
    return 0;
}

*/