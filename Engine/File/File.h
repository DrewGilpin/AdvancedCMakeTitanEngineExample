/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************

   Use 'File' to handle binary files management.

/******************************************************************************/
struct File
{
   // manage
   File& del(); // manually delete the file object (this does not delete the file on the disk, it only closes the handle of the C++ file object and releases used memory)

   Bool   editTry   (C Str     &name, const_mem_addr Cipher *cipher=null); // try to edit        stdio file, reading is     allowed in this mode, false on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), if a file doesn't exist then a new file is created, if a file already exists then that file is opened, its contents are preserved, position is set to the start
   Bool appendTry   (C Str     &name, const_mem_addr Cipher *cipher=null); // try to append      stdio file, reading is     allowed in this mode, false on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), if a file doesn't exist then a new file is created, if a file already exists then that file is opened, its contents are preserved, position is set to the end
   Bool  writeTry   (C Str     &name, const_mem_addr Cipher *cipher=null); // try to write to    stdio file, reading is     allowed in this mode, false on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), if a file doesn't exist then a new file is created, if a file already exists then that file is opened, its contents are destroyed, position is set to the start, size is reset to 0
   Bool   readStdTry(C Str     &name, const_mem_addr Cipher *cipher=null); // try to read        stdio file, writing is not allowed in this mode, false on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool   readTry   (C Str     &name, const_mem_addr Cipher *cipher=null); // try to read Pak or stdio file, writing is not allowed in this mode, false on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool   readTry   (C UID     &id  , const_mem_addr Cipher *cipher=null); // try to read Pak or stdio file, writing is not allowed in this mode, false on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool   readTry   (C Str     &name, C Pak    &pak                     ); // try to read Pak          file, writing is not allowed in this mode, false on fail
   Bool   readTry   (C UID     &id  , C Pak    &pak                     ); // try to read Pak          file, writing is not allowed in this mode, false on fail
   Bool   readTry   (C Str     &name, C PakSet &paks                    ); // try to read Pak          file, writing is not allowed in this mode, false on fail
   Bool   readTry   (C UID     &id  , C PakSet &paks                    ); // try to read Pak          file, writing is not allowed in this mode, false on fail
   Bool   readTry   (C PakFile &file, C Pak    &pak                     ); // try to read Pak          file, writing is not allowed in this mode, false on fail

   File& writeMemFixed(           Int size    , const_mem_addr Cipher *cipher=null); // start writing to   fixed     memory file   , reading is     allowed in this mode, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File& writeMemDest ( Ptr data, Int size    , const_mem_addr Cipher *cipher=null); // start writing to   fixed     memory address, reading is     allowed in this mode, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File& writeMem     (UInt block_elms=64*1024, const_mem_addr Cipher *cipher=null); // start writing to   resizable memory file   , reading is     allowed in this mode, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File&  readMem     (CPtr data, Int size    , const_mem_addr Cipher *cipher=null); // start reading from fixed     memory address, writing is not allowed in this mode, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)

   File& mustEdit   (C Str     &name, const_mem_addr Cipher *cipher=null); // edit        stdio file, reading is     allowed in this mode, Exit on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), if a file doesn't exist then a new file is created, if a file already exists then that file is opened, its contents are preserved, position is set to the start
   File& mustAppend (C Str     &name, const_mem_addr Cipher *cipher=null); // append      stdio file, reading is     allowed in this mode, Exit on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), if a file doesn't exist then a new file is created, if a file already exists then that file is opened, its contents are preserved, position is set to the end
   File& mustWrite  (C Str     &name, const_mem_addr Cipher *cipher=null); // write to    stdio file, reading is     allowed in this mode, Exit on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), if a file doesn't exist then a new file is created, if a file already exists then that file is opened, its contents are destroyed, position is set to the start, size is reset to 0
   File& mustReadStd(C Str     &name, const_mem_addr Cipher *cipher=null); // read        stdio file, writing is not allowed in this mode, Exit on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File& mustRead   (C Str     &name, const_mem_addr Cipher *cipher=null); // read Pak or stdio file, writing is not allowed in this mode, Exit on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File& mustRead   (C UID     &id  , const_mem_addr Cipher *cipher=null); // read Pak or stdio file, writing is not allowed in this mode, Exit on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File& mustRead   (C Str     &name, C Pak    &pak                     ); // read Pak          file, writing is not allowed in this mode, Exit on fail
   File& mustRead   (C UID     &id  , C Pak    &pak                     ); // read Pak          file, writing is not allowed in this mode, Exit on fail
   File& mustRead   (C Str     &name, C PakSet &paks                    ); // read Pak          file, writing is not allowed in this mode, Exit on fail
   File& mustRead   (C UID     &id  , C PakSet &paks                    ); // read Pak          file, writing is not allowed in this mode, Exit on fail
   File& mustRead   (C PakFile &file, C Pak    &pak                     ); // read Pak          file, writing is not allowed in this mode, Exit on fail

