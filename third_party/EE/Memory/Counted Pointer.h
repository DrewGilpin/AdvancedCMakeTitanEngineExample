/******************************************************************************

   Create classes based on 'PtrCounter' that will hold information about how many pointers are accessing class objects.

   Access existing objects with 'CountedPtr' pointers.
      When pointing to the object for the first time, its   'load' method will be called. If it failed then 'CountedPtr' will be set to null.
      When there are no more pointers to this object, its 'unload' method will be called.

/******************************************************************************/
struct PtrCounter
{
   Bool  unloaded()C {return _ptrs==0;} // if object is unloaded
   Bool    loaded()C {return _ptrs>=1;} // if object is   loaded, there are any      'CountedPtr' referencing this element or was loaded and now scheduled for removal
   Bool   anyPtrs()C {return _ptrs>=2;} // if                     there are any      'CountedPtr' referencing this element
   Bool multiPtrs()C {return _ptrs>=3;} // if                     there are multiple 'CountedPtr' referencing this element

  ~PtrCounter();

#if !EE_PRIVATE
private:
#endif
   UInt _ptrs=0;
#if EE_PRIVATE
private:
#endif
   Bool        decRef();
   void        decRef(void (*unload)(Ptr elm));
   PtrCounter* incRef();
   PtrCounter* incRef(Bool (*  load)(Ptr elm));
   PtrCounter* incRef(Bool (*  load)(Ptr elm, Ptr user), Ptr user);
   T1(TYPE) friend struct CountedPtr;
};
/******************************************************************************/
T1(TYPE) struct CountedPtr // Counted Element Pointer - can hold a reference to a TYPE object which must be based on 'PtrCounter'
{
   // operators
   TYPE* operator ()  (                  )C {return  T._data            ;} // access the data, you can use the returned pointer   as long as this 'CountedPtr' object exists and not modified
   TYPE* operator ->  (                  )C {return  T._data            ;} // access the data, you can use the returned pointer   as long as this 'CountedPtr' object exists and not modified
   TYPE& operator *   (                  )C {return *T._data            ;} // access the data, you can use the returned reference as long as this 'CountedPtr' object exists and not modified
   Bool  operator ==  (  null_t          )C {return  T._data==null      ;} // if pointers are equal
   Bool  operator !=  (  null_t          )C {return  T._data!=null      ;} // if pointers are different
   Bool  operator ==  (C TYPE       *data)C {return  T._data==data      ;} // if pointers are equal
   Bool  operator !=  (C TYPE       *data)C {return  T._data!=data      ;} // if pointers are different
   Bool  operator ==  (C CountedPtr &eptr)C {return  T._data==eptr._data;} // if pointers are equal
   Bool  operator !=  (C CountedPtr &eptr)C {return  T._data!=eptr._data;} // if pointers are different
         operator Bool(                  )C {return  T._data!=null      ;} // if pointer  is  valid

   // operations
              CountedPtr& clear    (                               ); // clear the pointer to  null , this automatically decreases the reference count of current data
              Bool        cancel   (                               ); // clear the pointer to  null , this automatically decreases the reference count of current data !! DOES NOT CALL 'unload' !! returns if 'unload' should be called manually
              CountedPtr& operator=(  null_t                       ); // clear the pointer to  null , this automatically decreases the reference count of current data
              CountedPtr& operator=(  TYPE       * data            ); // set       pointer to 'data', this automatically decreases the reference count of current data and increases the reference count of the new data
              CountedPtr& operator=(C CountedPtr & eptr            ); // set       pointer to 'eptr', this automatically decreases the reference count of current data and increases the reference count of the new data
              CountedPtr& operator=(  CountedPtr &&eptr            ); // set       pointer to 'eptr', this automatically decreases the reference count of current data and increases the reference count of the new data
              CountedPtr& set      (  TYPE       * data, Ptr   user); // set       pointer to 'data', this automatically decreases the reference count of current data and increases the reference count of the new data, use 'user' for 'load'  function
   T1(USER)   CountedPtr& set      (  TYPE       * data, USER &user); // set       pointer to 'data', this automatically decreases the reference count of current data and increases the reference count of the new data, use 'user' for 'load'  function
   T1(USER)   CountedPtr& set1     (  TYPE       * data, USER &user); // set       pointer to 'data', this automatically decreases the reference count of current data and increases the reference count of the new data, use 'user' for 'load1' function, this function uses 'load1' instead of 'load'

   // constructors / destructors
   CountedPtr(  null_t=null      ); // initialize the pointer with  null
   CountedPtr(  TYPE       * data); // initialize the pointer with 'data', this automatically increases the reference count of the    'data'
   CountedPtr(C CountedPtr & eptr); // initialize the pointer with 'eptr', this automatically increases the reference count of the    'eptr'
   CountedPtr(  CountedPtr &&eptr); // initialize the pointer with 'eptr', this automatically increases the reference count of the    'eptr'
  ~CountedPtr(                   ); // release    the pointer            , this automatically decreases the reference count of current data

private:
   TYPE *_data;
              static void  DecRef      (TYPE *data);
              static Bool  DecRefCancel(TYPE *data);
              static TYPE* IncRef      (TYPE *data);
              static TYPE* IncRefLoad  (TYPE *data);
              static TYPE* IncRefLoad  (TYPE *data, Ptr   user);
   T1(USER)   static TYPE* IncRefLoad  (TYPE *data, USER &user);
   T1(USER)   static TYPE* IncRefLoad1 (TYPE *data, USER &user);
};
/******************************************************************************/
void DelayRemoveTime(Flt time); // set amount of time (in seconds) after which unused elements are removed (<=0 value specifies immediate unloading), default=0
void DelayRemoveNow (        ); // immediately remove all elements that were marked for delay removal at a later time to free as much memory as possible
#if EE_PRIVATE
void DelayRemoveUpdate();
#endif
/******************************************************************************/
