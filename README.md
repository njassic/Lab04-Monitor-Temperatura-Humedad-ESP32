# Laboratorio 04: Monitor de Temperatura y Humedad Inteligente

**Asignatura:** Arquitecturas para Automatización Industrial en la Nube  
**Institución:** Universidad del Valle  
**Plataforma IoT:** ThingSpeak

## 1. Descripción del proyecto

Se implementó un sistema IoT de monitoreo ambiental utilizando un microcontrolador ESP32 y un sensor de temperatura y humedad de la familia DHT.

El sistema adquiere mediciones de temperatura y humedad relativa, controla una alarma LED mediante una condición de temperatura y publica los resultados en ThingSpeak para su visualización remota.

## 2. Objetivo

Implementar un sistema de monitoreo de temperatura y humedad relativa con ESP32, integrando una alarma local y una plataforma IoT para el registro y la visualización de datos.

## 3. Componentes utilizados

- ESP32.
- Módulo Temperature & Humidity V1.2, aparentemente DHT11.
- LED externo.
- Resistencia limitadora de corriente.
- Protoboard y cables de conexión.
- Cable USB.

## 4. Herramientas de software

- Arduino IDE 2.3.7.
- Lenguaje C++.
- Biblioteca DHT de Adafruit.
- Bibliotecas WiFi.h y HTTPClient.h.
- ThingSpeak.
- GitHub.

## 5. Conexiones eléctricas

| Componente | Conexión ESP32 |
|---|---|
| Sensor VCC | 3V3 |
| Sensor GND | GND |
| Sensor SIG | GPIO 18 |
| Sensor NC | Sin conexión |
| LED (ánodo mediante resistencia) | GPIO 4 |
| LED (cátodo) | GND |

## 6. Funcionamiento

1. El ESP32 inicializa el sensor y establece conexión Wi-Fi.
2. Lee la temperatura en grados Celsius y la humedad relativa en porcentaje.
3. Compara la temperatura con un umbral configurado de 30 °C.
4. Si la temperatura supera el umbral, activa el LED.
5. Si la temperatura es igual o inferior al umbral, desactiva el LED.
6. Publica temperatura, humedad y estado de alarma en ThingSpeak mediante HTTP.
7. Las gráficas del canal permiten visualizar los registros.

## 7. Variables del canal ThingSpeak

| Campo | Variable |
|---|---|
| Field 1 | Temperatura_C |
| Field 2 | Humedad_Relativa |
| Field 3 | Estado_Alarma |

La variable Estado_Alarma utiliza 0 para LED apagado y 1 para LED encendido.

## 8. Pruebas realizadas

Se comprobó la adquisición de temperatura y humedad mediante el monitor serie de Arduino IDE.

Se verificó la publicación de datos en ThingSpeak y su representación gráfica.

También se realizó una prueba controlada de activación de la alarma utilizando temporalmente un umbral de 29 °C. Posteriormente se restableció el umbral de 30 °C.

## 9. Resultados observados

Durante las pruebas se registraron temperaturas cercanas a 30 °C y valores de humedad relativa entre 41 % y 44 % en las capturas disponibles.

La plataforma ThingSpeak recibió los datos y permitió visualizar las tres variables.

## 10. Seguridad

Las credenciales Wi-Fi y las claves API deben configurarse localmente y no publicarse en el repositorio.

## 11. Conclusión

La práctica permitió integrar adquisición de datos, procesamiento en un sistema embebido, actuación mediante una salida digital y comunicación con una plataforma IoT en la nube.

El sistema desarrollado constituye un prototipo académico de monitoreo ambiental con alarma de temperatura.
