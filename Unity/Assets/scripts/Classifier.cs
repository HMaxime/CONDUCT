using System;
using UnityEngine;
using static Util;
using System.Collections.Generic;
using System.Linq;

//DONE
/*
 *Cette classe permet de faire de la classification grâce à ses différents méthodes.
 *
 */
public class Classifier {
    static DistancesSorter sorter = new DistancesSorter ();
    /*
     * La méthode knn permet de faire une classification selon l'algorithme des K plus proches voisins.
     * Entrées : 
     *      K : Entier, determine combien de voisins proches nous allons prendre pour faire notre classification
     *      datas : Tableaux de nos données de références (les voisins)
     *      target : Les étiquettes de notre jeu de données de référence
     *      data : La donnée dont on veut déterminer la nature
     */
    public int knn (int k, List<List<float>> datas, List<int> target, List<float> data) {
        List<List<float>> distances = new List<List<float>> ();
        foreach (List<float> dataRef in datas) {
            distances.Add (new List<float> () { computeEuclidianDistance (dataRef, data), target[datas.IndexOf (dataRef)] });
        }

        distances.Sort (sorter);
        List<int> classes = getFirstKcolumn (k, 1, distances);
        return getMostFrequentElement (classes);
    }

    public int knn (int k, List<List<List<float>>> datas, List<int> target, List<List<float>> data) {
        List<List<float>> distances = new List<List<float>> ();
        foreach(List<List<float>> dataRef in datas ){
            distances.Add(new List<float>() {computeDTWDistance(dataRef,data),target[datas.IndexOf (dataRef)]});
        }

        distances.Sort(sorter);
        List<int> classes = getFirstKcolumn (k, 1, distances);
        return getMostFrequentElement(classes);
    }
}