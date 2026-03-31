#include <Reader.hpp>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> Reader::getFileName(std::string path) {
  std::filesystem::path data{path};
  std::vector<std::string> namesFound;

  for (auto const &dir_entry : std::filesystem::directory_iterator{data}) {
    namesFound.push_back(dir_entry.path().string());
  }

  return namesFound;
}

Reader::Reader(const std::string &path) : fileNames(getFileName(path)) {}

void Reader::readData() {
  for (const auto &f : fileNames) {
    std::ifstream fs(f);
    std::string mapKey{std::filesystem::path(f).filename().string()};
    std::string line;
    while (std::getline(fs, line)) {
      // NASA Horizons system designates the Start of Ephemeris (SOE) data block
      // with "$$SOE"
      if (line == "$$SOE") {
        // Extract the immediate subsequent line containing the empirical state
        // vectors
        std::getline(fs, line);
        std::stringstream ss(line);
        std::string word;

        // Discard preceding temporal coordinate columns (Julian Date, Calendar
        // Date)
        std::getline(ss, word, ',');
        std::getline(ss, word, ',');

        // Parse Cartesian elements mapping structural transformation from [km]
        // to [m] (SI Units) X-axis celestial coordinate

        std::getline(ss, word, ',');
        datasMap[mapKey][0] = std::stod(word) * 1000.0;

        //  Y-axis celestial coordinate
        std::getline(ss, word, ',');
        datasMap[mapKey][1] = std::stod(word) * 1000.0;

        //  Z-axis celestial coordinate
        std::getline(ss, word, ',');
        datasMap[mapKey][2] = std::stod(word) * 1000.0;

        //  X-axis velocity vector invariant
        std::getline(ss, word, ',');
        datasMap[mapKey][3] = std::stod(word) * 1000.0;

        //  Y-axis velocity vector invariant
        std::getline(ss, word, ',');
        datasMap[mapKey][4] = std::stod(word) * 1000.0;

        //  Z-axis velocity vector invariant
        std::getline(ss, word, ',');
        datasMap[mapKey][5] = std::stod(word) * 1000.0;

        break;
      }
    }
  }
}

const std::map<std::string, std::array<double, 6>> &Reader::getMap() const {
  return datasMap;
}