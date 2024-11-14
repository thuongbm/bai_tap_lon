#include <bits/stdc++.h>
using namespace std;

class work {
public:
    int time;
    string name;
    int priority;
    bool done;
    work *next;

    work(string n, int t, int p, bool d): name(n), time(t), priority(p), done(d), next(nullptr) {}
};

class day_work {
public:
    string day;
    work *w;
    day_work *left;
    day_work *right;

    day_work(string d): day(d), w(nullptr), left(nullptr), right(nullptr) {}
};

class schedule {
private:
    day_work *root;

    day_work *find_day(day_work *root, string &x) {
        if (!root) return nullptr;
        if (root->day == x) return root;
        else if (root->day < x) return find_day(root->right, x);
        return find_day(root->left, x);
    }

    void addwork_inday(day_work* day, string& name, int time, int priority, bool done) {
        work* new_work = new work(name, time, priority, done);
        if (!day->w) {
            day->w = new_work;
        } else {
            work* temp = day->w;
            work* prev = nullptr;
            while (temp && temp->time < time) {
                prev = temp;
                temp = temp->next;
            }
            if (prev) {
                prev->next = new_work;
            } else {
                day->w = new_work;
            }
            new_work->next = temp;
        }
    }

    void viewWorkCompleted(day_work* node) {
        if (node == nullptr) return;
        
        viewWorkCompleted(node->left);
        
        work* temp = node->w;
        while (temp != nullptr) {
            if (temp->done) {
                cout << "- Cong viec: " << temp->name 
                     << ", Gio: " << temp->time 
                     << ", Tinh chat: " << temp->priority 
                     << ", Trang thai: Da hoan thanh" << endl;
            }
            temp = temp->next;
        }
        
        viewWorkCompleted(node->right);
    }

    void unfinishedBusiness(day_work* node){
         if (node == nullptr) return;
        
        unfinishedBusiness(node->left);
        
        work* temp = node->w;
        while (temp != nullptr) {
            if (!temp->done) {
                cout << "- Cong viec: " << temp->name 
                     << ", Gio: " << temp->time 
                     << ", Tinh chat: " << temp->priority 
                     << ", Trang thai: Chua hoan thanh" << endl;
            }
            temp = temp->next;
        }
        
        unfinishedBusiness(node->right);
    }

    void viewBetween (day_work *node, string& start, string& end){
        if (!node) return;

        if (node->day < start) return viewBetween (node->left, start, end);

        if (node->day >= start || node->day <= end) viewDaySchedule(node->day);

        if (node->day > end) return viewBetween(node->right, start, end);
    }

