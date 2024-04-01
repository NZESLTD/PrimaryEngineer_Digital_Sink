// #include <Arduino.h>
// #include "Arduino_H7_Video.h"
// #include "Arduino_GigaDisplayTouch.h"
// #include "lvgl.h"

// // Internal Include
// #include "display.h"

// Arduino_H7_Video Display(800, 480, GigaDisplayShield); 
// Arduino_GigaDisplayTouch  TouchDetector;

// lv_obj_t *amountOfWaterUsedLabel;
// lv_obj_t *costOfWaterUsedLabel;

// /* Slider update value handler */
// static void set_slider_val(void * bar, int32_t val) {
//   lv_bar_set_value((lv_obj_t *)bar, val, LV_ANIM_ON);
// }

// void start_display() {
//   Serial.begin(115200);

//   Display.begin();
//   TouchDetector.begin();

//   /* Create a container with grid 2x2 */
//   static lv_coord_t col_dsc[] = {370, 370, LV_GRID_TEMPLATE_LAST};
//   static lv_coord_t row_dsc[] = {215, 215, LV_GRID_TEMPLATE_LAST};
//   lv_obj_t * cont = lv_obj_create(lv_scr_act());
//   lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
//   lv_obj_set_size(cont, Display.width(), Display.height());
//   lv_obj_set_style_bg_color(cont, lv_color_hex(0x00BBD3), LV_PART_MAIN);
//   lv_obj_center(cont);

//   lv_obj_t * label;
//   lv_obj_t * obj;

//   //Top Section
//   obj = lv_obj_create(cont);
//   lv_obj_set_grid_cell(obj,LV_GRID_ALIGN_STRETCH, 0, 2,LV_GRID_ALIGN_STRETCH, 0,1);
//   //Image
//   LV_IMG_DECLARE(ThalesLogo);
//   lv_obj_t * img1 = lv_img_create(obj);
//   lv_img_set_src(img1, &ThalesLogo);
//   lv_obj_align(img1, LV_ALIGN_LEFT_MID, 0, 0);
//   lv_obj_set_size(img1, 701, 127);

//   //Bottom Left
//   obj = lv_obj_create(cont);
//   lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,
//                         LV_GRID_ALIGN_STRETCH, 1, 1);
//   //Amount of water used
//   lv_obj_t *amountOfWaterUsedTitleLabel = lv_label_create(obj);
//   lv_label_set_text_fmt(amountOfWaterUsedTitleLabel, "%s", "Amount of water used Today");
//   lv_obj_align(amountOfWaterUsedTitleLabel, LV_ALIGN_CENTER,-60,-50);

//   amountOfWaterUsedLabel = lv_label_create(obj);
//   lv_label_set_text_fmt(amountOfWaterUsedLabel, "%s", "0L");
//   lv_obj_align(amountOfWaterUsedLabel, LV_ALIGN_CENTER,100,-50);
//   //Cost of water
//   lv_obj_t *costOfWaterUsedTitleLabel = lv_label_create(obj);
//   lv_label_set_text_fmt(costOfWaterUsedTitleLabel, "%s", "Cost of water used Today");
//   lv_obj_align(costOfWaterUsedTitleLabel, LV_ALIGN_CENTER,-68,-20);

//   costOfWaterUsedLabel = lv_label_create(obj);
//   lv_label_set_text_fmt(costOfWaterUsedLabel, "%s", "£00.00");
//   lv_obj_align(costOfWaterUsedLabel, LV_ALIGN_CENTER,100,-20);

//   //Creates button
//   /*lv_obj_t * btn = lv_btn_create(obj);
//   lv_obj_set_size(btn, 100, 40);
//   lv_obj_center(btn);
//   lv_obj_add_event(btn, btn_event, LV_EVENT_CLICKED, NULL);
//   //Creates label for button
//   label = lv_label_create(btn);
//   lv_label_set_text(label, "Click me!");
//   lv_obj_center(label);*/

//   //Bottom Right
//   obj = lv_obj_create(cont);
//   lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 1, 1,
//                         LV_GRID_ALIGN_STRETCH, 1, 1);
  
//   //Creates Slider
//   lv_obj_t * slider = lv_slider_create(obj);
//   lv_slider_set_value(slider, 75, LV_ANIM_OFF);
//   lv_obj_center(slider);
//   //Creates label for slider
//   label = lv_label_create(obj);
//   lv_label_set_text(label, "Drag to select price of water ");
//   lv_obj_align_to(label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  
// }

// void loop_display(unsigned long &currentMillis, ) { 
//   static unsigned long previousRefresh = 0;
//   /* Feed LVGL engine - For Display */
//   lv_timer_handler();

//   // Every second, calculate and print litres/hour
//   if(currentMillis -  >= (cloopTime + 1000))
//   {
//     //Sets water used amount
//     lv_label_set_text(amountOfWaterUsedLabel, strTotalVolume.c_str());
//     lv_label_set_text(costOfWaterUsedLabel, strTotalCost.c_str());
//     // Update last refresh
//     previousRefresh = currentMillis;
//   }
// }

