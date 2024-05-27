#include <iostream>

#include <iostream>
using namespace std;
struct node {
    union {
        int number;
        char function;
    };
    int howmanynumbers=0;
    node* next_;
    bool isint;
    explicit node(const int& value) : number(value), next_(nullptr), isint(true) {}
    explicit node(const char& value) : function(value), next_(nullptr), isint(false) {}

};
class stack {
private:
    int counter_ = 0;

public:
    node* top_;
    stack() : top_(nullptr) {}

    bool is_empty() const;
    void push(const int& new_value) {
        node* new_node = new node(new_value);
        new_node->next_ = top_;
        top_ = new_node;
        counter_++;
    }
    void push(const char& new_value) {
        node* new_node = new node(new_value);
        new_node->next_ = top_;
        top_ = new_node;
        counter_++;
    }

    int returnhowmanynumbers() const {
        return top_->howmanynumbers;
    }
    int peekint() const {
        return top_->number;
    };
    char peekchar() const{
        return top_->function;
    }
    void pop();
    void print() const;
    ~stack();

};
stack::~stack() {
    while (!is_empty()) {
        pop();
    }
}


bool stack::is_empty() const {
    return counter_ <= 0;
}



void stack::pop(){
    if (is_empty()) {
        return;
    }
    node* node = top_;
    top_ = top_->next_;
    delete node;
    counter_--;
}

void stack::print() const {
    node* current = top_;

    while (current != nullptr) {
        if (current->isint) cout << current->number << " ";
        else if (current->function == 'I') cout << current->function << "F ";
        else if (current->function == 'N') cout << current->function << " ";
        else if (current->function == 'A') cout << "MAX" << current->howmanynumbers << " ";
        else if (current->function == 'Z') cout << "MIN" << current->howmanynumbers << " ";
        else cout << current->function << " ";
        current = current->next_;
    }
    std::cout << std::endl;
}
int get_priority(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == 'N' || op == 'A' || op == 'Z' || op == 'I')
        return 3;
    return -1; // Dla innych operatorów zwracamy -1 lub możemy obsłużyć błąd.
}

