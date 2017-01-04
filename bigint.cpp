// $Id: bigint.cpp,v 1.77 2016/07/03 02:37:47 mchaboll Exp $
// Marcos Chabolla [1437530]
// ID:mchaboll
// Amit Khatri [1398993]

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"

bigint::bigint (long that): uvalue (that), is_negative (that < 0) {
   DEBUGF ('~', this << " -> " << uvalue)
}

bigint::bigint (const ubigint& uvalue, bool is_negative):
                uvalue(uvalue), is_negative(is_negative) {
}

bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

bigint bigint::operator+ () const 
{
   return *this;
}

bigint bigint::operator- () const {
   return {uvalue, not is_negative};
}

bigint bigint::operator+ (const bigint& that) const 
{
    //that.uvalue = top of stack (b)
   //uvalue = bottom (a)
 
    
   ubigint result;
   
   //If signs are the same
   if(is_negative == that.is_negative) 
   { 
      result = uvalue + that.uvalue;
      return {result,is_negative};
   }
   //If signs different
   else if(is_negative != that.is_negative) 
   {
     
     //if b>=a
     if(that.uvalue >= uvalue) 
     {   
         result = uvalue - that.uvalue; //a+b
         return{result,!that.is_negative};//Use sign of larger
     }
      //if b<a
     else if(that.uvalue < uvalue)
     {
         
       result = uvalue - that.uvalue;//a-b
       return (result);//Use sign of larger
     }
     
     
   }
   
   return{result,is_negative}; 
   //The above line is included to remove a compiler warning
 
}

bigint bigint::operator- (const bigint& that) const 
{
     ubigint result;
   
   //If signs are the same
   if(is_negative == that.is_negative) 
   {
      //Both negative
     if(is_negative == true && that.is_negative == true)
     {
         //if a<=b
        if(uvalue <= that.uvalue) 
        {
          result = that.uvalue - uvalue;//b-a
          return {result,!is_negative};//return positive
        }
        //if a>=b
        else if(uvalue >= that.uvalue) 
        {
           result = uvalue - that.uvalue;//a-b
           return {result,is_negative};//return negative
        }
    }
    //Both positive
      if(is_negative==false && that.is_negative==false)
      {
        //If a<=b
        if(that.uvalue >= uvalue)
        {
           
          result = that.uvalue - uvalue;//b-a
          return{result,!that.is_negative};//return negative
        }
        //If a>=b
        else if(uvalue >= that.uvalue)
        {
           
          result = uvalue - that.uvalue;//a-b
          return {result,that.is_negative};//return positive
        }
      }
   }
   
   //If signs are different
   if(is_negative != that.is_negative)
   {
     result = uvalue + that.uvalue;//a+b
     return {result,is_negative};//return with sign of a
   }
   
   return result;
   
   
  // ubigint result = uvalue - that.uvalue;
   //return result;
}

bigint bigint::operator* (const bigint& that) const 
{
    //Using rule of signs as mentioned
    //in assignment
    
    
   //Get the multipled result 
   bigint result = uvalue * that.uvalue;
 
   //If signs are the same
   if (is_negative == that.is_negative) 
   {
      result.is_negative = false;
   } 
   //If signs are different
   else 
   {
      result.is_negative = true;
   }
   return result;
 
}

bigint bigint::operator/ (const bigint& that) const {
   bigint result = uvalue / that.uvalue;
   return result;
}

bigint bigint::operator% (const bigint& that) const {
   bigint result = uvalue % that.uvalue;
   return result;
}

bool bigint::operator== (const bigint& that) const 
{
    
    //If the signs are the same
    if(is_negative == that.is_negative)
    {
      //If the values are the same
      if(uvalue == that.uvalue)
      {
        return true;
      }
    }
    
    return false;
   //return is_negative == that.is_negative and uvalue == that.uvalue;
}

bool bigint::operator< (const bigint& that) const 
{
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const bigint& that) {
   return out << "bigint(" << (that.is_negative ? "-" : "+")
              << "," << that.uvalue << ")";
}

