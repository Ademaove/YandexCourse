#pragma once

#include "database.h"

#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& out, const set<T>& st) {
    out << "{";
    bool f = true;
    for (const auto& a : st) {
        if (!f) {
            out << ", ";
        }
        f = false;
        out << a;
    }
    out << "}";
    return out;
}

template<typename T>
ostream& operator << (ostream& out, const vector<T>& vec) {
    out << "{";
    bool f = true;
    for (const auto& c : vec) {
        if (!f) {
            out << ", ";
        }
        f = false;
        out << c;
    }
   out << "}";
    return out;
}

template <class K, class V>
ostream& operator << (ostream& out, const map<K, V>& m) {
    out << "{";
    bool f = true;
    for (const auto& pr : m) {
        if (!f) {
            out << ", ";
        }
        f = false;
        out << pr.first << ": " << pr.second;
    }
out << "}";
    return out;}

template<class T, class K>
void AssertEqual(const T& t, const K& k,
                 const string& hint)
{
    if (t != k) {
        ostringstream out;
        out << "Assertion failed: " << t << " != " << k << " hint: " << hint;	
        throw runtime_error(out.str());
    }
}

inline void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}
class TestRunner {
public:
    template <typename TestFunc>
    void RunTest(TestFunc fun, const string& s) {
        try {
            fun();
            cerr << s << " OK!" << endl;
        }
        catch (runtime_error & error) {
            ++cnt;
            cerr << s << " failed, reason: " << error.what() << endl;
        }
    }
    ~TestRunner() {
        if (cnt > 0) {
            cerr << cnt << " tests failed. Exit" << endl;
            exit(1);
        }
    }
private:
    int cnt = 0;
};
