/* Bootstrap Interface for ESP8266 projects
 * Change theme using Bootswatch CDN
 * Display DHT22 and BMP180 measures
 * Use GPIO from Web Interface (use Leds to simulate for example)
 * 
 * Libraries used :WiFiClient, ESP8266WebServer, DHT and Adafruit_BMP085
 *  
 * More info 
 * - Understanding how to program a web server on an ESP8266 : http://www.diyprojects.io/esp8266-web-server-tutorial-create-html-interface-connected-object/
 * - How to create beautiful interface with Bootstrap : http://www.diyprojects.io/bootstrap-create-beautiful-web-interface-projects-esp8266/
 * - How to change Boootstrap theme with Bootswatch CDN : http://www.diyprojects.io/bootstrap-web-server-esp8266-use-bootswatch-themes/
 * 
 * Créer une interface Web pour vos projets ESP8266
 * Changer de thème avec Bootswatch
 * Afficher les mesures d'un DHT22 et d'un BMP180
 * Comment utiliser le GPIO depuis l'interface Web
 * 
 * Tutoriels en Français
 * - Comprendre comment programmer un serveur web sur un ESP8266 : http://www.projetsdiy.fr/esp8266-serveur-web-interface-graphique-html/
 * - Comment utiliser Bootstrap dans un projet ESP8266 http://www.projetsdiy.fr/bootstrap-esp8266-webserver-interface/
 * - Comment changer le thème Bootstrap avec les thème Bootswatch : http://www.projetsdiy.fr/bootstrap-bootswatch-webserver-esp8266-personnaliser-theme-defaut/
 * 
 * Licence : MIT
 * Copyright : www.projetsdiy.fr and www.diyprojects.io
*/
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

#define ssid      "yourSSID"      // WiFi SSID
#define password  "yourPASSWORD"  // WiFi password
#define DHTTYPE   DHT22           // DHT type (DHT11, DHT22)
#define DHTPIN    D4              // Broche du DHT - DHT Pin
const uint8_t GPIOPIN[4] = {D5,D6,D7,D8};  // Broches Led - Led Pins
float   t = 0 ;
float   h = 0 ;
float   p = 0;
String  etatGpio[4] = {"OFF","OFF","OFF","OFF"};
String  theme = "bootstrap";

// Création des objets - create Objects
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
ESP8266WebServer server ( 80 );

