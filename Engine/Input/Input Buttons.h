/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
enum BS_FLAG // Button State Flag
{
   BS_NONE    =   0, // none
   BS_ON      =1<<0, // on
   BS_PUSHED  =1<<1, // pushed
   BS_RELEASED=1<<2, // released
   BS_DOUBLE  =1<<3, // double clicked
   BS_TAPPED  =1<<4, // tapped
};
SET_ENUM_FLAGS(BS_FLAG);
inline Bool ButtonOn(BS_FLAG x) {return FlagOn(x, BS_ON      );} // if button is on
inline Bool ButtonPd(BS_FLAG x) {return FlagOn(x, BS_PUSHED  );} // if button pushed
inline Bool ButtonRs(BS_FLAG x) {return FlagOn(x, BS_RELEASED);} // if button released
inline Bool ButtonDb(BS_FLAG x) {return FlagOn(x, BS_DOUBLE  );} // if button double clicked
inline Bool ButtonTp(BS_FLAG x) {return FlagOn(x, BS_TAPPED  );} // if button tapped
/******************************************************************************/
enum KB_KEY : Byte // Keyboard Keys
{
   KB_NONE=0,

   KB_0='0',
   KB_1='1',
   KB_2='2',
   KB_3='3',
   KB_4='4',
   KB_5='5',
   KB_6='6',
   KB_7='7',
   KB_8='8',
   KB_9='9',

   KB_A='A',
   KB_B='B',
   KB_C='C',
   KB_D='D',
   KB_E='E',
   KB_F='F',
   KB_G='G',
   KB_H='H',
   KB_I='I',
   KB_J='J',
   KB_K='K',
   KB_L='L',
   KB_M='M',
   KB_N='N',
   KB_O='O',
   KB_P='P',
   KB_Q='Q',
   KB_R='R',
   KB_S='S',
   KB_T='T',
   KB_U='U',
   KB_V='V',
   KB_W='W',
   KB_X='X',
   KB_Y='Y',
   KB_Z='Z',

   KB_F1 =0x70, // F1
   KB_F2 =0x71, // F2
   KB_F3 =0x72, // F3
   KB_F4 =0x73, // F4
   KB_F5 =0x74, // F5
   KB_F6 =0x75, // F6
   KB_F7 =0x76, // F7
   KB_F8 =0x77, // F8
   KB_F9 =0x78, // F9
   KB_F10=0x79, // F10
   KB_F11=0x7A, // F11
   KB_F12=0x7B, // F12

   KB_ESC  =0x1B, // escape
   KB_ENTER=0x0D, // enter
   KB_SPACE=0x20, // space
   KB_BACK =0x08, // backspace
   KB_TAB  =0x09, // tab

   KB_LCTRL =0xA2, // left  control
   KB_RCTRL =0xA3, // right control
   KB_LSHIFT=0xA0, // left  shift
   KB_RSHIFT=0xA1, // right shift
   KB_LALT  =0xA4, // left  alt
   KB_RALT  =0xA5, // right alt
   KB_LWIN  =0x5B, // left  win
   KB_RWIN  =0x5C, // right win
   KB_MENU  =0x5D, // menu
   KB_FIND  =0xAA, // find

   KB_LEFT =0x25, // left  arrow
   KB_RIGHT=0x27, // right arrow
   KB_UP   =0x26, // up    arrow
   KB_DOWN =0x28, // down  arrow

   KB_INS =0x2D, // insert
   KB_DEL =0x2E, // delete
   KB_HOME=0x24, // home
   KB_END =0x23, // end
   KB_PGUP=0x21, // page up
   KB_PGDN=0x22, // page down

   KB_SUB       =0xBD, // subtract      -_
   KB_EQUAL     =0xBB, // equals        =+
   KB_LBRACKET  =0xDB, // left  bracket [{
   KB_RBRACKET  =0xDD, // right bracket ]}
   KB_SEMICOLON =0xBA, // semicolon     ;:
   KB_APOSTROPHE=0xDE, // apostrophe    '"
   KB_COMMA     =0xBC, // comma         ,<
   KB_DOT       =0xBE, // dot           .>
   KB_SLASH     =0xBF, // slash         /?
   KB_BACKSLASH =0xDC, // backslash     \|
   KB_TILDE     =0xC0, // tilde         `~

   KB_NPDIV  =0x6F, // numpad divide   /
   KB_NPMUL  =0x6A, // numpad multiply *
   KB_NPSUB  =0x6D, // numpad subtract -
   KB_NPADD  =0x6B, // numpad add      +
   KB_NPDEL  =0x6E, // numpad del
   KB_NPENTER=0x0D, // numpad enter

   KB_NP0=0x60, // numpad 0
   KB_NP1=0x61, // numpad 1
   KB_NP2=0x62, // numpad 2
   KB_NP3=0x63, // numpad 3
   KB_NP4=0x64, // numpad 4
   KB_NP5=0x65, // numpad 5
   KB_NP6=0x66, // numpad 6
   KB_NP7=0x67, // numpad 7
   KB_NP8=0x68, // numpad 8
   KB_NP9=0x69, // numpad 9

   KB_CAPS  =0x14, // caps   lock
   KB_NUM   =0x90, // num    lock
   KB_SCROLL=0x91, // scroll lock
   KB_PRINT =0x2C, // print  screen
   KB_PAUSE =0x13, // pause  break

   KB_NAV_BACK   =0xA6, // navigate backward
   KB_NAV_FORWARD=0xA7, // navigate  forward

   KB_VOL_DOWN=0xAE, // volume -
   KB_VOL_UP  =0xAF, // volume +
   KB_VOL_MUTE=0xAD, // mute

   KB_MEDIA_PREV=0xB1, // media previous
   KB_MEDIA_NEXT=0xB0, // media next
   KB_MEDIA_PLAY=0xB3, // media play/pause
   KB_MEDIA_STOP=0xB2, // media stop

   KB_ZOOM_IN =0xFB, // zoom in
   KB_ZOOM_OUT=0xFC, // zoom out

   // shorter names
   KB_LBR   =KB_LBRACKET  ,
   KB_RBR   =KB_RBRACKET  ,
   KB_SEMI  =KB_SEMICOLON ,
   KB_APO   =KB_APOSTROPHE,
   KB_BSLASH=KB_BACKSLASH ,
};
/******************************************************************************/
