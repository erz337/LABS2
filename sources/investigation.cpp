// Copyright 2021 Your Name <novikovwarlock@yandex.ru>

#include "investigation.hpp"

Cache::Cache(std::string type)
    : _type(type), _time()
{
  for (size_t i = 0.5 * cachesize[0]; i <= 1.5 * cachesize[2]; i *= 2) {
    _buffer_size.push_back(i);
  }
  _buffer_size.push_back(1.5 * cachesize[2]);
}

Cache::~Cache(){
}

void Cache::direct(){
  [[maybe_unused]]int k = 0;
  for (const size_t size : _buffer_size) {
    int* arr = new int[size / 4];
    for (size_t i = 0; i < size / 4; i += 16) {
      k = arr[i];
    }

    clock_t start = clock();
    for (size_t it = 0; it < itr; it++) {
      for (size_t j = 0; j < size / 4; j += 16) {
        k = arr[j];
      }
    }
    clock_t stop = clock();
    delete[] arr;
    _time.push_back(static_cast<double>(stop - start) / CLOCKS_PER_SEC *
                    1000);
  }
}

void Cache::reverse(){
  [[maybe_unused]]int k = 0;
  for (const size_t size : _buffer_size) {
    int* arr = new int[size / 4];
    for (int i = size / 4; i >= 0; i -= 16) {  //прогрев
      k = arr[i];
    }

    clock_t start = clock();
    for (size_t it = 0; it < itr; it++) {
      for (int j = size / 4; j >= 0; j -= 16) {
        k = arr[j];
      }
    }
    clock_t stop = clock();
    delete[] arr;
    _time.push_back(static_cast<double>(stop - start) / CLOCKS_PER_SEC *
                    1000);
  }
}

void Cache::random(){
  [[maybe_unused]]int k = 0;
  for (const size_t size : _buffer_size) {
    int* arr = new int[size / 4];
    for (size_t i = 0; i < size / 4; i += 16) {
      unsigned int rnd = i;
      k = arr[(rand_r(&rnd) % (size / 4 / 16)) * 16];
    }

    clock_t start = clock();
    for (size_t it = 0; it < itr; it++) {
      for (size_t j = 0; j < size / 4; j += 16) {
        unsigned int rnd = j;
        k = arr[(rand_r(&rnd) % (size / 4 / 16)) * 16];
      }
    }
    clock_t stop = clock();
    delete[] arr;
    _time.push_back(static_cast<double>(stop - start) / CLOCKS_PER_SEC *
                    1000);
  }
}

void Cache::print(std::ostream& os){
  os << "Cache:\n";
  os << "\ttravel order: \"" << _type << "\"\n";
  os << "\texperiments: \n";
  for (size_t i = 0; i < _time.size(); i ++){
    os << "\t- experiment: \n";
    os << "\t\tnumber: " << i + 1 << "\n";
    os << "\t\tinput data: \n";
    int n = _buffer_size[i] >= 1024 * 1024 ? _buffer_size[i] / 1024 / 1024
                                           : _buffer_size[i] / 1024;
    std::string str = _buffer_size[i] >= 1024 * 1024 ? "Mb" : "Kb";
    os << "\t\t\tbuffer size: \"" << n << str << "\"\n";
    double d = _time[i] > 1000 ? _time[i] / 1000 : _time[i];
    str = _time[i] > 1000 ? "s" : "ms";
    os << "\t\tresults: \n";
    os << "\t\t\tduration: \"" << d << str << "\"\n";
  }
  os << "\n";
}
void exprmt(){
  Cache Direction = Cache("direct");
  Direction.direct();
  Direction.print(std::cout);
  Cache Reverse = Cache("reverse");
  Reverse.reverse();
  Reverse.print(std::cout);
  Cache Random = Cache("random");
  Random.random();
  Random.print(std::cout);
}