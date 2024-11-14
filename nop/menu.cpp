#include <bits/stdc++.h>
#include "lop.cpp"
using namespace std;
using ll = long long;
class manage{
public:
	void quanlisinhvien(){
		class_ c;
		fstream fin;
		do{
			cout << "\n1. Nhap sinh vien\n";
			cout << "2. Xuat sinh vien\n";
			cout << "3. Sap xep sinh vien theo diem\n";
			cout << "4. Sinh vien diem cao nhat\n";
			cout << "5. Tim sinh vien\n";
			cout << "6. Xoa sinh vien\n";
			cout << "7. Them sinh vien\n";
			cout << "8. Thoat";
			cout << "\nnhap lua chon cua ban\n";
			int x;
			cin >> x;
			system("cls");
			if (x == 1) {
				fin.open("sv.txt", ios::in);
				fin >> c;
				fin.close();
				
			}
			if (x == 2){
				cout << "\ndanh sach sinh vien\n";
				cout << c;
			}
			if (x == 3){
				c.sort_byscore();
				cout << "\nsap xep sinh vien theo so le la\n";
				c.output_odd_stu();
				cout << "\nsap xep sinh vien theo so chan la\n";
				c.output_even_stu();	
			} 
			if (x == 4){
				cout << "sinh vien diem cao nhat la: ";
				student a = c.max_();
				cout << a << endl;
			}
			if (x == 5){
				cout << "\nnhap ma sinh vien can  tim: ";
				int a;
				cin >> a;
				cout << *c.find(a) << endl;
			}
			if (x == 6){
				cout << "\nnhap ma sinh vien can xoa";
				int a;
				cin >> a;
				c.delete_(a);
			}
			if (x == 7){
			    cout << "\nnhap thong tin sinh vien can them: \n";
			    cin.ignore();
			    string name;
			    getline(cin, name);
			    int stu_num;
			    int age;
			    float score;
			    cin >> stu_num >> age >> score;
			    student s(name, stu_num, age, score);
			    c.push_(s);
			    cout << s;
	//			student s;
	//			cin >> s;
	//			c.push_(s);
			}
			if (x == 8) return ;
		}
		while (1);
		}
};
main(){
	manage m;
	m.quanlisinhvien();
}


