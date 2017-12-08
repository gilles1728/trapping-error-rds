/* d'après https://github.com/bastibl/gr-rds */
#include<iostream>
#include<bitset>
using namespace std;
const unsigned long gen = 0x5B9;
//x^10+x^8+x^7+x^5+x^4+x^3+1; 
const unsigned int gdeg = 10;
const unsigned int mlen = 26;
//ini vaudra 1
unsigned long int divise(unsigned long mot, unsigned long ini) {
  unsigned long reg = 0;
  unsigned int i;
 for (i = mlen; i > 0; i--) {
   //on traite les bits non nuls
   if ((mot >> (i-1)) & 0x01) reg= (reg <<1) ^ ini ;
   //multiplication par x  
   else reg = (reg << 1) ;
   //syndrome
   if  (reg & (0x01 << gdeg))    reg = reg ^ gen;
 }
 return(reg);
}
int main(void) {
  unsigned long message,sortie ;
  cout << "Entrer le message, exemple 9726E0" << endl;
  cin >> hex >> message  ; 
  sortie=divise(message,1); 
  cout << "le syndrome est "<<  hex << sortie << endl;
  bitset<10> binaire(sortie); cout << binaire << endl;
  return 0;
}


