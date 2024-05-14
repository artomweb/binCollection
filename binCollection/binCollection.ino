#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include "secrets.h"
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include <Fonts/FreeMonoBold9pt7b.h>
#include <GxEPD2_3C.h>

#include <TZ.h>
#include <sntp.h>
#include <sys/time.h>
#include <time.h>

// GENERAL 34x50px
const unsigned char epd_bitmap_trash_can_rubbish_bin_simple_modern_icon_design_vector_30112137[] PROGMEM = {
    0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x7f, 0xcc, 0x00, 0x00, 0x00,
    0x70, 0x0c, 0x00, 0x00, 0x00, 0xc0, 0x04, 0x3e, 0x00, 0x00, 0xc0, 0x0f, 0xff, 0x00, 0x00, 0x60,
    0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff,
    0x00, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
    0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x00,
    0x7f, 0xff, 0xff, 0xff, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x3f,
    0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff,
    0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x3c, 0x7f, 0x3f, 0x9f, 0x00, 0x3c, 0x7f, 0x3f,
    0x9f, 0x00, 0x3c, 0x7f, 0x3f, 0x9e, 0x00, 0x3c, 0x7f, 0x3f, 0x9e, 0x00, 0x3c, 0x7f, 0x3f, 0x9e,
    0x00, 0x1e, 0x7f, 0x3f, 0x9e, 0x00, 0x1e, 0x7f, 0x3f, 0x9e, 0x00, 0x1e, 0x7f, 0x3f, 0x9e, 0x00,
    0x1e, 0x7f, 0x3f, 0x1e, 0x00, 0x1e, 0x7f, 0x3f, 0x1e, 0x00, 0x1e, 0x7f, 0x3f, 0x1e, 0x00, 0x1e,
    0x3f, 0x3f, 0x1e, 0x00, 0x1e, 0x3f, 0x3f, 0x1e, 0x00, 0x1e, 0x3f, 0x3f, 0x1e, 0x00, 0x1e, 0x3f,
    0x3f, 0x1e, 0x00, 0x1e, 0x3f, 0x3f, 0x1c, 0x00, 0x1e, 0x3f, 0x3f, 0x3c, 0x00, 0x1e, 0x3f, 0x3f,
    0x3c, 0x00, 0x1f, 0x3f, 0x3f, 0x3c, 0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0xfc,
    0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x00,
    0x07, 0xff, 0xff, 0xf8, 0x00, 0x01, 0xff, 0xff, 0xe0, 0x00};

// FOOD 30x50px
const unsigned char epd_bitmap_20[] PROGMEM = {
    0x00, 0x80, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x00, 0x06, 0x1f, 0xe0, 0x00, 0x06, 0x00, 0x3f, 0x00,
    0x06, 0x00, 0x03, 0x80, 0x06, 0x00, 0x00, 0xc0, 0x06, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x40,
    0x06, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x40,
    0x06, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x40, 0x06, 0x7f, 0xc0, 0x40, 0x07, 0xff, 0xfe, 0x40,
    0x1f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xf8,
    0x3f, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xf0,
    0x3f, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf0,
    0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0,
    0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0,
    0x0f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xe0,
    0x0f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xc0,
    0x0f, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xfe, 0x00,
    0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00};

