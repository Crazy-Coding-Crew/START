// START include(s)
#include "App.h"
#include "Database.h"
#include "Share.h"
#include "Tick.h"

namespace START
{
  list App::getListOfISINs()
  {
    Database& db = Database::getDatabase("cgumpert","START");
    std::vector<std::string> vList = db.getListOfISINs();
    list l;
    for(auto& s: vList)
      l.append(s);
    
    return l; 
  }

  list App::getShare(const std::string& sISIN)
  {
    Database& db = Database::getDatabase("cgumpert","START");
    Share share = db.getShare(sISIN);

    list allTicks;
    const std::list<Tick>& lTicks = share.getTicks();
    for(const auto& tick: lTicks)
    {
      list l;
      l.append(tick.open());
      l.append(tick.high());
      l.append(tick.low());
      l.append(tick.close());
      allTicks.append(l);
    }

    return allTicks;
  }
} // end of namespace

#include <boost/python.hpp>

BOOST_PYTHON_MODULE(Start)
{
  using namespace boost::python;
  def("getListOfISINs",START::App::getListOfISINs);
  def("getShare",START::App::getShare);
}