    day_work* minDay(day_work* node){
        day_work* temp = node;
        while (temp != nullptr && temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    }

    day_work* deleteDay(day_work* node, string& date){
        if (!node) return node;
        if (node->day < date) return deleteDay(node->left, date);
        else if(node->day > date) return deleteDay(node->right, date);
        else {
            if (node->left == nullptr){
                day_work *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr){
                day_work *temp = node->left;
                delete node;
                return temp;
            }
            else {
                day_work *temp = minDay(node);
                node->day = temp->day;
                temp->right = deleteDay(temp->right, temp->day); 
            }
        }
        return node;
    }

public:
    schedule(): root(nullptr) {}

    void add_day(string& date) {
        day_work* newday = new day_work(date);
        if (!root) {
            root = newday;
        } else {
            day_work *tmp = root;
            while (true) {
                if (date < tmp->day) {
                    if (tmp->left) {
                        tmp = tmp->left;
                    } else {
                        tmp->left = newday;
                        break;
                    }
                } else if (date > tmp->day) {
                    if (tmp->right) {
                        tmp = tmp->right;
                    } else {
                        tmp->right = newday;
                        break;
                    }
                } else {
                    break;
                }
            }
        }
    }

    void addwork(string& date, int time, string name, int priority, bool done = false) {
        day_work* day = find_day(root, date);
        if (!day) {
            add_day(date);
            day = find_day(root, date);
        }
        addwork_inday(day, name, time, priority, done);
    }

    void viewDaySchedule(const string& date) {
        day_work* dayNode = find_day(root, const_cast<string&>(date));
        if (dayNode) {
            work* temp = dayNode->w;
            cout << "Lich cong tac ngay " << date << ":" << endl;
            while (temp) {
                cout << "- Cong viec: " << temp->name  
                     << ", Gio: " << temp->time  
                     << ", Tinh chat: " << temp->priority  
                     << ", Trang thai: " << (temp->done ? "Da hoan thanh" : "Chua hoan thanh")  
                     << endl;
                temp = temp->next;
            }
        } else {
            cout << "Khong co cong viec nao trong ngay nay." << endl;
        }
    }

    void viewWorkCompleted() {
        cout << "Danh sach cong viec da hoan tat:" << endl;
        viewWorkCompleted(root);
    }

    void unfinishedBusiness() {
        cout << "Danh sach cong viec chua hoan tat:" << endl;
        unfinishedBusiness(root);
    }

    void viewBetween(string& start, string& end){
        cout << "Danh sach cong viec trong khoang thoi gian la " << endl;
        viewBetween(root, start, end);
    }

    void deleteDay(string& date){
        root = deleteDay(root, date);
    }

    void deleteWork(string& date, string& name){
        day_work* dayNode = find_day(root, date);

        if (!dayNode) return;
        cout << "Khong tim thay ngay " << date << " trong lich cong tac" << endl;

        work* current = dayNode->w;
        work* prev = nullptr;

        while (current && current->name != name){
            prev = current;
            current = current->next;
        }

        if (!prev){
            dayNode->w = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        cout << "Da xoa cong viec " << name << " trong ngay " << date << endl;

        if (!dayNode->w){
            deleteDay(date);
        }
    }

    void uppdateWork(string& date, string& name, int newTime = -1, int newPriority = -1, bool newdone = NULL){
        day_work* dayNode = find_day(root, date);
        if (!dayNode){
            cout << "Khong tim thay ngay " << date << " trong lich cong tac" << endl;
            return;
        }

        work *current = dayNode->w;

        while(current && current->name == name){
            current = current->next;
        }

        if (!current){
            cout << "Khong tim thay cong viec " << name << endl;
            return;
        }

        if (newTime != -1) current->name = newTime;
        if (newPriority != -1) current->priority = newPriority;
        if (newdone == NULL) current->done = newdone;

        cout << "Da cap nhat cong viec " << name << " trong ngay " << date << endl; 

        if (newTime != -1){
            work* temp = current->next;
            current->next = nullptr;
            addwork_inday(root, name, current->time, current->priority, current->done);

            work *prev = dayNode->w;
            while (prev && prev->next != current){
                prev = prev->next;
            }
            if (prev) prev->next = temp;
        }    
    }

};

// Menu de lua chon thao tac
void menu() {
    cout << "\n=== LICH CONG TAC ===" << endl;
    cout << "1. Them cong viec" << endl;
    cout << "2. Xem lich cong tac theo ngay" << endl;
    cout << "3. Xem cong viec da hoan tat" << endl;
    cout << "4. Xem cong viec chua hoan tat" << endl;
    cout << "5. Xoa ngay" << endl;
    cout << "6. Xoa cong viec" << endl;
    cout << "7. Cap nhat cong viec" << endl;
    cout << "8. Xem lich cong tac trong khoang thoi gian" << endl; 
    cout << "0. Thoat chuong trinh" << endl;
    cout << "Nhap lua chon: ";
}

// Ham dieu khien chinh cho chuong trinh
void run() {
    schedule schedule;
    int choice;

    do {
        menu();
        cin >> choice;
        cin.ignore();  // Bỏ qua ký tự xuống dòng sau khi nhập số

        if (choice == 1) {
            string date, task_name;
            int start_hour, priority;
            char progress;

            cout << "Nhap ngay (dd-mm-yyyy): ";
            getline(cin, date);

            char continueAdding;
            do {
                cout << "Nhap ten cong viec: ";
                getline(cin, task_name);

                cout << "Nhap gio bat dau: ";
                cin >> start_hour;

                cout << "Nhap tinh chat cong viec: ";
                cin >> priority;
                cin.ignore(); 

                cout << "Cong viec da hoan thanh? (y/n): ";
                cin >> progress;
                cin.ignore();
                bool done = (progress == 'y' || progress == 'Y');

                schedule.addwork(date, start_hour, task_name, priority, done);
                cout << "Cong viec da duoc them vao lich cong tac." << endl;

                cout << "Ban co muon them cong viec khac cho ngay nay khong? (y/n): ";
                cin >> continueAdding;
                cin.ignore();

            } while (continueAdding == 'y' || continueAdding == 'Y');

        } else if (choice == 2) {
            string date;
            cout << "Nhap ngay can xem (dd-mm-yyyy): ";
            cin >> date;
            schedule.viewDaySchedule(date);

        } else if (choice == 3) {
            schedule.viewWorkCompleted();

        } else if (choice == 4) {
            schedule.unfinishedBusiness();

        } else if (choice == 5) {
            string date;
            cout << "Nhap ngay can xoa (dd-mm-yyyy): ";
            cin >> date;
            schedule.deleteDay(date);
            cout << "Da xoa ngay " << date << " khoi lich cong tac." << endl;

        } else if (choice == 6) {
            string date, task_name;
            cout << "Nhap ngay cua cong viec can xoa (dd-mm-yyyy): ";
            cin >> date;
            cin.ignore();

            cout << "Nhap ten cong viec can xoa: ";
            getline(cin, task_name);

            schedule.deleteWork(date, task_name);

        } else if (choice == 7) {
            string date, task_name;
            int new_time = -1, new_priority = -1;
            char new_progress;

            cout << "Nhap ngay cua cong viec can cap nhat (dd-mm-yyyy): ";
            cin >> date;
            cin.ignore();

            cout << "Nhap ten cong viec can cap nhat: ";
            getline(cin, task_name);

            cout << "Nhap gio moi (hoac -1 neu khong doi): ";
            cin >> new_time;

            cout << "Nhap tinh chat moi (hoac -1 neu khong doi): ";
            cin >> new_priority;
            cin.ignore();

            cout << "Cong viec da hoan thanh? (y/n/bo qua): ";
            cin >> new_progress;
            bool new_done = (new_progress == 'y' || new_progress == 'Y');

            schedule.uppdateWork(date, task_name, new_time, new_priority, new_progress != 'b' ? new_done : NULL);

        } else if (choice == 8) {
            string start, end;
            cout << "Nhap ngay bat dau (dd-mm-yyyy): ";
            cin >> start;
            cout << "Nhap ngay ket thuc (dd-mm-yyyy): ";
            cin >> end;
            schedule.viewBetween(start, end);

        } else if (choice == 0) {
            cout << "Thoat chuong trinh." << endl;
        } else {
            cout << "Lua chon khong hop le, vui long thu lai." << endl;
        }
    } while (choice != 0);
}

int main() {
    run();
    return 0;
}
