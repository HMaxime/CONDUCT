using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

/*
 * UIController permet de controler les éléments UI des interfaces graphiques.
 */ 
public class UIController : MonoBehaviour
{
    Slider volumeSlider;
    Slider tempoSlider;
    Slider vibratoSlider;
    Slider frequencySlider;
    
    // Start is called before the first frame update
    void Start()
    {
        volumeSlider = gameObject.transform.GetChild(0).GetComponent<Slider>();
        tempoSlider = gameObject.transform.GetChild(1).GetComponent<Slider>();
        vibratoSlider = gameObject.transform.GetChild(2).GetComponent<Slider>();
        frequencySlider = gameObject.transform.GetChild(3).GetComponent<Slider>();
    }

    /*
    * Met à jour la valeur du Slider de volume
    */
    public void setVolumeSliderValue(float value)
    {
        this.volumeSlider.value = value;
    }
    
    /*
    * Met à jour la valeur du Slider de Tempo
    */
    public void setTempoSliderValue(float value)
    {
        this.tempoSlider.value = value;
    }

    /*
    * Met à jour la valeur du Slider de Vibrato
    */
    public void setVibratoSlider(float value)
    {
        this.vibratoSlider.value = value;
    }

    /*
    * Met à jour la valeur du Slider de Pitch
    */
    public void setFrequencySliderValue(float value)
    {
        this.frequencySlider.value = value;
    }

    /*
    * Obtention de la valeur du slider de volume
    */
    public float getVolumeSliderValue()
    {
        return this.volumeSlider.value;
    }

    /*
    * Obtention de la valeur du slider de volume
    */
    public float getTempoSliderValue()
    {
        return this.tempoSlider.value;
    }
    
    /*
    * Obtention de la valeur du slider de volume
    */
    public float getVibratoSliderValue()
    {
        return this.vibratoSlider.value;
    }

    /*
    * Obtention de la valeur du slider de volume
    */
    public float getFrequencySliderValue()
    {
        return this.frequencySlider.value;
    }







}
