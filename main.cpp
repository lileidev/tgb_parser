#include <cstddef>
#include <exception>
#include <fstream>
#include <istream>
#include <sstream>
#include <unordered_map>

#include "parser.h"
#include "driver.h"
#include "tnode.h"

#include <yaml-cpp/emitter.h>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/node/iterator.h>


// Remove whitespaces at head and tail
void StringTrim(std::string &str) {
  // Find the first non-whitespace character from the beginning
  auto start = str.begin();
  while (start != str.end() && std::isspace(*start)) {
    ++start;
  }

  // Find the first non-whitespace character from the end
  auto end = str.end();
  while (end != start && std::isspace(*(end - 1))) {
    --end;
  }

  str = std::string(start, end);
}

// Split string with specified seperator
void StringSplit(const std::string &str, const char &split, std::vector<std::string> &res) {
  if (str == "") return;
  std::string strs = str + split;
  size_t pos = strs.find(split);

  std::string temp;
  while (pos != strs.npos) {
    temp = strs.substr(0, pos);
    StringTrim(temp);   // trim spaces
    res.emplace_back(temp);

    strs = strs.substr(pos+1, strs.size());
    pos = strs.find(split);
  }
}

// Operands' and outputs' name cannot be same as tgb_input_symbol and tgb_output_symbol
bool AssertCompoundFuncArgs(const std::vector<std::string> &inputs,
                            const std::vector<std::string> &outputs) {
  auto func = [](const std::vector<std::string> &vec) {
    for (const auto &it : vec) {
      if (std::regex_match(it, input_regex) || std::regex_match(it, output_regex)) {
        std::string message = "Identifier " + it + " is reserved word.";
        return false;
      }
    }
    return true;
  };
  return func(inputs) && func(outputs);
}

void GetNameAndArgsFromSchema(const std::string &schema, std::string &name,
                              std::vector<std::string> &inputs) {
  std::string expr = schema;
  int pos = expr.find_first_of('(');
  name = expr.substr(0, pos);
  expr = expr.substr(pos+1, expr.size());
  pos = expr.find_first_of(')');
  // Get inputs
  std::string inputs_expr = expr.substr(0, pos);
  StringSplit(inputs_expr, ',', inputs);
}

void GetNameAndArgsFromSchema(const std::string &schema, std::string &name,
                                           std::vector<std::string> &inputs, std::vector<std::string> &outputs) {
  std::string expr = schema;
  std::vector<std::string> function_parts;
  StringSplit(expr, '=', function_parts);
  StringSplit(function_parts[0], ',', outputs);
  expr = function_parts[1];
  int pos = expr.find_first_of('(');
  name = expr.substr(0, pos);
  expr = expr.substr(pos+1, expr.size());
  pos = expr.find_first_of(')');
  // Get inputs
  std::string inputs_expr = expr.substr(0, pos);
  StringSplit(inputs_expr, ',', inputs);
}

int main(int argc, char** argv) {
  std::string config_file_path("config.yaml");
  std::ifstream config_file(config_file_path);
  if (!config_file.good()) {
    std::cerr << "Open config file failed!" << std::endl;

    return -1;
  }

  YAML::Node config = YAML::LoadFile(config_file_path);

  YAML::Node fundamentals = config["FundamentalFuncs"];
  YAML::Node helpers = config["HelperFuncs"];
  YAML::Node compounds = config["CompoundFuncs"];

  // Get all fundamental functions
  std::vector<std::string> fundamental_funcs;
  for (const auto &func_node : fundamentals) {
    std::string func = func_node["func"].as<std::string>();
    fundamental_funcs.emplace_back(func);
  }

  // Get all helper functions
  std::vector<std::string> helper_funcs;
  for (const auto &func_node : helpers) {
    std::string func = func_node["func"].as<std::string>();
    helper_funcs.emplace_back(func);
  }

  // Get all compound functions
  std::vector<std::string> compound_funcs;
  for (const auto &func_node : compounds) {
    if (!func_node["func"] || !func_node["expressions"]) {
      std::cout << "Keyword func or expressions not found! Please check fundamental_functions.yaml." << std::endl;
      continue;
    }
    YAML::Node compound_schema = func_node["func"];
    std::string schema = compound_schema.as<std::string>();
    std::string compound_opname;
    std::vector<std::string> compound_operands, compound_outputs;
    GetNameAndArgsFromSchema(schema, compound_opname, compound_operands, compound_outputs);
    compound_funcs.emplace_back(compound_opname);
  }

  for (const auto &func_node : compounds) {
    YAML::Node compound_schema = func_node["func"];
    std::string schema = compound_schema.as<std::string>();
    std::string compound_opname;
    std::vector<std::string> compound_operands, compound_outputs;
    GetNameAndArgsFromSchema(schema, compound_opname, compound_operands, compound_outputs);
    const YAML::Node compound_expr = func_node["expressions"];
    YAML::Emitter emitter;
    emitter << compound_expr;
    std::string expr_str = emitter.c_str();
    std::cout << compound_opname << " expr: " << expr_str << std::endl;
    try {  
      // YY_BUFFER_STATE buffer = yy_scan_string(expr_str.c_str());
      // InitParser(compound_operands, compound_outputs, fundamental_funcs, compound_funcs, helper_funcs);
      tensorglue::parser::Driver driver(compound_operands, compound_outputs, fundamental_funcs, compound_funcs, helper_funcs);
      std::stringstream ss(expr_str);
      driver.parse(ss);
      driver.CheckTree(driver.GetRoot());
      driver.PrintTree(driver.GetRoot(), 0, false);
      driver.DeleteTree(driver.GetRoot());
      // yyparse();
      // yy_delete_buffer(buffer);
    } catch (std::exception &e) {
      std::cout << "Exception: " << e.what() << std::endl;
      break;
    }
  }

  return 0;
}
