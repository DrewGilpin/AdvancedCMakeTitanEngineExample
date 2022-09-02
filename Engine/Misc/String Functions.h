/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************

   Following functions accept 'CChar*' and 'CChar8*' parameters,
      however you can also use 'Str' and 'Str8' parameters
      as string classes support auto casting to 'CChar*' and 'CChar8*' respectively.

/******************************************************************************/
enum WHOLE_WORD
{
   WHOLE_WORD_NO    =0                                , // whold word not required
   WHOLE_WORD_ALPHA =CHARF_ALPHA                      , // whold word     required (relaxed), words are made from alphabetic                         characters, "ab" is a word, "ab12" is NOT a word, "ab12_" is NOT a word
   WHOLE_WORD_YES   =CHARF_ALPHA|CHARF_DIG            , // whold word     required (medium ), words are made from alphabetic and digit               characters, "ab" is a word, "ab12" is     a word, "ab12_" is NOT a word, use this for most cases
   WHOLE_WORD_STRICT=CHARF_ALPHA|CHARF_DIG|CHARF_UNDER, // whold word     required (strict ), words are made from alphabetic,    digit and underline characters, "ab" is a word, "ab12" is     a word, "ab12_" is     a word, use this for checking code tokens
};
/******************************************************************************/
inline Bool Is        (CChar  *t) {return t && t[0];} // if  text has any data
inline Bool Is        (CChar8 *t) {return t && t[0];} // if  text has any data
       Int  Length    (CChar  *t);                    // get text length (number of characters)
       Int  Length    (CChar8 *t);                    // get text length (number of characters)
       Bool HasUnicode(CChar  *t);                    // if  text contains unicode characters
       Bool HasUnicode(CChar8 *t);                    // if  text contains unicode characters
       Bool HasUnicode(C Str  &s);                    // if  text contains unicode characters
       Bool HasUnicode(C Str8 &s);                    // if  text contains unicode characters

Char * Set   (Char  *dest, CChar  *src, Int dest_elms); // set    'dest' text from 'src' and return 'dest', 'dest_elms'=maximum available elements in the 'dest' pointer
Char * Set   (Char  *dest, CChar8 *src, Int dest_elms); // set    'dest' text from 'src' and return 'dest', 'dest_elms'=maximum available elements in the 'dest' pointer
Char8* Set   (Char8 *dest, CChar  *src, Int dest_elms); // set    'dest' text from 'src' and return 'dest', 'dest_elms'=maximum available elements in the 'dest' pointer
Char8* Set   (Char8 *dest, CChar8 *src, Int dest_elms); // set    'dest' text from 'src' and return 'dest', 'dest_elms'=maximum available elements in the 'dest' pointer
Char * Append(Char  *dest, CChar  *src, Int dest_elms); // append 'dest' text from 'src' and return 'dest', 'dest_elms'=maximum available elements in the 'dest' pointer
Char * Append(Char  *dest, CChar8 *src, Int dest_elms); // append 'dest' text from 'src' and return 'dest', 'dest_elms'=maximum available elements in the 'dest' pointer
Char8* Append(Char8 *dest, CChar  *src, Int dest_elms); // append 'dest' text from 'src' and return 'dest', 'dest_elms'=maximum available elements in the 'dest' pointer
Char8* Append(Char8 *dest, CChar8 *src, Int dest_elms); // append 'dest' text from 'src' and return 'dest', 'dest_elms'=maximum available elements in the 'dest' pointer

template<Int elms>  Char *  Set   (Char  (&dest)[elms], CChar  *src) {return Set   (dest, src, elms);} // set    'dest' text from 'src' and return 'dest' (autodetect 'dest_elms')
template<Int elms>  Char *  Set   (Char  (&dest)[elms], CChar8 *src) {return Set   (dest, src, elms);} // set    'dest' text from 'src' and return 'dest' (autodetect 'dest_elms')
template<Int elms>  Char8*  Set   (Char8 (&dest)[elms], CChar  *src) {return Set   (dest, src, elms);} // set    'dest' text from 'src' and return 'dest' (autodetect 'dest_elms')
template<Int elms>  Char8*  Set   (Char8 (&dest)[elms], CChar8 *src) {return Set   (dest, src, elms);} // set    'dest' text from 'src' and return 'dest' (autodetect 'dest_elms')
template<Int elms>  Char *  Append(Char  (&dest)[elms], CChar  *src) {return Append(dest, src, elms);} // append 'dest' text from 'src' and return 'dest' (autodetect 'dest_elms')
template<Int elms>  Char *  Append(Char  (&dest)[elms], CChar8 *src) {return Append(dest, src, elms);} // append 'dest' text from 'src' and return 'dest' (autodetect 'dest_elms')
template<Int elms>  Char8*  Append(Char8 (&dest)[elms], CChar  *src) {return Append(dest, src, elms);} // append 'dest' text from 'src' and return 'dest' (autodetect 'dest_elms')
template<Int elms>  Char8*  Append(Char8 (&dest)[elms], CChar8 *src) {return Append(dest, src, elms);} // append 'dest' text from 'src' and return 'dest' (autodetect 'dest_elms')

