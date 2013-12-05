/*
 * statisticsmodel.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef STATISTICSMODEL_H_
#define STATISTICSMODEL_H_
#include "roadnetworkmodel.h"
#include <fstream>
#include <boost/container/set.hpp>

const char *TOOL_NAME = "CATSim";
const char *TOOL_DESCRIPTION = "Cellular Automata Traffic Simulator";
const char *TOOL_VERSION = "0.1";

enum DATA_PARAMS
{
	ROAD_DENSITY,
	SPEED,
	FLOW,
	VEHICLES,
	PASSAGE_TIME,
	ROAD_QUEUE
};

enum STAT_PARAMS
{
	MEAN,
	MEDIAN,
	KURTOSIS,
	MAX,
	MIN,
	SUM,
	VARIANCE,
	DEVIATION
};

class statistics_model {
	long data_accumulation_time;
	boost::container::set<DATA_PARAMS> data_params;
	boost::container::set<STAT_PARAMS> stat_params;
	std::string output_filename;
	std::ofstream out;
public:
	statistics_model(std::string filename) :
		output_filename(filename),
		out(filename.data(), std::ofstream::out)
	{
		out.precision(5);
		data_accumulation_time = 0;
	};

	virtual ~statistics_model()
	{
		out.close();
	};

	void set_data_accumulation_time(const long t) {this->data_accumulation_time = t;};
	long get_data_accumulation_time() const{return this->data_accumulation_time;}

	void add_data_param(DATA_PARAMS param)
	{
		data_params.insert(param);
	}

	void add_stat_param(STAT_PARAMS param)
	{
		stat_params.insert(param);
	}

	void print_model_data(int iterations, float initial_density, float final_density, float density_step, road_network_model_ptr network)
	{
		if(!out.is_open())
			return;
		print_header("Информация о программе");
		out << " " << TOOL_NAME << " - " << TOOL_DESCRIPTION << std::endl;
		print_value("Версия", TOOL_VERSION);
		print_header("Моделирование сети дорог");
		print_value("Количество итераций", iterations);
		print_value("Начальная плотность", initial_density);
		print_value("Конечная плотность", final_density);
		print_value("Шаг плотности", density_step);
		print_value_with_postfix("","Время накопления данных", data_accumulation_time, "итераций");
		print_value("Количество дорог", network->roads_factory->count());
		print_header("Шаги моделирования");
	};

	void print_simulation_data(float current_density, road_network_model_ptr network)
	{
		if(!out.is_open())
			return;
		road_stat_data_map stat_data = network->get_stat_data_map();
		print_delimeter();
		print_value("Current roads density", current_density);
		road_stat_data_map::iterator it;
		for (it = stat_data.begin(); it != stat_data.end();++it)
		{
			std::string road_id = it->first;
			road_stat_data_ptr data = it->second;
			out << std::endl;
			print_subheader("ID дороги", road_id);
			print_value("Среднее значение потока", data->get_road_flow());
			print_value("Количество авто на дороге", data->get_current_vehicles_number());
			print_value("Количество авто, проехавших за это время", data->get_passed_vehicles_number());
			print_table_header();
			BOOST_FOREACH(boost::container::set<DATA_PARAMS>::value_type param, data_params)
			{
				switch(param)
				{
					case ROAD_DENSITY:
						print_data(" Плотность", data->get_density());
						break;
					case SPEED:
						print_data(" Скорость", data->get_total_speed());
						break;
					case PASSAGE_TIME:
						print_data(" Passage time", data->get_passage_time());
						break;
					case VEHICLES:
						print_data(" Количество проехавших авто", data->get_passed_vehicles());
						break;
					case ROAD_QUEUE:
						print_data(" Длина очереди", data->get_queue());
						break;
					default:
						break;
				}
			}

			out << std::endl;
		}
	};

private:
	void print_data(const char *name, stat_data_params params)
	{
		if(!out.is_open())
			return;
		char *sym = " |";
		int tabwidth = 12;
		out.unsetf(std::ios::right);
		out.setf(std::ios::left);
		out << std::setw(20) << name << sym;
		out.unsetf(std::ios::left);
		out.setf(std::ios::right);
		BOOST_FOREACH(boost::container::set<STAT_PARAMS>::value_type param, stat_params)
		{
			switch(param)
			{
				case MIN:
					out << std::setw(tabwidth) << params.min << sym;
					break;
				case MAX:
					out << std::setw(tabwidth) << params.max << sym;
					break;
				case SUM:
					out << std::setw(tabwidth) << params.sum << sym;
					break;
				case MEAN:
					out << std::setw(tabwidth) << params.mean << sym;
					break;
				case MEDIAN:
					out << std::setw(tabwidth) << params.median << sym;
					break;
				case KURTOSIS:
					out << std::setw(tabwidth) << params.kurtosis << sym;
					break;
				case VARIANCE:
					out << std::setw(tabwidth) << params.variance << sym;
					break;
				case DEVIATION:
					out << std::setw(tabwidth) << params.deviation << sym;
					break;
				default:
					break;
			}
		}
		out << std::endl;
	};

	void print_header(const char* string)
	{
		if(!out.is_open())
			return;
		out << std::endl;
		out.width(80);
		out.setf(std::ios::right);
		out << std::setw(30) << std::setfill(' ') << string << std::endl;
		out << std::endl;
	}


	template <class T>
	void print_value_with_postfix(const char *prefix, const char *name, const T value, const char *postfix)
	{
		if(!out.is_open())
			return;
		out.unsetf(std::ios::right);
		out.setf(std::ios::left);
		out << prefix << " ";
		out << std::setw(25) << name << ": ";
		out.unsetf(std::ios::left);
		out.setf(std::ios::right);
		out << std::setw(10) << value << ' ';
		out.unsetf(std::ios::right);
		out.setf(std::ios::left);
		out << std::setw(10) << postfix << std::endl;
	};

	template <class T>
	void print_subheader(const char *string, const T value)
	{
		if(!out.is_open())
			return;
		out << " ==== " << string << ": " << value << std::endl;
	};

	template <class T>
	void print_value(const char *name, const T value)
	{
		print_value_with_postfix<T>("", name, value, "");
	};

	void print_delimeter()
	{
		if(!out.is_open())
			return;
		out << "==================================================";
		out << "==================================================";
		out << "==================================";
		out << std::endl;
	};

	void print_table_header()
	{
		if(!out.is_open())
			return;
		char *sym = " |";
		int tabwidth = 12;
		out.unsetf(std::ios::right);
		out.setf(std::ios::left);
		out << std::setw(20) << ' ' << sym;
		out.unsetf(std::ios::left);
		out.setf(std::ios::right);
		BOOST_FOREACH(boost::container::set<STAT_PARAMS>::value_type param, stat_params)
		{
			switch(param)
			{
				case MIN:
					out << std::setw(tabwidth) << "МИН" << sym;
					break;
				case MAX:
					out << std::setw(tabwidth) << "МАКС" << sym;
					break;
				case SUM:
					out << std::setw(tabwidth) << "SUM" << sym;
					break;
				case MEAN:
					out << std::setw(tabwidth) << "СРЕДНЕЕ" << sym;
					break;
				case MEDIAN:
					out << std::setw(tabwidth) << "МЕДИАНА" << sym;
					break;
				case KURTOSIS:
					out << std::setw(tabwidth) << "KURTOSIS" << sym;
					break;
				case VARIANCE:
					out << std::setw(tabwidth) << "VARIANCE" << sym;
					break;
				case DEVIATION:
					out << std::setw(tabwidth) << "DEVIATION" << sym;
					break;
				default:
					break;
			}
		}
		out << std::endl;
		out << "--------------------------------------------------";
		out << "--------------------------------------------------";
		out << "----------------------------------";
		out << std::endl;
	}
};

typedef boost::shared_ptr<statistics_model> statistics_model_ptr;

#endif /* STATISTICSMODEL_H_ */
