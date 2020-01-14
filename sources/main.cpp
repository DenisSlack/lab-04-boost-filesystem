// Copyright 2020 Stitch

#include <FTPA.h>

#include <iostream>

#define dpath "/home/denis/CLionProjects/lab-04-boost-filesystem/misc/ftp"

int main(int argc, char *argv[]) {
  boost::filesystem::path path = "misc/ftp";
  if (argc > 1) path = argv[1];
  FTPA myanalis;
  myanalis.show_directory_analys(path);
  std::cout << "-----------------------------------------------\n";
  myanalis.show_accounts();
}
