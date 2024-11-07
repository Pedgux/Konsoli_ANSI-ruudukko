#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <unordered_map>

const std::string reset = "\x1b[0m";

const std::unordered_map<int, std::string> väriMap{
    {0, "\x1b[30m"}, // Musta
    {1, "\x1b[31m"}, // Punane
    {2, "\x1b[32m"}, // Vihriä
    {3, "\x1b[33m"}, // Keltainen
    {4, "\x1b[34m"}, // Sininen
    {5, "\x1b[35m"}, // Magenta???
    {6, "\x1b[36m"}, // Melkeen sininen
    {7, "\x1b[37m"}, // Valkoinen
};

// Funktio joka setuppaa roskat
void alusta() {
  std::cout << "\x1b[?25l"; // Piilottaa konsolin kursorin
  system("cls");            // Tyhjentää konsolin jos jotai turhaa jääny
  std::cout << "\x1b[H";    // Siirtää kursorin vasempaan yläreunaan
  std::cout << "\x1b[37m";  // Laittaa tekstin värin valkoiseksi
  std::cout << "\x1b[40m";  // Laittaa taustan värin mustaksi
}

// Luo ruudukon
std::vector<std::vector<int>> luoRuudukko(int& kolumnit, int& rivit, int& arvo) {
  return std::vector<std::vector<int>>(rivit, std::vector<int>(kolumnit, arvo));
}

// Paskoo ruudukon stringiin niin se on tehokkaampaa piirtää, ottaa myös värit huomioon
// ANSI-koodit löytyy netistä googlaa ite :3
std::string pakkaaRuudukko(const std::vector<std::vector<int>>& ruudukko,
  const std::unordered_map<int, std::string>& väriMap) {
  std::string ruutuString; // Väliaikanen variable
  for (const auto& rivi : ruudukko) {
    for (const auto& arvo : rivi) {
      // Hassun hauska juttu googlaa unordered_map::find jos et tiiä mitä se tekee
      if (väriMap.find(arvo) != väriMap.end()) {
        ruutuString += väriMap.at(arvo) + std::to_string(arvo);
      }
      else {
        // Jos väriä ei löydy niin resetoidaan se
        ruutuString += reset;
      }
    }
    ruutuString += "\n";
  }
  ruutuString += reset;
  return ruutuString;
}

// Piirretääs ruudukko stringinä jee
void piirräRuudukko(const std::vector<std::vector<int>>& ruudukko,
  const std::unordered_map<int, std::string>& väriMap) {
  std::cout << "\x1b[H"; // Siirtää konsolin kursorin vasempaan yläreunaan, jos se ei ny siellä vittu ollut
  std::string piirrettävä = pakkaaRuudukko(ruudukko, väriMap);
  std::cout << piirrettävä; // Ilmiselvää
  std::cout << "\x1b[H";    // Takasin homo
}

int main() {
  alusta();
  int cols = 50;
  int rows = 30;
  int value = 1;
  auto ruudukko = luoRuudukko(cols, rows, value);
  piirräRuudukko(ruudukko, väriMap);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  ruudukko[20][20] = 2;
  ruudukko[21][20] = 2;
  ruudukko[22][20] = 2;
  piirräRuudukko(ruudukko, väriMap);
}