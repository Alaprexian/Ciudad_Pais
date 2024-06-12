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

float rt=6371;
float Haversine(float lat1, float long1, float lat2, float long2){
    float lat=(lat2-lat1)*M_PI/180; float lng=(long2-long1)*M_PI/180;
    float a=pow(sin(lat/2),2) + cos(lat1*M_PI/180)*cos(lat2*M_PI/180)*pow(sin(lng/2),2);
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

void Test1(){
  std::cout<<"Test 1: \n";
  std::cout<<"Test 1.1: Busqueda de datos de lugar 1:\n";
  //Comprueba si la función busqueda funciona correctamente
  Location n1={"Tokyo" , "Japan", 35.6897, 139.6922};
  Location n2={"Tokyo" , "Japan",0,0};
  busqueda(n2);
    //La diferencia no debe ser mayor a 1e-5
  assert((abs(n1.latitude-n2.latitude)<=pow(10,-5) && abs(n1.longitude-n2.longitude)<=pow(10,-5)));
  std::cout<<"Test 1.1 OK"<<std::endl;

  std::cout<<"\nTest 1.2: Busqueda de datos de lugar 2:\n";
  //Comprueba si la función busqueda funciona correctamente para otro caso
  Location n3={"Delhi" , "India", 28.6100, 77.2300};
  Location n4={"Delhi" , "India",0,0};
  busqueda(n4);
    //La diferencia no debe ser mayor a 1e-5
  assert((abs(n3.latitude-n4.latitude)<=pow(10,-5) && abs(n3.longitude-n4.longitude)<=pow(10,-5)));
  std::cout<<"Test 1.2 OK"<<std::endl;

  std::cout<<"\nTest 1.3: Metodo Haversine:\n";
  //Comprueba si la función Haversine funciona correctamente
    assert((abs(Haversine(n1.latitude,n1.longitude,n3.latitude,n3.longitude)-Haversine(n2.latitude,n2.longitude,n4.latitude,n4.longitude))<=pow(10,-5)));
  std::cout<<"Test 1.3 OK"<<std::endl;
}

void Test2(){
  std::cout<<"\nTest 2: Se entrega datos que no existen\n";
  //Comprueba si la función busqueda funciona correctamente para un caso donde no existe
  Location n2={"Tokyo" , "Japen",0,0};
  assert(!busqueda(n2));  
  std::cout<<"Test 2 OK"<<std::endl;
}

void Test3(){
  std::cout<<"\nTest 3: Se entrega la misma ciudad\n";
  //Comprueba si la función busqueda funciona correctamente para un caso donde la ciudad es la misma
  Location n1={"Tokyo" , "Japan", 35.6897, 139.6922};
  Location n2={"Tokyo" , "Japan",35.6897, 139.6922};
  assert(Haversine(n1.latitude,n1.longitude,n2.latitude,n2.longitude)==0);
  std::cout<<"Test 3 OK"<<std::endl;
}

int main() {
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
