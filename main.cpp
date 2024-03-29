//#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

//struct Employee{
//    char employee_id [13];
//    char dept_id [30];
//    char employee_name [50];
//    char employee_position [50];
//};

struct Department{
    char dept_id [30];
    char dept_name [50];
    char dept_manager [50];
};

const char DELETE_FLAG = '*';
const char ACTIVE_FLAG = ' ';
const int FILE_HEADER_SIZE = sizeof(int);

class Employee
{
private:
    char employee_id [13];
    //char dept_id [30];
    char employee_name [50];
    char employee_position [50];
    //int RRN;

public:
    const char *getEmployeeId() const;

    const char *getEmployeeName() const;

    const char *getEmployeePosition() const;

    Employee();
    Employee( string , string , string );
    //void setRRN(int);
    int writeEmployeeLengthIndecator(fstream &);
    
    static bool deleteEmployeeByRRN(int , fstream &);
    //static Employee GetEmployeeByRRN(int , fstream &);
    void readEmployee(fstream &);
    void writeEmployee(fstream &);
    friend istream& operator >> (istream &, Employee &);
    friend ostream& operator << (ostream &, Employee &);
    ~Employee();
};

Employee getEmployee(fstream &fstream);

Employee::Employee(string name, string position, string id)
{
    strcpy(employee_name,name.c_str());
    strcpy(employee_position,position.c_str());
    strcpy(employee_id,id.c_str());
}
Employee::Employee()
{
    string emptyStr = "                                                 ";
    strcpy(employee_name,emptyStr.c_str());
    strcpy(employee_position,emptyStr.c_str());
    strcpy(employee_id,emptyStr.c_str());
}
Employee::~Employee(){}


void Employee::readEmployee(fstream &infile) {
    char c;
    int nextDel = -1;
    infile.get(c);

    if (c==DELETE_FLAG) {
        cout<<"deleted record"<<endl;
        return;
    }

    infile.read((char*)&nextDel, sizeof(int));
    //cout<<"view nextDe:"<<nextDel<<endl;
    infile.read(employee_name, 10);
    //cout<<"name: "<<employee_name<<endl;
    infile.read(employee_position, 10);
    //cout<<"password: "<<employee_position<<endl;
    infile.read(employee_id, 10);
    //cout<<"id: "<<employee_id<<endl;
}

bool Employee::deleteEmployeeByRRN(int RNN, fstream &file)
{
    int lastDeletedRecord = -1, numOfRecords = 0;
    char c;

    file.seekp(0, ios::end);
    numOfRecords = file.tellp()/ 35;
    if(RNN >= numOfRecords) return false;

    file.seekg(0,ios::beg);
    file.read((char*)&lastDeletedRecord, FILE_HEADER_SIZE);

    file.seekg(FILE_HEADER_SIZE + RNN * 35, ios::beg);
    file.get(c);
    if(c==DELETE_FLAG) return false;

    file.seekp(FILE_HEADER_SIZE + RNN * 35, ios::beg);
    file.put(DELETE_FLAG);
    file.write((char*)& lastDeletedRecord, sizeof(int));

    file.seekp(0,ios::beg);
    file.write((char*)& RNN, FILE_HEADER_SIZE);

    return true;
}


int Employee::writeEmployeeLengthIndecator(fstream &file)
{
    //RRN = -1;
    int lastDeletedRecord = -1, nextDeletedRecord = -1;
    char c;
    file.seekg(0,ios::beg);
    file.read((char*)&lastDeletedRecord, FILE_HEADER_SIZE);
    if(lastDeletedRecord == -1)
    {
        file.seekp(0, ios::end);
        //RRN = file.tellp()/ 35;
    }
    else
    {
        //RRN = lastDeletedRecord;
        file.seekg(FILE_HEADER_SIZE + lastDeletedRecord*35, ios::beg);
        file.get(c);
        if (c != DELETE_FLAG) return -1;
        file.read((char*)&nextDeletedRecord, sizeof(int));
        file.seekp(0,ios::beg);
        file.write((char*)&nextDeletedRecord, FILE_HEADER_SIZE);

        file.seekp(FILE_HEADER_SIZE + lastDeletedRecord*35, ios::beg);

    }
    writeEmployee(file);

    return 1;
}

void Employee::writeEmployee(fstream &outfile) {
    int nextDel = -1;
    outfile.put(ACTIVE_FLAG);
    outfile.write((char*)& nextDel, sizeof(int));
    outfile.write(employee_name, 10);
    outfile.write(employee_position, 10);
    outfile.write(employee_id, 10);
}


