// STL include(s)
#include <iostream>
#include <fstream>
#include <memory>

// BOOST include(s)
#include <boost/program_options.hpp>

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
  // command line options
  namespace po = boost::program_options;
  po::options_description desc("options");
  desc.add_options()
    ("help,h","print usage")
    ("dbname,d",po::value<std::string>()->default_value("START")->required(),"name of postgreSQL database")
    ("user,u",po::value<std::string>()->required(),"user name for access to the postgreSQL database");

  try
  {
    po::variables_map vm;
    po::store(po::parse_command_line(argc,argv,desc),vm);

    if(vm.count("help"))
    {
      std::cout << desc << std::endl;
      return 0;
    }
  
    po::notify(vm);
  }
  catch(po::error& e)
  {
  }
  
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
