#include <string>
#include <chrono>
#include <iomanip>
#include "format.h"

using std::string;

// helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long s) { 
  std::chrono::seconds sec{s};
  std::chrono::hours hr = std::chrono::duration_cast<std::chrono::hours>(sec);
  sec -= std::chrono::duration_cast<std::chrono::seconds>(hr);
  std::chrono::minutes min = std::chrono::duration_cast<std::chrono::minutes>(sec);
  sec -= std::chrono::duration_cast<std::chrono::seconds>(min);
  std::stringstream ss{};
  //HH:MM:SS
  ss << std::setw(2) << std::setfill('0') << hr.count() << std::setw(1) << ":"<< std::setw(2) << std::setfill('0') << min.count()<< std::setw(1) << ":"<< std::setw(2) << std::setfill('0') << sec.count(); 
  return ss.str(); 
}