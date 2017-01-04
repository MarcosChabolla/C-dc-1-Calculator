// $Id: ubigint.cpp,v 1.15 2016/07/03 02:37:47 mchaboll Exp $
// Marcos Chabolla [1437530]
// ID:mchaboll
// Amit Khatri [1398993]

#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "ubigint.h"
#include "debug.h"

ubigint::ubigint (unsigned long that): ubig_value (that) {
   //DEBUGF ('~', this << " -> " << ubig_value)
}

ubigint::ubigint (const string& that): ubig_value(0) {
   DEBUGF ('~', "that = \"" << that << "\"");
   for (char digit: that) {
      if (not isdigit (digit)) {
         throw invalid_argument ("ubigint::ubigint(" + that + ")");
      }
      //ubig_value = ubig_value * 10 + digit - '0';
      ubig_value.insert(ubig_value.begin(),digit);
      
   }
}

ubigint ubigint::operator+ (const ubigint& that) const 
{
  
    //return ubigint (ubig_value + that.ubig_value);
   //that.ubig_value = top of stack (b)
   //ubig_value = bottom (a)
     ubigint result;
  
   int sum;
   int carry = 0;
   
   //If b.size < a.size
   if(that.ubig_value.size() < ubig_value.size())
   {
      
       //Until we reach the end of a
      for( unsigned int i=0;i<ubig_value.size();i++)
      {
          //If we have reached the end of b
          if(i>that.ubig_value.size()-1)
          {  
              //a + carry
              sum = (ubig_value[i]-'0') + carry;
              
              //If there is a carry
              if(sum >= 10)
              {
                 result.ubig_value.push_back((sum-10)+'0');
              }
              //If no carry
              else if(sum<10)
              {
                result.ubig_value.push_back(sum + '0');
              }
          
              carry = sum/10;
              
              //If there is a carry on the last digit
              if(i==ubig_value.size()-1 && carry==1)
              {
                result.ubig_value.push_back('1'); 
              }
          }
          
          else if(i<=that.ubig_value.size()-1)
          {
            //(a + b) + carry
            sum = ((ubig_value[i]-'0') + (that.ubig_value[i]-'0')) + carry;
          
            //If there is a carry
            if(sum>=10)
            {
                result.ubig_value.push_back((sum-10)+'0');
            }
            //If no carry
            else if(sum<10)
            {
              result.ubig_value.push_back(sum+'0');
            }
          
            carry = sum/10;
         }
          
      }
      
      
      
      
     
   }
   //If b.size > a.size()
   if(that.ubig_value.size() > ubig_value.size())
   {
      //Until we reach the end of B
      for(unsigned int i=0;i<that.ubig_value.size();i++)
      {
          
           //If we have reached the end of a   
          if(i>ubig_value.size()-1)
          {
              //(a + carry)
              sum = (that.ubig_value[i]-'0') + carry;
          
              //If there is a carry
              if(sum>=10)
              {
                 result.ubig_value.push_back((sum-10)+'0');
              }
              //If there is no carry
              else if(sum<10)
              {
                result.ubig_value.push_back(sum+'0');
              }
          
              carry = sum/10;
              //If there is a carry on last digit
              if(i==that.ubig_value.size()-1 && carry==1)
              {
                result.ubig_value.push_back('1'); 
              }
          }
          else if(i<=ubig_value.size()-1)
          {
            //(a + b) + carry
            sum = ((ubig_value[i]-'0') + (that.ubig_value[i]-'0')) + carry;
          
            //If there is a carry
            if(sum>=10)
            {
                result.ubig_value.push_back((sum-10)+'0');
            }
            //If no carry
            else if(sum<10)
            {
              result.ubig_value.push_back(sum+'0');
            }
          
            carry = sum/10;
         }
        
          
      }
      
      
   }
   //If a.size() == b.size()
   if(that.ubig_value.size()==ubig_value.size())
   {
       //Until we reach the end
       for(unsigned int i=0;i<that.ubig_value.size();i++)
      {
    
              
            //(a + b) + carry
            sum = ((ubig_value[i]-'0') + (that.ubig_value[i]-'0')) + carry;
            
            //If there is a carry
            if(sum>=10)
            {
                result.ubig_value.push_back((sum-10)+'0');
            }
            //If no carry
            else if(sum < 10)
            {
              result.ubig_value.push_back(sum+'0');
            }
          
            carry = sum/10;
            
            //If carry on the last digit
            if(i==that.ubig_value.size()-1 && carry==1)
             {
               result.ubig_value.push_back('1'); 
             }
         }
          
   }
   
   
     return result;
  
}

