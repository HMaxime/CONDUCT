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
     * Calcule la distance euclidienne entre deux points.
     */
    public static float computeEuclidianDistance(float[] p1_, float[] p2_)
    {
        float res = 0;
        for (int i = 0; i < p1_.Length; i++)
        {
            res += Mathf.Pow(p1_[i] - p2_[i], 2);
        }
        return res;
    }
    /*
    * Calcule la distance DTW entre deux ensembles de points qui constituent des courbes.
    * La distance DTW permet de mesurer la similarité entre deux séries temporelles.
    */
    public static float computeDTWDistance(float[][] p1_, float[][] p2_)
    {
        int n = p1_.Length;
        int m = p2_.Length;

        float[][] costMatrix = computeCostMatrix(p1_,p2_);
        float[][] DTWMatrix = initializeDTWMatrix(n,m);


        DTWMatrix[0][0]=0;
        DTWMatrix[1][1]=costMatrix[0][0];

        for (int i=2;i<n+1;i++){
            DTWMatrix[i][1] = costMatrix[i-1][0]+DTWMatrix[i-1][1];
        }

        for(int i=2;i<m+1;i++){
            DTWMatrix[1][i]=costMatrix[0][i-1]+DTWMatrix[1][i-1];
        }

        for(int i=2;i<n+1;i++){
            for(int j=2;j<m+1;i++){
                DTWMatrix[i][j] = costMatrix[i-1][j-1]; //+ min(DTW[i-1,j-1],DTW[i-1,j],DTW[i,j-1])
            }
        }

        int[][] path=optimalWarpingPath(DTWMatrix);
        float dtwDistance=DTWMatrix[n][m]/path.Length;

        return dtwDistance;

    }

    private static float[][] initializeDTWMatrix(int n_,int m_){
        float[][] res = new float[n_+1][];
        for(int i=0;i<res.Length;i++){
            for(int j=0;j<res[0].Length;i++){
                res[i][i]=float.PositiveInfinity;
            }
        }
        return res;
    }   

    private static float[][] computeCostMatrix(float[][] p1_,float[][] p2_)
    {
        float[][] res = new float[p1_.Length][];

        for(int i = 0;i<p1_.Length;i++){
            for(int j=0;j<p2_.Length;i++){
                res[i][j]=computeEuclidianDistance(p1_[i],p2_[j]);
            }
        }
        return res;
    }

    private static int[][] optimalWarpingPath(float[][] DTW){
        return new int[1][];
    }
    
    /*
     * permet de convertir un objet de la classe Transform en array.
     */
    public static float[] posTransformToArray(Transform tr) => new float[3] { tr.position.x, tr.position.y, tr.position.z };

}
