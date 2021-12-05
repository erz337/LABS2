// Copyright 2021 Your Name <novikovwarlock@yandex.ru>

#ifndef INCLUDE_INVESTIGATION_HPP_
#define INCLUDE_INVESTIGATION_HPP_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <ctime>

const std::vector <size_t> cachesize{ 256 * 1024,     // L1
                                     2 * 1024 * 1024,   // L2
                                     12 * 1024 * 1024 };// L3
const size_t itr = 1000;

class Cache {
 private:
  std::string _type;
  std::vector <size_t> _buffer_size;      // объём буфера
  std::vector <double> _time;         // время
 public:
  explicit Cache(std::string type = "");
  ~Cache();
  void direct();
  void reverse();
  void random();
  void print(std::ostream& os);
};
void exprmt();

#endif // INCLUDE_INVESTIGATION_HPP_
