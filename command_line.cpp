/*
 * command_line.cpp
 *
 *  Created on: 20.03.2013
 *      Author: ekaterina
 */

#include "command_line.h"


/*namespace po = boost::program_options;

command_line::command_line() {
	// TODO Auto-generated constructor stub

}

command_line::~command_line() {
	// TODO Auto-generated destructor stub
}

int command_line::parser(int ac, char* av[])
{

	 po::options_description desc("Allowed options");
		 desc.add_options()
		      ("help,h", "produce help message")
		      ("test,t",po::value<double>()->default_value(50),"test");
		 	//  ("config,c", value<std::string>(&conf_file)->default_value(std::string(CONF_FILE)), "set configuration file");

	 po::variables_map vm;
	 po::parsed_options parsed = po::command_line_parser(ac, av).options(desc).allow_unregistered().run();
	 po::store(parsed,vm);
//	 po::store(po::parse_command_line(ac, av, desc), vm);
	 po::notify(vm);



	 if (vm.count("help"))
		 {
		     std::cout << desc << "\n";

		 }
	 if (vm.count("test")){
	        	std::cout << "test " << vm["test"].defaulted()<<".\n";
	 	 }
	 return 0;

}*/

namespace po=boost::program_options;

command_line::command_line() {
	// TODO Auto-generated constructor stub

}

command_line::~command_line() {
	// TODO Auto-generated destructor stub
}
void run(const po::variables_map& vm)
{
  std::string input_path, info_path, output_path;
  if (vm.count("input"))
    input_path = vm["input"].as<std::string>();
  if(vm.count("config"))
    info_path = vm["config"].as<std::string>();
  if(vm.count("output"))
    output_path = vm["output"].as<std::string>();
  std::cout<<"run: "<<input_path<<" "<<info_path<<" "<<output_path<<std::endl;
}

int command_line::parser(int ac, char* av[])
{
  po::options_description desc("General options");
  std::string task_type;
  desc.add_options()
    ("help,h", "Show help")
    ("type,t", po::value<std::string>(&task_type), "Select: run, ...,...")
    ;
  po::options_description run_desc("Run options");
  run_desc.add_options()
    ("input,I", po::value<std::string>(), "Input .xml file")
    ("config,c", po::value<std::string>(), "Input .txt file")
    ("output,O", po::value<std::string>(), "Output parameters file .txt")
    ;

  po::variables_map vm;
  try {
    po::parsed_options parsed = po::command_line_parser(ac, av).options(desc).allow_unregistered().run();
    po::store(parsed, vm);
    po::notify(vm);
    if(task_type == "run") {
      desc.add(run_desc);
      po::store(po::parse_command_line(ac,av,desc), vm);
      run(vm);
    }

    else {
      desc.add(run_desc);
      std::cout << desc << std::endl;
    }
  }
  catch(std::exception& ex) {
    std::cout << desc << std::endl;
  }
  return 0;
}
