# OiAK-Projekt </br> Ulepszenia prostych przyborów domowych - Czajnik

|      Wydział elektroniki       |  Kierunek: informatyka techniczna |
|:-------------------------------|------------------------:|
| Grupa zajęciowa: Wt 7:30       | Semestr: 2020/2021 Lato |
| Prowadzący:                    | dr inż. Dominik Żelazny |

| Autorzy         |
|:---------------:|
| Byczko Maciej   |
| Zuzanna Jasińska|

## Wstęp

Nasz projekt ma na celu ulepszenie prostego urządzenia domowego w naszym przypadku czajnika.
Moduły które chcemy zaimplementować:

- Pomiar temperatury
- Uruchamianie za pomocą strony internetowej
- Otrzymywanie powiadomień o wykonanej akcji (Zagotowanie się wody)
- Podświetlenie led zmieniające barwę w zależności od temperatury wody
- Czujnik pojemności czajnika

## Potrzebne elementy

### Podzespoły

- Mikrokontroler, w naszym przypadku esp8266
- Czujnik temperatury (Thermistor)
- Taśma LED wraz z potrzebnymi komponentami (Zasilacz, kontroler)

### Oprogramowanie

Strona internetowa:

- HTML
- CSS
- Framework (Opcjonalny, jeżeli chcemy rozbudować stronę o np. zakładkę z wykresami temperatur potrzebnych do zaparzania herbat, śledzenia ilości wody ugotowanej przez miesiąc użytkowania)

Mikrokontroler:

- język C
- Wstawki z assemblerem za pomocą bloku asm{ }

## Plan działania

- Narysowanie schematu logicznego działania
- Narysowanie schematu elektronicznego
- Uruchomienie esp8266
- Odczytywanie wartości z czujnika
- Podłączenie esp do przekaźnika
- Podłączenie czajnika
- Połączenie z serwerem (stroną internetową)
- Połączenie LEDów
