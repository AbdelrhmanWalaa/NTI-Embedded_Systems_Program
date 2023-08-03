/*
 * keypad.c
 *
 * Created: 7/7/2021 1:17:08 PM
 *  Author: MahmoudH
 */ 
#include "keypad.h"

u8 keys[4][4] = {
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'}
};


void	Key_Init(void){
	/* Rows Out */
	setBits(KEY_ROWS_DDR,KEY_ROWS_MSK);
	/* Default deactivated */
	setBits(KEY_ROWS_PORT,KEY_ROWS_MSK);
	/* Cols In */
	clearBits(KEY_COLS_DDR,KEY_COLS_MSK);
	/* Cols Pullup */
	setBits(KEY_COLS_PORT,KEY_COLS_MSK);
}
/*
	for each row
			activate this row
			for each column
			 if this column is activated
				calculate and return the key
			 end 
			end
			deactivate this row
	end
*/
u8		Key_GetKey(void){
	u8 row = 0;
	u8 col = 0;
	for (row = 0; row < 4; row++)
	{
		clearBit(KEY_ROWS_PORT, row);
		_delay_ms(1);
		for (col = 0; col < 4; col++)
		{
			if(readBit(KEY_COLS_PINR,(col+KEY_COLS_START)) == 0){
				while(readBit(KEY_COLS_PINR,(col+KEY_COLS_START)) == 0);
				return keys[row][col];
			}
		}
		setBit(KEY_ROWS_PORT, row);
	}
	return 0;
}
