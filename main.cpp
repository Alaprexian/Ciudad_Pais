#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

// Función auxiliar para eliminar comillas de un string
std::string removeQuotes(const std::string& str) {
    if (str.length() >= 2 && str.front() == '"' && str.back() == '"') {
        return str.substr(1, str.length() - 2);
    }
    return str;
}

struct Location {
  std::string city;
    std::string country;
    double latitude;
    double longitude;
};

float rt=6.371;
float Haversine(float lat1, float long1, float lat2, float long2){
    float lat=lat2-lat1; float lng=long2-long1;
    float a=pow(sin(lat/2),2) + cos(lat1)*cos(lat2)*pow(sin(lng/2),2);
    float c= 2*atan2(sqrt(a), sqrt(1-a));
    return rt*c;    
}

bool busqueda(Location& n1){
  std::string filename = "worldcities.csv";
  
  // Abrir el archivo csv
  std::ifstream file(filename);
  if (!file.is_open()) {
      std::cerr << "Error al abrir el archivo " << filename << std::endl;
      return 1;
  }

  std::string line;
  getline(file, line);
  
  // Leer el archivo línea por línea
  while (std::getline(file, line)) {
      std::stringstream ss(line);
      std::string city, city_ascii, lat_str, lng_str, country, iso2, iso3, admin_name, capital, population, id;

      // Parsear los campos de la línea
      std::getline(ss, city, ',');
      std::getline(ss, city_ascii, ',');
      std::getline(ss, lat_str, ',');
      std::getline(ss, lng_str, ',');
      std::getline(ss, country, ',');
      std::getline(ss, iso2, ',');
      std::getline(ss, iso3, ',');
      std::getline(ss, admin_name, ',');
      std::getline(ss, capital, ',');
      std::getline(ss, population, ',');
      std::getline(ss, id, ',');

      // Eliminar comillas
      city = removeQuotes(city);
      country = removeQuotes(country);
      lat_str = removeQuotes(lat_str);
      lng_str = removeQuotes(lng_str);

      // Convertir los campos a valores numéricos
      float lat = std::stof(lat_str);
      float lng = std::stof(lng_str);
    
      // Comparar con los valores de búsqueda
      if (city == n1.city && country == n1.country) {
          std::cout << "Coincidencia encontrada"<< std::endl;
          n1.latitude=lat; n1.longitude=lng;
        file.close();
        return true;
      }
    }
  
  // Cerrar el archivo
  file.close();
  return false;
  
}

int main() {
    // Nombre del archivo CSV


    // Valores de búsqueda
    std::string search_city1, search_country1, search_city2, search_country2;

    std::cout<<"Ingrese el nombre de la ciudad y pais a calcular:"<<std::endl;
    std::cout<<"Lugar 1"<<std::endl;
    std::cout<<"\tCiudad: "; std::cin>>search_city1; std::cout<<std::endl;
    std::cout<<"\tPais: "; std::cin>>search_country1; std::cout<<std::endl;
    Location l1= {search_city1, search_country1, 0, 0};
    while(!busqueda(l1)){
      std::cout<<"ERROR!, nombre de pais o ciudad incorrecto, intente de nuevo"<<std::endl;
      std::cout<<"Lugar 1"<<std::endl;
      std::cout<<"\tCiudad: "; std::cin>>search_city1; std::cout<<std::endl;
      std::cout<<"\tPais: "; std::cin>>search_country1; std::cout<<std::endl;
      l1= {search_city1, search_country1, 0, 0};
    }
    std::cout<<std::endl;
  
    std::cout<<"Lugar 2"<<std::endl;
    std::cout<<"\tCiudad: "; std::cin>>search_city2; std::cout<<std::endl;
    std::cout<<"\tPais: "; std::cin>>search_country2; std::cout<<std::endl;
    Location l2= {search_city2, search_country2, 0, 0};
    while(!busqueda(l2)){
    std::cout<<"ERROR!, nombre de pais o ciudad incorrecto, intente de nuevo"<<std::endl;
    std::cout<<"Lugar 2"<<std::endl;
    std::cout<<"\tCiudad: "; std::cin>>search_city2; std::cout<<std::endl;
    std::cout<<"\tPais: "; std::cin>>search_country2; std::cout<<std::endl;
    l2= {search_city2, search_country2, 0, 0};
    std::cout<<std::endl;
    }
    std::cout<<"La distancia entre los 2 lugares usando el metodo de Haversine es: "<<Haversine(l1.latitude, l1.longitude, l2.latitude, l2.longitude)<<" km"<<std::endl;

  }