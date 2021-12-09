#include <string>
using namespace std ;
class Department {

private:
    char dept_id [30];
    char dept_name [50];
    char dept_manager [50];
public:
    const char *getDeptId() const {
        return dept_id;
    }

    const char *getDeptName() const {
        return dept_name;
    }

    const char *getDeptManager() const {
        return dept_manager;
    }

    void setID(string id){
        strcpy(dept_id , id.c_str()) ;
    }

    friend istream& operator >> (istream &str, Department &department){
        string ss;
        cout << "Enter Department Name : " ;
        str>>ss;
        strcpy(department.dept_name,ss.c_str());

        cout <<endl<<"Enter Department Manager: " ;
        str>>ss;
        strcpy(department.dept_manager, ss.c_str());

        return str;
    }

    void setValues(string record){
        string temp = "" ;
        int counter = 0 ;
        for (int i = 1; i < record.size(); ++i) {
            if (record[i] == '|'){
                switch (counter) {
                    case 0:
                        strcpy(dept_name,temp.c_str()) ;
                        break;
                    case 1:
                        strcpy(dept_manager,temp.c_str()) ;
                        break;
                    case 2:
                        strcpy(dept_id,temp.c_str()) ;
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

    friend ostream& operator << (ostream &out , Department &dept){
        out<<setw(13)<<dept.getDeptId();
        out<<setw(20)<<dept.getDeptName();
        out<<setw(20)<<dept.getDeptManager()<< endl ;
        return out;
    }
};