Int CompareCI(Char8 a, Char8 b); // compare characters Case-Insensitive, returns -1, 0, +1
Int CompareCI(Char8 a, Char  b); // compare characters Case-Insensitive, returns -1, 0, +1
Int CompareCI(Char  a, Char8 b); // compare characters Case-Insensitive, returns -1, 0, +1
Int CompareCI(Char  a, Char  b); // compare characters Case-Insensitive, returns -1, 0, +1

Int CompareCS(Char8 a, Char8 b); // compare characters Case-Sensitive, returns -1, 0, +1
Int CompareCS(Char8 a, Char  b); // compare characters Case-Sensitive, returns -1, 0, +1
Int CompareCS(Char  a, Char8 b); // compare characters Case-Sensitive, returns -1, 0, +1
Int CompareCS(Char  a, Char  b); // compare characters Case-Sensitive, returns -1, 0, +1

Int Compare(CChar  *a, CChar  *b, Bool case_sensitive=false); // compare texts, returns -1, 0, +1
Int Compare(CChar  *a, CChar8 *b, Bool case_sensitive=false); // compare texts, returns -1, 0, +1
Int Compare(CChar8 *a, CChar  *b, Bool case_sensitive=false); // compare texts, returns -1, 0, +1
Int Compare(CChar8 *a, CChar8 *b, Bool case_sensitive=false); // compare texts, returns -1, 0, +1

inline Bool Equal(CChar  *a, CChar  *b, Bool case_sensitive=false) {return !Compare(a, b, case_sensitive);} // if texts are equal
inline Bool Equal(CChar  *a, CChar8 *b, Bool case_sensitive=false) {return !Compare(a, b, case_sensitive);} // if texts are equal
inline Bool Equal(CChar8 *a, CChar  *b, Bool case_sensitive=false) {return !Compare(a, b, case_sensitive);} // if texts are equal
inline Bool Equal(CChar8 *a, CChar8 *b, Bool case_sensitive=false) {return !Compare(a, b, case_sensitive);} // if texts are equal

inline Int CompareCI(C Str  &a, C Str  &b) {return Compare(a, b, false);} // compare texts Case-Insensitive, you can use this function directly to other parts of the engine which require comparison functions in this format
inline Int CompareCI(C Str8 &a, C Str8 &b) {return Compare(a, b, false);} // compare texts Case-Insensitive, you can use this function directly to other parts of the engine which require comparison functions in this format
inline Int CompareCS(C Str  &a, C Str  &b) {return Compare(a, b, true );} // compare texts Case-  Sensitive, you can use this function directly to other parts of the engine which require comparison functions in this format
inline Int CompareCS(C Str8 &a, C Str8 &b) {return Compare(a, b, true );} // compare texts Case-  Sensitive, you can use this function directly to other parts of the engine which require comparison functions in this format

       Int ComparePath(CChar  *a, CChar  *b, Bool case_sensitive=false); // compare paths, returns -1, 0, +1 (this function works the same as comparing texts, except that '/' is treated as equal to '\\')
       Int ComparePath(CChar  *a, CChar8 *b, Bool case_sensitive=false); // compare paths, returns -1, 0, +1 (this function works the same as comparing texts, except that '/' is treated as equal to '\\')
       Int ComparePath(CChar8 *a, CChar  *b, Bool case_sensitive=false); // compare paths, returns -1, 0, +1 (this function works the same as comparing texts, except that '/' is treated as equal to '\\')
       Int ComparePath(CChar8 *a, CChar8 *b, Bool case_sensitive=false); // compare paths, returns -1, 0, +1 (this function works the same as comparing texts, except that '/' is treated as equal to '\\')
