#pragma once

#ifndef MYCODE_DATABASE_H
#define MYCODE_DATABASE_H
#include <map>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

#include "date.h"
// #include <map>
// #include <set>
// #include <vector>
// #include <functional>
// #include <algorithm>
// #include <iterator>
using namespace std;
// #include "date.h"

class Database {
public:
  void Add(const Date &date, const string &e);

  void Print(ostream &s) const;

  vector<pair<Date, string>> FindIf(const function<bool(Date, string)> &p) const;

  int RemoveIf(const function<bool(Date, string)> &p);

  string Last(const Date &date) const;

private:
  map<Date, set<string>> uniq_evnts;
  map<Date, vector<string>> evnts;
};

ostream &operator<<(ostream &s, const pair<Date, string> &event);

#endif