#include "date.h"

Date::Date(int y, int m, int d)
        : year(y), month(m), day(d) {
}

int Date::GetYear() const {
  return year;
}

int Date::GetMonth() const {
  return month;
}

int Date::GetDay() const {
  return day;
}

bool Date::operator<(const Date &right) const {
//  return Toword() < right.Toword();
  return DTuple() < right.DTuple();
}

bool Date::operator<=(const Date &right) const {
//  return Toword() <= right.Toword();
  return DTuple() <= right.DTuple();
}

bool Date::operator>(const Date &right) const {
//  return Toword() > right.Toword();
  return DTuple() > right.DTuple();
}

bool Date::operator>=(const Date &right) const {
//  return Toword() >= right.Toword();
  return DTuple() >= right.DTuple();
}

bool Date::operator==(const Date &right) const {
//  return Toword() == right.Toword();
  return DTuple() == right.DTuple();
}

bool Date::operator!=(const Date &right) const {
//  return Toword() != right.Toword();
  return DTuple() != right.DTuple();
}

string Date::Toword() const {
 ostringstream  ss;
 ss << setw(4) << setfill('0') << to_string(year);
 ss << '-';
 ss << setw(2) << setfill('0') << to_string(month);
 ss << '-';
 ss << setw(2) << setfill('0') << to_string(day);
 return ss.str();
}
 



tuple<int, int, int> Date::DTuple() const {
  return tuple(year, month, day);
}

istream &operator>>(istream &is, Date &dt) {
    int y, m, d;
    char das;
    bool valid_d = true;
    string dt_st;
    is >> dt_st;

    istringstream stream(dt_st);
    stream >> y;
    stream >> das;
    valid_d &= das == dash;
    stream >> m;
    stream >> das;
    valid_d &= das == dash;
    stream >> d;
    if (!stream || stream >> das || !valid_d) {
      throw std::runtime_error(DateW + dt_st);
    }
    dt = Date(y, m, d);
    return is;
}

ostream &operator<<(ostream &s, const Date &d) {
  s << d.Toword();
  return s;
}

Date ParseDate(istream &s) {
  Date date;
  s >> date;
  return date;
}