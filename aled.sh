#!/bin/bash

# Lire le fichier contenant la liste des fichiers manquants
while read -r line; do
    # Extraire le chemin du fichier source depuis la ligne
    src_file=$(echo "$line" | sed -n 's/Seulement dans \/home\/lancelot\/Dev\/TN\/video-game-01\/src\/assets\(.*\): \(.*\)/\/home\/lancelot\/Dev\/TN\/video-game-01\/src\/assets\1\/\2/p')

    # Déterminer le chemin du fichier de destination
    dest_file=$(echo "$src_file" | sed 's/\/home\/lancelot\/Dev\/TN\/video-game-01\/src\/assets/\.\/src\/assets/')

    # Créer le répertoire de destination s'il n'existe pas
    mkdir -p "$(dirname "$dest_file")"

    # Copier le fichier
    cp "$src_file" "$dest_file"
done < missing_files.txt
