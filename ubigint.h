// $Id: ubigint.h,v 1.12 2016/07/03 02:37:47 mchaboll Exp $
// Marcos Chabolla [1437530]
// ID:mchaboll
// Amit Khatri [1398993]

#ifndef __UBIGINT_H__
#define __UBIGINT_H__

#include <exception>
#include <iostream>
#include <limits>
#include <utility>
using namespace std;

#include "debug.h"
#include "relops.h"

class ubigint {
   friend ostream& operator<< (ostream&, const ubigint&);
   private:
      using quot_rem = pair<ubigint,ubigint>; 
      using udigit_t = unsigned char;
      using ubigvalue_t = vector<udigit_t>;
      ubigvalue_t ubig_value;
      quot_rem divide (const ubigint&) const;
   public:
      void multiply_by_2();
      void divide_by_2();

      ubigint() = default; // Need default ctor as well.
      ubigint (unsigned long);
      ubigint (const string&);

      ubigint operator+ (const ubigint&) const;
      ubigint operator- (const ubigint&) const;
      ubigint operator* (const ubigint&) const;
      ubigint operator/ (const ubigint&) const;
      ubigint operator% (const ubigint&) const;

      bool operator== (const ubigint&) const;
      bool operator<  (const ubigint&) const;
};

#endif

