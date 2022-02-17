# Descriere
Topicul temei este jocul “Among us”. Pentru această temă se cere o implementare simplificată a unui model asemănător cu jocul cunoscut.

Pentru implementarea temei trebuie înțelese următoarele 3 structuri prezente în “utils.h”:

Location:
- x – întreg care reprezintă coordonata x a poziției
- y – întreg care reprezintă coordonata y a poziției

Game:
- name – șir de caractere care reprezintă numele jocului curent
- killRange – întreg care reprezintă distanța maximă de la care un Impostor poate să omoare un alt jucător
numberOfCrewmates – întreg care reprezintă numărul de colegi de echipaj
- crewmates – vector de referințe la structuri de tip Player care reprezintă colegii de echipaj
- impostor – referința la structura de tip Player care reprezintă impostorul din joc

Player:
- name – șir de caractere care reprezintă numele jucătorului
- color – șir de caractere care reprezintă culoarea jucătorului
- hat – șir de caractere care reprezintă pălăria jucătorului
- alive – întreg care reprezintă dacă jucătorul este în viață sau nu
- indexOfLocation – indicele din vectorul de locații care reprezintă locația curentă a jucătorului
- numberOfLocations – numărul de locații în care se poate afla jucătorul
- locations – vector de structuri de tip Location
- playerRole – enum de tip PlayerRoles care reprezintă tipul de jucător
- ability – referință la funcție de tipul void * task(void *) care reprezintă task-ul jucătorului curent

Rolurile jucătorilor sunt salvate în enum-ul playerRole. Valorile din enum sunt:
- Rotator
- Decoder
- Invertor
- Impostor

Task-urile pe care jucătorii trebuie să le facă sunt salvate în vectorul de referințe la funcții: 
```
void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};.
```
Valorile din playerRole corespund indicilor din vectorul de referințe la funcții.

Jocul constă în prezența unei structuri de tip Game în care sunt prezente setările jocului, vectorul de colegi de echipaj si impostorul. Fiecare jucător, inclusiv impostorul, este o structura de tipul Player si are date despre numele, culoarea si pălăria sa. Acesta mai conține si dacă jucătorul este sau nu în viață și traseul lui în joc (un vector de structuri de tip Location, un număr de locații pentru acel jucător care reprezintă lungimea vectorului de locații și un indice care reprezintă locația din vector în care se afla jucătorul acum). Pe lângă acestea, un jucător mai are un rol (Rotator, Decoder, Invertor sau Impostor) care îi definește rolul lui în joc și, prin urmare task-ul pe care îl are de făcut. Task-ul lui este salvat ca o referință la o funcție.

Fiecare jucător se mișcă circular prin vectorul de locații. Dacă un jucător are 3 locații, în următoarele 5 cicluri de joc se va mișca astfel:
```
0 -> 1 -> 2 -> 0 -> 1-> 2
```
Jocul se desfășoară în modul următor:

- se citește de la input un joc si jucătorii lui
- se inițializează jucătorii lui și se afișează datele importante despre joc la output
- se calculează ciclurile jocului(rundele)

Jocul se desfășoară pe cicluri(runde). Un ciclu este reprezentat de următoarele acțiuni:

- fiecare coleg de echipaj se mișcă la următoarea sa locație din vectorul de locații (jucătorii încep de la locația cu indicele 0 din vector și în primul ciclu se duc la locația 1 si așa mai departe)
- fiecare coleg de echipaj își face task-ul, apelând câmpul ability, care este o referința la o funcție, apoi își afișează rezultatul task-ului său
- urmează rândul impostorului să se miște la următoarea sa locație și să își facă task-ul adică să încerce să omoare un jucător

# Rulare
## Task 1
Funcția primește un void * care este un pointer la un int (n). Să se creeze o matrice n*n cu elementele de forma ij cu i, j indicii elementului curent (i și j pornesc de la 1) și apoi să se rotească matricea la dreapta. Output-ul este un șir de caractere care reprezintă afișarea matricei de sus in jos, de la stânga la dreapta.

## Task 2
Funcția primește un void * care este un șir de caractere. Șirul este de forma a1_a2_a3_…_an, unde ai este un întreg. Să se calculeze suma elementelor ai. Output-ul este un șir de caractere care reprezintă suma calculată.

## Task 3
Funcția primește un void * care reprezintă un vector. Primul element al vectorului este numărul de elemente rămase în vector. Dacă lungimea vectorului rămas este număr par să se interschimbe elementele de pe pozițiile 2k + 1 cu elementele de pe pozițiile 2k + 2. Dacă lungimea vectorului rămas este număr impar să se inverseze vectorul. Output-ul este vectorul fără primul element sub formă de sir de caractere.

## Task 4
Se dorește alocarea structurilor Player și Game și a câmpurilor lor. Pentru Player trebuie să se aloce câmpurile name, color și hat și să ii se atribuie valoarea 1 pentru alive. Pentru Game trebuie să se aloce câmpul name. Toate șirurile de caractere sunt alocate cu lungimea MAX_LEN_STR_ATR.

