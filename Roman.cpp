#include "std_lib_facilities.h"
#include "Roman.h"


bool IsValidRoman(string num){
 // Loop through each character in num
 for(char i:num){
    bool check=false;
    // Check if character is a valid Roman numeral
    for (char k : "IVXLCDM" ) {
      if (i==k){
        check=true;
        break;
      }
    }
    // If not a valid Roman numeral, return false
    if (not check){
      return false;
    }
 }
 // If all characters are valid Roman numerals, return true
 return true;
}

string ChangeToRIm(int number){ // меняет число на римское 
  unordered_map<int, string> roman_system;
  roman_system[ 1000 ] = "M" ;
  roman_system[ 900 ] =  "CM" ;
  roman_system[ 500 ] =  "D" ;
  roman_system[ 400 ] =  "CD" ;
  roman_system[ 100 ] =  "C" ;
  roman_system[ 90 ] =  "XC" ;
  roman_system[ 50 ] =  "L" ;
  roman_system[ 40 ] =  "XL" ;
  roman_system[ 10 ] =  "X" ;
  roman_system[ 9 ] =  "IX" ;
  roman_system[ 5 ] =  "V" ;
  roman_system[ 4 ] =  "IV" ;
  roman_system[ 1 ] =  "I" ;
    string ans = "";
    for (int i=1000; i>=1; i-=1){
      for (const auto&[index,value] : roman_system){
        if (i==index){
          while(number>=i){
            ans+=roman_system[i];
            number-=i;
          }
        }
      }
    }
    return ans;
};
int ChangeToInt(string number){
  reverse(number.begin(), number.end());
  int ans=0;
  for (char i : number){

    if (i=='I'){
      if (ans<5){
        ans+=1;
      }
      else if ((ans==5) or (ans==10)){
        ans-=1;  
      }
      else{
        error("Wrong Roman number input");
      }
    }

    if (i == 'V'){ans+=5;}
    
    if(i == 'X'){
      if (ans/10<5){
        ans+=10;
      }
      else if ((ans/10==5) or (ans/10==10)){
        ans-=10;  
      }
      else{
        error("Wrong Roman number input");
      }
    }

    if (i == 'L'){ans+=50;}

    if (i == 'C'){
      if (ans/100<5){
        ans+=100;
      }
      else if ((ans/100==5) or (ans/100==10)){
        ans-=100;  
      }
      else{
        error("Wrong Roman number input");
      }
    }

    if (i == 'D'){ans+=500;}

    if(i == 'M'){ans+=1000;}
  }
  return ans;
};