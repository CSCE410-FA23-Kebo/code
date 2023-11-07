#include "RoundRobin.h"

/*
This is a constructor for RoundRobin Scheduler, you should use the extractProcessInfo function first
to load process information to process_info and then sort process by arrival time;

Also initialize time_quantum
*/
RoundRobin::RoundRobin(string file, int time_quantum) {
	// extract info from file
	extractProcessInfo(file);

	// initialize time_quantum
	this->time_quantum = time_quantum;
}

// Schedule tasks based on RoundRobin Rule
// the jobs are put in the order the arrived
// Make sure you print out the information like we put in the document
void RoundRobin::schedule_tasks() {
	int system_time = 0;
	// iterate until all processes are complete
	while (!processVec.empty()) {
		// go to next non-complete process
		shared_ptr<Process> temp_proc = processVec.front();
		processVec.pop();

		// run process for time quantum, unless there is less time remaining
		int elapsed_time = min(time_quantum, temp_proc->get_remaining_time());
		assert(elapsed_time >= 0 && !temp_proc->is_Completed()); // if elapsed time is less than 0 then should be complete
		temp_proc->Run(elapsed_time);
		
		// "wait" until arrival time if system is ahead and print NOP
		for (; system_time < temp_proc->get_arrival_time(); ++system_time) {
			print(system_time, -1, false);
		}

		// print each system time step
		int pid = temp_proc->getPid();
		for (int i = 0; i < elapsed_time; ++i) {
			print(system_time, pid, false);
			system_time++;
		}

		// update num_complete processes
		if (temp_proc->is_Completed()) {
			print(system_time, pid, true);
		}
		// re-add process if incomplete
		else {
			processVec.push(temp_proc);
		}
	}
}


/*************************** ALL FUNCTIONS UNDER THIS LINE ARE COMPLETED FOR YOU ***************************/


// Default constructor
RoundRobin::RoundRobin() {
	time_quantum = 0;
}

// Time quantum setter
void RoundRobin::set_time_quantum(int quantum) {
	this->time_quantum = quantum;
}

// Time quantum getter
int RoundRobin::get_time_quantum() {
	return time_quantum;
}

// Print function for outputting system time as part of the schedule tasks function
// Feel free to modify this if you want :)
void RoundRobin::print(int system_time, int pid, bool isComplete){
	string s_pid = pid == -1 ? "NOP" : to_string(pid);
	cout << "System Time [" << system_time << "].........Process[PID=" << s_pid << "] ";
	if (isComplete)
		cout << "finished its job!" << endl;
	else
		cout << "is Running" << endl;
}

// Read a process file to extract process information
// All content goes to proces_info vector
void RoundRobin::extractProcessInfo(string file){
	// open file
	ifstream processFile (file);
	if (!processFile.is_open()) {
		perror("could not open file");
		exit(1);
	}

	// read contents and populate process_info vector
	string curr_line, temp_num;
	int curr_pid, curr_arrival_time, curr_burst_time;
	while (getline(processFile, curr_line)) {
		// use string stream to seperate by comma
		stringstream ss(curr_line);
		getline(ss, temp_num, ',');
		curr_pid = stoi(temp_num);
		getline(ss, temp_num, ',');
		curr_arrival_time = stoi(temp_num);
		getline(ss, temp_num, ',');
		curr_burst_time = stoi(temp_num);
		shared_ptr<Process> p(new Process(curr_pid, curr_arrival_time, curr_burst_time));

		processVec.push(p);
	}

	// close file
	processFile.close();
}