#pragma once

#ifndef MYCODE_DATE_H
#define MYCODE_DATE_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <tuple>

using namespace std;

const string MInvA = "Month value is invalid: ";
const string DInvA = "Day value is invalid: ";
const string DateW = "Wrong date format: ";
const char dash = '-';

class Date {
public:
  Date(int y = 1, int m = 1, int d = 1);

  int GetYear() const;

  int GetMonth() const;

  int GetDay() const;

  tuple<int, int, int> DTuple() const;

  string Toword() const;

  bool operator<(const Date &right) const;

  bool operator<=(const Date &right) const;

  bool operator>(const Date &right) const;

  bool operator>=(const Date &right) const;

  bool operator==(const Date &right) const;

  bool operator!=(const Date &right) const;

private:
  int year;
  int month;
  int day;
};

istream &operator>>(istream &s, Date &dt);

ostream &operator<<(ostream &s, const Date &d);

Date ParseDate(istream &s);

#endif 


//cpp
