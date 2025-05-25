#include "MyClass.h"
#include "stdafx.h"

MyClass::MyClass(const Str& name, int value) : name(name), value(value) {}

void MyClass::setValue(int newValue)
{
   value = newValue;
}

int MyClass::getValue() const
{
   return value;
}

Str MyClass::getName() const
{
   return name;
}

void MyClass::print() const
{
   D.text(0, 0.3, S + "Name: " + name + ", Value: " + value); // Display details on screen
}
