#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266WebServer.h>

const char* ssid = "ND-guest"; // change to your wifi name
const char* password = ""; // change to your wifi password

int ledPin = 2; // GPIO2
WiFiServer server( 80);

void setup() {
 Serial.begin( 115200);
 delay( 10);

 pinMode( ledPin, OUTPUT);
 digitalWrite( ledPin, LOW); // Connect to WiFi network
 Serial.println();
 Serial.println();
 Serial.print(" Connecting to ");
 Serial.println( ssid);

 WiFi.begin( ssid, password);
 while (WiFi.status() != WL_CONNECTED)
 {
 delay( 500); Serial.print(".");
 }
 Serial.println("");
 Serial.println(" WiFi connected");
 // Start the server
 server.begin();
 Serial.println(" Server started");
 // Print the IP address
 Serial.print(" Use this URL to connect: ");
 Serial.print(" http://");
 Serial.print( WiFi.localIP());
 Serial.println("/"); }

 void loop() {
 // Check if a client has connected

 WiFiClient client = server.available();
 if (! client)
 { return; }
 // Wait until the client sends some data
 Serial.println(" new client");
 while(! client.available()){
  delay(1);
  } 
// Read the first line of the request
 String request = client.readStringUntil('\r');
 Serial.println(request);

 client.flush();

// Match the request
 int value = LOW;
 if (request.indexOf("/LED=ON") != -1) {
 digitalWrite( ledPin, HIGH);
 value = HIGH;
 }
 if (request.indexOf("/LED=OFF") != -1) {
 digitalWrite( ledPin, LOW);
 value = LOW;
 }
 // Set ledPin according to the request
 // digitalWrite( ledPin, value); 
 // Return the response

client.println("HTTP/1.1 200 OK");
 client.println("Content-Type:text/html");
 client.println("");
 // do not forget this one
 client.println("<!DOCTYPE html>");
 client.println("<html lang=\"en\">");
 client.println("<head>");
 client.println("<meta charset=\"utf-8\">");
 client.println("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
 client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
 client.println("<meta name=\"description\" content=\"\"><meta name=\"author\" content=\"\">");
 client.println("<link rel=\"icon\" href=\"http://getbootstrap.com/favicon.ico\">");
 client.println("<title>Styled Example</title>");
 client.println("<link href=\"http://getbootstrap.com/dist/css/bootstrap.min.css\" rel=\"stylesheet\">");
 client.println("<link href=\"http://getbootstrap.com/assets/css/ie10-viewport-bug-workaround.css\" rel=\"stylesheet\">");
 client.println("<link href=\"http://getbootstrap.com/examples/starter-template/starter-template.css\" rel=\"stylesheet\">");
 client.println("<!--[if lt IE 9]><script src=\"http://getbootstrap.com/assets/js/ie8-responsive-file-warning.js\"></script><![endif]-->");
 client.println("<script src=\"http://getbootstrap.com/assets/js/ie-emulation-modes-warning.js\"></script>");
 client.println("<!--[if lt IE 9]>");
 client.println("<script src=\"https://oss.maxcdn.com/html5shiv/3.7.3/html5shiv.min.js\"></script>");
 client.println("<script src=\"https://oss.maxcdn.com/respond/1.4.2/respond.min.js\"></script>");
 client.println("<![endif]-->");
 client.println("</head>");
 client.println("<body>");
 client.println("<nav class=\"navbar navbar-inverse navbar-fixed-top\">");
 client.println("<div class=\"container\">");
 client.println("<div class=\"navbar-header\">");
 client.println("<button type=\"button\" class=\"navbar-toggle collapsed\" data-toggle=\"collapse\" data-target=\"#navbar\" aria-expanded=\"false\" aria-controls=\"navbar\">");
 client.println("<span class=\"sr-only\">Toggle navigation</span><span class=\"icon-bar\"></span><span class=\"icon-bar\"></span><span class=\"icon-bar\"></span>");
 client.println("</button><a class=\"navbar-brand\" href=\"#\">Project name</a>");
 client.println("</div>");
 client.println("<div id=\"navbar\" class=\"collapse navbar-collapse\">");
 client.println("<ul class=\"nav navbar-nav\"><li class=\"active\"><a href=\"#\">Home</a></li><li><a href=\"#about\">About</a></li><li><a href=\"#contact\">Contact</a></li></ul>");
 client.println("</div><!--/.nav-collapse -->");
 client.println("</div></nav>");
 client.println("<div class=\"container\">");
 client.println("<div class=\"starter-template\"><h1>Styled Example</h1>");
 client.println("<p class=\"lead\">Use this document as a way to quickly start any new project.<br> All you get is this text and a mostly barebones HTML document.</p>");          
 client.print("<div class=\"alert alert-info\">Led pin is now: ");
 if( value == HIGH) {
 client.print("On"); 
 } else {
  client.print("Off");
 }
 client.println("</div><br/>");
 client.println("<a href=\"/LED=ON\"\"><button class=\"btn btn-success\">Turn On</button></a>"); 
 client.println("<a href=\"/LED=OFF\"\"><button class=\"btn btn-warning\">Turn Off</button></a><br/>");
 client.println("</div></div><!-- /.container -->");  
client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js\"></script>");
client.println("<script src=\"http://getbootstrap.com/dist/js/bootstrap.min.js\"></script>");
client.println("<script src=\"http://getbootstrap.com/assets/js/ie10-viewport-bug-workaround.js\"></script>");
client.println("</body>"); 
client.println("</html>");
 delay(1);
 Serial.println("Client disonnected"); 
 Serial.println("");
}
