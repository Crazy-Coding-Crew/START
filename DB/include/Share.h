#ifndef SHARE_H
#define SHARE_H

// STL include(s)
#include <string>
#include <list>

// ODB include(s)
#include <odb/core.hxx>

// START include(s)
#include "Tick.h"

namespace START
{
  #pragma db object
  class Share
  {
  public:
    explicit Share(const std::string& sISIN);
    
    const std::string& ISIN() const;
    void addTick(const Tick& rTick);

    void print() const;
    
  private:
    friend class odb::access;
    Share();

    #pragma db id
    std::string m_sISIN;
    std::list<Tick> m_lTicks;
  };
} // end of namespace

#endif
