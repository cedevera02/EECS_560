#ifndef MY_INFIX_CALCULATOR_H
#define MY_INFIX_CALCULATOR_H

#include "myStack_c952d843.h"
#include <vector>
#include <string>

using namespace std;

class myInfixCalculator
{
    public:

    myInfixCalculator() {}
    ~myInfixCalculator() {}

    void tokenize(const std::string & s, std::vector<std::string> &tokens)
    {
        string temp;
        //double num;
        // stringstream ss;
        // ss << s;
        // while (!ss.eof()){
        //     ss >> temp;
        //     if (isNumeric(temp))
        //     {
        //         tokens.push_back(temp);
        //     }else {
        //         if(isOperator(temp))
        //             tokens.push_back(temp);
        //     }
        // }

        for (int i = 0; i < s.length(); i++)
        {
            temp = s[i];
            if (isOperator(temp)){
                tokens.push_back(temp);
            }else{
                if (s[i] != ' '){
                    temp = "";
                    //char t = s[i];
                    std::string lookAhead="";
                    lookAhead.push_back(s[i]);
                    while(!isOperator(lookAhead) && isNumeric(lookAhead)){
                        temp+=s[i];
                        i++;
                        lookAhead="";
                        lookAhead.push_back(s[i]);
                    }
                    i--;
                    tokens.push_back(temp);
                }
            }
        }
    }

    bool isOperator(std::string & s)
    {
        if(s == "/"|s == "("|s == ")"|s == "*"|s == "+"|s == "-")
            return true;
        else
            return false;
    }
    bool isNumeric(std::string & s)
    {
        bool isNum = true;
        int hasDec = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] >= 48 && s[i]<=57)
            {
                isNum=true;
            }else if (s[i]==46){
                if (hasDec == 0){
                    hasDec++;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        return isNum;
    }

    std::string infixToPostfix(const std::string & s)
    {
        std::string temp = "";
        std::string postFix = "";
        vector<string> vect;
        myStack<std::string> stack(10);
        tokenize(s,vect);
        for (int i = 0; i < vect.size(); i++){
            if (isNumeric(vect[i]))
                postFix= postFix + vect[i]+" ";
            else if (isOperator(vect[i])){
                if(stack.empty())
                    stack.push(vect[i]);
                else{
                    temp = stack.top();
                    if (vect[i] == "("){
                        stack.push(vect[i]);
                    }
                    else if (vect[i] == "*"){
                        while (stack.top() == "*" | stack.top() == "/"){
                            postFix= postFix + stack.top() + " ";
                            stack.pop();
                        }
                        stack.push(vect[i]);
                    }else if (vect[i] == "/"){
                        while (stack.top() == "*" | stack.top() == "/"){
                            postFix= postFix + stack.top() + " ";
                            stack.pop();
                        }
                        stack.push(vect[i]);
                    }else if (vect[i] == "+"){
                        while (stack.top() == "+" | stack.top() == "-" | stack.top() == "*" | stack.top() == "/"){
                            postFix= postFix + stack.top() + " ";
                            stack.pop();
                        }
                        stack.push(vect[i]);
                    }else if (vect[i] == "-"){
                        while (stack.top() == "+" | stack.top() == "-"| stack.top() == "*" | stack.top() == "/"){
                            postFix= postFix + stack.top() + " ";
                            stack.pop();
                        }
                        stack.push(vect[i]);
                    }else if (vect[i] == ")"){
                        while (stack.top() != "("){
                            postFix= postFix + stack.top() + " ";
                            stack.pop();
                        }
                        stack.pop();
                    }
                }

            }
        }
        while (!stack.empty()){
            postFix = postFix + stack.top() + " ";
            stack.pop();
        }

        return postFix;
    }

    double calculatePostfix(const std::string & s)
    {
        std::string temp = "";
        vector<string> vect;
        myStack<std::string> stack(10);
        tokenize(s,vect);
        for (int i = 0; i <vect.size(); i++){
            if (isNumeric(vect[i])){
                stack.push(vect[i]);
            }
            else if (isOperator(vect[i])){
                if (vect[i]=="*"){
                    double temp1 = std::stod(stack.top());
                    stack.pop();
                    double temp2 = std::stod(stack.top());
                    stack.pop();
                    stack.push(to_string(temp2*temp1));
                } else if (vect[i]=="/"){
                    double temp1 = std::stod(stack.top());
                    stack.pop();
                    double temp2 = std::stod(stack.top());
                    stack.pop();
                    stack.push(to_string(temp2/temp1));
                } else if (vect[i]=="-"){
                    double temp1 = std::stod(stack.top());
                    stack.pop();
                    double temp2 = std::stod(stack.top());
                    stack.pop();
                    stack.push(to_string(temp2-temp1));
                } else if (vect[i]=="+"){
                    double temp1 = std::stod(stack.top());
                    stack.pop();
                    double temp2 = std::stod(stack.top());
                    stack.pop();
                    stack.push(to_string(temp2+temp1));
                }
            }
        }
        double ans = std::stod(stack.top());
        stack.pop();
        return ans;
    }
};

#endif