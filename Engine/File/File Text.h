/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************

   Use 'FileText' to handle text files management.

/******************************************************************************/
enum ENCODING : Byte // text encoding mode
{
   ANSI       , //        8-bit per character
   UTF_16     , //       16-bit per character
   UTF_8      , // variable-bit per character
   UTF_8_NAKED, // variable-bit per character with no Byte Order Mark (BOM)
};
enum INDENT : Byte // indentation mode
{
   INDENT_NONE  , // disabled
   INDENT_TABS  , // use tabs
   INDENT_SPACES, // use spaces
};
/******************************************************************************/
struct FileText
{
   Int    depth ; // depth level which affects indentation when using 'startLine' and 'putLine' methods
   INDENT indent; // indentation mode, default=INDENT_TABS

   // manage
   FileText&   del   (                                                                              ); // delete manually
   Bool       read   (C Str &name                               , const_mem_addr Cipher *cipher=null); // read  from     file  , 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool       read   (C UID &id                                 , const_mem_addr Cipher *cipher=null); // read  from     file  , 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool       read   (C Str &name, Pak &pak                                                         ); // read  from Pak file
   Bool       read   (C UID &id  , Pak &pak                                                         ); // read  from Pak file
   FileText&  readMem(const_mem_addr C Str &data                                                    ); // read  from memory    , 'data'   must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   FileText&  readMem(  CPtr data, Int  size, Int encoding=   -1, const_mem_addr Cipher *cipher=null); // read  from memory    , 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), 'encoding'=encoding of the memory (-1=autodetect)
   FileText& writeMem(                   ENCODING encoding=UTF_8, const_mem_addr Cipher *cipher=null); // write to   memory    , 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool      write   (C Str &name,       ENCODING encoding=UTF_8, const_mem_addr Cipher *cipher=null); // write to   stdio file, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool      append  (C Str &name,       ENCODING encoding=UTF_8, const_mem_addr Cipher *cipher=null); // append     stdio file, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)

   // get
   Bool     end     ()C {return _f.end ();} // if  current position is at the end of the file
   Long     size    ()C {return _f.size();} // get file size
   Long     pos     ()C {return _f.pos ();} // get file position
   ENCODING encoding()C {return _code    ;} // get file encoding

   // read
   FileText& skipLine(       );                                                  // skip text until end of line found
   FileText& fullLine(Str  &s);   Str fullLine() {Str s; fullLine(s); return s;} // read text until end of line found, includes starting white chars (spaces and tabs)
   FileText&  getLine(Str  &s);   Str  getLine() {Str s;  getLine(s); return s;} // read text until end of line found, skips    starting white chars (spaces and tabs)
   FileText&  getLine(Str8 &s);                                                  // read text until end of line found, skips    starting white chars (spaces and tabs)
   FileText&  getAll (Str  &s);   Str  getAll () {Str s;  getAll (s); return s;} // read text until end of file
   Char       getChar(       );                                                  // read a single character

   // write
   FileText& startLine(            ); // write indentation according to 'indent'
   FileText&   endLine(            ); // write end of line marker
   FileText&   putChar(  Char8 c   ); // write a single character
   FileText&   putChar(  Char  c   ); // write a single character
   FileText&   putText(C Str  &text); // write              text
   FileText&   putLine(C Str  &text); // write indentation, text and end of line marker

   // operations
   FileText& rewind ();                        // reset to starting position, this can be useful when wanting to read previously written data
   Bool      ok     ()C {return _f.ok     ();} // check if no errors occurred during reading/writing. When a new file is opened this will be set to true by default, if any read/write call will fail then this will be set to false
   Bool      flush  ()  {return _f.flush  ();} // flush all buffered data to the disk, false on fail
   Bool      flushOK()  {return _f.flushOK();} // flush all buffered data to the disk and check if no other errors occurred before - "flush() && ok()", false on fail
   Bool      copy   (File &dest);              // copy the entire contents (from start to end) of this FileText into 'dest' file, including byte order mark (BOM) if present, false on fail
   Char      posInfo(Long pos, VecI2 &col_line); // get character, its column and line indexes at specified 'pos' file offset (in raw bytes), this method will start reading each character in the file from the start, until 'pos' file offset

   FileText();

private:
   ENCODING _code;
   File     _f;
   NO_COPY_CONSTRUCTOR(FileText);
};
/******************************************************************************/
