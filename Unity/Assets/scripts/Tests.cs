using System.Diagnostics;
using System.IO;
using UnityEngine;
using System.Collections.Generic;

/*
 * La méthode Tests nous permet de tester les différents algorithmes de classification, tout en permettant l'envoie de message OSC vers PureData.
 */
public class Tests : MonoBehaviour
{
    Mouvement hands;
    DataSet dataset;
    Transform palmLeft;
    Classifier classifier;
    UIController uiController;

    List<float> actualLeftHand;
    List<float> actualRightHand;

    float miniHorizontal = 20;
    float maxiHorizontal = -20;
    float miniVertical = 20;
    float maxiVertical = -20;

    int classe = -1;
    OscMessage message;
    OSC osc;
    bool calibration = false;
    bool calibrationVertical = false;

    float volume, tempo, attack, frequency = 0;

    public Tests()
    {
        this.actualLeftHand = new List<float>(5);
        this.actualRightHand = new List<float>(5);
    }

    /*
     * On initialise tous les champs dont nous allons avoir besoin par la suite.
     */
    private void Start()
    {
        this.osc = (OSC)GetComponent("OSC");
        this.dataset = new DataSet(Directory.GetCurrentDirectory() + @"\Assets\scripts\Datas\gestes_statiques",false);
        this.classifier = new Classifier();
        this.hands = (Mouvement)GetComponent("Mouvement");
        this.uiController = (UIController)GameObject.Find("Canvas").GetComponent("UIController");
    }

    // Update is called once per frame
    /*
     * On met à jour les mains, ainsi que la distance entre les différents doigts de la main gauche.
     */
    void Update()
    {

        this.hands = (Mouvement)GetComponent("Mouvement");
        palmLeft = this.hands.PalmLeft;
        this.actualLeftHand.Add(this.hands.getDistanceBetween(hands.ThumbLeft, palmLeft));
        this.actualLeftHand.Add(this.hands.getDistanceBetween(hands.IndexLeft, palmLeft));
        this.actualLeftHand.Add(this.hands.getDistanceBetween(hands.MiddleLeft, palmLeft));
        this.actualLeftHand.Add(this.hands.getDistanceBetween(hands.PinkLeft, palmLeft));
        this.actualLeftHand.Add(this.hands.getDistanceBetween(hands.RingLeft, palmLeft));

        this.classe = classifier.knn(3, dataset.DatasStatic, dataset.TargetStatic, actualLeftHand);
        this.actualLeftHand.Clear();
    }


    /*
     * OnGui nous permet d'avoir une interface graphique.
     */
    private void OnGUI()
    {
        GUIStyle style = new GUIStyle("Box");
        style.fontSize = 25;
        float value;
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
            message.address = "/127.0.0.1:5000";
            switch (this.classe)
            {
                case 0:
                    GUI.Label(new Rect(10, 10, 500, 100), "Poing Fermé !", style);
                    value = (this.hands.PalmRight.position.x - miniHorizontal) / (maxiHorizontal - miniHorizontal);
                    tempo = value;
                    uiController.setTempoSliderValue(tempo);
                    break;
                case 1:
                    GUI.Label(new Rect(10, 10, 500, 100), "Main ouverte !", style);
                    break;

                case 2:
                    GUI.Label(new Rect(10, 10, 500, 100), "Deux doigts !", style);
                    value = (this.hands.PalmRight.position.y - miniVertical) / (maxiVertical - miniVertical);
                    volume = value;
                    uiController.setVolumeSliderValue(volume);

                    message.address = "/127.0.0.1:5000";
                    message.values.Add(value);
                    break;

                case 3:
                    GUI.Label(new Rect(10, 10, 500, 100), "Un doigt !", style);
                    value = (this.hands.PalmRight.position.x - miniHorizontal) / (maxiHorizontal - miniHorizontal);
                    attack = value;
                    uiController.setAttackSliderValue(attack);
                    break;

                case 4:
                    GUI.Label(new Rect(10, 10, 500, 100), "Téléphone !", style);
                    value = (this.hands.PalmRight.position.y - miniVertical) / (maxiVertical - miniVertical);
                    frequency = value;
                    uiController.setFrequencySliderValue(frequency);

                    break;

            }
            message.values.Add(volume);
            message.values.Add(tempo);
            message.values.Add(attack);
            message.values.Add(frequency);
            osc.Send(message);
        }
    }
}
