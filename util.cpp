// $Id: util.cpp,v 1.2 2016/07/03 02:37:47 mchaboll Exp $
// Marcos Chabolla [1437530]
// ID:mchaboll
// Amit Khatri [1398993]

#include <cstring>
using namespace std;

#include "util.h"

ydc_exn::ydc_exn (const string& what): runtime_error (what) {
}

string exec::execname_; // Must be initialized from main().
int exec::status_ = EXIT_SUCCESS;

void exec::execname (const string& argv0) {
   execname_ = basename (argv0.c_str());
   cout << boolalpha;
   cerr << boolalpha;
   DEBUGF ('Y', "execname = " << execname_);
}

void exec::status (int new_status) {
   new_status &= 0xFF;
   if (status_ < new_status) status_ = new_status;
}

ostream& note() {
   return cerr << exec::execname() << ": ";
}

ostream& error() {
   exec::status (EXIT_FAILURE);
   return note();
}

