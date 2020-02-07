Faust permet de faire des instruments (voir ceux qui sont déjà faits)
Faust génère un fichier .dsp
Il faut convertir ce fichier .dsp en objet PureData.
Pour ce faire on installe dans les externals de PureData la librairie Faustgen
Un objet Faust dans PureData s'écrit donc faustgen~ nomDuFichierDsp.
Il faut envoyer un message "print" afin de voir combien d'input et d'output, et quels sont les types des paramètres.