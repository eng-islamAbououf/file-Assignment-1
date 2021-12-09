#include <iostream>
#include <string>
using namespace std;

class Parser{
private:
    string select_att;
    string where_att ;
    string table_name ;
    string where_att_value;
public:
    bool parse(){
        cout << "Enter Query :" << endl ;
        string x , temp = "" ;

        cin >> x ; // select
        temp = temp + x + " " ;
        cin >> select_att ;

        cin >> x ; // from
        temp = temp + x + " " ;
        cin >> table_name ;

        cin >> x ; // where
        temp = temp + x + " " ;
        cin >> where_att ;

        cin >> x ; // =
        temp = temp + x + " " ;
        cin >> where_att_value ;

        where_att_value = where_att_value.substr(1,where_att_value.length()-2) ;

        if (temp=="select from where = ")
            return true ;
        else
            return false ;
    }

    const string &getSelectAtt() const {
        return select_att;
    }

    void setSelectAtt(const string &selectAtt) {
        select_att = selectAtt;
    }

    const string &getWhereAtt() const {
        return where_att;
    }

    void setWhereAtt(const string &whereAtt) {
        where_att = whereAtt;
    }

    const string &getTableName() const {
        return table_name;
    }

    void setTableName(const string &tableName) {
        table_name = tableName;
    }

    const string &getWhereAttValue() const {
        return where_att_value;
    }

    void setWhereAttValue(const string &whereAttValue) {
        where_att_value = whereAttValue;
    }
};
