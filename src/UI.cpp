#include "Stack.hpp"
#include "Deque.hpp"
#include "Queue.hpp"
#include "Priority_Queue.hpp"
#include "Persistent.hpp"


#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "/home/nikolay/projects/algo/labs/2/src/mutable_list.h"
#include "/home/nikolay/projects/algo/labs/2/src/mutable_array.h"


std::vector<Stack<int>> stack_vec;

std::vector<Queue<int>> queue_vec;

std::vector<Deque<int>> deque_vec;

std::vector<Priority_Queue<int>> priority_q_vec;


void menu();
void run();
int create_adapter();
int check_state();
int printAdapter();
int get();
int push();
int pop();


// -----------------------------------------------------------------------------------------------------------------

void menu() {
	std::cout << std::endl;
	std::cout << "MENU\n";
	std::cout << std::endl;
	std::cout << "Available Commands:\n" << std::endl;
	std::cout << "0. exit \n" << std::endl;														
	std::cout << "1. menu\n" << std::endl;														
	std::cout << "2. create adapter\n" << std::endl;											
	std::cout << "3. check state\n" << std::endl;												
	std::cout << "4. print adapter\n" << std::endl;										
	std::cout << "5. get\n" << std::endl;														
	std::cout << "6. push\n" << std::endl;												
	std::cout << "7. pop\n" << std::endl;														
	std::cout << std::endl;
	std::cout << "Warning: " << "the program will finished after 10 unsuccessful input attempts\n";
	std::cout << std::endl;
}

