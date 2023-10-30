//Sistema de Seguridad con Contrasena | Password Security System
#include <16f877a.h>
#fuses NOWDT, XT, NOPROTECT, NOLVP
#use delay(clock=4000000)
#include <lcd.c>
#use standard_io(B)
#use fast_io(C)
#use fast_io(D)

//Declaracion de variables | Declaration of variables
char contrasena[3];
char contrase_ingre1 = '4';
char contrase_ingre2 = '6';
char contrase_ingre3 = '8';
char tecla;
int i = 0;

//----------------------------------------------
//TECLADO MATRICIAL | MATRIX KEYBOARD
//Definicion de los pines del teclado matricial | Definition of the pins of the matrix keyboard
#define ROW1 PIN_B0
#define ROW2 PIN_B1
#define ROW3 PIN_B2
#define ROW4 PIN_B3
#define COL1 PIN_B4
#define COL2 PIN_B5
#define COL3 PIN_B6
#define COL4 PIN_B7

//Funcion para leer el teclado | Function to read the keyboard
char read_kb() {

   //Configuracion de los pines del teclado | Configuration of the keyboard pins
   output_low(ROW1);
   output_high(ROW2);
   output_high(ROW3);
   output_high(ROW4);
   //Lectura de las teclas | Reading of the keys
   if(!input(COL1)) return '7';
   if(!input(COL2)) return '4';
   if(!input(COL3)) return '1';
   if(!input(COL4)) return 'C';

   //Configuracion de los pines del teclado | Configuration of the keyboard pins
   output_high(ROW1);
   output_low(ROW2);
   output_high(ROW3);
   output_high(ROW4);
   //Lectura de las teclas | Reading of the keys
   if(!input(COL1)) return '8';
   if(!input(COL2)) return '5';
   if(!input(COL3)) return '2';
   if(!input(COL4)) return '0';

   //Configuracion de los pines del teclado | Configuration of the keyboard pins
   output_high(ROW1);
   output_high(ROW2);
   output_low(ROW3);
   output_high(ROW4);
   //Lectura de las teclas
   if(!input(COL1)) return '9';
   if(!input(COL2)) return '6';
   if(!input(COL3)) return '3';
   if(!input(COL4)) return '=';

   //Configuracion de los pines del teclado | Configuration of the keyboard pins
   output_high(ROW1);
   output_high(ROW2);
   output_high(ROW3);
   output_low(ROW4);
   if(!input(COL1)) return '/';
   if(!input(COL2)) return '*';
   if(!input(COL3)) return '-';
   if(!input(COL4)) return '+';

   return 0;
}

//----------------------------------------------

