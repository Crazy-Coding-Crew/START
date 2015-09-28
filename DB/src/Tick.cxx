// STL include(s)
#include <algorithm>

// START include(s)
#include <Tick.h>

namespace START
{
  Tick::Tick(float fOpen,float fHigh,float fLow,float fClose,unsigned long int iVolume):
    m_fOpen(fOpen),
    m_fHigh(fHigh),
    m_fLow(fLow),
    m_fClose(fClose),
    m_iVolume(iVolume)
  {}

  Tick::Tick():
    m_fOpen(0),
    m_fHigh(0),
    m_fLow(0),
    m_fClose(0),
    m_iVolume(0)
  {}
  
  float Tick::open() const
  {
    return m_fOpen;
  }

  float Tick::high() const
  {
    return m_fHigh;
  }

  float Tick::low() const
  {
    return m_fLow;
  }

  float Tick::close() const
  {
    return m_fClose;
  }

  unsigned long int Tick::volume() const
  {
    return m_iVolume;
  }

  const Tick Tick::operator+(const Tick& rOther) const
  {
    return Tick(m_fOpen,std::max(m_fHigh,rOther.m_fHigh),std::min(m_fLow,rOther.m_fLow),m_fClose,m_iVolume + rOther.m_iVolume);
  }
} // end of namespace