void run() {
	menu();
	int bad_count = 10;
	int state = 1;
	std::string command;
	while (bad_count) {
		state = 1;
		std::cout << ">>> ";
		std::cin >> command;
		if (command == "0") {
			std::cout << "Are you sure? (y / n)" << std::endl;
			std::cout << ">> ";
			std::cin >> command;
			if (command == "yes" || command == "y" || command == "YES") {
				exit(0);
			}
		}
		else if (command == "1") { // menu
			menu();
			bad_count = 10;
		}
		else if (command == "2") { // create adapter
			state = create_adapter();
			if (state) {
				std::cout << "The operation was aborted" << std::endl;
			}
			else {
				std::cout << ">>> ";
				std::cin >> command;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "3") { // check state
			check_state();
			std::cout << ">> ";
			std::cin >> command;
			menu();
		}
		else if (command == "4") { // print adapter
			state = printAdapter();
			std::cout << ">> ";
			std::cin >> command;
			if (state) {
				std::cout << "The operation was aborted" << std::endl;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "5") { // get 
			state = get();
			std::cout << ">> ";
			std::cin >> command;
			if (state) {
				std::cout << "The operation was aborted" << std::endl;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "6") { // push 
			state = push();
			std::cout << ">> ";
			std::cin >> command;
			if (state) {
				std::cout << "The operation was aborted" << std::endl;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "7") { // pop 
			state = pop();
			std::cout << ">> ";
			std::cin >> command;
			if (state) {
				std::cout << "The operation was aborted" << std::endl;
			}
			menu();
			bad_count = 10;
		}
		else {
			std::cout << command << '\n';
			bad_count--;
		}
	}
}

// -----------------------------------------------------------------------------------------------------------------


void promptAbort() {
	std::cout << std::endl;
	std::cout << "Enter '" << "abort" << "' to finish the operation prematurely (the operation will not be executed)" << std::endl;
}

// -----------------------------------------------------------------------------------------------------------------


bool isValidSizeAdapter(const std::string& s_size) {
	size_t pos;
	try {
		int size = std::stoi(s_size, &pos);

		if (pos != s_size.length()) {
			return false;
		}
		if (size < 0 || size > 1000) {
			return false;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}


bool isValidIndex(const std::string& s_index, size_t size) {
	size_t pos;
	try {
		int index = std::stoi(s_index, &pos);

		if (pos != s_index.length()) {
			return false;
		}
		if (index < 0 || index >= size) {
			return false;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}

bool isValidInt(std::string s_defaultElement) {
	size_t pos;
	try {
		int defaultElement = std::stoi(s_defaultElement, &pos);

		if (pos != s_defaultElement.length()) {
			return false;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}


std::string getTypeAdapter() {
	std::cout << "1. stack" << std::endl;
	std::cout << "2. queue" << std::endl;
	std::cout << "3. deque" << std::endl;
    std::cout << "4. Priority queue" << std::endl;
	std::cout << "Input the " << "type" << " of adapter:" << std::endl;

	std::string type_adapter;
	int bad_count = 10;

	while (bad_count) {
		std::cout << ">> ";
		std::cin >> type_adapter;

		if (type_adapter == "1" || type_adapter == "stack" || type_adapter == "Stack") {
			type_adapter = "1";
			break;
		}
		else if (type_adapter == "2" || type_adapter == "queue" || type_adapter == "Queue") {
			type_adapter = "2";
			break;
		}
		else if (type_adapter == "3" || type_adapter == "deque" || type_adapter == "Deque") {
			type_adapter = "3";
			break;
		}
        else if (type_adapter == "4" || type_adapter == "Priority queue" || type_adapter == "pririty queue") {
            type_adapter = "4";
            break;
        }
		else if (type_adapter == "abort") {
			break;
		}
		else {
			std::cout << "Type of Adapter = '" << type_adapter << "' is not valid type of adapter\n" << std::endl;
			bad_count--;
		}
	}

	std::cout << '\n';

	if (bad_count == 0) {
		return "ERR-0001-ATTEXP"; // attempts expired
	}
	else if (type_adapter == "abort") {
		return "ERR-1111-FUNCINTERR"; // function interrupted
	}
	return type_adapter;
}


int getSizeAdapter() {
	std::string s_sizeadapter;
	int sizeadapter = -1;
	int bad_count = 10;

	std::cout << "Input the " << "size" << " of adapter" << std::endl;
	while (bad_count) {
		std::cout << ">> ";
		std::cin >> s_sizeadapter;
		if (isValidSizeAdapter(s_sizeadapter)) {
			size_t pos;
			sizeadapter = std::stoi(s_sizeadapter, &pos);
			break;
		}
		else if (s_sizeadapter == "abort") {
			break;
		}
		else {
			std::cout << "Size of Adapter = '" << s_sizeadapter << "' is not valid size for adapter\n" << std::endl;
			bad_count--;
		}
	}

	if (s_sizeadapter == "abort") {
		return -1;
	}
	else if (bad_count == 0) {
		return -1;
	}

	return sizeadapter;
}

// -----------------------------------------------------------------------------------------------------------------
// Create adapter

int fillStack(Stack<int>& stack, int size) {

	int bad_count = 10;
	std::string element;
	std::string forERR = "NONE";

	int i = 0;
	while (bad_count && i < size) {
		std::cout << "Input the " << "new element" << " for pushing in stack (added " << i << "/" << size << ")\n";
		std::cout << ">> ";
		std::cin >> element;

		if (isValidInt(element)) {
			size_t pos;
			int el = std::stoi(element, &pos);
			try {
				stack.push(el);
			}
			catch (const SEQUENCE_EXCEPTION& err) {
				std::cout << err.what() << std::endl;
				break;
			}
			i++;
		}
		else if (element == "abort") {
			forERR = "ERR-1111-FUNCINTERR";
			break;
		}
		else {
			std::cout << "Element = '" << element << "' is not valid element for stack" << std::endl;
			bad_count--;
		}
	}

	return 0;
}


int fillQueue(Queue<int>& queue, int size) {

	int bad_count = 10;
	std::string element;

	int i = 0;
	while (bad_count && i < size) {
		std::cout << "Input the " << "new element" << " for pushing in queue (added " << i << "/" << size << ")" << std::endl;
		std::cout << ">> ";
		std::cin >> element;

		if (isValidInt(element)) {
			size_t pos;
			int el = std::stoi(element, &pos);
			try {
				queue.enqueue(el);
			}
			catch (const SEQUENCE_EXCEPTION& err) {
				std::cout << err.what() << std::endl;
				break;
			}
			i++;
		}
		else {
			std::cout << "Element = '" << element << "' is not valid element for queue" << std::endl;
			bad_count--;
		}
	}

	return 0;
}


int fillDeque(Deque<int>& deque, int size) {

	int bad_count = 10;
	std::string element;
	std::string typepush;

	int i = 0;
	while (bad_count && i < size) {
		std::cout << "Input the " << "type of push" << " (1 = push_front / 2 = push_back)\n";
		std::cout << ">> ";
		std::cin >> typepush;
		if (typepush == "1" || typepush == "2") {
			std::cout << "Input the " << "new element" << " for pushing in deque (added " << i << "/" << size << ")" << std::endl;
			std::cout << ">> ";
			std::cin >> element;

			if (isValidInt(element)) {
				size_t pos;
				int el = std::stoi(element, &pos);
				try {
					if (typepush == "1") {
						deque.push_front(el);
					}
					else if (typepush == "2") {
						deque.push_back(el);
					}
				}
				catch (const SEQUENCE_EXCEPTION& err) {
					std::cout << err.what() << std::endl;
					break;
				}
				i++;
			}
			else {
				std::cout << "Element = '" << element << "' is not valid element for queue" << std::endl;
				bad_count--;
			}
		}
		else {
			std::cout << "Type of Push = '" << typepush << "' is not type of pushing element" << std::endl;
			bad_count--;
		}
	}
	return 0;
}


int fillPriorityQueue(Priority_Queue<int>& priority_queue, int size) {
    int bad_count = 10;
    std::string element;
    std::string priority;

    int i = 0;
    while (bad_count && i < size) {
        std::cout << "Input the " << "priority" << " for the new element (added " << i << "/" << size << ")" << std::endl;
        std::cout << ">> ";
        std::cin >> priority;

        if (!isValidInt(priority)) {
            std::cout << "Priority = '" << priority << "' is not valid priority" << std::endl;
            bad_count--;
            continue;
        }

        std::cout << "Input the " << "new element" << " for pushing in priority queue (added " << i << "/" << size << ")" << std::endl;
        std::cout << ">> ";
        std::cin >> element;

        if (isValidInt(element)) {
            size_t pos;
            int prio = std::stoi(priority, &pos);
            int el = std::stoi(element, &pos);
            try {
                priority_queue.push(prio, el);
            }
            catch (const SEQUENCE_EXCEPTION& err) {
                std::cout << err.what() << std::endl;
                break;
            }
            i++;
        }
        else {
            std::cout << "Element = '" << element << "' is not valid element for priority queue" << std::endl;
            bad_count--;
        }
    }

    return 0;
}


int create_adapter() {
	promptAbort();

	std::string type_adapter = getTypeAdapter();
	if (type_adapter.substr(0, 3) == "ERR") {
		return -1;
	}

	int sizeadapter = getSizeAdapter();
	if (sizeadapter < 0) {
		return -1;
	}

	if (type_adapter == "1") {
		stack_vec.push_back(Stack<int>());
		fillStack(stack_vec[stack_vec.size() - 1], sizeadapter);
	}
	else if (type_adapter == "2") {
		queue_vec.push_back(Queue<int>());
		fillQueue(queue_vec[queue_vec.size() - 1], sizeadapter);
	}
	else if (type_adapter == "3") {
		deque_vec.push_back(Deque<int>());
		fillDeque(deque_vec[deque_vec.size() - 1], sizeadapter);
	}
    else if (type_adapter == "4") {
        priority_q_vec.push_back(Priority_Queue<int>());
        fillPriorityQueue(priority_q_vec[priority_q_vec.size() - 1], sizeadapter);
    }

	return 0;
}

// ---------------------------------------------------------------------------------


void infoAdapter(int typeadapter, int index) {
	if (typeadapter == 1) {
		if (index >= 0 && index < stack_vec.size()) {
			std::cout << std::endl;
			std::cout << "Adapter - " << "Stack " << "[" << index << "]" << std::endl;
			std::cout << std::endl;

			std::cout << "Type of adapter: " << "stack" << std::endl;
			std::cout << "The size of adapter: " << stack_vec[index].size() << std::endl;
			std::cout << std::endl;
		}
		else {
			std::cout << "Index is out of range" << std::endl;
		}
	}
	else if (typeadapter == 2) {
		if (index >= 0 && index < queue_vec.size()) {
			std::cout << std::endl;
			std::cout << "Adapter - " << "Queue " << "[" << index << "]" << std::endl;
			std::cout << std::endl;

			std::cout << "Type of adapter: " << "queue" << std::endl;
			std::cout << "The size of adapter: " << queue_vec[index].size() << std::endl;
			std::cout << std::endl;
		}
		else {
			std::cout << "Index is out of range\n" << std::endl;
		}
	}
	else if (typeadapter == 3) {
		if (index >= 0 && index < deque_vec.size()) {
			std::cout << std::endl;
			std::cout << "Adapter - " << "Deque " << "[" << index << "]" << std::endl;
			std::cout << std::endl;

			std::cout << "Type of adapter: " << "deque" << std::endl;
			std::cout << "The size of adapter: " << deque_vec[index].size() << std::endl;
			std::cout << std::endl;
		}
    else if (typeadapter == 4) {
        if (index >= 0 && index < priority_q_vec.size()) {
            std::cout << std::endl;
            std::cout << "Adapter - " << "Priority Queue" << "[" << index << "]" << std::endl;
            std::cout << std::endl;

            std::cout << "Type of adapter: " << "Priority Queue" << std::endl;
            std::cout << "The size of adapter: " << priority_q_vec[index].size() << std::endl;
            std::cout << std::endl;
        }
    }
	else {
			std::cout << "Index is out of range" << std::endl;
		}
	}
}


int check_state() {
	if (stack_vec.size() == 0) {
		std::cout << std::endl;
		std::cout << "There are no one stack\n" << std::endl;
		std::cout << std::endl;
	}
	else {
		for (int i = 0; i < stack_vec.size(); ++i) {
			infoAdapter(1, i);
		}
	}

	if (queue_vec.size() == 0) {
		std::cout << std::endl;
		std::cout << "There are no one queue" << std::endl;
		std::cout << std::endl;
	}
	else {
		for (int i = 0; i < queue_vec.size(); ++i) {
			infoAdapter(2, i);
		}
	}

	if (deque_vec.size() == 0) {
		std::cout << std::endl;
		std::cout << "There are no one deque" << std::endl;
		std::cout << std::endl;
	}
	else {
		for (int i = 0; i < deque_vec.size(); ++i) {
			infoAdapter(3, i);
		}
	}
    if (priority_q_vec.size() == 0) {
        std::cout << std::endl;
        std::cout << "There are no one Priority Queue" << std::endl;
        std::cout << std::endl;
    }
    else {
        for (int i = 0; i < priority_q_vec.size(); ++i) {
            infoAdapter(4, i);
        }
    }

	return 0;
}


int select() {
	promptAbort();
	check_state();

	std::string type_adapter = getTypeAdapter();
	if (type_adapter.substr(0, 3) == "ERR") {
		return -1;
	}

	int bad_count = 10;
	std::string s_index;

	std::cout << "Input the " << "index" << " of adapter" << std::endl;
	while (bad_count) {
		std::cout << ">> ";
		std::cin >> s_index;
		if (s_index == "abort") {
			return -1;
		}
		if (type_adapter == "1") {
			if (isValidIndex(s_index, stack_vec.size())) {
				int index = stoi(s_index);
				return index;
			}
			else {
				std::cout << "Invalid index for stack-list: " << s_index << " is not found" << std::endl;
				bad_count--;
			}
		}
		else if (type_adapter == "2") {
			if (isValidIndex(s_index, queue_vec.size())) {
				int index = stoi(s_index);
				return index + stack_vec.size();
			}
			else {
				std::cout << "Invalid index for queue-list: " << s_index << " is not found" << std::endl;
				bad_count--;
			}
		}
		else if (type_adapter == "3") {
			if (isValidIndex(s_index, deque_vec.size())) {
				int index = stoi(s_index);
				return index + stack_vec.size() + queue_vec.size();
			}
			else {
				std::cout << "Invalid index for deque-list: " << s_index << " is not found" << std::endl;
				bad_count--;
			}
		}
	}

	if (!bad_count) {
		return -1;
	}
}


int printAdapter() {
    std::string type_adapter = getTypeAdapter();
    if (type_adapter.substr(0, 3) == "ERR") {
        return -1;
    }

    std::string s_index;
    int index = -1;
    int bad_count = 10;

    std::cout << "Input the " << "index" << " of adapter" << std::endl;
    while (bad_count) {
        std::cout << ">> ";
        std::cin >> s_index;
        if (isValidIndex(s_index, type_adapter == "1" ? stack_vec.size() :
                                      type_adapter == "2" ? queue_vec.size() :
                                      type_adapter == "3" ? deque_vec.size() :
                                      priority_q_vec.size())) {
            size_t pos;
            index = std::stoi(s_index, &pos);
            break;
        } else if (s_index == "abort") {
            break;
        } else {
            std::cout << "Index = '" << s_index << "' is not valid index for adapter\n" << std::endl;
            bad_count--;
        }
    }

    if (s_index == "abort") {
        return -1;
    } else if (bad_count == 0) {
        return -1;
    }

    if (type_adapter == "1") {
        if (index >= 0 && index < stack_vec.size()) {
            std::cout << "Stack [" << index << "]: ";
            stack_vec[index].print_stack();
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    } else if (type_adapter == "2") {
        if (index >= 0 && index < queue_vec.size()) {
            std::cout << "Queue [" << index << "]: ";
            queue_vec[index].print_queue();
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    } else if (type_adapter == "3") {
        if (index >= 0 && index < deque_vec.size()) {
            std::cout << "Deque [" << index << "]: ";
            deque_vec[index].print_Deque();
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    } else if (type_adapter == "4") {
        if (index >= 0 && index < priority_q_vec.size()) {
            std::cout << "Priority Queue [" << index << "]: ";
            priority_q_vec[index].print_Priority_Queue();
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    }

    return 0;
}

// -----------------------------------------------------------------------------------------------------------------
// Get / push / pop


int get() {
    std::string type_adapter = getTypeAdapter();
    if (type_adapter.substr(0, 3) == "ERR") {
        return -1;
    }

    std::string s_index;
    int index = -1;
    int bad_count = 10;

    std::cout << "Input the " << "index" << " of adapter" << std::endl;
    while (bad_count) {
        std::cout << ">> ";
        std::cin >> s_index;
        if (isValidIndex(s_index, type_adapter == "1" ? stack_vec.size() :
                                      type_adapter == "2" ? queue_vec.size() :
                                      type_adapter == "3" ? deque_vec.size() :
                                      priority_q_vec.size())) {
            size_t pos;
            index = std::stoi(s_index, &pos);
            break;
        } else if (s_index == "abort") {
            break;
        } else {
            std::cout << "Index = '" << s_index << "' is not valid index for adapter\n" << std::endl;
            bad_count--;
        }
    }

    if (s_index == "abort") {
        return -1;
    } else if (bad_count == 0) {
        return -1;
    }

    if (type_adapter == "1") {
        if (index >= 0 && index < stack_vec.size()) {
            std::cout << "Top element of Stack [" << index << "]: " << stack_vec[index].top() << std::endl;
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    } else if (type_adapter == "2") {
        if (index >= 0 && index < queue_vec.size()) {
            std::cout << "Front element of Queue [" << index << "]: " << queue_vec[index].front() << std::endl;
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    } else if (type_adapter == "3") {
        if (index >= 0 && index < deque_vec.size()) {
            std::cout << "Front element of Deque [" << index << "]: " << deque_vec[index].front() << std::endl;
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    }
	else if (type_adapter == "4") {
		std::cout << "Sorry, but you can't get element from Priority Queue, because this contradicts the logic of the priority queue" << std::endl;
	}

    return 0;
}

int push() {
    std::string type_adapter = getTypeAdapter();
    if (type_adapter.substr(0, 3) == "ERR") {
        return -1;
    }

    std::string s_index;
    int index = -1;
    int bad_count = 10;

    std::cout << "Input the " << "index" << " of adapter" << std::endl;
    while (bad_count) {
        std::cout << ">> ";
        std::cin >> s_index;
        if (isValidIndex(s_index, type_adapter == "1" ? stack_vec.size() :
                                      type_adapter == "2" ? queue_vec.size() :
                                      type_adapter == "3" ? deque_vec.size() :
                                      priority_q_vec.size())) {
            size_t pos;
            index = std::stoi(s_index, &pos);
            break;
        } else if (s_index == "abort") {
            break;
        } else {
            std::cout << "Index = '" << s_index << "' is not valid index for adapter\n" << std::endl;
            bad_count--;
        }
    }

    if (s_index == "abort") {
        return -1;
    } else if (bad_count == 0) {
        return -1;
    }

    std::string element;
    std::string priority; 
    std::cout << "Input the " << "new element" << " for pushing" << std::endl;
    std::cout << ">> ";
    std::cin >> element;

    if (!isValidInt(element)) {
        std::cout << "Element = '" << element << "' is not valid element" << std::endl;
        return -1;
    }

    int el = std::stoi(element);

    if (type_adapter == "1") {
        if (index >= 0 && index < stack_vec.size()) {
            stack_vec[index].push(el);
            std::cout << "Element pushed to Stack [" << index << "]" << std::endl;
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    } else if (type_adapter == "2") {
        if (index >= 0 && index < queue_vec.size()) {
            queue_vec[index].enqueue(el);
            std::cout << "Element pushed to Queue [" << index << "]" << std::endl;
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    } else if (type_adapter == "3") {
        if (index >= 0 && index < deque_vec.size()) {
            std::string typepush;
            std::cout << "Input the " << "type of push" << " (1 = push_front / 2 = push_back)\n";
            std::cout << ">> ";
            std::cin >> typepush;
            if (typepush == "1") {
                deque_vec[index].push_front(el);
            } else if (typepush == "2") {
                deque_vec[index].push_back(el);
            } else {
                std::cout << "Invalid push type" << std::endl;
                return -1;
            }
            std::cout << "Element pushed to Deque [" << index << "]" << std::endl;
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    } else if (type_adapter == "4") {
        if (index >= 0 && index < priority_q_vec.size()) {
            std::cout << "Input the " << "priority" << " for the new element" << std::endl;
            std::cout << ">> ";
            std::cin >> priority;
            if (!isValidInt(priority)) {
                std::cout << "Priority = '" << priority << "' is not valid priority" << std::endl;
                return -1;
            }
            int prio = std::stoi(priority);
            priority_q_vec[index].push(prio, el);
            std::cout << "Element pushed to Priority Queue [" << index << "]" << std::endl;
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    }

    return 0;
}


int pop() {
    std::string type_adapter = getTypeAdapter();
    if (type_adapter.substr(0, 3) == "ERR") {
        return -1;
    }

    std::string s_index;
    int index = -1;
    int bad_count = 10;

    std::cout << "Input the " << "index" << " of adapter" << std::endl;
    while (bad_count) {
        std::cout << ">> ";
        std::cin >> s_index;
        if (isValidIndex(s_index, type_adapter == "1" ? stack_vec.size() :
                                      type_adapter == "2" ? queue_vec.size() :
                                      type_adapter == "3" ? deque_vec.size() :
                                      priority_q_vec.size())) {
            size_t pos;
            index = std::stoi(s_index, &pos);
            break;
        } else if (s_index == "abort") {
            break;
        } else {
            std::cout << "Index = '" << s_index << "' is not valid index for adapter\n" << std::endl;
            bad_count--;
        }
    }

    if (s_index == "abort") {
        return -1;
    } else if (bad_count == 0) {
        return -1;
    }

    if (type_adapter == "1") {
        if (index >= 0 && index < stack_vec.size()) {
            if (!stack_vec[index].empty()) {
                stack_vec[index].pop();
                std::cout << "Element popped from Stack [" << index << "]" << std::endl;
            } else {
                std::cout << "Stack [" << index << "] is empty" << std::endl;
            }
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    } else if (type_adapter == "2") {
        if (index >= 0 && index < queue_vec.size()) {
            if (!queue_vec[index].empty()) {
                queue_vec[index].dequeue();
                std::cout << "Element popped from Queue [" << index << "]" << std::endl;
            } else {
                std::cout << "Queue [" << index << "] is empty" << std::endl;
            }
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    } else if (type_adapter == "3") {
        if (index >= 0 && index < deque_vec.size()) {
            std::string typepop;
            std::cout << "Input the " << "type of pop" << " (1 = pop_front / 2 = pop_back)\n";
            std::cout << ">> ";
            std::cin >> typepop;
            if (typepop == "1") {
                if (!deque_vec[index].empty()) {
                    deque_vec[index].pop_front();
                    std::cout << "Element popped from Deque [" << index << "]" << std::endl;
                } else {
                    std::cout << "Deque [" << index << "] is empty" << std::endl;
                }
            } else if (typepop == "2") {
                if (!deque_vec[index].empty()) {
                    deque_vec[index].pop_back();
                    std::cout << "Element popped from Deque [" << index << "]" << std::endl;
                } else {
                    std::cout << "Deque [" << index << "] is empty" << std::endl;
                }
            } else {
                std::cout << "Invalid pop type" << std::endl;
                return -1;
            }
        } else {
            std::cout << "Index is out of range" << std::endl;
            return -1;
        }
    }
    return 0;
}