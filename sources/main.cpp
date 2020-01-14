// Copyright 2020 Stitch

#include <FTPA.h>

#include <iostream>

#define path "/home/denis/CLionProjects/lab-04-boost-filesystem/misc/ftp"

int main() {
  FTPA myanalis;
  myanalis.show_directory_analys(path);
  std::cout << "-----------------------------------------------\n";
  myanalis.show_accounts();
}
