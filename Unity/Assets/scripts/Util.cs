using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
//DONE
/*
 * Util est une classe contenant des méthodes utilitaires.
 */
public class Util {
    /*
     * Donne l'élément le plus fréquent dans un tableau.
     */
    public static int getMostFrequentElement (List<int> tab_) {
        int[] histogram = new int[tab_.Max () + 1];
        foreach (int elt in tab_) {
            histogram[elt] += 1;
        }
        return histogram.ToList ().IndexOf (histogram.Max ());
    }

    /*
     * Permet, à partir d'un tableau, de retournerles K premières colonnes.
     */
    public static List<int> getFirstKcolumn (int k_, int i_, List<List<float>> tab_) {
        int[] res = new int[k_];
        for (int i = 0; i < k_; i++) {
            res[i] = (int) tab_[i][i_];
        }

        return new List<int> (res);
    }

    /*
     * Calcule la distance euclidienne entre deux points.
     */
    public static float computeEuclidianDistance (List<float> p1_, List<float> p2_) {
        float res = 0;
        for (int i = 0; i < p1_.Count; i++) {
            res += Mathf.Pow (p1_[i] - p2_[i], 2);
        }
        return res;
    }
    /*
     * Calcule la distance DTW entre deux ensembles de points qui constituent des courbes.
     * La distance DTW permet de mesurer la similarité entre deux séries temporelles.
     */
    public static float computeDTWDistance (List<List<float>> p1_, List<List<float>> p2_) {
        int n = p1_.Count;
        int m = p2_.Count;

        List<List<float>> costMatrix = computeCostMatrix (p1_, p2_);
        List<List<float>> DTWMatrix = initializeDTWMatrix (n, m);

        DTWMatrix[0][0] = 0;
        DTWMatrix[1][1] = costMatrix[0][0];

        for (int i = 2; i < n + 1; i++) {
            DTWMatrix[i][1] = costMatrix[i - 1][0] + DTWMatrix[i - 1][1];
        }

        for (int i = 2; i < m + 1; i++) {
            DTWMatrix[1][i] = costMatrix[0][i - 1] + DTWMatrix[1][i - 1];
        }

        for (int i = 2; i < n + 1; i++) {
            for (int j = 2; j < m + 1; j++) {
                DTWMatrix[i][j] = costMatrix[i - 1][j - 1]; //+ min(DTW[i-1,j-1],DTW[i-1,j],DTW[i,j-1])
            }
        }

        List < (int, int) > path = optimalWarpingPath (DTWMatrix);
        float dtwDistance = DTWMatrix[n][m] / path.Count;

        return dtwDistance;

    }

    private static List<List<float>> initializeDTWMatrix (int n_, int m_) {
        List<List<float>> res = new List<List<float>> (n_);
        for (int i = 0; i < n_ + 1; i++) {
            List<float> temp = new List<float> (m_);
            for (int j = 0; j < m_ + 1; j++) {
                temp.Add (float.PositiveInfinity);
            }
            res.Add (temp);
        }
        return res;
    }

    private static List<List<float>> computeCostMatrix (List<List<float>> p1_, List<List<float>> p2_) {
        List<List<float>> res = new List<List<float>> (p1_.Count);

        for (int i = 0; i < p1_.Count; i++) {
            List<float> temp = new List<float> (p2_.Count);
            for (int j = 0; j < p2_.Count; j++) {
                temp.Add (computeEuclidianDistance (p1_[i], p2_[j]));
            }
            res.Add (temp);
        }
        return res;
    }

    private static List < (int, int) > optimalWarpingPath (List<List<float>> DTW) {
        List < (int, int) > path = new List < (int, int) > ();
        int i = DTW.Count - 1;
        int j = DTW[0].Count - 1;
        path.Add ((i, j));
        while (i != 1 && j != 1) {
            if (i == 1) {
                path.Add ((1, j - 1));
                j = j - 1;
            } else if (j == 1) {
                path.Add ((i - 1, 1));
                i = i - 1;
            } else {
                int[] input = {
                    (int) DTW[i - 1][j - 1],
                    (int) DTW[i - 1][j],
                    (int) DTW[i][j - 1]
                };
                List<int> backStep = new List<int> (input);
                int arg = backStep.IndexOf (backStep.Max ());
                if (arg == 0) {
                    i = i - 1;
                    j = j - 1;
                } else if (arg == 1) {
                    i = i - 1;
                } else if (arg == 2) {
                    j = j - 1;
                }
                path.Add ((i, j));
            }
        }
        path.Add ((1, 1));

        return path;
    }

    /*
     * permet de convertir un objet de la classe Transform en array.
     */
    public static List<float> posTransformToList (Transform tr) => new List<float> () { tr.position.x, tr.position.y, tr.position.z };

}