#include <iostream>
#include <fstream>
#include <cstring>
#include "Employee.h"
using namespace std;

const char DELETE_FLAG = '*';
const char ACTIVE_FLAG = ' ';

fstream empPrimaryIndex("EmpPrimaryIndex.txt", ios::in | ios::out |ios::app);
fstream empSecondaryIndex("EmpSecondaryIndex.txt", ios::in | ios::out |ios::app);


void addEmpInPrimaryIndex(string id , int offset){
    empPrimaryIndex.seekp(0,ios::end) ;
    id = id + " " + to_string(offset) + '\n';
    empPrimaryIndex.write(id.c_str() , id.size()) ;
}

void addEmployee(Employee emp , fstream& empData ){

    empData.seekp(0,ios::end) ;
    int offset = empData.tellp() ;
    addEmpInPrimaryIndex(emp.getEmployeeId() , offset);

    string x = emp.getEmployeeName() ;
    x += "|" ;
    x += emp.getEmployeeId() ;
    x += "|" ;
    x += emp.getEmployeePosition() ;
    x += "|" ;
    x += emp.getDeptId() ;
    x += "|" ;

    empData << x.length() ;
    empData << x.data() ;
}



string getEmployee(int offset , fstream& empData) {
    empData.seekg(offset , ios::beg) ;
    int size ;
    empData >> size ;
    char x[size] ;
    empData.read(x, size) ;
    return x;
}


int main()
{
    char c ;
    bool b;
    Employee employee;
    static int EMP_ID = 20190000 ;

    fstream empData("EmployeesData.txt", ios::in | ios::out |ios::app);



    if(!empData || !empPrimaryIndex || !empSecondaryIndex)
    {
        cout << "couldn't open file"<<endl;
        system("PAUSE");
        return 0;
    }

    do {
        empData.seekp(0,ios::end);

        cout<< "Choose the operation to perform"<<endl;
        cout<< "V for View" <<endl;
        cout<< "I for insert" <<endl;
        cout<< "D for delete" <<endl;
        cout<< "E for Exit" <<endl;
        cin>>c;

        if (c=='V' || c== 'v') {
            employee.setValues(getEmployee(0 , empData));
            cout << employee << endl;
        }else if (c=='I' || c== 'i') {
            cin>>employee ;
            employee.setDeptID("252624") ;
            employee.setID(to_string(++EMP_ID)) ;
            addEmployee(employee ,empData) ;

            cout <<endl << "New Employee inserted Successfully \n" << employee ;
        }
    } while (c!='E' && c!='e');

    empData.close();
    empPrimaryIndex.close();
    empSecondaryIndex.close() ;

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
