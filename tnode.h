#pragma once 

#include <cstddef>
#include <vector>
#include <string>
#include <unordered_map>
#include <regex>

#include "utensor.h"

namespace tensorglue {
namespace top {

enum OperatorType {
  NONE,
  IN,
  OUT,
  INT,
  DOUBLE,
  FUNDAMENTAL,
  COMPOUND,
  HELPER,
  PLUGIN,
  IF,
  FOR,
  COMPOUNDOUTPUTS
};

const std::regex plugin_regex("^plugin_.+$");
const std::regex input_regex("^tgb##input\\d+$");
const std::regex output_regex("^tgb##output\\d+$");

struct TNode {
  std::string node_label_;
  std::string operator_str_;
  OperatorType operator_type_;
  std::vector<TNode*> branches_;

  std::vector<UTensor*> tensor_values_;

  TNode(const std::string &label)
    : node_label_(label) {}

  TNode(const std::string &label,
        const std::string &op_str)
    : node_label_(label)
    , operator_str_(op_str) {}

  TNode(const std::string &label,
        const std::string &op_str,
        const OperatorType &type)
    : node_label_(label)
    , operator_str_(op_str)
    , operator_type_(type) {}

  TNode(const std::string &label,
        const std::string &op_str,
        const OperatorType &type,
        TNode* node)
    : node_label_(label)
    , operator_str_(op_str)
    , operator_type_(type) {
      branches_.emplace_back(node);
    }

  TNode(const std::string &label,
        const std::string &op_str,
        const OperatorType &type,
        const std::vector<TNode*> &nodes)
    : node_label_(label)
    , operator_str_(op_str)
    , operator_type_(type)
    , branches_(nodes) {}

  TNode(TNode *node)
    : node_label_(node->node_label_)
    , operator_str_(node->operator_str_)
    , operator_type_(node->operator_type_)
    , branches_(node->branches_) {}

  ~TNode() {}
};

}  // namespace top
}  // namespace tensorglue