   // get / set
   Bool  is     (        )C {return _type!=0    ;} // if  file is opened
   Bool  pos    (Long pos);                        // set position, false on fail
   Long  pos    (        )C {return _pos        ;} // get position
   Long  size   (        )C {return _size       ;} // get size
   Long  left   (        )C {return _size-_pos  ;} // get size left (number of bytes from current position to the end of the file)
   Bool  end    (        )C {return _pos>=_size ;} // if  current position is at the end of the file
   Bool  skip   (Long n  )  {return  pos(_pos+n);} // skip 'n' bytes going forward
   Bool       ok(        )C {return _ok         ;} // check if no errors occurred during reading/writing. When a new file is opened this will be set to true by default, if any 'put' or 'get' call will fail then this will be set to false
   File& resetOK(        )  {_ok=true;  return T;} // reset 'ok' status to default

   // put / get
   Bool get( Ptr data, Int size); // read  from file to 'data' memory, false on fail, if error occurs then 'ok' will be set to false
   Bool put(CPtr data, Int size); // write from 'data' memory to file, false on fail, if error occurs then 'ok' will be set to false

   T1(TYPE) Bool  put       (C TYPE     &t       ) {return put(&t, SIZE(TYPE)  );} // write raw memory              of 't' object
   T1(TYPE) Bool  get       (  TYPE     &t       ) {return get(&t, SIZE(TYPE)  );} // read  raw memory              to 't' object
   T1(TYPE) Bool  putN      (C TYPE     *t, Int n) {return put( t, SIZE(TYPE)*n);} // write raw array of 'n' number of 't' objects
   T1(TYPE) Bool  getN      (  TYPE     *t, Int n) {return get( t, SIZE(TYPE)*n);} // read  raw array to 'n' number of 't' objects
   T1(TYPE) File& operator<<(C TYPE     &t       ) {       put( t);     return T;} // write raw memory              of 't' object
   T1(TYPE) File& operator>>(  TYPE     &t       ) {       get( t);     return T;} // read  raw memory              to 't' object
            File& operator<<(C Str8     &s       ) {return putStr(s);            } // write string
            File& operator<<(C Str      &s       ) {return putStr(s);            } // write string
            File& operator<<(C MultiStr &s       ) {       s.save(T);   return T;} // write string
            File& operator>>(  Str8     &s       ) {return getStr(s);            } // read  string
            File& operator>>(  Str      &s       ) {return getStr(s);            } // read  string
            File& operator>>(  MultiStr &s       ) {       s.load(T);   return T;} // read  string

