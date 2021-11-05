#define _CRT_SECURE_NO_WARNINGS // nhằm né lỗi localtime khi sử dụng
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

class User {
private:
    // Thẻ từ
    string ID; // 14 chữ số
    string PIN; // 6 chữ số

    // Thông tin User
    string Name; // Tên tài khoản
    unsigned long Money; // Số dư tài khoản
    string ISO; // Loại tiền tệ
    bool Khoa = false; // Khóa tài khoản
public:
    stack <string> lsTien; // Lưu lại lịch sử tiền bị biến động
    stack <string> lsLoaiGD; // Lưu lại thông tin thuộc lại giao dịch nào
    stack <string> lsTG; // Lưu lại thời gian thực hiện
    stack <string> lsTD; // Lưu lại thông điệp khi được chuyển khoản
    User() {
        ID = "00000000000000";
        PIN = "123456";
        Name = "Null";
        Money = 0;
        ISO = "VND";
    }
    User(string id, string pin, string name, unsigned long money, string iso) {
        ID = id;
        PIN = pin;
        Name = name;
        Money = money;
        ISO = iso;
    }

    // Phương thức get 
    string getID() { return ID; }
    string getPIN() { return PIN; }
    string getName() { return Name; }
    unsigned long getMoney() { return Money; }
    string getISO() { return ISO; }
    bool getKhoa() { return Khoa; }
    // Phương thức set 
    void setID(string ID) { this->ID = ID; }
    void setPIN(string PIN) { this->PIN = PIN; }
    void setName(string Name) { this->Name = Name; }
    void setMoney(unsigned long Money) { this->Money = Money; }
    void setISO(string ISO) { this->ISO = ISO; }
    void setKhoa(bool Khoa) { this->Khoa = Khoa; }

    friend istream& operator >> (istream& is, User& n) {
        //ifstream in("Test1.txt");
        cout << "ID (14 chu so): ";
        do {
            is >> n.ID;
            if (n.ID.size() != 14) cout << "Do dai ID phai la 14 chu so!!!" << endl;
        } while (n.ID.size() != 14);

        cout << "Ma PIN mac dinh cua ban: 123456" << endl;
        n.setPIN("123456");

        cout << "Ho va ten: ";
        //is.ignore();
        getline(is, n.Name);

        cout << "So tien tao tai khoan: ";
        do {
            is >> n.Money;
            if (n.Money < 0) cout << "Tien tao tai khoan khong the la so am!!!" << endl;
        } while (n.Money < 0);

        cout << "Don vi tien te: ";
        do {
            is >> n.ISO;
            if (n.ISO.size() != 3) cout << "Vui long nhap lai don vi tien te!!!" << endl;
        } while (n.ISO.size() != 3);

        //in.close();
        return is;
    }

    friend ostream& operator << (ostream& ou, User n) {
        //ofstream out("Output.txt");
        ou << "ID:                   \t\t\t" << n.ID << endl;
        ou << "Ten chu tai khoan:    \t\t\t" << n.Name << endl;
        ou << "So du hien co:        \t\t\t" << n.Money << endl;
        ou << "Loai tien te:         \t\t\t" << n.ISO << endl;
        //out.close();
        return ou;
    }
};

// Menu người dùng
void GiaoDich(User& A, char ct, unsigned long tien, string loai, string thongdiep = "") {
    A.lsTien.push(ct + to_string(tien));
    A.lsLoaiGD.push(loai);

    time_t now = time(0);
    tm* ltm = localtime(&now);
    string nam = to_string(1900 + ltm->tm_year);
    string thang = to_string(1 + ltm->tm_mon);
    string ngay = to_string(ltm->tm_mday);
    string gio = to_string(ltm->tm_hour);
    string phut = to_string(ltm->tm_min);
    string giay = to_string(ltm->tm_sec);

    A.lsTG.push(ngay + "/" + thang + "/" + nam + " " + gio + ":" + phut + ":" + giay);
    A.lsTD.push(thongdiep);
}

void XemThongTin(User& A) {
    system("cls");
    // Hiển thị màn hình
    cout << "\t\t\t  <<>> THONG TIN TAI KHOAN <<>> " << endl;
    cout << A;
    system("pause");
    return;
    // Quay lại bảng Menu
}

