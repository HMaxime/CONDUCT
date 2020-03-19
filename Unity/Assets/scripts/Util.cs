using UnityEngine;
//DONE
/*
 * Util est une classe contenant des méthodes utilitaires.
 */ 
public class Util
{
    /*
     * Donne l'élément le plus fréquent dans un tableau.
     */ 
    public static int getMostFrequentElement(int[] tab_)
    {
        int currentValue = tab_[0];
        int count = 1;
        int maxCount = 1;

        for (int i = 1; i < tab_.Length; i++)
        {
            if (tab_[i] == tab_[i - 1])
            {
                count += 1;
            }
            else
            {
                if (count > maxCount)
                {
                    maxCount = count;
                    currentValue = tab_[i - 1];
                }
                count = 1;
            }
        }
        if (count > maxCount)
        {
            maxCount = count;
            currentValue = tab_[tab_.Length - 1];
        }
        return currentValue;
    }

    /*
     * Permet, à partir d'un tableau, de retournerles K premières colonnes.
     */ 
    public static int[] getFirstKcolumn(int k_, int i_, float[][] tab_)
    {
        int[] res = new int[k_];
        for (int i = 0; i < k_; i++)
        {
            res[i] = (int)tab_[i][i_];
        }

        return res;
    }

    /*
     * Calcule la distance entre deux points.
     */ 
    public static float ComputeDistance(float[] p1, float[] p2)
    {
        float res = 0;
        for (int i = 0; i < p1.Length; i++)
        {
            res += Mathf.Pow(p1[i] - p2[i], 2);
        }
        return res;
    }

    /*
     * permet de convertir un objet de la classe Transform en array.
     */ 
    public static float[] posTransformToArray(Transform tr) => new float[3] { tr.position.x, tr.position.y, tr.position.z };

}
