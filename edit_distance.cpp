#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <string>
#include <tuple>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::max;
using std::min;
using std::pair;
using std::string;
using std::tie;
using std::vector;

string remove_whitespace(const string& s) {
    int n = s.size();
    string r;
    r.reserve(n);
    bool previous_white = false;
    for (char c : s) {
        if (isspace(c)) {
            if (!previous_white) {
                r.push_back(' ');
                previous_white = true;
            }
        } else {
            previous_white = false;
            r.push_back(c);
        }
    }
    return r;
}

string remove_cpp_comments(const string& s) {
    int i = 0;
    int n = s.size();
    char c;
    string r;
    r.reserve(n);
    while (i < n) {
        c = s[i++];
        if (c == '\'' || c == '"') {  // literal
            char q = c;
            do {
                r.push_back(c);
                if (c == '\\' && i < n) r.push_back(s[i++]);
                if (i >= n) break;
                c = s[i++];
            } while (c != q);
            r.push_back(c);
        } else if (c == '/') { /* opening comment ? */
            if (i >= n) break;
            c = s[i++];
            if (c != '*' && c != '/') { /* no, recover */
                r.push_back('/');
                i--;
            } else if (c == '*') {
                char p;
                r.push_back(' '); /* replace comment with space */
                do {
                    p = c;
                    c = s[i++];
                } while (i < n && (c != '/' || p != '*'));
            } else {  /* // comment  */
                r.push_back(' '); /* replace comment with space */
                while (i < n && s[i++] != '\n');  // seek newline
            }
        } else {
            r.push_back(c);
        }
    }
    return r;
}

string remove_preprocessor(const string& s) {
    int n = s.size();
    string r;
    r.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (s[i] == '#') {
            int j = i;
            while (++j < n) {
                if (s[j] == '\n' || s[j] == '>') break;
            }
            i = (j == n) ? i + 1 : j;
        } else {
            r.push_back(s[i]);
        }
    }
    return r;
}

string read(const string& filename) {
    ifstream f(filename, ios::in);
    if (!f) {
        cerr << "File: '" << filename << "' does not exist!\n";
        throw 1;
    }

    string s;
    getline (f, s, '\0');
    string nc = remove_cpp_comments(s);
    string np = remove_preprocessor(nc);
    string nw = remove_whitespace(np);
    return nw;
}

template <class T>
int levenshtein_distance(const T& s1, const T& s2) {
    int len1 = s1.size(), len2 = s2.size();
    vector<unsigned int> col(len2 + 1), prevCol(len2 + 1);

    for (int i = 0; i < len2 + 1; ++i) prevCol[i] = i;
    for (int i = 0; i < len1; ++i) {
        col[0] = i + 1;
        for (int j = 0; j < len2; ++j)
            col[j + 1] = min(min(prevCol[1 + j] + 1, col[j] + 1), prevCol[j] + (s1[i] != s2[j]));
        col.swap(prevCol);
    }
    return prevCol[len2];
}

int main(int argv, char** argc) {
    assert(argv >= 3);

    int num_of_files = argv - 1;
    cerr << "Reading files..." << endl;
    vector<string> files(num_of_files);
    for (int i = 0; i < num_of_files; ++i) {
        files[i] = read(argc[i + 1]);
    }
    cerr << "Comparing files..." << endl;
    int c = 0;
    int total = num_of_files * (num_of_files - 1) / 2;
    vector<pair<int, int>> pairs(total);
    for (int i = 0; i < num_of_files; ++i) {
        for (int j = i + 1; j < num_of_files; ++j) {
            pairs[c++] = {i, j};
        }
    }
    vector<pair<double, double>> result(total);
    #pragma omp parallel for
    for (int k = 0; k < total; ++k) {
        int i, j;
        tie(i, j) = pairs[k];
        double dist = levenshtein_distance(files[i], files[j]);
        double rel_dist = (dist) / max(files[i].size(), files[j].size());
        result[k] = {dist, rel_dist};
    }
    for (const auto& p : result) {
        cout << p.first << '~' << p.second << '\n';
    }
    cout.flush();
    cerr << "Done." << endl;

    return 0;
}
