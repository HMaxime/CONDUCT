using System;
using UnityEngine;
using static Util;
//DONE
/*
 *Cette classe permet de faire de la classification grâce à ses différents méthodes.
 *
 */
public class Classifier
{
    static DistancesSorter sorter = new DistancesSorter();
    /*
     * La méthode knn permet de faire une classification selon l'algorithme des K plus proches voisins.
     * Entrées : 
     *      K : Entier, determine combien de voisins proches nous allons prendre pour faire notre classification
     *      datas : Tableaux de nos données de références (les voisins)
     *      target : Les étiquettes de notre jeu de données de référence
     *      data : La donnée dont on veut déterminer la nature
     */ 
    public int knn(int K, float[][] datas, int[] target, float[] data)
    {
        float[][] distances = new float[target.Length][];
        for (int i = 0; i < datas.Length; i++)
        {
            distances[i] = new float[] { ComputeDistance(datas[i], data), target[i] };
        }
        Array.Sort(distances, sorter);
        int[] classes = getFirstKcolumn(K, 1, distances);
        return getMostFrequentElement(classes);
    }
}
