#include <curl/curl.h>

#include <fstream>
#include <iostream>

#include "single_include/nlohmann/json.hpp"

int main(int, char **) {
    std::cout << "Hello, from example!\n";

    using json = nlohmann::json;

    json ex1 = json::parse(R"(
  {
    "pi": 3.141,
    "happy": true
  }
)");
    std::cout << ex1["pi"];
}
