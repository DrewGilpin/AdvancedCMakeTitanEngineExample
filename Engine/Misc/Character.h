/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
enum CHAR_FLAG // Character Flag
{
   CHARF_DIG2 =1<<0, // if binary  digit 01
   CHARF_DIG10=1<<1, // if decimal digit 0123456789
   CHARF_DIG16=1<<2, // if hex     digit 0123456789ABCDEFabcdef
   CHARF_SIGN =1<<3, // if sign          `~!@#$%^&-+*=()[]{}<>;:'",./|\?
   CHARF_ALPHA=1<<4, // if alphabetic
   CHARF_UNDER=1<<5, // if underline
   CHARF_UP   =1<<6, // if upper case
   CHARF_SPACE=1<<7, // if space character (including Nbsp, FullWidthSpace, Tab)

   CHARF_DIG=CHARF_DIG10,
};

UInt CharFlag(Char  c); // get CHAR_FLAG
UInt CharFlag(Char8 c); // get CHAR_FLAG
/******************************************************************************/
enum CHAR_TYPE : Byte // Character Type
{
   CHART_NONE , // none/unknown
   CHART_CHAR , // alphabetic, digit or underline
   CHART_SPACE, // space
   CHART_SIGN , // symbol
};

CHAR_TYPE CharType(Char  c); // get character type
CHAR_TYPE CharType(Char8 c); // get character type
/******************************************************************************/
constexpr UInt CC4(Byte a, Byte b, Byte c, Byte d) {return a | (b<<8) | (c<<16) | (d<<24);}

Bool WhiteChar(Char c); // if char is a white char - ' ', '\t', '\n', '\r'

constexpr Byte   Unsigned(Char8  x) {return x;}
constexpr UShort Unsigned(Char   x) {return x;}

Char8 Char16To8(Char  c); // convert 16-bit to  8-bit character
Char  Char8To16(Char8 c); // convert  8-bit to 16-bit character

Char  CaseDown(Char  c); // return lower case 'c'
Char8 CaseDown(Char8 c); // return lower case 'c'
Char  CaseUp  (Char  c); // return upper case 'c'
Char8 CaseUp  (Char8 c); // return upper case 'c'

Int Compare(Char  a, Char  b, Bool case_sensitive=false); // compare characters, returns -1, 0, +1
Int Compare(Char  a, Char8 b, Bool case_sensitive=false); // compare characters, returns -1, 0, +1
Int Compare(Char8 a, Char  b, Bool case_sensitive=false); // compare characters, returns -1, 0, +1
Int Compare(Char8 a, Char8 b, Bool case_sensitive=false); // compare characters, returns -1, 0, +1

Bool Equal(Char  a, Char  b, Bool case_sensitive=false); // if characters are the same
Bool Equal(Char  a, Char8 b, Bool case_sensitive=false); // if characters are the same
Bool Equal(Char8 a, Char  b, Bool case_sensitive=false); // if characters are the same
Bool Equal(Char8 a, Char8 b, Bool case_sensitive=false); // if characters are the same

Bool EqualCS(Char  a, Char  b); // if characters are the same, case sensitive
Bool EqualCS(Char  a, Char8 b); // if characters are the same, case sensitive
Bool EqualCS(Char8 a, Char  b); // if characters are the same, case sensitive
Bool EqualCS(Char8 a, Char8 b); // if characters are the same, case sensitive

Char RemoveAccent(Char c); // convert accented character to one without an accent, for example RemoveAccent('ą') -> 'a', if character is not accented then it will be returned without any modifications, RemoveAccent('a') -> 'a'

inline Bool HasUnicode(Char  c) {return Unsigned(c)>=128;} // if character is a unicode character
inline Bool HasUnicode(Char8 c) {return Unsigned(c)>=128;} // if character is a unicode character
/******************************************************************************/
const Char8 CharNull      ='\0',
            CharTab       ='\t',
            CharLine      ='\n';
const Char  CharBullet    =u'•',
            CharDegree    =u'°',
            CharSection   =u'§',
            CharPlusMinus =u'±',
            CharMul       =u'×',
            CharDiv       =u'÷',
            CharStar      =u'★',

            CharLeft      =u'←',
            CharRight     =u'→',
            CharDown      =u'↓',
            CharUp        =u'↑',
            CharUpLeft    =u'↖',
            CharUpRight   =u'↗',
            CharDownLeft  =u'↙',
            CharDownRight =u'↘',
            CharLeftRight =u'↔',
            CharDownUp    =u'↕',

            CharTriLeft   =u'⯇',
            CharTriRight  =u'⯈',
            CharTriDown   =u'⯆',
            CharTriUp     =u'⯅',

            CharTriangleUp=u'△',
            CharSquare    =u'□', // med=◻, large=⬜
            CharCircle    =u'○', // med=⚪, large=◯
            CharCross     =u'✕', // ╳❌✖⨉??

            CharCopyright =u'©',
            CharRegTM     =u'®',
            CharTrademark =u'™',
            CharReturn    =u'⏎',
            CharEnter     =u'⎆',
            Nbsp          =u' ', // non-breaking space
            FullWidthSpace=u'　',
            Ellipsis      =u'…',
            CharAlpha     =u'α',
            CharBeta      =u'β',
            CharSuper2    =u'²',
            CharSuper3    =u'³',
            CharPermil    =u'‰'; // 1/1000
/******************************************************************************/
