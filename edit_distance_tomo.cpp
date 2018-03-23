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
#include <regex>

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

string remove_newlines(const string& s) {
    int n = s.size();
    string r;
    r.reserve(n);
    bool previous_white = false;
    for (char c : s) {
        if (c == '\n') {
            if (!previous_white) {
                r.push_back('\n');
                previous_white = true;
            }
        } else {
            previous_white = false;
            r.push_back(c);
        }
    }
    return r;
}

string remove_python_comments(const string& s) {
    int n = s.size();
    string r;
    r.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (s[i] == '#') {
            int j = i;
            while (++j < n) {
                if (s[j] == '\n') break;
            }
            i = (j == n) ? i + 1 : j;
        } else {
            r.push_back(s[i]);
        }
    }
    return r;
}

string remove_trailing_whitespace(const string& s) {
    return std::regex_replace(s, std::regex(" +$"), "");
}

string remove_tomo_code(const string& s) {
    string start = "# ============================================================================@\n\n'";
    auto idx = s.find(start);
    if (idx == string::npos) {
        return "";
    }
    return s.substr(0, idx);
}

string read(const string& filename) {
    ifstream f(filename, ios::in);
    if (!f) {
        cerr << "File: '" << filename << "' does not exist!\n";
        throw 1;
    }

    string s;
    getline (f, s, '\0');
    s = remove_trailing_whitespace(s);
    s = remove_tomo_code(s);
    if (s.empty()) {
        cerr << "File: '" << filename << "' has no Tomo signature!\n";
    }
    s = remove_python_comments(s);
    s = remove_newlines(s);
    return s;
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
        double dist = 1.0;
        if (files[i].size() > 10 && files[j].size() > 10) {
            dist = levenshtein_distance(files[i], files[j]);
        }
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
