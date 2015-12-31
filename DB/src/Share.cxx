// STL include(s)
#include <iostream>

// START include(s)
#include "DBWriter.h"
#include "Share.h"

namespace START
{
  Share::Share(const std::string& sISIN):
    DBObject(),
    m_sISIN(sISIN),
    m_lTicks()
  {}

  Share::Share():
    DBObject(),
    m_sISIN(),
    m_lTicks()
  {}

  bool Share::acceptWriter(const DBWriter& writer) const
  {
    return writer.write(*this);
  }

  const std::string& Share::ISIN() const
  {
    return m_sISIN;
  }

  void Share::addTick(const Tick& rTick)
  {
    m_lTicks.push_back(rTick);
  }

  const std::list<Tick>& Share::getTicks() const
  {
    return m_lTicks;
  }

  void Share::print() const
  {
    std::cout << "ISIN: " << m_sISIN << std::endl;
    for(auto& tick: m_lTicks)
    {
      std::cout << "  Open = " << tick.open()
		<< ", High = " << tick.high()
		<< ", Low = " << tick.low()
		<< ", Close = " << tick.close()
		<< ", Volume = " << tick.volume() << std::endl;
    }
  }
} // end of namespace
