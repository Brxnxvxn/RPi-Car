#include <stdio.h>
#include <i2c_driver.h>

/*
RS - register select => two register (IR and DR)
R/W - read and write pin
E - enable data transfer between pi and display
D0 - D7 - data pins

Features
-Clear Display - 0x01
-Entry Mode - I/D moves cursor or blinker when data is read or written to display
            - S shifts display by right or left depending on I/D

-Display ON/OFF control - D -display on = 1 display off = 0
                        - C cursor is displayed if 1
                        - character indicated by cursor blinks if 1

- Cursor or display shifts without reading or writing data 
- Function Set  - 4 or 8 bit data modes (4 bit mode uses D4-D7
                - N sets number of display lines
                - F set character font
*/

#define CMD         0
#define RS_PIN      0b0001
#define RW_PIN      0b0010 
#define EN_PIN      0b0100
#define BACKLIGHT   0b1000


static struct lcd_dev {
    int addr;
    int fd;
}lcd;

//send data to lcd
static void send_byte(uint8 data, uint8 register_select) {

    int first_bits = (data & 0xF0) | register_select;
    int last_bits = (data << 4) | register_select;
    
    //send data through i2c bus
    i2c_write(first_bits);
    i2c_write(last_bits);

}

//initialize lcd
static void lcd_init(int addr) {

    //power on lcd
    lcd.addr = addr;
    lcd.fd = i2c_init(addr);
    delay(15);

    send_byte(0x3, CMD);
    delay(4.1);

    send_byte(0x3, CMD);
    delay(0.1);

    send_byte(0x32, CMD); // third attempt to initialze to 4-bit mode for transfer  
    send_byte(0x28, CMD); // 4-bit mode with 2 lines and normal character font
    send_byte(0x08, CMD); // display off, cursor off, blink off
    send_byte(0x01, CMD); // display clear
    send_byte(0x06, CMD); // entry mode set
    send_byte(0x0C, CMD); // display on
}

//clear display
static void clear_lcd() {
    send_byte(0x01, CMD);
}

//move cursor to specific location
static void move_cursor(int loc) {
    send_byte(loc, CMD);
}

//print string to lcd
static void lcd_print_str(char str[], int length) {
    for(int = 0; i < length; i++) {
        send_byte(str[i], !CMD);
    }
}

//print char to lcd
static void lcd_print_char(char ch) {
    send_byte(ch, !CMD);
}

//print int to lcd
static void lcd_print_int(int num) {
    char ch[5];
    snprintf(ch, "%d", num);
    lcd_print_str(ch, 1);
}


