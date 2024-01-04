// Sistema de Seguridad con Contrasena | Password Security System

// Librerias | Libraries
#include <16f877a.h>
#fuses NOWDT, XT, NOPROTECT, NOLVP
#use delay(clock = 4000000)
#include <lcd.c>
#use standard_io(B)
#use fast_io(C)
#use fast_io(D)

// Declaracion de variables | Declaration of variables
char password[3];
char passwordDefault1 = '4';
char passwordDefault2 = '6';
char passwordDefault3 = '8';
char key;
int i = 0;

//----------------------------------------------
// TECLADO MATRICIAL | MATRIX KEYBOARD

// Definicion de los pines del teclado matricial | Definition of the pins of the matrix keyboard
#define ROW1 PIN_B0
#define ROW2 PIN_B1
#define ROW3 PIN_B2
#define ROW4 PIN_B3
#define COL1 PIN_B4
#define COL2 PIN_B5
#define COL3 PIN_B6
#define COL4 PIN_B7

// Funcion para leer el teclado | Function to read the keyboard
char read_kb()
{
    //Primera fila | First row

    // Configuracion de los pines del teclado | Configuration of the keyboard pins
    output_low(ROW1);
    output_high(ROW2);
    output_high(ROW3);
    output_high(ROW4);

    // Lectura de las teclas | Reading of the keys
    if (!input(COL1))
        return '7';
    if (!input(COL2))
        return '4';
    if (!input(COL3))
        return '1';
    if (!input(COL4))
        return 'C';


    //Segunda fila | Second row

    // Configuracion de los pines del teclado | Configuration of the keyboard pins
    output_high(ROW1);
    output_low(ROW2);
    output_high(ROW3);
    output_high(ROW4);

    // Lectura de las teclas | Reading of the keys
    if (!input(COL1))
        return '8';
    if (!input(COL2))
        return '5';
    if (!input(COL3))
        return '2';
    if (!input(COL4))
        return '0';


    // Tercera fila | Third row

    // Configuracion de los pines del teclado | Configuration of the keyboard pins
    output_high(ROW1);
    output_high(ROW2);
    output_low(ROW3);
    output_high(ROW4);

    // Lectura de las teclas | Reading of the keys
    if (!input(COL1))
        return '9';
    if (!input(COL2))
        return '6';
    if (!input(COL3))
        return '3';
    if (!input(COL4))
        return '=';


    // Cuarta fila | Fourth row

    // Configuracion de los pines del teclado | Configuration of the keyboard pins
    output_high(ROW1);
    output_high(ROW2);
    output_high(ROW3);
    output_low(ROW4);

    // Lectura de las teclas | Reading of the keys
    if (!input(COL1))
        return '/';
    if (!input(COL2))
        return '*';
    if (!input(COL3))
        return '-';
    if (!input(COL4))
        return '+';

    return 0;
}

//----------------------------------------------


