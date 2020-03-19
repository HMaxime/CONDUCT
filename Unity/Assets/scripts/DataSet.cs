using System.IO;
using System.Linq;
using UnityEngine;

/*
 * DataSet est une classe qui nous permet d'enregistrer des jeux de données.
 * 
 */ 
public class DataSet
{
    float[][] datas;
    int[] target;

    public float[][] Datas { get => datas; }
    public int[] Target { get => target; }
    public string[] files;
    public DataSet(string folderPath)
    {
        files = Directory.GetFiles(folderPath,"*.txt");
        int i = 0;
        //int nbElt= File.ReadLines(files[0]).Count() + File.ReadLines(files[1]).Count()+ File.ReadLines(files[2]).Count();
        int nbElt = 0;
        for(int l = 0; l < files.Length; l++)
        {
            nbElt += File.ReadLines(files[l]).Count();
        }
        datas = new float[nbElt][];
        target = new int[nbElt];
        int k = 0;
        foreach (string file in files)
        {
            StreamReader reader = File.OpenText(file);
            string line;
            while ((line = reader.ReadLine()) != null)
            {
                string[] stringDistances = line.Split(' ');
                float[] floatDistance = new float[stringDistances.Length];
                for (int j = 0; j < stringDistances.Length; j++)
                {
                    floatDistance[j] = float.Parse(stringDistances[j]);
                }
                datas[i] = floatDistance;
                target[i] = k;
                i++;
            }
            k++;
            reader.Close();
            
        }
        
    }


}
