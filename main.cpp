#include <iostream>
#include <vector>
class Value {
public:
  float data;
  float grad;
  char op;
  char label;
  Value *prev[2];

  Value(float _data, char _label)
      : data(_data), label(_label), grad(0.0), op(' '), prev{} {}
  Value(float _data, char _op, Value *_prev[])
      : data(_data), grad(0.0), op(_op) {
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

using namespace std;

void back_propagate(Value *root) {
  switch (root->op) {
  case '+':
    root->prev[0]->grad = root->grad;
    root->prev[1]->grad = root->grad;
    break;
  case '*':
    root->prev[0]->grad = root->prev[1]->data * root->grad;
    root->prev[1]->grad = root->prev[0]->data * root->grad;
    break;
  default:
    return;
  }

  back_propagate(root->prev[0]);
  back_propagate(root->prev[1]);
}

int main() {
  vector<Value *> topo;

  Value a(4.0, 'A');
  Value b(5.0, 'B');
  Value c(2.0, 'C');

  Value d = a + b;
  Value e = d * c;

  e.grad = 1.0;
  back_propagate(&e);

  cout << b.grad;

  return 0;
}
