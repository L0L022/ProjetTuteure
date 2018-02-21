#ifndef SEMANTICS_CALCULATION_HPP
#define SEMANTICS_CALCULATION_HPP

#include <QList>
#include <QString>
#include <QStringList>

class Calculation {

  struct Calcul{
    QString _word;
    int _occurenceCount;
    int _rankList;
    QList<float> _result;

    Calcul(QString word, int rank)
    :_word(word),_occurenceCount(1),_rankList(0),_result(0){}

    insert(int rank){
      _occurenceCount++;
      _rankList+=rank;
    }

    float rankCalculation(){
      _result = _rankList/_occurenceCount;
    }


  };

  struct SimpleGraph {
    QList<QString> _words;
    QList<float> _result;

    SimpleGraph(QList<QString> words, QList<float> result)
    :_words(words),_result(result){}
  };

    static SimpleGraph simpleGraph(QList<QStringList> question);
};

#endif
