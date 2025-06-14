/******************************************************************************/
struct PaletteID
{
   UID  id;
   Byte index;
#if EE_PRIVATE
   void zero() {Zero(T);}
#endif
};
/******************************************************************************/
struct MaterialPalette
{
   // get
   Int          elms      (     )C {return                     _data.elms    ()            ;} // get number of elements
 C MaterialPtr& operator[](Int i)C {return InRange(i, _data) ? _data[i].mtrl : MaterialNull;} // get i-th material
   UIntPtr      memUsage  (     )C {return                     _data.memUsage()            ;} // get memory usage

   Int index (C UID         &material); // get index of desired 'material' in the palette, if 'material' is not listed in the palette it will be added, up to 255 materials can be stored, 0 index is always reserved for null material, -1 on fail
   Int index0(C UID         &material); // get index of desired 'material' in the palette, if 'material' is not listed in the palette it will be added, up to 255 materials can be stored, 0 index is always reserved for null material,  0 on fail
   Int index (C MaterialPtr &material); // get index of desired 'material' in the palette, if 'material' is not listed in the palette it will be added, up to 255 materials can be stored, 0 index is always reserved for null material, -1 on fail
   Int index0(C MaterialPtr &material); // get index of desired 'material' in the palette, if 'material' is not listed in the palette it will be added, up to 255 materials can be stored, 0 index is always reserved for null material,  0 on fail

   // manage
   void del  (); // delete manually
   void clear(); // clear

   // operations
   void remove(Int  i                       ); // remove i-th   material , 0-th material can't be removed because it's always reserved for null material
   Bool clean (Bool is[256], Byte remap[256]); // remove unused materials, 'is'=array of 256 possible values (true if used, false otherwise), 'remap'=material index remap obtained after function return to be used in followig way: "remap[src]=dest"

   // io
   Bool save(File &f, CChar *path=null)C; // save to   'f' file, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail
   Bool load(File &f, CChar *path=null) ; // load from 'f' file, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail
#if EE_PRIVATE
   Bool loadOld(File &f, CChar *path=null);
   void setMap();
#endif

   MaterialPalette();

#if !EE_PRIVATE
private:
#endif
   struct Data
   {
      PaletteID   id;
      MaterialPtr mtrl;
   };
   PaletteID  _last;
   Memc<Data> _data;
};
/******************************************************************************/
struct IDPalette
{
   // get
   Int     elms      (     )C {return                     _data.elms    ()      ;} // get number of elements
 C UID&    operator[](Int i)C {return InRange(i, _data) ? _data[i].uid : UIDZero;} // get i-th ID
   UIntPtr memUsage  (     )C {return                     _data.memUsage()      ;} // get memory usage

   Int index (C UID &id); // get index of desired 'id' in the palette, if 'id' is not listed in the palette it will be added, up to 255 ids can be stored, 0 index is always reserved for 'UIDZero' id, -1 on fail
   Int index0(C UID &id); // get index of desired 'id' in the palette, if 'id' is not listed in the palette it will be added, up to 255 ids can be stored, 0 index is always reserved for 'UIDZero' id,  0 on fail

   // manage
   void del  (); // delete manually
   void clear(); // clear

   // operations
   void remove(Int  i                       ); // remove i-th   ID , 0-th ID can't be removed because it's always reserved for 'UIDZero'
   Bool clean (Bool is[256], Byte remap[256]); // remove unused IDs, 'is'=array of 256 possible values (true if used, false otherwise), 'remap'=ID index remap obtained after function return to be used in followig way: "remap[src]=dest"

   // io
   Bool save(File &f)C; // save to   'f' file, false on fail
   Bool load(File &f) ; // load from 'f' file, false on fail
#if EE_PRIVATE
   void setMap();
#endif

   IDPalette();

#if !EE_PRIVATE
private:
#endif
   struct Data
   {
      PaletteID id;
      UID      uid;
   };
   PaletteID  _last;
   Memc<Data> _data;
};
/******************************************************************************/
inline Int Elms(C MaterialPalette &mp) {return mp.elms();}
inline Int Elms(C       IDPalette &ip) {return ip.elms();}
/******************************************************************************/
