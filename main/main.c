#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "esp_now.h"
#include "esp_now_type.h"
#include "string.h"
#include "pwm.h"


esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
	uint16_t duty;
	memcpy(&duty,data, data_len);
	ESP_LOGI("MAIN", "on data received");
	if (data_len > 0){
		ESP_LOGI("MAIN", "%d", duty);
		pwm_set_duty(duty);
		pwm_start();
	}
}

void app_main(void)
{
    nvs_flash_init();
    tcpip_adapter_init();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_AP) );

    wifi_config_t ap_config = {
    		.ap = {
    				.ssid = "esp_pump",
    				.password = "password"
    		}
    };
    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_AP, &ap_config) );
    ESP_ERROR_CHECK( esp_wifi_start());
    ESP_ERROR_CHECK(esp_now_init());
    esp_now_register_recv_cb(OnDataRecv);
    //ESP_ERROR_CHECK( esp_wifi_stop());
    init_pwm(GPIO_NUM_5,1000);
}

