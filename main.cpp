#include <iostream>

#include "weather_library.h"

void print_weather(json WeatherData);

int main(int, char**) {
    std::string city = "Berlin";  // Замените на нужный город
    auto p = getLatLon(city);
    double latitude = p.first;
    double longitude = p.second;

    if (latitude == 0 && longitude == 0) {
        std::cerr << "ERROR in getting coordinates" << std::endl;
    } else {
        json weatherData = getWeatherData(latitude, longitude);
        if (weatherData == NULL)
            std::cerr << "ERROR in getting the weather data" << std::endl;
        else {
            // Вывод информации о погоде
            std::cout << "Погода в городе " << city << ":\n";
            print_weather(weatherData);
        }
    }
    return 0;
}

void print_weather(json WeatherData) {
    short int is_day = WeatherData["current"]["is_day"];
    std::string night_day = ((is_day) ? "День" : "Ночь");
    double temp = WeatherData["current"]["temperature_2m"];
    double app_temp = WeatherData["current"]["apparent_temperature"];
    double hum = WeatherData["current"]["relative_humidity_2m"];
    double precip = WeatherData["current"]["precipitation"];
    double wind = WeatherData["current"]["wind_speed_10m"];
    int code = WeatherData["current"]["weather_code"];
    std::cout << "Сейчас " << night_day << "\n"
              << "На улице " << weather_decoder(code) << "\n"
              << "Температура: " << temp << "°C\n"
              << "Ощущается как: " << app_temp << "°C\n"
              << "Влажность: " << hum << "%\n"
              << "Осадки: " << precip << " мм\n"
              << "Ветер: " << wind << " м/с" << std::endl;
}
