#include <semantics/calculation/Calculation.hpp>

static SimpleGraph simpleGraph(QList<QStringList> question){

  int indexOfOccurence(QString word, QList<calcul>& averageTermRank){ // return l'index du mot dans le calcul, retourne -1 si n'existe pas encore
    for(int i = 0; i < averageTermRank->size(); i++){
      if(averageTermRank->at(i)->word == word)
        return i;
    }
    return -1;
  }

  QList<Calcul> averageTermRank;
  QList<int> temp;
  int index;

  for( int i = 0; i < question.size() ; i++ ){                        // Pour tout les chaques questions
    for ( int j = 0; j < question.at(i).size() ; j++){                // Pour tout les listes de mots
      if(question.at(i).at(j) != ""){                                 // si le mot est vide ignoré
        if(index = isCreate(question.at(i).at(j),&averageTermRank) == -1){
          averageTermRank.pushback(Calcul(question.at(i).at(j),j));
        } else {
          averageTermRank.at(index).insert(j);
        }
      }
    }
  }

  for ( int i = 0; i < averageTermRank.size() < i++ ){
      averageTermRank.at(i).rankCalculation();
  }

return SimpleGraph(averageTermRank._words,averageTermRank._result);

}
