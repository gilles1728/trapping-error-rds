#include<iostream>
#include<bitset>
using namespace std;
const unsigned long  gen = 0x5B9;
const unsigned int  gdeg = 10;
const unsigned int  mlen = 26;
bool echec = 1  ;
/* d'après http://www.the-art-of-ecc.com/3\_Cyclic\_BCH/RBDS.c */
unsigned long int divise(unsigned long mot, unsigned long ini) {
 unsigned long reg = 0;
 unsigned int i;
 for (i = mlen; i > 0; i--) {
     if ((mot >> (i-1)) & 0x01) reg= (reg <<1) ^ ini ;
     else reg = (reg << 1) ; 
     if  (reg & (0x01 << gdeg))    reg = reg ^ gen;
 }
 return(reg);
}
unsigned long int corrige(unsigned long message) {
  int decale ;
  const unsigned long trap= 0x1f;
  unsigned long prem = 0x31b;//x^9+x^8+x^4+x^3+x+1
  unsigned long reg;//=x^325 mod gen
  reg=divise(message,prem) ;
  for (decale=16 ; decale>=0 ; decale--) {
    reg=divise(reg,1) ;
    if ( (reg & trap) == 0 ) {
      echec  = 0 ; break ;
    } 
    reg=(reg << 1); 
  }
  reg= (reg << decale );
  reg  = message ^ reg  ;
  return(reg) ;
}
int main(void) {
  unsigned long entree,sortie ;
  cout << "Entrer le message, exemple 9726E0" << endl;
  cin >> hex >> entree  ; 
  sortie=corrige(entree);
  if (echec) cout << "pas de piégeage" << endl;
  else {
  cout << "le message estimé  est " << hex << sortie << endl;;
  bitset<26> binaire(sortie);
  cout << binaire << endl;
  }
  return 0;
}
