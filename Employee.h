#include <string>
#include "Department.h"
using namespace std ;
class Employee
{
private:
    char employee_id [13];
    char dept_id [30];
    char employee_name [50];
    char employee_position [50];
public:

    const char *getEmployeeId() const{
        return employee_id ;
    }
    const char *getEmployeeName() const{
        return employee_name ;
    }
    const char *getEmployeePosition() const{
        return employee_position ;
    }
    const char *getDeptId() const{
        return dept_id ;
    }
    void setID(string id){
        strcpy(employee_id , id.c_str()) ;
    }

    void setDeptID(string id){
        strcpy(dept_id , id.c_str()) ;
    }
    Employee(){}
    void setValues(string record){
        string temp = "" ;
        int counter = 0 ;
        for (int i = 0; i < record.size(); ++i) {
            if (record[i] == '|'){
                switch (counter) {
                    case 0:
                        strcpy(employee_name,temp.c_str()) ;
                        break;
                    case 1:
                        strcpy(employee_id,temp.c_str()) ;
                        break;
                    case 2:
                        strcpy(employee_position,temp.c_str()) ;
                        break;
                    case 3:
                        strcpy(dept_id,temp.c_str()) ;
                        break;
                }
                counter++ ;
                temp="" ;
            }else {
                temp+=record[i] ;
            }
        }
    }
    // name|id|position|deptID
    Employee(string record){
        setValues(record) ;
    }

    friend istream& operator >> (istream &str, Employee &emp){
        string ss;
        cout << "Enter Employee Name : " ;
        str>>ss;
        strcpy(emp.employee_name, ss.c_str());

        cout <<endl<<"Enter Employee position : " ;
        str>>ss;
        strcpy(emp.employee_position, ss.c_str());

//        cout << "Enter Employee's Department ID : " ;
//        str>>ss;
//
//        while (!Department::searchByID(ss)){
//            cout << "Department don't found , please Enter Employee's Department ID Again : " ;
//            str>>ss;
//        }
//
//        strcpy(emp.dept_id,ss.c_str()) ;
        return str;
    }
    friend ostream& operator << (ostream &out , Employee &emp){
        out<<"Employee Name : "<<emp.getEmployeeName()<<endl;
        out<<"Employee Position : "<<emp.getEmployeePosition()<<endl;
        out<<"Employee ID : "<<emp.getEmployeeId()<<endl;
        out<<"Employee's Department ID : "<<emp.getDeptId()<<endl;
        return out;
    }
};

