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
  class Share;
  
  class Database
  {
  public:
    static Database& getDatabase(const std::string& sUser,const std::string& sDBName);
    ~Database();
    
    std::vector<std::string> getListOfISINs() const;
    Share getShare(const std::string& sISIN) const;

  private:
    Database(const std::string& sUser,const std::string& sDBName);

    std::unique_ptr<odb::database> m_pDatabase;
  };
} // end of namespace

#endif
