using System.Diagnostics;
using System.IO;
using UnityEngine;

public class Tests : MonoBehaviour
{
    Mouvement hands;
    DataSet dataset;
    Transform palmLeft;
    Classifier classifier;
    UIController uiController;

    float[] actualLeftHand;
    float[] actualRightHand;

    float miniHorizontal = 20;
    float maxiHorizontal = -20;
    float miniVertical = 20;
    float maxiVertical = -20;

    int classe = -1;
    OscMessage message;
    OSC osc;
    bool calibration = false;
    bool calibrationVertical = false;

    private void Start()
    {
        osc = (OSC)GetComponent("OSC");
        dataset = new DataSet(Directory.GetCurrentDirectory() + @"\Assets\scripts\Datas");
        actualLeftHand = new float[5];
        actualRightHand = new float[5];
        classifier = new Classifier();
        this.hands = (Mouvement)GetComponent("Mouvement");
        this.uiController = (UIController)GameObject.Find("Canvas").GetComponent("UIController");
    }

    // Update is called once per frame
    void Update()
    {
        this.hands = (Mouvement)GetComponent("Mouvement");
        palmLeft = hands.PalmLeft;
        actualLeftHand[0] = hands.getDistanceBetween(hands.ThumbLeft, palmLeft);
        actualLeftHand[1] = hands.getDistanceBetween(hands.IndexLeft, palmLeft);
        actualLeftHand[2] = hands.getDistanceBetween(hands.MiddleLeft, palmLeft);
        actualLeftHand[3] = hands.getDistanceBetween(hands.PinkLeft, palmLeft);
        actualLeftHand[4] = hands.getDistanceBetween(hands.RingLeft, palmLeft);
        this.classe = classifier.knn(3, dataset.Datas, dataset.Target, actualLeftHand);
    }



    private void OnGUI()
    {
        GUIStyle style = new GUIStyle("Box");
        style.fontSize = 25;

        //On fait la calibration
        if (!calibration)
        {
            //On fait la calibration vertical
            if (!calibrationVertical)
            {
                if (this.hands.PalmRight.position.y < miniVertical)
                {
                    miniVertical = this.hands.PalmRight.position.y;
                }
                else if (this.hands.PalmRight.position.y > maxiVertical)
                {
                    maxiVertical = this.hands.PalmRight.position.y;
                }
                GUI.Label(new Rect(10, 10, 500, 40), "Minimum Vertical = " + miniVertical, style);
                GUI.Label(new Rect(520, 10, 500, 40), "maximum Vertical = " + maxiVertical, style);
                GUI.Label(new Rect(1, 60, 1000, 40), "2 doigts => fin de la calibration vertical", style);

                //Fin de la calibration vertical
                if (this.classe == 2)
                {
                    calibrationVertical = true;
                }
            }
            //On fait la calibration horizontal
            else
            {
                if (this.hands.PalmRight.position.x < miniHorizontal)
                {
                    miniHorizontal = this.hands.PalmRight.position.x;
                }
                else if (this.hands.PalmRight.position.x > maxiHorizontal)
                {
                    maxiHorizontal = this.hands.PalmRight.position.x;
                }
                GUI.Label(new Rect(10, 10, 500, 40), "Minimum Vertical = " + miniVertical, style);
                GUI.Label(new Rect(520, 10, 500, 40), "Maximum Vertical = " + maxiVertical, style);

                GUI.Label(new Rect(10, 60, 500, 40), "Minimum horizontal = " + miniHorizontal, style);
                GUI.Label(new Rect(520, 60, 500, 40), "Maximum horizontal = " + maxiHorizontal, style);
                GUI.Label(new Rect(1, 110, 1000, 40), "Poings fermés => fin de la calibration", style);


                //Fin de la calibration horizontal et fin de la calibration générale
                if (this.classe == 0)
                {
                    calibration = true;
                }
            }
        }
        else
        {
            //Pour avoir les valeurs dans le bon interval : new_x=(x-M)/(N-M)
            message = new OscMessage();
            switch (this.classe)
            {
                case 0:
                    GUI.Label(new Rect(10, 10, 500, 100), "Poing Fermé !", style);


                    float value = this.hands.PalmRight.position.x * 3;
                    uiController.setStereoSliderValue(value);

                    message.address = "/127.0.0.1:5001";
                    message.values.Add(1);
                    osc.outPort = 5001;
                    print("Message : " + message);
                    osc.Send(message);


                    break;
                case 1:
                    GUI.Label(new Rect(10, 10, 500, 100), "Main ouverte !", style);
                    break;

                case 2:
                    GUI.Label(new Rect(10, 10, 500, 100), "Deux doigts !", style);
                    uiController.setVolumeSliderValue((this.hands.PalmRight.position.y-miniVertical)/(miniVertical-maxiVertical));

                    message.address = "/127.0.0.1:5000";
                    message.values.Add((this.hands.PalmRight.position.y-miniVertical)/(miniVertical-maxiVertical));
                    osc.outPort = 5000;
                    print("Message : " + message);
                    osc.Send(message);
                    break;

                default:
                    GUI.Label(new Rect(10, 10, 500, 100), "Chargement !", style);
                    break;
            }
        }

    }

}
