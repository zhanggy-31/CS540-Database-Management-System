#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

#define block 22
vector<vector<string>> emp();
vector<vector<string>> dept();

int main() {
    vector<vector<string>> emp_vs =emp();
    vector<vector<string>> dept_vs =dept();

    //sort emp_vs
    int emp_size = emp_vs.size();
    int emp_rmd = emp_size % block;
    if(emp_rmd == 0){
        int n = emp_size / block;
        for(int i = 0; i < n; i++){
            sort(emp_vs.begin() + i*(block),emp_vs.begin() + (i+1) * (block),[](const vector<string> & a, const vector<string> & b){
                int x = atoi(a[0].c_str());
                int y = atoi(b[0].c_str());
                return x < y;
            });
        }
    }
    else{
        int n = emp_size / block;
        for(int i = 0; i < n; i++){
            sort(emp_vs.begin() + i*block,emp_vs.begin() + (i+1)*block,[](const vector<string> & a, const vector<string> & b){
                int x = atoi(a[0].c_str());
                int y = atoi(b[0].c_str());
                return x < y;
            });
        }
        sort(emp_vs.begin() + block * n ,emp_vs.end(),[](const vector<string> & a, const vector<string> & b){
            int x = atoi(a[0].c_str());
            int y = atoi(b[0].c_str());
            return x < y;
        });
    }

    //sort dept_vs
    int dept_size = dept_vs.size();
    int dept_rmd = dept_size % block;
    if(dept_rmd == 0){
        int n = dept_size / block;
        for(int i = 0; i < n; i++){
            sort(dept_vs.begin() + i*block,dept_vs.begin() + (i+1)*block,[](const vector<string> & a, const vector<string> & b){
                int x = atoi(a[3].c_str());
                int y = atoi(b[3].c_str());
                return x < y;
            });
        }
    }
    else{
        int n = dept_size / block;
        for(int i = 0; i < n; i++){
            sort(dept_vs.begin() + i*block,dept_vs.begin() + (i+1)*block,[](const vector<string> & a, const vector<string> & b){
                int x = atoi(a[3].c_str());
                int y = atoi(b[3].c_str());
                return x < y;
            });
        }
        sort(dept_vs.begin() + block * n ,dept_vs.end(),[](const vector<string> & a, const vector<string> & b){
            int x = atoi(a[3].c_str());
            int y = atoi(b[3].c_str());
            return x < y;
        });
    }

    //merge emp_vs
    vector<vector<string>> emp_temp;
    if(emp_vs.size()/block > 0){
        int n = emp_size / block;
        for(int i = 0; i < n; i++){
            merge(emp_vs.begin() + i*block,emp_vs.begin() + (i+1)*block,emp_vs.begin() + (i+1)*block, emp_vs.end(),back_inserter(emp_temp), [](const vector<string> & a, const vector<string> & b){
                int x = atoi(a[0].c_str());
                int y = atoi(b[0].c_str());
                return x < y;
            });
        }
    }
    else{
        emp_temp = emp_vs;
    }

    //merge dept_vs
    vector<vector<string>> dept_temp;
    if(dept_vs.size()/block > 0){
        int n = dept_size / block;
        for(int i = 0; i < n; i++){
            merge(dept_vs.begin() + i*block,dept_vs.begin() + (i+1)*block,dept_vs.begin() + (i+1)*block, dept_vs.end(),back_inserter(dept_temp), [](const vector<string> & a, const vector<string> & b){
                int x = atoi(a[0].c_str());
                int y = atoi(b[0].c_str());
                return x < y;
            });
        }
    }
    else{
        dept_temp =dept_vs;
    }

    //join
    vector<vector<string>> result;

    for(int x = 0; x < emp_temp.size(); x++){
        for(int y = 0; y < dept_temp.size(); y++){
            if(emp_temp[x][0] == dept_temp[y][3]){
                emp_temp[x].insert(emp_temp[x].end(), dept_temp[y].begin(), dept_temp[y].end());
                result.push_back(emp_temp[x]);
            }
        }
    }
    ofstream output;
    if(output){
        output.open("join.csv", ios::out);
        for(int i = 0; i < result.size(); i++){
            for(int j = 0; j < result[0].size(); j++){
                output << result[i][j] << ",";
            }
            output << endl;
        }
    }

    return 0;
}

vector<vector<string>> emp(){
    ifstream open_emp;
    vector<vector<string>> emp_vec;
    vector<string> column;
    if(open_emp){
        open_emp.open("Emp.csv", ios::in);
        string line;
        string part;
        while(getline(open_emp, line)){
            column.clear();
            stringstream ss(line);
            while(getline(ss, part, ',')){
                column.push_back(part);
            }
            emp_vec.push_back(column);
        }
    }
    open_emp.close();
    return emp_vec;
}

vector<vector<string>> dept(){
    ifstream open_dept;
    vector<vector<string>> dept_vec;
    vector<string> column;
    if(open_dept){
        open_dept.open("Dept.csv", ios::in);
        string line;
        string part;
        while(getline(open_dept, line)){
            column.clear();
            stringstream ss(line);
            while(getline(ss, part, ',')){
                column.push_back(part);
            }
            dept_vec.push_back(column);
        }
    }
    open_dept.close();
    return dept_vec;
}