// Programa principal | Main program
void main()
{
    // Declarando los puertos de entrada y salida | Declaring the input and output ports
    set_tris_C(0b00000000);
    set_tris_D(0b00001000);
    // Inicializando el LCD | Initializing the LCD
    lcd_init();
    // Activar las resistencias de pull-up para el teclado | Activate the pull-up resistors for the keyboard
    port_b_pullups(true);

    //Ciclo infinito | Infinite cycle
    while(true)
    {
        // Muestra msj en el LCD | Show msj in the LCD
        lcd_gotoxy(1, 1);
        printf(lcd_putc, "     CERRADO   ");
        lcd_gotoxy(1, 2);
        printf(lcd_putc, "    ");

        // Enciende el LED rojo y apaga el LED verde | Turn on the red LED and turn off the green LED
        output_high(PIN_C1);
        output_low(PIN_C6);

        // Ciclo para ingresar la contraseña | Cycle to enter the password
        for (i = 0; i <= 2; i++)
        {
            i = 0;

            // Ciclo para ingresar 3 digitos | Cycle to enter 3 digits
            while(i <= 2)
            {
                // Lectura del teclado | Reading of the keyboard
                key = read_kb();

                if (key != 0)
                {
                    delay_ms(300);

                    //----------------------------------------------
                    // Si se presiona la tecla C, se borra la contraseña | If the C key is pressed, the password is deleted
                    if (key == 'C')
                    {
                        password[0] = ' ';
                        password[1] = ' ';
                        password[2] = ' ';

                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "            ");

                        i = 0;

                        break;
                    }
                    //----------------------------------------------

                    //----------------------------------------------
                    // Si se presiona la tecla =, se cambia la contraseña | If the = key is pressed, the password is changed
                    if (key == '=')
                    {
                        password[0] = ' ';
                        password[1] = ' ';
                        password[2] = ' ';

                        // Muestra msj en el LCD | Show msj in the LCD
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "Cambiar     ");
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "Contrasena  ");
                        delay_ms(1000);

                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "Antigua     ");
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "Contrasena  ");
                        delay_ms(1000);

                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "Contrasena  ");
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "            ");

                        i = 0;

                        // Se ingresa la contraseña antigua | The old password is entered
                        while(i <= 2)
                        {
                            // Lectura del teclado | Reading of the keyboard
                            key = read_kb();

                            if (key != 0)
                            {
                                delay_ms(300);

                                password[i] = key;

                                lcd_gotoxy(i + 1, 2);
                                printf(lcd_putc, "%c", password[i]);

                                // Si la contraseña antigua es correcta, se ingresa la nueva contraseña | If the old password is correct, the new password is entered
                                if ((password[0] == passwordDefault1) && (password[1] == passwordDefault2) && (password[2] == passwordDefault3))
                                {
                                    password[0] = ' ';
                                    password[1] = ' ';
                                    password[2] = ' ';

                                    // Muestra msj en el LCD | Show msj in the LCD
                                    lcd_gotoxy(1, 1);
                                    printf(lcd_putc, "Nueva       ");
                                    lcd_gotoxy(1, 2);
                                    printf(lcd_putc, "Contrasena  ");
                                    delay_ms(1000);

                                    lcd_gotoxy(1, 1);
                                    printf(lcd_putc, "Contrasena  ");
                                    lcd_gotoxy(1, 2);
                                    printf(lcd_putc, "            ");

                                    i = 0;

                                    // Se ingresa la nueva contraseña | The new password is entered
                                    while(i <= 2)
                                    {
                                        // Lectura del teclado | Reading of the keyboard
                                        key = read_kb();

                                        if (key != 0)
                                        {
                                            delay_ms(300);

                                            password[i] = key;
                                            lcd_gotoxy(i + 1, 2);
                                            printf(lcd_putc, "%c", password[i]);

                                            i++;
                                        }

                                        // Guarda la nueva contraseña | Save the new password
                                        if (i == 3)
                                        {
                                            passwordDefault1 = password[0];
                                            passwordDefault2 = password[1];
                                            passwordDefault3 = password[2];

                                            password[0] = ' ';
                                            password[1] = ' ';
                                            password[2] = ' ';

                                            key = ' ';

                                            lcd_gotoxy(1, 1);
                                            printf(lcd_putc, "Contrasena  ");
                                            lcd_gotoxy(1, 2);
                                            printf(lcd_putc, "Cambiada    ");
                                            delay_ms(1000);
                                        }
                                    }

                                    i = 0;
                                    break;
                                }

                                i++;

                                // Si la contraseña antigua es incorrecta, se muestra un mensaje | If the old password is incorrect, a message is displayed
                                if (i == 3)
                                {
                                    lcd_gotoxy(1, 1);
                                    printf(lcd_putc, "Contrasena  ");
                                    lcd_gotoxy(1, 2);
                                    printf(lcd_putc, "Incorrecta  ");
                                    delay_ms(1000);

                                    i = 0;
                                    break;
                                }
                            }
                        }
                    }

                    //----------------------------------------------

                    //----------------------------------------------
                    password[i] = key;

                    lcd_gotoxy(i + 1, 2);
                    printf(lcd_putc, "%c           ", password[i]);

                    i++;

                    //----------------------------------------------
                }
            }
        }

        // Si la contraseña es correcta, se abre la puerta | If the password is correct, the door is opened
        if (password[0] == passwordDefault1 && password[1] == passwordDefault2 && password[2] == passwordDefault3)
        {
            // Muestra msj en el LCD | Show msj in the LCD
            lcd_gotoxy(1, 1);
            printf(lcd_putc, "     ABIERTO   ");
            lcd_gotoxy(1, 2);
            printf(lcd_putc, " :D ");
            
            // Apaga el LED rojo | Turn off the red LED
            output_low(PIN_C1);
            // Enciende el LED verde y el motor | Turn on the green LED and the motor
            output_high(PIN_C7);
            output_high(PIN_C6);
            delay_ms(2000);

            // Apaga el LED verde y el motor | Turn off the green LED and the motor
            output_low(PIN_C7);
            output_low(PIN_C6);
        }
        else
        {
            // Muestra msj en el LCD si la contraseña es incorrecta | Show msj in the LCD if the password is incorrect
            lcd_gotoxy(1, 1);
            printf(lcd_putc, "   INCORRECTO   ");
            lcd_gotoxy(1, 2);
            printf(lcd_putc, " :C ");
            delay_ms(1000);
        }
    }
}
