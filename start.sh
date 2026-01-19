#!/bin/bash

#Handle termination
cleanup() {
    echo ""
    echo "Arrêt des services..."
    if [ -n "$(jobs -p)" ]; then
        kill $(jobs -p) 2>/dev/null
    fi
    exit
}
trap cleanup SIGINT EXIT

#copie des .dll (si vous êtes sur windows)
if [ -d "build/Release" ]; then
    echo "🪟 Windows détecté : Copie des DLLs vers le dossier Release..."
    find build -name "*.dll" -exec cp {} build/Release/ \; 2>/dev/null
fi

# C++
echo "Compilation du C++ (Mode Release)..."
cd low_level

#Compilation
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

echo "--- Démarrage de l'infrastructure ---"

# 1. QueueManager
cd ..
echo "Lancement du QueueManager..."
uv run python src/QueueManager.py &
sleep 2

# 2. Proxy
echo "Lancement du Proxy..."
uv run python src/proxy.py &
sleep 2

echo "--- Lancement des calculs ---"

# 3. Boss
echo "Lancement du Boss..."
uv run python src/boss.py &
PID_BOSS=$!
sleep 2

if [ -f "low_level/build/Release/low_level.exe" ]; then
    EXE_PATH="low_level/build/Release/low_level.exe"
elif [ -f "low_level/build/low_level" ]; then
    EXE_PATH="low_level/build/low_level"
else
    echo "Erreur : L'exécutable C++ est introuvable."
    echo "Veuillez compiler le projet 'low_level' avant de lancer ce script."
    exit 1
fi

echo "Lancement du Worker C++ ($EXE_PATH)..."
$EXE_PATH

wait $PID_BOSS

echo ""
echo "Scénario terminé."
echo "Appuyez sur Ctrl+C pour couper les serveurs restants."
wait
