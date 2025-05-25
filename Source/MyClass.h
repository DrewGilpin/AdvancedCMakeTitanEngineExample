#pragma once
#include "stdafx.h"

class MyClass
{
private:
   Str name; // Esenthel string type
   int value;

public:
   MyClass(const Str& name, int value); // Constructor
   void setValue(int newValue);         // Set value
   int getValue() const;                // Get value
   Str getName() const;                 // Get name
   void print() const;                  // Print details
};
