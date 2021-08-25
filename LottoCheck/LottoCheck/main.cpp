#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>

using namespace std;

string str;
vector<int> numbers; // lotto.txt 파일 정보
vector<int> first; // 1등 당첨번호와 보너스 번호
vector<int> myNumber;

void updateNumbers(){ // numbers 벡터에 lotto.txt 정보 가져오기
    ifstream fin("/Users/orijoon98/Desktop/GitHub/LottoCrawling/lotto.txt");
    while(!fin.eof()){
        fin >> str;
        numbers.push_back(stoi(str));
    }
    numbers.pop_back();
    fin.close();
}

void printRecentLotto(){ // 1등 당첨번호, 당첨 금액 출력하기
    cout<<numbers[0]<<"회 당첨번호"<<'\n';
    for(int i=1;i<=6;i++) cout<<numbers[i]<<' ';
    cout<<"+ "<<numbers[7]<<'\n';
    cout<<"1등 당첨 인원 수 : "<<numbers[9]<<'\n';
    cout<<"1등 1인당 당첨 금액 : ";
    for(int i=11;i<=numbers.size()-2;i++){
        cout<<numbers[i]<<",";
    }
    cout<<numbers[numbers.size()-1]<<'\n';
}

void setFirstLotto(){ // 당첨번호 설정하기
    for(int i=1;i<=7;i++) first.push_back(numbers[i]);
}

bool checkMyNumber(){ // 내 번호 제대로 입력했는지 확인
    set<int> s; // 중복 확인
    if(myNumber.size() != 6) return false;
    for(int cur: myNumber){
        if(cur < 1 || cur > 45) return false;
        s.insert(cur);
    }
    if(s.size() != 6) return false;
    return true;
}

int lottoRank(){ // 내 번호에 따른 등수 출력
    int cnt = 0, bonus = 0;
    for(int i=0;i<6;i++){
        for(int j=1;j<=6;j++){
            if(myNumber[i] == numbers[j]){
                cnt++;
                break;
            }
        }
        if(myNumber[i] == numbers[7]) bonus++;
    }
    if(cnt == 6) return 1;
    else if(cnt == 5 && bonus == 1) return 2;
    else if(cnt == 5 && bonus == 0) return 3;
    else if(cnt == 4) return 4;
    else if(cnt == 3) return 5;
    else return 6; // 낙첨
}

void inputYourNumber(){ // 내 번호 결과 확인
    while(true){
        string inputStr, cur = "";
        myNumber.clear();
        bool flag = false;
        cout<<"내 번호 당첨 확인(6개 숫자 입력) or -1 입력시 종료: ";
        getline(cin, inputStr);
        if(inputStr == "-1") break;
        for(int i=0;i<inputStr.size();i++){
            if(inputStr[i] != ' ' && inputStr[i]){
                cur += inputStr[i];
                flag = true;
            }
            else{
                if(flag){
                    myNumber.push_back(stoi(cur));
                    cur = "";
                    flag = false;
                }
            }
            if(i == inputStr.size()-1 && flag) myNumber.push_back(stoi(cur));
        }
        if(checkMyNumber()){ // 번호를 제대로 입력했다면
            if(lottoRank() != 6) cout<<"축하합니다! "<<lottoRank()<<"등 당첨입니다."<<'\n';
            else cout<<"낙첨입니다."<<'\n';
        }
        else cout<<"번호를 잘못 입력했습니다."<<'\n';
    }
}

int main(){
    updateNumbers();
    printRecentLotto();
    setFirstLotto();
    inputYourNumber();
}

/*
 0 : 회차
 1 ~ 6 : 당첨 번호
 7 : 보너스 번호
 9 : 1등 당첨 인원 수
 11 ~ end : 1등 1인당 당첨 금액
*/
