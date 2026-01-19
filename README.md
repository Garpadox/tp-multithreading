# Hybrid Multithreading Architecture (Python & C++)

![License](https://img.shields.io/badge/license-MIT-blue.svg)

L'objectif est de résoudre des systèmes linéaires matriciels ($Ax=b$) en comparant les performances entre :
1.  **Python (Numpy)** : Utilisant des librairies optimisées (BLAS/LAPACK).
2.  **C++ (Eigen + OpenMP)** : Une implémentation "Low Level" multithreadée communiquant via HTTP.

## Table des Matières

- [Architecture du Projet](#-architecture-du-projet)
- [Prérequis et Dépendances](#-prérequis-et-dépendances)
- [Installation](#-installation)
- [Démarrage Rapide](#-démarrage-rapide)
- [Tests](#-Tests)
- [Conclusion](Conclusion)

## Prérequis et Dépendances
Ce projet a été construit en utilisant le suivant
- [Python 3.10](https://www.python.org/downloads/release/python-3100/)
- [curl](https://curl.se/)
- [uv](https://github.com/astral-sh/uv)
- [C++]()
- [CPR](https://github.com/libcpr/cpr)
- [json from nlohmann](https://github.com/nlohmann/json)
- [Eigen](https://eigen.tuxfamily.org)

## Instalation

Vous devez utiliser Windows et un environement virtuel afin de pouvoir lancer les commandes suivantes :

Ouvrez un terminal et tapez le suivant :

```bash
# Install uv
curl -LsSf https://astral.sh/uv/install.sh | sh

# Clone the repository
git clone https://github.com/Garpadox/tp-multithreading

# Navigate to the project directory
cd tp-multithreading

# Sync uv
uv sync
```

## Démarrage Rapide

Un script automatisé start.sh a été conçu pour :

Compiler le code C++ en mode Release (optimisé).

Copier les DLLs nécessaires (si sur Windows).

Lancer le QueueManager, le Proxy, le Boss et le Worker dans l'ordre.

Afficher les résultats en temps réel.

### Étapes avant de lancer

Assurez-vous d'être à la racine du projet.

Rendez le script exécutable (nécessaire sur Linux/Mac/Git Bash) :

```
chmod +x start.sh
```

Lancez le projet :

./start.sh

## Tests

```
Sans OpenMP
--- Sending Tasks ---

Task 0 sent (Size: 2487)

Task 1 sent (Size: 973)

Task 2 sent (Size: 501)

Task 3 sent (Size: 424)

Task 4 sent (Size: 1792)

Task 5 sent (Size: 555)

Task 6 sent (Size: 1029)

Task 7 sent (Size: 2734)

Task 8 sent (Size: 2089)

Task 9 sent (Size: 1987)

--- Receiving & Comparing Results ---

Verifying Task 0 in Python... Done.

   [C++ Time]: 1.18082s

   [Py  Time]: 0.18709s

   -> Winner: Python (Diff: 0.99372s)

Verifying Task 1 in Python... Done.

   [C++ Time]: 0.06725s

   [Py  Time]: 0.01310s

   -> Winner: Python (Diff: 0.05415s)

Verifying Task 2 in Python... Done.

   [C++ Time]: 0.00832s

   [Py  Time]: 0.00263s

   -> Winner: Python (Diff: 0.00569s)

Verifying Task 3 in Python... Done.

   [C++ Time]: 0.00537s

   [Py  Time]: 0.00155s

   -> Winner: Python (Diff: 0.00382s)

Verifying Task 4 in Python... Done.

   [C++ Time]: 0.37571s

   [Py  Time]: 0.08074s

   -> Winner: Python (Diff: 0.29497s)

Verifying Task 5 in Python... Done.

   [C++ Time]: 0.01272s

   [Py  Time]: 0.00302s

   -> Winner: Python (Diff: 0.00970s)

Verifying Task 6 in Python... Done.

   [C++ Time]: 0.07558s

   [Py  Time]: 0.01546s

   -> Winner: Python (Diff: 0.06012s)

Verifying Task 7 in Python... Done.

   [C++ Time]: 1.67753s

   [Py  Time]: 0.25010s

   -> Winner: Python (Diff: 1.42743s)

Verifying Task 8 in Python... Done.

   [C++ Time]: 0.61055s

   [Py  Time]: 0.10932s

   -> Winner: Python (Diff: 0.50123s)

Verifying Task 9 in Python... Done.

   [C++ Time]: 0.52292s

   [Py  Time]: 0.09241s

   -> Winner: Python (Diff: 0.43051s)
```

```
avec OpenMP :

--- Lancement des calculs ---
Lancement du Boss...
--- Sending Tasks ---
Task 0 sent (Size: 2991)
Task 1 sent (Size: 1162)
Task 2 sent (Size: 2343)
Task 3 sent (Size: 1265)
Task 4 sent (Size: 2624)
Task 5 sent (Size: 1233)
Task 6 sent (Size: 506)
Task 7 sent (Size: 1949)
Task 8 sent (Size: 2481)
Task 9 sent (Size: 1088)

--- Receiving & Comparing Results ---
Verifying Task 0 in Python... Done.
   [C++ Time]: 2.52160s
   [Py  Time]: 0.32866s
   -> Winner: Python (Diff: 2.19294s)

Verifying Task 1 in Python... Done.
   [C++ Time]: 0.11510s
   [Py  Time]: 0.02256s
   -> Winner: Python (Diff: 0.09254s)

Verifying Task 2 in Python... Done.
   [C++ Time]: 0.96435s
   [Py  Time]: 0.16229s
   -> Winner: Python (Diff: 0.80206s)

Verifying Task 3 in Python... Done.
   [C++ Time]: 0.13974s
   [Py  Time]: 0.02925s
   -> Winner: Python (Diff: 0.11049s)

Verifying Task 4 in Python... Done.
   [C++ Time]: 1.53400s
   [Py  Time]: 0.23074s
   -> Winner: Python (Diff: 1.30327s)

Verifying Task 5 in Python... Done.
   [C++ Time]: 0.12658s
   [Py  Time]: 0.02649s
   -> Winner: Python (Diff: 0.10009s)

Verifying Task 6 in Python... Done.
   [C++ Time]: 0.00843s
   [Py  Time]: 0.00251s
   -> Winner: Python (Diff: 0.00592s)

Verifying Task 7 in Python... Done.
   [C++ Time]: 0.50127s
   [Py  Time]: 0.09467s
   -> Winner: Python (Diff: 0.40660s)

Verifying Task 8 in Python... Done.
   [C++ Time]: 1.20833s
   [Py  Time]: 0.19313s
   -> Winner: Python (Diff: 1.01519s)

Verifying Task 9 in Python... Done.
   [C++ Time]: 0.08759s
   [Py  Time]: 0.01976s
   -> Winner: Python (Diff: 0.06782s)


```

```
En changeant l'algorithme
--- Lancement des calculs ---
Lancement du Boss...
--- Sending Tasks ---
Task 0 sent (Size: 931)
Task 1 sent (Size: 1619)
Task 2 sent (Size: 626)
Task 3 sent (Size: 2700)
Task 4 sent (Size: 1923)
Task 5 sent (Size: 1637)
Task 6 sent (Size: 2618)
Task 7 sent (Size: 882)
Task 8 sent (Size: 2535)
Task 9 sent (Size: 2249)

--- Receiving & Comparing Results ---
Verifying Task 0 in Python... Done.
   [C++ Time]: 0.01606s
   [Py  Time]: 0.01162s
   -> Winner: Python (Diff: 0.00444s)
Verifying Task 1 in Python... Done.
   [C++ Time]: 0.08091s
   [Py  Time]: 0.05520s
   -> Winner: Python (Diff: 0.02571s)

Verifying Task 2 in Python... Done.
   [C++ Time]: 0.00521s
   [Py  Time]: 0.00427s
   -> Winner: Python (Diff: 0.00094s)

Verifying Task 3 in Python... Done.
   [C++ Time]: 0.35021s
   [Py  Time]: 0.24905s
   -> Winner: Python (Diff: 0.10116s)

Verifying Task 4 in Python... Done.
   [C++ Time]: 0.12896s
   [Py  Time]: 0.08926s
   -> Winner: Python (Diff: 0.03969s)

Verifying Task 5 in Python... Done.
   [C++ Time]: 0.08017s
   [Py  Time]: 0.05849s
   -> Winner: Python (Diff: 0.02168s)

Verifying Task 6 in Python... Done.
   [C++ Time]: 0.32111s
   [Py  Time]: 0.22868s
   -> Winner: Python (Diff: 0.09243s)

Verifying Task 7 in Python... Done.
   [C++ Time]: 0.01364s
   [Py  Time]: 0.00976s
   -> Winner: Python (Diff: 0.00388s)

Verifying Task 8 in Python... Done.
   [C++ Time]: 0.29403s
   [Py  Time]: 0.20635s
   -> Winner: Python (Diff: 0.08768s)

Verifying Task 9 in Python... Done.
   [C++ Time]: 0.20354s
   [Py  Time]: 0.13757s
   -> Winner: Python (Diff: 0.06596s)
```

## Conclusion
Python est 5 à 8 fois plus rapide que le C++.

En C++, nous utilisont colPivHouseholderQr, méthode stable mais couteuse en termes d'operation
En python, numpy utilise dgesv qui demande x2 fois moins de calculs.

En ajoutant du multithreading en C++ (OpenMP), cela semble améliorer les choses mais avec un gain très (très) faible voir pas du tout (tâche 2 sans OpenMP, taille 501 :  [C++ Time]: 0.00832s. Tâche 2 avec OpenMP, taille 506 : [C++ Time]: 0.00843s)

En passant par un algorithme sequentiel, cela n'améliore pas forcément les performances. En changeant l'algorithme (décomposition LU), on arrive à avoir un niveau presque égal à numpy.
