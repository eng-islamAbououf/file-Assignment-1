#include <fstream>
#include <cstring>
#include<bits/stdc++.h>
#include "Employee.h"
#include "Parser.h"

const char DELETE_FLAG = '*';
const char ACTIVE_FLAG = ' ';
const string EMP_P_INDEX = "primary.txt" ;
const string EMP_DATA = "EmployeesData.txt" ;
const string EMP_SEC_INDEX = "EmpSecIndex.txt" ;
const string DEPT_P_INDEX = "DeptPrimary.txt" ;
const string DEPT_DATA = "DepartmentData.txt" ;
const string META_DATA = "metaData.txt" ;

struct  Index{
    string id;
    int offset ;
    bool isActive = true ;
};
struct  EmpSecIndex{
    string dept_id;
    vector<int> offset ;
    bool isActive = true ;
};

int BSearch(Index pP[], int start, int end, string key);
void deleteDepartment(string id) ;
void addNewDepartment(Department department);

void deleteEmployee(string id);

void printEmp(string id , Employee& employee);

void printDepartment(string id , Department& department);

void write_query(Parser &parser);



Index setIndex(string txt){
    Index x ;
    if (txt[0]==DELETE_FLAG)
        x.isActive = false ;
    int index = 1 ;
    while (index < txt.length()){
        if (txt[index] == '|')
            break;
        index ++ ;
    }
    x.id = txt.substr(1,index-1).c_str() ;
    x.offset = stoi(txt.substr(index+1,txt.length()- index)) ;
    return x ;
}
//void addEmpToSecIndex(Employee & employee ,int offset){
//    fstream sec ;
//    sec.open(EMP_SEC_INDEX , ios:: app) ;
//    sec.seekp(0 , ios::end) ;
//    if (sec.tellp()==0){
//        sec << employee.getDeptId() << " " << to_string(offset) << "\n" ;
//    }else {
//
//    }
//    sec.close() ;
//}
void addNewEmployee(Employee &emp){

    fstream data ;
    fstream index ;
    data.open(EMP_DATA, ios::app) ;
    index.open(EMP_P_INDEX, ios::app) ;

    data.seekp(0,ios::end) ;
    index.seekp(0 , ios::end) ;

    int offset = data.tellp() ;
    int offset1 = index.tellp() ;
    string x = " ";
    x += emp.getEmployeeName() ;
    x += "|" ;
    x += emp.getEmployeeId() ;
    x += "|" ;
    x += emp.getEmployeePosition() ;
    x += "|" ;
    x += emp.getDeptId() ;
    x += "|" ;

    string y = " ";
    y+= emp.getEmployeeId() ;
    y+="|" ;
    y += to_string(offset) ;
    y+="\n" ;

    data << x.length() ;
    data << x.data() ;

    index << y.data() ;

    data.close() ;
    index.close() ;
//    addEmpToSecIndex(emp , offset1) ;
}

string getDepartment(int offset) {
    fstream file ;
    file.open(DEPT_DATA , ios :: in) ;
    file.seekg(offset , ios::beg) ;
    int size ;
    file >> size ;
    char x[size] ;
    file.read(x, size) ;
    return x;
}

string getEmployee(int offset) {
    fstream file ;
    file.open(EMP_DATA , ios :: in) ;
    file.seekg(offset , ios::beg) ;
    int size ;
    file >> size ;
    char x[size] ;
    file.read(x, size) ;
    return x;
}

void updateLastEmpID(int id ){
    fstream metaData ;
    metaData.open(META_DATA , ios::out | ios::in) ;
    metaData.seekp(0) ;
    string x = "LastEmpID : "+ to_string(id) ;
    metaData <<  x ;
    metaData.close();
}
void updateLastDeptID(int id ){
    fstream metaData ;
    metaData.open(META_DATA , ios::out | ios::in) ;
    char* x = new char [100];
    metaData.getline(x , 100 , '|') ;
    metaData.seekp(0 , ios::beg) ;

    metaData <<x <<"|LastDeptID : "<<to_string(id) ;
    metaData.close() ;
}
int getLastDeptID(){
    fstream metaData ;
    metaData.open(META_DATA, ios::in) ;
    int id ;
    metaData.seekg(33,ios::beg) ;
    metaData>> id ;
    metaData.close() ;
    return id ;
}