String getPage(){
  // Renvoi une chaine contenant le code HTML de la page - Return a string containing the HTML code of the page
  String page = "<html charset=UTF-8><head><meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1'/>";
  page += "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>";
  if ( theme == "bootstrap" ) {
    page += "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>";
  } else {
    page += "<link href='https://maxcdn.bootstrapcdn.com/bootswatch/3.3.7/";
    page += theme;
    page += "/bootstrap.min.css' rel='stylesheet'>";
  }
  page += "<title>ESP8266 Demo - www.projetsdiy.fr</title></head><body>";
  page += "<div class='container-fluid'>";
  page +=   "<div class='row'>";
  page +=     "<div class='col-md-12'>";
  page +=       "<h1>Demo Webserver ESP8266 + Bootstrap</h1>";
  page +=       "<h3>Mini station m&eacute;t&eacute;o</h3>";
  page +=       "<ul class='nav nav-pills'>";
  page +=         "<li class='active'>";
  page +=           "<a href='#'> <span class='badge pull-right'>";
  page +=           t;
  page +=           "</span> Temp&eacute;rature</a>";
  page +=         "</li><li>";
  page +=           "<a href='#'> <span class='badge pull-right'>";
  page +=           h;
  page +=           "</span> Humidit&eacute;</a>";
  page +=         "</li><li>";
  page +=           "<a href='#'> <span class='badge pull-right'>";
  page +=           p;
  page +=           "</span> Pression atmosph&eacute;rique</a></li>";
  page +=       "</ul>";
  page +=       "<table class='table'>";  // Tableau des relevés
  page +=         "<thead><tr><th>Capteur</th><th>Mesure</th><th>Valeur</th><th>Valeur pr&eacute;c&eacute;dente</th></tr></thead>"; //Entête
  page +=         "<tbody>";  // Contenu du tableau - Table content
  page +=           "<tr><td>DHT22</td><td>Temp&eacute;rature</td><td>"; // Première ligne : température - First line : temperature
  page +=             t;
  page +=             "&deg;C</td><td>";
  page +=             "-</td></tr>";
  page +=           "<tr class='active'><td>DHT22</td><td>Humidit&eacute;</td><td>"; // 2nd ligne : Humidité - 2nd line : humidity
  page +=             h;
  page +=             "%</td><td>";
  page +=             "-</td></tr>";
  page +=           "<tr><td>BMP180</td><td>Pression atmosph&eacute;rique</td><td>"; // 3ème ligne : PA (BMP180) - 3th line : atmospheric pressure
  page +=             p;
  page +=             "mbar</td><td>";
  page +=             "-</td></tr>";
  page +=       "</tbody></table>";
  page +=       "<h3>GPIO</h3>";
  page +=       "<div class='row'>";
  page +=         "<div class='col-md-4'><h4 class ='text-left'>D5 ";
  page +=           "<span class='badge'>";
  page +=           etatGpio[0];
  page +=         "</span></h4></div>";
  page +=         "<div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D5' value='1' class='btn btn-success btn-lg'>ON</button></form></div>";
  page +=         "<div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D5' value='0' class='btn btn-danger btn-lg'>OFF</button></form></div>";
  page +=         "<div class='col-md-4'><h4 class ='text-left'>D6 ";
  page +=           "<span class='badge'>";
  page +=           etatGpio[1];
  page +=         "</span></h4></div>";
  page +=         "<div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D6' value='1' class='btn btn-success btn-lg'>ON</button></form></div>";
  page +=         "<div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D6' value='0' class='btn btn-danger btn-lg'>OFF</button></form></div>";
  page +=         "<div class='col-md-4'><h4 class ='text-left'>D7 ";
  page +=           "<span class='badge'>";
  page +=           etatGpio[2];
  page +=         "</span></h4></div>";
  page +=         "<div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D7' value='1' class='btn btn-success btn-lg'>ON</button></form></div>";
  page +=         "<div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D7' value='0' class='btn btn-danger btn-lg'>OFF</button></form></div>";
  page +=         "<div class='col-md-4'><h4 class ='text-left'>D8 ";
  page +=           "<span class='badge'>";
  page +=           etatGpio[3];
  page +=         "</span></h4></div>";
  page +=         "<div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D8' value='1' class='btn btn-success btn-lg'>ON</button></form></div>";
  page +=         "<div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D8' value='0' class='btn btn-danger btn-lg'>OFF</button></form></div>";
  page +=       "</div>";
  page +=   "<div class='row'>";
  page +=     "<div class='col-md-4'>";
  page +=       "<form method='POST' name='selecttheme' id='selecttheme'/>"; 
  page +=       "<input class='span' id='choixtheme' name='theme' type='hidden'>";
  page +=       "<div class='btn-group'>";
  page +=         "<button class='btn btn-default'>Choisir un th&eacute;me</button>";
  page +=         "<button data-toggle='dropdown' class='btn btn-default dropdown-toggle'><span class='caret'></span></button>";
  page +=         "<ul class='dropdown-menu'>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"bootstrap\"); $(\"#selecttheme\").submit()'><a href='#'>Boostrap</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"cerulean\"); $(\"#selecttheme\").submit()'><a href='#'>Cerulean</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"cosmo\"); $(\"#selecttheme\").submit()'><a href='#'>Cosmo</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"cyborg\"); $(\"#selecttheme\").submit()'><a href='#'>Cyborg</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"darkly\"); $(\"#selecttheme\").submit()'><a href='#'>Darkly</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"flatly\"); $(\"#selecttheme\").submit()'><a href='#'>Flatly</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"journal\"); $(\"#selecttheme\").submit()'><a href='#'>Journal</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"lumen\"); $(\"#selecttheme\").submit()'><a href='#'>Lumen</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"paper\"); $(\"#selecttheme\").submit()'><a href='#'>Paper</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"readable\"); $(\"#selecttheme\").submit()'><a href='#'>Readable</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"sandstone\"); $(\"#selecttheme\").submit()'><a href='#'>Sandstone</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"simplex\"); $(\"#selecttheme\").submit()'><a href='#'>Simplex</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"slate\"); $(\"#selecttheme\").submit()'><a href='#'>Slate</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"spacelab\"); $(\"#selecttheme\").submit()'><a href='#'>Spacelab</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"superhero\"); $(\"#selecttheme\").submit()'><a href='#'>Superhero</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"united\"); $(\"#selecttheme\").submit()'><a href='#'>United</a></li>";
  page +=           "<li onclick='$(\"#choixtheme\").val(\"yeti\"); $(\"#selecttheme\").submit()'><a href='#'>Yeti</a></li>";
  page +=         "</ul>";
  page +=       "</div>";
  page +=       "</form></div>";
  page +=       "<div class='col-md-8'>";
  page +=         "<p><a href='http://www.projetsdiy.fr'>Version francaise : www.projetsdiy.fr</p>";
  page +=         "<p><a href='http://www.diyprojects.io'>English version : www.diyprojects.io</p>";
  page +=       "</div>";
  page +=   "</div>"; 
  page += "</div></div></div>";
  page += "</body></html>";
  return page;
}
void handleRoot(){ 
  if ( server.hasArg("theme") ) {
    handleTheme();
  } else if ( server.hasArg("D5") ) {
    handleD5();
  } else if ( server.hasArg("D6") ) {
    handleD6();
  } else if ( server.hasArg("D7") ) {
    handleD7();
  } else if ( server.hasArg("D8") ) {
    handleD8();
  } else {
    server.send ( 200, "text/html", getPage() );
  }  
}