void main(){
    //Declarando los puertos de entrada y salida | Declaring the input and output ports
    set_tris_B(0b11111111);
    set_tris_C(0b00000000);
    set_tris_D(0b00001000);
    //Inicializando el LCD | Initializing the LCD
    lcd_init();
    //Activar las resistencias de pull-up | Activate pull-up resistors
    port_b_pullups(true);
   
    While(true){
        //Muestra msj en el LCD | Show msj in the LCD
        lcd_gotoxy(1,1);
        printf(lcd_putc,"     CERRADO   ");
        lcd_gotoxy(1,2);
        printf(lcd_putc,"    ");

        //Enciende el LED  | Turn on the LED
        output_high(PIN_C1);
        output_low(PIN_C6);

        //Espera a que se presione una tecla | Wait for a key to be pressed
        for(i = 0; i <= 2; i++){

            i = 0;

            While( i <= 2){

                //Lectura del teclado | Reading of the keyboard
                tecla = read_kb();

                if(tecla != 0){
                    delay_ms(300);

                    //Si se presiona la tecla C, se borra la contraseña | If the C key is pressed, the password is deleted
                    if(tecla == 'C'){
         
                        contrasena[0] = ' ';
                        contrasena[1] = ' ';
                        contrasena[2] = ' ';

                        lcd_gotoxy(1,2);
                        printf(lcd_putc,"            ");

                        i = 0;
                    
                        break;
                    }
                    //Si se presiona la tecla =, se cambia la contraseña | If the = key is pressed, the password is changed
                    if(tecla == '='){

                        contrasena[0] = ' ';
                        contrasena[1] = ' ';
                        contrasena[2] = ' ';

                        lcd_gotoxy(1,1);
                        printf(lcd_putc,"Cambiar     ");
                        lcd_gotoxy(1,2);
                        printf(lcd_putc,"Contrasena  ");
                        delay_ms(1000);

                        lcd_gotoxy(1,1);
                        printf(lcd_putc,"Antigua     ");
                        lcd_gotoxy(1,2);
                        printf(lcd_putc,"Contrasena  ");
                        delay_ms(1000);

                        lcd_gotoxy(1,1);
                        printf(lcd_putc,"Contrasena  ");
                        lcd_gotoxy(1,2);
                        printf(lcd_putc,"            ");

                        i = 0;
                        //Se ingresa la contraseña antigua | The old password is entered
                        While( i <= 2){
                            
                            //Lectura del teclado | Reading of the keyboard
                            tecla = read_kb();

                            if(tecla != 0){
                                delay_ms(300);

                                contrasena[i] = tecla;
                                
                                lcd_gotoxy(i + 1,2);
                                printf(lcd_putc,"%c",contrasena[i]);

                                //Si la contraseña antigua es correcta, se ingresa la nueva contraseña | If the old password is correct, the new password is entered
                                if((contrasena[0] == contrase_ingre1) && (contrasena[1] == contrase_ingre2) && (contrasena[2] == contrase_ingre3)){
                                    
                                    contrasena[0] = ' ';
                                    contrasena[1] = ' ';
                                    contrasena[2] = ' ';

                                    lcd_gotoxy(1,1);
                                    printf(lcd_putc,"Nueva       ");
                                    lcd_gotoxy(1,2);
                                    printf(lcd_putc,"Contrasena  ");
                                    delay_ms(1000);

                                    lcd_gotoxy(1,1);
                                    printf(lcd_putc,"Contrasena  ");
                                    lcd_gotoxy(1,2);
                                    printf(lcd_putc,"            ");
                                    
                                    i = 0;

                                    While( i <= 2){
                                        
                                        //Lectura del teclado | Reading of the keyboard
                                        tecla = read_kb();
                                
                                        if(tecla != 0){
                                            delay_ms(300);

                                            contrasena[i] = tecla;
                                            lcd_gotoxy(i + 1,2);
                                            printf(lcd_putc,"%c",contrasena[i]);
                                            
                                            i++;
                                        }
                                        //Guarda la nueva contraseña | Save the new password
                                        if(i == 3){

                                            contrase_ingre1 = contrasena[0];
                                            contrase_ingre2 = contrasena[1];
                                            contrase_ingre3 = contrasena[2];

                                            contrasena[0] = ' ';
                                            contrasena[1] = ' ';
                                            contrasena[2] = ' ';
                                            tecla = ' ';

                                            lcd_gotoxy(1,1);
                                            printf(lcd_putc,"Contrasena  ");
                                            lcd_gotoxy(1,2);
                                            printf(lcd_putc,"Cambiada    ");
                                            delay_ms(1000);
                                        }
                                    }
                                    
                                    i = 0;
                                    break;
                                    
                                }

                                i++;
                                //Si la contraseña antigua es incorrecta, se muestra un mensaje | If the old password is incorrect, a message is displayed
                                if(i == 3){
                                    lcd_gotoxy(1,1);
                                    printf(lcd_putc,"Contrasena  ");
                                    lcd_gotoxy(1,2);
                                    printf(lcd_putc,"Incorrecta  ");
                                    delay_ms(1000);
                                    i = 0;
                                    break;
                                }
                            }

                        }
                    }

                    contrasena[i] = tecla;
                    
                    lcd_gotoxy(i + 1,2);
                    printf(lcd_putc,"%c           ",contrasena[i]);
                    i++;
                }
            }
        }
 
        //Si la contraseña es correcta, se abre la puerta | If the password is correct, the door is opened
        if (contrasena[0] == contrase_ingre1 && contrasena[1] == contrase_ingre2 && contrasena[2] == contrase_ingre3){
            //Apaga el LED | Turn off the LED
            output_low(PIN_C1);
            //Muestra msj en el LCD | Show msj in the LCD
            lcd_gotoxy(1,1);
            printf(lcd_putc,"     ABIERTO   ");
            lcd_gotoxy(1,2);
            printf(lcd_putc," :D ");

            //Enciende el LED y el motor | Turn on the LED and the motor
            output_high(PIN_C7);
            output_high(PIN_C6);
            delay_ms(2000);
            //Apaga el LED y el motor | Turn off the LED and the motor
            output_low(PIN_C7);
            output_low(PIN_C6);
 
        }
        else {
            //Muestra msj en el LCD | Show msj in the LCD
            lcd_gotoxy(1,1);
            printf(lcd_putc,"   INCORRECTO   ");
            lcd_gotoxy(1,2);
            printf(lcd_putc," :C ");
            delay_ms(1000);
        }
    }
}