int getLastEmpID(){
    fstream metaData ;
    metaData.open(META_DATA, ios::in) ;
    int id ;
    metaData.seekg(11,ios::beg) ;
    metaData>> id ;
    metaData.close() ;
    return id ;
}

int fillArray(Index *arr , string fileName){
    fstream file ;
    file.open(fileName, ios::in);
    int i = 0 ;
    string txt ;
    while (getline(file , txt) && i < 10){
        arr[i] = setIndex(txt);
        i++ ;
    }
    file.close();
    return i ;
}

void reWriteFile(Index* arr , int size , string fileName ){
    fstream file ;
    file.open(fileName, ios::out);
    file.seekp(0);
    string txt ;
    int i =0 ;
    while (i<size){
        if (arr[i].isActive)
            txt+= ACTIVE_FLAG;
        else
            txt += DELETE_FLAG ;
        txt = txt + arr[i].id + '|' + to_string(arr[i].offset) + '\n';
        i++;
    }
    file.write(txt.c_str() , txt.length()) ;
    file.close();
}

void display_all_Employees(){
    Index arr [15] ;
    Employee employee ;
    int size = fillArray(arr , EMP_P_INDEX) ;
    int index = 0 , counter = 0;
    cout << endl ;

    cout<<setw(14)<<"Employee ID";
    cout<<setw(20)<<"Employee Name";
    cout<<setw(20)<<"Employee Position";
    cout<<setw(20)<<"Department ID" << endl ;

    while (index<size){
        if (arr[index].isActive){
            employee.setValues(getEmployee(arr[index].offset)) ;
            cout << (++counter) << employee ;
        }
        index++ ;
    }
}

void display_all_Departments(){
    Index arr [15] ;
    Department department ;
    int size = fillArray(arr , DEPT_P_INDEX) ;
    int index = 0  , counter = 0;
    cout << endl ;

    cout<<setw(14)<<"Department ID";
    cout<<setw(20)<<"Department Name";
    cout<<setw(20)<<"Department Manager" << endl ;

    while (index<size){
        if (arr[index].isActive){
            department.setValues(getDepartment(arr[index].offset)) ;
            cout << (++counter) << department ;
        }
        index++ ;
    }
}

int main()
{
    int choice ;
    Employee employee;
    Department department ;
    string id  ;
    Parser parser ;

    int EMP_ID = getLastEmpID() ;
    int DEPT_ID = getLastDeptID() ;

    do {

        cout << "\nChoose the operation to perform"<<endl
         << "1- add New Employee " <<endl
         << "2- add New Department " <<endl
         << "3- Delete Employee (ID) " <<endl
         << "4- Delete Department (ID) " <<endl
         << "5- Print Employee (ID) " <<endl
         << "6- Print Employee (Dept_ID) " <<endl
         << "7- Print Department (ID) " <<endl
         << "8- Print Department (Name) " <<endl
         << "9- Write a Query" <<endl
         << "10- Exit" <<endl;
        cin>>choice;

        switch(choice) {
            case 1:
                cin>>employee ;
                cout << "\nChoose Your Department\n" ;
                display_all_Departments() ;
                cout << "Enter Department ID \n" ;
                cin >> id ;
                employee.setDeptID(id) ;
                employee.setID(to_string(++EMP_ID)) ;
                addNewEmployee(employee) ;
                cout <<endl << "New Employee inserted Successfully \n" << employee << endl  ;
                updateLastEmpID(EMP_ID) ;
                break;
            case 2:
                cin >> department ;
                department.setID(to_string(++DEPT_ID)) ;
                addNewDepartment(department) ;
                updateLastDeptID(DEPT_ID) ;
                cout << "\n Department created Successfully\n" << department ;
                break;
            case 3:
                cout << "Enter Employee ID : " << endl ;
                cin >> id ;
                deleteEmployee(id) ;
                break;
            case 4:
                cout << "Enter Department ID : " << endl ;
                cin >> id ;
                deleteDepartment(id ) ;
                break;
            case 5:
                cout << "Enter Employee ID : " << endl ;
                cin >> id ;
                printEmp(id ,employee) ;
                break;
            case 6:
                display_all_Employees() ;
                break;
            case 7:
                cout << "Enter Department ID : " << endl ;
                cin >> id ;
                printDepartment(id , department) ;
                break;
            case 8:
                break;
            case 9:
                write_query(parser) ;
                break;
        }
    } while (choice!=10);

    return EXIT_SUCCESS;
}