   File& putBool  (  Bool  b) {T<<b; return T;}    Bool  getBool  () {Bool   b; T>>b; return b;} // write/read  Bool
   File& putSByte ( SByte  b) {T<<b; return T;}   SByte  getSByte () {SByte  b; T>>b; return b;} // write/read SByte
   File& putByte  (  Byte  b) {T<<b; return T;}    Byte  getByte  () {Byte   b; T>>b; return b;} // write/read  Byte
   File& putShort (  Short i) {T<<i; return T;}    Short getShort () {Short  i; T>>i; return i;} // write/read  Short
   File& putUShort( UShort u) {T<<u; return T;}   UShort getUShort() {UShort u; T>>u; return u;} // write/read UShort
   File& putInt   (  Int   i) {T<<i; return T;}    Int   getInt   () {Int    i; T>>i; return i;} // write/read  Int
   File& putUInt  ( UInt   u) {T<<u; return T;}   UInt   getUInt  () {UInt   u; T>>u; return u;} // write/read UInt
   File& putLong  (  Long  i) {T<<i; return T;}    Long  getLong  () {Long   i; T>>i; return i;} // write/read  Long
   File& putULong ( ULong  u) {T<<u; return T;}   ULong  getULong () {ULong  u; T>>u; return u;} // write/read ULong
   File& putFlt   (  Flt   f) {T<<f; return T;}    Flt   getFlt   () {Flt    f; T>>f; return f;} // write/read  Float
   File& putDbl   (  Dbl   d) {T<<d; return T;}    Dbl   getDbl   () {Dbl    d; T>>d; return d;} // write/read  Double
   File& putUID   (C UID  &i) {T<<i; return T;}    UID   getUID   () {UID    i; T>>i; return i;} // write/read  UID

   File&  putStr(CChar8 *t); // write string
   File&  putStr(CChar  *t); // write string
   File&  putStr(C Str8 &s); // write string
   File&  putStr(C Str  &s); // write string
   Str    getStr(         ); // read  string, this method can be used to read previously written strings using all 'putStr' methods
   File&  getStr(  Str8 &s); // read  string, this method can be used to read previously written strings using all 'putStr' methods
   File&  getStr(  Str  &s); // read  string, this method can be used to read previously written strings using all 'putStr' methods
   File& skipStr(         ); // skip  string, this method can be used to skip previously written strings using all 'putStr' methods, this method works by reading a string without storing it

                       File& getStr(Char8  *t, Int t_elms);                          // read string into 't' array, 't_elms'=number of elements in the array, this method can be used to read previously written strings using all 'putStr' methods
                       File& getStr(Char   *t, Int t_elms);                          // read string into 't' array, 't_elms'=number of elements in the array, this method can be used to read previously written strings using all 'putStr' methods
   template<Int elms>  File& getStr(Char8 (&t)[elms]     ) {return getStr(t, elms);} // read string into 't' array,                                           this method can be used to read previously written strings using all 'putStr' methods
   template<Int elms>  File& getStr(Char  (&t)[elms]     ) {return getStr(t, elms);} // read string into 't' array,                                           this method can be used to read previously written strings using all 'putStr' methods

   File& putAsset  (CChar *name); // write asset location, this method is optimized for saving asset locations, typically assets are stored with file name based on UID, in such case this method can detect that and save the location using fewer bytes
   File& putAsset  (C UID &id  ); // write asset location, this method is optimized for saving asset locations, typically assets are stored with file name based on UID, in such case this method can detect that and save the location using fewer bytes
   File& getAsset  (  Str &s   ); // read  asset location, this method can be used to read previously written asset location using all 'putAsset' methods, returns ""        on fail
   Str   getAsset  (           ); // read  asset location, this method can be used to read previously written asset location using all 'putAsset' methods, returns ""        on fail
   UID   getAssetID(           ); // read  asset location, this method can be used to read previously written asset location using all 'putAsset' methods, returns 'UIDZero' on fail

   // compress / decompress
   File& cmpIntV   (  Int      i);                                                              //   compress any Int to   variable number of bytes (1..5) depending on the value of the Int (values -64..63 will require only 1 byte, -8192..8191 will require 2 bytes, -1048576..1048575 will require 3 bytes, bigger values will require more bytes)
   File& decIntV   (  Int     &i);   Int     decIntV   () {Int     i; decIntV   (i); return i;} // decompress any Int from variable number of bytes (1..5)

   File& cmpUIntV  ( UInt      u);                                                              //   compress any UInt to   variable number of bytes (1..5) depending on the value of the UInt (values 0..127 will require only 1 byte, 128..16383 will require 2 bytes, 16384..2097151 will require 3 bytes, bigger values will require more bytes)
   File& decUIntV  ( UInt     &u);   UInt    decUIntV  () {UInt    u; decUIntV  (u); return u;} // decompress any UInt from variable number of bytes (1..5)

