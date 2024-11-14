#include <bits/stdc++.h>
using namespace std;
using ll = long long;
class student{
private:
	string name;
	int stu_num;
	int age;
	float score;
public:
	friend istream& operator >> (istream& in, student& s);
	friend ostream& operator << (ostream& out, student& s);
	
	student operator + (student s); 
	student(){
		name = "";
		stu_num = 0;
		age = 0;
		score = 0;
	}
	
	student(string name, int stu_num, int age, float score) {
        this->name = name;
        this->stu_num = stu_num;
        this->age = age;
        this->score = score;
	}
	
	friend bool operator > (student s1, student s2){
		return s1.score > s2.score;
	}
	
	int get_stu_num(){
		return stu_num;
	}
	
	float get_score(){
		return score;
	}
	
};
istream& operator>>(istream& in, student& s) {
    getline(in, s.name);
    in >> s.stu_num >> s.age >> s.score;
    in.ignore(1000, '\n'); 
    return in;
}
ostream& operator << (ostream& out, student& s){
	out << s.name << ' ' << s.stu_num << ' ' << s.age << ' ' << s.score << endl;
	return out;
}
student student::operator + (student s){
	student temp = *this;
	temp.score = this->score + s.score;
	return temp;
}


