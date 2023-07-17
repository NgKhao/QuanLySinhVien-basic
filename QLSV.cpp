#include<iostream>
#include<string.h>
#include<sstream>
#include<fstream> 
#include<iomanip>
#include<vector>
#include<algorithm> 
using namespace std;
struct sv{
	string ma, ten, lop, ns;
	double gpa;
	
	void nhap(){
		cout<<"Nhap ma sinh vien: " ;
		cin >> ma;  
		cout<<"Nhap ten sinh vien:";
		cin.ignore();
		getline(cin, ten);
		cout<<"Nhap lop: ";
		cin >> lop;
		cout<<"nhap ngay sinh: ";
		cin >> ns;
		cout<<"nhap GPA: ";
		cin >> gpa;
	}
};
void inds( sv a[], int n){
	cout<< setw(17) << left <<"Ma sinh vien";
	cout<< setw(30) << left <<"Ten sinh vien";
	cout<< setw(10) << left <<"Lop";
	cout<< setw(20) << left <<"Ngay sinh";
	cout<< setw(4)  << right<<"GPA" << endl ;
	cout<< setfill('-');
	cout<< setw(81) << "-" << endl;
	cout<< setfill(' ');
	for(int i=0; i<n; i++){
		cout<< setw(17) << left <<a[i].ma;
		cout<< setw(30) << left <<a[i].ten;
		cout<< setw(10) << left <<a[i].lop;
		cout<< setw(20) << left <<a[i].ns;
		cout<< setw(4)  << right<< fixed << setprecision(2)<< a[i].gpa << endl;	
	}
}


void tkma( sv a[], int n){
	sv arrFound[n];
	int found=0;
	string ma;
	cout<<"Nhap ma sinh vien can tim: "; cin>>ma;
	bool flag = false;
	for(int i=0; i<n; i++){
		if(a[i].ma.find(ma) != string::npos){//npos: gt lon nhat cua size_t
			arrFound[found]=a[i];
			++found;
			flag = true;		
		}			
	}
	inds( arrFound, found);
	if( !flag){
		cout<<"Khong tim thay sinh vien co ma vua nhap\n";
	}
}

//danh sach sinh co GPA max
void lkgpa( sv a[], int n ){
	sv arrFound[n];
	int found=0;
	double res = 0;
	for(int i=0; i<n; i++){
		if(a[i].gpa > res) res = a[i].gpa;
	}
	cout << "Danh sach sinh vien co diem gpa cao nhat: \n";
	for(int i=0; i<n; i++){
		if( res == a[i].gpa ){
			arrFound[found]=a[i];
			++found;
		}
	}
	inds( arrFound, found);
}

// danh sach sinh vien co gpa >= 2.5
bool cmp(sv a, sv b){
	// kieu cmp la xap xep dua tren tieu chi gi do;
	return a.gpa > b.gpa;
}
void sxgpa( sv a[], int n){
	// sx roi loc >=2.5 hoac nguoc lai
	sv arrFound[n];
	int found=0;
	for(int i=0;i<n;i++){
		if(a[i].gpa >= 2.5){
			arrFound[found]=a[i];
			++found;
		}
	}
	sort(arrFound, arrFound+found,cmp); // vi da ++found nen found+1
	cout<< "Danh sach sinh vien co diem >= 2.5: \n";
	inds( arrFound, found);
}
// sap xep ten
//tach ra bo vao vector r dung cmp 
//vi co truong hop db
// nguyen van a
// hoang thi ab
// neu dung cach cu thi ab se dung truoc a
vector<string> chuanHoa( sv a ){
	stringstream ss(a.ten);
	vector<string>v;
	string tmp;
	while( ss >> tmp){
		v.push_back(tmp);
	}
	return v;
}
bool cmp2(sv a, sv b){
	vector<string> ten1 = chuanHoa(a);
	vector<string> ten2 = chuanHoa(b);
	if (ten1.back() != ten2.back()) return ten1.back() < ten2.back();
	for (int i=0; i<min(ten1.size(),ten2.size()); i++){
		if(ten1[i] != ten2[i]) return ten1[i] < ten2[i];
	}
	return ten1.size() < ten2.size();
}
void sxten (sv a[], int n){
	sort(a, a+n, cmp2);
}

//sap xep sinh vien theo lop, cung lop xep theo ten
bool cmp3( sv a, sv b){
	if( a.lop != b.lop) return a.lop < b.lop;
	vector<string> ten1 = chuanHoa(a);
	vector<string> ten2 = chuanHoa(b);
	if (ten1.back() != ten2.back()) return ten1.back() < ten2.back();
	for (int i=0; i<min(ten1.size(),ten2.size()); i++){
		if(ten1[i] != ten2[i]) return ten1[i] < ten2[i];
	}
	return ten1.size() < ten2.size();
}
void sxlop( sv a[], int n){
	sort (a, a+n, cmp3);
}

//sap xep sinh vien theo lop, cung lop xep theo gpa
bool cmp4( sv a, sv b){
	if( a.lop != b.lop) return a.lop < b.lop;
	return a.gpa > b.gpa;
}
void sxlop2( sv a[], int n){
	sort (a, a+n, cmp4);
}
int main(){
	sv a[1000];
	int n=0;
	while(1){
		cout << "----------------------MENU----------------------------------------------\n";
		cout << "-- 1. Nhap thong tin sinh vien                                        --\n";
		cout << "-- 2. Hien thi toan bo danh sach sinh vien                            --\n";
		cout << "-- 3. Tim kiem sinh vien theo ma                                      --\n";
		cout << "-- 4. Liet ke sinh vien co GPA cao nhat                               --\n";
		cout << "-- 5. Liet ke sinh vien cos GPA >= 2.5                                --\n";
		cout << "-- 6. Sap xep sinh vien theo ten                                      --\n";                                  
		cout << "-- 7. Sap xep sinh vien theo lop, cung lop xep theo ten               --\n";           
		cout << "-- 8. Sap xep sinh vien theo lop theo, cung lop xep theo GPA giam dan --\n";
		cout << "-- 0. Thoat                                                           --\n";
		cout << "------------------------------------------------------------------------\n";
		cout << "Nhap lua chon: "; int lc; cin>>lc;
		if (lc == 1){
			a[n].nhap();
			++n;
		}
		else if (lc == 2){
			inds(a,n);
		}
		else if (lc == 3){
			tkma(a,n);
		}
		else if (lc == 4){
			lkgpa(a,n);
		}
		else if (lc == 5){
			sxgpa(a,n);
		}
		else if (lc == 6){
			sxten(a,n);
			inds(a,n);
		}
		else if (lc == 7){
			sxlop(a,n);
			inds(a,n);
		}
		else if (lc ==8){
			sxlop2(a,n);
			inds(a,n);
		}
		else if (lc == 0){
			break;
		}
	}
	return 0;
}
