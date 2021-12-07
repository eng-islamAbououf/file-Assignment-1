#include <string>
using namespace std ;
class Department {

private:
    char dept_id [30];
    char dept_name [50];
    char dept_manager [50];
public:
    static bool searchByID(const string& id){
        return true ;
    }
};
