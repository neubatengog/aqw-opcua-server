#include "WeatherData.h"

const utility::string_t weatherserver::WeatherData::KEY_LATITUDE = U("latitude");
const utility::string_t weatherserver::WeatherData::KEY_LONGITUDE = U("longitude");
const utility::string_t weatherserver::WeatherData::KEY_TIMEZONE = U("timezone");
const utility::string_t weatherserver::WeatherData::KEY_ICON = U("icon");
const utility::string_t weatherserver::WeatherData::KEY_TEMPERATURE = U("temperature");
const utility::string_t weatherserver::WeatherData::KEY_APARENT_TEMPERATURE = U("apparentTemperature");
const utility::string_t weatherserver::WeatherData::KEY_HUMIDIY = U("humidity");
const utility::string_t weatherserver::WeatherData::KEY_PRESSURE = U("pressure");
const utility::string_t weatherserver::WeatherData::KEY_WINDSPEED = U("windSpeed");
const utility::string_t weatherserver::WeatherData::KEY_WINDBEARING = U("windBearing");
const utility::string_t weatherserver::WeatherData::KEY_CLOUD_COVER = U("cloudCover");
const utility::string_t weatherserver::WeatherData::KEY_CURRENTLY = U("currently");

char weatherserver::WeatherData::BROWSE_LATITUDE[] = "Latitude";
char weatherserver::WeatherData::BROWSE_LONGITUDE[] = "Longitude";
char weatherserver::WeatherData::BROWSE_TIMEZONE[] = "Timezone";
char weatherserver::WeatherData::BROWSE_ICON[] = "Icon";
char weatherserver::WeatherData::BROWSE_TEMPERATURE[] = "Temperature";
char weatherserver::WeatherData::BROWSE_APPARENT_TEMPERATURE[] = "ApparentTemperature";
char weatherserver::WeatherData::BROWSE_HUMIDITY[] = "Humidity";
char weatherserver::WeatherData::BROWSE_PRESSURE[] = "Pressure";
char weatherserver::WeatherData::BROWSE_WIND_SPEED[] = "WindSpeed";
char weatherserver::WeatherData::BROWSE_WIND_BEARING[] = "WindBearing";
char weatherserver::WeatherData::BROWSE_CLOUD_COVER[] = "CloudCover";

weatherserver::WeatherData::WeatherData(double latitude, double longitude, std::string timezone, std::string icon, 
    double temperature, double apparentTemperature, double humidity, double pressure, double windSpeed, double windBearing, double cloudCover)
    : latitude {latitude}, longitude {longitude}, timezone {timezone}, icon {icon},
    temperature {temperature}, apparentTemperature {apparentTemperature}, pressure {pressure}, 
  humidity{ humidity }, windSpeed{ windSpeed }, windBearing{ windBearing }, cloudCover{ cloudCover }
{}

weatherserver::WeatherData::WeatherData()
    : WeatherData {0, 0, "", "", 0, 0, 0, 0, 0, 0, 0}
{}

weatherserver::WeatherData weatherserver::WeatherData::parseJson(web::json::value & json) {
    double latitude = json.at(KEY_LATITUDE).as_double();
    double longitude = json.at(KEY_LONGITUDE).as_double();
    std::string timezone = utility::conversions::to_utf8string(json.at(KEY_TIMEZONE).as_string()); // Converts from wstring to string

    auto currently = json.at(KEY_CURRENTLY);        

    std::string icon = utility::conversions::to_utf8string(currently.at(KEY_ICON).as_string());
    double temperature = currently.at(KEY_TEMPERATURE).as_double();
    double apparentTemperature = currently.at(KEY_APARENT_TEMPERATURE).as_double();
    double pressure = currently.at(KEY_PRESSURE).as_double();
    double humidity = currently.at(KEY_HUMIDIY).as_double();
    double windSpeed = currently.at(KEY_WINDSPEED).as_double();
    double windBearing; // Not returned if wind speed is 0.
    if (windSpeed > 0.001)
        windBearing = currently.at(KEY_WINDBEARING).as_double();
    else
        windBearing = 0;
    double cloudCover = currently.at(KEY_CLOUD_COVER).as_double();

    return WeatherData(latitude, longitude, timezone, icon, temperature, apparentTemperature,
        humidity, pressure, windSpeed, windBearing, cloudCover);
}