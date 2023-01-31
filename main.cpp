#include "header.h"
int main(){
    regex bigRealFilter("[-+]?[0-9]+\\.[0-9]+");
    regex bigDecimalFilter("[-+]?[0-9]+");
    while(true){
        string n1, n2;
        cout << "Number 1 ====> ";
        cin >> n1;
        cout << "Number 2 ====> ";
        cin >> n2;
        if (regex_match(n1, bigRealFilter) && regex_match(n2, bigRealFilter))
        {
            char n;
            BigReal input1(n1);
            BigReal input2(n2);
            cout << "What Operation do you want to make? ";
            cin >> n;
            switch (n)
            {
                case '+':
                    cout << "Result is ====> " << input1 + input2;
                    cout << '\n';
                    break;
                case '-':
                    cout << "Result is ====> " << input1 - input2;
                    cout << '\n';
                    break;
                case '=':
                    cout << ((input1 == input2) ? "Input 1 is equal to Input 2" : " Input 1 is not equal to Input 2 ");
                    cout << '\n';
                    break;
                case '>':
                    cout << ((input1 > input2) ? "Input 1 is > than Input 2" : " Input 1 is not > than Input 2 ");
                    cout << '\n';
                    break;
                case '<':
                    cout << ((input1 < input2) ? "Input 1 is < than Input 2" : " Input 1 is not < than Input 2 ");
                    cout << '\n';
                    break;
                default:
                    cout << "Invalid Input\n";
                    break;
            }
        }
        else if(regex_match(n1, bigDecimalFilter) && regex_match(n2, bigDecimalFilter)){
            char n;
            BigDecimalInt input1(n1);
            BigDecimalInt input2(n2);
            cout << "What Operation do you want to make? ";
            cin >> n;
            switch (n)
            {
                case '+':
                    cout << "Result is ====> " << input1 + input2;
                    cout << '\n';
                    break;
                case '-':
                    cout << "Result is ====> " << input1 - input2;
                    cout << '\n';
                    break;
                case '=':
                    cout << ((input1 == input2) ? "Input 1 is equal to Input 2" : " Input 1 is not equal to Input 2 ");
                    cout << '\n';
                    break;
                case '>':
                    cout << ((input1 > input2) ? "Input 1 is > than Input 2" : " Input 1 is not > than Input 2 ");
                    cout << '\n';
                    break;
                case '<':
                    cout << ((input1 < input2) ? "Input 1 is < than Input 2" : " Input 1 is not < than Input 2 ");
                    cout << '\n';
                    break;
                default:
                    cout << "Invalid Input\n";
                    break;
            }
        }
        else{
            cout << "Invalid Input\n";
        }
        cout << "=========================\n";
    }


}