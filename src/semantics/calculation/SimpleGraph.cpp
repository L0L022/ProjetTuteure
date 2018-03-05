#include <semantics/calculation/SimpleGraph.hpp>

namespace semantics {
namespace core {

void insertReply(reply source,unordered_map &_unordered_map){
  if ( _unordered_map.empty()) _unordered_map.emplace(source.first,std::make_pair(1,source.second));
  else {
  for(int i=0 ; i < _unordered_map.size(); i++){
      for (auto &wordMap : _unordered_map ){
        if(wordMap.first == source.first ){
          wordMap.second.first++;
          wordMap.second.second+=source.second;
        }
        else {
          _unordered_map.emplace(source.first,std::make_pair(1,source.second));
        }
      }
    }
  }
}

void insertQuestion(stringVec source, unordered_map &_unordered_map){
  for(int i=0; i < source.size(); i++)
    insertReply(std::make_pair(source.at(i),i+1),_unordered_map);
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
  totalOfOccurence=+wordMap.second.first;

for (auto &wordMap : _unordered_map ){
  averageRank = ( double(wordMap.second.second) / double(wordMap.second.first) );
  frequency = ( double(wordMap.second.first) / totaloccurence);
  _result.push_back(std::tie(wordMap.first,temp,frequency));
  averageRank = 0;
}
return _result;

}

}
}