void NapTien(User& A) {
    system("cls");
    // Hiển thị màn hình
    cout << "\t\t\t  <<>> NAP TIEN <<>> " << endl;
    char tmp;
    string menhgia;
    int soto;
    unsigned long tong = 0;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    do {
        SetConsoleTextAttribute(h, 2);
        cout << "Vui long chon menh gia de nap (bam 0 de thoat ra va huy giao dich):" << endl;
        cout << "(10.000, 20.000, 50.000, 100.000, 200.000, 500.000)VND: ";
        do {
            cin >> menhgia;            
            if (menhgia == "0") {
                cout << "Quay lai Menu" << endl;
                system("pause");
                return;
            }
            if (menhgia != "10000" && menhgia != "20000" && menhgia != "50000" && menhgia != "100000" && menhgia != "200000" && menhgia != "500000") {
                cout << "Ban da chon sai menh gia, vui long nhap lai." << endl;
                cout << "(10.000, 20.000, 50.000, 100.000, 200.000, 500.000)VND: ";
            }
        } while (menhgia != "10000" && menhgia != "20000" && menhgia != "50000" && menhgia != "100000" && menhgia != "200000" && menhgia != "500000");
        
        cout << "Nhap so to (1 - 100): ";
        do {
            cin >> soto;
            if (soto <= 0 || soto >= 101) {
                cout << "Ban da nhap sai so to, vui long nhap lai." << endl;
                cout << "Nhap so to (1 - 100): ";
            }
        } while (soto <= 0 || soto >= 101);
        tong += stoi(menhgia) * soto;

        SetConsoleTextAttribute(h, 13);
        cout << "Da nhan " << tong << " vao he thong ATM." << endl;
        SetConsoleTextAttribute(h, 2);
        cout << "Ban co muon nap them? [Y/N]: ";
        cin >> tmp;
    } while (tmp == 'y' || tmp == 'Y');

    if (tmp == 'n' || tmp == 'N') {
        // cộng tiền vào tài khoản và kết thúc, lưu lại lịch sử giao dịch
        GiaoDich(A, '+', tong, "Nap Tien");
        A.setMoney(A.getMoney() + tong);
        SetConsoleTextAttribute(h, 13);
        cout << "=>> Tong so tien da nap:  \t\t\t" << tong << "VND." << endl;
        cout << "Tong so du hien co:       \t\t\t" << A.getMoney() << "VND." << endl;
        system("pause");
        return;
        // Quay lại bảng Menu
    }
}

void RutTien(User& A) {
    system("cls");
    // Hiển thị màn hình
    cout << "\t\t\t  <<>> RUT TIEN <<>> " << endl;
    char tmp;
    unsigned long rut, tong = 0;
    // Chặn lại nếu tiền dưới mức yêu cầu.
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 13);
    cout << "So du hien co trong tai khoan cua ban: " << A.getMoney() << " VND." << endl;
    do {        
        if (A.getMoney() < 50000) {
            cout << "Ban khong du tien de thuc hien, vui long nap them.";
            system("pause");
            return;
        }
        SetConsoleTextAttribute(h, 2);
        cout << "Vui long chon so tien de rut (>= 50.000 va phai la boi so cua 50)." 
            << endl << "(hoac nhap 0 de quay lai Menu va huy tat ca giao dich) VND: ";
        // thực hiện vòng lặp cho đến khi nhập đúng số tiền có thể rút ra được
        do {
            cin >> rut;
            if (rut == 0) {
                cout << "Quay lai Menu" << endl;
                system("pause");
                return;
            }
            if (rut < 50000 || rut % 50 != 0) cout << "So tien rut phai lon hon hoac bang 50.000 va la boi so cua 50 de rut, vui long nhap lai.";
        } while (rut < 50000 || rut % 50 != 0);
        // số dư ở trong tài khoản không đáp ứng
        if (rut - A.getMoney() < 50000) {
            SetConsoleTextAttribute(h, 13);
            cout << "So du hien tai khong du, vui long nap them." << endl;
            system("pause");
            return;
            // Quay lai bang Menu
        }
        SetConsoleTextAttribute(h, 2);
        tong = tong + rut;
        cout << "Ban co muon rut them? [Y/N]: ";
        cin >> tmp;
    } while (tmp == 'y' || tmp == 'Y');

    if (tmp == 'n' || tmp == 'N') {
        A.setMoney(A.getMoney() - tong);
        // Lưu lại vào lịch sử giao dịch
        GiaoDich(A, '-', tong, "Rut Tien");
        SetConsoleTextAttribute(h, 13);
        cout << "Rut tien thanh cong! Ban vua moi rut: " << tong << "VND." << endl;
        cout << "So du con lai trong tai khoan: " << A.getMoney() << endl;
        system("pause");
        return;
        // Quay lại bảng Menu
    }
}

void XemNoiDungGiaoDich(User A) {
    system("cls");
    // Hiển thị màn hình
    cout << "\t\t\t  <<>> NOI DUNG GIAO DICH <<>> " << endl;
    stack <string> Tien;
    stack <string> LoaiGD;
    stack <string> TG;
    stack <string> TD;
    Tien = A.lsTien;
    LoaiGD = A.lsLoaiGD;
    TG = A.lsTG;
    TD = A.lsTD;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 13);
    if (Tien.empty() && LoaiGD.empty() && TG.empty()) {
        cout << "Tai khoan cua ban chua co thuc hien cuoc giao dich nao trong hom nay." << endl;
        system("pause");
        return;
        // Quay lại bảng Menu
    }
    while (!Tien.empty() && !LoaiGD.empty() && !TG.empty()) {
        cout << "So ID:              \t\t\t" << A.getID() << endl;
        cout << "Ngay giao dich:     \t\t\t" << TG.top() << endl;
        TG.pop();
        cout << "Loai giao dich:    \t\t\t" << LoaiGD.top() << endl;
        LoaiGD.pop();
        cout << "So tien giao dich:  \t\t\t" << Tien.top() << endl;
        Tien.pop();
        cout << "So du hien tai:     \t\t\t" << A.getMoney() << endl;
        if (TD.top() != "")
            cout << "Thong diep:     " << TD.top() << endl;
        TD.pop();
        cout << endl;
    }
    system("pause");
    return;
    // Quay lại bảng Menu
}