// RECYCLING 50x50px
const unsigned char epd_bitmap_images[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03,
    0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x07, 0xff, 0xf7, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xdf,
    0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xdf, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xbf, 0xfc, 0x00,
    0x00, 0x00, 0x1f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x7f, 0xfe, 0xe0, 0x00, 0x00,
    0x3f, 0xff, 0x3f, 0xff, 0xc0, 0x00, 0x00, 0x7f, 0xfe, 0x3f, 0xff, 0x80, 0x00, 0x00, 0x7f, 0xfc,
    0x1f, 0xff, 0x80, 0x00, 0x00, 0x7f, 0xfc, 0x1f, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x0f, 0xff,
    0x00, 0x00, 0x00, 0x0f, 0xf8, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x0f, 0xfe, 0x00, 0x00,
    0x7f, 0xf0, 0xe0, 0x1f, 0xfc, 0x00, 0x00, 0x7f, 0xf0, 0x20, 0x07, 0xf8, 0x38, 0x00, 0x1f, 0xf8,
    0x00, 0x00, 0x00, 0x7c, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x1f, 0xfc, 0x00, 0x00,
    0x07, 0xfe, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x3f, 0xff,
    0x00, 0x7f, 0xff, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x1f, 0xff, 0x80, 0xff,
    0xfd, 0x80, 0x00, 0x0f, 0xff, 0x80, 0xff, 0xf8, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0xff, 0xf0, 0x00,
    0x00, 0x07, 0xff, 0xc0, 0x7f, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x3f, 0xe0, 0x00, 0x00, 0x03,
    0xff, 0x80, 0x1f, 0xe0, 0x00, 0x02, 0x01, 0xff, 0x80, 0x2f, 0xc0, 0x00, 0x03, 0x01, 0xff, 0x00,
    0x3d, 0xe1, 0xe0, 0x07, 0x00, 0xff, 0x00, 0x1f, 0xff, 0xfc, 0x07, 0xfe, 0xfe, 0x00, 0x1f, 0xff,
    0xfc, 0x0f, 0xff, 0x7e, 0x00, 0x0f, 0xff, 0xfc, 0x1f, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xfc, 0x1f,
    0xff, 0xbc, 0x00, 0x07, 0xff, 0xfc, 0x3f, 0xff, 0xb8, 0x00, 0x07, 0xff, 0xfc, 0x3f, 0xff, 0xf8,
    0x00, 0x03, 0xff, 0xfc, 0x7f, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xfc, 0x3f, 0xff, 0xe0, 0x00, 0x01,
    0xff, 0xfc, 0x3f, 0xff, 0x80, 0x00, 0x00, 0xff, 0xfc, 0x1f, 0xff, 0x80, 0x00, 0x00, 0x7f, 0xfc,
    0x0f, 0xff, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 272)
const int epd_bitmap_allArray_LEN = 3;
const unsigned char *epd_bitmap_allArray[3] = {
    epd_bitmap_trash_can_rubbish_bin_simple_modern_icon_design_vector_30112137,
    epd_bitmap_20,
    epd_bitmap_images};

// Initializes the display
#define ENABLE_GxEPD2_GFX 0
GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(/*CS=5*/ 15, /*DC=*/4, /*RES=*/5, /*BUSY=*/12)); // GDEM029C90 128x296, SSD1680

#define DISPLAY_WIDTH 296
#define DISPLAY_HEIGHT 128
#define NUM_IMAGES 3

// Wifi clients
WiFiClientSecure client;
HTTPClient http;

// Images and their names
const int imageWidths[3] = {34, 30, 50};
const char *imageNames[3] = {"General", "Food", "Recycling"};
#define IMAGE_HEIGHT 50

// Time stuff
#define MYTZ TZ_Europe_London
bool timeHasBeenSet = false;

// For reading battery voltage
ADC_MODE(ADC_VCC);

// How often the display should refresh
#define SLEEP_TIME 60 * 1 * 1000000
uint64_t sleepForHours = 10;
uint64_t totalDurationSeconds = sleepForHours * 60 * 60;
uint64_t SLEEP_COUNTS_FOR_BIN = totalDurationSeconds * 1000000 / SLEEP_TIME;

extern "C" {
#include "user_interface.h"
}

// Struct saved in rtc memory between deep sleeps
typedef struct {
    uint32_t sleepCount;
    uint16_t wokenBefore;
    bool wifiEnabled = false;
} rtcStore;

#define RTCMEMORYSTART 65

rtcStore rtcMem;

void setup() {
    Serial.begin(115200);
    Serial.println("");

    // delay(1000);

    Serial.println("Waking up...");

    // Read in current state from RTC
    system_rtc_mem_read(RTCMEMORYSTART, &rtcMem, sizeof(rtcMem));

    // If this is the first power-on
    if (rtcMem.wokenBefore != 0xABCD) {
        rtcMem.wokenBefore = 0xABCD;
        Serial.println("Not woken before, initialising to 0");
        rtcMem.sleepCount = 0;
        rtcMem.wifiEnabled = false;
        showBinsOnEINK();

    }
    // else waking up from deep sleep
    else {
        Serial.println("Waking from sleep");
        Serial.print("count = ");
        rtcMem.sleepCount++;
        Serial.println(rtcMem.sleepCount);
    }

    // if it's time to update the display
    if (rtcMem.sleepCount > SLEEP_COUNTS_FOR_BIN - 1) {
        Serial.println("Bin time!");

        if (!rtcMem.wifiEnabled) { // enable wifi on the next reset
            rtcMem.wifiEnabled = true;
            system_rtc_mem_write(RTCMEMORYSTART, &rtcMem, sizeof(rtcMem));
            ESP.deepSleep(SLEEP_TIME, WAKE_RFCAL);
            yield();
        }

        showBinsOnEINK();
    }

    // save the current state
    system_rtc_mem_write(RTCMEMORYSTART, &rtcMem, sizeof(rtcMem));
    yield();

    // Deepsleep and don't wake up with wifi
    ESP.deepSleep(SLEEP_TIME, WAKE_RF_DISABLED);
    yield();
}

