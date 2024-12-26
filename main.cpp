#include <iostream>
class Value {
public:
  float data;
  float grad;
  char op;
  Value *prev[2];

  Value(float _data) : data(_data), op(' '), prev{} {}
  Value(float _data, char _op, Value *_prev[]) : data(_data), op(_op) {
    for (int i = 0; i < 2; i++) {
      prev[i] = _prev[i];
    }
  }

  Value operator+(Value &other) {
    Value *parents[] = {this, &other};
    return Value(this->data + other.data, '+', parents);
  }

  Value operator*(Value &other) {
    Value *parents[] = {this, &other};
    return Value(this->data * other.data, '*', parents);
  }
};

int main() {
  Value a(3.0);
  Value b(5.0);

  Value c = a * b;

  std::cout << c.prev[0]->data << std::endl;

  return 0;
}
