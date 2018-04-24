#include <iostream>
#include <string>
#include <vector>
#include "../include/pipeline.h"

int main (int argc, char * argv[]) {

	std::vector <std::string> instructions, stage_if, stage_id;
	std::vector <std::string> stage_ex, stage_mem, stage_wb;

	int cycle = 0, worst_case = 1 + 4 * (instructions.size ());

	readInstructions (instructions);

	for (int i = 0; i < worst_case; i++) {
		stage_if.push_back ("0");
		stage_id.push_back ("0");
		stage_ex.push_back ("0");
		stage_mem.push_back ("0");
		stage_wb.push_back ("0");
	}

	pipeline (stage_if, stage_id, stage_ex, stage_mem, stage_wb, instructions, cycle);

	printStages (stage_if, stage_id, stage_ex, stage_mem, stage_wb, cycle);

}