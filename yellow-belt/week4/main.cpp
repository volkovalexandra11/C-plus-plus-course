#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
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
  ExpressionFormatter(int first_arg) : first_arg(first_arg) {}

  void AddOp(Operation operation) {
      operations.push_back(operation);
  }

  string ToString() {
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

private:
  int first_arg;
  vector<Operation> operations;
};

void FormatWithBraces() {
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

    cout << expression_formatter.ToString();
}


int main() {
//    cout << "Hello world!" << endl;
    FormatWithBraces();
    return 0;
}