int min(int howmanyoperands,stack& numbers){
    int min=numbers.peekint();
    numbers.pop();
    for (int i = 0; i < howmanyoperands-1; ++i) {
        if(numbers.peekint()<min) min=numbers.peekint();
        numbers.pop();
    }
    return min;
}
int max(int howmanyoperands,stack& numbers){
    int max=numbers.peekint();
    numbers.pop();
    for (int i = 0; i < howmanyoperands-1; ++i) {
        if(numbers.peekint()>max) max=numbers.peekint();
        numbers.pop();
    }
    return max;
}
void do_calculation(char token, stack& numbers,bool &iserror,int howmanyoperands){
    int a, b,c;

    switch (token) {

        case '+':
            cout << "+ ";
            numbers.print();
            a = numbers.peekint();

            numbers.pop();
            b = numbers.peekint();

            numbers.pop();
            numbers.push(a + b);
            break;
        case '-':
            cout << "- ";
            numbers.print();
            a = numbers.peekint();

            numbers.pop();
            b = numbers.peekint();

            numbers.pop();
            numbers.push(b - a);
            break;
        case '*':
            cout << "* ";
            numbers.print();
            a = numbers.peekint();

            numbers.pop();
            b = numbers.peekint();

            numbers.pop();
            numbers.push(a * b);
            break;
        case '/':
            cout << "/ ";
            numbers.print();
            a = numbers.peekint();
            numbers.pop();
            b = numbers.peekint();
            numbers.pop();
            if(a==0){
                iserror=true;
                cout << "ERROR" << endl;
                break;
            }
            else{
                numbers.push(b / a);
                break;
            }
        case 'A':
            cout << "MAX"<< howmanyoperands << " ";
            numbers.print();
            numbers.push(max(howmanyoperands,numbers));
            break;
        case 'Z':
            cout << "MIN"<< howmanyoperands << " ";
            numbers.print();
            numbers.push(min(howmanyoperands,numbers));
            break;
        case 'N':
            cout << "N ";
            numbers.print();
            a = numbers.peekint();
            numbers.pop();
            numbers.push(-a);
            break;
        case 'I':
            cout << "IF ";
            numbers.print();
            a = numbers.peekint();
            numbers.pop();
            b = numbers.peekint();
            numbers.pop();
            c = numbers.peekint();
            numbers.pop();
            if(c>0) numbers.push(b);
            else numbers.push(a);
            break;



    }

}
void reversestack(stack *s, stack& result) {
    stack tmp;
    while (!s->is_empty()) {
        if (s->top_->isint) {
            result.push(s->peekint());
        } else {
            result.push(s->peekchar());
            result.top_->howmanynumbers=s->top_->howmanynumbers;
        }
        s->pop();
    }
}
void functionoperators(stack *output);
void onp_converse(stack& s, stack *output,bool infunction,int licznik){
    char currenttoken;
    bool number_started = false;
    int number=0;
    int liczniknawiasow=0;

    while (std::cin >> currenttoken && currenttoken != '.') {

        if (isdigit(currenttoken)) {

            if (!number_started) {
                number = currenttoken - '0';
                number_started = true;
            }
            else {
                number = number * 10 + (currenttoken - '0');
            }
        }
        else {
            if (number_started) {
                output->push(number);
                number_started = false;

            }

            if (currenttoken == '(') {
                liczniknawiasow++;
                s.push(currenttoken);
            }
            else if (currenttoken == ')') {
                liczniknawiasow--;
                while (!s.is_empty()) {
                    currenttoken = s.peekchar();
                    s.pop();

                    if (currenttoken == '(') break;
                    else {
                        output->push(currenttoken);
                    }
                }
                if(currenttoken == '(' && infunction == true && liczniknawiasow==0){
                    break;
                }

            }
            else if(currenttoken== 'M' || currenttoken == 'I') functionoperators(output);
            else if(currenttoken==',') {
                licznik++;
                while (!s.is_empty()) {
                    currenttoken = s.peekchar();
                    s.pop();

                    if (currenttoken == '(') {
                        s.push(currenttoken);
                        break;
                    }
                    if(currenttoken == ',') {
                        s.push(currenttoken);
                        break;
                    }
                    else {
                            output->push(currenttoken);
                    }
                }
            }
            else {
                    int priority = get_priority(currenttoken);
                    while (!s.is_empty()) {
                        char top = s.peekchar();
                        s.pop();
                        if(currenttoken == 'N' && top == 'N'){
                            s.push(top);
                            break;

                        }

                        else if (top == '(' || get_priority(top) < priority) {
                            s.push(top);
                            break;
                        }
                        output->push(top);


                }
                s.push(currenttoken);
            }

        }
    } ;
    if(number_started) output->push(number);
    while (!s.is_empty()) {
        output->push(s.peekchar());
        s.pop();
    }

   if(infunction) output->top_->howmanynumbers=licznik;
}
void functionoperators(stack *output){
    stack tmp;
    int licznik=1;
    char currenttoken;
    cin>> currenttoken;
    if(currenttoken == 'A'){
        tmp.push(currenttoken);
        cin >> currenttoken;
    }
    else if(currenttoken=='I'){
        tmp.push('Z');
        cin >> currenttoken;
    }
    else if(currenttoken == 'F') tmp.push('I');
    onp_converse(tmp, output, true,licznik);


}
int main(){
    stack s;
    int n;
    cin >> n;
    stack result;
    stack onp;
    stack **output= new stack *[n];
    for (int i = 0; i < n; ++i) {
        output[i] = new stack();
    }
    for (int i = 0; i < n; ++i) {
        bool iserror = false;
        onp_converse(s, output[i], false,0);

        reversestack(output[i], onp);
        onp.print();
        while (!onp.is_empty()&&!iserror){


            if (onp.top_->isint) {
                result.push(onp.peekint());
                onp.pop();
            } else {
                do_calculation(onp.peekchar(), result,iserror,onp.returnhowmanynumbers());
                onp.pop();
            }

        }
        if(!iserror) cout << result.peekint() << endl;
       while (!result.is_empty()) {
            result.pop();
        }
        while (!onp.is_empty()) {
            onp.pop();
        }
        while (!output[i]->is_empty()) {
             output[i]->pop();
        }

    }
    delete[] output;
    return 0;
}