istream& operator >> (istream & str, Employee & s)
{
    string ss;
    str>>ss;
    strcpy(s.employee_name, ss.c_str());
    str>>ss;
    strcpy(s.employee_position, ss.c_str());
    str>>ss;
    strcpy(s.employee_id, ss.c_str());
    return str;
}

ostream& operator << (ostream & str, Employee & s)
{
    str<<s.employee_name<<endl;
    str<<s.employee_position<<endl;
    str<<s.employee_id<<endl;
    return str;
}

const char *Employee::getEmployeeId() const {
    return employee_id;
}

const char *Employee::getEmployeeName() const {
    return employee_name;
}

const char *Employee::getEmployeePosition() const {
    return employee_position;
}

void addEmployee(Employee emp,fstream& file ){
    file.seekp(0,ios::end);
    string x = emp.getEmployeeName() ;
    x += "|" ;
    x += emp.getEmployeePosition() ;
    x += "|" ;
    x += emp.getEmployeeId() ;
    x += "|" ;
    int size = x.size() ;
    string record = to_string(size) + x ;
    file.write(record.c_str() ,size+3);
}
//Employee parseEmp(string x){
//    int count = 0  , p = 0;
//    string name , id ,pos ;
//    for (int i = 0; i < x.size(); ++i) {
//        if (x[i]=='|'){
//            if (count==0){
//                name = x.substr(p,i) ;
//                cout << name << endl ;
//                p = i ;
//                count++ ;
//            }else if (count == 1){
//                pos = x.substr(p,i) ;
//                cout << pos << endl ;
//                p = i ;
//            }else {
//                id = x.substr(p,i) ;
//                cout << id << endl ;
//                p = i ;
//            }
//        }
//    }
//    return Employee(name , pos,id) ;
//}

void getEmployee1(fstream &file) {
    file.seekg(0 , ios::beg) ;
    int size ;
    file >> size ;//111
    char x[size] ;
    file.read(x, size) ;
    for (int i = 0; i < size; ++i) {
        cout << x[i] ;
    }
    cout << endl ;
}
int main()
{
    char c ;
    bool b;
    Employee employee;



    fstream f("EmployeesData.txt", ios::in | ios::out |ios::app);
    if(!f)
    {
        cout << "couldn't open file"<<endl;
        system("PAUSE");
        return 0;
    }


    do {
        f.seekp(0,ios::end);
//        int pos = f.tellp();
//        if(pos <= 0)
//        {
//            int header = -1;
//            f.write((char*) & header, FILE_HEADER_SIZE);
//        }

        cout<< "Choose the operation to perform"<<endl;
        cout<< "V for View" <<endl;
        cout<< "I for insert" <<endl;
        cout<< "D for delete" <<endl;
        cout<< "E for Exit" <<endl;
        cin>>c;

        switch(c)
        {
            case 'V':
            case 'v':
                getEmployee1(f) ;
                //cout << employee << endl ;
                break;
            case 'I':
            case 'i':
                cout<< "Enter Employee name, position, and ID" <<endl;
                cin >> employee;
                addEmployee(employee,f);
                //cout << "Employee inserted" << endl ;
                break;
            case 'D':
            case 'd':
                cout<< "enter RRN"<<endl;
                //cin>> RRN;
                //b = Employee::deleteEmployeeByRRN(RRN,f);
                if(b) cout << "sucessfully deleted"<<endl;
                else cout<< "Error, Invalid RRN or already deleted"<<endl;
                break;
            default:
                break;
        }

    } while (c!='E' && c!='e');

    f.close();

    system("PAUSE");
    return EXIT_SUCCESS;
}




//int main() {
//
//    static int empID = 0 , deptId = 0 ;
//    fstream myFile ;
//    Employee emp ;
//    myFile.open("data.txt" , ios::out | ios::in | ios::app) ;
//    string x,temp ;
//    cout << "Enter EMP Name : " << endl ;
//    cin >> emp.employee_name ;
//    //emp.employee_name += '|';
////    x+=temp ;
////    cout << "Enter EMP position : " << endl ;
////    cin >> temp ;
////    temp+='|' ;
////    x+=temp ;
////    empID ++ ;
////    deptId++;
////    x.append((char) empID+"|") ;
////    x.append((char) deptId+"|") ;
//
//
//    cout << x << endl ;
//
//}
