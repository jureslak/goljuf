#include <iostream>
#include <vector>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void read(const string& filename, string& content) {
    ifstream f(filename, ios::in);
    if (!f) {
        cerr << "File: '" << filename << "' does not exist!\n";
        throw 1;
    }

    f.seekg(0, ios::end);
    content.reserve(f.tellg());
    f.seekg(0, ios::beg);

    char c;
    while ((c = f.get()) != EOF)
        if (isgraph(c))
            content.append(1, c);
}


template<class T>
int levenshtein_distance(const T& s1, const T&  s2) {
    int len1 = s1.size(), len2 = s2.size();
    vector<unsigned int> col(len2+1), prevCol(len2+1);

    for (int i = 0; i < len2+1; ++i)
        prevCol[i] = i;
    for (int i = 0; i < len1; ++i) {
        col[0] = i + 1;
        for (int j = 0; j < len2; ++j)
            col[j+1] = min(min(prevCol[1 + j] + 1, col[j] + 1),
                               prevCol[j] + (s1[i] != s2[j]));
        col.swap(prevCol);
    }
    return prevCol[len2];
}

int main(int argv, char** argc) {
    assert(argv >= 3);

    int num_of_files = argv - 1;
    vector<string> files(num_of_files);
    size_t maxlen = 0;
    for (int i = 0; i < num_of_files; ++i) {
        read(argc[i+1], files[i]);
        if (files[i].size() > maxlen)
            maxlen = files[i].size();
    }

    for (int i = 0; i < num_of_files; ++i) {
        for (int j = i + 1; j < num_of_files; ++j) {
              double dist = levenshtein_distance(files[i], files[j]);
              double rel_dist = (dist) / max(files[i].size(), files[j].size());
//              cout << argc[i+1] << " : " << argc[j+1] << " ~ " << rel_dist << '\n';
              cout << dist << '~' << rel_dist << '\n';
        }
    }

    return 0;
}

