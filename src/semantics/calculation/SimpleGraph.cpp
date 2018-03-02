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
double temp = 0;
unordered_map _unordered_map;
result _result;

for(int i=0; i < form.size(); i++)
  insertQuestion(form.at(i),_unordered_map);

for (auto &wordMap : _unordered_map ){
  temp = ( double(wordMap.second.second) / double(wordMap.second.first) );
  _result.push_back(std::make_pair(wordMap.first,temp));
  temp = 0;
}
return _result;

}

}
}
