#include "mp3.h"
#include <string.h>

extern const size_t COL;

void mp3__init_lcd_display(void) {
  size_t song_size = sl__get_count();
  size_t row = 0;
  char temp_buffer[COL * 2]; // just adding padding to keep memory safe
  char row_buffer[COL];
  lcd__clr_screen();
  if (song_size > 0) {                   // at least one song
    while (row < song_size && row < 3) { // 3 cuz only have room to show 3 songs on lcd
      sprintf(temp_buffer, "%u. %s", row + 1, sl__get_item(row).filename);
      strncpy(row_buffer, temp_buffer, COL); // possibly don't need this func
      lcd__send_row(row_buffer, row);
      row++;
    }
    lcd__send_row(" ^ Up O sel !^", ROW_04); // 3 is the last row must have control function help at the bottom

  } else {
    lcd__send_row("No Songs Found.", ROW_01); // display on the first row.
  }
}

void mp3__init(void) {
  sl__refresh_list(); // init function for sl = song list
  lcd__init(9600);
  mp3__init_lcd_display();
}