void MaPinSao(string& pin) {
    char ast = ' '; // Hỗ trợ việc biến pass thành *
    int aste = 0; // Hỗ trợ việc biến pass thành *
    pin = ""; // reset lại pin mỗi lần nhập sai
    do {
        ast = _getch();
        if (ast == 13 || ast == ' ') { // checking ascii key 13 pressed or no
            break;
        }
        if (ast == 8 || ast == 127) {
            if (pin.size() != 0) {
                cout << "\b \b";
                pin.erase(pin.size() - 1);
                aste--;
            }
        }
        else {
            pin += ast;
            cout << "*";
            aste++;
        }
    } while (ast != 13 || ast != ' ');
}

void DoiMaPin(User& A) {
    system("cls");
    // Hiển thị màn hình
    cout << "\t\t\t  <<>> DOI MA PIN <<>> " << endl;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 13);
    cout << "Ma PIN gom 6 chu so (Nhap 0 de quay lai Menu)." << endl;
    SetConsoleTextAttribute(h, 2);
    cout << "Nhap ma PIN hien tai: ";
    char ast = ' '; // Hỗ trợ việc biến pass thành *
    int aste = 0; // Hỗ trợ việc biến pass thành *
    string pin, pinnew1, pinnew2; // Mã Pin hiện tại, 2 mã pin mới
    do {
        cout << "PIN: ";
        MaPinSao(pin);
        if (pin == "0") {
            cout << "\nQuay lai Menu." << endl;
            system("pause");
            return;
        }
        cout << endl;
        SetConsoleTextAttribute(h, 13);
        if (pin != A.getPIN()) cout << "Ma PIN nhap sai, vui long nhap lai." << endl;
    } while (pin != A.getPIN());

    if (pin == A.getPIN()) {
        do {
            SetConsoleTextAttribute(h, 2);
            cout << "Nhap Ma PIN moi: ";
            do {
                MaPinSao(pinnew1);
                cout << endl;
                if (pinnew1.size() != 6) cout << "Ma PIN phai co 6 chu so, vui long nhap lai: " << endl;
            } while (pinnew1.size() != 6);
            cout << "Xac nhan lai ma PIN moi: ";
            do {
                MaPinSao(pinnew2);
                cout << endl;
                if (pinnew2.size() != 6) cout << "Ma PIN phai co 6 chu so, vui long nhap lai: " << endl;
            } while (pinnew2.size() != 6);

            if (pinnew1 != pinnew2) cout << "Ma PIN moi khong khop nhau, vui long nhap lai ma PIN moi." << endl;
        } while (pinnew1 != pinnew2);

        if (pinnew1 == pinnew2) {
            A.setPIN(pinnew2);
            SetConsoleTextAttribute(h, 13);
            cout << "Doi ma PIN thanh cong!" << endl;
            system("pause");
            return;
            // Quay lại bảng Menu
        }
    }
}

void MenuUser(User A) {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 12);
    cout << "==================== <<>> CTQM BANK <<>> ====================" << endl;
    cout << "\t\t\t  MENU USER" << endl;
    cout << "\t\t\      Xin Chao - Welcome" << endl;
    cout << "\t\t\t  " << A.getName() << endl;
    cout << "=============== Vui long chon loai giao dich ================" << endl;
    cout << "| \t1. Xem thong tin tai khoan  \t\t\t    |" << endl;
    cout << "| \t2. Nap tien                 \t\t\t    |" << endl;
    cout << "| \t3. Rut tien                 \t\t\t    |" << endl;
    cout << "| \t4. Chuyen tien              \t\t\t    |" << endl;
    cout << "| \t5. Xem noi dung giao dich   \t\t\t    |" << endl;
    cout << "| \t6. Doi ma pin               \t\t\t    |" << endl;
    cout << "| \t7. Quay lai sanh            \t\t\t    |" << endl;
    cout << "=============================================================" << endl;
}

struct Node {
    User value;
    Node* next;
};

struct List {
private:
    string user[100]; // 5 tai khoan admin
    string pass[100]; // 5 mat khau admin
public:
    Node* first;
    Node* last;

    List() {
        for (int i = 0; i < 6; i++) {
            user[i] = "admin";
            pass[i] = "admin";
        }
    }
    // Phương thức get
    string getUseri(int i) { return user[i]; }
    string getPassi(int i) { return pass[i]; }
    // Phương thức set
    void setUseri(string user, int i) { this->user[i] = user; }
    void setPassi(string pass, int i) { this->pass[i] = pass; }
};