void loop() {
}

void showBinsOnEINK() {
    // Make sure WIFI is availiable
    WiFi.forceSleepWake();
    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);

    client.setInsecure();

    Serial.print(ssid);
    Serial.println(" ...");

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        delay(1000);
        Serial.print(++i);
        Serial.print(' ');
        if (i > 30) { // If cannot connect to wifi then reset and try again
            ESP.deepSleep(SLEEP_TIME, WAKE_RFCAL);
            yield();
        }
    }

    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());

    configTime(MYTZ, "pool.ntp.org");
    settimeofday_cb([](bool) {
        setTime();
    });

    while (!timeHasBeenSet) { // wait until we have ntp time
        delay(10);
    }

    time_t now = time(nullptr);

    // Format the current date
    struct tm *timeinfo;
    timeinfo = localtime(&now);

    int day = timeinfo->tm_mday;
    int month = timeinfo->tm_mon + 1; // Month starts from 0, so add 1
    int hour = timeinfo->tm_hour;
    int minute = timeinfo->tm_min;

    String suffix = getOrdinalSuffix(day);
    String monthName = getMonthCode(month);

    String dateTime = String(day) + suffix + " of " + monthName + " " + String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute);

    // Set-up the display
    display.init(115200, true, 50, false);
    display.setRotation(1);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setFullWindow();

    // Get the auth token for the api
    String token = getToken();

    if (token == "") {
        Serial.println("Failed to get token");
        return;
    }

    // Get the bin schedule from the api
    String bins = getBins(token);
    DynamicJsonDocument jsonBuffer(2048);
    DeserializationError error = deserializeJson(jsonBuffer, bins);

    if (error) {
        Serial.println("Failed to parse JSON");
        return;
    }

    JsonObject firstWeek = jsonBuffer["collectionWeeks"][0];

    JsonArray binsArray = firstWeek["bins"];

    String dateString = firstWeek["date"];

    // Format the next collection date
    int firstDash = dateString.indexOf('-');
    int secondDash = dateString.indexOf('-', firstDash + 1);
    int tIndex = dateString.indexOf('T');

    // Extract day and month from the input string
    int colmonth = dateString.substring(firstDash + 1, secondDash).toInt();
    int colday = dateString.substring(secondDash + 1, tIndex).toInt();

    String colsuffix = getOrdinalSuffix(colday);
    String colmonthName = getMonthCode(colmonth);

    String nextCollection = String(colday) + colsuffix + " of " + colmonthName;

    // Get the battery voltage (VCC)
    float volts = ESP.getVcc() / 1000.00;

    int totalImageWidth = 114;
    int imageSpacing = (display.width() - totalImageWidth) / 4;

    // Check which bins are collected outside of the loop so we only have to do it once
    bool binFound[3] = {false};

    for (int i = 0; i < 3; i++) {
        for (JsonObject bin : binsArray) {
            const char *binType = bin["type"];
            if (strcmp(imageNames[i], binType) == 0) {
                binFound[i] = true;
                break; // No need to continue searching if found
            }
        }
    }

    display.firstPage();
    do {
        // Show the dates
        display.setCursor(0, 10);
        display.print("Updated: ");
        display.print(dateTime);
        display.setCursor(0, 30);
        display.print("Next collection:");
        display.print(nextCollection);

        // Show the battery voltage at the bottom
        display.setCursor(0, display.height());
        display.print(volts);
        display.print("V");

        // Display images
        int currentX = imageSpacing;
        for (int i = 0; i < 3; i++) {
            if (binFound[i]) {
                int imageWidth = imageWidths[i];
                int midY = (display.height() - IMAGE_HEIGHT) / 2 + 10;
                display.drawBitmap(currentX, midY, epd_bitmap_allArray[i], imageWidth, IMAGE_HEIGHT, GxEPD_BLACK);
            }
            currentX += imageWidths[i] + imageSpacing; // always put the images in the same place
        }
    } while (display.nextPage());

    rtcMem.sleepCount = 0;
    rtcMem.wifiEnabled = false;
}