   File& cmpLongV  (  Long     l);                                                              //   compress any Long to   variable number of bytes (1..9) depending on the value of the Long (values -64..63 will require only 1 byte, -8192..8191 will require 2 bytes, -1048576..1048575 will require 3 bytes, bigger values will require more bytes)
   File& decLongV  (  Long    &l);   Long    decLongV  () {Long    l; decLongV  (l); return l;} // decompress any Long from variable number of bytes (1..9)

   File& cmpULongV ( ULong     u);                                                              //   compress any ULong to   variable number of bytes (1..9) depending on the value of the ULong (values 0..127 will require only 1 byte, 128..16383 will require 2 bytes, 16384..2097151 will require 3 bytes, bigger values will require more bytes)
   File& decULongV ( ULong    &u);   ULong   decULongV () {ULong   u; decULongV (u); return u;} // decompress any ULong from variable number of bytes (1..9)

   File& cmpFlt3cm (C Flt     &r);                                                              //   compress Float in range -83,800 .. 83,800 to   3 bytes with precision of 0.01 (this covers range of -83..83 kilometers with 1 centimeter precision)
   File& decFlt3cm (  Flt     &r);   Flt     decFlt3cm () {Flt     r; decFlt3cm (r); return r;} // decompress Float in range -83,800 .. 83,800 from 3 bytes with precision of 0.01 (this covers range of -83..83 kilometers with 1 centimeter precision)

   File& cmpSatFlt1(C Flt     &r);                                                              //   compress Saturated Float in range 0..1 to   1 byte  (having   256 possible values, and precision of ~0.00400)
   File& cmpSatFlt2(C Flt     &r);                                                              //   compress Saturated Float in range 0..1 to   2 bytes (having 65536 possible values, and precision of ~0.00001)
   File& decSatFlt1(  Flt     &r);   Flt     decSatFlt1() {Flt     r; decSatFlt1(r); return r;} // decompress Saturated Float in range 0..1 from 1 byte
   File& decSatFlt2(  Flt     &r);   Flt     decSatFlt2() {Flt     r; decSatFlt2(r); return r;} // decompress Saturated Float in range 0..1 from 2 bytes

   File& cmpAngle1 (C Flt     &r);                                                              //   compress Angle Float (0..PI2) to   1 byte  (having   256 possible values, and precision of ~0.02000)
   File& cmpAngle2 (C Flt     &r);                                                              //   compress Angle Float (0..PI2) to   2 bytes (having 65536 possible values, and precision of ~0.00009)
   File& decAngle1 (  Flt     &r);   Flt     decAngle1 () {Flt     r; decAngle1 (r); return r;} // decompress Angle Float          from 1 byte
   File& decAngle2 (  Flt     &r);   Flt     decAngle2 () {Flt     r; decAngle2 (r); return r;} // decompress Angle Float          from 2 bytes

   File& cmpDir2   (C Vec     &v);                                                              //   compress Normalized Direction Vector to   2 bytes
   File& cmpDir3   (C Vec     &v);                                                              //   compress Normalized Direction Vector to   3 bytes
   File& decDir2   (  Vec     &v);   Vec     decDir2   () {Vec     v; decDir2   (v); return v;} // decompress Normalized Direction Vector from 2 bytes
   File& decDir3   (  Vec     &v);   Vec     decDir3   () {Vec     v; decDir3   (v); return v;} // decompress Normalized Direction Vector from 3 bytes

   File& cmpOrient2(C Matrix3 &m);                                                              //   compress Orientation to   2 bytes (its scale is ignored, only rotation is saved)
   File& cmpOrient3(C Matrix3 &m);                                                              //   compress Orientation to   3 bytes (its scale is ignored, only rotation is saved)
   File& cmpOrient4(C Matrix3 &m);                                                              //   compress Orientation to   4 bytes (its scale is ignored, only rotation is saved)
   File& decOrient2(  Matrix3 &m);   Matrix3 decOrient2() {Matrix3 m; decOrient2(m); return m;} // decompress Orientation from 2 bytes
   File& decOrient3(  Matrix3 &m);   Matrix3 decOrient3() {Matrix3 m; decOrient3(m); return m;} // decompress Orientation from 3 bytes
   File& decOrient4(  Matrix3 &m);   Matrix3 decOrient4() {Matrix3 m; decOrient4(m); return m;} // decompress Orientation from 4 bytes