// Menu Admin
void IntList(List& l) {
    l.first = l.last = NULL;
}

Node* getNode(User c) {
    Node* p = new Node();
    p->value = c;
    p->next = NULL;
    return p;
}

void addCus(List& l, Node* p) {
    if (l.first == NULL) {
        l.first = l.last = p;
    }
    else {
        p->next = l.first;
        l.first = p;
    }
}

void addNode(List& l, Node* p) {
    if (l.first == NULL) {
        l.first = l.last = p;
    }
    else {
        l.last->next = p;
        l.last = p;
    }
}

void XemDanhSachTaiKhoan(List l) {
    system("cls");
    // Hiển thị màn hình
    cout << "\t\t\t  <<>> XEM DANH SACH TAI KHOAN <<>> " << endl;
    Node* p = l.first;
    int dem = 1; // đếm số khách hàng
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    while (p != NULL) {
        SetConsoleTextAttribute(h, 13);
        cout << "Khach hang thu " << dem << ":" << endl;
        cout << p->value;
        cout << "Trang thai tai khoan: \t\t\t";
        if (p->value.getKhoa() == true) {
            SetConsoleTextAttribute(h, 12);
            cout << "Bi khoa" << endl;
        }
        if (p->value.getKhoa() == false) {
            SetConsoleTextAttribute(h, 10);
            cout << "Dang hoat dong" << endl;
        }
        cout << endl;
        p = p->next;
        dem++;
    }
    if (dem == 1) cout << "Hien tai van chua co khach hang." << endl;
    cout << endl;
    system("pause");
    return;
}

void ThemTaiKhoan(List& l) {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    // Hiển thị màn hình
    cout << "\t\t\t  <<>> THEM TAI KHOAN <<>> " << endl;
    SetConsoleTextAttribute(h, 13);
    Node* p = l.first;
    string id, name, iso;
    unsigned long money;
    User tmp;
    cout << "Luu y, ID khong duoc trung (nhap exit de quay lai Menu)." << endl;
    do {
        SetConsoleTextAttribute(h, 2);
        cout << "Nhap ID (14 chu so): ";
        cin >> id;
        SetConsoleTextAttribute(h, 13);
        if (id == "exit" || id == "EXIT") {
            cout << "Quay lai Menu" << endl;
            system("pause");
            return;
        }
        if (id.size() != 14) cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
    } while (id.size() != 14);
    while (p != NULL) {
        if (p->value.getID() == id) {
            do {
                cout << "ID nay da ton tai, vui long nhap ID moi!!" << endl;
                cout << p->value << endl;
                cout << "Hay lay ID khac." << endl;
                do {
                    SetConsoleTextAttribute(h, 2);
                    cout << "Nhap ID (14 chu so): ";
                    cin >> id;
                    SetConsoleTextAttribute(h, 13);
                    if (id == "exit" || id == "EXIT") {
                        cout << "Quay lai Menu" << endl;
                        system("pause");
                        return;
                    }
                    if (id.size() != 14) cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
                } while (id.size() != 14);
            } while (id == p->value.getID());
            break;
        }
        p = p->next;
    }
    cout << "Ma PIN mac dinh cua ban: 123456" << endl;

    cout << "Ho va ten: ";
    cin.ignore();
    getline(cin, name);    

    cout << "So tien tao tai khoan: ";
    do {
        cin >> money;
        if (money < 0) cout << "Tien tao tai khoan khong the la so am!!!" << endl;
    } while (money < 0);

    cout << "Don vi tien te: ";
    do {
        cin >> iso;
        if (iso.size() != 3) cout << "Vui long nhap lai don vi tien te!!!" << endl;
    } while (iso.size() != 3);

    User tmp2(id, "123456", name, money, iso);
    addNode(l, getNode(tmp2));
    cout << "Tao tai khoan thanh cong! Xin chao " << name << endl;
    system("pause");
    return;
}

void DelHead(List& l) {
    if (l.first != NULL) {
        Node* p = l.first;
        l.first = p->next;
    }
}

void DelTail(List& l) {
    Node* p = l.first;
    while (p->next->next != NULL) {
        p = p->next;
    }
    p->next = NULL;
}

void XoaTaiKhoan(List& l) {
    system("cls");
    // Hiển thị màn hình
    cout << "\t\t\t  <<>> XOA TAI KHOAN <<>> " << endl;

    string id; // nhập id cần xóa
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    cout << "Nhap ID tai khoan can xoa (Nhap exit de quay lai Menu)." << endl;
    do {
        SetConsoleTextAttribute(h, 2);
        cout << "ID: ";
        cin >> id;        
        SetConsoleTextAttribute(h, 13);
        if (id == "exit" || id == "EXIT") {
            cout << "Quay lai Menu" << endl;
            system("pause");
            return;
        }
        if (id.size() != 14) cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
    } while (id.size() != 14);
    SetConsoleTextAttribute(h, 13);
    Node* p = l.first;
    
    while (p->next != NULL) {
        if (id == p->next->value.getID()) {
            cout << "Xoa tai khoan thanh cong!" << endl;
            cout << "Da xoa " << p->next->value.getName() << " ra khoi he thong." << endl;
            p->next = p->next->next;
            system("pause");
            return;
        }
        p = p->next;
    }

    SetConsoleTextAttribute(h, 12);
    cout << "Xoa tai khoan that bai, ID can xoa khong ton tai!" << endl;
    system("pause");
    return;
    // Quay lại Menu
}

