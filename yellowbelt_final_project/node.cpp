#include "node.h"

bool EmptyNode::Evaluate(const Date &date, const string &event) const {
  return true;
}

ComparisonNode::ComparisonNode(const Comparison &new_comppare)
        : comppare(new_comppare) {
}

DateComparisonNode::DateComparisonNode(const Comparison &new_comppare, const Date &new_date)
        : ComparisonNode(new_comppare), date(new_date) {
}

bool DateComparisonNode::Evaluate(const Date &d, const string &e) const {
  return Compare(d, date, comppare);
}

EventComparisonNode::EventComparisonNode(const Comparison &new_comppare, const string &new_event)
        : ComparisonNode(new_comppare), event(new_event) {
}

bool EventComparisonNode::Evaluate(const Date &d, const string &e) const {
  return Compare(e, event, comppare);
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &new_operation, const shared_ptr<Node> &new_left,
                                           const shared_ptr<Node> &new_right)
        : operation(new_operation), left(new_left), right(new_right) {
}

bool LogicalOperationNode::Evaluate(const Date &d, const string &e) const {
  const bool left_ev = left->Evaluate(d, e);
  const bool right_ev = right->Evaluate(d, e);
  switch (operation) {
    case LogicalOperation::Or:
      return left_ev || right_ev;
    case LogicalOperation::And:
      return left_ev && right_ev;
    default:
      throw std::invalid_argument("No alike operation ");
  }
}