inline Bool  EqualPath(CChar  *a, CChar  *b, Bool case_sensitive=false) {return !ComparePath(a, b, case_sensitive);} // if paths are equal (this function works the same as comparing texts, except that '/' is treated as equal to '\\')
inline Bool  EqualPath(CChar  *a, CChar8 *b, Bool case_sensitive=false) {return !ComparePath(a, b, case_sensitive);} // if paths are equal (this function works the same as comparing texts, except that '/' is treated as equal to '\\')
inline Bool  EqualPath(CChar8 *a, CChar  *b, Bool case_sensitive=false) {return !ComparePath(a, b, case_sensitive);} // if paths are equal (this function works the same as comparing texts, except that '/' is treated as equal to '\\')
inline Bool  EqualPath(CChar8 *a, CChar8 *b, Bool case_sensitive=false) {return !ComparePath(a, b, case_sensitive);} // if paths are equal (this function works the same as comparing texts, except that '/' is treated as equal to '\\')

inline Int ComparePathCI(C Str &a, C Str &b) {return ComparePath(a, b, false);} // compare paths Case-Insensitive, you can use this function directly to other parts of the engine which require comparison functions in this format
inline Int ComparePathCS(C Str &a, C Str &b) {return ComparePath(a, b, true );} // compare paths Case-  Sensitive, you can use this function directly to other parts of the engine which require comparison functions in this format

Int CompareNumber    (CChar  *a, CChar  *b, Bool case_sensitive=false); // compare texts with correct number support, for example "value 2" and "value 10" will be sorted according to the number value (2 vs 10) and not the first different character ('2' vs '1'), returns -1, 0, +1
Int CompareNumber    (CChar8 *a, CChar8 *b, Bool case_sensitive=false); // compare texts with correct number support, for example "value 2" and "value 10" will be sorted according to the number value (2 vs 10) and not the first different character ('2' vs '1'), returns -1, 0, +1
Int ComparePathNumber(CChar  *a, CChar  *b, Bool case_sensitive=false); // compare paths with correct number support, for example "value 2" and "value 10" will be sorted according to the number value (2 vs 10) and not the first different character ('2' vs '1'), returns -1, 0, +1 (this function works the same as 'CompareNumber', except that '/' is treated as equal to '\\')
Int ComparePathNumber(CChar8 *a, CChar8 *b, Bool case_sensitive=false); // compare paths with correct number support, for example "value 2" and "value 10" will be sorted according to the number value (2 vs 10) and not the first different character ('2' vs '1'), returns -1, 0, +1 (this function works the same as 'CompareNumber', except that '/' is treated as equal to '\\')

inline Int CompareNumberCI(C Str &a, C Str &b) {return CompareNumber(a, b, false);} // compare paths using 'CompareNumber' Case-Insensitive, you can use this function directly to other parts of the engine which require comparison functions in this format
inline Int CompareNumberCS(C Str &a, C Str &b) {return CompareNumber(a, b, true );} // compare paths using 'CompareNumber' Case-  Sensitive, you can use this function directly to other parts of the engine which require comparison functions in this format

inline Int ComparePathNumberCI(C Str &a, C Str &b) {return ComparePathNumber(a, b, false);} // compare paths using 'ComparePathNumber' Case-Insensitive, you can use this function directly to other parts of the engine which require comparison functions in this format
inline Int ComparePathNumberCS(C Str &a, C Str &b) {return ComparePathNumber(a, b, true );} // compare paths using 'ComparePathNumber' Case-  Sensitive, you can use this function directly to other parts of the engine which require comparison functions in this format