   // hashes
   UInt       crc32          (Long max_size=-1); // get file CRC32            from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)
   UInt           xxHash32   (Long max_size=-1); // get file      xxHash32    from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)
   UInt           xxHash64_32(Long max_size=-1); // get file      xxHash64-32 from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)
   ULong          xxHash64   (Long max_size=-1); // get file      xxHash64    from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)
   UInt       spookyHash32   (Long max_size=-1); // get file Spooky Hash32    from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)
   ULong      spookyHash64   (Long max_size=-1); // get file Spooky Hash64    from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)
   UID        spookyHash128  (Long max_size=-1); // get file Spooky Hash128   from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)
   ULong       metroHash64   (Long max_size=-1); // get file Metro  Hash64    from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)
   UID         metroHash128  (Long max_size=-1); // get file Metro  Hash128   from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)
   UID        md5            (Long max_size=-1); // get file MD5              from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)
   SHA1::Hash sha1           (Long max_size=-1); // get file SHA1             from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)
   SHA2::Hash sha2           (Long max_size=-1); // get file SHA2             from current position to the end, this reads the data and modifies file position, 'max_size'=number of bytes to process (-1=all remaining)

   // operations
   File& reset  (                            );   // reset all written  data to the memory, this method affects only files which have been created using 'writeMem', this method sets file position and size to zero, but keeps the file in mode available for writing new data
   Bool  flush  (                            );   // flush all buffered data to the disk  , false on fail, this method doesn't set 'ok' to false on error
   Bool  flushOK(                            );   // flush all buffered data to the disk and check if no other errors occurred before - "flush() && ok()", false on fail
   Bool  equal  (File &f   , Long max_size=-1);   // if has the same data as 'f' file   (only data from current positions to the end are compared, and not from the start to the end), 'max_size'=number of bytes to compare (-1=all remaining)
   Bool  copy   (File &dest, Long max_size=-1);   // copy file to 'dest', false on fail (only data from current position  to the end are copied  , and not from the start to the end), 'max_size'=number of bytes to copy    (-1=all remaining), 'dest' should be already opened for writing
   Bool  size   (Long size);                      // set file size                    , false on fail
   Bool  trim   (         ) {return size(pos());} // set file size to current position, false on fail

           ~File() {del();}
            File();
   explicit File(C Str     &name,              const_mem_addr Cipher *cipher=null); // read Pak or stdio file, Exit on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   explicit File(C UID     &id  ,              const_mem_addr Cipher *cipher=null); // read Pak or stdio file, Exit on fail, 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   explicit File(C Str     &name, C Pak &pak                                     ); // read Pak          file, Exit on fail
   explicit File(C PakFile &file, C Pak &pak                                     ); // read Pak          file, Exit on fail
   explicit File( CPtr      data,   Int  size, const_mem_addr Cipher *cipher=null); // start reading from memory address (writing is not allowed in this mode), 'cipher' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)

private:
   Byte       _type;
   Bool       _writable, _ok;
   FILE_PATH  _path;
   Int        _buf_pos, _buf_len, _buf_size, _cipher_offset;
   ULong      _offset, _pos, _size, _full_size;
 C Pak       *_pak;
   Cipher    *_cipher;
   Ptr        _buf;
union
{
      Int         _handle;
   struct
   {
      Ptr         _mem;
      Bool        _allocated;
   };
      Memb<Byte>  _memb;
   struct
   {
      FileStream *_stream;
      CPtr        _stream_buf;
   };
};
#if ANDROID
   Ptr        _aasset;
#endif
   NO_COPY_CONSTRUCTOR(File);
};
/******************************************************************************/
