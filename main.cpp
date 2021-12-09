#include <iostream>
#include <fstream>
#include <cstring>
#include "Employee.h"
using namespace std;

const char DELETE_FLAG = '*';
const char ACTIVE_FLAG = ' ';
const string EMP_P_INDEX = "primary.txt" ;
const string EMP_DATA = "EmployeesData.txt" ;
const string DEPT_P_INDEX = "DeptPrimary.txt" ;
const string DEPT_DATA = "DepartmentData.txt" ;
const string META_DATA = "metaData.txt" ;

struct  Index{
    string id;
    int offset ;
    bool isActive = true ;
};

int BSearch(Index pP[], int start, int end, string key);
void deleteDepartment(string id) ;
void addNewDepartment(Department department);

void deleteEmployee(string id);

void printEmp(string id , Employee& employee);

void printDepartment(string id , Department& department);

void display_all(){
    fstream emp ;
    int size ;
    Employee employee ;
    char *x ;
    emp.open("EmployeesData.txt" , ios::in) ;
    cout<<setw(13)<< "Employee Id";
    cout<<setw(20)<<"Employee Name";
    cout<<setw(20)<<"Employee Position";
    cout<<setw(20)<<"Department ID" << endl ;
    while (emp.good()){
        emp >> size ;
        x = new char [size] ;
        emp.read(x, size) ;
        employee.setValues(x) ;
        if (employee.getIsActive())
            cout << employee ;
    }
    cout << endl ;
    emp.close();
}

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

void addNewEmployee(Employee emp){

    fstream data ;
    fstream index ;
    data.open(EMP_DATA, ios::app) ;
    index.open(EMP_P_INDEX, ios::app) ;

    data.seekp(0,ios::end) ;
    index.seekp(0 , ios::end) ;

    int offset = data.tellp() ;
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
    metaData.open(META_DATA , ios::out) ;
    metaData.seekp(0 , ios::beg) ;
    metaData << "LastID : " << to_string(id) ;
    metaData.close() ;
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

int main()
{


    int choice ;
    Employee employee;
    Department department ;
    string id  ;

    int EMP_ID = getLastEmpID() ;
    int DEPT_ID = getLastDeptID() ;

    do {

        cout<< "Choose the operation to perform"<<endl;
        cout<< "1- add New Employee " <<endl;
        cout<< "2- add New Department " <<endl;
        cout<< "3- Delete Employee (ID) " <<endl;
        cout<< "4- Delete Department (ID) " <<endl;
        cout<< "5- Print Employee (ID) " <<endl;
        cout<< "6- Print Employee (Dept_ID) " <<endl;
        cout<< "7- Print Department (ID) " <<endl;
        cout<< "8- Print Department (Name) " <<endl;
        cout<< "9- Write a Query" <<endl;
        cout<< "10- Exit" <<endl;
        cin>>choice;

        switch (choice) {
            case 1:
                cin>>employee ;
                employee.setDeptID("252624") ;
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

                break;
            case 7:
                cout << "Enter Department ID : " << endl ;
                cin >> id ;
                printDepartment(id , department) ;
                break;
            case 8:
                break;
            case 9:
                break;
        }
//
//
//        if (c==1) {
//        }else if (c==3) {
//            string id;
//            cout << "Enter Emp ID : " << endl;
//            cin >> id;
//            //fill array
//            //empPrimaryIndex.seekg(0, ios::beg);
//            int i = fillArray(arr);
//            int res = BSearch(arr, 0, i - 1, id);
//
//            empPrimaryIndex.seekp(0, ios::beg) ;
//            if (res == -1)
//                cout << "Employee Not Found \n";
//            else {
//                arr[res].isActive = false ;
//                reWriteFile(arr,i) ;
//                reWriteDataFile(arr[res].offset) ;
//            }
//        }else if (c==5){
//
//            string id  ;
//            cout << "Enter Emp ID : " << endl ;
//            cin >> id ;
//
//            //fill array
//            empPrimaryIndex.seekg(0 , ios :: beg) ;
//            int i = fillArray(arr) ;
//            int res = BSearch(arr , 0 , i-1 , id);
//
//            if (res == -1)
//                cout << "Employee Not Found \n" ;
//            else {
//                Index r = arr[res] ;
//                employee.setValues(getEmployee(r.offset, empData));
//                cout << employee << endl;
//            }
//        }else if (c==2){
//            display_all() ;
//        }
    } while (choice!=10);

    return EXIT_SUCCESS;
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
