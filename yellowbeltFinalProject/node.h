//// class Node;
// class EmptyNode;
// class DateComparisonNode;
// class EventComparisonNode;
// class LogicalOperationNode;

#pragma once

#ifndef MC_NODE_H
#define MC_NODE_H

#include <memory>
#include "date.h"

using namespace std;

enum Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

enum LogicalOperation {
  Or,
  And
};

class Node {
public:
  virtual bool Evaluate(const Date &date, const string &event) const = 0;
};

class EmptyNode : public Node {
public:
  bool Evaluate(const Date &date, const string &event) const override;
};

class ComparisonNode : public Node {
public:
  ComparisonNode(const Comparison &new_comppare);

protected:
  template<typename T>
  bool Compare(const T &left, const T &right, const Comparison &comppare) const {
    switch (comppare) {
      case Comparison::Equal:
        return left == right;
		case Comparison::Greater:
        return left > right;
      case Comparison::LessOrEqual:
        return left <= right;
      case Comparison::Less:
        return left < right;
      case Comparison::NotEqual:
        return left != right;
      case Comparison::GreaterOrEqual:
        return left >= right;
      
      default:
        throw std::invalid_argument("No such Comparison");
    }
  }

  const Comparison comppare;
};

class DateComparisonNode : public ComparisonNode {
public:
  DateComparisonNode(const Comparison &new_comppare, const Date &new_date);

  bool Evaluate(const Date &date, const string &event) const override;

private:
  const Date date;
};
class LogicalOperationNode : public Node {
public:
  LogicalOperationNode(const LogicalOperation &new_operation, const shared_ptr<Node> &left, const shared_ptr<Node> &right);

  bool Evaluate(const Date &date, const string &event) const override;

private:
  const LogicalOperation operation;
  const shared_ptr<Node> left;
  const shared_ptr<Node> right;
};
class EventComparisonNode : public ComparisonNode {
public:
  EventComparisonNode(const Comparison &new_comppare, const string &new_event);

  bool Evaluate(const Date &date, const string &event) const override;

private:
  const string event;
};



#endif
//cpp
