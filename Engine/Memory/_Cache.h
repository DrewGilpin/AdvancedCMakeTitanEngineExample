/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
struct _Cache // Cache (base) - Do not use this class, use 'Cache' instead
{
   struct Desc
   {
      Str  file; // file name
      UInt flag, ptr_num;
   };
   struct Elm
   {
   };

   Int elms()C {return _elms;}

   void   lock()C;
   void unlock()C;

 ~_Cache() {del();}

private:
   struct DelayRemove
   {
      Flt  time;
      Elm *elm;
   };
mutable Byte         _d_lock;
   Bool              _case_sensitive;
   Byte              _mode;
   Int               _elms, /*_data_offset, */_desc_offset, _delay_remove_counter;
   Flt               _delay_remove_time;
   Dbl               _delay_remove_check;
   CChar8           *_debug_name;
   Elm             **_order;
   Memx<Elm>         _memx;
   Memc<DelayRemove> _delay_remove;
   SyncLock          _lock;
   Ptr               _user;
   Bool            (*_load          )( Ptr data, C Str &file);
   Bool            (*_load_user     )( Ptr data, C Str &file, Ptr user);
   Bool            (*_can_be_removed)(CPtr data);

   void clear         ();
   void del           ();
   Byte mode          (Byte mode);
   void caseSensitive (Bool sensitive);
   void delayRemove   (Flt  time);
   void delayRemoveNow();
   void delayRemoveInc();
   void delayRemoveDec();
   void reserve       (Int num);
   void update        ();

   void setLoadUser(Bool (*load_user)(Ptr data, C Str &file, Ptr user), Ptr user);

   Ptr    find      (CChar *file, CChar *path, Bool counted);
   Ptr    find      (C UID &id  , CChar *path, Bool counted);
   Ptr    get       (CChar *file, CChar *path, Bool counted);
   Ptr    get       (C UID &id  , CChar *path, Bool counted);
   Ptr    require   (CChar *file, CChar *path, Bool counted);
   Ptr    require   (C UID &id  , CChar *path, Bool counted);
   Bool   contains  (CPtr   data                           )C;
   Int    ptrCount  (CPtr   data                           )C;
   Bool   dummy     (CPtr   data                           )C;
   void   dummy     (CPtr   data, Bool   dummy             );
   C Str& name      (CPtr   data                           )C;
   CChar* name      (CPtr   data, CChar *path              )C;
   UID    id        (CPtr   data                           )C;
   void   removeData(CPtr   data                           );

   void incDecRef(CPtr inc, CPtr dec);
   void incRef(CPtr data);
   void decRef(CPtr data);

   void lockedFrom(C _Cache &src);

 C Desc& lockedDesc(Int i)C;
   CPtr  lockedData(Int i)C;

   explicit _Cache(CChar8 *name, Int block_elms);

   NO_COPY_CONSTRUCTOR(_Cache);

   T1(TYPE)                                    friend struct Cache;
   template<typename TYPE, Cache<TYPE> &CACHE> friend struct CacheElmPtr;
};
/******************************************************************************/
