// STL include(s)
#include <cstddef>

// ODB includes
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/pgsql/database.hxx>

// START include(s)
#include "Database.h"
#include "DBWriter.h"
#include "Share.h"
#include "Share-odb.h"

namespace START
{
  Database& Database::getDatabase(const std::string& sUser,const std::string& sDBName)
  {
    static Database db(sUser,sDBName);

    return db;
  }

  Database::~Database()
  {}

  bool Database::write(const DBObject& obj)
  {
    return obj.acceptWriter(*m_pDBWriter);
  }

  std::vector<std::string> Database::getListOfISINs() const
  {
    typedef odb::query<START::Share> query;
    typedef odb::result<START::Share> result;

    odb::transaction t(m_pDatabase->begin());
    result r(m_pDatabase->query<Share>());

    std::vector<std::string> lISINs;
    for(auto& share: r)
      lISINs.push_back(share.ISIN());
    
    t.commit();

    return lISINs;
  }

  Share Database::getShare(const std::string& sISIN) const
  {
    odb::transaction t(m_pDatabase->begin());
    std::unique_ptr<Share> pShare(m_pDatabase->load<Share>(sISIN));
    t.commit();

    return Share(*pShare);
  }
  
  Database::Database(const std::string& sUser,const std::string& sDBName):
    m_pDBWriter(nullptr),
    m_pDatabase(new odb::pgsql::database(sUser,"",sDBName))
  {}

};
