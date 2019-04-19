#include <string>
using namespace std;

class Symbol {
  string name;
  bool terminal;
  public:
  Symbol();
  Symbol(string);
  string getName();
  void setTerminal(bool);
  bool isTerminal();
  bool isEqual(string);
};
