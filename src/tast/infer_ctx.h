#pragma once
#include "nodes/core.h"
#include "nodes/type.h"
#include <fmt/core.h>
#include <map>
#include <set>


namespace TAST {
/**
* The inference context is used keep track of which variables are inferenced to the same type
*/
class InferCtx {
private:
  std::map<NodeId, int> nodesToRank;
  std::map<int, Ty> rankTypes;
  int curr_rank = 0;

  std::vector<NodeId> nodesInType(int rank) {
    std::vector<NodeId> nodes;
    for (auto& [key, value] : nodesToRank) {
      if (value == rank) {
        nodes.push_back(key);
      }
    }
    return nodes;
  }
public:
  InferCtx() {}

  void add(NodeId id, Ty ty) {
    nodesToRank[id] = curr_rank++;
    rankTypes[curr_rank] = ty;
  }

  void eq(NodeId id1, NodeId id2) {
    // find 2 sets, and merge them together
    // if they are already in the same set, do nothing
    // if they are in different sets, check if types are compatible
    // otherwise, throw an error
    auto rank1_it = nodesToRank.find(id1);
    auto rank2_it = nodesToRank.find(id2);
    int rank1;
    int rank2;
    if (rank1_it == nodesToRank.end() && rank2_it == nodesToRank.end()) {
      throw std::runtime_error(fmt::format("Both nodes {} and {} are not in the context", id1, id2));
    }
    // if one of them is not in the context, add it to the other's set
    if (rank1_it == nodesToRank.end()) {
      nodesToRank[id1] = rank2_it->second;
    } else {
      rank1 = rank1_it->second;
    }
    if (rank2_it == nodesToRank.end()) {
      nodesToRank[id2] = rank1_it->second;
    } else {
      rank2 = rank2_it->second;
    }

    if (rank1 == rank2) {
      return;
    }

    auto type1 = rankTypes.at(rank1);
    auto type2 = rankTypes.at(rank2);
    auto resolved = type1.resolve(type2);
    if (!resolved.has_value()) {
      throw std::runtime_error("Type mismatch");
    }
    for (auto& [id, rank] : nodesToRank) {
      if (rank == rank2) {
        nodesToRank[id] = rank1;
      }
    }
    rankTypes[rank1] = resolved.value();
    rankTypes.erase(rank2);
  }

  Ty getType(NodeId id) {
    auto rank = nodesToRank.at(id);
    return rankTypes.at(rank);
  }
};
}
