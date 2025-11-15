BINARY SEARCH

# Recherche binaire — Exercices et Benchmarks

Objectifs

- Savoir implémenter recherche linéaire (O(n)) et binaire (O(log n)) en itératif et récursif.
- Mesurer et comparer les temps d’exécution sur différentes tailles d’entrées.
- Maitriser des variantes classiques de recherche binaire.

Pré-requis

- Tableaux triés croissants.
- Gestion des bornes (low, high, mid), overflow évité avec mid = low + ((high - low) >> 1).

Commande conseillée

- Node.js: `node exercices/binary-search/bench.js`

---

## Cas de tests — Jeux d’exemples et résultats attendus

Note de contrat pour “recherche linéaire/binaire” de base:

- Retourner le premier index i tel que arr[i] == x, sinon -1 (déterministe, compatible doublons).

A) Recherche linéaire vs binaire (même contrat: premier index ou -1)

1. Cas vides et unitaires

- arr=[], x=10 → -1
- arr=[5], x=5 → 0
- arr=[5], x=4 → -1

2. Tableau trié sans doublons

- arr=[1,3,5,7,9]
  - x=1 → 0
  - x=5 → 2
  - x=9 → 4
  - x=6 → -1
  - x=0 → -1
  - x=10 → -1

3. Tableau trié avec doublons

- arr=[1,2,2,2,3,4,4,5]
  - x=2 → 1 (première occurrence)
  - x=4 → 5 (première occurrence)
  - x=6 → -1

4. Valeurs négatives et extrémités

- arr=[-10,-3,0,1,4,9,15]
  - x=-10 → 0
  - x=15 → 6
  - x=8 → -1

B) lower_bound (indice d’insertion: premier i tel que arr[i] >= x)

- arr=[]: x=10 → 0
- arr=[1,3,3,5,8]
  - x=0 → 0
  - x=1 → 0
  - x=2 → 1
  - x=3 → 1
  - x=4 → 3
  - x=8 → 4
  - x=9 → 5

C) upper_bound (premier i tel que arr[i] > x)

- arr=[1,3,3,5,8]
  - x=0 → 0
  - x=1 → 1
  - x=2 → 1
  - x=3 → 3
  - x=4 → 3
  - x=8 → 5
  - x=9 → 5

D) Première et dernière occurrence ([-1,-1] si absent)

- arr=[2,2,3,3,3,9]
  - x=2 → [0,1]
  - x=3 → [2,4]
  - x=9 → [5,5]
  - x=4 → [-1,-1]

E) Compter les occurrences (upper_bound - lower_bound)

- arr=[1,1,1,2,2,4]
  - x=1 → 3
  - x=2 → 2
  - x=3 → 0
  - x=4 → 1

F) Valeur la plus proche (en cas d’égalité, choisir la plus petite valeur)

- arr=[1,4,6,8]
  - x=5 → 4
  - x=7 → 6
  - x=6 → 6
  - x=0 → 1
  - x=9 → 8
- arr=[1,3], x=2 → 1 (égalité de distance: 1 préféré)

G) Racine entière (floor(sqrt(n)))

- n=0 → 0
- n=1 → 1
- n=2 → 1
- n=3 → 1
- n=4 → 2
- n=8 → 2
- n=9 → 3
- n=15 → 3
- n=16 → 4
- n=24 → 4
- n=25 → 5
- n=10^12 → 10^6

H) Recherche dans un tableau trié puis pivoté (rotated)

- arr=[4,5,6,7,0,1,2]
  - x=0 → 4
  - x=4 → 0
  - x=2 → 6
  - x=3 → -1
- arr=[1], x=1 → 0; x=0 → -1
- arr=[3,1], x=1 → 1; x=3 → 0

I) Minimum dans un tableau rotaté (renvoyer l’index du minimum)

- arr=[4,5,6,7,0,1,2] → 4
- arr=[1,2,3] → 0
- arr=[2,1] → 1
- arr=[1] → 0

J) Sommet d’un tableau “montagne” (index du pic)

- arr=[1,3,5,7,6,4,2] → 3
- arr=[0,2,1,0] → 1
- arr=[1,2,3,4,5,3,1] → 4

K) Recherche dans matrice 2D triée (retour [row,col] ou [-1,-1])

- mat=[[1,4,7],[2,5,8],[3,6,9]]
  - x=5 → [1,1]
  - x=6 → [2,1]
  - x=10 → [-1,-1]
- mat=[[1,2,3,4]] (1 ligne), x=3 → [0,2]
- mat=[[1],[3],[5]] (1 colonne), x=4 → [-1,-1]
- mat=[] ou [[]], x=1 → [-1,-1]

L) Campagnes de performance (attendus qualitatifs)

- Tailles: n ∈ {10^3, 10^4, 10^5, 10^6}; mix 50% présents / 50% absents.
- Attendu:
  - Pour n petit (~10^3): écart faible, overhead similaire.
  - Pour n grand (≥10^5): binaire nettement plus rapide (tendance ~ n / log2(n)).
  - Requêtes “absentes” et “début/fin” pénalisent davantage la linéaire.