void handleTheme(){
  theme = server.arg("theme");
  Serial.println("Update theme : "); Serial.print(theme);  
  server.send ( 200, "text/html", getPage() );
}

void handleD5() {
  String D5Value; 
  updateGPIO(0,server.arg("D5")); 
}

void handleD6() {
  String D6Value; 
  updateGPIO(1,server.arg("D6")); 
}

void handleD7() {
  String D7Value; 
  updateGPIO(2,server.arg("D7")); 
}

void handleD8() {
  String D8Value; 
  updateGPIO(3,server.arg("D8")); 
}

void updateGPIO(int gpio, String DxValue) {
  Serial.println("");
  Serial.println("Update GPIO "); Serial.print(GPIOPIN[gpio]); Serial.print(" -> "); Serial.println(DxValue);
  
  if ( DxValue == "1" ) {
    digitalWrite(GPIOPIN[gpio], HIGH);
    etatGpio[gpio] = "On";
    server.send ( 200, "text/html", getPage() );
  } else if ( DxValue == "0" ) {
    digitalWrite(GPIOPIN[gpio], LOW);
    etatGpio[gpio] = "Off";
    server.send ( 200, "text/html", getPage() );
  } else {
    Serial.println("Err Led Value");
  }  
}

void setup() {
  for ( int x = 0 ; x < 5 ; x++ ) { 
    pinMode(GPIOPIN[x],OUTPUT);
  }  
  Serial.begin ( 115200 );
  // Initialisation du BMP180 - Init BMP180 sensor
  if ( !bmp.begin() ) {
    Serial.println("BMP180 KO!");
    while(1);
  } else {
    Serial.println("BMP180 OK");
  }
  
  WiFi.begin ( ssid, password );
  // Attente de la connexion au réseau WiFi - Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 ); Serial.print ( "." );
  }
  // Connexion WiFi établie - WiFi connexion is OK
  Serial.println ( "" ); 
  Serial.print ( "Connected to " ); Serial.println ( ssid );
  Serial.print ( "IP address: " ); Serial.println ( WiFi.localIP() );

  // On branche la fonction qui gère la premiere page / Endpoints for HTTP server
  server.on ( "/", handleRoot );

  server.begin();
  Serial.println ( "HTTP server started" );
  
}

void loop() {
  // Vérifie régulièrement la connexion d'un nouveau client - check for incomming client connections frequently
  server.handleClient();
  t = dht.readTemperature();
  h = dht.readHumidity();
  p = bmp.readPressure() / 100.0F;

  delay(1000);
}
