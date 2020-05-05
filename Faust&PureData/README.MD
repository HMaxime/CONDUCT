Faust permet de faire des instruments (voir ceux qui sont déjà faits)
Faust génère un fichier .dsp
Il faut convertir ce fichier .dsp en objet PureData.
Pour ce faire on installe dans les externals de PureData la librairie Faustgen
Un objet Faust dans PureData s'écrit donc faustgen~ nomDuFichierDsp.
Il faut envoyer un message "print" afin de voir combien d'input et d'output, et quels sont les types des paramètres.

On utilise un fichier MIDI pour lire une mélodie.
On extrait les paramètres nécessaires et on les envoie aux instruments Faust.
On joue en boucle cette mélodie.
On écoute sur le port 5000 et on recoit sous le format OSC les paramètres à modifier sur l'instrument (ex : volume, attaque, vibrato, etc).
