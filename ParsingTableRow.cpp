#include "ParsingTableRow.h"

ParsingTableRow::ParsingTableRow(Symbol _nonTerminal) {
  nonTerminal = _nonTerminal;
}

void ParsingTableRow::addEntry(SymbolsSet ss, Symbol terminal) {
  terminals.push_back(terminal);
  row.push_back(ss);
}

bool ParsingTableRow::equals(Symbol _nonTerminal) {
  return nonTerminal.isEqual(_nonTerminal.getName());
}

vector<Symbol> ParsingTableRow::getCorrespondingSymbols(Symbol terminal) {
  for(int i = 0; i < terminals.size(); ++i) {
    if(terminals[i].isEqual(terminal.getName())) return row[i].getSymbolsVector();
  }
  return vector<Symbol>();
}
