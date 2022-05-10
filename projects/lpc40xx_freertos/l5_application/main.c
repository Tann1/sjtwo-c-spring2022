#include <math.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "lcd_driver.h"
#include "mp3.h"
#include "queue.h"
#include "sj2_cli.h"
#include "ssp2_lab.h"
#include "task.h"

static gpio_s cs;

static void task_one(void *task_parameter) {
  // mp3__init(); // mp3.h
  while (1) {
    vTaskDelay(100);
  }
}

int main(void) {
  cs = gpio__construct_as_output(GPIO__PORT_4, 28);
  gpio__set(cs);      // cs is enabled on low so set it to high
  ssp2_lab__init(24); // max 24mhz clk

  gpio__reset(cs); // select
  ssp2_lab__exchange_byte('a');
  gpio__set(cs);
  gpio__reset(cs); // select
  ssp2_lab__exchange_byte('b');
  gpio__set(cs);

  xTaskCreate(task_one, "mp3 init", 1024, NULL, PRIORITY_HIGH, NULL);
  vTaskStartScheduler();
  return 0;
}
