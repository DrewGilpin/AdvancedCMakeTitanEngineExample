/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
struct Aggregate
{
   void         del();
  ~Aggregate() {del();}
   Aggregate() {_aggr=null;}

private:
   Ptr _aggr;

   NO_COPY_CONSTRUCTOR(Aggregate);
};
/******************************************************************************/