void MoKhoaTaiKhoan(List& l) {
    system("cls");
    // Hiển thị màn hình
    cout << "\t\t\t  <<>> MO KHOA TAI KHOAN <<>> " << endl;
    string id; // nhập id cần xóa
    int dem = 1;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    Node* p = l.first;
    SetConsoleTextAttribute(h, 10);
    cout << "Nhap ID tai khoan can mo khoa (nhap exit de quay lai Menu)." << endl;
    do {
        SetConsoleTextAttribute(h, 2);
        cout << "ID: ";
        cin >> id;
        SetConsoleTextAttribute(h, 13);
        if (id == "exit" || id == "EXIT") {
            cout << "Quay lai Menu" << endl;
            system("pause");
            return;
        }
        if (id.size() != 14) cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
    } while (id.size() != 14);
    SetConsoleTextAttribute(h, 10);

    while (p->next != NULL) {
        if (id == p->value.getID()) {
            if (p->value.getKhoa() == false) {
                SetConsoleTextAttribute(h, 10);
                cout << "Tai khoan van dang duoc hoat dong binh thuong." << endl;
                system("pause");
                return;
            }
            else {
                p->value.setKhoa(false);
                cout << "Mo khoa tai khoan thanh cong!" << endl;
                system("pause");
                return;
            }
        }
        p = p->next;
    }
    //p = l.first;
    SetConsoleTextAttribute(h, 12);
    cout << "Mo tai khoan that bai, ID can mo khoa khong ton tai!" << endl;
    system("pause");
    return;
    // Quay lại Menu
}

void ChuyenTien(User& A, List& l) {
    system("cls");
    // Hiển thị màn hình
    cout << "\t\t\t  <<>> CHUYEN TIEN <<>> " << endl;
    string id; // nhập id cần chuyển đến
    char tmp;
    unsigned long chuyen;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);

    cout << "Nhap ID tai khoan can chuyen den (nhap exit de quay lai Menu)." << endl;
    do {
        SetConsoleTextAttribute(h, 2);
        cout << "ID: ";
        cin >> id;
        SetConsoleTextAttribute(h, 13);
        if (id == "exit" || id == "EXIT") {
            cout << "Quay lai Menu" << endl;
            system("pause");
            return;
        }
        if (id.size() != 14) cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
    } while (id.size() != 14);

    Node* p = l.first;
    while (p->next != NULL) {
        if (id == p->value.getID()) {
            SetConsoleTextAttribute(h, 13);
            if (p->value.getID() == A.getID()) {
                cout << "Chuyen khoan that bai, ID chuyen tien khong the trung voi ID chuyen toi!" << endl;
                system("pause");
                return;
            }
            else {
                cout << "Da tim thay ID!" << endl;
                cout << "So du hien co trong tai khoan cua ban: " << A.getMoney() << "VND." << endl;
                if (A.getMoney() < 50000) {
                    cout << "Ban khong du tien de thuc hien, vui long nap them." << endl;
                    system("pause");
                    return;
                    // Quay lại màn hình Menu
                }
                SetConsoleTextAttribute(h, 2);
                cout << "Vui long cho so tien de chuyen(>= 50.000 va phai la boi so cua 50)"
                    << endl << "(hoac nhap 0 de quay lai Menu va huy tat ca giao dich) VND: ";
                // thực hiện vòng lặp cho đến khi nhập đúng số tiền có thể rút ra được
                SetConsoleTextAttribute(h, 13);
                do {
                    cin >> chuyen;
                    if (chuyen == 0) {
                        cout << "Quay lai Menu" << endl;
                        system("pause");
                        return;
                    }
                    if (chuyen < 50000 || chuyen % 50 != 0) cout << "So tien phai lon hon hoac bang 50.000 va la boi so cua 50, vui long nhap lai.";
                } while (chuyen < 50000 || chuyen % 50 != 0);
                // số dư ở trong tài khoản không đáp ứng
                if (chuyen - A.getMoney() < 50000) {
                    cout << "So du hien tai khong du, vui long nap them.";
                    system("pause");
                    return;
                    // Quay lai bang Menu
                }
                else {
                    A.setMoney(A.getMoney() - chuyen);
                    p->value.setMoney(p->value.getMoney() + chuyen);
                    // Lưu lại vào lịch sử giao dịch
                    string thongdiep;
                    SetConsoleTextAttribute(h, 2);
                    cout << "Thong diep muon gui: ";
                    cin.ignore();
                    getline(cin, thongdiep);
                    SetConsoleTextAttribute(h, 13);
                    GiaoDich(A, '-', chuyen, "Chuyen Tien toi " + p->value.getName(), thongdiep);
                    GiaoDich(p->value, '+', chuyen, "Nhan tien duoc gui tu " + A.getName(), thongdiep);
                    cout << "Chuyen tien thanh cong! Ban vua moi chuyen: " << chuyen << "VND cho " << p->value.getName() << endl;
                    cout << "So du con lai trong tai khoan: " << A.getMoney() << endl;
                    system("pause");
                    return;
                }
            }
        }
        p = p->next;
    }


    SetConsoleTextAttribute(h, 13);
    cout << "Chuyen khoan that bai, ID can chuyen khong ton tai!" << endl;
    system("pause");
    return;
    // Quay lại bảng Menu

}

