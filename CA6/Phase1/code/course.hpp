#ifndef COURSE
#define COURSE

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "time.hpp"
#include "date.hpp"
#include "exception.hpp"
#include "messages.hpp"

class Course
{
public:
    Course(std::string i,std::string n , std::string p_n , int cap ,std::vector <std::string> m_i,std::string pre,std::string d, std::string t,std::string c_n);
    bool is_Valid_Id(std::string course_id);
    std::string get_Info();
    std::string get_All_Info();
    std::string get_Name();
    bool is_Interrupted(Course *course);
    bool is_Interrupted(std::string time);
    bool is_Valid_Semester(std::string semester);
    bool is_Valid_Major(std::string id);
    Week Specify_Day_Of_Week(std::string day_of_week_str);
    void Free_Allocated_Memory();

private:
    std::string id;
    std::string name;
    std::string professor_name;
    std::string class_number;
    std::string prerequisite;
    std::vector<std::string> majors_id;

    int capacity;
    Date *exam_date;
    Time *class_time;
};

#endif