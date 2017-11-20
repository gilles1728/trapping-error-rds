/* d'après https://github.com/bastibl/gr-rds */
#include<iostream>
#include<bitset>
using namespace std;
unsigned int calc_syndrome(unsigned long message) {
 unsigned long reg = 0;
 unsigned int i;
 const unsigned long gen = 0x5B9;//x^10+x^8+x^7+x^5+x^4+x^3+1; 
 const unsigned int gdeg = 10;
 const unsigned int mlen = 26;
 for (i = mlen; i > 0; i--) {
     reg = (reg << 1) | ((message >> (i-1)) & 0x01);
     if  (reg & (0x01 << gdeg))    reg = reg ^ gen;
   }
 return(reg);
}
int main() {
  unsigned long message,sortie ;
  cout << "Entrer le message, exemple 9726E0" << endl;
  cin >> hex >> message  ; 
  sortie=calc_syndrome(message); 
  cout << "le syndrome est "<<  hex << sortie << endl ;
  bitset<10> binaire(sortie); cout << binaire << endl;
  return 0;
}


