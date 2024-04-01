#include <Arduino.h>
#include "Arduino_H7_Video.h"
#include "Arduino_GigaDisplayTouch.h"
#include "lvgl.h"

// Internal Include
#include "display.h"
#include "container.h"

Arduino_H7_Video Display(800, 480, GigaDisplayShield);
Arduino_GigaDisplayTouch TouchDetector;

lv_obj_t *totalInLabel;
lv_obj_t *totalOutLabel;
lv_obj_t *coldFlowRateLabel;
lv_obj_t *hotFlowRateLabel;


/* Slider update value handler */
static void set_slider_val(void *bar, int32_t val) {
  lv_bar_set_value((lv_obj_t *)bar, val, LV_ANIM_ON);
}

void start_display() {
  Display.begin();
  TouchDetector.begin();

  /* Create a container with grid 2x2 */
  static lv_coord_t col_dsc[] = { 370, 370, LV_GRID_TEMPLATE_LAST };
  static lv_coord_t row_dsc[] = { 215, 215, LV_GRID_TEMPLATE_LAST };
  lv_obj_t *cont = lv_obj_create(lv_scr_act());
  lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
  lv_obj_set_size(cont, Display.width(), Display.height());
  lv_obj_set_style_bg_color(cont, lv_color_hex(0x00BBD3), LV_PART_MAIN);
  lv_obj_center(cont);

  lv_obj_t *label;
  lv_obj_t *obj;

  //Top Section
  obj = lv_obj_create(cont);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_STRETCH, 0, 1);
  //Image
  LV_IMG_DECLARE(ThalesLogo);
  lv_obj_t *img1 = lv_img_create(obj);
  lv_img_set_src(img1, &ThalesLogo);
  lv_obj_align(img1, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_set_size(img1, 701, 127);

  //Bottom Left
  obj = lv_obj_create(cont);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,
                       LV_GRID_ALIGN_STRETCH, 1, 1);
  //Amount of water used
  lv_obj_t *totalInTitle = lv_label_create(obj);
  lv_label_set_text_fmt(totalInTitle, "%s", "Total In:");
  lv_obj_align(totalInTitle, LV_ALIGN_CENTER, -60, -50);

  totalInLabel = lv_label_create(obj);
  lv_label_set_text_fmt(totalInLabel, "%s", "0L");
  lv_obj_align(totalInLabel, LV_ALIGN_CENTER, 100, -50);

  //Cost of water
  lv_obj_t *totalOutTitle = lv_label_create(obj);
  lv_label_set_text_fmt(totalOutTitle, "%s", "Total Out:");
  lv_obj_align(totalOutTitle, LV_ALIGN_CENTER, -68, -20);

  totalOutLabel = lv_label_create(obj);
  lv_label_set_text_fmt(totalOutLabel, "%s", "£00.00");
  lv_obj_align(totalOutLabel, LV_ALIGN_CENTER, 100, -20);

  //Cold In
  lv_obj_t *coldFlowRateTitle = lv_label_create(obj);
  lv_label_set_text_fmt(coldFlowRateTitle, "%s", "Cold Flow Rate:");
  lv_obj_align(coldFlowRateTitle, LV_ALIGN_CENTER, -86, 10);

  coldFlowRateLabel = lv_label_create(obj);
  lv_label_set_text_fmt(coldFlowRateLabel, "%s", "0L/min");
  lv_obj_align(coldFlowRateLabel, LV_ALIGN_CENTER, 100, 10);

  //Hot In
  lv_obj_t *hotFlowRateTitle = lv_label_create(obj);
  lv_label_set_text_fmt(hotFlowRateTitle, "%s", "Hot Flow Rate:");
  lv_obj_align(hotFlowRateTitle, LV_ALIGN_CENTER, -84, 40);

  hotFlowRateLabel = lv_label_create(obj);
  lv_label_set_text_fmt(hotFlowRateLabel, "%s", "0L/min");
  lv_obj_align(hotFlowRateLabel, LV_ALIGN_CENTER, 100, 40);

  //Creates button
  /*lv_obj_t * btn = lv_btn_create(obj);
  lv_obj_set_size(btn, 100, 40);
  lv_obj_center(btn);
  lv_obj_add_event(btn, btn_event, LV_EVENT_CLICKED, NULL);
  //Creates label for button
  label = lv_label_create(btn);
  lv_label_set_text(label, "Click me!");
  lv_obj_center(label);*/

  //Bottom Right
  obj = lv_obj_create(cont);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 1, 1,
                       LV_GRID_ALIGN_STRETCH, 1, 1);

  //Creates Slider
  lv_obj_t *slider = lv_slider_create(obj);
  lv_slider_set_value(slider, 75, LV_ANIM_OFF);
  lv_obj_center(slider);
  //Creates label for slider
  label = lv_label_create(obj);
  lv_label_set_text(label, "Drag to select price of water ");
  lv_obj_align_to(label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}

void loop_display(unsigned long &currentMillis) {
  static unsigned long previousRefresh = 0;
  /* Feed LVGL engine - For Display */
  lv_timer_handler();

  // Every second, calculate and print litres/hour
  if (currentMillis - previousRefresh >= 1000) {
    //Sets water used amount
    lv_label_set_text(totalInLabel, String(flowmeter.totalIn).c_str());
    lv_label_set_text(totalOutLabel, String(flowmeter.wasteFlowTotal).c_str());
    lv_label_set_text(coldFlowRateLabel, String(flowmeter.coldFlowRate).c_str());
    lv_label_set_text(hotFlowRateLabel, String(flowmeter.hotFlowRate).c_str());
    // Update last refresh
    previousRefresh = currentMillis;
  }
}
