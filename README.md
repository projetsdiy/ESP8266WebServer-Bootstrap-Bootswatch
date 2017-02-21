# ESP8266 WebServer + Bootstrap + Bootswatch
How to create a beautifull interface for your ESP8266 project and change theme dynamicaly
* Change theme using Bootswatch CDN
* Display DHT22 and BMP180 measures
* Use GPIO from Web Interface (use Leds to simulate for example)

Libraries used: WiFiClient, ESP8266WebServer, DHT and Adafruit_BMP085
Bootswatch CND : https://www.bootstrapcdn.com/

## Equipment used>

* Any ESP8266 ESP-12 module, for example <a href="http://www.banggood.com/search/esp8266-nodemcu/0-0-0-1-3-45-0-price-0-0_p-1.html?sortType=asc?p=RA18043558422201601Y" target="_blank" rel="nofollow" data-mce-href="http://www.banggood.com/search/esp8266-nodemcu/0-0-0-1-3-45-0-price-0-0_p-1.html?sortType=asc?p=RA18043558422201601Y">Wemos D1 mini</a>
* <a href="http://s.click.aliexpress.com/e/eM72zRrbE" target="_blank" rel="nofollow" data-mce-href="http://s.click.aliexpress.com/e/eM72zRrbE">BMP180</a> : Atmospheric pressure sensor
* <a href="http://s.click.aliexpress.com/e/BeYvjyfim" target="_blank" rel="nofollow" data-mce-href="http://s.click.aliexpress.com/e/BeYvjyfim">DHT22</a> Temperature and humidity sensor

## Wiring
|Sensor |Pin |ESP8266 Pin|
|-------|----|----------:|
|DHT22  |VCC |5V         |
|       |GND |G          |
|       |Data|D4         |
|BMP180 |VCC |5V         |
|       |GND |G          |
|       |SDA |D2         |
|       |SCL |D1         |

## More info
 - Understanding how to program a web server on an ESP8266 : http://www.diyprojects.io/esp8266-web-server-tutorial-create-html-interface-connected-object/
 - How to create beautiful interface with Bootstrap : http://www.diyprojects.io/bootstrap-create-beautiful-web-interface-projects-esp8266/
 - How to change Boootstrap theme with Bootswatch CDN : http://www.diyprojects.io/bootstrap-web-server-esp8266-use-bootswatch-themes/
 
# Interface Bootstrap pour vos projets ESP8266 
Comment créer une interface Web pour vos projets ESP8266
* Changer de thème avec Bootswatch
* Afficher les mesures d'un DHT22 et d'un BMP180
* Comment utiliser le GPIO depuis l'interface Web

## Matériel utilisé
* N'importe quel ESP8266 (ESP-12x), par exemple <a href="http://www.banggood.com/search/esp8266-nodemcu/0-0-0-1-3-45-0-price-0-0_p-1.html?sortType=asc?p=RA18043558422201601Y" target="_blank" rel="nofollow" data-mce-href="http://www.banggood.com/search/esp8266-nodemcu/0-0-0-1-3-45-0-price-0-0_p-1.html?sortType=asc?p=RA18043558422201601Y">Wemos D1 mini</a>
* <a href="http://s.click.aliexpress.com/e/eM72zRrbE" target="_blank" rel="nofollow" data-mce-href="http://s.click.aliexpress.com/e/eM72zRrbE">BMP180</a> : Capteur de pression atmosphérique
* <a href="http://s.click.aliexpress.com/e/BeYvjyfim" target="_blank" rel="nofollow" data-mce-href="http://s.click.aliexpress.com/e/BeYvjyfim">DHT22</a> capteur de température et d'humitité

## Cablage
|Sensor |Broche |Broche ESP8266|
|-------|-------|-------------:|
|DHT22  |VCC    |5V            |
|       |GND    |G             |
|       |Data   |D4            |
|BMP180 |VCC    |5V            |
|       |GND    |G             |
|       |SDA    |D2            |
|       |SCL    |D1            |

## Tutoriels en Français
* Comprendre comment programmer un serveur web sur un ESP8266 : http://www.projetsdiy.fr/esp8266-serveur-web-interface-graphique-html/
* Comment utiliser Bootstrap dans un projet ESP8266 http://www.projetsdiy.fr/bootstrap-esp8266-webserver-interface/
* Comment changer le thème Bootstrap avec les thème Bootswatch : http://www.projetsdiy.fr/bootstrap-bootswatch-webserver-esp8266-personnaliser-theme-defaut/


<img align="center" src="https://github.com/projetsdiy/ESP8266WebServer-Bootstrap-Bootswatch/blob/master/demo-webserver-esp8266-theme-bootstrap.png" style="max-width:100%;">

Licence : MIT

Copyright : www.projetsdiy.fr and www.diyprojects.io
