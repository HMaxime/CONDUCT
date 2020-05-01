using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.Timers;
using System.Threading;
using System.Threading.Tasks;

public class EnvironmentController : MonoBehaviour
{
    /*
    // PARTIE PEINTURE/SPLATS
    */
    const float max = 1.0f; //Valeur max des sliders
    const float min = 0.0f; //valeurs min des sliders
    const float YStart = -2.5f; //Coordonnée y du Bas du mur en face du joueur
    const float YEnd = 5.5f; //Coordonnée y du Haut du mur en face du joueur
    const float XStart = -8.0f;//Coordonnée x du Coté gauche du mur en face du joueur
    const float XEnd = 8.0f;//Coordonnée x du Coté droit du mur en face du joueur
    const float z = 9; //Coordonnée z du mur en face du joueur

    private static readonly System.Random random = new System.Random();
    UIController uiController;

    // Splat de peintures de 0 à 7 du plus foncé au plus clair
    public GameObject Splat0;
    public GameObject Splat1;
    public GameObject Splat2;
    public GameObject Splat3;
    public GameObject Splat4;
    public GameObject Splat5;
    public GameObject Splat6;

    GameObject[] splat;
    //temps à attendre entre chaque splat
    int timeBetweenSplat;

    //lock qui permet de controler la creation de splat
    bool isDone;

    //durée d'affichage du splat de peinture
    int splatDuration;

    //taille d'un splat
    float splatScaleFactor;

    /*
    // PARTIE LUMIERE
    */
    public GameObject lumiereGauche;
    public GameObject lumiereDroite;

    //L'environment se base sur les slider
    void Start()
    {
        /*
        // PARTIE PEINTURE/SPLATS
        */
        
        //assigne l'uicontroller
        this.uiController = (UIController)GameObject.Find("Canvas").GetComponent("UIController");
        
        //mets les différents splat de peinture dans tableau de taille 7
        splat = new GameObject[7]; 
        splat[0] = Splat0;
        splat[1] = Splat1;
        splat[2] = Splat2;
        splat[3] = Splat3;
        splat[4] = Splat4;
        splat[5] = Splat5;
        splat[6] = Splat6;

        isDone = false; //booleen indiquant si un nouveau splat peut être peint
        /*
        // PARTIE LUMIERE
        */
    }


    void Update()
    {
        float tempo = this.uiController.getTempoSliderValue(); 
        float volume = this.uiController.getVolumeSliderValue();
        float attack = this.uiController.getAttackSliderValue();
        float frequency = this.uiController.getFrequencySliderValue();
        
        int index = paintColor(0.32f);   
        setTimeBetweenSplat(tempo); //met à jour le temps entre chaque splat en fonction du tempo
        setSplatDuration(tempo); //determine la durée d'affichage d'un splat
        setScaleFactor(volume);
        syncTempoAndSplat(index);
        setLightAmbience(index);
    }

    /*
    // Influence la couleur de la scène en fonction de l'index
    */
    void setLightAmbience(int index){

    }

    /*
    //Determine le facteur d'agrandissement de la tache
    //max x2
    //min normal
    */
    void setScaleFactor(float volume){
        float factor = 1.0f + volume;
        splatScaleFactor = factor;
    }


    /*
    // recoit un tempo entre 0 et 1 et calcul le temps d'affichae d'un splat
    //max est 8 fois par secondes soit tous les 250 ms
    //min est 2500 ms
    */
    void setSplatDuration(float tempo){
        tempo = (1 - tempo) * 10.0f;
        splatDuration = Convert.ToInt32(tempo * 250.0f);
    }

    //recoit un tempo entre 0 et 1 et calcul le temps qui doit séparer chaque apparitions
    //max est 8 fois par secondes soit tous les 200 ms
    //min est 1 fois toute les 2 secondes 2000 ms
    void setTimeBetweenSplat(float tempo){
        tempo = (1 - tempo) * 10;
        timeBetweenSplat = Convert.ToInt32(tempo * 200);
    }

    /*
        Creer un splat tous les X millisecondes, 
        X est contenu dans la variable global timeToWait
    */
    public async Task syncTempoAndSplat(int index)  
    {  
        if(!isDone){
            isDone = true;
            createSplat(index);
            await Task.Delay(timeBetweenSplat);  
            isDone = false;
        }
    }

    /*
    //determine la couleur à donner au splat en fonction de la fréquence
    */
    int paintColor(float frequency)
    {
        frequency = frequency * 100.0f;
        //7 couleurs disponibles donc 100/7 = 14.28
        frequency =  frequency / 14.28f; 
        return Convert.ToInt32(frequency);
    }

    /*
    //Creer un nouveau splat à des corrodonées aléatoires
    */
    void createSplat(int index){
        //si le splat précédent à été créé il y a moins de "timeToWait", alors on fait rien
            
            //pour une rotation autour de z
            Quaternion rotation = Quaternion.Euler(0, 0, randomBetween(0.0,360.0));

            GameObject SplatClone = Instantiate(splat[index], 
                new Vector3(
                    randomBetween(XStart,XEnd), 
                    randomBetween(YStart,YEnd), 
                    z
                ),
                rotation
               );
            SplatClone.transform.localScale *= splatScaleFactor;
            SplatClone.GetComponent<PaintSplatAnimation>().isOriginal = false;
            SplatClone.GetComponent<PaintSplatAnimation>().duration = this.splatDuration;
    }

    /*
        Genre un nombre aléaoitre entre deux double
    */
    float randomBetween(double min, double max){
        var next = random.NextDouble();
        return Convert.ToSingle(min + (next * (max - min)));
    }

}
