/*
 * command_line.cpp
 *
 *  Created on: 20.03.2013
 *      Author: ekaterina
 */

#include "command_line.h"
#include "define/cadef.h"
#include "fstream"

namespace po=boost::program_options;

command_line::command_line() {}

command_line::~command_line() {}

void print_vector(const std::vector<std::string> &v, const std::string &name)
{
    std::cout << name << ": ";
    for (std::vector<std::string>::const_iterator i = v.begin(); i != v.end(); ++i)
        std::cout << *i << "/";
    std::cout << "\n";
}

void vector_notifer(std::vector<std::string> parametrs)
{
	print_vector(parametrs,"parametrs");
}

int command_line::parser(int ac, char* av[])
{

  po::options_description desc("General options");
  po::options_description run_desc("Run options");
  run_desc.add_options()
	("help,h", "Show help")
    ("input,i", po::value<std::string>(&input_path)->default_value("test_models/one_road_test.json",""), "Input .json file")
    ("config,c", po::value<std::string>(&config_path)->default_value("test_models/config.ini",""), "Input .ini config file")
//    ("parametrs,p", po::value<std::vector<std::string>>()->multitoken()->notifier(vector_notifer), "Output parameters separated by spaces")
    ("output,o", po::value<std::string>(&output_path)->default_value("test_models/output.txt",""), "Output parameters file .txt")
    ("iter,I", po::value<int>(&iterations)->default_value(3600,""),"Enter the number of iterations")
    ;
  desc.add(run_desc);

  po::options_description conf("Config file options");
  conf.add_options()
	("CELL_LENGTH", po::value<float>(&cadef::cell_lenght)->default_value(5.5))
  	("MAX_VEH_VELOCITY", po::value<short>(&cadef::max_veh_velocity)->default_value(100))
  	("VELOCITY_LIMIT",po::value<short>(&cadef::velocity_limit)->default_value(60))
  	("PROB_SLOWDOWN", po::value<float>(&cadef::prob_showdown)->default_value(0.01))
  	("PROB_LANE_CHANGE", po::value<float>(&cadef::prob_lane_change)->default_value(0.01))
  	("PROB_SLOW_TO_START",po::value<float>(&cadef::prob_slow_to_start)->default_value(0.1))
  	("PROB_FWD_ANTICIPATION", po::value<float>(&cadef::prob_fwd_anticipation)->default_value(0.9))
  	("PROB_SPEEDING", po::value<float>(&cadef::prob_speeding)->default_value(0.7))
  	("MIN_POSSIBLE_DISTANCE",po::value<short>(&cadef::min_possible_distance)->default_value(1))
  	("BLINK_DURATION", po::value<short>(&cadef::blink_duration)->default_value(3))
  	("GET_READY_DURATION", po::value<short>(&cadef::get_ready_duration)->default_value(2))
  	("STAT_ACCUMULATION_TIME",po::value<long>(&cadef::stat_accumulation_time)->default_value(60));

  po::variables_map vm;
  try {
	po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout<< desc<<std::endl;
		return 1;
	}

	if (vm.count("input"))
	{
		std::ifstream ifile(input_path.c_str());
		if (!ifile)
		{
			std::cout << "Can not open input file: " << input_path << "\n";
			return 1;
		}
	}

	if(vm.count("config"))
	{
	  std::ifstream cf(config_path.c_str());
	  if (cf)
	  {
		  po::store(po::parse_config_file(cf, conf), vm);
		  notify(vm);
		  if(cadef::init(true))
		  {
			  if (cadef::stat_accumulation_time>iterations)
				  std::cout<<"Error: stat_accumulation_time must be less or equal than number of iterations"
				  <<std::endl << "Check config file " << config_path << std::endl;
			  cf.close();
		  }
		  cf.close();
	  }
	  else
	  {
		  cadef::init(false);
		  std::cout << "Can not open config file: " << config_path << "\n";
		  return 1;
	  }

	}
	return 0;

} catch(std::exception& ex) {
	std::cout<< "ERROR! "<<ex.what()<<std::endl;
    std::cout << desc << std::endl;
    return 1;
  }

return 0;
}

