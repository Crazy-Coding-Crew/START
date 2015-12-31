#ifndef DBOBJECT_H
#define DBOBJECT_H

namespace START
{
  class DBWriter;

  /**
   * @brief base class for object which are stored in a database
   *
   * @author Christian Gumpert
   */
  class DBObject
  {
  public:
    virtual ~DBObject() = default;
    virtual bool acceptWriter(const DBWriter&) const = 0;
  };
} // end of namespace START

#endif // DBOBJECT_H
