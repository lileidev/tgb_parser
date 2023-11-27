#include "driver.h"
#include "parser.h"
#include "tnode.h"
#include <algorithm>
#include <cstddef>
#include <regex>
#include <string>
#include <type_traits>

namespace tensorglue {
namespace parser {

Driver::Driver(const std::vector<std::string> &ins,
               const std::vector<std::string> &outs,
               std::vector<std::string> &fundamentals,
               std::vector<std::string> &compounds,
               std::vector<std::string> &helpers)
  : scanner_(*this), parser_(scanner_, *this)
  , temp_label_id_(0)
  , fundamentals_(fundamentals)
  , compounds_(compounds)
  , helpers_(helpers) {
  for (size_t i = 0; i < ins.size(); ++i) {
    ins_id_idx_map_.emplace(ins[i], "tgb##tmp" + std::to_string(i));
  }
  for (size_t i = 0; i < outs.size(); ++i) {
    outs_id_idx_map_.emplace(outs[i], "tgb##output" + std::to_string(i));
  }
}

Driver::~Driver() {}

int Driver::parse(std::istream& in) {
  scanner_.switch_streams(in, std::cout);
  return parser_.parse();
}

std::string Driver::GetNodeTempName() {
  return "tgb##tmp" + std::to_string(temp_label_id_++);
}

void Driver::StoreMap(TNode *node) {
  temp_map_.emplace(node->node_label_, node);
}

bool Driver::IsStoredValue(const std::string &label) {
  if (temp_map_.count(label)) {
    return true;
  }

  return false;
}

TNode* Driver::GetStoredValue(const std::string &label) {
  return temp_map_.at(label);
}

void Driver::DeleteTree(TNode *node) {
  if (node == nullptr) {
    return;
  }

  for (auto &branch : node->branches_) {
    DeleteTree(branch);
  }

  delete node;
  node = nullptr;
}

TNode* Driver::CloneTree(TNode *node) {
  TNode* new_node = new TNode(node);
  for (auto &branch : new_node->branches_) {
    branch = CloneTree(branch);
  }

  return new_node;
}

void Driver::AddSubTree(TNode *parent, TNode *child) {
  parent->branches_.emplace_back(CloneTree(child));
}

void Driver::SetRoot(TNode* node) {
  root_ = node;
}

TNode* Driver::GetRoot() {
  return root_;
}

void Driver::ReleaseTempMapNodes() {
  for (auto &it : temp_map_) {
    DeleteTree(it.second);
  }
}

bool Driver::IsInput(const std::string &identifier) {
  if (ins_id_idx_map_.count(identifier)) {
    return true;
  }

  return false;
}

bool Driver::IsOutput(const std::string &identifier) {
  if (outs_id_idx_map_.count(identifier)) {
    return true;
  }

  return false;
}

std::string Driver::GetConvertedInputName(const std::string &identifier) {
  return ins_id_idx_map_.at(identifier);
}

std::string Driver::GetConvertedOutputName(const std::string &identifier) {
  return outs_id_idx_map_.at(identifier);
}

OperatorType Driver::GetOpFuncType(const std::string &identifier) {
  if (std::count(fundamentals_.begin(), fundamentals_.end(), identifier)) {
    return OperatorType::FUNDAMENTAL;
  } else if (std::count(compounds_.begin(), compounds_.end(), identifier)) {
    return OperatorType::COMPOUND;
  } else if (std::count(helpers_.begin(), helpers_.end(), identifier)) {
    return OperatorType::HELPER;
  } else if (std::regex_match(identifier, plugin_regex)) {
    return OperatorType::PLUGIN;
  } else {
    return OperatorType::NONE;
  }
}

bool Driver::CheckTree(TNode* node) {
  for (auto &branch : node->branches_) {
    if (!CheckTree(branch)) {
      return false;
    }
  }

  if (node->operator_type_ == OperatorType::NONE) {
    std::cout << "Node " << node->node_label_ << " invalid type!" << std::endl;
    return false;
  }

  return true;
}

void Driver::PrintTree(TNode *root, int depth, bool is_last) {
  if (root == nullptr) {
    return;
  }

  for (int i = 0; i < depth - 1 ; i++) {
    std::cout << (i == 0 ? " " : "|") << "  ";
  }
  if (depth > 0) {
    std::cout << (is_last ? "└──" : "├──");
  }
  if (root->operator_type_ == OperatorType::IN || root->operator_type_ == OperatorType::OUT ||
      root->operator_type_ == OperatorType::INT || root->operator_type_ == OperatorType::DOUBLE) {
    std::cout << root->operator_str_ << std::endl;
  } else {
    std::cout << root->operator_str_ << "(" << root->node_label_ << ") " << root << std::endl;
  }

  for (int i = 0; i < root->branches_.size(); i++) {
    PrintTree(root->branches_[i], depth + 1, i == root->branches_.size() - 1);
  }  
}

}
}
