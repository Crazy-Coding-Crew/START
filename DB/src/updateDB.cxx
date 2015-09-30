// STL include(s)
#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>

// ODB includes
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/pgsql/database.hxx>

// START include(s)
#include "Share.h"
#include "Share-odb.h"
#include "Tick.h"

int main(int argc,char* argv[])
{
  // open database
  std::unique_ptr<odb::core::database> db(new odb::pgsql::database("christian","","START_test"));

  // create example Share
  START::Share share("TestShare");
  
  // read input file
  std::ifstream infile(argv[1]);
  std::string sDate;
  float fOpen, fHigh, fLow, fClose;
  unsigned long int iVolume;
  while(infile.good())
  {
    infile >> sDate >> fOpen >> fHigh >> fLow >> fClose >> iVolume;
    share.addTick(START::Tick(sDate,fOpen,fHigh,fLow,fClose,iVolume));
  }

  try
  {
    odb::core::transaction t(db->begin());
    if(db->find<START::Share>(share.ISIN()))
       db->update(share);
    else
      db->persist(share);
    t.commit();
  }
  catch (const odb::exception& e)
  {
    std::cerr << e.what () << std::endl;
    return 1;
  }
  
  return 0;
}