Node* DangNhapUser(List& l) {
    string id, pin;
    User tmp;
    int dem = 1; // Đếm số lần đăng nhập thất bại
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    cout << "\t\t\tDANG NHAP USER" << endl;
    do {
        SetConsoleTextAttribute(h, 2);
        cout << "ID: ";
        cin >> id;
        if (id.size() != 14) cout << "ID phai co 14 chu so, vui long nhap lai." << endl;
    } while (id.size() != 14);
    Node* p = l.first;
    while (p != NULL) {
        if (p->value.getID() == id) {
            // ID tồn tại
            if (p->value.getKhoa() == false) {
                SetConsoleTextAttribute(h, 10);
                cout << "Nhap ma PIN dang nhap." << endl;
                do {
                    SetConsoleTextAttribute(h, 2);
                    cout << "PIN: ";
                    MaPinSao(pin);
                    cout << endl;
                    SetConsoleTextAttribute(h, 13);
                    if (dem == 3) {
                        cout << "ID cua ban se bi khoa vi nhap sai ma PIN 3 lan." << endl;
                        p->value.setKhoa(true);
                        system("pause");
                        return NULL;
                        // quay lại menu sảnh
                    }
                    if (pin.size() != 6) {
                        cout << "Ma PIN phai co 6 chu so, vui long nhap lai." << endl;
                        dem++;
                    }
                    else if (p->value.getPIN() != pin) {
                        cout << "Ma PIN sai, vui long nhap lai." << endl;
                        dem++;
                    }
                    else if (p->value.getPIN() == pin) {
                        cout << "Dang nhap thanh cong!" << endl;
                        system("pause");
                        return p;
                        // Xuất ra màn hình menu người dùng
                    }
                } while (pin.size() != 6 || p->value.getPIN() != pin);
            }

            else if (p->value.getKhoa() == true) {
                SetConsoleTextAttribute(h, 13);
                cout << "Tai khoan cua ban dang bi khoa, lien he admin de duoc mo khoa." << endl;
                system("pause");
                return NULL;
                // quay lại menu sảnh
            }
        }
        p = p->next;
    }
    SetConsoleTextAttribute(h, 13);
    cout << "Ma ID khong ton tai." << endl;
    system("pause");
    // quay lại menu sảnh
    return NULL;
}

bool DangNhapAdmin(List l) {
    string user, pass;
    char ast = ' '; // Hỗ trợ việc biến pass thành *
    int aste = 0; // Hỗ trợ việc biến pass thành *
    int dem = 0; // Đếm số lần đăng nhập thất bại
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    cout << "\t\t\tDANG NHAP ADMIN" << endl;
    SetConsoleTextAttribute(h, 2);
    cout << "User: "; cin >> user;
    for (int i = 0; i < 6; i++) {
        if (l.getUseri(i) == user) {
            do {
                if (dem == 3) {
                    SetConsoleTextAttribute(h, 13);
                    cout << "Ban da nhap sai qua qua nhieu lan, vui long thu lai trong giay lat." << endl;
                    system("pause");
                    return false;
                    // Hiện Menu sảnh
                }
                pass = ""; // reset lại pass sau mỗi lần nhập sai

                SetConsoleTextAttribute(h, 2);
                cout << "Pass: ";
                do {
                    ast = _getch();
                    if (ast == 13 || ast == ' ') { // checking ascii key 13 pressed or no
                        break;
                    }
                    if (ast == 8 || ast == 127) {
                        if (pass.size() != 0) {
                            cout << "\b \b";
                            pass.erase(pass.size() - 1);
                            aste--;
                        }
                    }
                    else {
                        pass += ast;
                        cout << "*";
                        aste++;
                    }
                } while (ast != 13 || ast != ' ');
                cout << endl;

                if (l.getPassi(i) == pass) {
                    SetConsoleTextAttribute(h, 13);
                    cout << "Dang nhap Admin thanh cong, xin chao " << user << "." << endl;
                    // Hiện Menu Admin
                    system("pause");
                    return true;
                }

                if (l.getPassi(i) != pass) {
                    SetConsoleTextAttribute(h, 13);
                    cout << "Mat khau nhap sai, vui long nhap lai." << endl;
                    dem++;
                }

            } while (l.getPassi(i) != pass);
        }
    }
    SetConsoleTextAttribute(h, 13);
    cout << "Dang nhap that bai, tai khoan hoac mat khau cua ban nhap sai." << endl;
    //Hiện Menu sảnh
    system("pause");
    return false;
}

