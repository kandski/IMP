/*******************************************************************************
   key.c: main for aplikation keyboard
   Copyright (C) 2009 Brno University of Technology,
                      Faculty of Information Technology
   Author(s): Jan Markovic <xmarko04 AT stud.fit.vutbr.cz>

   LICENSE TERMS

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the
      distribution.
   3. All advertising materials mentioning features or use of this software
      or firmware must display the following acknowledgement:

        This product includes software developed by the University of
        Technology, Faculty of Information Technology, Brno and its
        contributors.

   4. Neither the name of the Company nor the names of its contributors
      may be used to endorse or promote products derived from this
      software without specific prior written permission.

   This software or firmware is provided ``as is'', and any express or implied
   warranties, including, but not limited to, the implied warranties of
   merchantability and fitness for a particular purpose are disclaimed.
   In no event shall the company or contributors be liable for any
   direct, indirect, incidental, special, exemplary, or consequential
   damages (including, but not limited to, procurement of substitute
   goods or services; loss of use, data, or profits; or business
   interruption) however caused and on any theory of liability, whether
   in contract, strict liability, or tort (including negligence or
   otherwise) arising in any way out of the use of this software, even
   if advised of the possibility of such damage.

   $Id$


*******************************************************************************/

#include <fitkitlib.h>
#include <keyboard/keyboard.h>

char last_ch; //naposledy precteny znak
const int ROWS = 8;
const int COLS = 8;
int debug = 0;
int matrix[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};

int matrix2[8][8] = {
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
};
int matrix3[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 1, 0, 0},
        {1, 0, 1, 0, 0, 1, 0, 1},
        {1, 1, 0, 0, 0, 0, 1, 1}
};
int matrix4[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 1},
        {0, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
};
int matrix5[8][8] = {								//NECHAT je to v pohode
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
};
int matrix6[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
};



/*******************************************************************************
 * Vypis uzivatelske napovedy (funkce se vola pri vykonavani prikazu "help")
*******************************************************************************/
void print_user_help(void) {
}


/*******************************************************************************
 * Obsluha klavesnice
*******************************************************************************/
int keyboard_idle() {
    char ch;
    ch = key_decode(read_word_keyboard_4x4());
    if (ch != last_ch) // stav se zmnenil
    {
        last_ch = ch;
        if (ch == '1') {
            if (debug == 0) {
                debug = 1;
            }
            else {
                debug = 0;
            }
        }
        if (ch == 'D')
        {
            int row, col;
            for ( row = 0; row < ROWS; row++) {
                for ( col = 0; col < COLS; col++) {
                    matrix[row][col] = matrix2[row][col];
                }
            }
        }
        if (ch == 'A')
        {
            int row, col;
            for ( row = 0; row < ROWS; row++) {
                for ( col = 0; col < COLS; col++) {
                    matrix[row][col] = matrix3[row][col];
                }
            }
        }
        if (ch == 'B')
        {
            int row, col;
            for ( row = 0; row < ROWS; row++) {
                for ( col = 0; col < COLS; col++) {
                    matrix[row][col] = matrix4[row][col];
                }
            }
        }
        if (ch == 'C')
        {
            int row, col;
            for ( row = 0; row < ROWS; row++) {
                for ( col = 0; col < COLS; col++) {
                    matrix[row][col] = matrix6[row][col];
                }
            }
        }
	if (ch == '5')
        {
            int row, col;
            for ( row = 0; row < ROWS; row++) {
                for ( col = 0; col < COLS; col++) {
                    matrix[row][col] = matrix5[row][col];
                }
            }
        }
        if (ch == '0')
        {
            life();
        }
    }
    return 0;
}


//funkcia pre nastavovanie hodnot stlpcov
void setCols(int index) {
    switch (index) {
        case 0:
            P2DIR |= BIT5;
            return;
        case 1:
            P2DIR |= BIT1;
            return;
        case 2:
            P1DIR |= BIT5;
            return;
        case 3:
            P1DIR |= BIT3;
            return;
        case 4:
            P6DIR |= BIT7;
            return;
        case 5:
            P6DIR |= BIT5;
            return;
        case 6:
            P6DIR |= BIT3;
            return;
        case 7:
            P6DIR |= BIT1;
            return;
    }
}

