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

//  class EditDistance {
//      vector<vector<int>> d;
//    public:
//      EditDistance(int maxh, int maxw) : d(maxh, vector<int>(maxw)) {};
//      int dist(const string& s, const string& t) {
//          const int ls = s.size(), lt = s.size();
//          d[0][0] = 0;
//          for (int i = 1; i <= ls; ++i) d[i][0] = i;
//          for (int i = 1; i <= lt; ++i) d[0][i] = i;
//          for (int i = 1; i <= ls; ++i)
//              for (int j = 1; j <= lt; ++j)
//                  if (s[i-1] == t[j-1]) d[i][j] = d[i-1][j-1];
//                  else d[i][j] = min(min(d[i-1][j] + 1, d[i][j-1] + 1), d[i-1][j-1] + 1);
//          return d[ls][lt];
//      }
//      double relative_dist(const string& s, const string& t) {
//          return double(dist(s, t)) / max(s.size(), t.size());
//      }
//  };

template<class T>
unsigned int levenshtein_distance(const T &s1, const T & s2) {
    const size_t len1 = s1.size(), len2 = s2.size();
    vector<unsigned int> col(len2+1), prevCol(len2+1);

    for (unsigned int i = 0; i < prevCol.size(); i++)
        prevCol[i] = i;
    for (unsigned int i = 0; i < len1; i++) {
        col[0] = i+1;
        for (unsigned int j = 0; j < len2; j++)
            col[j+1] = std::min( std::min(prevCol[1 + j] + 1, col[j] + 1),
                                prevCol[j] + (s1[i]==s2[j] ? 0 : 1) );
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

//      EditDistance metric(maxlen+1, maxlen+1);


    for (int i = 0; i < num_of_files; ++i) {
        for (int j = i + 1; j < num_of_files; ++j) {
//              double rel_dist = metric.relative_dist(files[i], files[j]);
              double dist = levenshtein_distance(files[i], files[j]);
              double rel_dist = (dist) / max(files[i].size(), files[j].size());
//              cout << argc[i+1] << " : " << argc[j+1] << " ~ " << rel_dist << '\n';
              cout << rel_dist << '\n';
        }
    }

    return 0;
}

