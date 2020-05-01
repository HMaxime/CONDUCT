using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;

public class EnvironmentController : MonoBehaviour
{
    const float max = 1.0f; //Valeur max des sliders
    const float min = 0.0f; //valeurs min des sliders

    const float YStart = -2.5f; //Bas du mur en face du joueur
    const float YEnd = 5.5f; //Haut du mur en face du joueur

    const float XStart = -8.0f;//Coté gauche du mur en face du joueur
    const float XEnd = 8.0f;//Coté droit du mur en face du joueur
    private static readonly System.Random random = new System.Random();

    UIController uiController;
    // 0 à 7 du plus foncé au plus clair
    public GameObject Splat0;

    //L'environment se base sur les slider
    void Start()
    {
        this.uiController = (UIController)GameObject.Find("Canvas").GetComponent("UIController");
        
        //mets splat dans tableau de taille 7
    }

    void Update()
    {
        float tempo = this.uiController.getTempoSliderValue();
        float volume = this.uiController.getVolumeSliderValue();
        float attack = this.uiController.getAttackSliderValue();
        float frequency = this.uiController.getFrequencySliderValue();
        //paintColor(frequency);
        createSplat(3);
    }

    void paintColor(float frequency)
    {
        //frequency = frequency * 100.0;
        //7 couleurs disponibles donc 100/7 = 14.28
       // int color = frequency / 14.28; // on veut une valeur entière 0, 1, 2 .. 6

        
    }
    //On prend le splat correspondant a l'index dans le tableau et on le clone à des coord random
    void createSplat(int index){

        //va chercher splat à l'index dans le tableau puis clone coord random
        GameObject SplatClone = Instantiate(Splat0, new Vector3(randomBetween(XStart,XEnd), randomBetween(YStart,YEnd), Splat0.transform.position.z), Splat0.transform.rotation);

    }

    //retourne un nombre aléatoire entre les 2 valeurs min et max
    float randomBetween(double min, double max){
        var next = random.NextDouble();
         return Convert.ToSingle(min + (next * (max - min)));
    }

}
