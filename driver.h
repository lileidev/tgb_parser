/* Copyright 2023 The TensorGlue Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#pragma once

#include <unordered_map>

#include "scanner.h"
#include "parser.h"
#include "tnode.h"

namespace tensorglue {
namespace parser {

class Driver {
 public: 
  Driver(const std::vector<std::string> &ins,
         const std::vector<std::string> &outs,
         std::vector<std::string> &fundamentals,
         std::vector<std::string> &compounds,
         std::vector<std::string> &helpers);

  virtual ~Driver();

 public:
  int parse(std::istream &in);
 
 public:
  std::string GetNodeTempName();

  void StoreMap(TNode* node);

  bool IsStoredValue(const std::string &label);

  TNode* GetStoredValue(const std::string &label);

  void DeleteTree(TNode* node);

  TNode* CloneTree(TNode* node);

  void AddSubTree(TNode* parent, TNode* child);

  void SetRoot(TNode* node);

  TNode* GetRoot();

  void ReleaseTempMapNodes();

  bool IsInput(const std::string &identifier);

  bool IsOutput(const std::string &identifier);

  std::string GetConvertedInputName(const std::string &identifier);

  std::string GetConvertedOutputName(const std::string &identifier);

  OperatorType GetOpFuncType(const std::string &identifier);

  bool CheckTree(TNode* node);

  void PrintTree(TNode* root, int depth, bool is_last);

 private:
  Parser parser_;
  Scanner scanner_;

 private:
  TNode* root_;
  int temp_label_id_;
  std::unordered_map<std::string, TNode*> temp_map_;
  std::unordered_map<std::string, std::string> ins_id_idx_map_;
  std::unordered_map<std::string, std::string> outs_id_idx_map_;
  std::vector<std::string> fundamentals_;
  std::vector<std::string> compounds_;
  std::vector<std::string> helpers_;  
};

}  // namespace parser
}  // namespace tensorglue
