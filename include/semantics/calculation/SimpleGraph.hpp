#ifndef SEMANTICS_SIMPLEGRAPH_HPP
#define SEMANTICS_SIMPLEGRAPH_HPP

#include <unordered_map>
#include <pair>
#include <vector>
#include <string>
#include <tuple>


/**
 *  stringVec
 *  just represents a word list corresponds to an answer
 */

typedef std::vector<std::string> stringVec;

/**
 *  reply
 *  represents a response composed of:
 *    word
 *    his rank
 */

typedef std::pair<std::string,int> reply;

/**
 *  unordered_map
 *  the calculation data which are composed of:
 *    the std::string representing the word
 *    the std::pair representing the number of occurrences of the word, and the sum of these ranks, so std::pair <occurence, ranks>
 */

typedef std::unordered_map<std::string,std::pair<int,int>> unordered_map;

/**
 *  result
 *  The final result composed of:
 *    The std :: string representing the word in question
 *    The first double representing the middle of the rank
 *    The second double representing the frequency of the word
 */

typedef std::vector<std::tuple<std::string,double,double>> result;

namespace semantics {
namespace core {

result Calcul(std::vector<stringVec> form);

}
}
#endif
