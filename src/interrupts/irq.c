#include "../stdio/stdio.h"
#include "../io/io.h"

static const scanset1[0xFF] = {                                /*pressed*/
                                /*0-7*/      0 /*esc*/       , '1'              , '2'              , '3'              , '4'              , '5'              , '6'              , '7'              , 
                                /*8-15*/    '8'              , '9'              , '0'              , '-'              , '='              ,  0 /*backspace*/ ,  0 /*tab*/       , 'Q'              ,
                                /*16-23*/   'W'              , 'E'              , 'R'              , 'T'              , 'Y'              , 'U'              , 'I'              , 'O'              ,
                                /*24-31*/   'P'              , '['              , ']'              ,  0 /*enter*/     ,  0 /*L ctrl*/    , 'A'              , 'S'              , 'D'              ,   
                                /*32-39*/   'F'              , 'G'              , 'H'              , 'J'              , 'K'              , 'L'              , ';'              , '\''             ,
                                /*40-47*/   '`'              ,  0 /*L shift*/   , '\\'             , 'Z'              , 'X'              , 'C'              , 'V'              , 'B'              ,
                                /*48-55*/   'N'              , 'M'              , ','              , '.'              , '/'              ,  0 /*R shift*/   ,  0 /*keypad:* */ ,  0 /*L alt*/     ,
                                /*56-63*/    0 /*space*/     ,  0 /*capslock*/  ,  0 /*F1*/        ,  0 /*F2*/        ,  0 /*F3*/        ,  0 /*F4*/        ,  0 /*F5*/        ,  0 /*F6*/        ,
                                /*64-71*/    0 /*F7*/        ,  0 /*F8*/        ,  0 /*F9*/        ,  0 /*F10*/       ,  0 /*numLock*/   ,  0 /*scrollLock*/,  0 /*keypad:7 */ ,  0 /*keypad:8 */ ,
                                /*72-79*/    0 /*keypad:9 */ ,  0 /*keypad:- */ ,  0 /*keypad:4 */ ,  0 /*keypad:5 */ ,  0 /*keypad:6 */ ,  0 /*keypad:+ */ ,  0 /*keypad:1 */ ,  0 /*keypad:2 */ ,
                                /*80-87*/    0 /*keypad:3 */ ,  0 /*keypad:0 */ ,  0 /*keypad:. */ ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*F11*/       ,  0 /*F12*/       ,
                                                               /*released*/
                                /*88-95*/    0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*esc*/       , '1'              , '2'              , '3'              ,
                                /*96-103*/  '4'              , '5'              , '6'              , '7'              , '8'              , '9'              , '0'              , '-'              ,
                                /*104-111*/ '='              ,  0 /*backspace*/ ,  0 /*tab*/       , 'Q'              , 'W'              , 'E'              , 'R'              , 'T'              ,
                                /*112-119*/ 'Y'              , 'U'              , 'I'              , 'O'              , 'P'              , '['              , ']'              ,  0 /*enter*/     ,
                                /*120-127*/  0 /*L ctrl*/    , 'A'              , 'S'              , 'D'              , 'F'              , 'G'              , 'H'              , 'J'              ,
                                /*128-135*/ 'K'              , 'L'              , ';'              , '\''             , '`'              ,  0 /*L shift*/   , '\\'             , 'Z'              ,
                                /*136-143*/ 'X'              , 'C'              , 'V'              , 'B'              , 'N'              , 'M'              , ','              , '.'              ,
                                /*144-151*/ '/'              ,  0 /*R shift*/   ,  0 /*keypad:* */ ,  0 /*L alt*/     ,  0 /*space*/     ,  0 /*capslock*/  ,  0 /*F1*/        ,  0 /*F2*/        ,
                                /*152-159*/  0 /*F3*/        ,  0 /*F4*/        ,  0 /*F5*/        ,  0 /*F6*/        ,  0 /*F7*/        ,  0 /*F8*/        ,  0 /*F9*/        ,  0 /*F10*/       ,
                                /*160-167*/  0 /*numLock*/   ,  0 /*scrollLock*/,  0 /*keypad:7 */ ,  0 /*keypad:8 */ ,  0 /*keypad:9 */ ,  0 /*keypad:- */ ,  0 /*keypad:4 */ ,  0 /*keypad:5 */ ,
                                /*168-175*/  0 /*keypad:6 */ ,  0 /*keypad:+ */ ,  0 /*keypad:1 */ ,  0 /*keypad:2 */ ,  0 /*keypad:3 */ ,  0 /*keypad:0 */ ,  0 /*keypad:. */ ,  0 /*null*/      ,
         /*stopped at E0*/      /*176-183*/  0 /*null*/      ,  0 /*null*/      ,  0 /*F11*/       ,  0 /*F12*/       ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,
                                /*184-191*/  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,
                                /*192-199*/  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,
                                /*200-207*/  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,
                                /*208-215*/  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,
                                /*216-223*/  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,
                                /*224-231*/  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,
                                /*232-239*/  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,
                                /*240-247*/  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,
                                /*248-255*/  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      ,  0 /*null*/      };

void irq0_handler()
{
    //printf("int0!\n");
    outb(0x20, 0x20);
}

void irq1_handler()
{
    inb(0x60);
    //printf("int1! %d\n", inb(0x60));
    outb(0x20, 0x20);
}