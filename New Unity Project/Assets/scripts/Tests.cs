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
    float minimumHorizontal = 20;
    float maxmimumHorizontal = -20;
    int classe = -1;
    OscMessage message;
    OSC osc;
	bool alreadySent=false;


    private void Start()
    {
		osc=(OSC)GetComponent("OSC");
        message = new OscMessage();
        dataset = new DataSet(@"C:\Users\AIDN-etudiant\Documents\CONDUCT\New Unity Project\Assets\scripts\Datas");
        actualLeftHand = new float[5];
        actualRightHand = new float[5];
        classifier = new Classifier();
        this.hands = (Mouvement)GetComponent("Mouvement");
        this.uiController=(UIController)GameObject.Find("Canvas").GetComponent("UIController");
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
        style.fontSize = 50;

        switch (this.classe)
        {
            case 0:
                GUI.Label(new Rect(10, 10, 500, 100), "Poing Fermé !", style);
				if(this.alreadySent==false){
					message.values.Add(1);
					message.address="/127.0.0.1:5000";
					print("Message : "+message);
					osc.Send(message);
					this.alreadySent=true;
				}
                float value = this.hands.PalmRight.position.x * 3;
                uiController.setStereoSliderValue(value);
                break;
            case 1:
                GUI.Label(new Rect(10, 10, 500, 100), "Main ouverte !", style);
                break;

            case 2:
                GUI.Label(new Rect(10, 10, 500, 100), "Deux doigts !", style);
                uiController.setVolumeSliderValue(this.hands.PalmRight.position.y*3);
                break;

            default:
                GUI.Label(new Rect(10, 10, 500, 100), "Chargement !", style);
                break;
        }

    }

}
