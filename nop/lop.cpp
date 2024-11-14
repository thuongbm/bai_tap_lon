#include <bits/stdc++.h>
#include "sinhvien.cpp"
using namespace std;
using ll = long long;
class class_{
private:
	vector <student> s_odd;
	list <student> s_even;
public:
	friend istream& operator >> (istream& in, class_& c);
	friend ostream& operator << (ostream& out, class_& c);
	void push_(student x){
		if (x.get_stu_num() % 2 == 0){
			s_odd.push_back(x);
		}
		else s_even.push_back(x);
	}
	student max_() {
    if (s_odd.empty() && s_even.empty()) {
        return student(); 
    }

    student tmp1, tmp2;

    if (!s_odd.empty()) {
        tmp1 = s_odd[0];
        for (auto x : s_odd) {
            if (x.get_score() > tmp1.get_score()) tmp1 = x;
        }
    }

    if (!s_even.empty()) {
        tmp2 = s_even.front();
        for (auto x : s_even) {
            if (x.get_score() > tmp2.get_score()) tmp2 = x;
        }
    }

    return (tmp1.get_score() > tmp2.get_score()) ? tmp1 : tmp2;
}

	student *find (int x){
		for (auto& a : s_odd){
			if (a.get_stu_num() == x) return &a;
		}
		for (auto& a : s_even){
			if (a.get_stu_num() == x) return &a;
		}
		return nullptr;
	}
	void delete_(int x){
		if (s_odd.empty() && s_even.empty()) return;
		s_odd.erase(remove_if(s_odd.begin(), s_odd.end(), [x](student& s){
			return s.get_stu_num() == x;
		}), s_odd.end());
		s_even.remove_if([x](student& s){
			return s.get_stu_num() == x;
		});
	}
	void sort_byscore(){
		//sx giam dan theo diem
		//sx s_odd
		sort(s_odd.begin(), s_odd.end(), [] (student &s1, student &s2){
			return s1 > s2;
		});
		//sx s_even
		s_even.sort([](student &s1, student &s2){
			return s1 > s2;
		});
	}
	void output_odd_stu(){
		for (auto s : s_odd){
			cout << s << endl;
		}
	}
	void output_even_stu(){
		for (auto s : s_even){
			cout << s << endl;
		}
	}
};
istream& operator >> (istream& in, class_& c){
	int n;
	in >> n;
	in.ignore(1000, '\n');
	for (int i = 0 ; i < n ; i++){
		student s;
		in >> s;
		if (s.get_stu_num() % 2 != 0) c.s_odd.push_back(s);
		else c.s_even.push_back(s);
	}
	return in;
}
ostream& operator << (ostream& out, class_& c){
	cout << endl;
	for (auto s : c.s_odd){
		out << s << endl;
	}
	for (auto s : c.s_even){
		out << s << endl;
	}
	return out;
}



