#include "../include/pipeline.h"

/**
 * This function will store in a vector of strings the instructions give in file.
 * @param instructions
 */
void readInstructions (std::vector <std::string> instructions) {

	std::string instruction;

	while (getline (std::cin, instruction)) {
		instructions.push_back(instruction);
	}

}

/**
 * This function will change the dependencies to be check by the next
 * instruction, assuring that will be no data conflicts.
 */
void changeDependencies (std::vector <std::string> dependencyRegisters, 
						 const std::string newRegister) {

	for (int i = 3; i > 0; i--) {
		dependencyRegisters[i] = dependencyRegisters[i-1];
	}
	dependencyRegisters[0] = newRegister;

}

/**
 * This function will return the cycle that will be executed in the next line.
 */
int dependencies (const int cycle, 
				  std::vector <std::string> &dependencyRegisters,
				  const std::string register_2,
				  const std::string register_3,
				  const std::string register_aux = "0") {

	for (int i = 0; i < 4; i++) {

		if (cycle == 0) {
			return cycle;
		} else if ((dependencyRegisters[i].compare(register_2) == 0)
				|| (dependencyRegisters[i].compare(register_3) == 0)
				|| (dependencyRegisters[i].compare(register_aux) == 0)) {
			dependencyRegisters[i] = " ";
			return (cycle - i + 4);
		}

	}

	return (cycle +1);

}

/**
 * This function will assign each instruction on its stages' vector.
 */
void stages (std::vector <std::string> stage_if,
			 std::vector <std::string> stage_id,
			 std::vector <std::string> stage_ex,
			 std::vector <std::string> stage_mem,
			 std::vector <std::string> stage_wb,
			 const std::string instruction,
			 const int cycle,
			 const int i) {

	stage_if[cycle - i] = instruction;
	stage_id[cycle + 1 - i] = instruction;
	stage_ex[cycle + 2 - i] = instruction;
	stage_mem[cycle + 3 - i] = instruction;
	stage_wb[cycle + 4 - i] = instruction;

}

/**
 * This function will simulate the pipeline and handle the operations and dependencies. 
 */
void pipeline (std::vector <std::string> stage_if,
			   std::vector <std::string> stage_id,
			   std::vector <std::string> stage_ex,
			   std::vector <std::string> stage_mem,
			   std::vector <std::string> stage_wb, 
			   std::vector <std::string> instructions,
			   int cycle) {

	std::string instruction, label, operation;
	std::string register_aux, no_dependency = " ";
	std::string rest, register_1 = " ", register_2, register_3;
	std::vector <std::string> dependencyRegisters (4);
	std::size_t found;
	bool pass_label = false;
	int size = instructions.size ();

	for (int i = 0; i < size; i++, cycle++) {

		instruction = instructions [i];
		found = instruction.find_first_of (":");

		if (found != std::string::npos) {
			operation = instruction.substr (0, found);
		} else {
			found = instruction.find_first_of (":");
			operation = instruction.substr (0, found);
			rest = instruction.substr (found + 1);
		}

		if (operation.compare (label) == 0) {
			pass_label = false;
		} else if ((operation.compare ("add") == 0  || operation.compare("sub") == 0  
			     && pass_label == false)){

			found = rest.find_last_of (" ");
			register_3 = rest.substr (found + 1);
			rest = rest.substr (0, found - 1);
			found = rest.find_last_of (" ");
			register_2 = rest.substr (found + 1);
			register_aux = rest.substr (0, found - 1);
			cycle = dependencies (cycle, dependencyRegisters, register_2, 
				                  register_3, register_aux);
			stages (stage_if, stage_id, stage_ex, stage_mem, stage_wb,
				    instruction, cycle, i);
			register_1 = register_aux;

		} else if ((operation.compare ("beq") == 0  || operation.compare("bne") == 0  
			     && pass_label == false)) {

			found = rest.find_first_of (",");
			register_2 = rest.substr (0, found);
			rest = rest.substr (found + 2);
			found = rest.find_first_of (",");
			register_3 = rest.substr (0, found);
			label = rest.substr (found + 2);
			cycle = dependencies (cycle, dependencyRegisters, register_2,
				                  register_3);
			stages (stage_if, stage_id, stage_ex, stage_mem, stage_wb,
				    instruction, cycle, i);
			pass_label = true;
			register_1 = no_dependency;

		} else if (operation.compare ("lw") == 0 && pass_label == false) {

			found = rest.find_first_of (",");
			register_2 = rest.substr (0, found);
			rest = rest.substr (found + 2);
			found = rest.find_first_of ("(");
			rest = rest.substr (found + 1);
			register_3 = rest.substr (0, rest.size () - 1);
			cycle = dependencies (cycle, dependencyRegisters, register_2, register_3);
			stages (stage_if, stage_id, stage_ex, stage_mem, stage_wb,
				    instruction, cycle, i);
			register_1 = register_2;

		} else if (operation.compare ("sw") == 0 && pass_label == false) {

			found = rest.find_first_of (",");
			register_2 = rest.substr (0, found);
			rest = rest.substr (found + 2);
			found = rest.find_first_of ("(");
			rest = rest.substr (found + 1);
			register_3 = rest.substr (0, rest.size () - 1);
			cycle = dependencies (cycle, dependencyRegisters, register_2, register_3);
			stages (stage_if, stage_id, stage_ex, stage_mem, stage_wb,
				    instruction, cycle, i);
			register_1 = no_dependency;

		} else if (operation.compare ("j") == 0 && pass_label == false) {
			
			label = rest;
			if (cycle != 0) {
				cycle++;
			}
			stages (stage_if, stage_id, stage_ex, stage_mem, stage_wb,
				    instruction, cycle, i);
			pass_label = true;
			register_1 = no_dependency;

		}

		changeDependencies (dependencyRegisters, register_1);

	}

	cycle = cycle - size + 5;

}

/**
 * This function will print every stage in execution.
 */
void printStages (std::vector <std::string> stage_if,
		    std::vector <std::string> stage_id,
		    std::vector <std::string> stage_ex,
		    std::vector <std::string> stage_mem,
		    std::vector <std::string> stage_wb, 
		    int cycle) {

	std::cout << "Quantidade de ciclos total: " << cycle << std::endl;
	std::cout << std::endl << "-------------------------------------------------------" << std::endl;
	for (int i = 0; i < cycle; i++){
		std::cout << "Ciclo " << (i + 1) << std::endl;
		std::cout << "IF:     " << stage_if[i] << std::endl;
		std::cout << "ID:     " << stage_id[i] << std::endl;
		std::cout << "EX:     " << stage_ex[i] << std::endl;
		std::cout << "MEM:  " << stage_mem[i] << std::endl;
		std::cout << "WB:     " << stage_wb[i] << std::endl;
		std::cout << "-------------------------------------------------------" << std::endl;
	}

}