// Copyright 2020 Stitch

#include <boost/filesystem.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = boost::filesystem;

struct time {
  int day;
  int month;
  int year;
};

struct information {
  std::string type, account;
  int num_files = 0;
  struct time times;
};

class FTPA {
  std::vector<information> accounts;

 public:
  FTPA();
  void show_directory_analys(const fs::path p);
  bool check_format(fs::path);
  void accounts_information(const fs::path broker, const fs::path p);
  std::string acc(const fs::path file);
  struct time acc_data(const fs::path file);
  void show_accounts();
};

bool operator>(const struct time& t1, const struct time& t2) {
  if (t1.year > t2.year) return true;
  if (t1.year == t2.year) {
    if (t1.month > t2.month) return true;
    if (t1.month == t2.month) {
      if (t1.day > t2.day)
        return true;
      else
        return false;
    }
  }
  return false;
}

FTPA::FTPA() {}

void FTPA::show_directory_analys(const fs::path p) {
  for (const fs::directory_entry& x : fs::directory_iterator{p}) {
    fs::path brokers = x.path();
    for (const fs::directory_entry& xs : fs::directory_iterator{brokers}) {
      fs::path file = xs.path();
      if (check_format(file)) {
        std::string show =
            brokers.filename().string() + "  " + file.filename().string();
        std::cout << show << std::endl;
        accounts_information(brokers, file);
      }
    }
  }
}

bool FTPA::check_format(fs::path file) {
  if (file.stem().extension() == ".old") return false;
  if (file.extension() != ".txt") return false;

  std::stringstream ss;
  std::string format;
  int i = 0;

  while (file.stem().string()[i] != '_') {
    ss << file.stem().string()[i];
    i++;
  }
  ss >> format;
  if (format != "balance") return false;

  return true;
}

void FTPA::accounts_information(const fs::path broker, const fs::path p) {
  for (size_t i = 0; i < accounts.size(); i++) {
    if (accounts[i].account == acc(p)) {
      accounts[i].num_files++;
      if (acc_data(p) > accounts[i].times) accounts[i].times = acc_data(p);
      return;
    }
  }

  information temp;
  temp.type = broker.filename().string();
  temp.account = acc(p);
  temp.times = acc_data(p);
  temp.num_files++;

  accounts.push_back(temp);
}
std::string FTPA::acc(const fs::path file) {
  std::string temp;
  int i = 9;
  std::stringstream ss;
  while (file.stem().string()[i] != '_') {
    ss << file.stem().string()[i];
    i++;
  }
  ss >> temp;
  return temp;
}

struct time FTPA::acc_data(const fs::path file) {
  struct time temp {};
  std::stringstream ss;

  for (int i = 0; i < 4; i++) {
    ss << file.stem().string()[i + 17];
  }
  ss >> temp.year;
  ss.clear();
  for (int i = 0; i < 2; i++) {
    ss << file.stem().string()[i + 21];
  }
  ss >> temp.month;
  ss.clear();
  for (int i = 0; i < 2; i++) {
    ss << file.stem().string()[i + 23];
  }
  ss >> temp.day;
  return temp;
}
void FTPA::show_accounts() {
  for (size_t i = 0; i < accounts.size(); i++) {
    std::cout << "broker: " << accounts[i].type << "  ";
    std::cout << "account: " << accounts[i].account << "  ";
    std::cout << "files: " << accounts[i].num_files << "  ";
    std::cout << "last data: " << accounts[i].times.year << " "
              << accounts[i].times.month << "  " << accounts[i].times.day
              << std::endl;
  }
}