## Task 5
Se dorește citirea câmpurilor structurilor Player și Game. Funcțiile primesc la input fișierul(text) de intrare și returnează referința la structura pe care o aloca si o citesc.

Funcția de ReadGame trebuie să apeleze funcția de ReadPlayer pentru fiecare jucător din joc, inclusiv pentru impostor.

La citirea unui jucător, când se citește rolul unui jucător trebuie ca variabilei de tip enum playerRole să i se atribuie valoarea corespunzătoare. În fișierul tema4.c există un vector de referințe Abilities la funcțiile RotateMatrix, DecodeString, InvertArray și KillPlayer care corespund ca abilitate/task jucătorilor care au rolurile Rotator, Decoder, Invertor respectiv Impostor. Tot la citire trebuie să ii se atribuie pentru fiecare jucător referința ability la una dintre valorile din vectorul de referințe Abilities în funcție de enum-ul PlayerRole.

Input-ul este de forma următoare:
```
[nume_joc]
[killRange]
[numar_crewmates]
[crewmate_1]
…
[crewmate_n]
[impostor]
```
Unde [crewmate_1], …, [crewmate_n] si [impostor] au următoarea structura:
```
[nume_jucator]
[culoare]
[palarie]
[numar_locatii]
([x_1],[y_1])[spatiu]([x_2],[y_2])[spatiu]…
[rol_jucator]
```

## Task 6
Se dorește afișarea structurilor Player și Game. Trebuie să se completeze funcțiile WritePlayer și WriteGame. Funcțiile primesc ca parametrii structura pe care trebuie să o afișeze și fișierul(text) de output.

Funcția de WriteGame trebuie să apeleze funcția de WritePlayer pentru fiecare jucător din joc, inclusiv pentru impostor.

La finalul apelării funcției de WriteGame în fișierul de output trebuie să existe următoarea informație:
```
Game [nume_joc]  has just started!
[TAB]Game options:
Kill Range: [killRange]
Number of crewmates: [numberOfCrewmates]
[LINIE_GOALA]
[TAB]Crewmates:
Player [player_name] with color [player_color], hat [player_hat] and role [player_role] has entered the game.
Player's locations: ([x1],[y1])[spatiu]…
…
[LINIE_GOALA]
[TAB]Impostor:
Player [impostor_name] with color [impostor_color], hat [impostor_hat] and role Impostor has entered the game.
Player's locations: ([x1],[y1])[spatiu]…
```
## Task 7
Se dorește implementarea abilitații/task-ului impostorului. Input-ul funcției este un void * care este o referință la o structura de tip Game. Abilitatea impostorului este de a ucide cel mai apropriat coleg de echipaj dacă acesta este la o distanță mai mică sau egală ca killRange. Distanța dintre 2 puncte se calculează ca Distanta Manhattan.

Dacă impostorul reușește să omoare un coleg de echipaj, atunci câmpul alive al acelui coleg de echipaj devine 0 (moare). Dacă există mai mulți colegi de echipaj la aceeași distanță fată de impostor este omorât colegul de echipaj cu indicele cel mai mare. Output-ul funcției este un șir de caractere castat la void * .

Dacă impostorul reușește să omoare pe cineva output-ul o să fie de forma:
```
Impostor [nume_impostor] has just killed crewmate [nume_crewmate] from distance [distanta].
```
Daca impostorul nu reușește să omoare pe nimeni output-ul o să fie de forma:
```
Impostor [nume_impostor] couldn't kill anybody.
```

## Task 8
Se dorește implementarea unui ciclu de joc. Funcția primește ca parametrii o referință la o structura de tipul Game, un fișier de output și un void** care este un vector de input-uri de tip void * .

Pentru fiecare coleg de echipaj funcția trebuie să îi calculeze următoarea poziție și să afișeze acest lucru în următorul format:
```
Player [nume_jucator] went to location ([x],[y]).[\n]
```
Apoi funcția trebuie să apeleze pentru fiecare coleg de echipaj abilitatea/task-ul lui apelând referința la funcție ability cu input-ul void * luat din vectorul de input-uri dat ca parametru funcției CalculateNextCycleOfGame. Indicele colegului de echipaj în vectorul de crewmates dă indicele din vectorul de input-uri.

Output-ul fiecărui task al jucătorilor trebuie afișat sub forma:
```
Player [nume_jucator]'s output:[\n]
[Output]
```
Asemănător trebuie să se facă și pentru impostor.

Dacă un coleg de echipaj este mort atunci el nu se va mișca niciunde și nu își va mai face task-ul. În schimb va afișa:
```
Player [nume_jucator] is dead.[\n]
```

Drepturile de autor fata de crearea checkerului si conditiei apartin echipei de Programare a Calculatoarelor 2020

Implementarea codului: Calmis Liviu