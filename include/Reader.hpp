#include <array>
#include <map>
#include <string>
#include <vector>
class Reader {
private:
  std::map<std::string, std::array<double, 6>> datasMap;
  std::vector<std::string> fileNames;
  static std::vector<std::string> getFileName(std::string path);

public:
  Reader(const std::string &path);
  void readData();
  const std::map<std::string, std::array<double, 6>> &getMap() const;
};