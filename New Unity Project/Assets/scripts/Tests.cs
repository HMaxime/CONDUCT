using System.Diagnostics;
using System.IO;
using UnityEngine;

public class Tests : MonoBehaviour
{
    Mouvement hands;
    DataSet dataset;
    Transform palmLeft;
    float[] actualLeftHand;
    float[] actualRightHand;
    Classifier classifier;
    int classe=-1;

    public Tests()
    {
       
    }

    private void Start()
    {
        dataset = new DataSet(@"C:\Users\MaximeHamon\Documents\Cours\UBS\S2\INF2212_projet\CONDUCT\New Unity Project\Assets\scripts\Datas");
        actualLeftHand = new float[5];
        actualRightHand = new float[5];
        classifier = new Classifier();
        this.hands = (Mouvement)GetComponent("Mouvement");
    }

    // Update is called once per frame
    void Update()
    {
        palmLeft = hands.PalmLeft;
        actualLeftHand[0] = hands.getDistanceBetween(hands.ThumbLeft, palmLeft);
        actualLeftHand[1] = hands.getDistanceBetween(hands.IndexLeft, palmLeft);
        actualLeftHand[2] = hands.getDistanceBetween(hands.MiddleLeft, palmLeft);
        actualLeftHand[3] = hands.getDistanceBetween(hands.PinkLeft, palmLeft);
        actualLeftHand[4] = hands.getDistanceBetween(hands.RingLeft, palmLeft);
        this.classe=classifier.knn(3, dataset.Datas, dataset.Target, actualLeftHand);
    }



    private void OnGUI()
    {
        GUIStyle style = new GUIStyle("Box");
        style.fontSize = 50;

        switch (this.classe)
        {
            case 0:
                GUI.Label(new Rect(10, 10, 500, 100), "Poing Fermé !",style);
                break;
            case 1:
                GUI.Label(new Rect(10, 10, 500, 100), "Main ouverte !", style);
                break;

            case 2:
                GUI.Label(new Rect(10, 10, 500, 100), "Deux doigts !", style);
                break;

            default:
                GUI.Label(new Rect(10, 10, 500, 100), "Chargement !",style);
                break;
        }

    }

}
