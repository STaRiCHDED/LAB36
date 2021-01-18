// Copyright 2020 Nikita Klimov nik179804@gmail.com

#ifndef INCLUDE_HESHFUNC_H_
#define INCLUDE_HESHFUNC_H_

#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

using json = nlohmann::json;

const char kEndChar[] = "0000";
const size_t kEndCharSize = 4;
void init();

class JSON {
 private:
  mutable std::mutex mut;
  json j_array;

 public:
  void addHash(const std::string& data, const std::string& hash,
               std::time_t timestamp);
  friend std::ostream& operator<<(std::ostream& out, const JSON& j);
};

#endif  // INCLUDE_HESHFUNC_H_
