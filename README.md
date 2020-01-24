# CONDUCT
##Responsable
Sylvie Gibet (sylvie.gibet@univ-ubs.fr), équipe EXPRESSION, laboratoire IRISA
Contexte scientifique
Ce projet s’inscrit dans les axes de recherche l’équipe Expression (https://wwwexpression.irisa.fr/fr/) qui concernent l’analyse et la synthèse des données expressives
produites par l’humain (geste, son, image).
Plus précisément, on s’intéresse ici au contrôle gestuel de processus de simulation
sonore. Des travaux réalisés préalablement dans l’équipe [1], [2] et dans le cadre de
projets de master 1 (SONIC 1 et SONIC 2) ont permis de d’analyser et de synthétiser des
gestes instrumentaux (percussion, violon) et des gestes de chef d’orchestre.
##Objectif du projet
L’objectif final du projet est de contrôler et synthétiser des sons au moyen de la
reconnaissance et du tracking de gestes en temps réel. On s’intéresse à un ensemble de
gestes d’interprétation d’une mélodie donnée qui permettent de moduler de manière
expressive les sons constituants de cette mélodie (par exemple variation de l’intensité, de
la radiosité, de l’attaque, arrêt, variation du tempo, etc.).
Les gestes seront d’abord capturés au moyen du clavier expressif HAKEN afin de calibrer
le système de synthèse de son, puis reconnus à partir du système Leap Motion. La
reconnaissance de gestes statiques (postures clés prédéfinies) sera réalisée par un
algorithme d’apprentissage simple (K-NN ou SVM). La détection des gestes dynamiques
sera réalisée un tracking simple ou une reconnaissance temps réel du tracé du geste. 
La synthèse sera réalisée grâce au framework Faust et au système de synthèse Pure
Data.
Ce projet sera poursuivi en M2 dans le cadre d’une application de réalité virtuelle intégrant
la visualisation interactive d’objets sonores (exemple Audica).
##Méthodes et outils
###Matériel : clavier HAKEN, système Leap Motion pour la reconnaissance de gestes
et le tracking
###Environnement technique
Le projet pourra être développé dans l’environnement Unity 3D, mais pas nécessairement.
Le framework Faust sera utilisé pour générer un système de synthèse audionumérique, et
la communication sera gérée par le protocole OSC (Open Sound Control).
Le projet Unity 3D SONIC2 (2019) sera disponible sur l’une des machines de VirtualLab
(contrôle gestuel de sons de violon).
