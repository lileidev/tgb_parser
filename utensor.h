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

#include <iostream>
#include <vector>

#include "dlpack.h"

extern "C" {
namespace tensorglue {
namespace top {

enum UType {
  UTYPE_INVALID = 0,
  UTYPE_BOOL = 1,
  UTYPE_INT = 2,
  UTYPE_FLOAT = 3,
  UTYPE_DOUBLE = 4,
  UTYPE_LONG = 5,
  UTYPE_DLTENSORHANDLE = 6,
  UTYPE_VECTOR_INT64 = 7,
  UTYPE_AXIS = 8,
  UTYPE_VECTOR_AXIS = 9,
  UTYPE_VECTOR_BOOL = 10,
};

union UValue {
  bool v_bool_;
  int32_t v_int32_;
  int64_t v_int64_;
  float v_fp32_;
  double v_fp64_;
  UValue() { p_dl_ = nullptr; }
  UValue(bool value) { v_bool_ = value; }
  UValue(int32_t value) { v_int32_ = value; }
  UValue(int64_t value) { v_int64_ = value; }
  UValue(float value) { v_fp32_ = value; }
  UValue(double value) { v_fp64_ = value; }
  UValue(DLTensor *value) { p_dl_ = value; }
  DLTensor *p_dl_;
  // paddings or strides
  std::vector<int64_t> *p_attrs_;
  std::vector<bool> *p_mask_;
};

struct UTensor {
  UTensor(UType t, UValue v) : type_(t), value_(v) {}
  UTensor() {}
  UType type_;
  UValue value_;

  ~UTensor() {
    if (UTYPE_DLTENSORHANDLE == type_) {
      if (this->value_.p_dl_!=nullptr&&this->value_.p_dl_->malloc_flags) {
        if (nullptr != this->value_.p_dl_->shape) {
          delete this->value_.p_dl_->shape;
          this->value_.p_dl_->shape = nullptr;
        }
        if (nullptr != this->value_.p_dl_->strides) {
          delete this->value_.p_dl_->strides;
          this->value_.p_dl_->strides = nullptr;
        }
      }
      if (nullptr != this->value_.p_dl_) {
        delete this->value_.p_dl_;
        this->value_.p_dl_ = nullptr;
      }
    }
    if (UTYPE_VECTOR_INT64 == type_ || UTYPE_VECTOR_AXIS == type_) {
      delete this->value_.p_attrs_;
      this->value_.p_attrs_ = nullptr;
    }
    if (UTYPE_VECTOR_BOOL == type_) {
      delete this->value_.p_mask_;
      this->value_.p_mask_ = nullptr;
    }
  }

  operator bool() const { return this->value_.v_bool_; }
  operator float() const { return this->value_.v_fp32_; }
  operator double() const { return this->value_.v_fp64_; }
  operator int32_t() const { return this->value_.v_int32_; }
  operator int64_t() const { return this->value_.v_int64_; }
  operator DLTensor *() const { return this->value_.p_dl_; }
  operator std::vector<int64_t> *() const { return this->value_.p_attrs_; }

  operator void *() {
    switch (this->type_) {
      case UTYPE_BOOL: {
        if (this->value_.v_bool_) {
          return &(this->value_.v_bool_);
        } else {
          return nullptr;
        }
      }
      case UTYPE_INT: {
        return &(this->value_.v_int32_);
      }
      case UTYPE_LONG: {
        return &(this->value_.v_int64_);
      }
      case UTYPE_FLOAT: {
        return &(this->value_.v_fp32_);
      }
      case UTYPE_DOUBLE: {
        return &(this->value_.v_fp64_);
      }
      case UTYPE_DLTENSORHANDLE: {
        return this->value_.p_dl_;
      }
      default: {
        std::cout << this->type_ << std::endl;
        throw std::runtime_error("invalid type !");
      }
    }
  }
};

}  // namespace top
}  // namespace tensorglue
}
