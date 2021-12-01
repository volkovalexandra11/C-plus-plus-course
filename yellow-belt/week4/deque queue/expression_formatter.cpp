#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <sstream>

using namespace std;

enum class OperationType {
  ADD = '+',
  SUBTRACT = '-',
  MULTIPLY = '*',
  DIVIDE = '/'
};

struct Operation {
  OperationType type;
  int right_arg;
};

class ExpressionFormatter {
public:
  explicit ExpressionFormatter(int first_arg) : first_arg(first_arg) {}

  void AddOp(Operation operation) {
      operations.push_back(operation);
  }

  string ToStringWithBraces() {
      stringstream ss;
      for (int i = 0; i < operations.size(); i++) {
          ss << '(';
      }
      ss << first_arg << ')';

      for (auto operation: operations) {
          ss << ' ' << static_cast<char>(operation.type) << ' ' << operation.right_arg << ')';
      }


      string formatted = ss.str();
      formatted.pop_back();
      return formatted;
  }

  string ToStringWithoutBraces() {
      deque<char> formatted_expr;
      AddNumber(formatted_expr, first_arg);


      int last_operation_priority = 50;
      for (auto& operation: operations) {
          AddOperation(formatted_expr, operation, last_operation_priority);
          last_operation_priority = priority[operation.type];
      }

      return {formatted_expr.begin(), formatted_expr.end()};
  }

private:
  int first_arg;
  vector<Operation> operations;

  map<OperationType, int> priority = {
    {OperationType::ADD,      1},
    {OperationType::SUBTRACT, 1},
    {OperationType::MULTIPLY, 2},
    {OperationType::DIVIDE,   2}
  };

  static void AddNumber(deque<char>& dest, int number) {
      for (auto c: to_string(number)) {
          dest.push_back(c);
      }
  }

  void AddOperation(deque<char>& dest, Operation op, int prev_priority) {
      int cur_priority = priority[op.type];
      if (cur_priority > prev_priority) {
          dest.push_back(')');
          dest.push_front('(');
      }

      dest.push_back(' ');
      dest.push_back(static_cast<char>(op.type));
      dest.push_back(' ');
      AddNumber(dest, op.right_arg);
  }

};



ExpressionFormatter ReadAllToFormatter() {
    int first_int, operations_count;
    cin >> first_int;
    cin >> operations_count;

    ExpressionFormatter expression_formatter(first_int);

    for (int i = 0; i < operations_count; i++) {
        char op_type;
        int arg;
        cin >> op_type >> arg;
        expression_formatter.AddOp({static_cast<OperationType>(op_type), arg});
    }
    return expression_formatter;
}




