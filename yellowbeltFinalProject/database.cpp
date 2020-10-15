#include "database.h"

void Database::Add(const Date &date, const string &e) {
  if (uniq_evnts.count(date) == 0 || uniq_evnts[date].count(e) == 0) {
    uniq_evnts[date].insert(e);
    evnts[date].emplace_back(e);
  }
}

void Database::Print(ostream &s) const {
  for (const auto &[d, d_evnts] : evnts) {
    for (const auto &x : d_evnts) {
      s << d << ' ' << x << '\n';
    }
  }
}

vector<pair<Date, string>> Database::FindIf(const std::function<bool(Date, string)> &p) const {
  vector<pair<Date, string>> r;
  for (const auto &[d, d_evnts] : evnts) {
    for (const auto &x : d_evnts) {
      if (p(d, x)) {
        r.emplace_back(d, x);
      }
    }
  }
  return r;
}

int Database::RemoveIf(const std::function<bool(Date, string)> &p) {
  int cnt = 0;
  auto it_evnts = evnts.begin();
  while (it_evnts != evnts.end()) {
    auto it_remove = stable_partition(it_evnts->second.begin(), it_evnts->second.end(), [&](const string &e) {
      return !p(it_evnts->first, e);
    });
    if (it_remove != it_evnts->second.end()) {
      cnt += distance(it_remove, it_evnts->second.end());
      it_evnts->second.erase(it_remove, it_evnts->second.end());
      uniq_evnts[it_evnts->first].clear();
    }
    if (it_evnts->second.empty()) {
      uniq_evnts.erase(it_evnts->first);
      it_evnts = evnts.erase(it_evnts);
    } else {
      uniq_evnts[it_evnts->first].insert(it_evnts->second.begin(), it_evnts->second.end());
      ++it_evnts;
    }
  }
  return cnt;
}

string Database::Last(const Date &d) const {
  if (d < begin(uniq_evnts)->first || evnts.empty()) {
    throw std::invalid_argument("");
  }
  auto it_date = uniq_evnts.upper_bound(d);
  --it_date;
  ostringstream s;
  s << it_date->first << ' ' << evnts.at(it_date->first).back();
  return s.str();
}
ostream &operator<<(ostream &s, const pair<Date, string> &e) {
  return s << e.first << ' ' << e.second;
}