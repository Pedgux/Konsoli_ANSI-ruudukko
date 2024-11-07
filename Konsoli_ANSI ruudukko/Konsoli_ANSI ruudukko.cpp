#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <unordered_map>

const std::string reset = "\x1b[0m";

const std::unordered_map<int, std::string> v�riMap{
    {0, "\x1b[30m"}, // Musta
    {1, "\x1b[31m"}, // Punane
    {2, "\x1b[32m"}, // Vihri�
    {3, "\x1b[33m"}, // Keltainen
    {4, "\x1b[34m"}, // Sininen
    {5, "\x1b[35m"}, // Magenta???
    {6, "\x1b[36m"}, // Melkeen sininen
    {7, "\x1b[37m"}, // Valkoinen
};

// Funktio joka setuppaa roskat
void alusta() {
  std::cout << "\x1b[?25l"; // Piilottaa konsolin kursorin
  system("cls");            // Tyhjent�� konsolin jos jotai turhaa j��ny
  std::cout << "\x1b[H";    // Siirt�� kursorin vasempaan yl�reunaan
  std::cout << "\x1b[37m";  // Laittaa tekstin v�rin valkoiseksi
  std::cout << "\x1b[40m";  // Laittaa taustan v�rin mustaksi
}

// Luo ruudukon
std::vector<std::vector<int>> luoRuudukko(int& kolumnit, int& rivit, int& arvo) {
  return std::vector<std::vector<int>>(rivit, std::vector<int>(kolumnit, arvo));
}

// Paskoo ruudukon stringiin niin se on tehokkaampaa piirt��, ottaa my�s v�rit huomioon
// ANSI-koodit l�ytyy netist� googlaa ite :3
std::string pakkaaRuudukko(const std::vector<std::vector<int>>& ruudukko,
  const std::unordered_map<int, std::string>& v�riMap) {
  std::string ruutuString; // V�liaikanen variable
  for (const auto& rivi : ruudukko) {
    for (const auto& arvo : rivi) {
      // Hassun hauska juttu googlaa unordered_map::find jos et tii� mit� se tekee
      if (v�riMap.find(arvo) != v�riMap.end()) {
        ruutuString += v�riMap.at(arvo) + std::to_string(arvo);
      }
      else {
        // Jos v�ri� ei l�ydy niin resetoidaan se
        ruutuString += reset;
      }
    }
    ruutuString += "\n";
  }
  ruutuString += reset;
  return ruutuString;
}

// Piirret��s ruudukko stringin� jee
void piirr�Ruudukko(const std::vector<std::vector<int>>& ruudukko,
  const std::unordered_map<int, std::string>& v�riMap) {
  std::cout << "\x1b[H"; // Siirt�� konsolin kursorin vasempaan yl�reunaan, jos se ei ny siell� vittu ollut
  std::string piirrett�v� = pakkaaRuudukko(ruudukko, v�riMap);
  std::cout << piirrett�v�; // Ilmiselv��
  std::cout << "\x1b[H";    // Takasin homo
}

int main() {
  alusta();
  int cols = 50;
  int rows = 30;
  int value = 1;
  auto ruudukko = luoRuudukko(cols, rows, value);
  piirr�Ruudukko(ruudukko, v�riMap);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  ruudukko[20][20] = 2;
  ruudukko[21][20] = 2;
  ruudukko[22][20] = 2;
  piirr�Ruudukko(ruudukko, v�riMap);
}