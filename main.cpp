#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <cmath>
#define START 100
#define END 100000
using namespace std ;
class Currency
{
private:
    string name ;
    float value ;
public:
    Currency(string name_value="" , float Value=0.0){
        set_name(name_value);
        set_value(Value);
    }
    void set_name(string name_value){
        name = name_value ;
    }
    string get_name(){
        return name;
    }
    void set_value(float Value){
        value = Value ;
    }
    float get_value(){
        return value ;
    }
};
class Balance
{
private:
    Currency currency ;
    float amount ;
public:
    Balance(float amount_value=0.0){
        set_amount(amount_value);
    }
    void set_amount(float amount_value){
        amount = amount_value ;
    }
    float get_amount(){
        return amount ;
    }
    void set_currency(Currency currency_value){
        currency = currency_value ;
    }
    Currency get_currency(){
        return currency ;
    }
    
};
class Account
{
    friend class Wallet ;
private:
    vector <Balance> balances ;
    string name ;
    string password ; 
    string hashed_password ;
    int q ; 
    int p ;
    int e ;
    int n ;
    int phi ;
public:
    Account(string name_value="" , string hasshed_password_value="" , int n_value=0 , int e_value=0 , int q_value=0 , int p_value=0){
        set_name(name_value);
        set_password_hash(hasshed_password_value);
        set_e(e_value);
        set_n();
    }
    void set_password(string pass){
        password = pass ;
    }
    void ascii_hashed() {
        /*this fuction used hash_chars and cal ascii code of ech element of hashed_string*/
        int hash_chars[100];
        int i,j ;
        long long int sigma;
        for(i=0 ; i<password.length() ; i++)
            hash_chars[i] = ((3*password[i]+17)%26) + 65 ;
        for(j=0 ; j<16 ; j++){
            sigma = 0 ;
            for(i=0 ; i< password.length() ; i++){
                if(i%16==j%16)
                    sigma += hash_chars[i] ;
            }
            hashed_password += (sigma%26) + 65 ;
        } 
        return ;
    }
    void set_e(int e_value){
        e = e_value ;
    }
    int get_e(){
        return e ;
    }
    void set_n(){
        n = q * p ;
    }
    int get_n(){
        return n ;
    }
    void set_q(){
        q = generate_prime();
    }
    void set_p(){
        p=generate_prime();
    }
    int is_prime(int n) {
    if (n < 2 || (n > 2 && n % 2 == 0)) {
        return 0;
    }
    for (int i = 3; i <= sqrt(n); i+=2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
    }
    int generate_prime() {
        int n = rand() % (END - START + 1) + START;
        if (is_prime(n)) {
            return n;
        } else {
            return generate_prime();
        }
    }
    int Euler_function(){
        /*this fuction cal phi euler(n) with use n*(1-1/p)*(1-1/q)*/
        int ph ;
        ph = n- q - p + 1 ;
        phi = ph ;
    }
    int gcd (int a , int b){
        /*greatest common divisor cal*/
        int i ; 
        for(i=b ; i>=1 ; i--){
            if(b%i==0 && a%i==0)
                return i ;
        }
    }
    int find_public_key (){
        /*e is smaller that gcg(e,phi)==1  */
        int E ;
        for(E=2 ; E<phi ; E++){
            if(gcd(phi , E)==1)
                break;
        }
        e = E;
    }
    int find_private_key (){
    int k , D;
    for(k=1 ; ; k++){
        if((k*phi + 1)%e == 0 ){
            D= (k*phi + 1)/e ;
            break;
        }
    }
    return D ;
    }
    void set_name(string name_value){
        name = name_value ;
    }
    void set_password_hash(string hashed_password_value){
        hashed_password = hashed_password_value ;
    }
    string get_password_hash(){
        return hashed_password ;
    }
    string get_name(){
        return name ;
    }
    vector <Balance> get_balance(){
        return balances ;
    }
    void set_balance(vector <Balance> balance_vector){
        for(int i = 0 ; i<balance_vector.size() ; i++){
            balances.push_back(balance_vector[i]);
        }
    }
    int find_currency (string currency){
        int index = -1 ;
        for(int i =0 ; i<balances.size() ; i++){
            if(balances[i].get_currency().get_name()==currency){
                index = i ;
                break;
            }
        }
        return index ;
    }
    bool WITHDRAW(string currency , float amount){
        int index = find_currency(currency);
        float ex_amount = balances[index].get_amount() ;
        if(ex_amount < amount){
            cout<<"Insufficient Funds: "<<name<<endl ;
            return false ;
        } else{
            balances[index].set_amount(ex_amount - amount) ;
            return true ;
        }
    }
    bool DEPOSIT (string currency , float amount){
        int index = find_currency(currency);
        float ex_amount = balances[index].get_amount() ;
        balances[index].set_amount(ex_amount + amount) ;
        return true ;
    }
};
class Sarafi : public Account
{
private:
    
public:
    Sarafi(string name_value="") :  Account(name_value){

    }
    
};
class Wallet
{
private:
    vector <Account> accounts ;
    vector <Currency > currencys ;
    Sarafi sarafi ;
public:
    Wallet(){
    }
    void menu () {
        int choice ;
        cout << "Menu:\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                sing_in();
                menu() ;
                // Add your register logic here
                break;
            case 2:
                login();
                // Add your login logic here
                break;
            default:
                menu();
                break;
        }
        return ;
    }
    void Add_sarafi(int e , int n , string name , string hashed_pass){
        sarafi.set_name(name);
        sarafi.set_password(hashed_pass);
        sarafi.set_e(e);
        sarafi.set_n();
        vector <Balance> balaces ;
        for(int i = 0 ; i<currencys.size(); i++){
            Balance balance;
            balance.set_currency(currencys[i]);
            balaces.push_back(balance);
        }
        sarafi.set_balance(balaces);
    }
    void Add_currecny(Currency currency_value){
        currencys.push_back(currency_value);
    }
    void Add_Account (int e , int n , string name , string hashed_pass){
        Account account(name , hashed_pass , n , e) ;
        vector <Balance> balaces ;
        Balance balance ;
        for(int i = 0 ; i<currencys.size(); i++){
            balance.set_currency(currencys[i]);
            balaces.push_back(balance);
        }
        account.set_balance(balaces);
        accounts.push_back(account);
    }
    void set_amounts (){
        string file_name ;
        ifstream coin ;
        string name ;
        float amount ;
        int j ;
        for(int i = 0 ; i < currencys.size() ; i++){
            j = 0 ;
            file_name = currencys[i].get_name()+".txt" ; 
            coin.open(file_name , ios::in) ;
            coin>>name>>amount ;
            sarafi.balances[i].set_amount(amount)  ;
            while(coin>>name>>amount){
                accounts[j].balances[i].set_amount(amount);
                j++ ;
            }
            coin.close() ;
        }
    }
    string ascii_hashed(string password) {
        int hash_chars[100];
        int i,j ;
        long long int sigma;
        string hashed_password = "";
        for(i=0 ; i<password.length() ; i++)
            hash_chars[i] = ((3*password[i]+17)%26) + 65 ;
        for(j=0 ; j<16 ; j++){
            sigma = 0 ;
            for(i=0 ; i< password.length() ; i++){
                if(i%16==j%16)
                    sigma += hash_chars[i] ;
            }
            hashed_password += (sigma%26) + 65 ;
        } 
        return hashed_password;
    }
    int find_user (string user){
        int index = -1 ;
        for(int i =0 ; i<accounts.size() ; i++){
            if(accounts[i].get_name()==user){
                index = i ;
                break;
            }
        }
        return index ;
    }
    int find_currency (string currency){
        int index = -1 ;
        for(int i =0 ; i<currencys.size() ; i++){
            if(currencys[i].get_name()==currency){
                index = i ;
                break;
            }
        }
        return index ;
    }
    float cal_wage (string currency){
        int index_jib = find_currency("jibCoin") ;
        int index_coin = find_currency(currency);
        float wage = 10 * currencys[index_jib].get_value()/ currencys[index_coin].get_value() ;
        return wage ;
    }
    bool WITHDRAW(string user , string currency_name , float amount){
        int index = find_user(user) ;
        if(index==-1){
            cout<<"Invalid User: "<<user<<endl ;
            return false ;
        }
        else {
            if(accounts[index].WITHDRAW(currency_name , amount)){
                sarafi.DEPOSIT(currency_name,amount);
                return true ;
            }
            else 
                return false ;
        }
    }
    bool DEPOSIT(string user , string currency_name , float amount){
        int index = find_user(user) ;
        if(index==-1){
            cout<<"Invalid User: "<<user<<endl ;
            return false ;
        }
        else {
            if(sarafi.WITHDRAW(currency_name , amount)){
               accounts[index].DEPOSIT(currency_name , amount) ; 
                return true ;
            }else
                return false ;
        }
    }
    bool TRANSFER(string user1 , string user2 , string currency_name , float amount ){
        int index1 = find_user(user1);
        int index2 = find_user(user2);
        float wage ; 
        if(index1==-1){
            cout<<"Invalid User: "<<user1<<endl ;
            return false ;
        }
        if(index2==-1){
            cout<<"Invalid User: "<<user2<<endl ;
            return false ;
        }
        if(amount<100){
            wage = 0.1 * amount ;
        }
        else{
            wage = cal_wage(currency_name);
        }
        if(accounts[index1].WITHDRAW(currency_name,amount+wage)){
            accounts[index2].DEPOSIT(currency_name,amount);
            sarafi.DEPOSIT(currency_name,wage);
            return true;
        }else   
            return false ;
    }
    bool EXCHANGE(string user , string currency_name1 , string currency_name2 , float amount){
        int index = find_user(user) ;
        int index_coin2 = find_currency(currency_name2);
        int index_coin1 = find_currency(currency_name1);
        float exchange_rate = currencys[index_coin1].get_value()/currencys[index_coin2].get_value() ;
        float wage ;
        if(index==-1){
            cout<<"Invalid User: "<<user<<endl ;
            return false ;
        }
        if(amount<1000){
            wage = amount*0.01 ;
        }
        else {
            wage = cal_wage(currency_name1);
        }
        if(accounts[index].WITHDRAW(currency_name1,amount + wage)){
            if(sarafi.WITHDRAW(currency_name2,amount*exchange_rate)){
                accounts[index].DEPOSIT(currency_name2,amount*exchange_rate);
                sarafi.DEPOSIT(currency_name1,amount+wage);
                return true ;
            }else{
                accounts[index].DEPOSIT(currency_name1,amount+wage) ;
                return false ;
            }
        }else
            return false ;
    } 
    void get_order(string username, bool is_sarafi) {
        string command, currency1, currency2, order="";
        float amount;
        string user1, user2;
        cout << "Enter your command: for exit press 0" << endl;
        getline(cin , order);
        if (order == "0") {
            exit(1);
        }
        stringstream ss(order);
        ss >> command;
        if (command == "DEPOSIT" && is_sarafi) {
            if (ss >> user1 >> currency1 >> amount) {
                if(DEPOSIT(user1, currency1, amount))
                    log_operation(username, order, "success");
                else
                    log_operation(username, order, "failure");
            } else {
                cout << "Invalid Command" << endl;
                log_operation(username, order, "failure");
            }
        } else if (command == "WITHDRAW" && !is_sarafi) {
            if (ss >> currency1 >> amount) {
                if(WITHDRAW(username, currency1, amount))
                    log_operation(username, order, "success");
                else
                    log_operation(username, order, "failure");
            } else {
                cout << "Invalid Command" << endl;
                log_operation(username, order, "failure");
            }
        } else if (command == "EXCHANGE" && !is_sarafi) {
            if (ss >> currency1 >> currency2 >> amount) {
                if(EXCHANGE(username, currency1, currency2, amount))
                    log_operation(username, order, "success");
                else
                    log_operation(username, order, "failure");    
            } else {
                cout << "Invalid Command" << endl;
                log_operation(username, order, "failure");
            }
        } else if (command == "TRANSFER" && !is_sarafi) {
            if (ss >> user2 >> currency1 >> amount) {
                if(TRANSFER(username, user2, currency1, amount))
                    log_operation(username, order, "success");
                else
                    log_operation(username, order, "failure");    
            } else {
                cout << "Invalid Command" << endl;
                log_operation(username, order, "failure");
            }
        } else {
            if(command=="REPORT" && !is_sarafi)
                print_user_transactions(username);
            else {
            cout << "Invalid Command" << endl;
            log_operation(username, order, "failure");
            }
        }
        update_files();
        get_order(username, is_sarafi);
    }
    void print_user_transactions(string username) {
    ifstream log_file("log.txt");
    string line;
    while (getline(log_file, line)) {
        stringstream ss(line);
        string user, operation, status;
        ss >> user >> operation >> status;
        if (user == username) {
            cout << line << endl;
        }
    }
    log_file.close();
    }
    void log_operation(string username, string command, string status) {
    ofstream logFile;
    logFile.open("log.txt", ios::app);
    logFile << username << " " << command << " " << status << endl;
    logFile.close();
}
    void sing_in(){
        string username, password;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].get_name() == username) {
                cout << "This username is already taken. Please try again." << endl;
                sing_in();
            }
        }
        Account new_account(username);
        new_account.set_password(password);
        new_account.ascii_hashed();
        new_account.set_p();
        new_account.set_q();
        new_account.set_n();
        new_account.Euler_function();
        new_account.find_public_key();
        accounts.push_back(new_account);
        cout << "Account successfully created." << endl;
        cout << "Public key: "<<new_account.get_e()<<endl ;
        cout<< "Private key: "<<new_account.find_private_key()<<endl ;
        ofstream users_file("users.txt", ios::app); // open in append mode
        users_file << username << " " << new_account.get_password_hash() <<" "<< new_account.get_e()<< " "<<new_account.get_n() <<endl;
        users_file.close();
        for (int i = 0; i < currencys.size(); i++) {
        string file_name = currencys[i].get_name()+".txt" ;
        ofstream currency_file(file_name, ios::app); // open in append mode
        currency_file << username << " " << 0.0 << endl;
        currency_file.close();
        }
        // Add the new account to the accounts vector
    }
    void login(){
        bool loggedIn = false;
        bool is_sarafi = false ;
        string username, password;
        while (!loggedIn) {
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        ifstream users_file("users.txt");
        string file_username, file_password_hash;
        int file_e, file_n;

        while (users_file >> file_username >> file_password_hash >> file_e >> file_n) {
            if (file_username == username) {
                string hashed_password = ascii_hashed(password);
                
                if (hashed_password == file_password_hash) {
                    cout << "Logged in successfully!" << endl;
                    if(username=="SARAFI")
                        is_sarafi = true ;
                    loggedIn = true;
                    break;
                }
            }
        }
        if (!loggedIn) {
            cout << "Invalid username or password. Please try again." << endl;
            }
        }
        cin.ignore() ;
        get_order(username , is_sarafi);
    }
    void update_files() {
    for (int i = 0; i < currencys.size(); i++) {
        string file_name = currencys[i].get_name()+".txt" ;
        ofstream currency_file(file_name, ios::out); // open in write mode
        currency_file << sarafi.get_name() << " " << sarafi.balances[i].get_amount() << endl;
        for (int j = 0; j < accounts.size(); j++) {
            currency_file << accounts[j].get_name() << " " << accounts[j].balances[i].get_amount() << endl;
        }
        currency_file.close();
    }
}
};

int main(){
    Wallet wallet ;
    ifstream currencys("currencies.txt" , ios::in);
    string currency_name ;
    float value ;
    while(currencys>>currency_name>>value){
        Currency currency(currency_name,value) ;
        wallet.Add_currecny(currency);
    }
    currencys.close();
    ifstream users("users.txt" , ios::in) ;
    int e , n ;
    string hashed_pass , name ;

    users>>name>>hashed_pass>>e>>n ;
    wallet.Add_sarafi(e,n,name,hashed_pass);
    while(users>>name>>hashed_pass>>e>>n){
        wallet.Add_Account(e,n,name,hashed_pass);
    }
    users.close();
    wallet.set_amounts();
    wallet.menu() ;
     return 0 ;
}