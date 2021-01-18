// Copyright 2020 Nikita Klimov nik179804@gmail.com

#include "HeshFunc.hpp"

const size_t TenMB =10 * 1024 * 1024;

void init() {
  //Настройка логирования
  // Файловый логгер, в который записываются результаты с уровнями логгирования
  // trace и info
  auto fileLoggerTrace = boost::log::add_file_log(
      boost::log::keywords::file_name =
          "/home/starich/STARICHDED/SEM3/LAB36/logs/"
          "loggerFileTrace_%N.log",
      boost::log::keywords::rotation_size = TenMB,
      boost::log::keywords::format =
          "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
  // Файловый логгер, в который записываются результаты с уровнем логгирования
  // info
  auto fileLoggerInfo = boost::log::add_file_log(
      boost::log::keywords::file_name =
          "/home/starich/STARICHDED/SEM3/LAB36/logs/"
          "loggerFileInfo.log",
      boost::log::keywords::format =
          "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
  // Консольный логгер, в который записываются результаты с уровнем логгирования
  // info
  auto consoleLogger = boost::log::add_console_log(
      std::cout, boost::log::keywords::format =
          "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");

  //Установка фильтрации
  fileLoggerTrace->set_filter(boost::log::trivial::severity >=
                              boost::log::trivial::trace);
  fileLoggerInfo->set_filter(boost::log::trivial::severity ==
                             boost::log::trivial::info);
  consoleLogger->set_filter(boost::log::trivial::severity ==
                            boost::log::trivial::info);
}

void JSON::addHash(const std::string& data, const std::string& hash,
                   std::time_t timestamp) {
  std::scoped_lock<std::mutex> lock(mut);
  std::stringstream rightData;
  rightData << std::hex << std::uppercase << std::stoi(data);
  json j_map;
  j_map["data"] = rightData.str();
  j_map["hash"] = hash;
  j_map["timestamp"] = timestamp;
  j_array.push_back(j_map);
}
std::ostream& operator<<(std::ostream& out, const JSON& j) {
  std::scoped_lock<std::mutex> lock(j.mut);
  out << j.j_array.dump(4);
  return out;
}
