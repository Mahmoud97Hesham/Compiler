#include "Symbol.h"

Symbol::Symbol() {
  name = "";
  terminal = false;
}

Symbol::Symbol(string _name) {
  name = _name;
  terminal = false;
}

string Symbol::getName() {
  return name;
}

void Symbol::setTerminal(bool _terminal) {
  terminal = _terminal;
}

bool Symbol::isTerminal() {
  return terminal;
}