String getBins(String token) {

    const char *host = "api.cardiff.gov.uk";
    const char *uri = "/WasteManagement/api/WasteCollection";
    String body = "{\"systemReference\":\"web\",\"language\":\"eng\",\"uprn\":" + String(uprn) + ",\"includecancelled\":true}";

    http.begin(client, host, 443, uri);

    http.addHeader("Content-Type", "application/json; charset=UTF-8");
    http.addHeader("Host", host);
    http.addHeader("origin", "https://www.cardiff.gov.uk");
    http.addHeader("referer", "https://www.cardiff.gov.uk/");
    http.addHeader("Authorization", "Bearer " + token);
    http.addHeader("Content-Length", String(body.length())); // Convert Content-Length to string

    int httpResponseCode = http.POST(body);

    delay(1000);

    if (httpResponseCode > 0) {
        String response = http.getString(); // Get the response
        // Serial.println("HTTP Response code: " + String(httpResponseCode));
        // Serial.println("Response: " + response);
        int startIndex = response.indexOf("{");
        int endIndex = response.lastIndexOf("}");

        if (startIndex >= 0 && endIndex >= 0) {
            String jsonResponse = response.substring(startIndex, endIndex + 1);
            // Serial.println();
            // Serial.println("As json:");
            // Serial.println(jsonResponse);
            return jsonResponse;
        }
    } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    http.end(); // Free resources

    return "";
}

String getToken() {
    const char *host = "authwebservice.cardiff.gov.uk";
    const char *uri = "/AuthenticationWebService.asmx?op=GetJWT";
    const char *body = "<?xml version='1.0' encoding='utf-8'?><soap:Envelope xmlns:soap='http://schemas.xmlsoap.org/soap/envelope/' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:xsd='http://www.w3.org/2001/XMLSchema'><soap:Body><GetJWT xmlns='http://tempuri.org/' /></soap:Body></soap:Envelope>";

    http.begin(client, host, 443, uri);

    http.addHeader("Content-Type", "text/xml; charset=UTF-8"); // Set content type header
    http.addHeader("Host", host);
    http.addHeader("origin", "https://www.cardiff.gov.uk");
    http.addHeader("referer", "https://www.cardiff.gov.uk/");
    http.addHeader("Content-Length", String(strlen(body))); // Convert Content-Length to string

    int httpResponseCode = http.POST(body); // Make POST request with body

    if (httpResponseCode > 0) {
        String response = http.getString(); // Get the response
        // Serial.println("HTTP Response code: " + String(httpResponseCode));
        // Serial.println("Response: " + response);

        int tokenIndex = response.indexOf("\"access_token\":\"");
        if (tokenIndex != -1) {
            int tokenEndIndex = response.indexOf("\"", tokenIndex + 16);
            return response.substring(tokenIndex + 16, tokenEndIndex);
        }
    }

    else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    http.end(); // Free resources

    return "";
}

void setTime() {
    timeHasBeenSet = true;
    time_t now = time(nullptr);
    Serial.println("Time set");
}

String getOrdinalSuffix(int day) {
    if (day >= 11 && day <= 13) {
        return "th";
    }
    switch (day % 10) {
    case 1:
        return "st";
    case 2:
        return "nd";
    case 3:
        return "rd";
    default:
        return "th";
    }
}

String getMonthCode(int month) {
    switch (month) {
    case 1:
        return "Jan";
    case 2:
        return "Feb";
    case 3:
        return "Mar";
    case 4:
        return "Apr";
    case 5:
        return "May";
    case 6:
        return "Jun";
    case 7:
        return "Jul";
    case 8:
        return "Aug";
    case 9:
        return "Sep";
    case 10:
        return "Oct";
    case 11:
        return "Nov";
    case 12:
        return "Dec";
    default:
        return "Inv";
    }
}
