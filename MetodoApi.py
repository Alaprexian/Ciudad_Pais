import requests
import math

# Función para obtener coordenadas de una ciudad y país usando Nominatim API
def obtener_coordenadas(ciudad, pais):
    url = f"https://nominatim.openstreetmap.org/search?q={ciudad},{pais}&format=json"
    respuesta = requests.get(url).json()
    
    # Filtrar la respuesta para obtener el resultado más relevante
    if respuesta:
        # Seleccionar el primer resultado como el más relevante
        resultado = respuesta[0]
        latitud = float(resultado['lat'])
        longitud = float(resultado['lon'])
        return (latitud, longitud)
    else:
        raise Exception("No se encontraron coordenadas para la ciudad especificada.")

# Función para calcular la distancia usando la fórmula de Haversine
def calcular_distancia(coord1, coord2):
    # Radio de la Tierra en kilómetros
    R = 6371.0
    
    lat1, lon1 = coord1
    lat2, lon2 = coord2
    
    dlat = math.radians(lat2 - lat1)
    dlon = math.radians(lon2 - lon1)
    
    a = math.sin(dlat / 2)**2 + math.cos(math.radians(lat1)) * math.cos(math.radians(lat2)) * math.sin(dlon / 2)**2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    
    distancia = R * c
    return distancia

# Clase para representar una ciudad
class Ciudad:
    def __init__(self, nombre_pais, nombre_ciudad):
        self.nombre_pais = nombre_pais
        self.nombre_ciudad = nombre_ciudad
        self.coordenadas = self.obtener_coordenadas()
    
    def obtener_coordenadas(self):
        return obtener_coordenadas(self.nombre_ciudad, self.nombre_pais)

# Función principal
def main():
    ciudad1 = Ciudad("Peru", "Lima")
    ciudad2 = Ciudad("Argentina", "Buenos Aires")
    
    distancia = calcular_distancia(ciudad1.coordenadas, ciudad2.coordenadas)
    print(f"La distancia entre {ciudad1.nombre_ciudad}, {ciudad1.nombre_pais} y {ciudad2.nombre_ciudad}, {ciudad2.nombre_pais} es {distancia:.2f} km")

if __name__ == "__main__":
    main()
