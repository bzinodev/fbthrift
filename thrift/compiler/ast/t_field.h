/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <memory>
#include <sstream>
#include <string>

#include <thrift/compiler/ast/t_const_value.h>
#include <thrift/compiler/ast/t_named.h>
#include <thrift/compiler/ast/t_type.h>

namespace apache {
namespace thrift {
namespace compiler {

class t_struct;

/**
 * class t_field
 *
 * Class to represent a field in a thrift structure. A field has a data type,
 * a symbolic name, and a numeric identifier.
 *
 */
class t_field : public t_named {
 public:
  /**
   * Constructor for t_field
   *
   * @param type - A field based on thrift types
   * @param name - The symbolic name of the field
   */
  t_field(t_type* type, std::string name) : t_named(name), type_(type) {}

  /**
   * Constructor for t_field
   *
   * @param type - A field based on thrift types
   * @param name - The symbolic name of the field
   * @param key  - The numeric identifier of the field
   */
  t_field(t_type* type, std::string name, int32_t key)
      : t_named(name), type_(type), key_(key) {}

  t_field(const t_field&) = delete;
  t_field& operator=(const t_field&) = delete;
  t_field(t_field&&) = delete;
  t_field& operator=(t_field&&) = delete;

  ~t_field() {}

  /**
   * Determines if the field is required in the thrift object
   */
  enum e_req {
    T_REQUIRED = 0,
    T_OPTIONAL = 1,
    T_OPT_IN_REQ_OUT = 2,
  };

  /**
   * t_field setters
   */
  void set_value(std::unique_ptr<t_const_value> value) {
    value_ = std::move(value);
  }

  void set_req(e_req req) {
    req_ = req;
  }

  void set_next(t_field* field) {
    next_ = field;
  }

  /**
   * t_field getters
   */
  t_type* get_type() const {
    return type_;
  }

  int32_t get_key() const {
    return key_;
  }

  const t_const_value* get_value() const {
    return value_.get();
  }

  t_const_value* get_value() {
    return value_.get();
  }

  t_field* get_next() const {
    return next_;
  }

  e_req get_req() const {
    return req_;
  }

  /**
   * Thrift AST nodes are meant to be non-copyable and non-movable, and should
   * never be cloned. This method exists to grand-father specific uses in the
   * target language generators. Do NOT add any new usage of this method.
   */
  std::unique_ptr<t_field> clone_DO_NOT_USE() {
    auto clone = std::make_unique<t_field>(type_, name_, key_);

    if (!!value_) {
      clone->value_ = value_->clone();
    }

    clone->next_ = next_;
    clone->req_ = req_;

    return clone;
  }

 private:
  t_type* type_;
  int32_t key_{0};
  std::unique_ptr<t_const_value> value_{nullptr};
  t_field* next_{nullptr};

  e_req req_{T_OPT_IN_REQ_OUT};
};

/**
 * A simple struct for the parser to use to store a field ID, and whether or
 * not it was specified by the user or automatically chosen.
 */
struct t_field_id {
  int64_t value;
  bool auto_assigned;
};

} // namespace compiler
} // namespace thrift
} // namespace apache
