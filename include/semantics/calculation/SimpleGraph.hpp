#ifndef SEMANTICS_SIMPLEGRAPH_HPP
#define SEMANTICS_SIMPLEGRAPH_HPP

#include <unordered_map>
#include <utility>
#include <vector>
#include <string>

namespace semantics {
namespace core {

  struct reply {
    std::string word;
    int rank;

    reply(std::string _word, int _rank)
    :word(_word),rank(_rank){};
  };

  struct middleResult {
    int occurences;
    int sum;

    middleResult(int _occurences, int _sum)
    :occurences(_occurences),sum(_sum){};
  };

  struct result {
    std::string word;
    float middleRank;
    float frequency;

    result(std::string _word, float _middleRank, float _frequency)
    :word(_word),middleRank(_middleRank),frequency(_frequency){};
  };

  typedef std::vector<std::string> stringVec;
  typedef std::unordered_map<std::string,middleResult> unordered_map;
  typedef std::vector<result> results;

  results Calcul(std::vector<stringVec> form);

}
}
#endif
