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
    ("user,u",po::value<std::string>()->required(),"user name for access to the postgreSQL database")
    ("ISIN",po::value<std::string>()->required(),"ISIN of stock market asset")
    ("file,f",po::value<std::string>()->required(),"input file with tick data");

  // read command line options into map
  po::variables_map vm;
  try
  {
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
    std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
    std::cerr << desc << std::endl;

    return 1;
  }

  // open database
  std::unique_ptr<odb::core::database> db(new odb::pgsql::database(vm["user"].as<std::string>(),"",vm["dbname"].as<std::string>()));

  // create example Share
  START::Share share(vm["ISIN"].as<std::string>());
  
  // read input file
  std::ifstream infile(vm["file"].as<std::string>());
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
    {
      std::cout << "updating" << std::endl;
      db->update(share);
    }
    else
    {
      std::cout << "inserting" << std::endl;
      db->persist(share);
    }
    t.commit();
  }
  catch (const odb::exception& e)
  {
    std::cerr << e.what () << std::endl;
    return 1;
  }
  
  return 0;
}
