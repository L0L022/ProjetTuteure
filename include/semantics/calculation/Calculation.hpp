#ifndef SEMANTICS_CALCULATION_HPP
#define SEMANTICS_CALCULATION_HPP

#include <QList>
#include <QString>
#include <QStringList>

struct Calcul{
  QString _word;
  int _occurenceCount
  int _rankList;
  QList<float> _result;

  Calcul(QString word, int rank)
  :_word(word),_occurenceCount(1),_rankList(0),_result(0){
  }

  Calcul::insert(int rank){
    _occurenceCount++;
    _rankList+=rank;
  }

  float Calcul::rankCalculation(){
    _result = _rankList/_occurenceCount;
  }
}

class Calculation {
    static QList<Calcul> SimpleGraph(QList<QStringList> question);
};

#endif
