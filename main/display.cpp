#include "Arduino_H7_Video.h"
#include "lvgl.h"
#include "Arduino_GigaDisplayTouch.h"

Arduino_H7_Video Display(800, 480, GigaDisplayShield);
Arduino_GigaDisplayTouch TouchDetector;

void start_display() {
  Display.begin();
  TouchDetector.begin();

  //Display & Grid Setup
  lv_obj_t* screen = lv_obj_create(lv_scr_act());
  lv_obj_set_size(screen, Display.width(), Display.height());

  static lv_coord_t col_dsc[] = { 370, 370, LV_GRID_TEMPLATE_LAST };
  static lv_coord_t row_dsc[] = { 215, 215, 215, 215, LV_GRID_TEMPLATE_LAST };

  lv_obj_t* grid = lv_obj_create(lv_scr_act());
  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
  lv_obj_set_size(grid, Display.width(), Display.height());

  //top left
  lv_obj_t* obj;
  obj = lv_obj_create(grid);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,  //column
                       LV_GRID_ALIGN_STRETCH, 0, 1);      //row

  //bottom left
  obj = lv_obj_create(grid);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,  //column
                       LV_GRID_ALIGN_STRETCH, 1, 1);      //row
  //top right
  obj = lv_obj_create(grid);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 1, 1,  //column
                       LV_GRID_ALIGN_STRETCH, 0, 1);      //row

  //bottom right
  obj = lv_obj_create(grid);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 1, 1,  //column
                       LV_GRID_ALIGN_STRETCH, 1, 1);      //row
}

void loop_display(unsigned long &currentMillis) {
  lv_timer_handler();
}