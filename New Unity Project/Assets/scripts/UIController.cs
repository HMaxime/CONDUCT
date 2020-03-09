using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIController : MonoBehaviour
{
    Slider volumeSlider;
    Slider tempoSlider;
    Slider attackSlider;
    Slider frequencySlider;
    
    // Start is called before the first frame update
    void Start()
    {
        volumeSlider = gameObject.transform.GetChild(0).GetComponent<Slider>();
        tempoSlider = gameObject.transform.GetChild(1).GetComponent<Slider>();
        attackSlider = gameObject.transform.GetChild(2).GetComponent<Slider>();
        frequencySlider = gameObject.transform.GetChild(3).GetComponent<Slider>();
    }

    public void setVolumeSliderValue(float value)
    {
        this.volumeSlider.value = value;
    }

    public void setTempoSliderValue(float value)
    {
        this.tempoSlider.value = value;
    }

    public void setAttackSliderValue(float value)
    {
        this.attackSlider.value = value;
    }

    public void setFrequencySliderValue(float value)
    {
        this.frequencySlider.value = value;
    }






}
