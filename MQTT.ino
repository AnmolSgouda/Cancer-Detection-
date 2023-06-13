
#include <WiFiClientSecure.h>
#include <PubSubClient.h> // install with Library Manager, I used v2.6.0

const char* ssid = "Redmi Note 10 Pro"; //Provide your SSID
const char* password = "anmol@1234";   
const char* awsEndpoint = "a2qj72ejotvwiu-ats.iot.eu-north-1.amazonaws.com"; //AWS IoT Core--> Settings (Device data endpoint)

// xxxxxxxxxx-certificate.pem.crt
static const char certificate_pem_crt[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAPmjUyi0WT0XAoWhiN+u90hNa3rtMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzA2MTMxMDQy
NTVaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDhy/pCNkrmPoOza/zt
8Fo6GbZvBeptRKduQX2snG/28eHFZf2MONz7PSZrk/6EZ8Qmi0DP1SRdKO3PlL66
KW/FpaZGYJidS42SNt9DM44hIYh+Xp8rBsHifcA7afvFX8Z9xTJS6A2BG6J2Fkp0
bUFJu1v1bB7qq3Ph4f/FUOHEBubxJ5DX/BsuDtxrUBpKuKEt2scYfuFYDSCRL1s1
PrA5b1WqFoISHlYhTaMSelbnWW+Kr4GFJvFWQM3g9xJw4F1WBLCmtawMgKyFg+wH
b8WbHVlrKGpTxuOWbGKfTS/U/o/3w43ydSQo/fkjjz0RtzM1zoTfJ92p7thNNs5K
opDdAgMBAAGjYDBeMB8GA1UdIwQYMBaAFPjiC6x7E4bX/BCosNZXoYpgZTw4MB0G
A1UdDgQWBBQJrbUPd9yP9t0ZR9iPuQpBPoPS6zAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAaf66+UGsldUIQDoKbBGtMh9+
+Ew84Mk4Wc1eslfJDOE7dBCZN12exdkSCvPxIE1qF0WRXBbVHgbV/hhultcvlCHt
jsIiwIaKsv4YwS64o5L5Fjy/a/ibUTc6874ksjGcuJWdZeaRHH0ev2c54upK6+I9
GU2wazubU10dJjUSXtkDy5/H1hKE6WWDuMVVgUWxyYwbMVG4PqsHaZ8xpdgz45vP
1ZetLODRrwg1z6pixjgHtuaLalgOoYFKBbbxnlat0raLIugl4H+S5U6LHMlbSEHN
K+hZc7kUDVuIAPdBnLanMCuVXDnyyvKN5/908x1h7MmEm0Ih15kSwlXqGz4dhA==
-----END CERTIFICATE-----
)KEY";

