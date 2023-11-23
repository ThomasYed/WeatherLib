#include "weather_library.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

std::pair<double, double> getLatLon(const std::string& city) {
    std::string geocodeUrl =
        "https://geocoding-api.open-meteo.com/v1/search?name=" + city + "&count=1&language=en&format=json";

    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, geocodeUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return {0.0, 0.0};
        }

        // Обработка JSON-ответа от сервиса геокодирования
        json geocodeData = json::parse(response_string);

        if (geocodeData.contains("results") && !geocodeData["results"].empty()) {
            double latitude = geocodeData["results"][0]["latitude"];
            double longitude = geocodeData["results"][0]["longitude"];
            return {latitude, longitude};
        } else {
            std::cerr << "Unable to retrieve geocode data." << std::endl;
            return {0.0, 0.0};
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return {0.0, 0.0};
}

json getWeatherData(const double latitude, const double longitude) {
    std::string apiUrl =
        "https://api.open-meteo.com/v1/"
        "forecast?latitude=" +
        std::to_string(latitude) + "&longitude=" + std::to_string(longitude) +
        "&current=temperature_2m,relative_humidity_2m,apparent_temperature,is_day,precipitation,weather_code,"
        "wind_speed_10m&wind_speed_unit=ms";

    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    json weatherData = NULL;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        res = curl_easy_perform(curl);

        // Проверка на ошибки
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Обработка JSON-ответа
            // std::cout << response_string << std::endl;
            weatherData = json::parse(response_string);
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return weatherData;
}

std::string weather_decoder(const int code) {
    std::string output;
    switch (code) {
        case 0:
            output = "Ясно";
            break;
        case 1:
            output = "Малооблачно";
            break;
        case 2:
            output = "Облачно";
            break;
        case 3:
            output = "Пасмурно";
            break;
        case 45:
            output = "Туман";
            break;
        case 48:
            output = "Ледяной туман";
            break;
        case 51:
            output = "Морось";
            break;
        case 53:
            output = "Умеренная морось";
            break;
        case 55:
            output = "Сильная морось";
            break;
        case 56:
            output = "Ледяная морось";
            break;
        case 57:
            output = "Сильная ледяная морось";
            break;
        case 61:
            output = "Легкий дождь";
            break;
        case 63:
            output = "Умеренный дождь";
            break;
        case 65:
            output = "Сильный дождь";
            break;
        case 66:
            output = "Ледяной дождь";
            break;
        case 67:
            output = "Сильный ледяной дождь";
            break;
        case 71:
            output = "Слабый снегопад";
            break;
        case 73:
            output = "Умеренный снегопад";
            break;
        case 75:
            output = "Сильный снегопад";
            break;
        case 77:
            output = "Снежные зёрна";
            break;
        case 80:
            output = "Небольшой ливень";
            break;
        case 81:
            output = "Умеренный ливень";
            break;
        case 82:
            output = "Сильный ливень";
            break;
        case 85:
            output = "Снегопад";
            break;
        case 86:
            output = "Сильный снегопад";
            break;
        case 95:
            output = "Гроза";
            break;
        case 96:
            output = "Гроза с небольшим градом";
            break;
        case 99:
            output = "Гроза с сильным градом";
            break;
        default:
            output = "Ошибка";
            break;
    }
    return output;
}