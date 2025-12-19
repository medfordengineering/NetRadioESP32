/*https://npr-ice.streamguys1.com/live.mp3
http://as-hls-ww-live.akamaized.net/pool_01505109/live/ww/bbc_radio_one/bbc_radio_one.isml/bbc_radio_one-audio%3d96000.norewind.m3u8
https://playerservices.streamtheworld.com/api/livestream-redirect/WRJAFM.mp3
https://am820.wnyc.org/wnycam.aac?_gl=1*1mn8wdx*_gcl_au*MjM3MjE1OTM5LjE3NjYxNTEzMDY.
https://fm939.wnyc.org/wnycfm.aac
https://playerservices.streamtheworld.com/api/livestream-redirect/KGOUFM_64.mp3*/

const char *stationPaths[] = {
  "http://www.byte.fm/stream/bytefm.m3u",
  "https://npr-ice.streamguys1.com/live.mp3",
  "https://playerservices.streamtheworld.com/api/livestream-redirect/WRJAFM.mp3",
  "https://fm939.wnyc.org/wnycfm.aac",
  "https://playerservices.streamtheworld.com/api/livestream-redirect/KGOUFM_64.mp3"
};  // Paths to the


#include <WiFi.h>
#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"

#define WIFI_SSID "EngineeringSubNet"
#define WIFI_PASS "password"

#define I2S_DOUT 5
#define I2S_BCLK 6
#define I2S_LRC 9

Audio audio;

void setup() {
  Serial.begin(115200);


  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  // Volume (0-100)
  audio.setVolume(10);
  // Radio stream, e.g. Byte.fm
  //audio.connecttohost("http://www.byte.fm/stream/bytefm.m3u");

  audio.connecttohost(stationPaths[3]);
}

void loop() {
  int limit;
  audio.loop();
  uint16_t station = analogRead(A5);
  for ( limit=0; limit < 500; limit += 20) {
    if ((station > limit) && (station < limit + 5))
      break;
  }
  //station /= 500;
  //station *= 10;
  Serial.println(limit);
  delay(100);
}

// Print station info
void audio_info(const char *info) {
  Serial.print("info        ");
  Serial.println(info);
}
void audio_id3data(const char *info) {  //id3 metadata
  Serial.print("id3data     ");
  Serial.println(info);
}
void audio_eof_mp3(const char *info) {  //end of file
  Serial.print("eof_mp3     ");
  Serial.println(info);
}
void audio_showstation(const char *info) {
  Serial.print("station     ");
  Serial.println(info);
}
void audio_showstreaminfo(const char *info) {
  Serial.print("streaminfo  ");
  Serial.println(info);
}
void audio_showstreamtitle(const char *info) {
  Serial.print("streamtitle ");
  Serial.println(info);
}
void audio_bitrate(const char *info) {
  Serial.print("bitrate     ");
  Serial.println(info);
}
void audio_commercial(const char *info) {  //duration in sec
  Serial.print("commercial  ");
  Serial.println(info);
}
void audio_icyurl(const char *info) {  //homepage
  Serial.print("icyurl      ");
  Serial.println(info);
}
void audio_lasthost(const char *info) {  //stream URL played
  Serial.print("lasthost    ");
  Serial.println(info);
}
void audio_eof_speech(const char *info) {
  Serial.print("eof_speech  ");
  Serial.println(info);
}