//funkcia pre nastavovanie hodnot riadkov
void setRows(int index) {
    switch (index) {
        case 0:
            P2DIR |= BIT4;
            P2OUT |= BIT4;
            break;
        case 1:
            P1DIR |= BIT6;
            P1OUT |= BIT6;
            break;
        case 2:
            P1DIR |= BIT4;
            P1OUT |= BIT4;
            break;
        case 3:
            P1DIR |= BIT2;
            P1OUT |= BIT2;
            break;
        case 4:
            P6DIR |= BIT6;
            P6OUT |= BIT6;
            break;
        case 5:
            P6DIR |= BIT4;
            P6OUT |= BIT4;
            break;
        case 6:
            P6DIR |= BIT2;
            P6OUT |= BIT2;
            break;
        case 7:
            P6DIR |= BIT0;
            P6OUT |= BIT0;
            break;

    }
}


/*******************************************************************************
 * Dekodovani a vykonani uzivatelskych prikazu
*******************************************************************************/
unsigned char decode_user_cmd(char *cmd_ucase, char *cmd) {
    return CMD_UNKNOWN;
}


//modulo osetrene na zaporne hodnoty kvoli skumaniu susedov
//prevzate z 
//https://stackoverflow.com/questions/4003232/how-to-code-a-modulo-operator-in-c-c-obj-c-that-handles-negative-numbers
int mod (int a, int b)
{
    if (b < 0)
        return mod(a, -b);
    int ret = a % b;
    if (ret < 0)
        ret +=b;
    return ret;
}

/*******************************************************************************
 * Inicializace periferii/komponent po naprogramovani FPGA
*******************************************************************************/
void fpga_initialized() {
}

void life() {
    int temp[COLS][ROWS];

    int row;
    int col;
    int i;
    int x;
    int y;
    int neigh;

    //vynulovanie pomocnej matice	
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            temp[row][col] = 0;
        }
    }
    //hlavny cyklus algoritmu
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            neigh = 0;
	    //najdenie susedov 
            for (y = -1; y < 2; y++) {
                for (x = -1; x < 2; x++) {
		    // seba za suseda nepocitame
                    if (x == 0 && y == 0)
                        continue;
                    neigh += matrix[mod((row + y),ROWS)][mod((col + x), COLS)];
                }
            }
	    //rozhodovanie ozivenia/umrtia
            if (matrix[row][col] == 1) {
                if (neigh < 2 || neigh > 3) {
                    temp[row][col] = 0;
                } else {
                    temp[row][col] = 1;
                }
            } else {
                if (neigh == 3) {
                    temp[row][col] = 1;
                } else {
                    temp[row][col] = 0;
                }
            }
        }
    }
    //zavedenia zmien do hlavnej matice	
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            matrix[row][col] = temp[row][col];
        }
    }
}

void print_matrix() {
    unsigned cnt = 0;
    int flag = 0;
    //HLAVNY CYKLUS
    while (1) {
        if (cnt > 7) {
		//prepinac debug modu
            if (debug == 0)
            {
		    //volanie life algoritmu raz za 350 obnoveni riadkov displeja
                if (flag == 50){
                    life();
                    flag = 0;
                }
                flag++;
            }
            cnt = 0;
            flip_led_d6(); 
        }
        int i = 0;
        int j = 0;
        i = cnt;

	//vykreslovanie hlavnej matice
        for (j = 0; j < COLS; j++) {
            if (matrix[i][j] != 0) {
                setRows(i);
                setCols(j);

            }
        }

        delay_ms(1.5);
        P1DIR = 0x00;
        P2DIR = 0x00;
        P6DIR = 0x00;


        cnt++;
        terminal_idle();                   // obsluha terminalu
        keyboard_idle();
    }
}

/*******************************************************************************
 * Hlavni funkce
*******************************************************************************/

int main(void) {
    unsigned int cnt = 0;
    last_ch = 0;

    initialize_hardware();
    keyboard_init();
    set_led_d6(1);                       // rozsviceni D6
    set_led_d5(1);                       // rozsviceni D5

//  pociatocne nastavenie portov displeja // bliknutie na zaciatku
    P6DIR |= BIT0|BIT2|BIT4|BIT6;
    P6OUT = 0x55;
    P6DIR |= BIT1|BIT3|BIT5|BIT7;
    P1DIR |= BIT2|BIT4|BIT6;
    P1OUT = 0x54;
    P1DIR |= BIT3|BIT5;
    P2DIR |= BIT4;
    P2OUT = 0x10;
    P2DIR |= BIT1|BIT5;

    //hlavna funkcia vykreslenia
    print_matrix();

}