ubigint ubigint::operator- (const ubigint& that) const 
{
    ubigint result;
   int diff = 0;
   int carry = 0;
   unsigned int i = 0;
   
    //If b.size() < a.size()   
    if(that.ubig_value.size() < ubig_value.size())
    {
        //Until we reach end of a
        for(i=0;i<ubig_value.size();i++)
        {
             //if b has already ended
             if(i>that.ubig_value.size()-1)
             {
                 diff = (ubig_value[i]-'0') + carry;
                 carry = 0;
                 result.ubig_value.push_back(diff+'0');
             }
             else
             {
                 //(a - b) + carry
                diff = ((ubig_value[i]-'0') - (that.ubig_value[i]-'0')) + carry;
                carry = 0;
                
                
                if(diff<0)
                {
                    //Add 10 to result and push back
                    result.ubig_value.push_back((diff+10)+'0');
                    carry = -1;
                }
                else
                {
                  result.ubig_value.push_back(diff+'0');
                }
             }
             
        }
       
    }
    
    //if b.size > a.size
    if(that.ubig_value.size() > ubig_value.size())
   { 
       
       //Until we reach end of b
      for(i=0;i<that.ubig_value.size();i++)
      {
         
          //If a has already ended
          if(i>ubig_value.size()-1)
          {
              diff = (that.ubig_value[i]-'0') + carry;
              carry = 0;
              result.ubig_value.push_back(diff+'0');
          }
          
          else
          {
            //(b - a) + carry
            diff = ((that.ubig_value[i]-'0') - (ubig_value[i]-'0')) + carry;
            carry = 0;
          
            if(diff<0)
            {
                //Add 10 to result and push back
                result.ubig_value.push_back((diff+10)+'0');
                carry = -1;
            }
            else
            {
              result.ubig_value.push_back(diff+'0');
            }
          
            
         }
         
          
      }
      
     
   
   
  }
  
  // b.size = a.size
  if(that.ubig_value.size() == ubig_value.size())
   { 
       
     
       //Until we reach end of b
      for(i=0;i<that.ubig_value.size();i++)
      {
          // (a-b) + carry
          diff = ((ubig_value[i] - '0') - (that.ubig_value[i]-'0')) + carry;
          
          carry = 0;
          
          //If there is a carry before the end
          if(diff<0 && i!=(that.ubig_value.size()-1))
          {
            
            result.ubig_value.push_back((diff+10)-'0');
            carry = -1;
          }
          //If there is a carry at the end
          else if(diff<0 && i!=(that.ubig_value.size()-1))
          {
             
            result.ubig_value.push_back((diff*-1)  + '0');
          }
          //otherwise
          else
          {
              
            result.ubig_value.push_back((diff)  + '0');
          }
          
      }
      
     
   
   
  }
  //Pop back leading zeroes
  while (result.ubig_value.size() > 0 
      and result.ubig_value.back() == 0+'0' 
      and result.ubig_value.size() != 1) 
  {
      result.ubig_value.pop_back();
  }
  
  return result;
   //if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
  //return ubigint (ubig_value - that.ubig_value);
}

ubigint ubigint::operator* (const ubigint& that) const 
{
  //Using algorithm given in assignment.
   ubigint result;
   
   //get size of product
   int size = ubig_value.size() + that.ubig_value.size();

   //initialize a vector of size nxm of 0's
   for (int i = 0; i < size + 1; i++) 
   {
      result.ubig_value.push_back('0' + 0);
   }
 
   for (unsigned int i = 0; i < ubig_value.size(); i++) 
   {
      int carry = 0;
      
      for (unsigned int j = 0; j < that.ubig_value.size(); j++) 
      {
         int count = 0;
         
         count = result.ubig_value.at(i + j) - '0';
         count += (ubig_value.at(i) - '0') * (that.ubig_value.at(j) - '0') + carry;
         result.ubig_value.at(i + j) = ((count % 10) + '0');
         carry = count / 10;
      }
     
      result.ubig_value.at(i + that.ubig_value.size()) = carry + '0';
   }
   
   while (result.ubig_value.size() > 0 and
      result.ubig_value.back() == 0 +'0') 
   {
      result.ubig_value.pop_back();
   }
return result;
}

void ubigint::multiply_by_2() {
  // ubig_value *= 2;
}

void ubigint::divide_by_2() {
  // ubig_value /= 2;
}


struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, ubigint divisor) {
   // Note: divisor is modified so pass by value (copy).
   ubigint zero {0};
   if (divisor == zero) throw domain_error ("udivide by zero");
   ubigint power_of_2 {1};
   ubigint quotient {0};
   ubigint remainder {dividend}; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (power_of_2 > zero) {
      if (divisor <= remainder) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   return {.quotient = quotient, .remainder = remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   return udivide (*this, that).quotient;
}

ubigint ubigint::operator% (const ubigint& that) const {
   return udivide (*this, that).remainder;
}

bool ubigint::operator== (const ubigint& that) const 
{
    //If size is the same
     if(ubig_value.size() == that.ubig_value.size())
    {
      for(unsigned int i=0;i<ubig_value.size();i++)
      {
          //If values are the same
         if(ubig_value[i] == that.ubig_value[i])
         {
           continue;
         }
         //If values not the same
         else if(ubig_value[i] != that.ubig_value[i])
         {
            return false;
         }
      }
    }
    //If sizes not the same
    else if(ubig_value.size() != that.ubig_value.size())
    {
     return false;
    }
    
    return true;
  // return ubig_value == that.ubig_value;
}

bool ubigint::operator< (const ubigint& that) const 
{
    //If a.size does not equal b.size
    if (ubig_value.size() != that.ubig_value.size()) 
    {
        //Return whether a<b
       return ubig_value.size() < that.ubig_value.size();
    }
    
    //If the numbers are the same
    if ((*this) == that) 
    {
       
       return false;
    }
        
   //Until we reach the end of a
   for (int i = ubig_value.size() - 1; i >= 0; i--) 
   {
       //If current value of a < current value b
      if(ubig_value[i] < that.ubig_value[i]) 
      {
        return true;
      }
      //Fix this?    
      else if (ubig_value[i] < that.ubig_value[i]) 
      {
        return false;
      }
          
   }

   return false;
  
}

ostream& operator<< (ostream& out, const ubigint& that) 
{ 
    if(that.ubig_value.size() == 0)
      out << "0";
   int cnt = 0;
   for(auto itor = that.ubig_value.rbegin(); 
      itor != that.ubig_value.rend(); ++itor) 
   {
      out << (*itor - '0');
      if(++cnt == 69) 
      {
         out << "\\" << endl;
         cnt = 0;
      }
   }
   return out;
   //return out << "ubigint(" << that.ubig_value << ")";
}

