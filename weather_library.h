#include <curl/curl.h>

#include <iostream>

#include "single_include/nlohmann/json.hpp"

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
std::pair<double, double> getLatLon(const std::string& city);
json getWeatherData(const double latitude, const double longitude);

std::string weather_decoder(const int code);