Bool Starts    (CChar  *t, CChar  *start, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 't' starts with 'start'
Bool Starts    (CChar  *t, CChar8 *start, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 't' starts with 'start'
Bool Starts    (CChar8 *t, CChar  *start, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 't' starts with 'start'
Bool Starts    (CChar8 *t, CChar8 *start, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 't' starts with 'start'
Bool Ends      (CChar  *t, CChar  *end  , Bool case_sensitive=false                                     ); // if 't' ends   with 'end'
Bool Ends      (CChar  *t, CChar8 *end  , Bool case_sensitive=false                                     ); // if 't' ends   with 'end'
Bool Ends      (CChar8 *t, CChar  *end  , Bool case_sensitive=false                                     ); // if 't' ends   with 'end'
Bool Ends      (CChar8 *t, CChar8 *end  , Bool case_sensitive=false                                     ); // if 't' ends   with 'end'
Bool StartsPath(CChar  *t, CChar  *start                                                                ); // if 't' starts with 'start' path, (this function works the same as 'Starts', except that '/' is treated as equal to '\\')
Bool StartsPath(CChar  *t, CChar8 *start                                                                ); // if 't' starts with 'start' path, (this function works the same as 'Starts', except that '/' is treated as equal to '\\')
Bool StartsPath(CChar8 *t, CChar  *start                                                                ); // if 't' starts with 'start' path, (this function works the same as 'Starts', except that '/' is treated as equal to '\\')
Bool StartsPath(CChar8 *t, CChar8 *start                                                                ); // if 't' starts with 'start' path, (this function works the same as 'Starts', except that '/' is treated as equal to '\\')

Bool Contains   (C Str  &src,  Char   c                                                                ); // if 'src' contains 'c' character
Bool Contains   (C Str  &src,  Char8  c                                                                ); // if 'src' contains 'c' character
Bool Contains   (C Str8 &src,  Char   c                                                                ); // if 'src' contains 'c' character
Bool Contains   (C Str8 &src,  Char8  c                                                                ); // if 'src' contains 'c' character
Bool Contains   (CChar  *src,  Char   c                                                                ); // if 'src' contains 'c' character
Bool Contains   (CChar  *src,  Char8  c                                                                ); // if 'src' contains 'c' character
Bool Contains   (CChar8 *src,  Char   c                                                                ); // if 'src' contains 'c' character
Bool Contains   (CChar8 *src,  Char8  c                                                                ); // if 'src' contains 'c' character
Bool Contains   (CChar  *src, CChar  *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains 't' text
Bool Contains   (CChar  *src, CChar8 *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains 't' text
Bool Contains   (CChar8 *src, CChar  *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains 't' text
Bool Contains   (CChar8 *src, CChar8 *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains 't' text
Bool ContainsAny(CChar  *src, CChar  *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains any words from 't' (words are separated by spaces)
Bool ContainsAny(CChar  *src, CChar8 *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains any words from 't' (words are separated by spaces)
Bool ContainsAny(CChar8 *src, CChar  *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains any words from 't' (words are separated by spaces)
Bool ContainsAny(CChar8 *src, CChar8 *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains any words from 't' (words are separated by spaces)
Bool ContainsAll(CChar  *src, CChar  *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains all words from 't' (words are separated by spaces)
Bool ContainsAll(CChar  *src, CChar8 *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains all words from 't' (words are separated by spaces)
Bool ContainsAll(CChar8 *src, CChar  *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains all words from 't' (words are separated by spaces)
Bool ContainsAll(CChar8 *src, CChar8 *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // if 'src' contains all words from 't' (words are separated by spaces)

Str SkipWhiteChars(C Str &t              ); // skip all starting white chars, Sample Usage: SkipWhiteChars("   a b c") -> "a b c"
Str SkipStartPath (C Str &t, C Str &start); // if 't' starts with 'start' path then return 't' after   'start', in other case return full 't', Sample Usage: SkipStartPath("C:/Folder/Temp/file.ext", "C:/Folder") -> "Temp/file.ext" (treats '/' as equal to '\\')
Str SkipStart     (C Str &t, C Str &start); // if 't' starts with 'start'      then return 't' after   'start', in other case return full 't', Sample Usage: SkipStart    ("abcd", "ab") -> "cd", SkipStart("abcd", "ef") -> "abcd"
Str SkipEnd       (C Str &t, C Str &end  ); // if 't' ends   with 'end'        then return 't' without 'end'  , in other case return full 't', Sample Usage: SkipEnd      ("abcd", "cd") -> "ab", SkipEnd  ("abcd", "ef") -> "abcd"

Str Replace(C Str &text, Char   from, Char   to                                                                ); // replace 'from' -> 'to' in 'text', Sample Usage: Replace("abcde", 'd', '7') -> "abc7e"
Str Replace(C Str &text, C Str &from, C Str &to, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // replace 'from' -> 'to' in 'text', Sample Usage: Replace("This is not a cat", "not ", "") -> "This is a cat"

Str  Trim(C Str  &text, Int pos, Int length); // trim string by removing start and end, to keep only the part starting at 'pos' of 'length' length
Str8 Trim(C Str8 &text, Int pos, Int length); // trim string by removing start and end, to keep only the part starting at 'pos' of 'length' length

Str CaseDown(C Str &t); // return case down version of the string, Sample Usage: CaseDown("AbCdEFG") -> "abcdefg"
Str CaseUp  (C Str &t); // return case up   version of the string, Sample Usage: CaseUp  ("AbCdEFG") -> "ABCDEFG"

void      Split(MemPtr<Str> splits, C Str &string, Char separator); // split 'string' into an array of strings separated by 'separator', Sample Usage: Split("123:45::6:", ':') -> {"123", "45", "", "6", ""}
Memc<Str> Split(                    C Str &string, Char separator); // split 'string' into an array of strings separated by 'separator', Sample Usage: Split("123:45::6:", ':') -> {"123", "45", "", "6", ""}

void Tokenize(MemPtr<Str> tokens, C Str &string); // tokenize 'string' into tokens, this works by removing all white chars and making sure that symbols are separate from words, Sample Usage: Split("Sample value   = 15") -> {"Sample", "value", "=", "15"}

Int     TextPosI(CChar  *src, Char  c); // get            position of first 'c' character in 'src' text (-1   if none)
Int     TextPosI(CChar8 *src, Char8 c); // get            position of first 'c' character in 'src' text (-1   if none)
CChar * TextPos (CChar  *src, Char  c); // get pointer to position of first 'c' character in 'src' text (null if none)
CChar8* TextPos (CChar8 *src, Char8 c); // get pointer to position of first 'c' character in 'src' text (null if none)
 Char * TextPos ( Char  *src, Char  c); // get pointer to position of first 'c' character in 'src' text (null if none)
 Char8* TextPos ( Char8 *src, Char8 c); // get pointer to position of first 'c' character in 'src' text (null if none)

Int     TextPosI(CChar  *src, CChar  *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // get            position of first 't' text in 'src' text (-1   if none)
Int     TextPosI(CChar  *src, CChar8 *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // get            position of first 't' text in 'src' text (-1   if none)
Int     TextPosI(CChar8 *src, CChar8 *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // get            position of first 't' text in 'src' text (-1   if none)
CChar * TextPos (CChar  *src, CChar  *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // get pointer to position of first 't' text in 'src' text (null if none)
CChar * TextPos (CChar  *src, CChar8 *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // get pointer to position of first 't' text in 'src' text (null if none)
CChar8* TextPos (CChar8 *src, CChar8 *t, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // get pointer to position of first 't' text in 'src' text (null if none)

Str StrInside(C Str &str, C Str &from, C Str &to, Bool case_sensitive=false, WHOLE_WORD whole_word=WHOLE_WORD_NO); // get part of the string located between 'from' and 'to' strings, "" is returned if not found

// convert from value to text, 'digits'=number of digits to generate (-1=autodetect), 'separate'=number of digits to be separated with a space ' ', 'prefix'=if insert a prefix ("0b" for binary and "0x" for hexadecimal)
   CChar8* TextBool(Bool  b                                                     ); // return b ? "true" : "false";
       Str TextInt (Int   i, Int digits   =-1, Int separate=0                   );
       Str TextInt (Long  i, Int digits   =-1, Int separate=0                   );
       Str TextInt (UInt  u, Int digits   =-1, Int separate=0                   );
       Str TextInt (ULong u, Int digits   =-1, Int separate=0                   );
       Str TextBin (UInt  u, Int digits   =-1, Int separate=0, Bool prefix=false);
       Str TextBin (ULong u, Int digits   =-1, Int separate=0, Bool prefix=false);
       Str TextHex (UInt  u, Int digits   =-1, Int separate=0, Bool prefix=false);
       Str TextHex (ULong u, Int digits   =-1, Int separate=0, Bool prefix=false);
       Str TextHex (Flt   r                                                     );
       Str TextHex (Dbl   r                                                     );
       Str TextReal(Dbl   r, Int precision=-6, Int separate=0                   );
inline Str TextFlt (Dbl   r,                   Int separate=0                   ) {return TextReal(r, 3, separate);}
inline Str TextDbl (Dbl   r,                   Int separate=0                   ) {return TextReal(r, 9, separate);}
       Str TextVer (C VecI4 &ver                                                );

Str TextHexMem(CPtr data, Int size, Bool prefix=false); // convert memory to its hex representation, 'prefix'=if include "0x" prefix at the start

// convert from text to value
CChar * TextValue(CChar  *t, CalcValue &value, Bool allow_real=true); // sets 'value' according to 't' input, returns pointer to the place in 't' after it stopped reading, 'allow_real'=if allow parsing floating point values
CChar8* TextValue(CChar8 *t, CalcValue &value, Bool allow_real=true); // sets 'value' according to 't' input, returns pointer to the place in 't' after it stopped reading, 'allow_real'=if allow parsing floating point values

Bool   TextBool  (CChar *t);   Bool   TextBool  (CChar8 *t); // false     on fail (if 't' string is empty, then 'false' is returned)
Bool   TextBool1 (CChar *t);   Bool   TextBool1 (CChar8 *t); // false     on fail (if 't' string is empty, then 'true'  is returned)
Int    TextInt   (CChar *t);   Int    TextInt   (CChar8 *t); // 0         on fail
UInt   TextUInt  (CChar *t);   UInt   TextUInt  (CChar8 *t); // 0         on fail
Long   TextLong  (CChar *t);   Long   TextLong  (CChar8 *t); // 0         on fail
ULong  TextULong (CChar *t);   ULong  TextULong (CChar8 *t); // 0         on fail
Flt    TextFlt   (CChar *t);   Flt    TextFlt   (CChar8 *t); // 0         on fail
Dbl    TextDbl   (CChar *t);   Dbl    TextDbl   (CChar8 *t); // 0         on fail
Vec2   TextVec2  (CChar *t);   Vec2   TextVec2  (CChar8 *t); // (0,0)     on fail
VecD2  TextVecD2 (CChar *t);   VecD2  TextVecD2 (CChar8 *t); // (0,0)     on fail
VecI2  TextVecI2 (CChar *t);   VecI2  TextVecI2 (CChar8 *t); // (0,0)     on fail
VecB2  TextVecB2 (CChar *t);   VecB2  TextVecB2 (CChar8 *t); // (0,0)     on fail
VecSB2 TextVecSB2(CChar *t);   VecSB2 TextVecSB2(CChar8 *t); // (0,0)     on fail
VecUS2 TextVecUS2(CChar *t);   VecUS2 TextVecUS2(CChar8 *t); // (0,0)     on fail
Vec    TextVec   (CChar *t);   Vec    TextVec   (CChar8 *t); // (0,0,0)   on fail
VecD   TextVecD  (CChar *t);   VecD   TextVecD  (CChar8 *t); // (0,0,0)   on fail
VecI   TextVecI  (CChar *t);   VecI   TextVecI  (CChar8 *t); // (0,0,0)   on fail
VecB   TextVecB  (CChar *t);   VecB   TextVecB  (CChar8 *t); // (0,0,0)   on fail
VecSB  TextVecSB (CChar *t);   VecSB  TextVecSB (CChar8 *t); // (0,0,0)   on fail
VecUS  TextVecUS (CChar *t);   VecUS  TextVecUS (CChar8 *t); // (0,0,0)   on fail
Vec4   TextVec4  (CChar *t);   Vec4   TextVec4  (CChar8 *t); // (0,0,0,0) on fail
VecD4  TextVecD4 (CChar *t);   VecD4  TextVecD4 (CChar8 *t); // (0,0,0,0) on fail
VecI4  TextVecI4 (CChar *t);   VecI4  TextVecI4 (CChar8 *t); // (0,0,0,0) on fail
VecB4  TextVecB4 (CChar *t);   VecB4  TextVecB4 (CChar8 *t); // (0,0,0,0) on fail
VecSB4 TextVecSB4(CChar *t);   VecSB4 TextVecSB4(CChar8 *t); // (0,0,0,0) on fail
Color  TextColor (CChar *t);   Color  TextColor (CChar8 *t); // (0,0,0,0) on fail
UID    TextUID   (CChar *t);   UID    TextUID   (CChar8 *t); // 'UIDZero' on fail
VecI4  TextVer   (CChar *t);   VecI4  TextVer   (CChar8 *t); // (0,0,0,0) on fail

Str  FromUTF8(CChar8 *text); // convert 'text' from UTF-8 format into Str
Str8 UTF8    (C Str  &text); // convert 'text' from   Str        into UTF-8 format

Str Censor(C Str &text); // censor 'text' by removing profanities [Supported Platforms: NintendoSwitch]

// compare strings
   // Str == (Str, Str8, CChar*, CChar8*, Char, Char8)
   inline Bool operator==(C Str  &a, C Str  &b) {return Equal(a, b);}
   inline Bool operator==(C Str  &a, C Str8 &b) {return Equal(a, b);}
   inline Bool operator==(C Str  &s, CChar  *t) {return Equal(s, t);}
   inline Bool operator==(C Str  &s, CChar8 *t) {return Equal(s, t);}
   inline Bool operator==(CChar  *t, C Str  &s) {return Equal(s, t);}
   inline Bool operator==(CChar8 *t, C Str  &s) {return Equal(s, t);}
   inline Bool operator==(C Str  &s, Char    c) {return s.length()==1 && !Compare(s[0], c);}
   inline Bool operator==(C Str  &s, Char8   c) {return s.length()==1 && !Compare(s[0], c);}
   inline Bool operator==(Char    c, C Str  &s) {return s.length()==1 && !Compare(s[0], c);}
   inline Bool operator==(Char8   c, C Str  &s) {return s.length()==1 && !Compare(s[0], c);}

   // Str != (Str, Str8, CChar*, CChar8*, Char, Char8)
   inline Bool operator!=(C Str  &a, C Str  &b) {return !Equal(a, b);}
   inline Bool operator!=(C Str  &a, C Str8 &b) {return !Equal(a, b);}
   inline Bool operator!=(C Str  &s, CChar  *t) {return !Equal(s, t);}
   inline Bool operator!=(C Str  &s, CChar8 *t) {return !Equal(s, t);}
   inline Bool operator!=(CChar  *t, C Str  &s) {return !Equal(s, t);}
   inline Bool operator!=(CChar8 *t, C Str  &s) {return !Equal(s, t);}
   inline Bool operator!=(C Str  &s, Char    c) {return s.length()!=1 || Compare(s[0], c);}
   inline Bool operator!=(C Str  &s, Char8   c) {return s.length()!=1 || Compare(s[0], c);}
   inline Bool operator!=(Char    c, C Str  &s) {return s.length()!=1 || Compare(s[0], c);}
   inline Bool operator!=(Char8   c, C Str  &s) {return s.length()!=1 || Compare(s[0], c);}

   // Str8 == (Str, Str8, CChar*, CChar8*, Char, Char8)
   inline Bool operator==(C Str8 &a, C Str  &b) {return Equal(a, b);}
   inline Bool operator==(C Str8 &a, C Str8 &b) {return Equal(a, b);}
   inline Bool operator==(C Str8 &s, CChar  *t) {return Equal(s, t);}
   inline Bool operator==(C Str8 &s, CChar8 *t) {return Equal(s, t);}
   inline Bool operator==(CChar  *t, C Str8 &s) {return Equal(s, t);}
   inline Bool operator==(CChar8 *t, C Str8 &s) {return Equal(s, t);}
   inline Bool operator==(C Str8 &s, Char    c) {return s.length()==1 && !Compare(s[0], c);}
   inline Bool operator==(C Str8 &s, Char8   c) {return s.length()==1 && !Compare(s[0], c);}
   inline Bool operator==(Char    c, C Str8 &s) {return s.length()==1 && !Compare(s[0], c);}
   inline Bool operator==(Char8   c, C Str8 &s) {return s.length()==1 && !Compare(s[0], c);}

   // Str8 != (Str, Str8, CChar*, CChar8*, Char, Char8)
   inline Bool operator!=(C Str8 &a, C Str  &b) {return !Equal(a, b);}
   inline Bool operator!=(C Str8 &a, C Str8 &b) {return !Equal(a, b);}
   inline Bool operator!=(C Str8 &s, CChar  *t) {return !Equal(s, t);}
   inline Bool operator!=(C Str8 &s, CChar8 *t) {return !Equal(s, t);}
   inline Bool operator!=(CChar  *t, C Str8 &s) {return !Equal(s, t);}
   inline Bool operator!=(CChar8 *t, C Str8 &s) {return !Equal(s, t);}
   inline Bool operator!=(C Str8 &s, Char    c) {return s.length()!=1 || Compare(s[0], c);}
   inline Bool operator!=(C Str8 &s, Char8   c) {return s.length()!=1 || Compare(s[0], c);}
   inline Bool operator!=(Char    c, C Str8 &s) {return s.length()!=1 || Compare(s[0], c);}
   inline Bool operator!=(Char8   c, C Str8 &s) {return s.length()!=1 || Compare(s[0], c);}
/******************************************************************************/