void write_query(Parser &parser) {
    if (parser.parse()){

    }else
        cout << "\nQuery Not in right form !!\n" ;
}

void printDepartment(string id , Department& department) {
    Index arr [10] ;

    int size = fillArray(arr , DEPT_P_INDEX) ;
    int pos = BSearch(arr , 0 , size-1 , id) ;
    if (pos==-1)
        cout<<"\nDepartment Not Found\n" ;
    else {
        department.setValues(getDepartment(arr[pos].offset)) ;
        cout << department ;
    }
}

void printEmp(string id , Employee& employee) {
    Index arr [10] ;

    int size = fillArray(arr , EMP_P_INDEX) ;
    int pos = BSearch(arr , 0 , size-1 , id) ;
    if (pos==-1)
        cout<<"\nEmployee Not Found\n" ;
    else {
        employee.setValues(getEmployee(arr[pos].offset)) ;
        cout << employee ;
    }
}

void deleteEmployee(string id) {
    Index arr [10] ;
    int size = fillArray(arr , EMP_P_INDEX) ;
    int pos = BSearch(arr , 0 , size-1 , id) ;
    if (pos==-1)
        cout<<"\nEmployee Not Found\n" ;
    else {
        arr[pos].isActive = false ;
        fstream temp ;
        temp.open(EMP_DATA , ios::app) ;
        temp.seekp(arr[pos].offset+2) ;
        temp.put(DELETE_FLAG) ;
        temp.close() ;
        reWriteFile(arr , size , EMP_P_INDEX) ;
        cout << "\nEmployee with ID : " << arr[pos].id << " deleted successfully \n" ;
    }
}

void deleteDepartment(string id) {
    Index arr [10] ;
    int size = fillArray(arr , DEPT_P_INDEX) ;
    int pos = BSearch(arr , 0 , size-1 , id) ;
    if (pos==-1)
        cout<<"\nEmployee Not Found\n" ;
    else {
        arr[pos].isActive = false ;
        reWriteFile(arr , size , DEPT_P_INDEX) ;
        cout << "\nDepartment with ID : " << arr[pos].id << " deleted successfully \n" ;
    }
}

void addNewDepartment(Department department) {
    fstream data ;
    fstream index ;
    data.open(DEPT_DATA, ios::app) ;
    index.open(DEPT_P_INDEX, ios::app) ;

    data.seekp(0,ios::end) ;
    index.seekp(0 , ios::end) ;

    int offset = data.tellp() ;
    string x = " ";
    x += department.getDeptName();
    x += "|" ;
    x += department.getDeptManager();
    x += "|" ;
    x += department.getDeptId() ;
    x += "|" ;

    string y = " ";
    y+= department.getDeptId() ;
    y+="|" ;
    y += to_string(offset) ;
    y+="\n" ;

    data << x.length() ;
    data << x.data() ;

    index << y.data() ;

    data.close() ;
    index.close() ;
}

int BSearch(Index arr[], int start, int end, string key) {
    int mid  = (start+end) / 2 ;
    int Aid = stoi(arr[mid].id) ;
    int Kid = stoi(key) ;

    if (start>end){
        return -1 ;
    }
    if (Aid == Kid && arr[mid].isActive)
        return mid ;
    else if (Aid > Kid)
        return BSearch(arr , start , mid-1 , key);
    else
        return BSearch(arr , mid+1 , end , key) ;
}
