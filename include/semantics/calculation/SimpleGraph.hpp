#ifndef SEMANTICS_SIMPLEGRAPH_HPP
#define SEMANTICS_SIMPLEGRAPH_HPP

#include <unordered_map>
#include <pair>
#include <vector>
#include <string>



/**
 *  stringVec
 *  représente simplement une liste de mot correspond à une réponse
 */

typedef std::vector<std::string> stringVec;

/**
 *  reply
 *  représente une réponse composé de :
 *    le mot
 *    son rang
 */

typedef std::pair<std::string,int> reply;

/**
 *  unordered_map
 *  les données du calcul qui sont composés de :
 *    le std::string représentant le mot en question
 *    le std::pair représentant le nombre d'occurence du mot, et la somme de ces rangs, donc std::pair<occurence,rangs>
 */

typedef std::unordered_map<std::string,std::pair<int,int>> unordered_map;

typedef std::vector<std::pair<std::string,double>> result;

namespace semantics {
namespace core {

result Calcul(std::vector<stringVec> form);

}
}
#endif
