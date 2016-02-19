//
//  main.cpp
//  2016_2_21
//
// Assignment: date+n
//

#include <iostream>
using namespace std;

// functions: get/show date
void GetDate(int &m, int &d, int &y);
void GetDateN(int &n);
void ShowDate(int m, int d, int y);

// function: date calculation
bool DayPlusN(int &m, int &d, int &y, int n);
bool DayNo2Date(int n, int &d, int &m, int &y);

int DaysInMonth (int m, int y);
bool DateIsValid(int m, int d, int y);
bool IsLeapYear(int y);
/*
 *
 */
int main() {
    // initialize variable: month, day, year, number of days to add
    int m, d, y;
    int n;
    char ans;
    
    do
    {
        GetDate(m, d, y);
        GetDateN(n);
        ShowDate(m, d, y);
        cout << " + " << n << " days = ";
        
        bool errorCode = DayPlusN(m, d, y, n);
//        bool errorCode = DayNo2Date(n, d, m, y);
        if (!errorCode)
        {
            ShowDate(m, d, y);
        }
        else
        {
            cout << endl << "ERROR: date is invalid." << endl;
        }
        
        cout << endl << "Test again? (Type y for yes or n for no): ";
        cin >> ans;
        cout << endl;
    } while(ans == 'y' || ans == 'Y');
    
    return 0;
}

// GetDate function: user enter date in m/d/y format
void GetDate(int &m, int &d, int &y) {
    char slash;
    cout << "Enter the calendar date in m/d/y format: ";
    cin >> m >> slash >> d >> slash >> y;
}

// GetDateN function: number of days to add
void GetDateN(int &n) {
    cout << "Enter number of days to add: ";
    cin >> n;
}

// ShowDate function: display date
void ShowDate(int m, int d, int y) {
    cout << m << "/" << d << "/" << y;
}

// DayPlusN function
// new_day 는 number of days to add + user entered date
// do loop 에서 총날짜수가 월별날짜수마다 클경우 계속해서 다음달로 옮겨가고 또한 년도도 옮겨갑니다.
// new_day 의 날짜수가 현재 month 날짜수보다 클경우 다음달로 넘어가고 new_day 에서 현재 month 의 날짜를 빼주며 month + 1 합니다.
// month + 1 가 12보타 크면 year + 1 을 하고 month 을 1 으로 setting 합니다.
// do loop 에서 계속계산후 new_day 가 현재 month 보다 날짜수가 적으면 loop 을 빠저나갑니다.
bool DayPlusN(int &m, int &d, int &y, int n) {
    if (!DateIsValid(m, d, y)) {
        return true;
    }
    else {
        int new_day = d + n;
        bool flag;
        
        do
        {
            if(new_day > DaysInMonth(m, y)) {
                new_day -= DaysInMonth(m, y);
                m++;
                flag = true;
            }
            else {
                flag = false;
            }
            
            if (m > 12) {
                y++;
                m = 1;
            }
            
        } while(flag);
        d = new_day;
        
        return false;
    }
}

// DayNo2Date function
// DayPlusN 과 같은 algorithm 이며 input parameters 순서만 틀림
bool DayNo2Date(int n, int &d, int &m, int &y) {
    if (!DateIsValid(m, d, y)) {
        return true;
    }
    else {
        int new_day = d + n;
        bool flag;
        
        do
        {
            flag = false;
            if(new_day > DaysInMonth(m, y)) {
                new_day -= DaysInMonth(m, y);
                m++;
                flag = true;
            }
            
            if (m > 12) {
                y++;
                m = 1;
            }
            
        } while(flag);
        d = new_day;
        
        return false;
    }
}

// DateIsValid function: validate entered month and date
// 유저가 잘못된 date 을 입력할경우 return false
bool DateIsValid(int m, int d, int y) {
    if (d > 0 && d <= DaysInMonth (m, y))
        return true;
    else
        return false;
}

// DaysInMonth function: calculate number of days base on Month user entered
// month: 1, 3, 5, 7, 8, 10, 12 월일경우 날짜수가 31일
// month: 4, 6, 9, 11 월일경우 날짜수가 30일
// month: 2 월일경우 윤달이 있는지 확인 후 윤달이 있을경우 29일 아닐경우 28일
int DaysInMonth (int m, int y) {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
            break;
        case 4: case 6: case 9: case 11:
            return 30;
            break;
        case 2:
            if (IsLeapYear(y))
                return 29;
            else
                return 28;
            break;
        default:
            return 0;
            break;
    }
}

// IsLeapYear function: validate leap year
// user entered year 로 윤달 확인 윤달이 있을경우 return true, 아닐결우 return false
// leap year 계산은 text book 에 나와있는 algorithm 사용하였음
bool IsLeapYear(int y) {
    if (y % 4 == 0) {
        if (y % 100 == 0) {
            if (y % 400 == 0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