void MenuAdmin() {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 12);
    cout << "==================== <<>> CTQM BANK <<>> ====================" << endl;
    cout << "\t\t\t  MENU ADMIN" << endl;
    cout << "=============== Vui long chon loai chuc nang ================" << endl;
    cout << "\t1. Xem danh sach tai khoan   \t\t\t    |" << endl;
    cout << "\t2. Them tai khoan            \t\t\t    |" << endl;
    cout << "\t3. Xoa tai khoan             \t\t\t    |" << endl;
    cout << "\t4. Mo khoa tai khoan         \t\t\t    |" << endl;
    cout << "\t5. Quay lai sanh             \t\t\t    |" << endl;
    cout << "=============================================================" << endl;
}

void MenuSanh() {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11);
    cout << "==================== <<>> CTQM BANK <<>> ====================" << endl;
    cout << "\t\t        Sanh CTQM bank" << endl;
    cout << "================== Ban la Admin hay la User =================" << endl;
    cout << "| \t 1. Dang nhap bang Admin       \t\t\t\    |" << endl;
    cout << "| \t 2. Dang nhap bang User        \t\t\t\    |" << endl;
    cout << "| \t 3. Thoat                      \t\t\t\    |" << endl;
    cout << "=============================================================" << endl;
}

void CapNhatFileTheTu(List l) {
    // Xuất thông tin Thẻ từ ra TheTu.txt
    ofstream out1("TheTu.txt");
    Node* p = l.first;
    while (p != NULL) {
        out1 << p->value.getID() << endl;
        out1 << p->value.getPIN() << endl;
        if (p->value.getKhoa() == false) out1 << "0" << endl; // Không bị khóa
        if (p->value.getKhoa() == true) out1 << "1" << endl; // bị khóa
        p = p->next;
    }
}

void CapNhatFileID(List l) {
    // Xuất thông tin id ra [ID].txt
    ofstream out3("[ID].txt");
    Node* p = l.first;
    while (p != NULL) {
        out3 << p->value.getID() << endl;
        out3 << p->value.getName() << endl;
        out3 << p->value.getMoney() << endl;
        out3 << p->value.getISO() << endl;
        p = p->next;
    }
    out3.close();
}

void CapNhatFileLichSu(List l) {
    // Xuất thông tin giao dịch ra [LichSuID].txt
    ofstream out2("[LichSuID].txt");
    Node* p = l.first;
    while (p != NULL) {
        if (!p->value.lsTien.empty()) {
            stack <string> Tien = p->value.lsTien; // Lưu lại lịch sử tiền bị biến động
            stack <string> LoaiGD = p->value.lsLoaiGD; // Lưu lại thông tin thuộc lại giao dịch nào
            stack <string> TG = p->value.lsTG; // Lưu lại thời gian thực hiện
            stack <string> TD = p->value.lsTD; // Lưu lại thông điệp khi được chuyển khoản
            while (!TG.empty() && !LoaiGD.empty() && !Tien.empty() && !TD.empty()) {
                out2 << p->value.getID() << endl;
                out2 << TG.top() << endl;       TG.pop();
                out2 << LoaiGD.top();           LoaiGD.pop();
                if (TD.top() != "")
                    out2 << " voi thong diep: " << TD.top();   TD.pop();
                out2 << endl;
                out2 << Tien.top() << endl;     Tien.pop();
                //out2 << p->value.getMoney() << endl;
            }
        }
        p = p->next;
    }
    out2.close();
}

