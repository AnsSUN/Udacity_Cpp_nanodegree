#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  	string line;
	float freemem;
  	float totmem;
  	float usedmem;
  	string value;
  	string key;
  	string memunit;
  	std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  	if (filestream.is_open()) {
    	while (std::getline(filestream, line)) {
      		std::istringstream linestream(line);
      		while(linestream >> key >> value >> memunit){
      			if(key == "MemTotal:") {
        			totmem = std::stof(value);
      			} 
      			if (key == "MemFree:"){
        			freemem = std::stof(value);
      			}
            }
         usedmem = (totmem-freemem)/totmem;
      	}
      
  	}
  	return usedmem;
}

// Read and return the system uptime
long LinuxParser::UpTime() { 
	string line;
  	long uptime;
  	std::ifstream filestream(kProcDirectory + kUptimeFilename);
  	if (filestream.is_open()) {
    	std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> uptime;
  	}
  	return (uptime);
}

// Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return ActiveJiffies()+IdleJiffies(); }

// Read and return the number of active jiffies for a PID

long LinuxParser::ActiveJiffies(int pid) { 
  string line;
  long utime;
  long stime;
  long cutime;
  long cstime;
  string value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for(int i=0;i<13; ++i) {
      linestream >> value;
    }
    linestream >> utime >> stime >> cutime >> cstime;
  }
  return utime + stime + cutime + cstime ;
}

// Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
	string cpu;
  	string line;
  	long kuser;
  	long knice;
  	long ksystem;
  	std::ifstream stream(kProcDirectory + kVersionFilename);
  	if (stream.is_open()) {
      	std::getline(stream, line);
      	std::istringstream linestream(line);
      	linestream >> cpu;
      	if (cpu == "cpu"){
          linestream >> kuser >> knice >> ksystem; 
          return kuser + knice + ksystem;
        }
    }
  	return kuser + knice + ksystem; 
}

// Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  	string cpuname;
  	string line;
  	string kuser;
  	string knice;
  	string ksystem;
  	long kidle;
  	long kiowait;
  	std::ifstream filestream(kProcDirectory + kVersionFilename);
  	if (filestream.is_open()) {
      	std::getline(filestream, line);
      	std::istringstream linestream(line);
      	linestream >> cpuname;
          if(cpuname == "cpu"){
            linestream >> kuser >> knice >> ksystem >> kidle >> kiowait; 
            return kidle + kiowait;
          }
    }
  	return kidle + kiowait; 
}

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  	vector<string> cpu_val;
  	string val1, val2, val3, val4, val5, val6, val7, val8, val9, val10;
  	string key;
  	string ncpu;
  	string line;
  	std::ifstream stream(kProcDirectory + kVersionFilename);
  	if (stream.is_open()) {
      	std::getline(stream, line);
      	std::istringstream linestream(line);
        while(linestream >> key >> val1>> val2>> val3>> val4>> val5>> val6>> val7>> val8>> val9>> val10){
          	if(key == "cpu"){
          		cpu_val = {val1, val2 ,val3 , val4 , val5 , val6 , val7 , val8 , val9 , val10};
            }
    	}
    }
  	return cpu_val; 
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return std::stoi(value);
        }
      }
    }
  }
  return std::stoi(value);
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return stoi(value);
        }
      }
    }
  }
  return stoi(value);
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  string cmdl;
  string line;

  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> cmdl; 
    }
  return cmdl;
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  double value;
  string val;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        //changed to VmRSS: the exact physical memory being used as a part of Physical RAM Code review: https://review.udacity.com/?utm_campaign=ret_000_auto_ndxxx_submission-reviewed&utm_source=blueshift&utm_medium=email&utm_content=reviewsapp-submission-reviewed&bsft_clkid=4dad1220-a1d1-4d5a-b945-61117c4e2199&bsft_uid=62fde118-1634-41ba-bee3-a8ca24609a2d&bsft_mid=27cf6c9f-9452-4a10-abd9-82f9e5fa2267&bsft_eid=6f154690-7543-4582-9be7-e397af208dbd&bsft_txnid=d129d001-636e-4ede-9a73-fb565aa30469&bsft_mime_type=html&bsft_ek=2022-05-07T15%3A38%3A49Z&bsft_aaid=8d7e276e-4a10-41b2-8868-423fe96dd6b2&bsft_lx=3&bsft_tv=14#!/reviews/3504132
        if (key == "VmRSS:") {
          val = to_string((value / 1024));
          return val.substr(0,5);
        }
      }
    }
  }
  return val;
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return value;
}

//Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  string line;
  string usernm;
  string userid;
  string uid = Uid(pid);
  string x;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> usernm >> x >> userid) {
        if (userid == uid) {
          return usernm;
        }
      }
    }
  }
  return usernm;
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  string line;
  long pid_start;
  string value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for(int i=0;i<22; ++i) {
      linestream >> pid_start;
    }
  }
  return (pid_start) / sysconf(_SC_CLK_TCK);
}

