#ifndef APP_H
#define APP_H

// STL include(s)
#include <vector>
#include <string>

// BOOST include(s)
#include <boost/python.hpp>
using namespace boost::python;

namespace START
{
  class App
  {
  public:
    static list getListOfISINs();
    static list getShare(const std::string& sISIN);
  };
} // end of namespace

#endif 
