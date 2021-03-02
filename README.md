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
- Uruchamianie za pomocą aplikacji
- Otrzymywanie powiadomień o wykonanej akcji (Zagotowanie się wody)
- Podświetlenie led zmieniające barwę w zależności od temperatury wody
- Czujnik pojemności czajnika
- Moduł obliczający zużycie energii i na tej podstawie ustalenie czy czajnik należy już odkamienić

## Potrzebne elementy

### Podzespoły
- Mikrokontroler (Arduino z modułem wifi)
- Czujnik temperatury
- Taśma LED wraz z potrzebnymi komponentami (Zasilacz, kontroler)

### Oprogramowanie
Można albo napisać aplikację jak w store na telefony wtedy:
- Android studio?


lecz można zrobić stronę internetową wtedy:
- HTML
- CSS
- Framework (Opcjonalny, jeżeli chcemy rozbudować stronę o np. zakładkę z wykresami temperatur potrzebnych do zaparzania herbat, śledzenia ilości wody ugotowanej przez miesiąc użytkowania)

Potrzebny będzie serwer do komunikacji z czajnikiem, VPS, raspberry lub AWS
