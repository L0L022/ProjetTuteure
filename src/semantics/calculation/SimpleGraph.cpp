#include <semantics/calculation/SimpleGraph.hpp>

namespace semantics {
namespace core {

void insertReply(reply source,unordered_map &_unordered_map){
  if ( _unordered_map.empty()) _unordered_map.emplace(source.rank,std::make_pair(1,source.rank));
  else {
  for(int i=0 ; i < _unordered_map.size(); i++){
      for (auto &wordMap : _unordered_map ){
        if(wordMap.first == source.word ){
          wordMap.second.occurences++;
          wordMap.sum.sum+=source.rank;
        }
        else {
          _unordered_map.emplace(source.rank,middleResult(1,source.rank));
        }
      }
    }
  }
}

void insertQuestion(stringVec source, unordered_map &_unordered_map){
  for(int i=0; i < source.size(); i++)
    insertReply(reply(source.at(i),i+1),_unordered_map);
}


result Calcul(std::vector<stringVec> form){
  double averageRank = 0;
  double frequency = 0;
  double totalOfOccurence = 0;
  unordered_map _unordered_map;
  result _result;

  for(int i=0; i < form.size(); i++)
    insertQuestion(form.at(i),_unordered_map);

  for (auto &wordMap : _unordered_map )
    totalOfOccurence=+wordMap.second.occurences;

  for (auto &wordMap : _unordered_map ){
    averageRank = ( double(wordMap.second.sum) / double(wordMap.second.occurences) );
    frequency = ( double(wordMap.second.sum) / totaloccurence);
    _result.push_back(result(wordMap.first,temp,frequency));
    averageRank = 0;
  }
  return _result;

}

}
}
