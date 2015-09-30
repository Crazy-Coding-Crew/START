#ifndef TICK_H
#define TICK_H

// STL include(s)
#include <string>

// ODB include(s)
#include <odb/core.hxx>

namespace START
{
  #pragma db value
  class Tick
  {
  public:
    Tick(const std::string& sDate,float fOpen,float fHigh,float fLow,float fClose,unsigned long int iVolume);
    std::string date() const;
    float open() const;
    float high() const;
    float low() const;
    float close() const;
    unsigned long int volume() const;
    
    const Tick operator+(const Tick& rOther) const;

  private:
    friend class odb::access;
    Tick();

    std::string       m_sDate;
    float             m_fOpen;
    float             m_fHigh;
    float             m_fLow;
    float             m_fClose;
    unsigned long int m_iVolume;
  };
} // end of namespace
#endif
