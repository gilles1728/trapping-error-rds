#include<iostream>
#include<bitset>
using namespace std;
const unsigned long  gen = 0x5B9;
const unsigned long prem = 0x31b  ; // x^9 + x^8 + x^4 + x^3 + x + 1
const unsigned int  gdeg = 10;//=x^325 mod gen
const unsigned int  mlen = 26;
/* d'après https://github.com/bastibl/gr-rds */
 unsigned int calc_syndrome(unsigned long message)
{
 unsigned long reg = 0;
 unsigned int i;
 for (i = mlen; i > 0; i--)   {
   reg = (reg << 1) | ((message >> (i-1)) & 0x01);
   if  (reg & (0x01 << gdeg))    reg = reg ^ gen;
 }
 return(reg);
}
 unsigned long int synd_mes_premultiplie(unsigned long message)
{
 unsigned long reg = 0;
 unsigned int i;
 for (i = mlen; i > 0; i--) {
     if ((message >> (i-1)) & 0x01) reg= (reg <<1)  ^ prem ;
     else reg = (reg << 1) ; 
     if  (reg & (0x01 << gdeg))    reg = reg ^ gen;
 }
 return(reg);
}
unsigned long int corrige(unsigned long message) {
  int decale ;
  const unsigned long trap= 0x1f;
  unsigned long reg ;
  reg=synd_mes_premultiplie(message);
  for (decale=20 ; decale>=0 ; decale--) {
	reg=(reg << 1);
	reg=calc_syndrome(reg);
	if ( (reg & trap) == 0 ) break ;
  }
     reg= (reg << decale );
     reg= (reg >> 5 );
     reg  = message ^ reg  ;
         return(reg) ;
}
int main() {
  unsigned long entree,sortie ;
  cout << "Entrer le message, exemple 9726E0" << endl;
  cin >> hex >> entree  ; 
  sortie=corrige(entree); 
  cout << "le message décodé  est "<< hex << sortie << endl;;
  bitset<26> binaire(sortie);
  cout << binaire << endl;
  return 0;
}


