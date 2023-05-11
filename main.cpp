#include "header.h"
#include <regex>
int main(){
    regex bigRealFilter("[-+]?[0-9]+\\.[0-9]+");
    regex bigDecimalFilter("[-+]?[0-9]+");
    BigNumber* num1;
    BigNumber* num2;
    string n1, n2;
    while(true){
        // Deallocate the dynamically allocated memory
        cout << "Number 1 ====> ";
        cin >> n1;
        cout << "Number 2 ====> ";
        cin >> n2;
        if (regex_match(n1, bigRealFilter) && regex_match(n2, bigRealFilter))
        {
            num1 = new BigReal(n1);
            num2 = new BigReal(n2);
            dynamic_cast<BigReal*>(num1);
            dynamic_cast<BigReal*>(num2);
        }
        else if(regex_match(n1, bigDecimalFilter) && regex_match(n2, bigDecimalFilter)){
            num1 = new BigDecimalInt(n1);
            num2 = new BigDecimalInt(n2);
            dynamic_cast<BigDecimalInt*>(num1);
            dynamic_cast<BigDecimalInt*>(num2);
        }
        else{
            cout << "Invalid Input\n";
            continue;
        }
        cout << "What operation do you want to make? ";
        char n;
        cin >> n;
        switch (n)
        {
            case '+':
                cout << "Result is ====> " << *num1 + *num2;
                cout << '\n';
                break;
            case '-':
                cout << "Result is ====> " << *num1 - *num2;
                cout << '\n';
                break;
            case '=':
                cout << ((*num1 == *num2) ? "Input 1 is equal to Input 2" : " Input 1 is not equal to Input 2 ");
                cout << '\n';
                break;
            case '>':
                cout << ((*num1 > *num2) ? "Input 1 is > than Input 2" : " Input 1 is not > than Input 2 ");
                cout << '\n';
                break;
            case '<':
                cout << ((*num1 < *num2) ? "Input 1 is < than Input 2" : " Input 1 is not < than Input 2 ");
                cout << '\n';
                break;
            default:
                cout << "Invalid Input\n";
                break;
        }
        cout << "=========================\n";
    }
    delete num1;
    delete num2;
}


