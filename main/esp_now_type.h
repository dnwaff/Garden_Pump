#ifndef _ESP_NOW_TYPE_H_
#define _ESP_NOW_TYPE_H_

typedef struct __attribute__((packed)) esp_now_msg_t
{
  uint8_t pmp_start;
  uint16_t pmp_duration;
  uint16_t pmp_duty;
} esp_now_msg_t;

#endif
