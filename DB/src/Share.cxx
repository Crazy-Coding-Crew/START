// STL include(s)
#include <iostream>

// START include(s)
#include <Share.h>

namespace START
{
  Share::Share(const std::string& sISIN):
    m_sISIN(sISIN),
    m_lTicks()
  {}

  Share::Share():
    m_sISIN(),
    m_lTicks()
  {}

  const std::string& Share::ISIN() const
  {
    return m_sISIN;
  }

  void Share::addTick(const Tick& rTick)
  {
    m_lTicks.push_back(rTick);
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
