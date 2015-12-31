#ifndef DBWRITER_H
#define DBWRITER_H

namespace START
{
  // forward declarations
  class Share;

  class DBWriter
  {
  public:
    virtual ~DBWriter() = default;
    virtual bool write(const Share& rShare) const = 0;
  };
}  // end of namespace START

#endif