// xxxxxxxxxx-private.pem.key
static const char private_pem_key[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEA4cv6QjZK5j6Ds2v87fBaOhm2bwXqbUSnbkF9rJxv9vHhxWX9
jDjc+z0ma5P+hGfEJotAz9UkXSjtz5S+uilvxaWmRmCYnUuNkjbfQzOOISGIfl6f
KwbB4n3AO2n7xV/GfcUyUugNgRuidhZKdG1BSbtb9Wwe6qtz4eH/xVDhxAbm8SeQ
1/wbLg7ca1AaSrihLdrHGH7hWA0gkS9bNT6wOW9VqhaCEh5WIU2jEnpW51lviq+B
hSbxVkDN4PcScOBdVgSwprWsDICshYPsB2/Fmx1ZayhqU8bjlmxin00v1P6P98ON
8nUkKP35I489EbczNc6E3yfdqe7YTTbOSqKQ3QIDAQABAoIBAQDhkABPtqb5/UdZ
rK3+EBZCZj9OB43ZXDUaOohOL/TVr2rH5Iv2UTPIM5026J/gKzzS+Fdlh1oNSn7O
2JvzosNKoaFKOuMad0hU4UYFfvIj/Li67NF6jQSQuuiXMdfWo0fJin4sPi6HZFDW
QIxeZGpNOsKxmDIGYgKgi0EUHyl5xT7lv7ApIlw/yb7pYlUElmXJ1gy//6DNpgBc
CLJR1VuE46LKbQXd25/eUoAe1kbRkvsl6qM/mhntRPTx9vLVmx8tA/+C4mYNILoI
NoqUBX4Tpr+aUblIUMns5mAtbmqQbn2/FzkuDc9+d2vUk2n54pvUPfZG2dPREMTs
dF3M9m5tAoGBAPWgkVC1kZ0OHLebtuQixeQNKpDYjDaoaGnqWdBoyYc49lAJT4UO
rgooNKFAiYMAsMXhJdNP4XE5QAyTRiQ1vpn6HGMQqh2UYuCyd7FlSx80+tpn+Dob
dVfTaiDp9tuae549z4lj+ImqBN6+HB3AVg4SKoDRZ1jwm5e4k96wd4C7AoGBAOtV
BtOwNhUGSm838UbNYp8IlBBL928hx8fSStwmN/mi1FvaSDmLZmOnWT4wZyc2nMnV
D0kCi+AAunixxDp7iKmCARmMiyjuA9/hW2aQE9nneIVFwkjaufraZRN+b13JKjlU
HGTaaXvxszbO43krmKv1EwmXY2+x7bsFdSxevkdHAoGBAMm/Ibw99iUewz2X+2d0
nD/NBKpGAxydxG1CXJTOjMCxa7affx4VyaN0FI5h2NCuD4Pogs4GrW/3CwGJMbJq
JmyIPyqrNF7pUzGlxKQDQ+mU9XnQrdTkWsRRVLlGEkmboG9/62e4ohpIeImPcr6J
DOWvzBNUa+NkdRfwNhxRq0YjAoGAL1sY2JhpCaoOaHsVbm3+HoqXYQAodpCRp0BG
GC8IrI97tFAkoI/QttUCPGV5HIb83hCl1sdQZm8/FvKOzkX1pkam+gEyL7ZVyUOM
JQNxOzQ9KHR1ODvrmPNBy75xoqnMeWTXoePhvjNRIQJY/BUtz8ytXAy+0cc4U54x
ihA2shkCgYEArklnuOVCoXQAXCGz841ILkh0EXmpwfY5jZ+fKCc4iuXahCmSPWTC
4BC/M01lxS+fd0as0Q+PMdeav9xo/yfMOPTGitYEoZwQScdYsGIUJR+LsNRLUXYs
eA7zZKy9RifXRVr3BPmaibvBVGljBE6KnW0E/Gt1q2ih9i3HJBnTcX4=
-----END RSA PRIVATE KEY-----
)KEY";

/* root CA found at:
  https://www.amazontrust.com/repository/AmazonRootCA1.pem
  fungible between regions, I dont care if you use mine below or paste in your own.
*/
static const char rootCA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";


WiFiClientSecure wiFiClient;
void msgReceived(char* topic, byte* payload, unsigned int len);
PubSubClient pubSubClient(awsEndpoint, 8883, msgReceived, wiFiClient); 

void setup() {
  Serial.begin(115200); delay(50); Serial.println();
  Serial.println("ESP32 AWS IoT Example");
  Serial.printf("SDK version: %s\n", ESP.getSdkVersion());

  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  WiFi.waitForConnectResult();
  Serial.print(", WiFi connected, IP address: "); Serial.println(WiFi.localIP());

  wiFiClient.setCACert(rootCA);
  wiFiClient.setCertificate(certificate_pem_crt);
  wiFiClient.setPrivateKey(private_pem_key);
}

unsigned long lastPublish;
int msgCount;

void loop() {

  pubSubCheckConnect();

   //If you need to increase buffer size, you need to change MQTT_MAX_PACKET_SIZE in PubSubClient.h
   char fakeData[128];

  float var1 =  random(55,77); //fake number range, adjust as you like
  float var2 =  random(77,99);
  sprintf(fakeData,  "{\"uptime\":%lu,\"temp\":%f,\"humid\":%f}", millis() / 1000, var1, var2);


  if (millis() - lastPublish > 10000) {
  boolean rc = pubSubClient.publish("outTopic", fakeData);
    Serial.print("Published, rc="); Serial.print( (rc ? "OK: " : "FAILED: ") );
    Serial.println(fakeData);
    lastPublish = millis();

    
  }
}

void msgReceived(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on "); Serial.print(topic); Serial.print(": ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void pubSubCheckConnect() {
  if ( ! pubSubClient.connected()) {
    Serial.print("PubSubClient connecting to: "); Serial.print(awsEndpoint);
    while ( ! pubSubClient.connected()) {
      Serial.print(".");
      pubSubClient.connect("ESPthingXXXX");
      delay(1000);
    }
    Serial.println(" connected");
    pubSubClient.subscribe("inTopic");
  }
  pubSubClient.loop();
}