int main() {
    // Nhóm CTQM - Mô phỏng cây ATM
    List Admin;

    IntList(Admin);

    // Lấy admin từ Admin.txt
    ifstream in1("Admin.txt");
    int i = 0;
    string user, pass;
    while (in1 >> user) {
        in1 >> user >> pass;
        Admin.setUseri(user, i);
        Admin.setPassi(pass, i);
        i++;
    }
    in1.close();

    // Lấy thông tin từ [ID].txt và thẻ từ TheTu.txt
    ifstream in2("[ID].txt");
    ifstream in3("TheTu.txt");
    string id, name, iso, id2, pin, khoa;
    unsigned long money;
    while (in2 >> id) {
        in2.ignore();
        getline(in2, name);
        in2 >> money;
        in2 >> iso;
        in3 >> id2;
        //if (id2 == id) {
            in3 >> pin;
            in3 >> khoa;
            if (pin == "") pin = "123456";
            User tmp(id, pin, name, money, iso);
            if (khoa == "1") tmp.setKhoa(true);
            if (khoa == "0") tmp.setKhoa(false);
            addCus(Admin, getNode(tmp));
        //}
        //else return 0; // đảm bảo việc file ID và file thẻ từ khớp nhau
    }
    in2.close();
    in3.close();

    // Lấy thông tin từ [LichSuID.txt]
    ifstream in4("[LichSuID].txt");
    while (in4 >> id) {
        string tg, loai, tien, thongdiep="";
        in4.ignore();
        getline(in4, tg);        
        getline(in4, loai);        
        in4 >> tien;
        // lấy lại thông điệp từ loại
        for (int j = 0; j < loai.size(); j++) {
            if (loai[j] == ':') {
                int q;
                for (q = j + 1; q < loai.size(); q++) {
                    thongdiep = thongdiep + loai[q];
                }
                loai.erase(loai.begin() + j, loai.begin() + q); // Xóa dòng thông điệp
                loai.erase(loai.begin() + loai.size() - 15, loai.begin() + loai.size()); // Xóa chữ với thông điệp
                break;
            }
        }
        Node* p = Admin.first;
        while (p != NULL) {
            if (p->value.getID() == id) {
                p->value.lsTG.push(tg);
                p->value.lsLoaiGD.push(loai);
                p->value.lsTien.push(tien);
                p->value.lsTD.push(thongdiep);
            }
            p = p->next;
        }
    }
    in4.close();

    CapNhatFileID(Admin);
    CapNhatFileTheTu(Admin);
    CapNhatFileLichSu(Admin);

    while (true) {
        MenuSanh();
        int tmp;
        string chon;
        bool MenuA = true;
        bool MenuU = true;
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 2);
        do {
            cout << "Vui long chon: ";  cin >> chon;
            if (chon != "1" && chon != "2" && chon != "3") cout << "Ban da chon sai, vui long chon lai." << endl;
        } while (chon != "1" && chon != "2" && chon != "3");
        tmp = stoi(chon);
        switch (tmp) {
        case 1: {
            if (DangNhapAdmin(Admin) == true) {
                do {
                    MenuAdmin();
                    int tmp1;
                    do {
                        cout << "Vui long chon: ";  cin >> chon;
                        if (chon != "1" && chon != "2" && chon != "3" && chon != "4" && chon != "5") cout << "Ban da chon sai, vui long chon lai." << endl;
                    } while (chon != "1" && chon != "2" && chon != "3" && chon != "4" && chon != "5");
                    tmp1 = stoi(chon);
                    switch (tmp1) {
                    case 1: {
                        XemDanhSachTaiKhoan(Admin);
                        break;
                    }
                    case 2: {
                        ThemTaiKhoan(Admin);
                        CapNhatFileID(Admin);
                        CapNhatFileTheTu(Admin);
                        break;
                    }
                    case 3: {
                        XoaTaiKhoan(Admin);
                        CapNhatFileID(Admin);
                        CapNhatFileTheTu(Admin);
                        break;
                    }
                    case 4: {
                        MoKhoaTaiKhoan(Admin);
                        CapNhatFileID(Admin);
                        CapNhatFileTheTu(Admin);
                        
                        break;
                    }
                    case 5: {
                        MenuA = false;
                        break;
                    }
                    }
                } while (MenuA == true);
            }
            break;
        }
        case 2: {
            Node* p = DangNhapUser(Admin);
            CapNhatFileTheTu(Admin); // cập nhật lại khóa nếu nhập sai 3 lần
            CapNhatFileID(Admin);
            if (p != NULL) {
                do {
                    MenuUser(p->value);
                    int tmp2;
                    do {
                        cout << "Vui long chon: ";  cin >> chon;
                        if (chon != "1" && chon != "2" && chon != "3" && chon != "4" && chon != "5" && chon != "6" && chon != "7") cout << "Ban da chon sai, vui long chon lai." << endl;
                    } while (chon != "1" && chon != "2" && chon != "3" && chon != "4" && chon != "5" && chon != "6" && chon != "7");
                    tmp2 = stoi(chon);
                    switch (tmp2) {
                    case 1: {
                        XemThongTin(p->value);
                        break;
                    }
                    case 2: {
                        NapTien(p->value);
                        CapNhatFileID(Admin);
                        CapNhatFileTheTu(Admin);
                        CapNhatFileLichSu(Admin);
                        break;
                    }
                    case 3: {
                        RutTien(p->value);
                        CapNhatFileID(Admin);
                        CapNhatFileTheTu(Admin);
                        CapNhatFileLichSu(Admin);
                        break;
                    }
                    case 4: {
                        ChuyenTien(p->value, Admin);
                        CapNhatFileID(Admin);
                        CapNhatFileTheTu(Admin);
                        CapNhatFileLichSu(Admin);
                        break;
                    }
                    case 5: {
                        XemNoiDungGiaoDich(p->value);
                        break;
                    }
                    case 6: {
                        DoiMaPin(p->value);
                        CapNhatFileID(Admin);
                        CapNhatFileTheTu(Admin);
                        break;
                    }
                    case 7: {
                        MenuU = false;
                        break;
                    }
                    }
                } while (MenuU == true);
            }
            break;
        }
        case 3: {
            return 0;
        }
        }
    }

    return 0;
}