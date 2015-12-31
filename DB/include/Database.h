#ifndef DATABASE_H
#define DATABASE_H

// STL include(s)
#include <memory>
#include <vector>
#include <string>

// forward definitions
namespace odb
{
  class database;
}

namespace START
{
  // forward declarations
  class DBObject;
  class DBWriter;
  class Share;
  
  class Database
  {
  public:
    static Database& getDatabase(const std::string& sUser,const std::string& sDBName);
    ~Database();
    
    bool write(const DBObject&);
    std::vector<std::string> getListOfISINs() const;
    Share getShare(const std::string& sISIN) const;

  private:
    Database(const std::string& sUser,const std::string& sDBName);

    // member variables
    std::unique_ptr<DBWriter>      m_pDBWriter;
    std::unique_ptr<odb::database> m_pDatabase;
  };
} // end of namespace

#endif
