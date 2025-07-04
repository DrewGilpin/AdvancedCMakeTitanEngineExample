/******************************************************************************/
#define MEMX_INDEX_END (!IOS) // if place index at end of data (or at start)
struct _Memx // Block Based Extended Container Base - Do not use this class, use 'Memx' instead
{
   static constexpr Bool Continuous=false; // Memx memory is NOT continuous

   void del  ();
   void clear();

    Int    absElms ()C {return               _abs.elms();}
    Int  validElms ()C {return             _valid.elms();}
    Int       elms ()C {return             _valid.elms();}
   UInt    elmSize ()C {return _abs.elmSize()-SIZE(UInt);}
   UIntPtr memUsage()C;
#if EE_PRIVATE
   UInt    maxElms ()C {return _valid.maxElms();}
#if MEMX_INDEX_END // index at end
   UInt&   elmIndex     ( Ptr elm  )  {return *(UInt*)(((Byte*)elm)+elmSize());}
   UInt    elmIndex     (CPtr elm  )C {return *(UInt*)(((Byte*)elm)+elmSize());}
   UInt&   elmIndexAbs  ( Int abs  )  {return elmIndex(_abs[       abs   ]);}
   UInt    elmIndexAbs  ( Int abs  )C {return elmIndex(_abs[       abs   ]);}
   UInt&   elmIndexValid( Int valid)  {return elmIndex(_abs[_valid[valid]]);}
#else // index at start
   UInt&   elmIndex     ( Ptr elm  )  {return ((UInt*)elm)[-1];}
   UInt    elmIndex     (CPtr elm  )C {return ((UInt*)elm)[-1];}
   UInt&   elmIndexAbs  ( Int abs  )  {return *(UInt*)_abs[       abs   ];}
   UInt    elmIndexAbs  ( Int abs  )C {return *(UInt*)_abs[       abs   ];}
   UInt&   elmIndexValid( Int valid)  {return *(UInt*)_abs[_valid[valid]];}
#endif
#endif

#if MEMX_INDEX_END // index at end
   Ptr   absElm  (Int i)C {return        _abs  [i] ;}
#else // index at start
   Ptr   absElm  (Int i)C {return (Byte*)_abs  [i]+SIZE(UInt);}
#endif
   Ptr validElm  (Int i)C {return absElm(_valid[i]);}
   Ptr addr      (Int i)C {return InRange(i, T) ?     T[i] : null;}
   Ptr addrFirst (     )C {return elms   (    ) ? first( ) : null;}
   Ptr addrLast  (     )C {return elms   (    ) ?  last( ) : null;}
   Ptr operator[](Int i)C {return validElm(i);}
   Ptr first     (     )C {return validElm(0);}
   Ptr last      (     )C {return validElm(validElms()-1);}
   Ptr New       (     );
   Ptr NewAt     (Int i);

   Int  validToAbsIndex(Int  valid)C;
   Int  absToValidIndex(Int  abs  )C;
   Bool absIndexIsValid(Int  abs  )C;
   Int  validIndex     (CPtr elm  )C;
   Int    absIndex     (CPtr elm  )C;
   Bool   contains     (CPtr elm  )C {return validIndex(elm)>=0;}
#if EE_PRIVATE
   Int  absToInvalidIndex(Int abs)C;
   UInt validToAbsIndexFastUnsafe(Int  valid)C {return _valid[valid];}
   Int  validIndexFastUnsafeValid(CPtr elm)C; // fast version that doesn't do any safety checks, assumes that "elm!=null" and points exactly to the element, and it is valid (not removed)
   Int    absIndexFastUnsafeValid(CPtr elm)C; // fast version that doesn't do any safety checks, assumes that "elm!=null" and points exactly to the element, and it is valid (not removed)
#endif

   void removeAbs  (Int  i  , Bool keep_order=false);
   void removeValid(Int  i  , Bool keep_order=false);
   void removeData (CPtr elm, Bool keep_order=false);
   void removeLast ();

   void setNum (Int num);
   Int  addNum (Int num);
   void reserve(Int num);

   Bool binarySearch(CPtr value, Int &index, Int compare(CPtr a, CPtr b))C;
   void         sort(           Int compare(CPtr a, CPtr b           ));
   void         sort(CPtr user, Int compare(CPtr a, CPtr b, CPtr user));
   void reverseOrder();
   void    swapOrder(Int i  , Int j);
   void moveElm     (Int elm, Int new_index);
   void moveToStart (Int elm);
   void moveToEnd   (Int elm);

   void cleanup();

   Bool saveRaw(File &f)C;
   Bool loadRaw(File &f) ;

#if EE_PRIVATE
   void moveElmLeftUnsafe(Int elm, Int new_index);

   void copyTo  ( Ptr dest)C;
   void copyFrom(CPtr src ) ;
   void verify  ()C;
#endif

 ~_Memx() {del();}

private:
  _Memb       _abs;
   Memc<UInt> _valid, _invalid;
   void     (*_new)(Ptr elm),
            (*_del)(Ptr elm);

   explicit _Memx(Int elm_size, Int block_elms, void (*_new)(Ptr elm), void (*_del)(Ptr elm));
      void _reset(Int elm_size, Int block_elms, void (*_new)(Ptr elm), void (*_del)(Ptr elm));

   NO_COPY_CONSTRUCTOR(_Memx);

   T1(TYPE) friend struct Memx;
   T1(TYPE) friend struct MemxAbstract;
};
/******************************************************************************/
