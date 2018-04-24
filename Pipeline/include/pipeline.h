#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include <iostream>
#include <string>
#include <vector>

void readInstructions (std::vector <std::string> &instructions);

void changeDependencies (std::vector <std::string> &dependencyRegisters, 
						 const std::string &newRegister);

int dependencies (const int &cicle, 
				  std::vector <std::string> &dependencyRegisters,
				  const std::string &register_2,
				  const std::string &register_3,
				  const std::string &register_aux);

void stages (std::vector <std::string> &stage_if,
			 std::vector <std::string> &stage_id,
			 std::vector <std::string> &stage_ex,
			 std::vector <std::string> &stage_mem,
			 std::vector <std::string> &stage_wb,
			 const std::string instruction,
			 const int &cycle,
			 const int &i);

void pipeline (std::vector <std::string> &stage_if,
			   std::vector <std::string> &stage_id,
			   std::vector <std::string> &stage_ex,
			   std::vector <std::string> &stage_mem,
			   std::vector <std::string> &stage_wb, 
			   std::vector <std::string> instructions,
			   int &cycle);

void printStages (std::vector <std::string> stage_if,
		    std::vector <std::string> stage_id,
		    std::vector <std::string> stage_ex,
		    std::vector <std::string> stage_mem,
		    std::vector <std::string> stage_wb, 
		    int cycle);

#endif