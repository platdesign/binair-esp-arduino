#ifndef BINAIR_H
#define BINAIR_H


#include <ESP8266httpUpdate.h>

#ifdef DEBUG_ESP_BINAIR
#ifdef DEBUG_ESP_PORT
#define DEBUG_BINAIR(...) { DEBUG_ESP_PORT.printf("[BINAIR] "); DEBUG_ESP_PORT.printf( __VA_ARGS__ ); }
#endif
#endif

#ifndef DEBUG_BINAIR
#define DEBUG_BINAIR(...)
#endif

// Important: trailing slash
#define BINAIR_API "http://binair.platdesign.de/v1/"
//#define BINAIR_SSL_FINGERPRINT "EA 21 B3 6E 17 A9 5C 82 23 A2 67 B4 68 18 C6 87 D3 36 6F 7E"



class BinairClass;
extern BinairClass Binair;

const char* __BINAIR_MAGIC;
#define BINAIR(vendor, product, token, platform, version) __BINAIR_MAGIC = "\x42\x69\x6e\x41\x69\x72\x5f\x53" \
	vendor "\x3a\x3a" \
	product "\x3a\x3a" \
	token "\x3a\x3a" \
	platform "\x3a\x3a" \
	version "\x42\x69\x6e\x41\x69\x72\x5f\x45"; \
	Binair.__configure(vendor, product, token, platform, version);





class BinairClass {

	public:
		inline void __configure(
			const char* vendor,
			const char* product,
			const char* token,
			const char* platform,
			const char* version
		) {
			this->config.vendor = vendor;
			this->config.product = product;
			this->config.token = token;
			this->config.platform = platform;
			this->config.version = version;
		}


		inline void check() {
			if(millis() - this->lastCheckMillis > this->checkInterval || (
				this->lastCheckMillis == 0 && this->checkInterval > millis()
			)) {
				this->lastCheckMillis = millis();
				this->upgrade();
			}
		}



		inline void upgrade(bool reboot = true) {

			DEBUG_BINAIR("Upgrade fw\n");

			ESPhttpUpdate.rebootOnUpdate(reboot);

			t_httpUpdate_return result = ESPhttpUpdate.update(
				String(BINAIR_API) + this->config.product + "/firmware/" + this->config.platform + "/latest?token=" + this->config.token,
				this->config.version
			);

			switch(result) {
					case HTTP_UPDATE_FAILED:
						DEBUG_BINAIR("failed\n");
						Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
					break;
					case HTTP_UPDATE_NO_UPDATES:
						DEBUG_BINAIR("no update.\n");
					break;
					case HTTP_UPDATE_OK:
						//Serial.println("[update] Update ok."); // may not called we reboot the ESP
					break;
			}


		}


	private:
		uint16_t version;
		uint32_t checkInterval = 3600000; // one hour
		long lastCheckMillis = 0;

		struct {
			const char* vendor;
			const char* product;
			const char* token;
			const char* platform;
			const char* version;
		} config;


		struct {
			const char* version;
			const char* hash;
		} latestVersion;

};

BinairClass Binair;

#endif
